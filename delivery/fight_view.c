/*
** EPITECH PROJECT, 2024
** Nom du projet
** File description:
** Description du projet
*/

#include "./fight_view.h"

void fight_view__render(
    sfRenderWindow *window,
    game_app *app,
    sfClock *clock,
    sfEvent event,
    sfSprite **life_sprites_player,
    sfSprite **life_sprites_player2
    ) {
    float delta_time = sfTime_asSeconds(sfClock_restart(clock));
    event_player_update(app->player, delta_time);
    event_player_update(app->player2, delta_time);
    sfRenderWindow_clear(window, sfColor_fromRGB(0, 0, 0));
    sfRenderWindow_drawSprite(window, app->decor, NULL);
    draw_player(window, app->player);
    draw_player(window, app->player2);
    for (int i = 0; i < app->player->life; i++) {
        sfRenderWindow_drawSprite(window, life_sprites_player[i], NULL);
    }
    for (int i = 0; i < app->player2->life; i++) {
        sfRenderWindow_drawSprite(window, life_sprites_player2[i], NULL);
    }
    check_player_attack(app->player, app->player2, delta_time);
    check_player_attack(app->player2, app->player, delta_time);
}