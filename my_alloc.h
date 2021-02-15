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

void printMemory();
void printMemoryBis(metadata_t *ptr);
int my_put_nbr(unsigned nb);

#endif // MY_ALLOC_H