/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** header.h
*/

#ifndef MY_ALLOC_H
#define MY_ALLOC_H

#include <unistd.h>

typedef struct metadata_s metadata_t;
struct metadata_s
{
    size_t size;
    metadata_t *next;
    metadata_t *prev;
    char free;
    void *ptr;
};

extern const size_t MD_SIZE;

extern metadata_t *first;
extern metadata_t *last;

metadata_t *search_meta(void *ptr);
metadata_t *fusion_free_data(metadata_t *meta);

#endif // MY_ALLOC_H