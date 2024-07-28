//
// Created by Chenxi on 2024/7/27.
//
#include "money.h"
void Set_Init_Money(Player *player)
{
    char str[6] = {0};
    int first_money = 0;
    printf("Please enter initial funds\n");

    fgets(str, 6, stdin);
    sscanf(str, "%d", &first_money);
    printf("Initial funds: %d\n", first_money);

    for (char i = 0; i < CELL_MAX_PLAYER; i++)
    {
        player[i].money = first_money;
    }
}

void step_cell_logit(Player *players, Player *now_player, Map *map)
{
    // In case of that the cell involved belongs to HOUSE.
    int pos = now_player->position;
    int route_num = 0;
    char cell_owner = 'N';
    if(map->data[pos].owner == OWNER_Q){
        cell_owner = 'Q';
    } else if(map->data[pos].owner == OWNER_A){
        cell_owner = 'A';
    } else if(map->data[pos].owner == OWNER_S){
        cell_owner = 'S';
    } else if(map->data[pos].owner == OWNER_J){
        cell_owner = 'J';
    }
    char player_name = get_player_name(now_player->number);
    int cell_cost = get_cost(pos);
    char choose;
    // char now_player_char;
    // now_player_char = get_player_name();

    if (player_name == cell_owner)
    {
        invest_house_execute(now_player, map);
    }
    else
    {
        if (cell_owner == 'N' && (now_player->money >= cell_cost))
        {
            printf("Arrived at an empty space, sufficient funds, do you want to buy?\n");
            scanf("%c", &choose);
            getchar();
            if (choose == 'Y')
            {
                printf("Successfully purchased!\n");
                (now_player->properties)[pos]++;
                map->data[pos].owner = (owner_enum)now_player->number;
                now_player->money -= cell_cost;
            }
            else if (choose == 'N')
            {
                printf("Declined to purchase\n");
            }
        }
        else
        {
            pay_rentment(players, map, now_player, cell_owner, pos);
        }
    }
}

void invest_house_execute(Player *player, Map *map)
{
    int pos = player->position;
    int cost = get_cost(pos);
    if (player->properties[pos] >= 4)
    {
        printf("Highest Scale yet, unable to upgrade anymore.\n");
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
            map->data[pos].base ++;
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

char get_player_name(int number)
{
    switch (number)
    {
        case 1:
            return 'Q';
            break;
        case 2:
            return 'A';
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

void sell_house(Player *player, Cell *cell, int pos)
{
    char owner = get_player_name(player->number);
    if (owner == cell[pos].owner)
    {
        int income = cell[pos].sum_invested_money * 2;
        player->money += income;
        player->property_count--;
        // cell[pos].house_scale = 0;
        player->properties[pos] = 0;
        cell[pos].sum_invested_money = 0;
        cell[pos].owner = 'N';
        player->properties[pos] = 0;
        printf("Property sold successfully!\n");
    }
    else
    {
        printf("You are not permitted to sell the property since it's not yours!\n");
    }
}

void pay_rentment(Player *players, Map *cell, Player *now_player, char owner, int pos)
{
    for (int i = 0; i <= 3; i++)
    {
        char name = get_player_name(players[i].number);
        if (name == owner)
        {
            int rentment = cell->data[pos].base * get_cost(pos) / 2;
            players[i].money += rentment;
            now_player->money -= rentment;
        }
    }
}

Player search_by_char(Player *players, char name_to_search)
{
    for (int i = 0; i < 4; i++)
    {
        char name = get_player_name(players[i].number);
        if (name == name_to_search)
            return players[i];
    }
    printf("Failed to search\n");
    return players[0];
}

// void chech_out_of_money(Player *players, Map *map) {
//     if(players->money < 0) {
//         printf("you are out of game\n");
//
//     }
// }



// 破产  房产数  查询 Help
