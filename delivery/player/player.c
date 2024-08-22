/*
** EPITECH PROJECT, 2024
** csfml
** File description:
** player
*/

#include "player.h"
#include "sword.h"
#include "../utils/sprite_texture_utils.h"
#include <stdlib.h>
#include <stdio.h>

const float position_y = 805.0;
const float jump_height = 300.0;
const float jump_speed = 1200.0;

const int playerFrameWidth = 80;
const int playerFrameHeight = 80;

const int x_max = 1950;
const int x_min = -30;

const short max_player_life = 6;

app_player* init_player(
    sfKeyCode move_left,
    sfKeyCode move_right,
    sfKeyCode jump,
    sfKeyCode attack
)
{
    app_player *player = malloc(sizeof(app_player));

    player->hasHitOpponent = sfFalse;
    player->move_left = move_left;
    player->move_right = move_right;
    player->jump = jump;
    player->attack = attack;
    player->pos = (sfVector2f){50, position_y};
    player->scale = (sfVector2f){2, 2};
    player->speed = 1000;
    player->life = max_player_life;
    player->jump_status = 0;
    player->isInAttack = sfFalse;
    player->current_sword_frame = 0;
    player->attack_timer = 0.0f;
    player->player_entity = init_sprite_entity("assets/sprites.png", playerFrameWidth, playerFrameHeight, 0, 0);
    set_empty_sprite(player->player_entity);
    player->sword_entity = create_sword_entity();
    return player;
}

void jump_player(app_player *player, float delta_time)
{
    if (player->jump_status == 1 && player->pos.y > position_y - jump_height) {
        player->pos.y -= jump_speed * delta_time;
        if (player->pos.y <= position_y - jump_height) {
            player->jump_status = 2;
        }
    }
    if (player->jump_status == 2 && player->pos.y < position_y) {
        player->pos.y += jump_speed * delta_time;
        if (player->pos.y >= position_y) {
            player->pos.y = position_y;
            player->jump_status = 0;
        }
    }
}



void flip_player(app_player *player)
{
    if (is_flipped(player->player_entity->sprite)) {
        player->scale.x = 2;
        player->pos.x -= 150;
    } else {
        player->scale.x = -2;
        player->pos.x += 150;
    }
}

int get_player_x_min(app_player *player)
{
    if (is_flipped(player->player_entity->sprite))
        return x_min + 150;
    return x_min;
}

int get_player_x_max(app_player *player)
{
    if (!is_flipped(player->player_entity->sprite))
        return x_max - 150;
    return x_max;
}

sfBool player_movement_process(app_player *player, float delta_time)
{
    sfBool is_not_walking = sfTrue;

    if (sfKeyboard_isKeyPressed(player->move_left)
        && player->pos.x >= get_player_x_min(player)) {
        player->pos.x -= player->speed * delta_time;
        if (!is_flipped(player->player_entity->sprite))
            flip_player(player);
        is_not_walking = sfFalse;
    } else if (sfKeyboard_isKeyPressed(player->move_right)
        && player->pos.x <= get_player_x_max(player)) {
        player->pos.x += player->speed * delta_time;
        if (is_flipped(player->player_entity->sprite))
            flip_player(player);
        is_not_walking = sfFalse;
    }
    return is_not_walking;
}

typedef enum { IDLE, WALKING, JUMPING, ATTACK } AnimationPlayer;

void set_animation(app_player *player, AnimationPlayer anim) {
    switch (anim)
    {
    case ATTACK:
        player->player_entity->startColumn = 0;
        player->player_entity->startRow = 4;
        break;
    case IDLE:
        player->player_entity->startColumn = 0;
        player->player_entity->startRow = 0;
        break;
    case WALKING:
        player->player_entity->startColumn = 1;
        player->player_entity->startRow = 0;
        break;
    case JUMPING:
        player->player_entity->startColumn = 1;
        player->player_entity->startRow = 9;
        break;
    default:
        break;
    }
}

void event_player_update(app_player *player, float delta_time)
{
    sfBool is_not_walking = player_movement_process(player, delta_time);
    if (sfKeyboard_isKeyPressed(player->jump) && player->jump_status == 0) {
        player->jump_status = 1;
    }
    if (is_not_walking)
        set_sprite(player->player_entity, 0);
    attack_manager(player, delta_time);
    jump_player(player, delta_time);
    
    if (player->isInAttack) {
        set_animation(player, ATTACK);
        update_animation(player->player_entity, 6, delta_time, 0.2f);
    } else if (player->jump_status != 0) {
        set_animation(player, JUMPING);
        update_animation(player->player_entity, 7, delta_time, 0.12f);
    } else if(!is_not_walking) {
        set_animation(player, WALKING);
        update_animation(player->player_entity, 4, delta_time, 0.12f);
    } else {
        set_animation(player, IDLE);
        update_animation(player->player_entity, 1, delta_time, 0.12f);
    }
    
    sfSprite_setPosition(player->player_entity->sprite, player->pos);
    sfSprite_setPosition(player->sword_entity->sprite, get_sword_pos(player));
    sfSprite_setScale(player->player_entity->sprite, player->scale);
    sfSprite_setScale(player->sword_entity->sprite, get_sword_scale(player));
}

void draw_player(sfRenderWindow *window, app_player *player) {
    sfRenderWindow_drawSprite(window, player->player_entity->sprite, NULL);
    if (player->isInAttack) {
        sfRenderWindow_drawSprite(window, player->sword_entity->sprite, NULL);
    }
}

sfBool check_player_attack(app_player *player, app_player *player2, float delta_time)
{
    if (player->isInAttack && !player->hasHitOpponent) {
        sfFloatRect sword_rect = sfSprite_getGlobalBounds(player->sword_entity->sprite);
        sword_rect.width -= 50;
        sfFloatRect player_rect = sfSprite_getGlobalBounds(player2->player_entity->sprite);
        if (sfFloatRect_intersects(&sword_rect, &player_rect, NULL)) {
            player->hasHitOpponent = sfTrue;
            player2->life--;
            player->current_sword_frame = 0;
            return sfTrue;
        }
    } else if (!player->isInAttack) {
        player->hasHitOpponent = sfFalse;
    }
    return sfFalse;
}

sfSprite **get_player_life_sprites(app_player *player, sfBool is_right)
{
    sfSprite **life_sprites = malloc(sizeof(sfSprite *) * max_player_life);
    for (short i = 0; i < player->life; i++) {
        int x = i * 85 + 15;
        if (is_right)
            x = 1840 - i * 85;
        life_sprites[i] = create_sprite_with_texture("assets/life.png");
        sfSprite_setPosition(life_sprites[i], (sfVector2f){x, 15});
        sfSprite_setScale(life_sprites[i], (sfVector2f){0.3, 0.3});
    }
    return life_sprites;
}
