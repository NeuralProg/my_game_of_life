/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** calculate_mouse_pos.c
*/

#include "game_of_life.h"

sfVector2f recalculate_mouse_position(interface_t *interface)
{
    sfVector2i pixel_pos = sfMouse_getPositionRenderWindow(interface->win->window);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(interface->win->window, pixel_pos, sfRenderWindow_getView(interface->win->window));

    return world_pos;
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
