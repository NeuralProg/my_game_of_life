/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** trigger_pop_up.c
*/

#include "game_of_life.h"

void trigger_pop_up(game_t *game, interface_t *interface, char *message)
{
    sfClock_restart(game->pop_up->clock);
    game->pop_up->message = message;
    game->pop_up->active = 1;
    game->pop_up->timer = game->pop_up->duration;
}
