//
// Created by Chenxi on 2024/7/27.
//
#include "money.h"
#include "../terminal/terminal.h"

void Set_Init_Money(Player *player)
{
    char str[7] = {0};
    int first_money = 10000;
    printf("Please enter initial funds\n");

    fgets(str, 7, stdin);
    sscanf(str, "%d", &first_money);
    printf("Initial fund: %d\n", first_money);

    for (char i = 0; i < CELL_MAX_PLAYER; i++) {
        player[i].money = first_money;
    }
    if (first_money<1000||first_money>50000){
        printf("The initial fund is out of range, please enter again\n");
        Set_Init_Money(player);
    }
}

void step_cell_logit(Player *players, Player *now_player, Map *map, Cell *cell) {
    // In case of that the cell involved belongs to HOUSE.
    int pos = now_player->position;
    int route_num = 0;
    char str[INSTRUCTION_MAX_LEN] = {0};
    char cell_owner = 'N';
    char tmp;
    if(map->data[pos].owner == OWNER_Q){
        cell_owner = 'Q';
    } else if(map->data[pos].owner == OWNER_A){
        cell_owner = 'A';
    } else if(map->data[pos].owner == OWNER_S){
        cell_owner = 'S';
    } else if(map->data[pos].owner == OWNER_J){
        cell_owner = 'J';
    }
    char player_name = 'N';
    if(now_player->number == OWNER_Q){
        player_name = 'Q';
    } else if(now_player->number == OWNER_A){
        player_name = 'A';
    } else if(now_player->number == OWNER_S){
        player_name = 'S';
    } else if(now_player->number == OWNER_J){
        player_name = 'J';
    }
    int cell_cost = get_cost(pos);
    // char now_player_char;
    // now_player_char = get_player_name();
    if(pos == 0||pos == 28||pos == 35||pos == 49||pos == 63||pos == 64||pos == 14||pos == 65||pos == 66||pos == 67||pos == 68||pos == 69)
        printf("This is a special plot and cannot be purchased\n");
    else{
        if (player_name == cell_owner)
        {
            if(now_player->money >= cell_cost) {
                printf("Arrived at your space, sufficient funds, do you want to upgrade?\n");

                fgets(str, INSTRUCTION_MAX_LEN, stdin);
                fflush(stdin);
                if(str[0] == 'Y'||str[0] == 'y') invest_house_execute(now_player, map,cell);
                else   printf("forgive to upgrade\n");

            }
            else printf("lack of money,unable to upgrade!\n");
        }
        else
        {
            if (cell_owner == 'N' && (now_player->money >= cell_cost))
            {
                printf("Arrived at an empty space, sufficient funds, do you want to buy?\n");
                fgets(str, INSTRUCTION_MAX_LEN, stdin);
                fflush(stdin);
                if(str[0] == 'Y'||str[0] == 'y')
                {
                    printf("Successfully purchased!\nThe cost is %d\n",cell_cost);
                    printf("you have %d money left\n",now_player->money - cell_cost);
                    (now_player->properties)[pos]++;
                    map->data[pos].owner = (owner_enum)now_player->number;
                    now_player->money -= cell_cost;
                    chech_out_of_money(now_player, map , cell);
                }
                else
                {
                    printf("Purchasing action declined.\n");
                }
            }
            else if(cell_owner == 'N' && (now_player->money < cell_cost)) {
                //printf("Arrived at an empty space,out of money,unable to purchase\n");
                printf("You have arrived at an empty property with insufficient fund, unable to purchase it.\n");
            }
        }
    }
}

void invest_house_execute(Player *player, Map *map,Cell *cell)
{
    int pos = player->position;
    int cost = get_cost(pos);
    int house;
    if (player->properties[pos] >= 4)
    {
        printf("Highest Level yet, unable to upgrade anymore.\n");
    }
    else
    {
        if (player->money - cost)
        {
            printf("Property upgraded successfully!\n");
            if (player->properties[pos] == 0)
                player->property_count++;
            player->properties[pos]++;
            player->money -= cost;
            chech_out_of_money(player, map , cell);
            house=map->data[pos].kind;
            house ++;
            map->data[pos].kind = (kind_enum)house;
            printf("Now you have %d money left\n",player->money);
        }
        else
        {
            printf("Unable to afford the cost!\n");
        }
    }
}

int get_cost(int pos)
{
    if (pos > 0 && pos < 28)
        return 200;
    else if (pos > 28 && pos < 35)
        return 500;
    else if (pos > 35 && pos < 69)
        return 300;
    else
        return 0;
}

void sell_house(Player *player, Map *map, int pos)
{
    if (player->number == map->data[pos].owner)
    {
        int income = map->data[pos].kind * get_cost(pos) * 2;
        player->money += income;
        player->property_count--;
        // cell[pos].house_scale = 0;
        player->properties[pos] = 0;
        map->RemoveSpace(pos);
        printf("Property sold successfully!\n");
        printf("Now you have %d money left\n",player->money);
    }
    else
    {
        printf("This is not your property so you have no authority to sell it!\n");
    }
}

void pay_rentment(Player *players, Map *map, Player *now_player,Cell *cell , int pos)
{
    int rentment = map->data[pos].kind * get_cost(pos) / 2;
    int owner = 0;
    for (int i = 0; i < 4; ++i) {
        if (map->data[pos].owner == players[i].number) {
            owner = i;
            break;
        }
    }
    players[owner].money += rentment;
    now_player->money -= rentment;
    chech_out_of_money(now_player, map, cell);
}

//Player search_by_char(Player *players, char name_to_search)
//{
//    for (int i = 0; i < 4; i++)
//    {
//        char name = get_player_name(players[i].number);
//        if (name == name_to_search)
//            return players[i];
//    }
//    printf("Failed to search\n");
//    return players[0];
//}

void chech_out_of_money(Player *players, Map *map,Cell* cell) {
    if(players->money < 0) {
        printf("you are out of game\n");
        players->alive = false;
        map->data[players->position].Remove_Passer((owner_enum)players->number);
        for (int i = 0;i<70;i++) {
            if (players->properties[i] != 0) {
                map->RemoveSpace(i);
            }
        }
        map->SetCell(cell);
        map->PrintMap();
    }
}



// 破产  房产数  查询 Help
