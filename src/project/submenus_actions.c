/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** submenus_actions.c
*/

#include "game_of_life.h"

int action_toogle_grid(interface_t *interface, game_t *game)
{
    interface->display_grid = !interface->display_grid;
    return 0;
}

int action_toogle_colors(interface_t *interface, game_t *game)
{
    interface->display_colors = !interface->display_colors;
    return 0;
}
