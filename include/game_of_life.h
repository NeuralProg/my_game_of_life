/*
** EPITECH PROJECT, 2024
** B-MUL-100-MLH-1-1-myradar-yann.toison-chabane
** File description:
** game_of_life.h
*/

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Config.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include "uthash.h"

#ifndef GAME_OF_LIFE_H_
    #define GAME_OF_LIFE_H_

    #define HELP_MESSAGE "include/help_message.txt"
    #define SCREEN_WIDTH 1920
    #define SCREEN_HEIGHT 1080
    #define BASIC_FONT "assets/fonts/hk_grotesk/HKGrotesk-SemiBold.ttf"
    #define DARK_GREY sfColor_fromRGB(41, 41, 41)
    #define PAUSED_S "assets/sprites/paused.png"
    #define PLAYING_S "assets/sprites/playing.png"
    #define ZOOM_IN_S "assets/sprites/zoom_in.png"
    #define ZOOM_OUT_S "assets/sprites/zoom_out.png"
    #define SPEED_UP_S "assets/sprites/speed_up.png"
    #define SPEED_DOWN_S "assets/sprites/speed_down.png"
    #define STATS_ON_S "assets/sprites/stats_on.png"
    #define STATS_OFF_S "assets/sprites/stats_off.png"


typedef struct interface_s interface_t;
typedef struct game_s game_t;

typedef struct window_s {
    sfRenderWindow *window;
    sfVideoMode v_mode;
    sfEvent event;
    sfClock *clock;
    unsigned long int time; // in tenth of secs
} window_t;

typedef struct sub_menu_s {
    sfText *text;
    sfVector2f pos;
    sfVector2f dimensions;
    int (*action)(struct interface_s *interface, struct game_s *game);
} sub_menu_t;

typedef struct menu_item_s {
    int active;
    sfText *text;
    sfVector2f pos;
    sfVector2f dimensions;
    sfRectangleShape *active_box;
    sfRectangleShape *inactive_box;
    sub_menu_t **sub_menus;
} menu_item_t;

typedef struct button_item_s {
    int active;
    sfTexture *active_texture;
    sfTexture *inactive_texture;
    sfSprite *sprite;
    sfVector2f pos;
    sfVector2f dimensions;
    int (*action)(struct interface_s *interface, struct game_s *game);
} button_item_t;

typedef struct interface_s {
    window_t *win;
    menu_item_t **menu_items;
    button_item_t **button_items;
    int display_grid;
    int display_colors;
    int play_sounds;
    int zoom;
    long int **screen_pos;
} interface_t;

typedef struct active_cell_s {
    long int x;
    long int y;
    int neighbours;
    UT_hash_handle hh;
} active_cell_t;

typedef struct game_s {
    int playing;
    active_cell_t *grid;
    unsigned int gen;
    unsigned long int alive;
    int speed;
    unsigned long int last_update;
} game_t;


// Basics
int my_puterr(char *str);
char *my_int_to_str(int nb);
char *my_str_concatenate(char *str1, char *str2);
int random_int(int min, int max);
// Display usage
int display_help(void);
int my_int_len(int nb);
int my_strlen(char const *str);

// Project
// Initialisation of all structures and variables
int init_structs(interface_t *interface, game_t *game);
// Initialisation of the interface
int initialize_interface(interface_t *interface);

#endif
