/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** free.c
*/

#include "my_alloc.h"

static metadata_t *fusion_free_data(metadata_t *meta)
{
    for (; meta->next && meta->next->free == 1; meta = meta->next);
    for (metadata_t *prev = meta->prev; prev
    && prev->free == 1; prev = prev->prev) {
        prev->size += meta->size + MD_SIZE;
        prev->next = meta->next;
        if (meta->next)
            meta->next->prev = prev;
        meta = prev;
    }
    return (meta);
}

static size_t align_size_down(size_t size, size_t nb)
{
    size_t result = size;

    if (size % nb != 0)
        result = (size - (size % nb));
    return (result);
}

void free(void *ptr)
{
    metadata_t *meta;

    if (!ptr)
        return;
    meta = (metadata_t *)((char *)ptr - MD_SIZE);
    meta->free = 1;
    meta = fusion_free_data(meta);
    if (!meta->next) {
        if (meta->size >= (size_t)(getpagesize() * 2)) {
            size_t aligned_size =
            align_size_down(meta->size, (size_t)(getpagesize() * 2));
            meta->size -= aligned_size;
            sbrk(-aligned_size);
        }
        last = meta;
    }
}