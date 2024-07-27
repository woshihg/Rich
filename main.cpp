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

    if (argc == 1) {
        strcpy(filename, "../user.json");
    } else {
        strcpy(filename, argv[1]);
    }

    read_json(use_players, jsonmap, users, now_user, filename);
    Map map(users,use_players,cell);
    map.SetCell(cell);
    map.PrintMap();
    int flag_ifquit = 0;

    while(!flag_ifquit) {
        int flag_ifwalk = 1;
        int flag_ifover = 0;
        int flag_ifshop = 1;
        int route_num = Find_Player_Num(use_players, now_user);
        int if_continue = 0;
        if_continue = Player_Route_Start(use_players, now_user, &map, cell);
        if (if_continue == 1) {
            printf("%s", now_user);
            printf(" skip\n");
            Route_Num_Change(use_players, now_user);
            continue;
        } else {
          while (!flag_ifover && !flag_ifquit) {
              //输入命令

              if (!flag_ifover){terminal(use_players[route_num],filename);}


              if (flag_ifover){ break;}
              else
              if (strcmp(RichStructure.instruction, "Sell") == 0) {
                  sell_house(&(use_players[route_num]),cell,RichStructure.parameter);
              }else
              if (strcmp(RichStructure.instruction, "Quit") == 0) {
                  flag_ifquit = 1;
              }else
              if (strcmp(RichStructure.instruction, "Step") == 0) {
                  map.PlayerGoto((owner_enum)use_players[route_num].number, use_players[route_num].position,
                                 use_players[route_num].position + RichStructure.parameter );
                  use_players[route_num].position += RichStructure.parameter;
                  use_players[route_num].position %= 70;

                  step_cell_logit(use_players,&use_players[route_num],&map);
                  map.SetCell(cell);
                  map.PrintMap();

                  if(use_players[route_num].position == 49){
                      use_players[route_num].prison = true;
                      use_players[route_num].de_continue = 2;
                      printf("You are in prison\n");
                  }else
                  if (use_players[route_num].position == 28) {
                      PlayerTool(&(use_players[route_num]),&map);
                  }
                  flag_ifover = 1;
              }else
              if (strcmp(RichStructure.instruction, "Roll") == 0 && flag_ifwalk) { // init初始化地图和用户
                  //投掷骰子
                  walk_roll(use_players, now_user, &map);
                  use_players[route_num].prison = false;
                  flag_ifwalk = 0;

                  step_cell_logit(use_players,&use_players[route_num],&map);
                  map.SetCell(cell);
                  map.PrintMap();

                  if(use_players[route_num].position == 49){
                      use_players[route_num].prison = true;
                      use_players[route_num].de_continue = 2;
                      printf("You are in prison\n");
                  }else
                  if (use_players[route_num].position == 28) {
                      PlayerTool(&(use_players[route_num]),&map);
                  }
                  flag_ifover = 1;
              }else{}
              write_json(use_players, jsonmap, users, now_user, filename);
          }
        }
      Route_Num_Change(use_players, now_user);
    }
    return 0;
}
