/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** key_actions.c
*/

#include "game_of_life.h"

void reset_board(game_t *game, interface_t *interface)
{
    free_grid(&game->grid);
    game->grid = NULL;
    game->gen = 0;
    interface->screen_pos[0] = 0;
    interface->screen_pos[1] = 0;
    game->playing = 0;
}

void focus_random_cell(game_t *game, interface_t *interface)
{
    long int x = random_int(0, game->alive);
    active_cell_t *current;
    active_cell_t *tmp;

    if (game->alive == 0)
        return;
    HASH_ITER(hh, game->grid, current, tmp) {
        if (x == 0) {
            interface->screen_pos[0] = current->x - 20;
            interface->screen_pos[1] = current->y - 20;
            return;
        }
        x--;
    }
}