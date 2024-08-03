//
// Created by 张峻领 on 24-7-27.
//

#include "player.h"

//players[4] 玩家结构体数组

int compare_chars(const void* a, const void* b) {
    return *(const char*)a - *(const char*)b;
}
void sort_string(char* str) {
    qsort(str, strlen(str), sizeof(char), compare_chars);
}

int hasDuplicateChars(const std::string& str) {
    std::unordered_set<char> charSet;
    for (char c : str) {
        if (charSet.count(c)) {
            return 1;
        }
        charSet.insert(c);
    }
    return 0;
}


int Player_Init(Player* players, char* now_user, const int money){
    int max_player_num = 0;
    for (int i = 0; i < CELL_MAX_PLAYER; ++i) {
        players[i].number = i;
        players[i].position = 0;
        players[i].money = money;
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
        if (hasDuplicateChars(input_user)) {
            printf(LIGHT_CYAN);
            printf("玩家ID重复\n");
            printf(COLOR_NULL);
            continue;
        }
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
    route_num = get_player_num(now_user[0]);
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

char get_player_char(owner_enum player) {
    char player_name = 'N';
    if(player == OWNER_Q){
        player_name = 'Q';
    } else if(player == OWNER_A){
        player_name = 'A';
    } else if(player == OWNER_S){
        player_name = 'S';
    } else if(player == OWNER_J){
        player_name = 'J';
    }
    return player_name;
}

owner_enum get_player_num(char player_char) {
    owner_enum player_name = OWNER_NULL;
    if(player_char == 'Q'){
        player_name = OWNER_Q;
    } else if(player_char == 'A'){
        player_name = OWNER_A;
    } else if(player_char == 'S'){
        player_name = OWNER_S;
    } else if(player_char == 'J'){
        player_name = OWNER_J;
    }
    return player_name;
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


void After_Walk(Player *use_players, Map *map, Cell *cell, int route_num,int relative_move) {
    int skip = 0;
    int tool_flag =tool_to_hospital(&use_players[route_num], map,
                                    use_players[route_num].position,
                                    use_players[route_num].position + relative_move);
    if(tool_flag ==-1)
    {
        skip =1;
    }
    else
    {
        map->PlayerGoto((owner_enum) use_players[route_num].number,
                        use_players[route_num].position,
                        use_players[route_num].position + tool_flag);
        use_players[route_num].position += tool_flag + 70;
        use_players[route_num].position %= 70;
        map->SetCell(cell);
        map->PrintMap();
    }

    if (!skip)
    {
        if (map->data[use_players[route_num].position].owner != use_players[route_num].number
            && map->data[use_players[route_num].position].owner != OWNER_NULL) {
            printf(LIGHT_CYAN);
            printf("你走到了别人的地产，需要交租金.\n");
            printf(COLOR_NULL);
            pay_rentment(use_players, map,&(use_players[route_num]),cell, use_players[route_num].position);
            if (use_players[route_num].alive == 0){
                skip = 1;
            }else
            {
                printf(LIGHT_CYAN);
                printf("现在你剩下 %d 元\n",use_players[route_num].money);
                printf(COLOR_NULL);
            }
        }
        in_mountain(&use_players[route_num]);
        step_cell_logit(use_players, &use_players[route_num], map, cell);
        if(Is_Arrive_GiftRoom(&use_players[route_num]))
        {
            Choose_Gift(&use_players[route_num]);
        }
    }
    if (false){}
    else
//    if(use_players[route_num].position == 49){
//        use_players[route_num].prison = true;
//        use_players[route_num].de_continue = 2;
//        printf("You are in prison!\n");
//    }else
    if (use_players[route_num].position == 28) {
        PlayerTool(&(use_players[route_num]));
    }
}
