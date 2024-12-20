/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** display_help.c
*/

#include "game_of_life.h"

static void draw_help_text(sfRenderWindow *window)
{
    char *buff;
    FILE *file = fopen(HELP_MESSAGE, "r");
    char *line = NULL;
    size_t len = 0;
    sfText *text;
    int i = 0;
    
    if (file == NULL) {
        my_puterr("Error: could not open help file\n");
        return;
    }
    while (getline(&line, &len, file) != -1) {
        text = init_text(line, (sfVector2f){10, 15 * (i + 1)}, 10);
        sfRenderWindow_drawText(window, text, NULL);
        sfFont_destroy((sfFont *)sfText_getFont(text));
        sfText_destroy(text);
        i++;
    }
    free(line);
    fclose(file);
}

int display_help(void)
{
    FILE *file = fopen(HELP_MESSAGE, "r");
    char *line = NULL;
    size_t len = 0;

    if (file == NULL)
        return my_puterr("Error: could not open help file\n");
    while (getline(&line, &len, file) != -1)
        printf("%s", line);
    fclose(file);
}

int display_help_window(interface_t *interface)
{
    sfRenderWindow *window;
    sfVideoMode mode = {540, 600, 32};
    sfEvent event;

    window = sfRenderWindow_create(mode, "Help", sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 30);
    sfRenderWindow_setFramerateLimit(interface->win->window, 1);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfWhite);
        while (sfRenderWindow_pollEvent(interface->win->window, &interface->win->event)) {
            if (interface->win->event.type == sfEvtClosed ||
                (sfKeyboard_isKeyPressed(sfKeyEscape) && interface->win->event.type == sfEvtKeyPressed)) {
                sfRenderWindow_close(interface->win->window);
                sfRenderWindow_close(window);
            }
        }
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed ||
                (sfKeyboard_isKeyPressed(sfKeyEscape) && event.type == sfEvtKeyPressed))
                sfRenderWindow_close(window);
        }
        draw_help_text(window);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    sfRenderWindow_setFramerateLimit(interface->win->window, 0);
    return 0;
}
