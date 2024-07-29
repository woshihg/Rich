//
// Created by 张峻领 on 24-7-27.
//

#include "player.h"
#include "../json/json.h"
#include<cstdio>
#include<cstring>
#include"../map/mapdraw.h"
#include "../terminal/terminal.h"
#include <ctime>

//players[4] 玩家结构体数组

int compare_chars(const void* a, const void* b) {
    return *(const char*)a - *(const char*)b;
}
void sort_string(char* str) {
    qsort(str, strlen(str), sizeof(char), compare_chars);
}

int Player_Init(Player* players, char* now_user){
    int max_player_num = 0;
    for (int i = 0; i < CELL_MAX_PLAYER; ++i) {
        players[i].number = i;
        players[i].position = 0;
        players[i].money = 0;
        players[i].point = 0;
        players[i].prison = false;
        players[i].hospital = false;
        players[i].alive = false;
        players[i].de_continue = 0;
    }
    while(true) {
        int if_continue = 1;
        int i = 0;
        char input_user[5] = {0};
        printf(LIGHT_CYAN);
        printf("请输入玩家ID，e.g. 1234\n");
        printf("1:钱夫人\n");
        printf("2:阿土伯\n");
        printf("3:孙小美\n");
        printf("4:金贝贝\n");
        printf(COLOR_NULL);
        scanf("%s", input_user);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}// 清空输入缓冲区
        input_user[4] = '\0';
//        sort_string(input_user);
        printf(LIGHT_CYAN);
        printf("玩家ID : %s\n", input_user);
        printf(COLOR_NULL);

        for (i = 0; i < CELL_MAX_PLAYER; ++i) {
            if (input_user[i] == '\0') {
                break;
            }
            switch (input_user[i]) {
                case '1':
                    players[i].number = 1;
                    players[i].alive = true;
                    break;
                case '2':
                    players[i].number = 2;
                    players[i].alive = true;
                    break;
                case '3':
                    players[i].number = 3;
                    players[i].alive = true;
                    break;
                case '4':
                    players[i].number = 4;
                    players[i].alive = true;
                    break;
                default:
                    printf(LIGHT_CYAN);
                    printf("玩家选择错误 :");
                    printf(" %c",input_user[i]);
                    printf("\n");
                    printf(COLOR_NULL);
                    if_continue = 0;
                    break;
            }
        }
        if (if_continue){
            max_player_num = i;
            printf(LIGHT_CYAN);
            printf("玩家选择成功 : %s\n", input_user);
            printf("最大玩家数为 : %d\n",max_player_num);
            printf(COLOR_NULL);
            break;
        }
    }
    return max_player_num;
}
int Find_Player_Num(Player* players, const char* now_user,int max_player_num) {
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
    printf(LIGHT_CYAN);
    printf("错误：找不到玩家\n");
    printf(COLOR_NULL);
    return 0;
}

//void Route_Num_Change(Player * players,char* now_user ,int max_player_num) {
//    static int route_num = 0;
////    route_num = Find_Player_Num(players, now_user, max_player_num);
//    ++route_num;
//    if (route_num == max_player_num) {
//        route_num = 0;
//    }
//    if(players[route_num].number == OWNER_Q){
//        now_user[0] = 'Q';
//    } else if(players[route_num].number == OWNER_A){
//        now_user[0] = 'A';
//    } else if(players[route_num].number == OWNER_S){
//        now_user[0] = 'S';
//    } else if(players[route_num].number == OWNER_J){
//        now_user[0] = 'J';
//    }
//}

int Player_Route_Start(Player *players, int route_num, Map *map, Cell pCell[70],int max_player_num) {//回合开始
//    static int route_num = 0;
////    route_num = Find_Player_Num(players, now_user,max_player_num);
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


// Function to return a random number between 1 and 6
int roll_dice() {
    srand(static_cast<unsigned>(std::time(nullptr))); // Seed the random number generator
    int dice = rand() % 6 + 1;
    printf(LIGHT_CYAN);
    printf("骰子点数为 %d\n",dice);
    printf(COLOR_NULL);
    return dice; // Generate a random number between 1 and 6
}
