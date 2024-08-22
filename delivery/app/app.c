/*
** EPITECH PROJECT, 2024
** csfml
** File description:
** app
*/

#include "./app.h"
#include "../player/player.h"
#include "../decor.h"
#include <stdlib.h>
#include <SFML/Graphics.h>

game_app* init_game_app()
{
    game_app *app = malloc(sizeof(game_app));
    app_player *player = init_player(sfKeyLeft, sfKeyRight, sfKeyUp, sfKeyN);
    app_player *player2 = init_player(sfKeyQ, sfKeyD, sfKeySpace, sfKeyC);
    player2->pos.x += 1600;
    flip_player(player2);
    sfSprite *decor = load_decor();

    app->player = player;
    app->player2 = player2;
    app->decor = decor;
    return app;
}
