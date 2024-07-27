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
void invest_house_logit(Player* player ,Cell* cell);
void invest_house_execute(Player* player, Cell* cell);
void Set_Init_Money(Player *player);

#endif //MONEY_H
