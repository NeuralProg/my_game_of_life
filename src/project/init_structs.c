/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** init_structs.c
*/

#include "game_of_life.h"

int init_structs(interface_t *interface, game_t *game)
{
    if (interface == NULL || game == NULL)
        return 84;
    if (initialize_interface(interface) == 84)
        return 84;
    return 0;
}