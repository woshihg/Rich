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
    use_players[0].alive = true;
    use_players[0].number = 1;
    use_players[0].position = 2;
    use_players[1].alive = true;
    use_players[1].number = 2;
    use_players[1].position = 4;
    use_players[2].alive = true;
    use_players[2].number = 3;
    use_players[2].position = 6;
    use_players[3].alive = true;
    use_players[3].number = 4;
    use_players[3].position = 8;
    Cell cell[70] = {0};
    cell[1].has_tool = 1;//炸弹
    cell[2].has_tool = 2;//路障
    use_players[0].properties[13] = 1;
    use_players[0].properties[15] = 3;

    char filename[256] = {};    // jsonWrite
    char now_user[2] = "Q";
    system("");


    int flag_ifwalk = 0;
    int flag_ifover = 0;
    read_json(use_players, jsonmap, users, now_user, "../user.json");
    Map map(users,use_players,cell);
    map.SetCell(cell);
    while(1) {
        flag_ifwalk = 1;
        flag_ifover = 0;
        int route_num = Find_Player_Num(use_players, now_user);
        int if_continue = 0;
        if_continue = Player_Route_Start(use_players, now_user, &map, cell);
        if (if_continue == 1) {
            printf("%s", now_user);
            printf(" skip\n");
            Route_Num_Change(use_players, now_user);
            continue;
        } else {
          while (!flag_ifover) {
              //输入命令
              if (use_players[route_num].position == 28) {
                  PlayerTool(&(use_players[route_num]));
                  flag_ifover = 1;
              }else{
                  terminal(use_players[route_num],filename);
                  if (strcmp(RichStructure.instruction, "Quit") == 0) {
                      flag_ifover = 1;
                  }


                  if (strcmp(RichStructure.instruction, "Step") == 0) {
                      map.PlayerGoto((owner_enum)use_players[route_num].number, use_players[route_num].position,
                                     use_players[route_num].position + RichStructure.parameter );
                      map.SetCell(cell);
                  }
                  // init初始化地图和用户
                  if (strcmp(RichStructure.instruction, "Roll") == 0 && flag_ifwalk) {
                      //投掷骰子
                      walk_roll(use_players, now_user, &map);
                      map.SetCell(cell);
                      flag_ifwalk = 0;
                  }
              }
              write_json(use_players, jsonmap, users, now_user, filename);
          }
          Route_Num_Change(use_players, now_user);
      }
    }
    return 0;
}
