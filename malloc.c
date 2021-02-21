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

static metadata_t *search_free_space(size_t size)
{
    metadata_t *result = NULL;

    for (metadata_t *meta = first; meta; meta = meta->next)
        if (meta->free
        && meta->size > size
        && (!result || meta->size < result->size))
            result = meta;
    return (result);
}

static size_t align_break_size(size_t aligned_size)
{
    size_t size;

    if (!last
    || !last->free)
        size = align_size(aligned_size, getpagesize() * 2);
    else {
        if (aligned_size <= last->size)
            aligned_size = 1;
        else
            aligned_size = aligned_size - last->size;
        size = align_size(aligned_size, getpagesize() * 2);
    }
    return (size);
}

static metadata_t *create_space(size_t aligned_size)
{
    size_t size = align_break_size(aligned_size + MD_SIZE);
    metadata_t *check = sbrk(size);

    if (check == (void *)(-1))
        return (NULL);
    else {
        if (last && last->free)
            last->size += size;
        else {
            check->size = size - MD_SIZE;
            check->next = NULL;
            check->prev = last;
            check->free = 1;
            check->ptr = (void*)((char*)(check) + MD_SIZE);
            if (last)
                last->next = check;
            last = check;
        }
        first = (first ? first : check);
    }
    return (last);
}

static metadata_t *split_space(metadata_t *meta, size_t size)
{
    metadata_t *new;

    if (meta->size - size > MD_SIZE) {
        new = (void *)((char *)(meta->ptr) + size);
        new->next = meta->next;
        if (meta->next)
            meta->next->prev = new;
        new->prev = meta;
        new->size = meta->size - (MD_SIZE + size);
        new->free = 1;
        new->ptr = (void *)((char *)(new) + MD_SIZE);
        meta->next = new;
        if (meta == last)
            last = new;
        meta->size = size;
    }
    meta->free = 0;
    return (meta);
}

void *malloc(size_t size)
{
    size_t aligned_size = align_size(size, 8);
    metadata_t *meta = search_free_space(aligned_size);

    if (!meta)
        meta = create_space(aligned_size);
    if (meta)
        return (split_space(meta, aligned_size)->ptr);
    return (NULL);
}