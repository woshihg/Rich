//
// Created by ASUS on 2024/7/28.
//

#include "gift.h"

int Is_Arrive_GiftRoom(Player* player)
{
    if(player->position==35)
    {
        printf(LIGHT_CYAN);
        printf("��ӭ������Ʒ��\n");
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
    printf("��ѡ�������Ʒ\n");
    printf("����1��2ѡ���Ӧ����Ʒ����������F����ѡ��\n");
    printf("1:2000�ʽ�\n");
    printf("2:200����\n");
    printf(COLOR_NULL);
    scanf("%c",&gift_num);
    tmp=getchar();
    if(gift_num=='1' && tmp=='\n')
        Choose_Money(player);
    else if(gift_num=='2' && tmp=='\n')
        Choose_Point(player);
    else
    {
        printf(LIGHT_CYAN);
        printf("ѡ����Ʒʧ�ܣ�\n");
        printf(COLOR_NULL);
    }

}

void Choose_Money(Player* player)
{
    player->money+=2000;
    printf(LIGHT_CYAN);
    printf("����ʽ��� %d\n",player->money);
    printf(COLOR_NULL);
}

void Choose_Point(Player* player)
{
    player->point+=200;
    printf(LIGHT_CYAN);
    printf("��ĵ����� %d\n",player->point);
    printf(COLOR_NULL);
}


