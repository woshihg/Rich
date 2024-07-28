#include <iostream>
#include <cstring>
#include "json/json.h"
#include "map/mapdraw.h"
#include "money/money.h"
#include "terminal/terminal.h"
#include "player/player.h"
#include "tool/tool.h"

int main(int argc, char *argv[])
{
    jsonMap jsonmap;
    char users[10];

    Player use_players[4] = {0};
    Cell cell[70] = {0};

    char filename[256] = {};    // jsonWrite
    char now_user[2] = "Q";
    system("");
    int playerNum = 0;
    if (argc == 1) {
        strcpy(filename, "../user.json");
        read_json(use_players, jsonmap, users, now_user, "../user.json");
        playerNum = (int)strlen(users);
        playerNum = Player_Init(use_players, now_user);
        Set_Init_Money(use_players);
    } else {
        strcpy(filename, argv[1]);
        read_json(use_players, jsonmap, users, now_user, filename);
        playerNum = (int)strlen(users);
    }

    Map map(users,use_players,cell);
    map.SetCell(cell);
    map.PrintMap();
    int flag_ifquit = 0;

    while(!flag_ifquit) {
        int flag_ifwalk = 1;
        int flag_ifover = 0;
        int flag_ifshop = 1;
        int flag_ifusetoll =1;
        int route_num = Find_Player_Num(use_players, now_user, playerNum);
        int if_continue = 0;
        if_continue = Player_Route_Start(use_players, now_user, &map, cell, playerNum);
        map.data[use_players[route_num].position].Remove_Passer((owner_enum)use_players[route_num].number);//轮次开始的时候让人显示到上层
        map.data[use_players[route_num].position].Add_Passer((owner_enum)use_players[route_num].number);
        map.SetCell(cell);
        map.PrintMap();
        if (if_continue == 1) {
            printf("%s", now_user);
            printf(" skip\n");
            Route_Num_Change(use_players, now_user, playerNum);
            continue;
        } else {
          while (!flag_ifover && !flag_ifquit) {
              //输入命令
              if(flag_ifusetoll){
                  tool_use( &use_players[route_num], &map, filename);
                  flag_ifusetoll = 0;
              }
              terminal(use_players[route_num],filename);
              if (strcmp(RichStructure.instruction, "Sell") == 0) {
                  sell_house(&(use_players[route_num]),&map,RichStructure.parameter);
              }else
              if (strcmp(RichStructure.instruction, "Query") == 0) {
                  printf("@ Player : ");
                  printf("%c\n", now_user[0]);
                  printf("\tMoney : ");
                  printf("%d\n", use_players[route_num].money);
                  printf("\tPoint : ");
                  printf("%d\n", use_players[route_num].point);
                  printf("You have %d set(s) of property altogether.Details as follows",use_players[route_num].property_count);
                  //printf("\tProperties details: ");
                  for(int j =0; j<70; j++) {
                      if (use_players[route_num].properties[j]) {
                          printf(" [Position: %d Level: %d]",j,use_players[route_num].properties[j] - 1);
                      }
                  }
                  printf("\n");
                  printf("\tBlock : ");
                  printf("%d\n", use_players[route_num].block);
                  printf("\tBomb : ");
                  printf("%d\n", use_players[route_num].bomb);
                  printf("\tRobot : ");
                  printf("%d\n", use_players[route_num].robot);
                  printf("\tRich Man Power : ");
                  printf("%d %d\n", use_players[route_num].buff, use_players[route_num]._continue);
              }else
              if (strcmp(RichStructure.instruction, "Quit") == 0) {
                  flag_ifquit = 1;
              }else

              if (strcmp(RichStructure.instruction, "Step") == 0) {
                  map.PlayerGoto((owner_enum)use_players[route_num].number, use_players[route_num].position,
                                 use_players[route_num].position + RichStructure.parameter );
                  use_players[route_num].position += RichStructure.parameter;
                  use_players[route_num].position %= 70;

                  step_cell_logit(use_players,&use_players[route_num],&map,cell);
                  map.SetCell(cell);
//                  map.PrintMap();

                  if(use_players[route_num].position == 49){
                      use_players[route_num].prison = true;
                      use_players[route_num].de_continue = 2;
                      printf("You are in prison!\n");
                  }else
                  if (use_players[route_num].position == 28) {
                      PlayerTool(&(use_players[route_num]));
                  }
                  flag_ifover = 1;
              }else
              if (strcmp(RichStructure.instruction, "Roll") == 0 && flag_ifwalk) { // init初始化地图和用户
                  //投掷骰子
                  walk_roll(use_players, now_user, &map, playerNum);
                  use_players[route_num].prison = false;
                  flag_ifwalk = 0;

                  step_cell_logit(use_players,&use_players[route_num],&map,cell);
                  map.SetCell(cell);
//                  map.PrintMap();

                  if(use_players[route_num].position == 49){
                      use_players[route_num].prison = true;
                      use_players[route_num].de_continue = 2;
                      printf("You are in prison!\n");
                  }else
                  if (use_players[route_num].position == 28) {
                      PlayerTool(&(use_players[route_num]));
                  }
                  flag_ifover = 1;
              }else if(strcmp(RichStructure.instruction, "Help") == 0) {
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
                  printf(LIGHT_GRAY);
                  printf("Query: Display your assets\n");
                  printf("Quit: Exit the game\n");
                  printf(COLOR_NULL);
              }
              else{}
              write_json(use_players, jsonmap, users, now_user, filename);
          }
        }
      Route_Num_Change(use_players, now_user, playerNum);
    }
    return 0;
}
