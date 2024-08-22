/*
** EPITECH PROJECT, 2024
** Nom du projet
** File description:
** Description du projet
*/

#ifndef __SWORD__
    #define __SWORD__
    #include <SFML/Graphics.h>
    #include "player.h"
    #include "../utils/sprite_texture_utils.h"

sfVector2f get_sword_pos(app_player *player);
sfVector2f get_sword_scale(app_player *player);
void attack_manager(app_player *player, float delta_time);
void attack_process(
    app_player *player,
    float delta_time,
    float frameDuration
);
sprite_sheet_entity *create_sword_entity();

#endif
