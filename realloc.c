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
    write(1, "Realloc ", 8);
    size_t aligned_size = align_size(size, 8);
    metadata_t *meta;

    if (!ptr) {
        write(1, "Done\n", 5);
        return (malloc(size));
    }

    meta = (metadata_t *)((char *)(ptr) - MD_SIZE);
    if (meta->next) {
        if (!meta->next->free
        || meta->next->size + meta->size <= aligned_size) {
            write(1, "Done\n", 5);
            return (create_new_copy_ptr(ptr, aligned_size));
        }
        else {
            meta->next->ptr =
            (void *)((char *)(meta->next->ptr) + aligned_size - meta->size);
            meta->next->size -= aligned_size - meta->size;
            meta->size = aligned_size;
        }
    } else {
        sbrk(align_size(aligned_size, getpagesize() * 2));
        meta->size = aligned_size;
    }
    write(1, "Done\n", 5);
    return (meta->ptr);
}