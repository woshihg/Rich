//
// Created by 张峻领 on 24-7-27.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../json/json.h"
#include "../map/mapdraw.h"
int roll_dice();
int Player_Route_Start(Player *players,int routeNum, Map *map, Cell pCell[70],int max_player_num);
//void Route_Num_Change(Player * players,char* now_user,int max_player_num);
int Find_Player_Num(Player* players, const char* now_user,int max_player_num);
int Player_Init(Player* players, char* now_user);
#endif //PLAYER_H
