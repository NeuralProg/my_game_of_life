/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** display_all.c
*/

#include "game_of_life.h"

static sfColor set_unactive_cell_color(game_t *game, interface_t *interface, long int x, long int y)
{
    sfColor new_rgb = sfTransparent;

    if (interface->display_colors == 0)
        return new_rgb;
    if (get_neighbours(game->grid, x, y) == 3)
        new_rgb = (sfColor){150, 255, 200, 170};
    return new_rgb;
}

static sfColor set_active_cell_color(game_t *game, interface_t *interface, long int x, long int y)
{
    sfColor new_rgb = sfWhite;
    float color_addition = 5;

    if (interface->display_colors == 0)
        return new_rgb;
    if (get_cell_age(game->grid, x, y) != -1) {
        if (get_cell_age(game->grid, x, y) * color_addition <= 255)
            new_rgb.b -= (int)(get_cell_age(game->grid, x, y) * color_addition);
        if (get_cell_age(game->grid, x, y) * color_addition > 255 &&
            get_cell_age(game->grid, x, y) * color_addition <= 510) {
            new_rgb.b = 0;
            new_rgb.g -= get_cell_age(game->grid, x, y) * color_addition - 255;
        }
        if (get_cell_age(game->grid, x, y) * color_addition > 510) {
            new_rgb.b = 0;
            new_rgb.g = 0;
        }
    }
    if (get_neighbours(game->grid, x, y) != 2 &&
        get_neighbours(game->grid, x, y) != 3)
        new_rgb = (sfColor){255, 170, 200, 255};
    return new_rgb;
}

static void display_backgrounds(interface_t *interface, game_t *game)
{
    sfRectangleShape *top_back = sfRectangleShape_create();
    sfRectangleShape *bottom_right_back = sfRectangleShape_create();
    char *zoom_nbr = my_int_to_str(interface->zoom);
    char *zoom_txt = my_str_concatenate(zoom_nbr, "%");
    char *speed_nbr = my_int_to_str(game->speed);
    char *speed_txt = my_str_concatenate(speed_nbr, "%");

    if (top_back == NULL || bottom_right_back == NULL)
        return;
    sfRectangleShape_setSize(top_back, (sfVector2f){SCREEN_WIDTH, 30});
    sfRectangleShape_setFillColor(top_back, sfWhite);
    sfRenderWindow_drawRectangleShape(interface->win->window, top_back, NULL);
    sfRectangleShape_setSize(bottom_right_back, (sfVector2f){180, 115});
    sfRectangleShape_setFillColor(bottom_right_back, sfWhite);
    sfRectangleShape_setPosition(bottom_right_back, (sfVector2f){SCREEN_WIDTH - 180, SCREEN_HEIGHT - 200});
    sfRenderWindow_drawRectangleShape(interface->win->window, bottom_right_back, NULL);

    draw_text(interface, zoom_txt, (sfVector2f){SCREEN_WIDTH - 105, SCREEN_HEIGHT - 185}, 20);
    draw_text(interface, speed_txt, (sfVector2f){SCREEN_WIDTH - 105, SCREEN_HEIGHT - 125}, 20);
    free(zoom_nbr);
    free(zoom_txt);
    free(speed_nbr);
    free(speed_txt);
}

static void display_buttons_and_menus(interface_t *interface, game_t *game)
{
    int submenus_size[3] = {4, 3, 1};

    interface->button_items[0]->active = game->playing;
    for (int i = 0; i < 6; i++) {
        if (interface->button_items[i]->active == 0)
            sfSprite_setTexture(interface->button_items[i]->sprite, interface->button_items[i]->inactive_texture, sfTrue);
        else
            sfSprite_setTexture(interface->button_items[i]->sprite, interface->button_items[i]->active_texture, sfTrue);
        sfRenderWindow_drawSprite(interface->win->window, interface->button_items[i]->sprite, NULL);
    }
    for (int i = 0; i < 3; i++) {
        sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[i]->inactive_box, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[i]->text, NULL);
        if (interface->menu_items[i]->active == 1) {
            sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[i]->active_box, NULL);
            for (int j = 0; j < submenus_size[i]; j++)
                sfRenderWindow_drawText(interface->win->window, interface->menu_items[i]->sub_menus[j]->text, NULL);
        }
    }
}

static void display_grid(interface_t *interface, game_t *game)
{
    active_cell_t *current;
    active_cell_t *tmp;
    sfRectangleShape *cell = sfRectangleShape_create();
    sfVector2u screen_dim = sfRenderWindow_getSize(interface->win->window);
    int new_zoom = screen_dim.x / (2 * (110 - interface->zoom));
    int y = interface->screen_pos[1];
    int x = interface->screen_pos[0];

    if (cell == NULL)
        return;

    // Create and set the view
    sfView *view = sfView_createFromRect((sfFloatRect){0, 0, screen_dim.x, screen_dim.y});
    sfRenderWindow_setView(interface->win->window, view);

    sfRectangleShape_setSize(cell, (sfVector2f){new_zoom, new_zoom});
    sfRectangleShape_setOutlineThickness(cell, (float)interface->display_grid / 2);
    sfRectangleShape_setOutlineColor(cell, sfBlack);

    for (int i = 0; i <= (screen_dim.y - 30) / new_zoom + 30; i++) {
        for (int j = 0; j <= screen_dim.x / new_zoom; j++) {
            if (cell_exists(game->grid, j + x, i + y) == 1) {
                sfRectangleShape_setFillColor(cell, set_active_cell_color(game, interface, j + x, i + y));
            } else {
                sfRectangleShape_setFillColor(cell, set_unactive_cell_color(game, interface, j + x, i + y));
            }
            sfRectangleShape_setPosition(cell, (sfVector2f){j * new_zoom, i * new_zoom});
            sfRenderWindow_drawRectangleShape(interface->win->window, cell, NULL);
        }
    }
    sfRectangleShape_destroy(cell);

    // Reset to the default view
    sfRenderWindow_setView(interface->win->window, sfRenderWindow_getDefaultView(interface->win->window));
    sfView_destroy(view);
}

void draw_text(interface_t *interface, char *str, sfVector2f pos, int size)
{
    sfFont *font = sfFont_createFromFile(BASIC_FONT);
    sfText *text = sfText_create();

    if (font == NULL || text == NULL)
        return;
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setFillColor(text, sfBlack);
    sfText_setPosition(text, pos);
    sfText_setString(text, str);
    sfRenderWindow_drawText(interface->win->window, text, NULL);
}

void display_elements(interface_t *interface, game_t *game)
{
    display_grid(interface, game);
    display_backgrounds(interface, game);
    display_buttons_and_menus(interface, game);
}
