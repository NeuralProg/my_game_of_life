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

    game->playing = 1;
    game->grid = NULL;
    set_cell(&game->grid, 0, 0);
    set_cell(&game->grid, 1, 0);
    set_cell(&game->grid, 2, 0);

    game->gen = 0;
    game->alive = 0;
    game->speed = 50;
    game->last_update = 0;
    return 0;
}