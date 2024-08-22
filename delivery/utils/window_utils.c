/*
** EPITECH PROJECT, 2017
** name
** File description:
** description
*/

#include "./window_utils.h"

sfRenderWindow *init_window()
{
    sfRenderWindow *window;
    sfVideoMode video_mode = {1920, 1080, 32};

    window = sfRenderWindow_create(
        video_mode,
        "My First Window",
        sfResize | sfClose,
        NULL
        );
    return window;
}
