#include <iostream>
#include <cstring>
#include "json/json.h"
#include "map/mapdraw.h"
int main(int argc, char *argv[])
{
    char filename[256] = {};
    strcpy(filename, argc > 1 ? argv[1] : "init.json");
    // init初始化地图和用户
    system("");
    Map map;
    map.PrintMap();
    map.TXTMap(filename);
}
