/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** free.c
*/

#include "my_alloc.h"

void free(void *ptr)
{
    metadata_t *meta;

    if (!ptr)
        return;
    meta = (metadata_t *)((char *)ptr - MD_SIZE);
    meta->free = 1;
    meta = fusion_free_data(meta);
    if (!meta->prev && !first->next)
        first = NULL;
    if (!meta->next) {
        last = meta->prev;
        if (meta->prev)
            meta->prev->next = NULL;
        sbrk(-(meta->size + MD_SIZE));
    }
}