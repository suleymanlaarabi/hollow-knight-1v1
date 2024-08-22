/*
** EPITECH PROJECT, 2024
** Nom du projet
** File description:
** Description du projet
*/

#include "sword.h"
#include "../utils/sprite_texture_utils.h"
#include <SFML/Graphics.h>

const float attackDuration = 0.5f;
const int numFrames = 3;
const int swordFrameWidth = 190;
const int swordFrameHeight = 140;

sprite_sheet_entity *create_sword_entity()
{
  sprite_sheet_entity *entity = init_sprite_entity("assets/sword_attack.png", swordFrameWidth, swordFrameHeight, 0, 0);
  sfSprite_setRotation(entity->sprite   , 90.0);
  set_empty_sprite(entity);
  return entity;
}

sfVector2f get_sword_pos(app_player *player)
{
    sfVector2f pos = player->pos;

    if (is_flipped(player->player_entity->sprite)) {
        pos.x -= 50;
    } else {
        pos.x += 50;
    }
    return pos;
}

sfVector2f get_sword_scale(app_player *player)
{
    sfVector2f scale = {1, 2};

    if (is_flipped(player->player_entity->sprite)) {
        scale.y = 1.7;
    } else {
        scale.y = -1.7;
    }
    return scale;
}

void attack_manager(app_player *player, float delta_time)
{
    float frameDuration = 0.0f;

    if (sfKeyboard_isKeyPressed(player->attack) && !player->isInAttack) {
        player->isInAttack = sfTrue;
        player->current_sword_frame = 0;
        player->attack_timer = 0.0f;
    }
    if (player->isInAttack) {
        attack_process(player, delta_time, frameDuration);
    }
}

void attack_process(
    app_player *player,
    float delta_time,
    float frameDuration
)
{
    player->attack_timer += delta_time / 0.7;
    frameDuration = attackDuration / numFrames;
    if (player->attack_timer >= frameDuration) {
        player->attack_timer -= frameDuration;
        player->current_sword_frame++;
        set_sprite(player->sword_entity, player->current_sword_frame);
        if (player->current_sword_frame >= numFrames) {
            player->isInAttack = sfFalse;
            set_empty_sprite(player->sword_entity);
            player->current_sword_frame = 0;
        }
    }
}