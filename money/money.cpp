//
// Created by Chenxi on 2024/7/27.
//
#include "money.h"
#include "../terminal/terminal.h"

void Set_Init_Money(int& init_money)
{
    char str[7] = {0};
    int first_money = 10000;
    printf(LIGHT_CYAN);
    printf("�������ʼ�ʽ�1000~50000��\n");
    printf(COLOR_NULL);

    fgets(str, 7, stdin);
    sscanf(str, "%d", &first_money);
    fflush(stdin);
    printf(LIGHT_CYAN);
    printf("��ʼ�ʽ���: %d\n", first_money);
    printf(COLOR_NULL);

    init_money = first_money;
    if (first_money<1000||first_money>50000){
        printf(LIGHT_CYAN);
        printf("��ʼ�ʽ𳬳�����Χ�����������룡\n");
        printf(COLOR_NULL);
        Set_Init_Money(init_money);
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
    if(pos == 0||pos == 28||pos == 35||pos == 49||pos == 63||pos == 64||pos == 14||pos == 65||pos == 66||pos == 67||pos == 68||pos == 69) {
        printf(LIGHT_CYAN);
        printf("����һ������ؿ飬���ܹ���\n");
        printf(COLOR_NULL);
    }
    else{
        if (player_name == cell_owner)
        {
            if(now_player->money >= cell_cost && (map->data[pos].kind < 4)) {

                printf(LIGHT_CYAN);
                printf("�������Լ��ĵز����ʽ���㣬�Ƿ������ز�?\n");
                printf(COLOR_NULL);

                fgets(str, INSTRUCTION_MAX_LEN, stdin);
                if(str[0] == 'Y'||str[0] == 'y') invest_house_execute(now_player, map,cell);
                else {
                    printf(LIGHT_CYAN);
                    printf("��������\n");
                    printf(COLOR_NULL);
                }

            }else if(map->data[pos].kind >= 4){
                printf(LIGHT_CYAN);
                printf("��ĵز��Ѿ��������޷�������\n");
                printf(COLOR_NULL);
            }
            else {
                printf(LIGHT_CYAN);
                printf("�������Լ��ĵز����ʽ��㣬�޷�������\n");
                printf(COLOR_NULL);
            }
        }
        else
        {
            if (cell_owner == 'N' && (now_player->money >= cell_cost))
            {
                printf(LIGHT_CYAN);
                printf("����һ��յ����ʽ���㣬�Ƿ���\n");
                printf(COLOR_NULL);

                fgets(str, INSTRUCTION_MAX_LEN, stdin);
                if(str[0] == 'Y'||str[0] == 'y')
                {
                    printf(LIGHT_CYAN);
                    printf("����ɹ�\n������ %d\n",cell_cost);
                    printf("��ʣ�� %d Ԫ\n",now_player->money - cell_cost);
                    printf(COLOR_NULL);
                    (now_player->properties)[pos]++;
                    map->data[pos].owner = (owner_enum)now_player->number;
                    now_player->money -= cell_cost;
                    now_player->property_count++;
                    chech_out_of_money(now_player, map , cell);
                }
                else
                {
                    printf(LIGHT_CYAN);
                    printf("��������\n");
                    printf(COLOR_NULL);
                }
            }
            else if(cell_owner == 'N' && (now_player->money < cell_cost)) {
                //printf("Arrived at an empty space,out of money,unable to purchase\n");
                printf(LIGHT_CYAN);
                printf("����һ��յص��ʽ��㣬�޷�����\n");
                printf(COLOR_NULL);
            }
        }
    }
}

void invest_house_execute(Player *player, Map *map, Cell *cell)
{
    int pos = player->position;
    int cost = get_cost(pos);
    int house;
    if (player->properties[pos] >= 4)
    {
        printf(LIGHT_CYAN);
        printf("�ز��ȼ��ﵽ��ߣ��޷���������\n");
        printf(COLOR_NULL);
    }
    else
    {
        if (player->money - cost>= 0)
        {
            printf(LIGHT_CYAN);
            printf("�ز������ɹ���\n");
            printf(COLOR_NULL);
            if (player->properties[pos] == 0)
                player->property_count++;
            player->properties[pos]++;
            player->money -= cost;
            chech_out_of_money(player, map , cell);
            house=map->data[pos].kind;
            house ++;
            map->data[pos].kind = (kind_enum)house;
            printf(LIGHT_CYAN);
            printf("������ʣ�� %d Ԫ\n",player->money);
            printf(COLOR_NULL);
        }
        else
        {
            printf(LIGHT_CYAN);
            printf("�ʽ��㣡\n");
            printf(COLOR_NULL);
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
        printf(LIGHT_CYAN);
        printf("�ز��ɹ�����!\n");
        printf("������ʣ�� %d Ԫ\n",player->money);
        printf(COLOR_NULL);
    }
    else
    {
        printf(LIGHT_CYAN);
        printf("�ⲻ����ĵز�����������\n");
        printf(COLOR_NULL);
    }
}

void pay_rentment(Player *players, Map *map, Player *now_player,Cell *cell , int pos)
{
    if (now_player->buff == 0)
    {
        int rentment = map->data[pos].kind * get_cost(pos) / 2;
        int owner = 0;
        for (int i = 0; i < 4; ++i) {
            if (map->data[pos].owner == players[i].number) {
                owner = i;
                break;
            }
        }
        now_player->money -= rentment;
        if(now_player->money >= 0)
            players[owner].money += rentment;
        else {
            printf(LIGHT_CYAN);
            printf("��������Ʋ�����Ǯ������\n");
            printf(COLOR_NULL);
        }
        chech_out_of_money(now_player, map, cell);
    }  else {
        if(now_player->_continue == 0) {
            now_player->buff = false;
        }
        printf(LIGHT_CYAN);
        printf("�в����ӣ����轻�⣡\n");
        printf(COLOR_NULL);
    }
}


void chech_out_of_money(Player *players, Map *map,Cell* cell) {
    if(players->money < 0) {
        printf(LIGHT_CYAN);
        printf("���Ʋ��ˣ�\n");
        printf(COLOR_NULL);
        players->money=0;
        players->alive = false;
        map->data[players->position].Remove_Passer((owner_enum)players->number);
        for (int i = 0;i<70;i++) {
            if (players->properties[i] != 0) {
                map->RemoveSpace(i);
            }
            players->properties[i] = 0;
        }
    }
}



// �Ʋ�  ������  ��ѯ Help
