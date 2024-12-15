/*
** EPITECH PROJECT, 2023
** B-MUL-100-MLH-1-1-myradar-yann.toison-chabane
** File description:
** my_str_concatenate.c
*/

#include "game_of_life.h"

char *my_str_concatenate(char *str1, char *str2)
{
    char *str = malloc(sizeof(char) * (my_strlen(str1) +
                                    my_strlen(str2) + 1));
    int i = 0;
    int j = 0;

    if (str == NULL)
        return NULL;
    while (str1[i] != '\0') {
        str[i] = str1[i];
        i++;
    }
    while (str2[j] != '\0') {
        str[i] = str2[j];
        i++;
        j++;
    }
    str[i] = '\0';
    return str;
}
