/*
** EPITECH PROJECT, 2017
** name
** File description:
** description
*/

#include "./sprite_texture_utils.h"
#include <stdlib.h>

void set_sprite(sprite_sheet_entity *entity, int offset)
{
    sfIntRect rect = {
        (entity->startColumn + offset) * entity->frameWidth,
        ((entity->startRow) * entity->frameHeight) + 1,
        entity->frameWidth,
        entity->frameHeight
    };

    sfSprite_setTextureRect(entity->sprite, rect);
}

void set_empty_sprite(sprite_sheet_entity *entity)
{
    sfIntRect rect = {
        0,
        0,
        0,
        0
    };

    sfSprite_setTextureRect(entity->sprite, rect);
}

sprite_sheet_entity *init_sprite_entity(
    char texture[],
    int frameWidth,
    int frameHeight,
    int startColumn,
    int startRow
)
{
    sprite_sheet_entity *entity = malloc(sizeof(sprite_sheet_entity));

    entity->sprite = create_sprite_with_texture(texture);
    entity->frameWidth = frameWidth;
    entity->frameHeight = frameHeight;
    entity->startColumn = startColumn;
    entity->startRow = startRow;
    return entity;
}

sfBool is_flipped(sfSprite *sprite)
{
    sfBool is_flipped = sfFalse;
    sfVector2f scale = sfSprite_getScale(sprite);

    if (scale.x < 0) {
        is_flipped = sfTrue;
    }
    return is_flipped;
}

sfSprite *create_sprite_with_texture(char texture[])
{
    sfSprite *my_sprite = sfSprite_create();
    sfTexture *my_texture = sfTexture_createFromFile(texture, NULL);

    sfSprite_setTexture(my_sprite, my_texture, sfFalse);
    return my_sprite;
}

void update_animation(
    sprite_sheet_entity *entity,
    int total_frames,
    float delta_time,
    float frame_time
)
{
    static int frame = -1;
    static float timer = 0.0f;

    if (frame == -1) {
        frame = entity->startRow;
    }
    timer += delta_time;
    if (timer >= frame_time) {
        timer -= frame_time;
        frame++;
        if (frame >= entity->startRow + total_frames) {
            frame = entity->startRow;
        }
        set_sprite(entity, frame);
    }
}