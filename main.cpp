#include <iostream>
#include <cstring>
#include "json/json.h"
#include "map/mapdraw.h"
#include "money/money.h"
#include "terminal/terminal.h"
#include "player/player.h"
#include "tool/tool.h"
#include "giftroom/gift.h"

void After_Walk(Player *use_players, Map *map, Cell *cell, int route_num,int relative_move = 0);

int main(int argc, char *argv[])
{
    jsonMap jsonmap;
    char users[10];
    char* name_ch = 0;
    Player use_players[4] = {0};
    Cell cell[70] = {0};

    char filename[256] = {};    // jsonWrite
    char now_user[2] = "Q";
    system("");
    int playerNum = 0;
    int routeNum = 0;
    if (argc == 1) {
        strcpy(filename, "../user.json");
        read_json(use_players, jsonmap, users, now_user, "../test/test204/user.json");
        playerNum = (int)strlen(users);
        playerNum = Player_Init(use_players, now_user);
        Set_Init_Money(use_players);
    } else {
        strcpy(filename, argv[1]);
        read_json(use_players, jsonmap, users, now_user, filename);
        playerNum = (int)strlen(users);
    }

    Map map(users,use_players,cell);
    map.ReadCell(jsonmap.cells);
    int flag_ifquit = 0;

    while(!flag_ifquit) {
        int flag_ifwalk = 1;
        int flag_ifover = 0;
        int flag_ifshop = 1;
        int flag_ifusetoll =1;
        int count = 0;
        int winner = 0;

        for (int i = 0; i < 4; ++i) {
            if (use_players[i].alive){
                ++count;
                winner = use_players[i].number;
            }
        }
        if (count == 1){
            char* win = 0;
            if(winner == OWNER_Q){
                win = "钱夫人";
                printf(COLOR_RED);
            } else if(winner == OWNER_A){
                win = "阿土伯";
                printf(COLOR_GREEN);
            } else if(winner == OWNER_S){
                win = "孙小美";
                printf(COLOR_BLUE);
            } else if(winner == OWNER_J) {
                win = "金贝贝";
                printf(COLOR_YELLOW);
            }
            printf("%s",win);
            printf(LIGHT_CYAN);
            printf("胜利!\n");
            printf(COLOR_NULL);
            break;
        }

//        int route_num = Find_Player_Num(use_players, now_user, playerNum);
        int if_continue = 0;
        if_continue = Player_Route_Start(use_players, routeNum, &map, cell, playerNum);
        map.SetCell(cell);
        if (if_continue == 1) {
            printf("%s", name_ch);
            printf(" 跳过\n");
        } else {
            map.data[use_players[routeNum].position].Remove_Passer((owner_enum)use_players[routeNum].number);//轮次开始的时候让人显示到上层
            map.data[use_players[routeNum].position].Add_Passer((owner_enum)use_players[routeNum].number);
            while (!flag_ifover && !flag_ifquit) {
              //输入命令
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
              map.SetCell(cell);
              map.PrintMap();
              terminal(use_players[routeNum],filename);
              if (strcmp(RichStructure.instruction, "Sell") == 0) {
                  sell_house(&(use_players[routeNum]),&map,RichStructure.parameter);
              }else
              if (strcmp(RichStructure.instruction, "Query") == 0) {
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
//                  printf("\tBomb : ");
//                  printf("%d\n", use_players[routeNum].bomb);
                  printf("\t机器娃娃 : ");
                  printf("%d\n", use_players[routeNum].robot);
                  printf("\t正面增益及持续时间 : ");
                  printf("%d %d\n", use_players[routeNum].buff, use_players[routeNum]._continue);
                  printf(COLOR_NULL);
              }else
              if (strcmp(RichStructure.instruction, "Quit") == 0) {
                  flag_ifquit = 1;
              }else

              if (strcmp(RichStructure.instruction, "Step") == 0) {
                  After_Walk(use_players, &map, cell, routeNum,RichStructure.parameter);
                  flag_ifover = 1;
              }else
              if (strcmp(RichStructure.instruction, "Roll") == 0) { // init初始化地图和用户
                  After_Walk(use_players, &map, cell, routeNum,roll_dice());
                  flag_ifover = 1;
              }else
              if(strcmp(RichStructure.instruction, "Help") == 0) {
                  printf(LIGHT_CYAN);
                  printf("你可以使用下列指令。\n");
//                  printf(COLOR_RED);
                  printf("Roll: 掷骰子，随机走1~6步。\n");
                  printf("Sell n: 你可以卖出任意一套属于你的房产，卖出获得的金钱为你在该房产处花费资金的两倍。\n");
//                  printf(BROWN);
                  printf("Block n: 在前后10格以内放置一个路障。\n");
//                  printf("Bomb n: Place a bomb in relative position n to damage the player\n");
                  printf("Robot: 清除前方10格以内的所有障碍。\n");
                  printf("Query: 显示你的资产\n");
                  printf("Quit: 强制退出游戏\n");
                  printf(COLOR_NULL);
              }else{
                  Tool_Use(use_players, &map, routeNum,RichStructure.parameter);
              }
              map.SetCell(jsonmap.cells);
              write_json(use_players, jsonmap, users, now_user, filename);
            }
        }
        map.SetCell(jsonmap.cells);
        write_json(use_players, jsonmap, users, now_user, filename);
        routeNum++;
        if (routeNum == playerNum) {
            routeNum = 0;
        }
        if(use_players[routeNum].number == OWNER_Q){
            now_user[0] = 'Q';
        } else if(use_players[routeNum].number == OWNER_A){
            now_user[0] = 'A';
        } else if(use_players[routeNum].number == OWNER_S){
            now_user[0] = 'S';
        } else if(use_players[routeNum].number == OWNER_J){
            now_user[0] = 'J';
        }
//        Route_Num_Change(use_players, now_user, playerNum);
    }

    system("pause");
    return 0;
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
            printf("你走到了别人的房产处，请付租金。\n");
            printf(COLOR_NULL);
            pay_rentment(use_players, map,&(use_players[route_num]),cell, use_players[route_num].position);
            if (use_players[route_num].alive == 0){
                skip = 1;
            }else
            {
                printf(LIGHT_CYAN);
                printf("现在你还剩下 %d 元\n",use_players[route_num].money);
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

    if(use_players[route_num].position == 49){
        use_players[route_num].prison = true;
        use_players[route_num].de_continue = 2;
        printf("You are in prison!\n");
    }else
    if (use_players[route_num].position == 28) {
        PlayerTool(&(use_players[route_num]));
    }
}
