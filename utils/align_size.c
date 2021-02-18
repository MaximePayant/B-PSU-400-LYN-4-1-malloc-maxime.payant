/*
** EPITECH PROJECT, 2021
** Tek2
** File description:
** search_meta.c
*/

#include <unistd.h>

size_t align_size(size_t size, size_t nb)
{
    size_t result = size;

    if (size % nb != 0)
        result = (size - (size % nb)) + nb;
    return (result);
}