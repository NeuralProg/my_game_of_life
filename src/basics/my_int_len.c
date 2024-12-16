/*
** EPITECH PROJECT, 2024
** B-MUL-100-MLH-1-1-myradar-yann.toison-chabane
** File description:
** my_int_len.c
*/

#include "../../include/game_of_life.h"

int my_int_len(int nb)
{
    int len = 0;

    if (nb == 0)
        return 1;
    if (nb < 0) {
        nb *= -1;
    }
    while (nb > 0) {
        nb /= 10;
        len++;
    }
    return len;
}
