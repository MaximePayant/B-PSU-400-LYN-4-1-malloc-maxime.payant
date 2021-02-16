/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** malloc.c
*/

#include "my_alloc.h"

const size_t MD_SIZE = sizeof(metadata_t);
metadata_t *first = NULL;
metadata_t *last = NULL;

metadata_t *search_free_space(size_t size)
{
    metadata_t *result = NULL;

    for (metadata_t *meta = first; meta; meta = meta->next)
        if (meta->free
        && meta->size > size + MD_SIZE
        && (!result || meta->size < result->size))
            result = meta;
    return (result);
}

metadata_t *create_space(metadata_t *meta, size_t size)
{
    meta = sbrk(MD_SIZE + size);
    if (meta != (void *)(-1)) {
        if (!first)
            first = meta;
        if (last)
            last->next = meta;
        meta->size = size;
        meta->next = NULL;
        meta->prev = last;
        meta->free = 0;
        meta->ptr = (void *)((char *)meta + MD_SIZE);
        last = meta;
    }
    else
        return (NULL);
    return (meta);
}

metadata_t *split_space(metadata_t *meta, size_t size)
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
    return (meta);
}

void *malloc(size_t size)
{
    size_t align_size = (size + size % 2);
    metadata_t *meta = search_free_space(align_size);

    meta = (meta ? split_space(meta, align_size) : create_space(meta, align_size));
    if (meta)
        return (meta->ptr);
    return (NULL);
}