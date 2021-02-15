/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** realloc.c
*/

#include "my_alloc.h"

#include <unistd.h>

static void *create_new_copy_ptr(metadata_t *meta, void *ptr, size_t size)
{
    void *new_ptr = malloc(size);

    for (size_t ctr = 0; ctr < size; ctr += 1)
        ((char *)(ptr))[ctr] = ((char *)(meta->ptr))[ctr];
    free(meta->ptr);
    return (new_ptr);
}

void *realloc(void *ptr, size_t size)
{
    metadata_t *meta = search_meta(ptr);

    if (meta->next) {
        if (!meta->next->free
        || meta->next->size + meta->size <= size)
            return (create_new_copy_ptr(meta, ptr, size));
        else {
                meta->next->ptr = (void *)((size_t)(meta->next->ptr) + size - meta->size);
                meta->next->size -= size - meta->size;
                meta->size = size;
        }
    } else {
        sbrk(size - meta->size);
        meta->size = size;
    }
    return (meta->ptr);
}