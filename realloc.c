/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** realloc.c
*/

#include "my_alloc.h"

#include <string.h>
#include <unistd.h>

static void *create_new_copy_ptr(void *ptr, size_t size)
{
    void *new_ptr = malloc(size);

    new_ptr = memcpy(new_ptr, ptr, size);
    free(ptr);
    return (new_ptr);
}

static metadata_t *split_space(metadata_t *meta, size_t size)
{
    metadata_t *new = (void *)((char *)(meta) + MD_SIZE + size);

    new->next = meta->next;
    if (meta->next)
        meta->next->prev = new;
    new->prev = meta;
    new->size = meta->size - MD_SIZE - size;
    new->free = 1;
    new->ptr = (void *)((char *)(new) + MD_SIZE);
    meta->next = new;
    meta->free = 0;
    meta->size = size;
    if (meta == last)
        last = new;
    return (meta);
}

static metadata_t *split_space2(metadata_t *meta, size_t size)
{
    metadata_t *new = (void *)((char *)(meta->ptr) + size);

    new->next = NULL;
    if (meta->next == last)
        last = new;
    if (meta->next->next) {
        meta->next->next->prev = new;
        new->next = meta->next->next;
    }
    new->prev = meta;
    new->free = 1;
    new->size = meta->next->size - (size - meta->size);
    new->ptr = (void *)((char *)(new) + MD_SIZE);
    meta->next = new;
    meta->size = size;
    return (meta);
}

void *realloc(void *ptr, size_t size)
{
    size_t aligned_size = align_size(size, 8);
    metadata_t *meta;

    if (!ptr)
        return (malloc(size));
    else if (!size)
        return (free(ptr), NULL);
    meta = (metadata_t *)((char *)(ptr) - MD_SIZE);
    if (aligned_size == meta->size
    || (aligned_size < meta->size && meta->size - aligned_size < MD_SIZE))
        return (ptr);
    else if (aligned_size < meta->size
    && meta->size - aligned_size < MD_SIZE)
        return (split_space(meta, aligned_size)->ptr);
    if (meta->next->free
    && meta->size + meta->next->size >= aligned_size)
        return (split_space2(meta, aligned_size)->ptr);
    else
        return (create_new_copy_ptr(ptr, aligned_size));
    return (meta->ptr);
}