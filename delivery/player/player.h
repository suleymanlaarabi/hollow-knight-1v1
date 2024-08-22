/*
** EPITECH PROJECT, 2024
** Nom du projet
** File description:
** Description du projet
*/

#ifndef __PLAYER_MANAGER__
    #define __PLAYER_MANAGER__
    #include <SFML/Graphics.h>
    #include "../utils/sprite_texture_utils.h"

typedef struct app_player {
    sprite_sheet_entity *sword_entity;
    sprite_sheet_entity *player_entity;
    sfVector2f pos;
    sfVector2f scale;
    short jump_status; // 0 = no jump | 1 = to up | 2  to down
    sfBool isInAttack;
    sfBool hasHitOpponent;
    int current_sword_frame;
    float attack_timer;
    float speed;
    short life;
    // control
    sfKeyCode move_right;
    sfKeyCode move_left;
    sfKeyCode jump;
    sfKeyCode attack;
} app_player;

app_player* init_player(
    sfKeyCode move_left,
    sfKeyCode move_right,
    sfKeyCode jump,
    sfKeyCode attack
);

void event_player_update(app_player *player, float delta_time);
void draw_player(sfRenderWindow *window, app_player *player);
void flip_player(app_player *player);


sfSprite **get_player_life_sprites(app_player *player, sfBool is_right);

sfBool check_player_attack(app_player *player, app_player *player2, float delta_time);

#endif
