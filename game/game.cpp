//
// Created by 15779 on 24-7-29.
//

#include "game.h"
#include "../terminal/terminal.h"
#include "../money/money.h"
#include "../tool/tool.h"
#include <cstdlib>
#include <ctime>

using namespace std;

char * name_ch=0;

void Print_Query(Player *use_players, int routeNum, char *now_user) {
    printf(LIGHT_CYAN);
    printf("@ 玩家 : ");
    printf("%s\n",name_ch);
    printf("\t资金 : ");
    printf("%d\n", use_players[routeNum].money);
    printf("\t点数 : ");
    printf("%d\n", use_players[routeNum].point);
    printf("你一共拥有 %d 套房产。细节如下",use_players[routeNum].property_count);
    //printf("\tProperties details: ");
    for(int j =0; j<70; j++) {
        if (use_players[routeNum].properties[j]) {
            printf(" [位置: %d 等级: %d]",j,use_players[routeNum].properties[j] - 1);
        }
    }
    printf("\n");
    printf("\t路障 : ");
    printf("%d\n", use_players[routeNum].block);
    printf("\t机器娃娃 : ");
    printf("%d\n", use_players[routeNum].robot);
    printf("\t正面增益及持续时间 : ");
    printf("%d %d\n", use_players[routeNum].buff, use_players[routeNum]._continue);
    printf(COLOR_NULL);
}

void Print_Help(){
    printf(LIGHT_CYAN);
    printf("你可以使用下列指令。\n");
    printf("Roll: 掷骰子，随机走1~6步。\n");
    printf("Sell n: 你可以卖出任意一套属于你的房产，卖出获得的金钱为你在该房产处花费资金的两倍。\n");
    printf("Block n: 在前后10格以内放置一个路障。\n");
    printf("Robot: 清除前方10格以内的所有障碍。\n");
    printf("Query: 显示你的资产\n");
    printf("Quit: 强制退出游戏\n");
    printf(COLOR_NULL);
}

void Print_PlayerTurn(Player *use_players, int routeNum, char *now_user,int turn_num) {
    switch(use_players[routeNum].number)
    {
        case 1:
            name_ch="钱夫人";
            printf(COLOR_RED);
            break;
        case 2:
            name_ch="阿土伯";
            printf(COLOR_GREEN);
            break;
        case 3:
            name_ch="孙小美";
            printf(COLOR_BLUE);
            break;
        case 4:
            name_ch="金贝贝";
            printf(COLOR_YELLOW);
            break;
        default:break;
    }
    printf("@ 现在是 %s 的回合", name_ch);
    printf(COLOR_NULL);
    printf("\n");
}

void Print_PlayerOver(Player *use_players, int routeNum, char *now_user) {
    switch(use_players[routeNum].number)
    {
        case 1:
            name_ch="钱夫人";
            printf(COLOR_RED);
            break;
        case 2:
            name_ch="阿土伯";
            printf(COLOR_GREEN);
            break;
        case 3:
            name_ch="孙小美";
            printf(COLOR_BLUE);
            break;
        case 4:
            name_ch="金贝贝";
            printf(COLOR_YELLOW);
            break;
        default:break;
    }
    printf("@ %s 的回合结束了", name_ch);
    printf(COLOR_NULL);
    printf("\n");
}

int Route_Start(Player *use_players,int routeNum,char* now_user,Map &map,Cell *cell,char *filename) {
    int flag_ifwalk = 1;
    int flag_ifover = 0;
    int flag_ifshop = 1;
    int flag_ifusetoll =1;
    int flag_ifquit = 0;
    map.data[use_players[routeNum].position].Remove_Passer((owner_enum)use_players[routeNum].number);//轮次开始的时候让人显示到上层
    map.data[use_players[routeNum].position].Add_Passer((owner_enum)use_players[routeNum].number);
    while (!flag_ifover && !flag_ifquit) {
        map.SetCell(cell);
        map.PrintMap();
        //输入命令
        terminal(use_players[routeNum],filename);

        if (strcmp(RichStructure.instruction, "Sell") == 0) {
            sell_house(&(use_players[routeNum]),&map,RichStructure.parameter);
        }else
        if (strcmp(RichStructure.instruction, "Query") == 0) {
            Print_Query(use_players, routeNum, now_user);
        }else
        if (strcmp(RichStructure.instruction, "Quit") == 0) {
            flag_ifquit = 1;
        }else
        if (strcmp(RichStructure.instruction, "Step") == 0) {
            After_Walk(use_players, &map, cell, routeNum,RichStructure.parameter);
            flag_ifover = 1;
        }else
        if (strcmp(RichStructure.instruction, "Roll") == 0 ||
            strcmp(RichStructure.instruction, "") == 0){ // init初始化地图和用户
            After_Walk(use_players, &map, cell, routeNum,roll_dice());
            flag_ifover = 1;
        }else
        if(strcmp(RichStructure.instruction, "Help") == 0) {
            Print_Help();
        }else{
            Tool_Use(use_players, &map, routeNum,RichStructure.parameter);
        }
    }
    return flag_ifquit;
}


