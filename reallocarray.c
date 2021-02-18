/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** reallocarray.c
*/

#include <errno.h>
#include <limits.h>
#include <unistd.h>

#include "my_alloc.h"

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if ((long)(align_size(nmemb * size, 8)) > INT_MAX) {
        errno = ENOMEM;
        return (NULL);
    }
    return (realloc(ptr, nmemb * size));
}