//
// Created by Zhang Junling on 24-7-27.
//
//
// Created by Zhang Junling on 24-7-27.
//
#include "tool.h"

#include"../map/mapdraw.h"
void PlayerTool(Player* player ) {
    char input[100];
    char* token;
    int tool_id;
    printf(LIGHT_CYAN);
    printf("欢迎来到道具屋，请选择你需要的道具:\n");
    printf("1. 路障: 50 点\n");
    printf("2. 机器娃娃: 30 点\n");
//    printf("3. Bomb 50 points\n");
    printf("你现在拥有的点数: %d 点\n",player->point);
    printf("每个玩家最多拥有10个道具, 你现在拥有:\n");
    //printf("Bombs: %d\n",player->bomb_count);
    printf("路障: %d\n",player->block);
    printf("机器娃娃: %d\n",player->robot);
//    printf("bombs: %d\n",player->bomb);
    printf("总数: %d\n",player->block+player->robot+player->bomb);//player->bomb_count+player->barrier_count+player->robot_count);
    printf(COLOR_NULL);
    if (player->point < 30){
        printf(LIGHT_CYAN);
        printf("你的点数不足，自动退出道具屋！\n");
        printf(COLOR_NULL);
        return;
    }else if(player->block+player->robot+player->bomb >= 10){
        printf(LIGHT_CYAN);
        printf("你的道具达到上限，自动退出道具屋\n");
        printf(COLOR_NULL);
        return;
    }

    printf(LIGHT_CYAN);
    printf("请输入你想买的道具ID，输入F放弃购买:");
    printf(COLOR_NULL);

    while(fgets(input, 100, stdin)) {
        // Split the input string
        token = strtok(input, " ");
        while(token != NULL) {
            // If the input is "F" or "f", exit
            if (token[0] == 'F'  || token[0] == 'f') {
                printf(LIGHT_CYAN);
                printf("你退出了道具屋\n");
                printf(COLOR_NULL);
                return;
            }
            // Try to convert the input string to a number
            tool_id = atoi(token);
            if (tool_id < 1 || tool_id > 2) {
                printf(LIGHT_CYAN);
                printf("错误的道具ID，请输入1 或 2\n");
                printf(COLOR_NULL);
            }
            // Buy the tool
            PlayerBuyTool(player, tool_id);
            // Get the next segmented part
            token = strtok(NULL, " ");
        }
        if (player->point < 30){
            printf(LIGHT_CYAN);
            printf("你的点数不足，自动退出道具屋！\n");
            printf(COLOR_NULL);
            return;
        }
    }
};
void PlayerBuyTool(struct Player* player, int toolID) {
    // Ensure that the total number of tools the player owns does not exceed 10
    int total_tool_count = player->block + player->robot;//player->bomb_count + player->barrier_count + player->robot_count;
    if (total_tool_count >= 10) {
        printf(LIGHT_CYAN);
        printf("你的道具数量达到上限，不能继续购买\n");
        printf(COLOR_NULL);
        return;
    }
    if (toolID == 1) {
        if (player->point >= 50) {
            player->point -= 50;
            PlayerGetBlock(player);
            printf(LIGHT_CYAN);
            printf("购买路障成功!\n");
            printf(COLOR_NULL);
        } else {
            printf(LIGHT_CYAN);
            printf("点数不足，无法购买路障!\n");
            printf(COLOR_NULL);
        }
    } else if (toolID == 2) {
        if (player->point >= 30) {
            player->point -= 30;
            PlayerGetRobot(player);
            printf(LIGHT_CYAN);
            printf("成功购买机器娃娃!\n");
            printf(COLOR_NULL);
        } else {
            printf(LIGHT_CYAN);
            printf("点数不足，无法购买机器娃娃!\n");
            printf(COLOR_NULL);
        }
    }
//    else
//        if(toolID == 3) {
//        if(player->point >=50) {
//            player->point-=50;
//            PlayerGetBomb(player);
//            printf("Successfully purchased bomb!\n");
//        }else {
//            printf("Not enough points to buy a bomb!\n");
//        }
//    }
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
//void tool_use(Player* player,Map* map,char *filename) {
//    int use_position;
//    char command[50];
//    int tool_id;
//    char input[100];
//    char *token;
//    while(fgets(input, 100, stdin)) {
//        token = strtok(input, "\n");
//        //分割字符串 block n ;bomb n;robot
//        terminal(*player,filename);
//        printf("%s\n",RichStructure.instruction);
//        printf("%d\n", RichStructure.parameter);
//
//    }
//}
//机器娃娃
void robot_use(int pos,Map* map) {
    //清理路障
    for(int i=0;i<11;i++) {
        map->ToolRemove((pos+i)%70);
    }
}
/*
 parameter:
    map 地图指针
    player 用户结构体指针
 */
int tool_to_hospital(Player* player,Map* map,int origin_pos,int final_pos){
    //遍历原位置和最终位置上的地块的道具
    int i;
    for(i=0;i<final_pos-origin_pos+1;i++) {
        //路障启动
        int real_pos = (origin_pos+i)%70;
        if(map->data[real_pos].has_tool == 1) {
            map->ToolRemove(real_pos);
            printf(LIGHT_CYAN);
            printf("你遇到了路障!\n");
            printf(COLOR_NULL);
            printf("\n");
            return i;
        }else
        if(map->data[real_pos].has_tool == 3){
            map->ToolRemove(real_pos);
            printf(LIGHT_CYAN);
            printf("你遇到了财神!\n");
            printf(COLOR_NULL);
            printf("\n");
            player->buff = true;
            player->_continue = 5;
            map->data[real_pos].has_tool = 0;
            map->data[real_pos].color = (char*)COLOR_NULL;
        }
    }
    if(map->data[final_pos%70].has_tool == 2){
        printf(COLOR_RED);
        printf(">>>  B O M B ! <<<");
        printf(COLOR_NULL);
        printf("\n");
        printf(COLOR_RED);
        printf("you are in hospital!");
        printf(COLOR_NULL);
        printf("\n");
        map->ToolRemove(final_pos%70);
        map->PlayerGoto((owner_enum) player->number, origin_pos, 14);
        player->hospital = true;
        player->de_continue = 3;
        return -1;
    }
    return final_pos-origin_pos;
}
void in_mountain(Player* player) {
    switch(player->position) {
        case 69:
            printf(LIGHT_CYAN);
            printf("你获得了20点\n");
            printf(COLOR_NULL);
            player->point += 20;
            break;
        case 68:
            printf(LIGHT_CYAN);
            printf("你获得了80点\n");
            printf(COLOR_NULL);
            player->point += 80;
            break;
        case 67:
            printf(LIGHT_CYAN);
            printf("你获得了100点\n");
            printf(COLOR_NULL);
            player->point += 100;
            break;
        case 66:
            printf(LIGHT_CYAN);
            printf("你获得了40点\n");
            printf(COLOR_NULL);
            player->point += 40;
            break;
        case 65:
            printf(LIGHT_CYAN);
            printf("你获得了80点\n");
            printf(COLOR_NULL);
            player->point += 80;
            break;
        case 64:
            printf(LIGHT_CYAN);
            printf("你获得了60点\n");
            printf(COLOR_NULL);
            player->point += 60;
            break;
        default:
            break;
    }
}

void Tool_Use(Player* use_players,Map* map,int route_num,int pos) {
    int real_pos = (pos+use_players[route_num].position + 70)%70;

    if (strcmp(RichStructure.instruction, "Block") == 0) {
        if(map->data[real_pos].has_tool != 0 ||
           map->data[real_pos].passer_num != 0 ||
           real_pos == 14 ||
           real_pos == 28 ||
           real_pos == 35 ||
           real_pos == 49 ||
           real_pos == 63
           )
        {
            printf(LIGHT_CYAN);
            printf("你不能在这里使用路障\n");
            printf(COLOR_NULL);
        }
        else
        if (use_players[route_num].block >= 1) {
            printf(LIGHT_CYAN);
            printf("使用路障成功\n");
            printf(LIGHT_CYAN);
            use_players[route_num].block--;
            map->ToolCreat(real_pos, 1);
        }
        else
        {
            printf(LIGHT_CYAN);
            printf("你没有足够的路障\n");
            printf(COLOR_NULL);
        }
    } else if (strcmp(RichStructure.instruction, "Robot") == 0) {
        if (use_players[route_num].robot >= 1) {
            printf(LIGHT_CYAN);
            printf("使用机器娃娃成功\n");
            printf(COLOR_NULL);
            use_players[route_num].robot--;
            robot_use(use_players[route_num].position, map);
        } else {
            printf(LIGHT_CYAN);
            printf("你没有足够的机器娃娃\n");
            printf(COLOR_NULL);
        }
    } else if (strcmp(RichStructure.instruction, "Bomb") == 0) {
        if(map->data[real_pos].has_tool != 0 ||
           map->data[real_pos].passer_num != 0 ||
           real_pos == 14 ||
           real_pos == 28 ||
           real_pos == 35 ||
           real_pos == 49 ||
           real_pos == 63
                )
        {
            printf("you can't use bomb here\n");
        }
        else
        if (use_players[route_num].bomb >= 1) {
            printf("successful use bomb\n");
            use_players[route_num].bomb--;
            map->ToolCreat(real_pos, 2);
        } else {
            printf("you dont have enough bomb\n");
        }
    }
}