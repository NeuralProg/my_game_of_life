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

typedef struct cell_key_s {
    long int x;
    long int y;
} cell_key_t;

typedef struct window_s {
    sfRenderWindow *window;
    sfVideoMode v_mode;
    sfEvent event;
    sfClock *clock;
    double time;
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
    long int *screen_pos;
} interface_t;

typedef struct active_cell_s {
    long int x;
    long int y;
    long int age;
    UT_hash_handle hh;
} active_cell_t;

typedef struct pop_up_message_s {
    int active;
    char *message;
    sfVector2f pos;
    sfVector2f size;
    sfRectangleShape *back;
    sfClock *clock;
    float duration;
    double timer;
} pop_up_message_t;

typedef struct selection_s {
    int active;
    active_cell_t *selected_cells;
    long int start_pos[2];
    long int end_pos[2];
    long int width;
    long int height;
} selection_t;

typedef struct game_s {
    int playing;
    int stats_active;
    active_cell_t *grid;
    pop_up_message_t *pop_up;
    selection_t *selection;
    unsigned int gen;
    unsigned long int alive;
    int speed;
    double last_update;
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
// Get the selection coordinates on the grid (top left to right bottom)
long int *get_selection_boundaries(game_t *game);
// Init of a text element
sfText *init_text(char *txt, sfVector2f pos, int size);
// Init a box item
sfRectangleShape *init_box(sfVector2f pos, sfVector2f dim, float border);
// Initialisation of the menu items
int file_subitems(interface_t *interface, int *active_rectsize);
int display_subitems(interface_t *interface, int *active_rectsize);
int help_subitems(interface_t *interface, int *active_rectsize);
// If the cell exists in the grid
int cell_exists(active_cell_t *grid, long int x, long int y);
// Get the age of a cell
long int get_cell_age(active_cell_t *grid, long int x, long int y);
// Add or edit a cell to from the grid
void set_cell(active_cell_t **grid, long int x, long int y, long int age);
// Remove a cell from the grid
void remove_cell(active_cell_t **grid, long int x, long int y);
// Free the grid
void free_grid(active_cell_t **grid);
// Create the grid for the next generation
void calculate_next_gen(interface_t *interface, game_t *game);
// Get the mouse position on the grid
long int *get_mouse_pos_on_grid(interface_t *interface);
// Get the number of neighbours of a cell
int get_neighbours(active_cell_t *grid, long int x, long int y);
// Display all elements on screen
void display_elements(interface_t *interface, game_t *game, int screenshot);
// Is a cell withing the range of the active cell
int is_cell_in_selection_range(game_t *game, long int x, long int y);
// Width of the selection
long int get_selection_width(game_t *game);
// Height of the selection
long int get_selection_height(game_t *game);
// Start a pop_up message
void trigger_pop_up(game_t *game, interface_t *interface, char *message);
// Manage all events
void manage_events(interface_t *interface, game_t *game);
// Draw texts on screen
void draw_text(interface_t *interface, char *str, sfVector2f pos, int size);
// Buttons actions
int action_play(interface_t *interface, game_t *game);
int action_zoom_in(interface_t *interface, game_t *game);
int action_zoom_out(interface_t *interface, game_t *game);
int action_speed_up(interface_t *interface, game_t *game);
int action_speed_down(interface_t *interface, game_t *game);
int action_stats(interface_t *interface, game_t *game);
// Submenus actions
int action_toogle_grid(interface_t *interface, game_t *game);
int action_toogle_colors(interface_t *interface, game_t *game);
int action_take_screenshot(interface_t *interface, game_t *game);
int action_random_map(interface_t *interface, game_t *game);
// Key actions
void reset_board(game_t *game, interface_t *interface);
void focus_random_cell(game_t *game, interface_t *interface);

#endif
