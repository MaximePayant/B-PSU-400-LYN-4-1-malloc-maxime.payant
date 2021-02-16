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

void *realloc(void *ptr, size_t size)
{
    metadata_t *meta;

    if (!ptr)
        return (malloc(size));

    meta = (metadata_t *)((char *)(ptr) - MD_SIZE);
    if (meta->next) {
        if (!meta->next->free
        || meta->next->size + meta->size <= size)
            return (create_new_copy_ptr(ptr, size));
        else {
            meta->next->ptr =
            (void *)((char *)(meta->next->ptr) + size - meta->size);
            meta->next->size -= size - meta->size;
            meta->size = size;
        }
    } else {
        sbrk(size - meta->size);
        meta->size = size;
    }
    return (meta->ptr);
}