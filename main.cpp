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
    strcpy(filename, argc > 1 ? argv[1] : "init.json");

    jsonMap* jsonmap;
    char users[4];
    char now_user[1];
    Player *use_players;
    read_json(use_players, jsonmap, users, now_user);
    write_json(use_players, jsonmap, users, now_user);
    // init初始化地图和用户
    system("");
    Map map;
    map.PrintMap();
    map.TXTMap(filename);

}
