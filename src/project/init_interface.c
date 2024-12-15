/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** init_interface.c
*/

#include "game_of_life.h"

static window_t *init_window(void)
{
    window_t *win = malloc(sizeof(window_t));

    if (win == NULL)
        return NULL;
    win->v_mode = (sfVideoMode){SCREEN_WIDTH, SCREEN_HEIGHT, 32};
    win->window = sfRenderWindow_create(win->v_mode, "Game of Life",
                    sfClose, NULL);
    win->clock = sfClock_create();
    win->time = 0;
    return win;
}

static sfText *init_text(char *txt, sfVector2f pos, int size)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile(BASIC_FONT);

    if (text == NULL || font == NULL)
        return NULL;
    sfText_setString(text, txt);
    sfText_setCharacterSize(text, size);
    sfText_setFont(text, font);
    sfText_setColor(text, sfBlack);
    sfText_setPosition(text, pos);
    return text;
}

static sfRectangleShape *init_box(sfVector2f pos, sfVector2f dim, float border)
{
    sfRectangleShape *box = sfRectangleShape_create();

    if (box == NULL)
        return NULL;
    sfRectangleShape_setPosition(box, pos);
    sfRectangleShape_setSize(box, dim);
    sfRectangleShape_setFillColor(box, sfWhite);
    sfRectangleShape_setOutlineThickness(box, border);
    sfRectangleShape_setOutlineColor(box, sfBlack);
    return box;
}

static menu_item_t *init_menu_item(char *txt, sfVector2f pos, sfVector2f dim,
        sfVector2f dim_sub)
{
    menu_item_t *menu_item = malloc(sizeof(menu_item_t));

    if (menu_item == NULL)
        return NULL;
    menu_item->active = 0;
    menu_item->text = init_text(txt, (sfVector2f){pos.x + 2, pos.y}, 20);
    menu_item->pos = pos;
    menu_item->dimensions = dim;
    menu_item->active_box = init_box((sfVector2f){pos.x, pos.y + dim.y}, dim_sub, 0.25);
    menu_item->inactive_box = init_box(pos, dim, 0.75);
    if (menu_item->text == NULL || menu_item->active_box == NULL ||
                                    menu_item->inactive_box == NULL)
        return NULL;
    menu_item->sub_menus = NULL;
    return menu_item;
}

static int file_subitems(interface_t *interface, int *active_rectsize)
{
    char *subitems[4] = {"Import File", "Export File", "Share as image", "Random map"};
    int (*actions[4])(interface_t *interface, game_t *game) = {NULL, NULL, NULL, NULL}; // TODO: add functions
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

static int display_subitems(interface_t *interface, int *active_rectsize)
{
    char *subitems[3] = {"Grid visibility", "Color visibility", "Sound toogle"};
    int (*actions[3])(interface_t *interface, game_t *game) = {NULL, NULL, NULL}; // TODO: add functions
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

static int help_subitems(interface_t *interface, int *active_rectsize)
{
    char *subitems[1] = {"Rules"};
    int (*actions[1])(interface_t *interface, game_t *game) = {NULL}; // TODO: add functions
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

static int set_all_menu_items( interface_t *interface)
{
    int active_rectsize[3][2] = {{150, 160}, {150, 120}, {100, 40}};

    interface->menu_items[0] = init_menu_item("File", (sfVector2f){3, 5},
        (sfVector2f){80, 25}, (sfVector2f){active_rectsize[0][0],
            active_rectsize[0][1]});
    interface->menu_items[1] = init_menu_item("Display", (sfVector2f){85, 5},
        (sfVector2f){100, 25}, (sfVector2f){active_rectsize[1][0],
            active_rectsize[1][1]});
    interface->menu_items[2] = init_menu_item("Help", (sfVector2f){187, 5},
        (sfVector2f){55, 25}, (sfVector2f){active_rectsize[2][0],
            active_rectsize[2][1]});
    if (interface->menu_items[0] == NULL || interface->menu_items[1] == NULL ||
        interface->menu_items[2] == NULL)
        return 84;
    if (file_subitems(interface, active_rectsize[0]) == 84 ||
        display_subitems(interface, active_rectsize[1]) == 84 ||
        help_subitems(interface, active_rectsize[2]) == 84)
        return 84;
    return 0;
}

static int set_all_button_items(interface_t *interface)
{
    char *inactive_textures[6] = {PAUSED_S, ZOOM_IN_S, ZOOM_OUT_S,
        SPEED_UP_S, SPEED_DOWN_S, STATS_OFF_S};
    char *active_textures[6] = {PLAYING_S, NULL, NULL, NULL, NULL, STATS_ON_S};
    sfVector2f pos[6] = {{SCREEN_WIDTH - 75, 5}, {SCREEN_WIDTH - 45, SCREEN_HEIGHT - 185},
        {SCREEN_WIDTH - 150, SCREEN_HEIGHT - 185}, {SCREEN_WIDTH - 45, SCREEN_HEIGHT - 125},
        {SCREEN_WIDTH - 150, SCREEN_HEIGHT - 125}, {45, SCREEN_HEIGHT - 150}};
    sfVector2f dim[6] = {{50, 25}, {25, 25}, {25, 25}, {25, 25}, {25, 25}, {25, 25}};
    int (*actions[6])(interface_t *interface, game_t *game) =
        {NULL, NULL, NULL, NULL, NULL, NULL}; // TODO: add functions
    
    for (int i = 0; i < 6; i++) {
        interface->button_items[i] = malloc(sizeof(button_item_t));
        if (interface->button_items[i] == NULL)
            return 84;
        interface->button_items[i]->active = 0;
        interface->button_items[i]->inactive_texture = sfTexture_createFromFile(inactive_textures[i], NULL);
        if (active_textures[i] != NULL)
            interface->button_items[i]->active_texture = sfTexture_createFromFile(active_textures[i], NULL);
        else
            interface->button_items[i]->active_texture = NULL;
        interface->button_items[i]->sprite = sfSprite_create();
        if (interface->button_items[i]->inactive_texture == NULL ||
            interface->button_items[i]->sprite == NULL)
            return 84;
        sfSprite_setPosition(interface->button_items[i]->sprite, pos[i]);
        sfSprite_setScale(interface->button_items[i]->sprite, (sfVector2f){0.1, 0.1});
        interface->button_items[i]->pos = pos[i];
        interface->button_items[i]->dimensions = dim[i];
        interface->button_items[i]->action = actions[i];
    }
    return 0;
}

int initialize_interface(interface_t *interface)
{
    interface->win = init_window();
    interface->menu_items = malloc(sizeof(menu_item_t *) * 3);
    interface->button_items = malloc(sizeof(button_item_t *) * 6);
    if (interface->win == NULL || interface->menu_items == NULL || interface->button_items == NULL)
        return 84;
    if (set_all_menu_items(interface) == 84 ||
        set_all_button_items(interface) == 84)
        return 84;
    interface->display_colors = 0;
    interface->display_grid = 1;
    interface->play_sounds = 0;
    interface->screen_pos = malloc(sizeof(long int) * 2);
    if (interface->screen_pos == NULL)
        return 84;
    interface->screen_pos[0] = 0;
    interface->screen_pos[1] = 0;
    interface->zoom = 50;
    return 0;
}
