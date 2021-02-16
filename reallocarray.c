/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** reallocarray.c
*/

#include <errno.h>
#include <limits.h>
#include <unistd.h>

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    if ((long)(nmemb * size) > INT_MAX) {
        errno = ENOMEM;
        return (NULL);
    }
    return (realloc(ptr, nmemb * size));
}