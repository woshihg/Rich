//
// Created by 张峻领 on 24-7-27.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "../json/json.h"
#include "../map/mapdraw.h"
void walk_roll(Player *players, char* now_user, Map* map);
int Player_Route_Start(Player *players, char *now_user, Map *map, Cell pCell[70]);
void Route_Num_Change(char* now_user);

#endif //PLAYER_H
