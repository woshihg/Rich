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
    printf("��ӭ���������ݣ���ѡ������Ҫ�ĵ���:\n");
    printf("1. ·��: 50 ��\n");
    printf("2. ��������: 30 ��\n");
//    printf("3. Bomb 50 points\n");
    printf("������ӵ�еĵ���: %d ��\n",player->point);
    printf("ÿ��������ӵ��10������, ������ӵ��:\n");
    //printf("Bombs: %d\n",player->bomb_count);
    printf("·��: %d\n",player->block);
    printf("��������: %d\n",player->robot);
//    printf("bombs: %d\n",player->bomb);
    printf("����: %d\n",player->block+player->robot+player->bomb);//player->bomb_count+player->barrier_count+player->robot_count);
    printf(COLOR_NULL);
    if (player->point < 30){
        printf(LIGHT_CYAN);
        printf("��ĵ������㣬�Զ��˳������ݣ�\n");
        printf(COLOR_NULL);
        return;
    }else if(player->block+player->robot+player->bomb >= 10){
        printf(LIGHT_CYAN);
        printf("��ĵ��ߴﵽ���ޣ��Զ��˳�������\n");
        printf(COLOR_NULL);
        return;
    }

    printf(LIGHT_CYAN);
    printf("������������ĵ���ID������F��������:");
    printf(COLOR_NULL);

    while(fgets(input, 100, stdin)) {
        // Split the input string
        token = strtok(input, " ");
        while(token != NULL) {
            // If the input is "F" or "f", exit
            if (token[0] == 'F'  || token[0] == 'f') {
                printf(LIGHT_CYAN);
                printf("���˳��˵�����\n");
                printf(COLOR_NULL);
                return;
            }
            // Try to convert the input string to a number
            tool_id = atoi(token);
            if (tool_id < 1 || tool_id > 2) {
                printf(LIGHT_CYAN);
                printf("����ĵ���ID��������1 �� 2\n");
                printf(COLOR_NULL);
            }
            // Buy the tool
            PlayerBuyTool(player, tool_id);
            // Get the next segmented part
            token = strtok(NULL, " ");
        }
        if (player->point < 30){
            printf(LIGHT_CYAN);
            printf("��ĵ������㣬�Զ��˳������ݣ�\n");
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
        printf("��ĵ��������ﵽ���ޣ����ܼ�������\n");
        printf(COLOR_NULL);
        return;
    }
    if (toolID == 1) {
        if (player->point >= 50) {
            player->point -= 50;
            PlayerGetBlock(player);
            printf(LIGHT_CYAN);
            printf("����·�ϳɹ�!\n");
            printf(COLOR_NULL);
        } else {
            printf(LIGHT_CYAN);
            printf("�������㣬�޷�����·��!\n");
            printf(COLOR_NULL);
        }
    } else if (toolID == 2) {
        if (player->point >= 30) {
            player->point -= 30;
            PlayerGetRobot(player);
            printf(LIGHT_CYAN);
            printf("�ɹ������������!\n");
            printf(COLOR_NULL);
        } else {
            printf(LIGHT_CYAN);
            printf("�������㣬�޷������������!\n");
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
//        //�ָ��ַ��� block n ;bomb n;robot
//        terminal(*player,filename);
//        printf("%s\n",RichStructure.instruction);
//        printf("%d\n", RichStructure.parameter);
//
//    }
//}
//��������
void robot_use(int pos,Map* map) {
    //����·��
    for(int i=0;i<11;i++) {
        map->ToolRemove((pos+i)%70);
    }
}
/*
 parameter:
    map ��ͼָ��
    player �û��ṹ��ָ��
 */
int tool_to_hospital(Player* player,Map* map,int origin_pos,int final_pos){
    //����ԭλ�ú�����λ���ϵĵؿ�ĵ���
    int i;
    for(i=0;i<final_pos-origin_pos+1;i++) {
        //·������
        int real_pos = (origin_pos+i)%70;
        if(map->data[real_pos].has_tool == 1) {
            map->ToolRemove(real_pos);
            printf(LIGHT_CYAN);
            printf("��������·��!\n");
            printf(COLOR_NULL);
            printf("\n");
            return i;
        }else
        if(map->data[real_pos].has_tool == 3){
            map->ToolRemove(real_pos);
            printf(LIGHT_CYAN);
            printf("�������˲���!\n");
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
            printf("������20��\n");
            printf(COLOR_NULL);
            player->point += 20;
            break;
        case 68:
            printf(LIGHT_CYAN);
            printf("������80��\n");
            printf(COLOR_NULL);
            player->point += 80;
            break;
        case 67:
            printf(LIGHT_CYAN);
            printf("������100��\n");
            printf(COLOR_NULL);
            player->point += 100;
            break;
        case 66:
            printf(LIGHT_CYAN);
            printf("������40��\n");
            printf(COLOR_NULL);
            player->point += 40;
            break;
        case 65:
            printf(LIGHT_CYAN);
            printf("������80��\n");
            printf(COLOR_NULL);
            player->point += 80;
            break;
        case 64:
            printf(LIGHT_CYAN);
            printf("������60��\n");
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
            printf("�㲻��������ʹ��·��\n");
            printf(COLOR_NULL);
        }
        else
        if (use_players[route_num].block >= 1) {
            printf(LIGHT_CYAN);
            printf("ʹ��·�ϳɹ�\n");
            printf(LIGHT_CYAN);
            use_players[route_num].block--;
            map->ToolCreat(real_pos, 1);
        }
        else
        {
            printf(LIGHT_CYAN);
            printf("��û���㹻��·��\n");
            printf(COLOR_NULL);
        }
    } else if (strcmp(RichStructure.instruction, "Robot") == 0) {
        if (use_players[route_num].robot >= 1) {
            printf(LIGHT_CYAN);
            printf("ʹ�û������޳ɹ�\n");
            printf(COLOR_NULL);
            use_players[route_num].robot--;
            robot_use(use_players[route_num].position, map);
        } else {
            printf(LIGHT_CYAN);
            printf("��û���㹻�Ļ�������\n");
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