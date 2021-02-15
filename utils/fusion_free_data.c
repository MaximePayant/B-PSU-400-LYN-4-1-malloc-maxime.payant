/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** fusion_free_data.c
*/

#include "my_alloc.h"

metadata_t *fusion_free_data(metadata_t *meta)
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