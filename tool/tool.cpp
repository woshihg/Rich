//
// Created by Zhang Junling on 24-7-27.
//
//
// Created by Zhang Junling on 24-7-27.
//
#include "tool.h"
#include <cstdio>
#include <cstdlib>
#include "../terminal/terminal.h"
#include"../map/mapdraw.h"
//todo 触发道具屋
void PlayerTool(Player* player ) {
    char input[100];
    char* token;
    int tool_id;
    printf("Welcome to the tool shop, please select the tool you need:\n");
    printf("1. Roadblock 50 points\n");
    printf("2. Robot 30 points\n");
    printf("3. Bomb 50 points\n");
    printf("You currently have points: %d points\n",player->point);
    printf("Each player can have up to 10 tools, you currently have:\n");
    //printf("Bombs: %d\n",player->bomb_count);
    printf("Roadblocks: %d\n",player->block);
    printf("Robots: %d\n",player->robot);
    printf("bombs: %d\n",player->bomb);
    printf("Total: %d\n",player->block+player->robot+player->bomb);//player->bomb_count+player->barrier_count+player->robot_count);
    if (player->point < 30){
        printf("You do not have enough points to buy any tools, automatically exit the tool shop\n");
        return;
    }
    printf("Please enter the tool ID you want to buy, press 'F' to manually exit the tool shop:");
    while(fgets(input, 100, stdin)) {
        // Split the input string
        token = strtok(input, " ");
        while(token != NULL) {
            // If the input is "F" or "f", exit
            if (token[0] == 'F'  || token[0] == 'f') {
                printf("You have exited the tool shop\n");
                return;
            }
            // Try to convert the input string to a number
            tool_id = atoi(token);
            if (tool_id < 1 || tool_id > 3) {
                printf("Invalid tool ID entered! Please enter 1 or 2.\n");
            }
            // Buy the tool
            PlayerBuyTool(player, tool_id);
            // Get the next segmented part
            token = strtok(NULL, " ");
        }
        if (player->point < 30){
            printf("You do not have enough points to buy any tools, automatically exit the tool shop\n");
            return;
        }
    }
};
void PlayerBuyTool(struct Player* player, int toolID) {
    // Ensure that the total number of tools the player owns does not exceed 10
    int total_tool_count = player->block + player->robot;//player->bomb_count + player->barrier_count + player->robot_count;
    if (total_tool_count >= 10) {
        printf("Your tool box is full and you cannot continue to buy\n");
        return;
    }
    if (toolID == 1) {
        if (player->point >= 50) {
            player->point -= 50;
            PlayerGetBlock(player);
            printf("Successfully purchased roadblock!\n");
        } else {
            printf("Not enough points to buy a roadblock!\n");
        }
    } else if (toolID == 2) {
        if (player->point >= 30) {
            player->point -= 30;
            PlayerGetRobot(player);
            printf("Successfully purchased robot!\n");
        } else {
            printf("Not enough points to buy a robot!\n");
        }
    }else if(toolID == 3) {
        if(player->point >=50) {
            player->point-=50;
            PlayerGetBomb(player);
            printf("Successfully purchased bomb!\n");
        }else {
            printf("Not enough points to buy a bomb!\n");
        }
    }
}
void PlayerGetBlock(Player* player) {
    player->block++;
}
void PlayerGetRobot(Player* player) {
    player->robot++;
}
void PlayerGetBomb(Player* player) {
    player->bomb++;
}
void tool_use(Player* player,Map* map,char *filename) {
    int use_position;
    char command[50];
    int tool_id;
    char input[100];
    char *token;
    while(fgets(input, 100, stdin)) {
        token = strtok(input, "\n");
        //分割字符串 block n ;bomb n;robot
        terminal(*player,filename);
        printf("%s\n",RichStructure.instruction);
        printf("%d\n", RichStructure.parameter);
        if(strcmp(RichStructure.instruction,"Block")==0) {
            if(player->block >= 1) {
                use_position = RichStructure.parameter;
                printf("successful use block\n");
                player->block--;
                //todo 将路障放到地图上
                map->ToolCreat(use_position, 1);
                return;
            }
            else {
                printf("you dont have enough tool\n");
                return;
            }
        }
        else if(strcmp(RichStructure.instruction,"Robot")==0) {
            if(player->robot >= 1) {
                printf("successful use robot\n");
                player->robot--;
                //todo 将机器娃娃放到地图上
                robot_use(player,map);
                return;
            }
            else {
                printf("you dont have enough tool\n");
                return;
            }
        }
        else if(strcmp(RichStructure.instruction,"Bomb")==0) {
            if(player->bomb >= 1) {
                use_position = RichStructure.parameter;
                printf("successful use bomb\n");
                player->bomb--;
                //todo 将炸弹放到地图上 调用接口 Toolcraet
                map->ToolCreat(use_position, 2);
                return;
            }
            else {
                printf("you dont have enough tool\n");
                return;
            }
        }
    }
}
//机器娃娃
void robot_use(Player* player,Map* map) {
    //清理路障
    int cur_position;
    for(int i=0;i<10;i++) {
        cur_position = player->position;
        (&(map-> data[cur_position+i]))->has_tool = 0;
    }
}
/*
 parameter:
    map 地图指针
    player 用户结构体指针
 */
//todo 路障拦人 炸弹炸人
int tool_to_hospital(Player* player,Map* map,int origin_pos,int final_pos){
    //遍历原位置和最终位置上的地块的道具
    int i;
    for(i=0;i<final_pos-origin_pos;i++) {
        //路障启动
        if(map->data[origin_pos+i].has_tool == 1) {
            printf("you are in block and stop!\n");
            return i;
        }
            //炸弹启动
        else if(map->data[origin_pos+i].has_tool == 2){
            printf("you are in hospital!\n");
            player->position = 14;
            player->hospital = true;
            player->de_continue = 3;
            return 0;
        }
    }
    return final_pos-origin_pos;
}
void in_mountain(Player* player) {
    switch(player->position) {
        case 69:
            printf("you get 20 points\n");
            player->point += 20;
        case 68:
            printf("you get 80 points\n");
            player->point += 80;
        case 67:
            printf("you get 100 points\n");
            player->point += 100;
        case 66:
            printf("you get 40 points\n");
            player->point += 40;
        case 65:
            printf("you get 80 points\n");
            player->point += 80;
        case 64:
            printf("you get 60 points\n");
            player->point += 60;
    }
}