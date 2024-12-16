/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** grid_actions.c
*/

#include "game_of_life.h"

int cell_exists(active_cell_t *grid, long int x, long int y)
{
    active_cell_t *cell;
    cell_key_t full_key = {x, y};

    if (grid == NULL)
        return 0;
    HASH_FIND(hh, grid, &full_key, sizeof(cell_key_t), cell);
    if (cell == NULL)
        return 0;
    return 1;
}

long int get_cell_age(active_cell_t *grid, long int x, long int y)
{
    active_cell_t *cell;
    cell_key_t full_key = {x, y};

    if (cell_exists(grid, x, y) == 0)
        return -1;
    HASH_FIND(hh, grid, &full_key, sizeof(cell_key_t), cell);
    return cell->age;
}

void set_cell(active_cell_t **grid, long int x, long int y, long int age)
{
    active_cell_t *new_cell;
    cell_key_t full_key = {x, y};

    if (cell_exists(*grid, x, y) == 1) {
        return;
    }
    new_cell = malloc(sizeof(active_cell_t));
    if (new_cell == NULL)
        return;
    new_cell->x = x;
    new_cell->y = y;
    new_cell->age = age;
    HASH_ADD(hh, *grid, x, sizeof(long int) * 2, new_cell);
}

void remove_cell(active_cell_t **grid, long int x, long int y)
{
    active_cell_t *cell;
    cell_key_t full_key = {x, y};

    if (cell_exists(*grid, x, y) == 0)
        return;
    HASH_FIND(hh, *grid, &full_key, sizeof(cell_key_t), cell);
    HASH_DEL(*grid, cell);
    free(cell);
}

void free_grid(active_cell_t **grid)
{
    active_cell_t *current;
    active_cell_t *tmp;

    HASH_ITER(hh, *grid, current, tmp) {
        HASH_DEL(*grid, current);
        free(current);
    }
}