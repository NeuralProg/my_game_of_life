/*
** EPITECH PROJECT, 2023
** B-MUL-100-MLH-1-1-myradar-yann.toison-chabane
** File description:
** random_int.c
*/

#include "game_of_life.h"

int random_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
