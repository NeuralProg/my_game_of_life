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
    if (interface->display_grid == 1)
        trigger_pop_up(game, interface, "Grid Activated.");
    else
        trigger_pop_up(game, interface, "Grid Hidden.");
    return 0;
}

int action_toogle_colors(interface_t *interface, game_t *game)
{
    interface->display_colors = !interface->display_colors;
    if (interface->display_colors == 1)
        trigger_pop_up(game, interface, "Colors Activated.");
    else 
        trigger_pop_up(game, interface, "Colors Hidden.");
    return 0;
}

int action_toogle_sounds(interface_t *interface, game_t *game)
{
    if (sfMusic_getStatus(game->sounds->bg_music) == sfPaused ||
        sfMusic_getStatus(game->sounds->bg_music) == sfStopped) {
        sfMusic_play(game->sounds->bg_music);
        trigger_pop_up(game, interface, "Sounds Activated.");
    } else {
        sfMusic_pause(game->sounds->bg_music);
        trigger_pop_up(game, interface, "Sounds Shut.");
    }
    return 0;
}

char *file_name(interface_t *interface, char *str, char *end)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char buffer[80];
    char *filename;
    char *final_filename;

    strftime(buffer, 80, "%Y_%m_%d_%H:%M:%S", tm_info);
    filename = my_str_concatenate(str, buffer);
    final_filename = my_str_concatenate(filename, end);
    if (filename == NULL || final_filename == NULL)
        return NULL;
    free(filename);
    return final_filename;
}

int action_take_screenshot(interface_t *interface, game_t *game)
{
    sfVector2u size = sfRenderWindow_getSize(interface->win->window);
    char *filename = file_name(interface, "screenshots/screenshot_", ".png");
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
    trigger_pop_up(game, interface, "Screenshot taken.");
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
    trigger_pop_up(game, interface, "Random generation.");
    return 0;
}

int action_show_help(interface_t *interface, game_t *game)
{
    display_help_window(interface);
    return 0;
}

int action_import_file(interface_t *interface, game_t *game)
{
    FILE *file;
    char *filename = malloc(sizeof(char) * 256);
    struct stat sd;
    char *buff;
    cJSON *json = NULL;

    if (filename == NULL)
        return 84;
    trigger_pop_up(game, interface, "Choose config...");
    printf("File to import: my_game_of_life/ ");
    scanf("%s", filename);
    printf("Importing file: %s\n", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        trigger_pop_up(game, interface, "Error: invalid file.");
        free(filename);
        return 84;
    }
    stat(filename, &sd);
    if (sd.st_size == 0) {
        trigger_pop_up(game, interface, "Error: empty file.");
        free(filename);
        return 84;
    }
    free(filename);
    buff = malloc(sizeof(char) * (sd.st_size + 1));
    if (buff == NULL)
        return 84;
    fread(buff, 1, (sd.st_size), file);
    fclose(file);

    json = cJSON_Parse(buff); 
    if (json == NULL) {
        trigger_pop_up(game, interface, "Error: invalid json.");
        free(buff);
        return 84;
    }

    interface->display_grid = cJSON_GetObjectItem(json, "display_grid")->valueint;
    interface->display_colors = cJSON_GetObjectItem(json, "display_colors")->valueint;
    sfMusic_setVolume(game->sounds->bg_music, cJSON_GetObjectItem(json, "play_sounds")->valueint == 0 ? 0 : 100);
    interface->screen_pos[0] = cJSON_GetObjectItem(json, "view_x")->valueint;
    interface->screen_pos[1] = cJSON_GetObjectItem(json, "view_y")->valueint;
    game->gen = cJSON_GetObjectItem(json, "gen")->valueint;
    game->alive = cJSON_GetObjectItem(json, "cells_nb")->valueint;
    free_grid(&game->grid);
    for (unsigned int i = 0; i < game->alive; i++) {
        cJSON *cell = cJSON_GetObjectItem(json, my_unsigned_int_to_str(i));
        set_cell(&game->grid, cell->child->valueint, cell->child->next->valueint, cell->child->next->next->valueint);
    }
    trigger_pop_up(game, interface, "Imported config.");
    printf("Imported config.\n");
    free(buff);
    cJSON_Delete(json);
    return 0;
}

int action_export_file(interface_t *interface, game_t *game)
{
    FILE *file;
    char *json_str;
    active_cell_t *current;
    active_cell_t *tmp;
    cJSON *cell;
    cJSON *json = cJSON_CreateObject();
    unsigned int i = 0;
    char *i_txt;
    char *filename = file_name(interface, "configs/config_", ".json");

    if (filename == NULL)
        exit(my_puterr("Error: invalid filename."));
    cJSON_AddNumberToObject(json, "display_grid", interface->display_grid);
    cJSON_AddNumberToObject(json, "display_colors", interface->display_colors);
    cJSON_AddNumberToObject(json, "play_sounds", sfMusic_getVolume(game->sounds->bg_music) == 0 ? 0 : 1);
    cJSON_AddNumberToObject(json, "view_x", interface->screen_pos[0]);
    cJSON_AddNumberToObject(json, "view_y", interface->screen_pos[1]);
    cJSON_AddNumberToObject(json, "gen", game->gen);
    cJSON_AddNumberToObject(json, "cells_nb", game->alive);
    HASH_ITER(hh, game->grid, current, tmp) {
        cell = cJSON_CreateArray();
        cJSON_AddItemToArray(cell, cJSON_CreateNumber(current->x));
        cJSON_AddItemToArray(cell, cJSON_CreateNumber(current->y));
        cJSON_AddItemToArray(cell, cJSON_CreateNumber(current->age));
        i_txt = my_unsigned_int_to_str(i);
        if (i_txt == NULL)
            continue;
        cJSON_AddItemToObject(json, i_txt, cell);
        free(i_txt);
        i++;
    }
    json_str = cJSON_Print(json);
    file = fopen(filename, "w");
    trigger_pop_up(game, interface, "Exported config.");
    fputs(json_str, file);
    fclose(file);
    free(filename);
    return 0;
}