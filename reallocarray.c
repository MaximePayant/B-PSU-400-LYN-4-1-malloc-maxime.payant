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
    if (nmemb > ULONG_MAX / size) {
        errno = ENOMEM;
        return (NULL);
    }
    return (realloc(ptr, nmemb * size));
}