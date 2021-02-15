/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** calloc.c
*/

#include "my_alloc.h"

#include <unistd.h>

void *calloc(size_t nmemb, size_t size)
{
    void *ptr;

    if (!nmemb || !size)
        return (NULL);
    ptr = malloc(size * nmemb);
    for (size_t ctr = 0; ctr < size * nmemb; ctr += 1)
        ((char *)(ptr))[ctr] = 0;
    return (ptr);
}