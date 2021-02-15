/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** free.c
*/

#include "my_alloc.h"

metadata_t *search_ptr(void *ptr)
{
    if (!ptr)
        return (NULL);
    for (metadata_t *meta = first; meta; meta = meta->next)
        if (meta->ptr == ptr)
            return (meta);
    return (NULL);
}

metadata_t *move_meta(metadata_t *meta)
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

void free(void *ptr)
{
    metadata_t *meta = search_ptr(ptr);

    if (!meta)
        return;
    meta->free = 1;
    meta = move_meta(meta);
    if (!meta->prev && !first->next)
        first = NULL;
    if (!meta->next) {
        last = meta->prev;
        if (meta->prev)
            meta->prev->next = NULL;
        sbrk(-(meta->size + MD_SIZE));
    }
}