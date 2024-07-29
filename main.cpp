#include <iostream>
#include <cstring>
#include "json/json.h"
#include "map/mapdraw.h"
#include "money/money.h"
#include "player/player.h"
#include "game/game.h"


int main(int argc, char *argv[])
{
    //data init
    jsonMap jsonmap;
    char users[10];
    Player use_players[4] = {0};
    Cell cell[70] = {0};
    char filename[256] = {};    // jsonWrite
    char now_user[2] = "Q";
    system("");
    int playerNum = 0;

    if (argc == 1) {
        playerNum = Player_Init(use_players, now_user);
        Set_Init_Money(use_players);
        for(int i = 0;i<70;i++) {
            jsonmap.cells[i].has_tool = 0;
        }
    } else {
        strcpy(filename, argv[1]);
        read_json(use_players, jsonmap, users, now_user, filename);
        playerNum = (int)strlen(users);
    }
    Map map(users,use_players,cell);//init map
    map.ReadCell(jsonmap.cells);
    Game_Start(filename, use_players, map, cell,jsonmap,users, playerNum, now_user);

    return 0;
}



