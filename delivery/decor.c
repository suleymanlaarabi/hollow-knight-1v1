/*
** EPITECH PROJECT, 2024
** Nom du projet
** File description:
** Description du projet
*/

#include "./decor.h"
#include "./utils/sprite_texture_utils.h"
#include <stdio.h>
#include <SFML/Graphics.h>

sfSprite *load_decor()
{
    sfSprite *sprite = create_sprite_with_texture("assets/arena.png");
    sfVector2f pos = {0, 0};
    sfVector2f scale = {1.3, 1.3};

    sfSprite_setPosition(sprite, pos);
    sfSprite_setScale(sprite, scale);
    return sprite;
}
