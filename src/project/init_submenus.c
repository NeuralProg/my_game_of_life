/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** init_submenus.c
*/

#include "game_of_life.h"

int file_subitems(interface_t *interface, int *active_rectsize)
{
    char *subitems[4] = {"Import File", "Export File", "Share as image", "Random map"};
    int (*actions[4])(interface_t *interface, game_t *game) =
        {NULL, NULL, &action_take_screenshot, &action_random_map}; // TODO: add functions
    int font_size = 15;

    interface->menu_items[0]->sub_menus = malloc(sizeof(sub_menu_t *) * 4);
    if (interface->menu_items[0]->sub_menus == NULL)
        return 84;
    for (int i = 0; i < 4; i++) {
        interface->menu_items[0]->sub_menus[i] = malloc(sizeof(sub_menu_t));
        if (interface->menu_items[0]->sub_menus[i] == NULL)
            return 84;
        interface->menu_items[0]->sub_menus[i]->text = init_text(subitems[i],
            (sfVector2f){interface->menu_items[0]->pos.x + 5,
            (interface->menu_items[0]->dimensions.y + interface->menu_items[0]->pos.y)
            + (i) * active_rectsize[1] / 4 + (font_size / 2)}, font_size);
        if (interface->menu_items[0]->sub_menus[i]->text == NULL)
            return 84;
        interface->menu_items[0]->sub_menus[i]->pos = (sfVector2f){interface->menu_items[0]->pos.x,
            (interface->menu_items[0]->dimensions.y + interface->menu_items[0]->pos.y)
            + (i) * active_rectsize[1] / 4};
        interface->menu_items[0]->sub_menus[i]->dimensions = (sfVector2f){active_rectsize[0], active_rectsize[1] / 4};
        interface->menu_items[0]->sub_menus[i]->action = actions[i];
    }
    return 0;
}

int display_subitems(interface_t *interface, int *active_rectsize)
{
    char *subitems[3] = {"Grid visibility", "Color visibility", "Sound toogle"};
    int (*actions[3])(interface_t *interface, game_t *game) =
            {&action_toogle_grid, &action_toogle_colors, &action_toogle_sounds}; // TODO: add functions
    int font_size = 15;

    interface->menu_items[1]->sub_menus = malloc(sizeof(sub_menu_t *) * 3);
    if (interface->menu_items[1]->sub_menus == NULL)
        return 84;
    for (int i = 0; i < 3; i++) {
        interface->menu_items[1]->sub_menus[i] = malloc(sizeof(sub_menu_t));
        if (interface->menu_items[1]->sub_menus[i] == NULL)
            return 84;
        interface->menu_items[1]->sub_menus[i]->text = init_text(subitems[i],
            (sfVector2f){interface->menu_items[1]->pos.x + 5,
            (interface->menu_items[1]->dimensions.y + interface->menu_items[1]->pos.y)
            + (i) * active_rectsize[1] / 3 + (font_size / 2)}, font_size);
        if (interface->menu_items[1]->sub_menus[i]->text == NULL)
            return 84;
        interface->menu_items[1]->sub_menus[i]->pos = (sfVector2f){interface->menu_items[1]->pos.x,
            (interface->menu_items[1]->dimensions.y + interface->menu_items[1]->pos.y)
            + (i) * active_rectsize[1] / 3};
        interface->menu_items[1]->sub_menus[i]->dimensions = (sfVector2f){active_rectsize[0], active_rectsize[1] / 3};
        interface->menu_items[1]->sub_menus[i]->action = actions[i];
    }
    return 0;
}

int help_subitems(interface_t *interface, int *active_rectsize)
{
    char *subitems[1] = {"Rules"};
    int (*actions[1])(interface_t *interface, game_t *game) = {&action_show_help}; // TODO: add functions
    int font_size = 15;

    interface->menu_items[2]->sub_menus = malloc(sizeof(sub_menu_t *) * 1);
    if (interface->menu_items[2]->sub_menus == NULL)
        return 84;
    for (int i = 0; i < 1; i++) {
        interface->menu_items[2]->sub_menus[i] = malloc(sizeof(sub_menu_t));
        if (interface->menu_items[2]->sub_menus[i] == NULL)
            return 84;
        interface->menu_items[2]->sub_menus[i]->text = init_text(subitems[i],
            (sfVector2f){interface->menu_items[2]->pos.x + 5,
            (interface->menu_items[2]->dimensions.y + interface->menu_items[2]->pos.y)
            + (i) * active_rectsize[1] / 1 + (font_size / 2)}, font_size);
        if (interface->menu_items[2]->sub_menus[i]->text == NULL)
            return 84;
        interface->menu_items[2]->sub_menus[i]->pos = (sfVector2f){interface->menu_items[2]->pos.x,
            (interface->menu_items[2]->dimensions.y + interface->menu_items[2]->pos.y)
            + (i) * active_rectsize[1] / 1};
        interface->menu_items[2]->sub_menus[i]->dimensions = (sfVector2f){active_rectsize[0], active_rectsize[1] / 1};
        interface->menu_items[2]->sub_menus[i]->action = actions[i];
    }
    return 0;
}