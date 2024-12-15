/*
** EPITECH PROJECT, 2024
** my_game_of_life
** File description:
** display_help.c
*/

#include "game_of_life.h"

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
