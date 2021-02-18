/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** calloc.c
*/

#include <string.h>
#include <unistd.h>

#include "my_alloc.h"

void *calloc(size_t nmemb, size_t size)
{
    void *ptr;

    if (!nmemb || !size)
        return (NULL);
    ptr = malloc(size * nmemb);
    ptr = memset(ptr, 0, align_size(size * nmemb, 8));
    return (ptr);
}