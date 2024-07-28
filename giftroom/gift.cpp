//
// Created by ASUS on 2024/7/28.
//

#include "gift.h"

int Is_Arrive_GiftRoom(Player* player)
{
    if(player->position==35)
    {
        printf("Welcome to giftroom!\n");
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
    printf("Please choose your gift!\n");
    printf("Enter 1, 2, 3 to choose gift or enter F to quit!\n");
    scanf("%c",&gift_num);
    tmp=getchar();
    fflush(stdin);              //清空缓冲区
    if(gift_num=='1' && tmp=='\n')
        Choose_Money(player);
    else if(gift_num=='2' && tmp=='\n')
        Choose_Point(player);
    else if(gift_num=='3' && tmp=='\n')
        Choose_God(player);
    else
        printf("Failed to choose gift!\n");
}

void Choose_Money(Player* player)
{
    player->money+=2000;
    printf("Your money is %d\n",player->money);
}

void Choose_Point(Player* player)
{
    player->point+=200;
    printf("Your point is %d\n",player->point);
}

void Choose_God(Player* player)
{
    player->buff=1;
    player->_continue=5;
    printf("Choose God success!\n");
    printf("Now you won't pay any rent in 5 rounds!\n");
}