void Route_Event(Map &map,Player* use_players,int routeNum,char* now_user) {
    static int richMan_route = 0;
    static int global_route = 0;
    static int richMan_pos = 0;
    static int richMan_flag = 0;
    if (routeNum == 0){
        ++richMan_route;
        ++global_route;
    }
    Print_PlayerTurn(use_players, routeNum, now_user,global_route);

    if (richMan_route == 10){
        srand(static_cast<unsigned>(std::time(nullptr))); // Seed the random number generator
        int if_create = rand() % 3; // Generate a random number between 0 and 1,2
        if (!if_create && richMan_flag == 0){
            while (true){
                srand(static_cast<unsigned>(std::time(nullptr))); // Seed the random number generator
                richMan_pos = rand() % 70; // Generate a random number between 0 and 69
                if (map.data[richMan_pos].passer_num == 0 &&
                    map.data[richMan_pos].kind != TOOLSHOP &&
                    map.data[richMan_pos].kind != GIFTSHOP &&
                    map.data[richMan_pos].has_tool == 0)
                {
                    printf(LIGHT_CYAN);
                    printf("财神在 %d . 加油!\n",richMan_pos);
                    printf(COLOR_NULL);
                    map.ToolCreat(richMan_pos,3);
                    richMan_flag = 1;
                    break;
                }
            }
        }else{
            if (!richMan_flag){
                richMan_route = 9;
            }
        }
    }else if (richMan_route == 15){
        richMan_route = 0;
        richMan_flag = 0;
        map.data[richMan_pos].color = (char*)COLOR_NULL;
        map.data[richMan_pos].has_tool = 0;
        printf(LIGHT_CYAN);
        printf("财神消失\n");
        printf(COLOR_NULL);
    }else if(richMan_flag && map.data[richMan_pos].has_tool == 3){
        printf(LIGHT_CYAN);
        printf("离财神消失还有 %d 轮\n",15-richMan_route);
        printf(COLOR_NULL);
    }else if(map.data[richMan_pos].has_tool != 3 && richMan_flag){
        richMan_route = 0;
        richMan_flag = 0;
    }
}

void Game_Start(char *filename,Player *use_players, Map &map, Cell *cell, jsonMap &jsonmap,char* users, int playerNum, char *now_user) {
    int routeNum = 0;
    int flag_ifquit = 0;
    while(!flag_ifquit) {
        int count = 0;
        int winner = 0;
        int if_continue;

        for (int i = 0; i < 4; ++i) {
            if (use_players[i].alive){
                ++count;
                winner = use_players[i].number;
            }
        }
        if (count == 1){
            char win = 0;
            win = get_player_char((owner_enum)winner);
            if(win == 'Q'){
                printf(COLOR_RED);
                printf("钱夫人");
            } else if(win == 'A'){
                printf(COLOR_GREEN);
                printf("阿土伯");
            } else if(win == 'S'){
                printf(COLOR_BLUE);
                printf("孙小美");
            } else if(win == 'J') {
                printf(COLOR_YELLOW);
                printf("金贝贝");
            }
            printf(LIGHT_CYAN);
            printf("胜利!\n");
            printf(COLOR_NULL);
            break;
        }

//      int route_num = Find_Player_Num(use_players, now_user, playerNum);

        if_continue = Player_Route_Start(use_players, routeNum, &map, cell, playerNum);


        map.SetCell(cell);
        now_user[0] = get_player_char((owner_enum)use_players[routeNum].number);

        if (if_continue) {
            printf(LIGHT_CYAN);
            printf("%s", name_ch);
            printf(" 跳过\n");
            printf(COLOR_NULL);
        } else {
            Route_Event(map,use_players,routeNum,now_user);
            flag_ifquit = Route_Start(use_players, routeNum, now_user, map, cell, filename);
            if (use_players[routeNum]._continue > 0) {
                use_players[routeNum]._continue--;
            }
            if(use_players[routeNum]._continue == 0) {
                use_players[routeNum].buff = false;
            }
            map.SetCell(jsonmap.cells);
            write_json(use_players, jsonmap, users, now_user, filename);
        }
        Print_PlayerOver(use_players,routeNum,now_user);
        map.SetCell(jsonmap.cells);
        write_json(use_players, jsonmap, users, now_user, filename);
        routeNum++;
        if (routeNum == playerNum) {
            routeNum = 0;
        }
//      Route_Num_Change(use_players, now_user, playerNum);
    }
}