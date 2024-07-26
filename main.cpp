#include <iostream>
#include <cstring>
#include "json/json.h"
#include "map/mapdraw.h"
#include "init/init.h"

int main(int argc, char *argv[])
{
    // init初始化地图和用户
//     game_init();

    //
    // jsonWrite
    char filename[256] = {};
    strcpy(filename, argc > 1 ? argv[1] : "");

    jsonMap jsonmap;
    char users[10];
    char now_user[2];
    Player use_players[4] = {0};
    use_players[0].alive = true;
    use_players[0].number = 2;
    use_players[0].position = 3;
//    read_json(use_players, jsonmap, users, now_user, filename);
//
//    write_json(use_players, jsonmap, users, now_user, filename);
    // init初始化地图和用户
    system("");
    Map map(users,use_players);
    map.PrintMap();
    map.TXTMap(filename);
    return 0;
}
