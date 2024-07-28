//
// Created by 张峻领 on 24-7-27.
//
#ifndef TOOL_H
#define TOOL_H
#include "../json/json.h"
#include "../map/mapdraw.h"
void PlayerTool(Player* player);
void PlayerBuyTool(struct Player* player, int toolID);
void PlayerGetBlock(Player* player);
void PlayerGetRobot(Player* player);
void PlayerGetBomb(Player* player);
void Tool_Use(Player* use_players,Map* map,int route_num,int pos);
void ToolCreat(int poistion, int tollkind);
void robot_use(int pos,Map* map);
int tool_to_hospital(Player* player,Map* map,int origin_pos,int final_pos);
void in_mountain(Player* player);
#endif //TOOL_H
