//
// Created by ASUS on 2024/7/28.
//

#ifndef THE_RICH_GIFT_H
#define THE_RICH_GIFT_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../json/json.h"
#include "../map/mapdraw.h"

int Is_Arrive_GiftRoom(Player* player);
void Choose_Gift(Player* player);
void Choose_Money(Player* player);
void Choose_Point(Player* player);
void Choose_God(Player* player);

#endif //THE_RICH_GIFT_H
