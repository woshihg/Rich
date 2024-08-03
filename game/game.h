//
// Created by 15779 on 24-7-29.
//

#ifndef THE_RICH_GAME_H
#define THE_RICH_GAME_H

#include "../player/player.h"
#include "../terminal/terminal.h"
#include "../money/money.h"
#include "../tool/tool.h"
#include "../json/json.h"
#include <cstdlib>
#include <ctime>

void Game_Start(char *filename,Player *use_players, Map &map, Cell *cell, jsonMap &jsonmap,char* users, int playerNum, char *now_user,int debug);

#endif //THE_RICH_GAME_H
