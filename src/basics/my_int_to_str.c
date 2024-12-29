/*
** EPITECH PROJECT, 2024
** B-MUL-100-MLH-1-1-myradar-yann.toison-chabane
** File description:
** my_int_to_str.c
*/

#include "game_of_life.h"

char *my_unsigned_int_to_str(unsigned int nb)
{
    char *str = malloc(sizeof(char) * (my_int_len(nb) + 1));
    int i = my_int_len(nb) - 1;

    if (str == NULL)
        return NULL;
    str[i + 1] = '\0';
    while (i >= 0) {
        str[i] = nb % 10 + '0';
        nb /= 10;
        i--;
    }
    return str;
}

char *my_int_to_str(int nb)
{
    char *str = malloc(sizeof(char) * (my_int_len(nb) + 2));
    int i = my_int_len(nb) - 1;
    int min = 0;

    if (str == NULL)
        return NULL;
    if (nb < 0) {
        str[0] = '-';
        nb *= -1;
        min = 1;
    }
    str[i + 1 + min] = '\0';
    while (i >= 0) {
        str[i + min] = nb % 10 + '0';
        nb /= 10;
        i--;
    }
    return str;
}
