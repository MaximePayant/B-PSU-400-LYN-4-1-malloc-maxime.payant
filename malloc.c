/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** malloc.c
*/

#include <stdio.h>

#include "test/utils.h"

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

metadata_t *create_space(size_t aligned_size)
{
    size_t size = align_size(aligned_size, getpagesize() * 2);
    metadata_t *meta = sbrk(size);

    if (meta != (void *)(-1)) {
        if (!first)
            first = meta;
        if (last)
            last->next = meta;
        meta->size = size - MD_SIZE;
        meta->next = NULL;
        meta->prev = last;
        meta->free = 1;
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
    if (meta == last)
        last = new;
    return (meta);
}

void *malloc(size_t size)
{
    //write(1, "Malloc ", 7);
    size_t aligned_size = align_size(size, 8);
    metadata_t *meta = search_free_space(aligned_size);

    if (!meta)
        meta = create_space(aligned_size);
    if (meta) {
        meta = split_space(meta, aligned_size);
        //write(1, "Done\n", 5);
        return (meta->ptr);
    }
    //write(1, "Fail\n", 5);
    return (NULL);
}