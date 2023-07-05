/*
** EPITECH PROJECT, 2023
** Valentin Scheller
** File description:
** tools.c
*/

#include "../../include/server.h"

int count_array(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return i;
}
