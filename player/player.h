//
// Created by 张峻领 on 24-7-27.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../json/json.h"
#include<cstdio>
#include<cstring>
#include"../map/mapdraw.h"
#include "../terminal/terminal.h"
#include "../tool/tool.h"
#include "../money/money.h"
#include "../giftroom/gift.h"
#include <ctime>
#include <unordered_set>
int roll_dice();
int Player_Route_Start(Player *players,int routeNum, Map *map, Cell pCell[70],int max_player_num);
void After_Walk(Player *use_players, Map *map, Cell *cell, int route_num,int relative_move);
owner_enum get_player_num(char player_char);
char get_player_char(owner_enum player_num);
//int Find_Player_Num(Player* players, const char* now_user,int max_player_num);
int Player_Init(Player* players, char* now_user);
#endif //PLAYER_H
