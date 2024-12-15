/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** main.c
*/

#include "game_of_life.h"

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

        while (sfRenderWindow_pollEvent(interface->win->window, &interface->win->event)) {
            if (interface->win->event.type == sfEvtClosed ||
                        sfKeyboard_isKeyPressed(sfKeyEscape))
                sfRenderWindow_close(interface->win->window);
        }

        //display_elements(interface, game);
        sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[0]->inactive_box, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[0]->text, NULL);
        sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[1]->inactive_box, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[1]->text, NULL);
        sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[2]->inactive_box, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[2]->text, NULL);

        /*sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[0]->active_box, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[0]->sub_menus[0]->text, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[0]->sub_menus[1]->text, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[0]->sub_menus[2]->text, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[0]->sub_menus[3]->text, NULL);*/

        sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[1]->active_box, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[1]->sub_menus[0]->text, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[1]->sub_menus[1]->text, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[1]->sub_menus[2]->text, NULL);

        /*sfRenderWindow_drawRectangleShape(interface->win->window, interface->menu_items[2]->active_box, NULL);
        sfRenderWindow_drawText(interface->win->window, interface->menu_items[2]->sub_menus[0]->text, NULL);*/

        for (int i = 0; i < 6; i++) {
            if (interface->button_items[i]->active == 0)
                sfSprite_setTexture(interface->button_items[i]->sprite, interface->button_items[i]->inactive_texture, sfTrue);
            else
                sfSprite_setTexture(interface->button_items[i]->sprite, interface->button_items[i]->active_texture, sfTrue);
            sfRenderWindow_drawSprite(interface->win->window, interface->button_items[i]->sprite, NULL);
        }

        sfRenderWindow_display(interface->win->window);
    }
    return 0;
}
