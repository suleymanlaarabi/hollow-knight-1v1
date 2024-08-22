/*
** EPITECH PROJECT, 2024
** Nom du projet
** File description:
** Description du projet
*/

#ifndef __FIGHT_VIEW__
    #define __FIGHT_VIEW__
    #include <SFML/Graphics.h>
    #include "./app/app.h"
    
void fight_view__render(
    sfRenderWindow *window,
    game_app *app,
    sfClock *clock,
    sfEvent event,
    sfSprite **life_sprites_player,
    sfSprite **life_sprites_player2
); 

#endif
