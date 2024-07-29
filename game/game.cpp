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

void Print_Query(Player *use_players, int routeNum, char *now_user) {
    printf("@ Player : ");
    printf("%c\n", now_user[0]);
    printf("\tMoney : ");
    printf("%d\n", use_players[routeNum].money);
    printf("\tPoint : ");
    printf("%d\n", use_players[routeNum].point);
    printf("You have %d set(s) of property altogether.Details as follows",use_players[routeNum].property_count);
    //printf("\tProperties details: ");
    for(int j =0; j<70; j++) {
        if (use_players[routeNum].properties[j]) {
            printf(" [Position: %d Level: %d]",j,use_players[routeNum].properties[j] - 1);
        }
    }
    printf("\n");
    printf("\tBlock : ");
    printf("%d\n", use_players[routeNum].block);
    printf("\tBomb : ");
    printf("%d\n", use_players[routeNum].bomb);
    printf("\tRobot : ");
    printf("%d\n", use_players[routeNum].robot);
    printf("\tRich Man Power : ");
    printf("%d %d\n", use_players[routeNum].buff, use_players[routeNum]._continue);
}

void Print_Help(){
    printf("\033[3;30;47mYou can use the following commands.\033[m\n");
    printf(COLOR_PURPLE);
    printf("Roll: Dice roll command. Walk randomly for 1~6 steps.\n");
    printf(COLOR_RED);
    printf("\033[3;30;45mSell n: You can sell your property in location n for twice the total cost of the investment\033[m\n");
    printf(BROWN);
    printf("Block n: Place a barricade in relative position n to block the player.\n");
    printf(LIGHT_CYAN);
    printf("Bomb n: Place a bomb in relative position n to damage the player\n");
    printf("Robot: Clear the tools for a certain path ahead\n");
    printf(COLOR_LIGHT_GRAY);
    printf("Query: Display your assets\n");
    printf("Quit: Exit the game\n");
    printf(COLOR_NULL);
}

void Print_PlayerTurn(Player *use_players, int routeNum, char *now_user,int turn_num) {
    switch(use_players[routeNum].number)
    {
        case 1:
            printf("\033[3;30;41m");
            break;
        case 2:
            printf("\033[3;30;42m");
            break;
        case 3:
            printf("\033[3;30;44m");
            break;
        case 4:
            printf("\033[3;30;43m");
            break;
        default:break;
    }
    printf("@ Now is %s turn , it`s turn %d", now_user,turn_num);
    printf(COLOR_NULL);
    printf("\n");
}

void Print_PlayerOver(Player *use_players, int routeNum, char *now_user) {
    switch(use_players[routeNum].number)
    {
        case 1:
            printf("\033[3;30;41m");
            break;
        case 2:
            printf("\033[3;30;42m");
            break;
        case 3:
            printf("\033[3;30;44m");
            break;
        case 4:
            printf("\033[3;30;43m");
            break;
        default:break;
    }
    printf("vvv %s turn is over vvv", now_user);
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
                    printf(COLOR_CYAN);
                    printf("Rich Man Power in %d . Hurry up!\n",richMan_pos);
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
        map.ToolRemove(richMan_pos);
        printf(COLOR_CYAN);
        printf("Rich Man Power fade\n");
        printf(COLOR_NULL);
    }else if(richMan_flag){
        printf(COLOR_CYAN);
        printf("Rich Man Power have %d turn\n",15-richMan_route);
        printf(COLOR_NULL);
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
            printf("Player %c win!\n",win);
            break;
        }

//      int route_num = Find_Player_Num(use_players, now_user, playerNum);

        if_continue = Player_Route_Start(use_players, routeNum, &map, cell, playerNum);


        map.SetCell(cell);
        now_user[0] = get_player_char((owner_enum)use_players[routeNum].number);

        if (if_continue) {
            printf("%s", now_user);
            printf(" skip\n");
        } else {
            Route_Event(map,use_players,routeNum,now_user);
            flag_ifquit = Route_Start(use_players, routeNum, now_user, map, cell, filename);
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