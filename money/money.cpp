//
// Created by 陈曦 on 2024/7/27.
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

void invest_house_logit(Player* player ,Cell* cell) {
    // In case of that the cell involved belongs to HOUSE.
    int pos = player->position;
    char cell_owner = cell[pos].owner;
    char player_name = get_player_name(player->number);

    if(player_name == cell_owner)
    {
        invest_house_execute(player, cell);
    }
    /*else {
        pay_rentment();
    }*/
}

void invest_house_execute(Player* player, Cell* cell) {
    int pos = player->position;
    int cost = get_cost(cell[pos].rank);
    if(player->properties[pos] >= 4) {
        printf("Highest Scale yet, unable to upgrade anymore.\n");
    }
    else{
        if(player->money - cost) {
            printf("Property upgraded successfully!\n");
            if(player->properties[pos] == 0)
                player->property_count++;
            player->properties[pos]++;
            player->money -= cost;

        }
        else {
            printf("Unable to afford the cost!");
        }
    }
}

int get_cost(int rank) {
    switch(rank) {
        case 1:
            return 200;
        case 2:
            return 500;
        case 3:
            return 300;
        default:
            return 0;
    }
}

char get_player_name(int number) {
    switch (number) {
        case 1:
            return  'Q';
        break;
        case 2:
            return'A';
        break;
        case 3:
            return 'S';
        break;
        case 4:
            return 'J';
        break;
        default:
            return '0';
        break;
    }
}

void sell_house(Player* player, Cell* cell, int pos) {
    char owner = get_player_name(player->number);
    if(owner == cell[pos].owner) {
        int income = cell[pos].sum_invested_money*2;
        player->money += income;
        player->property_count--;
        // cell[pos].house_scale = 0;
        player->properties[pos] = 0;
        cell[pos].sum_invested_money = 0;
        cell[pos].owner = 'N';
    }
    else {
        printf("这不是你的房子，无权出售！\n");
    }

}