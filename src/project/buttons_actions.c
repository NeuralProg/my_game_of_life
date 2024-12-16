/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** buttons_actions.c
*/

#include "game_of_life.h"

int action_stats(interface_t *interface, game_t *game)
{
    game->stats_active = !game->stats_active;
    return 0;
}

int action_play(interface_t *interface, game_t *game)
{
    if (game->alive > 0)
        game->playing = !game->playing;
    return 0;
}

int action_zoom_in(interface_t *interface, game_t *game)
{
    if (interface->zoom < 100)
        interface->zoom += 5;
    return 0;
}

int action_zoom_out(interface_t *interface, game_t *game)
{
    if (interface->zoom > 5)
        interface->zoom -= 5;
    return 0;
}

int action_speed_up(interface_t *interface, game_t *game)
{
    if (game->speed < 100)
        game->speed += 5;
    return 0;
}

int action_speed_down(interface_t *interface, game_t *game)
{
    if (game->speed > 10)
        game->speed -= 5;
    return 0;
}
