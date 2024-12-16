/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** submenus_actions.c
*/

#include "game_of_life.h"

int action_toogle_grid(interface_t *interface, game_t *game)
{
    interface->display_grid = !interface->display_grid;
    return 0;
}

int action_toogle_colors(interface_t *interface, game_t *game)
{
    interface->display_colors = !interface->display_colors;
    return 0;
}

char *screenshot_name(interface_t *interface)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buffer[80];
    char *filename;
    char *final_filename;

    strftime(buffer, 80, "%Y_%m_%d_%H:%M:%S", tm_info);
    filename = my_str_concatenate("screenshots/screenshot_", buffer);
    final_filename = my_str_concatenate(filename, ".png");
    if (filename == NULL || final_filename == NULL)
        return NULL;
    free(filename);
    return final_filename;
}

int action_take_screenshot(interface_t *interface, game_t *game)
{
    sfVector2u size = sfRenderWindow_getSize(interface->win->window);
    char *filename = screenshot_name(interface);
    sfTexture *texture = sfTexture_create(size.x, size.y);
    sfImage *image;

    if (filename == NULL || texture == NULL)
        return 84;
    display_elements(interface, game, 1);
    sfTexture_updateFromRenderWindow(texture, interface->win->window, 0, 0);
    image = sfTexture_copyToImage(texture);
    if (image == NULL) {
        sfTexture_destroy(texture);
        return 84;
    }
    sfImage_saveToFile(image, filename);
    sfImage_destroy(image);
    sfTexture_destroy(texture);
    free(filename);
    return 0;
}

int action_random_map(interface_t *interface, game_t *game)
{
    long int x;
    long int y;

    reset_board(game, interface);
    for (int i = 0; i < 40000; i++) {
        x = random_int(-100, 300);
        y = random_int(-100, 300);
        set_cell(&game->grid, x, y, 0);
    }
    return 0;
}