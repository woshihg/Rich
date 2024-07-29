//
// Created by ASUS on 2024/7/28.
//

#include "gift.h"

int Is_Arrive_GiftRoom(Player* player)
{
    if(player->position==35)
    {
        printf(LIGHT_CYAN);
        printf("欢迎来到礼品屋\n");
        printf(COLOR_NULL);
        return 1;
    }
    else
        return 0;
}

void Choose_Gift(Player* player)
{
    char gift_num=0;
    char tmp=0;
    int i=0;
    printf(LIGHT_CYAN);
    printf("请选择你的礼品\n");
    printf("输入1，2选择对应的礼品，或者输入F放弃选择\n");
    printf("1:2000资金\n");
    printf("2:200点数\n");
    printf(COLOR_NULL);
    scanf("%c",&gift_num);
    tmp=getchar();
    if(gift_num=='1' && tmp=='\n')
        Choose_Money(player);
    else if(gift_num=='2' && tmp=='\n')
        Choose_Point(player);
//    else if(gift_num=='3' && tmp=='\n')
//        Choose_God(player);
    else
    {
        printf(LIGHT_CYAN);
        printf("选择礼品失败！\n");
        printf(COLOR_NULL);
    }

}

void Choose_Money(Player* player)
{
    player->money+=2000;
    printf(LIGHT_CYAN);
    printf("你的资金是 %d\n",player->money);
    printf(COLOR_NULL);
}

void Choose_Point(Player* player)
{
    player->point+=200;
    printf(LIGHT_CYAN);
    printf("你的点数是 %d\n",player->point);
    printf(COLOR_NULL);
}

//void Choose_God(Player* player)
//{
//    player->buff=1;
//    player->_continue=5;
//    printf("Choose God success!\n");
//    printf("Now you won't pay any rent in 5 rounds!\n");
//}


