/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** init_structs.c
*/

#include "game_of_life.h"

static pop_up_message_t *init_pop_up(game_t *game)
{
    pop_up_message_t *new_pop_up = malloc(sizeof(pop_up_message_t));

    if (new_pop_up == NULL)
        return NULL;
    new_pop_up->active = 0;
    new_pop_up->size = (sfVector2f){200, 30};
    new_pop_up->pos = (sfVector2f){SCREEN_WIDTH / 2 -
        new_pop_up->size.x / 2, 40};
    new_pop_up->back = init_box(new_pop_up->pos, new_pop_up->size, 1);
    new_pop_up->duration = 1.5;
    new_pop_up->timer = 0;
    new_pop_up->clock = sfClock_create();
    return new_pop_up;
}

static selection_t *init_selection(game_t *game)
{
    selection_t *new_selection = malloc(sizeof(selection_t));

    if (new_selection == NULL)
        return NULL;
    new_selection->active = 0;
    new_selection->selected_cells = NULL;
    new_selection->start_pos[0] = 0;
    new_selection->start_pos[1] = 0;
    new_selection->end_pos[0] = 0;
    new_selection->end_pos[1] = 0;
    return new_selection;
}

static sounds_t *init_sounds(game_t *game)
{
    sounds_t *new_sounds = malloc(sizeof(sounds_t));

    new_sounds->bg_music = sfMusic_createFromFile(BG_MUSIC);
    if (new_sounds->bg_music == NULL)
        return NULL;
    sfMusic_setLoop(new_sounds->bg_music, 1);
    sfMusic_setVolume(new_sounds->bg_music, 100);
    sfMusic_play(new_sounds->bg_music);
    return new_sounds;
}

static int init_game(game_t *game)
{
    game->playing = 0;
    game->stats_active = 0;
    game->grid = NULL;
    game->pop_up = init_pop_up(game);
    if (game->pop_up == NULL)
        return 84;
    game->selection = init_selection(game);
    if (game->selection == NULL)
        return 84;
    game->sounds = init_sounds(game);
    if (game->sounds == NULL)
        return 84;
    game->gen = 0;
    game->alive = 0;
    game->speed = 50;
    game->last_update = 0;
    return 0;
}

int init_structs(interface_t *interface, game_t *game)
{
    if (interface == NULL || game == NULL)
        return 84;
    if (initialize_interface(interface) == 84)
        return 84;
    if (init_game(game) == 84)
        return 84;
    return 0;
}