//
// Created by 张峻领 on 24-7-27.
//

#include "player.h"
#include "../json/json.h"
#include<cstdio>
#include<cstring>
#include"../map/mapdraw.h"
#include "../terminal/terminal.h"

//players[4] 玩家结构体数组

int Find_Player_Num(Player* players, char* now_user,int max_player_num) {
    int route_num = 0;
    if(now_user[0] == 'Q'){
        route_num = OWNER_Q;
    } else if(now_user[0] == 'A'){
        route_num = OWNER_A;
    } else if(now_user[0] == 'S'){
        route_num = OWNER_S;
    } else if(now_user[0] == 'J'){
        route_num = OWNER_J;
    }
    for (int i = 0; i < max_player_num; ++i) {
        if (players[i].number == route_num) {
            return i;
        }
    }
    printf("error: can't find player\n");
    return 0;
}

void Route_Num_Change(Player * players,char* now_user ,int max_player_num) {
    int route_num = 0;
    route_num = Find_Player_Num(players, now_user, max_player_num);
    ++route_num;
    if (route_num == max_player_num) {
        route_num = 0;
    }
    if(players[route_num].number == OWNER_Q){
        now_user[0] = 'Q';
    } else if(players[route_num].number == OWNER_A){
        now_user[0] = 'A';
    } else if(players[route_num].number == OWNER_S){
        now_user[0] = 'S';
    } else if(players[route_num].number == OWNER_J){
        now_user[0] = 'J';
    }
}

int Player_Route_Start(Player *players, char *now_user, Map *map, Cell pCell[70],int max_player_num) {//回合开始
    int route_num = 0;
    route_num = Find_Player_Num(players, now_user,max_player_num);
    int if_continue = 0;
    if (players[route_num].prison || players[route_num].hospital || !players[route_num].alive) {
        //用户轮空
        players[route_num].de_continue--;
        if (players[route_num].de_continue == 0) {
            players[route_num].prison = false;
            players[route_num].hospital = false;
        }
        if_continue = 1;
    }
    return if_continue;
}
void walk_roll(Player *players, char* now_user, Map* map,int max_player_num)
{//回合结束
    //判断当前玩家状态
    int route_num = 0;
    route_num = Find_Player_Num(players, now_user,max_player_num);
    int dice_num;
    char temp[10];
    int new_position;
    srand((unsigned) time(NULL));
    dice_num = rand() % 6 + 1;
    printf("your dice point: %d\n", dice_num);
    new_position = players[route_num].position + dice_num;

    map->PlayerGoto((owner_enum)players[route_num].number,
                    players[route_num].position,
                    new_position);
    players[route_num].position = new_position;
}
