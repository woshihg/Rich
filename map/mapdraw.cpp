//
// Created by 15779 on 24-7-26.
//

// mapWrite(filename);
// //test0 --> map0



#include "mapdraw.h"
#include "../json/json.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

MapData::MapData(){
    show = '0';
    color = (char*)COLOR_NULL;
    kind = SPACE;
    rank = RANK_NULL;
    has_tool = 0;
    owner = OWNER_NULL;
    for (auto & passer : passers) //遍历passers数组
        passer = OWNER_NULL;
}

void MapData::Show_Char() const {
    printf(color);
    cout <<  show ;
    printf(COLOR_NULL);
}

Map::Map(){
    for (int i = 0; i<=63 ;i++){
        switch (i) {
            case 0:
                data[i].color = (char*)COLOR_RED;
                data[i].show = 'Q';
                break;
            case 14:
                data[i].show = 'H';
                break;
            case 28:
                data[i].show = 'T';
                break;
            case 35:
                data[i].show = 'G';
                break;
            case 49:
                data[i].show = 'P';
                break;
            case 63:
                data[i].show = 'M';
                break;
            default:
                data[i].show = '0';
                break;
        }
    }
    for (int i = 64; i<=69 ;i++){
        data[i].show = '$';
    }
}


void Map::PrintMap() {
    for (int i = 0; i <= 28; i++) {
        data[i].Show_Char();
    }
    cout << endl;
    for(int i = 5; i >= 0; i--) {
        data[64+i].Show_Char();
        for (int i = 0; i < 27; i++)
        {
            cout << ' ';
        }
        data[34-i].Show_Char();
        cout << endl;
    }
    for (int i = 63; i >= 35; i--) {
        data[i].Show_Char();
    }
    cout << endl;
}

void Map::TXTMap(char* filename) {
    char mapname[256] = {};
    strcpy(mapname, filename);
    replaceString(mapname, "test", "map");
    replaceString(mapname, "json", "txt");
    fopen(mapname, "w");
    ofstream outfile("map.txt");
    if (!outfile.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    for (int i = 0; i <= 28; i++) {
        outfile << data[i].show;
    }
    outfile << endl;

    for(int i = 5; i >= 0; i--) {
        outfile << data[64+i].show;
        for (int j = 0; j < 27; j++) {
            outfile << ' ';
        }
        outfile << data[34-i].show;
        outfile << endl;
    }

    for (int i = 63; i >= 35; i--) {
        outfile << data[i].show;
    }
    outfile << endl;


    outfile.close();
}

//
