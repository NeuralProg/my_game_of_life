/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** init_structs.c
*/

#include "game_of_life.h"

static void init_game(game_t *game)
{
    game->playing = 0;
    game->stats_active = 0;
    game->grid = NULL;
    game->gen = 0;
    game->alive = 0;
    game->speed = 50;
    game->last_update = 0;
}

int init_structs(interface_t *interface, game_t *game)
{
    if (interface == NULL || game == NULL)
        return 84;
    if (initialize_interface(interface) == 84)
        return 84;
    init_game(game);
    return 0;
}