//
// Created by 15779 on 24-7-29.
//

#include "game.h"


using namespace std;

char * name_ch=0;

void Print_Query(Player *use_players, int routeNum, char *now_user) {
    printf(LIGHT_CYAN);
    printf("@ ��� : ");
    printf("%s\n",name_ch);
    printf("\t�ʽ� : ");
    printf("%d\n", use_players[routeNum].money);
    printf("\t���� : ");
    printf("%d\n", use_players[routeNum].point);
    printf("\t��һ��ӵ�� %d �׷�����ϸ������\n",use_players[routeNum].property_count);
    //printf("\tProperties details: ");
    for(int j =0; j<70; j++) {
        if (use_players[routeNum].properties[j]) {
            printf(" [λ��: %d �ȼ�: %d]",j,use_players[routeNum].properties[j] - 1);
        }
    }
    printf("\n");
    printf("\t·�� : ");
    printf("%d\n", use_players[routeNum].block);
    printf("\t�������� : ");
    printf("%d\n", use_players[routeNum].robot);
    printf("\t�������漰����ʱ�� : ");
    printf("%d %d\n", use_players[routeNum].buff, use_players[routeNum]._continue);
    printf(COLOR_NULL);
}

void Print_Help(){
    printf(LIGHT_CYAN);
    printf("�����ʹ������ָ�\n");
    printf("Roll: �����ӣ������1~6����\n");
    printf("Sell n: �������������һ��������ķ�����������õĽ�ǮΪ���ڸ÷����������ʽ��������\n");
    printf("Block n: ��ǰ��10�����ڷ���һ��·�ϡ�\n");
    printf("Robot: ���ǰ��10�����ڵ������ϰ���\n");
    printf("Query: ��ʾ����ʲ�\n");
    printf("Quit: ǿ���˳���Ϸ\n");
    printf(COLOR_NULL);
}

void Print_PlayerTurn(Player *use_players, int routeNum, char *now_user,int turn_num) {
    switch(use_players[routeNum].number)
    {
        case 1:
            name_ch="Ǯ����";
            printf(COLOR_RED);
            break;
        case 2:
            name_ch="������";
            printf(COLOR_GREEN);
            break;
        case 3:
            name_ch="��С��";
            printf(COLOR_BLUE);
            break;
        case 4:
            name_ch="�𱴱�";
            printf(COLOR_YELLOW);
            break;
        default:break;
    }
    printf("@ ������ %s �Ļغ�", name_ch);
    printf(COLOR_NULL);
    printf("\n");
}

void Print_PlayerOver(Player *use_players, int routeNum, char *now_user) {
    switch(use_players[routeNum].number)
    {
        case 1:
            name_ch="Ǯ����";
            printf(COLOR_RED);
            break;
        case 2:
            name_ch="������";
            printf(COLOR_GREEN);
            break;
        case 3:
            name_ch="��С��";
            printf(COLOR_BLUE);
            break;
        case 4:
            name_ch="�𱴱�";
            printf(COLOR_YELLOW);
            break;
        default:break;
    }
    printf("@ %s �ĻغϽ�����", name_ch);
    printf(COLOR_NULL);
    printf("\n");
}

