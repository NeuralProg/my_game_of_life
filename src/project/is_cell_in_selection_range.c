/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** is_cell_in_range.C
*/

#include "game_of_life.h"

long int *get_selection_boundaries(game_t *game)
{
    long int x_min = game->selection->start_pos[0] < game->selection->end_pos[0] ?
            game->selection->start_pos[0] : game->selection->end_pos[0];
    long int x_max = game->selection->start_pos[0] > game->selection->end_pos[0] ?
            game->selection->start_pos[0] : game->selection->end_pos[0];
    long int y_min = game->selection->start_pos[1] < game->selection->end_pos[1] ?
            game->selection->start_pos[1] : game->selection->end_pos[1];
    long int y_max = game->selection->start_pos[1] > game->selection->end_pos[1] ?
            game->selection->start_pos[1] : game->selection->end_pos[1];
    long int *boundaries = malloc(4 * sizeof(long int));

    if (boundaries == NULL)
        return NULL;
    boundaries[0] = x_min;
    boundaries[1] = y_min;
    boundaries[2] = x_max;
    boundaries[3] = y_max;
    return boundaries;
}

long int get_selection_width(game_t *game)
{
    long int *selection = get_selection_boundaries(game);
    long int res = 0;

    if (selection == NULL)
        return 0;
    res = selection[2] - selection[0];
    free(selection);
    return res;
}

long int get_selection_height(game_t *game)
{
    long int *selection = get_selection_boundaries(game);
    long int res = 0;

    if (selection == NULL)
        return 0;
    res = selection[3] - selection[1];
    free(selection);
    return res;
}

int is_cell_in_selection_range(game_t *game, long int x, long int y)
{
    long int x_min = game->selection->start_pos[0] < game->selection->end_pos[0] ?
            game->selection->start_pos[0] : game->selection->end_pos[0];
    long int x_max = game->selection->start_pos[0] > game->selection->end_pos[0] ?
            game->selection->start_pos[0] : game->selection->end_pos[0];
    long int y_min = game->selection->start_pos[1] < game->selection->end_pos[1] ?
            game->selection->start_pos[1] : game->selection->end_pos[1];
    long int y_max = game->selection->start_pos[1] > game->selection->end_pos[1] ?
            game->selection->start_pos[1] : game->selection->end_pos[1];

    if (x >= x_min && x <= x_max &&
        y >= y_min && y <= y_max)
        return 1;
    return 0;
}
