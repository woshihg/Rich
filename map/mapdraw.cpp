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
    base = '0';
    color = (char*)COLOR_NULL;
    kind = SPACE;
    rank = RANK_NULL;
    has_tool = 0;
    owner = OWNER_NULL;
    passer_num = 0;
    for (auto & passer : passers) //遍历passers数组
        passer = OWNER_NULL;
}

void MapData::Show_Char() const {
    printf(color);
    cout <<  show ;
    printf(COLOR_NULL);
}
void MapData::Sort_Passers(){
    if(passer_num > 0){
        int startchange = 0;
        for (int i = 0; i < CELL_MAX_PLAYER-1; i++){
            if (passers[i] == OWNER_Q && startchange == 0){
                startchange = 1;
            }
            if (startchange == 1){
                passers[i] = passers[i+1];
            }
        }
    }
}
void MapData::Update_Char(){
    if(passer_num == 0){
        show = base;
        color = (char*)COLOR_NULL;
    }else{
        switch (passers[passer_num-1]) {
            case OWNER_Q:
                show = 'Q';
                color = (char*)COLOR_RED;
                break;
            case OWNER_A:
                show = 'A';
                color = (char*)COLOR_GREEN;
                break;
            case OWNER_S:
                show = 'S';
                color = (char*)COLOR_BLUE;
                break;
            case OWNER_J:
                show = 'J';
                color = (char*)COLOR_YELLOW;
                break;
            default:
                show = base;
                color = (char*)COLOR_NULL;
                break;
        }
    }
}

void MapData::Update_Passer_Num(){
    int count = 0;
    for (auto & passer : passers) {
        if (passer != OWNER_Q){
            ++count;
        }
    }
    passer_num = count;
}

int MapData::Add_Passer(owner_enum passer){
    int error = 0;
    if (passer_num < CELL_MAX_PLAYER){
        passers[passer_num] = passer;
        ++passer_num;
        Update_Char();
    } else{
        error = 1;
    }
    return error;
}
int MapData::Remove_Passer(owner_enum passer){
    int error = 0;
    if (passer_num == 0){
        error = 1;
    }else{
        for (int i = 0; i < CELL_MAX_PLAYER; ++i) {
            if (passers[i] == passer){
                passers[i] = OWNER_NULL;
                --passer_num;
                Sort_Passers();
                Update_Char();
                break;
            }
            if (i == CELL_MAX_PLAYER-1){ //如果没有找到
                error = 2;
            }
        }
    }
    return error;
}
Map::Map(char* players, Player* players_data,Cell* cell){
    for (int i = 0; i<=63 ;i++){
        switch (i) {
            case 0:
                data[i].base = 'S';
                data[i].show = 'S';
                break;
            case 14:
                data[i].base = 'H';
                data[i].show = 'H';
                break;
            case 28:
                data[i].base = 'T';
                data[i].show = 'T';
                break;
            case 35:
                data[i].base = 'G';
                data[i].show = 'G';
                break;
            case 49:
                data[i].base = 'P';
                data[i].show = 'P';
                break;
            case 63:
                data[i].base = 'M';
                data[i].show = 'M';
                break;
            default:
                data[i].base = '0';
                data[i].show = '0';
                break;
        }


    }
    for (int i = 64; i<=69 ;i++){
        data[i].base = '$';
        data[i].show = '$';
    }
//    int count = (int)strlen(players);
    for(int i = 0;i<70;i++) {
        if(cell[i].has_tool)     //地图上显示道具
            Toll_Creat(i,cell[i].has_tool);
        if(cell[i].owner != 'N')
            Bought_Space(i,cell[i].owner,cell[i].rank);
    }
    for (int i =0; i<4; ++i) {
        if (players_data[i].alive) {
            PlayerCreate((owner_enum) players_data[i].number, players_data[i].position);
        }
    }
}

void Map::PlayerCreate(owner_enum player,int to){
    int error = 0;
    error = data[to].Add_Passer(player);
    if (error){
        cout << "Error Create: Too many Passers" << error << endl;
    }
}

void Map::PlayerGoto(owner_enum player,int from,int to){
    int error = 0;
    error = data[from].Remove_Passer(player);
    if (!error){
        error = data[to].Add_Passer(player);
    }else{
        if (error == 1) {
            cout << "Error: Too few Passers" << error << endl;
        } else{
            cout << "Error: Player not in Cell" << error << endl;
        }
    }
    if (error){
        cout << "Error: Too many Passers" << error << endl;
    }
    else {

    }
}

void Map::PrintMap() {
    for (int i = 0; i <= 28; i++) {
        data[i].Show_Char();
    }
    cout << endl;
    for(int i = 5; i >= 0; i--) {
        data[64+i].Show_Char();
        for (int j = 0; j < 27; j++)
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
    if(strcmp(mapname,"") == 0){
        strcpy(mapname, "map.txt");
    }else{
        replaceString(mapname, "test", "map");
        replaceString(mapname, "json", "txt");
    }
    fopen(mapname, "w");
    ofstream outfile(mapname);
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
//地图道具显示与修改
void Map::Toll_Creat(int poistion,int tollkind){
    if(tollkind==1) {
        data[poistion].show = '@';
        data->has_tool = 1;
    }
    else {
        data[poistion].show = '#';
        data->has_tool = 2;
    }
}
//有主地块
void Map::Bought_Space(int poistion,char owner,int rank) {
    data[poistion].base += rank;
    switch (owner) {
        case OWNER_Q:
            data[poistion].color = (char*)COLOR_RED;
        case OWNER_A:
            data[poistion].color = (char*)COLOR_RED;
        case OWNER_S:
            data[poistion].color = (char*)COLOR_RED;
        case OWNER_J:
            data[poistion].color = (char*)COLOR_RED;
    }
}
//