int Route_Start(Player *use_players, int routeNum, char *now_user, Map &map, Cell *cell, char *filename, int& dump, const int debug) {
    int flag_ifwalk = 1;
    int flag_ifover = 0;
    int flag_ifshop = 1;
    int flag_ifusetoll = 1;
    int flag_ifquit = 0;
    map.data[use_players[routeNum].position].Remove_Passer((owner_enum) use_players[routeNum].number);//�ִο�ʼ��ʱ��������ʾ���ϲ�
    map.data[use_players[routeNum].position].Add_Passer((owner_enum) use_players[routeNum].number);
    while (!flag_ifover && !flag_ifquit) {
        map.SetCell(cell);
        map.PrintMap();
        //��������
        terminal(use_players[routeNum], filename, debug);

        if (strcmp(RichStructure.instruction, "Sell") == 0) {
            sell_house(&(use_players[routeNum]), &map, RichStructure.parameter);
        } else if (strcmp(RichStructure.instruction, "Query") == 0) {
            Print_Query(use_players, routeNum, now_user);
        } else if (strcmp(RichStructure.instruction, "Quit") == 0) {
            flag_ifquit = 1;
        } else if (strcmp(RichStructure.instruction, "Step") == 0) {
            After_Walk(use_players, &map, cell, routeNum, RichStructure.parameter);
            flag_ifover = 1;
        } else if (strcmp(RichStructure.instruction, "Roll") == 0 ||
                   strcmp(RichStructure.instruction, "") == 0) { // init��ʼ����ͼ���û�
            After_Walk(use_players, &map, cell, routeNum, roll_dice());
            flag_ifover = 1;
        } else if (strcmp(RichStructure.instruction, "Help") == 0) {
            Print_Help();
        } else if (strcmp(RichStructure.instruction, "Dump") == 0) {
            dump = 1;
            printf(LIGHT_CYAN);
            printf("�������ݳɹ�\n");
            printf(COLOR_NULL);
        }
        else {
            Tool_Use(use_players, &map, routeNum, RichStructure.parameter);
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
                    printf("������ %d . ����!\n",richMan_pos);
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
        printf("������ʧ\n");
        printf(COLOR_NULL);
    }else if(richMan_flag && map.data[richMan_pos].has_tool == 3){
        printf(LIGHT_CYAN);
        printf("�������ʧ���� %d ��\n",15-richMan_route);
        printf(COLOR_NULL);
    }else if(map.data[richMan_pos].has_tool != 3 && richMan_flag){
        richMan_route = 0;
        richMan_flag = 0;
    }
}

void Game_Start(char *filename,Player *use_players, Map &map, Cell *cell, jsonMap &jsonmap,char* users, int playerNum, char *now_user, int debug) {
    int routeNum = 0;
    int flag_ifquit = 0;
    while(!flag_ifquit) {
        int count = 0;
        int winner = 0;
        int if_continue;
        int dump_flag = 0;
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
                printf("Ǯ����");
            } else if(win == 'A'){
                printf(COLOR_GREEN);
                printf("������");
            } else if(win == 'S'){
                printf(COLOR_BLUE);
                printf("��С��");
            } else if(win == 'J') {
                printf(COLOR_YELLOW);
                printf("�𱴱�");
            }
            printf(LIGHT_CYAN);
            printf("ʤ��!\n");
            printf(COLOR_NULL);
//            �ȴ��û�����
            char c;
            printf("����q�˳���Ϸ\n");
            while (1) {
                c = getchar();
                if (c == 'q') {
                    flag_ifquit = 1;
                    break;
                }
            }
            break;
        }

//      int route_num = Find_Player_Num(use_players, now_user, playerNum);

        if_continue = Player_Route_Start(use_players, routeNum, &map, cell, playerNum);


        map.SetCell(cell);
        now_user[0] = get_player_char((owner_enum)use_players[routeNum].number);

        if (if_continue) {
            printf(LIGHT_CYAN);
            printf("%s", name_ch);
            printf(" ����\n");
            printf(COLOR_NULL);
        } else {
            Route_Event(map,use_players,routeNum,now_user);
            flag_ifquit = Route_Start(use_players, routeNum, now_user, map, cell, filename, dump_flag, debug);
            if (use_players[routeNum]._continue > 0) {
                use_players[routeNum]._continue--;
            }
            if(use_players[routeNum]._continue == 0) {
                use_players[routeNum].buff = false;
            }
            if (debug) {
                map.SetCell(jsonmap.cells);
                write_json(use_players, jsonmap, users, now_user, filename);
            }
        }
        Print_PlayerOver(use_players,routeNum,now_user);
        if(dump_flag == 1 && debug == 1) {
            map.SetCell(jsonmap.cells);
            write_json(use_players, jsonmap, users, now_user, filename);
        }
        routeNum++;
        if (routeNum == playerNum) {
            routeNum = 0;
        }
//      Route_Num_Change(use_players, now_user, playerNum);
    }
}