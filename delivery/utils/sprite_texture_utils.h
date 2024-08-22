/*
** EPITECH PROJECT, 2017
** name
** File description:
** description
*/

#ifndef __SPRITE_TEXTURE_UTILS__
    #define __SPRITE_TEXTURE_UTILS__
    #include <SFML/Graphics.h>

sfSprite *create_sprite_with_texture(char texture[]);

typedef struct sprite_sheet_entity {
    sfSprite *sprite;
    int frameWidth;
    int frameHeight;
    int startColumn;
    int startRow;
} sprite_sheet_entity;

sprite_sheet_entity *init_sprite_entity(
    char texture[],
    int frameWidth,
    int frameHeight,
    int startColumn,
    int startRow
);

void set_sprite(sprite_sheet_entity *entity, int offset);
void set_empty_sprite(sprite_sheet_entity *entity);
sfBool is_flipped(sfSprite *sprite);

void update_animation(
    sprite_sheet_entity *entity,
    int total_frames,
    float delta_time,
    float frame_time
);

#endif
