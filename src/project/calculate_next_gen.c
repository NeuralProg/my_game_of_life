/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** calculate_next_gen.c
*/

#include "game_of_life.h"

static int get_neighbours(active_cell_t *grid, long int x, long int y)
{
    int neighbours = 0;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            if (cell_exists(grid, x + i, y + j) == 1)
                neighbours++;
        }
    }
    return neighbours;
}

static void check_active_cells_next(active_cell_t *grid,
    active_cell_t **new_grid, long int x, long int y)
{
    if (cell_exists(grid, x, y) == 1 &&
            (get_neighbours(grid, x, y) == 2 ||
            get_neighbours(grid, x, y) == 3))
        set_cell(new_grid, x, y);

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0)
                continue;
            if (cell_exists(grid, x + i, y + j) == 0 &&
                    get_neighbours(grid, x + i, y + j) == 3 &&
                    cell_exists(*new_grid, x + i, y + j) == 0)
                set_cell(new_grid, x + i, y + j);
        }
    }
}

void calculate_next_gen(interface_t *interface, game_t *game)
{
    active_cell_t *new_grid = NULL;
    active_cell_t *current;
    active_cell_t *tmp;

    HASH_ITER(hh, game->grid, current, tmp) {
        check_active_cells_next(game->grid, &new_grid, current->x, current->y);
    }
    free_grid(&game->grid);
    game->grid = new_grid;
    game->gen++;
    game->alive = HASH_COUNT(game->grid);
    game->last_update = interface->win->time;

    if (game->alive == 0)
        game->playing = 0;
    HASH_ITER(hh, game->grid, current, tmp) {
        printf("x: %ld, y: %ld\n", current->x, current->y);
    }
    printf("gen: %d\n", game->gen);
}
