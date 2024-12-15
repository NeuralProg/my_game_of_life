/*
** EPITECH PROJECT, 2024
** B-MUL-100-MLH-1-1-myradar-yann.toison-chabane
** File description:
** my_strlen.c
*/

#include "../../include/game_of_life.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}
