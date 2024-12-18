/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** manage_events.c
*/

#include "game_of_life.h"

static sfVector2f recalculate_mouse_position(interface_t *interface)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(interface->win->window);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(interface->win->window, pixel_pos, sfRenderWindow_getView(interface->win->window));

    return world_pos;
}

static void manage_left_click(interface_t *interface, game_t *game)
{
    int sizes[3] = {4, 3, 1};
    int edited = 0;
    
    sfVector2u screen_dim = sfRenderWindow_getSize(interface->win->window);
    int new_zoom = screen_dim.x / (2 * (110 - interface->zoom));
    sfVector2f mouse_pos = recalculate_mouse_position(interface);
    sfVector2i mouse_local_pos = sfMouse_getPositionRenderWindow(interface->win->window);

    for (int i = 0; i < 6; i++) {
        if (mouse_pos.x >= interface->button_items[i]->pos.x &&
            mouse_pos.x <= interface->button_items[i]->pos.x + interface->button_items[i]->dimensions.x &&
            mouse_pos.y >= interface->button_items[i]->pos.y &&
            mouse_pos.y <= interface->button_items[i]->pos.y + interface->button_items[i]->dimensions.y) {
            interface->button_items[i]->active = 1;
            interface->button_items[i]->action(interface, game);
            edited = 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (interface->menu_items[i]->active == 1) {
            for (int j = 0; j < sizes[i]; j++) {
                if (mouse_pos.x >= interface->menu_items[i]->sub_menus[j]->pos.x &&
                    mouse_pos.x <= interface->menu_items[i]->sub_menus[j]->pos.x + interface->menu_items[i]->sub_menus[j]->dimensions.x &&
                    mouse_pos.y >= interface->menu_items[i]->sub_menus[j]->pos.y &&
                    mouse_pos.y <= interface->menu_items[i]->sub_menus[j]->pos.y + interface->menu_items[i]->sub_menus[j]->dimensions.y) {
                    interface->menu_items[i]->sub_menus[j]->action(interface, game);
                    edited = 1;
                }
            }
        }
        if (mouse_pos.x >= interface->menu_items[i]->pos.x &&
            mouse_pos.x <= interface->menu_items[i]->pos.x + interface->menu_items[i]->dimensions.x &&
            mouse_pos.y >= interface->menu_items[i]->pos.y &&
            mouse_pos.y <= interface->menu_items[i]->pos.y + interface->menu_items[i]->dimensions.y
            && interface->menu_items[i]->active == 0) {
            interface->menu_items[i]->active = 1;
            edited = 1;
        } else {
            interface->menu_items[i]->active = 0;
        }
    }
    if (edited == 0 && game->playing == 0) {
        if (new_zoom <= 0)
            new_zoom = 1;
        for (int i = 0; i <= (screen_dim.y - 30) / new_zoom + 30; i++) {
            for (int j = 0; j <= screen_dim.x / new_zoom; j++) {
                if (mouse_local_pos.x > j * new_zoom &&
                    mouse_local_pos.x < j * new_zoom + new_zoom &&
                    mouse_local_pos.y > i * new_zoom &&
                    mouse_local_pos.y < i * new_zoom + new_zoom) {
                    if (cell_exists(game->grid, interface->screen_pos[0] + j, interface->screen_pos[1] + i) == 1)
                        remove_cell(&game->grid, interface->screen_pos[0] + j, interface->screen_pos[1] + i);
                    else
                        set_cell(&game->grid, interface->screen_pos[0] + j, interface->screen_pos[1] + i, 0);
                }
            }
        }
    }
}

static void copy_selection(game_t *game, interface_t *interface)
{
    long int *selection = get_selection_boundaries(game);

    if (selection == NULL)
        return;
    if (game->selection->active == 1 &&
        sfKeyboard_isKeyPressed(sfKeyLControl) && sfKeyboard_isKeyPressed(sfKeyC) &&
        interface->win->event.type == sfEvtKeyPressed) {
        if (game->selection->selected_cells != NULL)
            free_grid(&game->selection->selected_cells);
        game->selection->selected_cells = NULL;
        for (long int i = selection[0]; i <= selection[2]; i++) {
            for (long int j = selection[1]; j <= selection[3]; j++) {
                if (cell_exists(game->grid, i, j) == 1) {
                    set_cell(&game->selection->selected_cells, i - selection[0], j - selection[1], get_cell_age(game->grid, i, j));
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
    free(selection);
}

static void delete_selection(game_t *game, interface_t *interface)
{
    long int *selection = get_selection_boundaries(game);

    if (selection == NULL)
        return;
    if (game->selection->active == 1 &&
        sfKeyboard_isKeyPressed(sfKeyBackspace) && interface->win->event.type == sfEvtKeyPressed) {
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
    free(selection);
}

static void paste_selection(game_t *game, interface_t *interface, long int *pos)
{
    if (sfKeyboard_isKeyPressed(sfKeyLControl) && sfKeyboard_isKeyPressed(sfKeyV) &&
        interface->win->event.type == sfEvtKeyPressed) {
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
}

long int *get_mouse_pos_on_grid(interface_t *interface)
{
    sfVector2u screen_dim = sfRenderWindow_getSize(interface->win->window);
    int new_zoom = screen_dim.x / (2 * (110 - interface->zoom));
    sfVector2f mouse_pos = recalculate_mouse_position(interface);
    sfVector2i mouse_local_pos = sfMouse_getPositionRenderWindow(interface->win->window);
    long int *pos = malloc(sizeof(long int) * 2);

    if (pos == NULL)
        return (long int *)-1;
    if (new_zoom <= 0)
        new_zoom = 1;
    for (int i = 0; i <= (screen_dim.y - 30) / new_zoom + 30; i++) {
        for (int j = 0; j <= screen_dim.x / new_zoom; j++) {
            if (mouse_local_pos.x > j * new_zoom &&
                mouse_local_pos.x < j * new_zoom + new_zoom &&
                mouse_local_pos.y > i * new_zoom &&
                mouse_local_pos.y < i * new_zoom + new_zoom) {
                pos[0] = interface->screen_pos[0] + j;
                pos[1] = interface->screen_pos[1] + i;
                return pos;
            }
        }
    }
    pos[0] = -1;
    pos[1] = -1;
    return pos;
}

void manage_events(interface_t *interface, game_t *game)
{
    long int *mouse_pos = get_mouse_pos_on_grid(interface);

    if (mouse_pos[0] == -1 || mouse_pos[1] == -1)
        return;
    while (sfRenderWindow_pollEvent(interface->win->window, &interface->win->event)) {
        if (interface->win->event.type == sfEvtClosed ||
                    sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(interface->win->window);

        if (interface->win->event.type == sfEvtMouseButtonPressed &&
            interface->win->event.mouseButton.button == sfMouseLeft) {
            game->selection->start_pos[0] = mouse_pos[0];
            game->selection->start_pos[1] = mouse_pos[1];
        }
        if (interface->win->event.type == sfEvtMouseButtonReleased &&
            interface->win->event.mouseButton.button == sfMouseLeft) {
            game->selection->end_pos[0] = mouse_pos[0];
            game->selection->end_pos[1] = mouse_pos[1];
            if ((game->selection->start_pos[0] != game->selection->end_pos[0] ||
                game->selection->start_pos[1] != game->selection->end_pos[1]) && game->playing == 0) {
                game->selection->active = 1;
            } else {
                if (game->selection->active == 0)
                    manage_left_click(interface, game);
                game->selection->active = 0;
            }
        }
        if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue) {
            game->selection->end_pos[0] = mouse_pos[0];
            game->selection->end_pos[1] = mouse_pos[1];
        }
        delete_selection(game, interface);
        copy_selection(game, interface);
        paste_selection(game, interface, mouse_pos);

        if (sfKeyboard_isKeyPressed(sfKeySpace) && interface->win->event.type == sfEvtKeyPressed) {
            action_play(interface, game);
        }
        if (sfKeyboard_isKeyPressed(sfKeyUp) && interface->win->event.type == sfEvtKeyPressed) {
            interface->screen_pos[1]--;
        }
        if (sfKeyboard_isKeyPressed(sfKeyDown) && interface->win->event.type == sfEvtKeyPressed) {
            interface->screen_pos[1]++;
        }
        if (sfKeyboard_isKeyPressed(sfKeyRight) && interface->win->event.type == sfEvtKeyPressed) {
            interface->screen_pos[0]++;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLeft) && interface->win->event.type == sfEvtKeyPressed) {
            interface->screen_pos[0]--;
        }
        if (sfKeyboard_isKeyPressed(sfKeyZ) && interface->win->event.type == sfEvtKeyPressed) {
            action_zoom_in(interface, game);
        }
        if (sfKeyboard_isKeyPressed(sfKeyS) && interface->win->event.type == sfEvtKeyPressed) {
            action_zoom_out(interface, game);
        }
        if (sfKeyboard_isKeyPressed(sfKeyE) && interface->win->event.type == sfEvtKeyPressed) {
            action_speed_up(interface, game);
        }
        if (sfKeyboard_isKeyPressed(sfKeyA) && interface->win->event.type == sfEvtKeyPressed) {
            action_speed_down(interface, game);
        }
        if (sfKeyboard_isKeyPressed(sfKeyR) && interface->win->event.type == sfEvtKeyPressed) {
            reset_board(game, interface);
        }
        if (sfKeyboard_isKeyPressed(sfKeyF) && interface->win->event.type == sfEvtKeyPressed) {
            focus_random_cell(game, interface);
        }
    }
}
