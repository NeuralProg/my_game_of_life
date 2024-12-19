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
    trigger_pop_up(game, interface, "Reset done.");
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
    trigger_pop_up(game, interface, "Focused :");
}

void action_copy_selection(game_t *game, interface_t *interface, long int *selection)
{
    if (game->selection->selected_cells != NULL)
        free_grid(&game->selection->selected_cells);
    game->selection->selected_cells = NULL;
    for (long int i = selection[0]; i <= selection[2]; i++) {
        for (long int j = selection[1]; j <= selection[3]; j++) {
            if (cell_exists(game->grid, i, j) == 1) {
                set_cell(&game->selection->selected_cells,
                    i - selection[0], j - selection[1], get_cell_age(game->grid, i, j));
            }
        }
    }
    trigger_pop_up(game, interface, "Copied selection.");
    game->selection->active = 0;
    game->selection->width = get_selection_width(game);
    game->selection->height = get_selection_height(game);
    game->selection->end_pos[0] = game->selection->start_pos[0];
    game->selection->end_pos[1] = game->selection->start_pos[1];
}

void action_delete_selection(game_t *game, interface_t *interface, long int *selection)
{
    for (long int i = selection[0]; i <= selection[2]; i++) {
        for (long int j = selection[1]; j <= selection[3]; j++) {
            remove_cell(&game->grid, i, j);
        }
    }
    trigger_pop_up(game, interface, "Deleted selection.");
    game->selection->active = 0;
    game->selection->end_pos[0] = game->selection->start_pos[0];
    game->selection->end_pos[1] = game->selection->start_pos[1];
}

void action_paste_selection(game_t *game, interface_t *interface, long int *pos)
{
    if (game->selection->selected_cells == NULL) {
        trigger_pop_up(game, interface, "Nothing to paste.");
        return;
    }
    for (long int i = 0; i <= game->selection->width; i++) {
        for (long int j = 0; j <= game->selection->height; j++) {
            if (cell_exists(game->selection->selected_cells, i, j) == 1)
                set_cell(&game->grid, pos[0] + i, pos[1] + j, get_cell_age(game->selection->selected_cells, i, j));
            else
                remove_cell(&game->grid, pos[0] + i, pos[1] + j);
        }
    }
    trigger_pop_up(game, interface, "Pasted selection.");
}

void action_cut_selection(game_t *game, interface_t *interface, long int *selection)
{
    action_copy_selection(game, interface, selection);
    action_delete_selection(game, interface, selection);
    trigger_pop_up(game, interface, "Cut selection.");
}
