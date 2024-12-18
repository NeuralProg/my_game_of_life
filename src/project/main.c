/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** main.c
*/

#include "game_of_life.h"

static void free_all(interface_t *interface, game_t *game)
{
    sfRenderWindow_destroy(interface->win->window);
    free(interface->win);
    free_grid(&game->grid);
    free(interface);
    free(game);
}

int main(int ac, char const *av[])
{
    interface_t *interface = malloc(sizeof(interface_t));
    game_t *game = malloc(sizeof(game_t));

    if (ac == 2) {
        if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0)
            return display_help();
    }
    if (ac != 1)
        return my_puterr("Invalid arguments\n");
    if (init_structs(interface, game) == 84)
        return 84;
    while (sfRenderWindow_isOpen(interface->win->window)) {
        sfRenderWindow_clear(interface->win->window, DARK_GREY);

        if (sfRenderWindow_getSize(interface->win->window).x < 800 || sfRenderWindow_getSize(interface->win->window).y < 600) {
            sfRenderWindow_setSize(interface->win->window, (sfVector2u){800, 600});
        }
        manage_events(interface, game);
        game->alive = HASH_COUNT(game->grid);
        if (game->alive <= 0)
            game->playing = 0;
        if (game->playing == 1) {
            interface->win->time += sfClock_getElapsedTime(interface->win->clock).microseconds / 1000000.0;
            sfClock_restart(interface->win->clock);
        }
        if (game->pop_up->active == 1) {
            game->pop_up->timer -= sfClock_getElapsedTime(game->pop_up->clock).microseconds / 1000000.0;
            sfClock_restart(game->pop_up->clock);
        }
        if (game->playing == 1 && game->last_update + (0.1 + ((100 - game->speed) / 10) * 0.1) <= interface->win->time)
            calculate_next_gen(interface, game);
        if (game->pop_up->active == 1 && game->pop_up->timer <= 0)
            game->pop_up->active = 0;

        display_elements(interface, game, 0);

        sfRenderWindow_display(interface->win->window);
    }
    free_all(interface, game);
    return 0;
}
