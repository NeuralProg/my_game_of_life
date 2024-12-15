/*
** EPITECH PROJECT, 2024
** B-MUL-100-MLH-1-1-myradar-yann.toison-chabane
** File description:
** my_puterr.c
*/

#include "game_of_life.h"

int my_puterr(char *str)
{
    write(2, str, my_strlen(str));
    return 84;
}
