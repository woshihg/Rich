//
// Created by 张峻领 on 24-7-27.
//

#ifndef TOOL_H
#define TOOL_H
#include "../json/json.h"
#include "../map/mapdraw.h"

void PlayerTool(Player* player,Map* map);
void PlayerBuyTool(struct Player* player, int toolID);
void PlayerGetBlock(Player* player);
void PlayerGetRobot(Player* player);
void PlayerGetBomb(Player* player);
void tool_use(Player *player, Map *map);
void tool_map(Player* player,Map* map);
void ToolCreat(int poistion, int tollkind);
#endif //TOOL_H
