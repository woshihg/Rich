//
// Created by 15779 on 24-7-29.
//

#ifndef THE_RICH_GAME_H
#define THE_RICH_GAME_H

#include "../player/player.h"

void Game_Start(char *filename,Player *use_players, Map &map, Cell *cell, jsonMap &jsonmap,char* users, int playerNum, char *now_user);

#endif //THE_RICH_GAME_H
