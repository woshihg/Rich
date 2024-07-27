//
// Created by Lenovo on 24-7-26.
//

#include "money.h"

void Set_Init_Money(Player *player)
{
    char str[6]={0};
    int first_money=0;
    printf("请输入初始资金\n");

    fgets(str,6,stdin);
    sscanf(str, "%d", &first_money);
    printf("初始资金为：%d\n",first_money);

    for(char i=0;i<CELL_MAX_PLAYER;i++)
    {
        player[i].money = first_money;
    }
}















