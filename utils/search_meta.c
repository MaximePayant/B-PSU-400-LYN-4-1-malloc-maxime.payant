/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** search_meta.c
*/

#include "my_alloc.h"

metadata_t *search_meta(void *ptr)
{
    if (!ptr)
        return (NULL);
    for (metadata_t *meta = first; meta; meta = meta->next)
        if (meta->ptr == ptr)
            return (meta);
    return (NULL);
}