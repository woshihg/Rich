//
// Created by 陈曦 on 2024/7/27.
//
#include "money.h"
void invest_house_logit(Player* player ,Cell* cell) {
    // In case of that the cell involved belongs to HOUSE.
    int pos = player->position;
    char cell_owner = cell[pos].owner;
    char player_name;
    switch (player->number) {
        case 1:
            player_name = 'Q';
        break;
        case 2:
            player_name = 'A';
        break;
        case 3:
            player_name = 'S';
        break;
        case 4:
            player_name = 'J';
        break;
        default:
            player_name = '0';
        break;
    }
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
    if(cell[pos].house_scale >= 3) {
        printf("Highest Scale yet, unable to upgrade anymore.\n");

        if(player->money - cost) {
            printf("Property upgraded successfully!\n");
            cell[pos].house_scale++;
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