#include <iostream>
#include <cstring>
#include "json/json.h"
#include "map/mapdraw.h"
#include "money/money.h"
#include "terminal/terminal.h"

int main(int argc, char *argv[])
{
    jsonMap jsonmap;
    char users[10];
    char now_user[2];
    Player use_players[4] = {0};
    use_players[0].alive = true;
    use_players[0].number = 0;
    use_players[0].position = 2;
    Cell cell[70] = {0};
    cell[1].has_tool = 1;//炸弹
    cell[2].has_tool = 2;//路障
    char filename[256] = {};    // jsonWrite

    //设置初始资金
//    Set_Init_Money(use_players);
    while(1)
    {
        //输入命令
        terminal(use_players[0],filename);
        if(strcmp(RichStructure.instruction,"Quit")==0)
        {
            break;
        }
        //Sell指令
        else if(strcmp(RichStructure.instruction,"Sell")==0) {
            Player now_player =  search_by_char(use_players,now_user[0]);
            sell_house(&now_player,jsonmap.cells,RichStructure.parameter);
        }

        //读写json
        read_json(use_players, jsonmap, users, now_user, filename);
        write_json(use_players, jsonmap, users, now_user, filename);

        // init初始化地图和用户
        system("");
        Map map(users,use_players,cell);
        map.SetCell(cell);

        //map.PlayerGoto((owner_enum)use_players[0].number, use_players[0].position, use_players[0].position + RichStructure.parameter);
        map.SetCell(cell);
    }
    return 0;
}
