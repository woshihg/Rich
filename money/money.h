//
// Created by Lenovo on 24-7-26.
//

#ifndef MONEY_H
#define MONEY_H
//
// Created by Lenovo on 24-7-26.
// Created by 陈曦 on 2024/7/27.
//

#include "../json/json.h"

#include "../map/mapdraw.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int get_cost(int rank);
char get_player_name(int number);
void step_cell_logit(Player *players, Player *now_player, Map *map, Cell *cell);
void invest_house_execute(Player *player, Map *map,Cell *cell);
void Set_Init_Money(Player *player);
void sell_house(Player* player, Map* map, int pos);
void pay_rentment(Player *players, Map *map, Player *now_player,Cell *cell, int pos);
Player search_by_char(Player* players, char name_to_search);
void chech_out_of_money(Player *players, Map *map,Cell* cell);
#endif //MONEY_H
///