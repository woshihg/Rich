//
// Created by 15779 on 24-7-26.
//

// mapWrite(filename);
// //test0 --> map0
#include "mapdraw.h"
//#include "../json/json.h"
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

void MapData::Show_Char()  {
    if(!passer_num) {
        if(has_tool == 1) {
            show = '@';
            color = (char*)COLOR_NULL;
        }
        else if (has_tool == 2){
            show = '#';
            color = (char*)COLOR_NULL;
            }
        else if(owner) {
            switch (owner) {
                case OWNER_Q:
                    color = (char*)COLOR_RED;
                break;
                case OWNER_A:
                    color = (char*)COLOR_GREEN;
                break;
                case OWNER_S:
                    color = (char*)COLOR_BLUE;
                break;
                case OWNER_J:
                    color = (char*)COLOR_YELLOW;
                break;
                default:
                    break;
            }
            switch (kind) {
                case COTTAGE:
                    show = '1';
                break;
                case HOUSE:
                    show = '2';
                break;
                case SKYSCRAPER:
                    show = '3';
                break;
                default:
                    break;
            }
        }
    }
    printf("%s", color);
    cout <<  show ;
    printf(COLOR_NULL);
}
void MapData::Sort_Passers(){
    if(passer_num > 0){
        int startchange = 0;
        for (int i = 0; i < CELL_MAX_PLAYER-1; i++){
            if (passers[i] == OWNER_NULL && startchange == 0){
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
Map::Map( char* users,Player* players_data,Cell* cell) {
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
            ToolCreat(i, cell[i].has_tool);
        // else if(cell[i].owner != 'N' && cell[i].owner != 0){
        //     BoughtSpace(i,players_data[i].properties,(kind_enum)cell[i].kind);
        // }
    }
    for (int i =0; i<4; ++i) {
        for(int j =0; j<70; j++) {
            if (players_data[i].properties[j]) {
                BoughtSpace((owner_enum) players_data[i].number,players_data[i].properties,j);
            }
        }

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
    while(to > 69){ //如果to超出地图范围
        to -= 70;
    }
    int error = 0;
    error = data[from].Remove_Passer(player);
    if (!error){
        error = data[to].Add_Passer(player);
    }else{
        if (error == 1) {
            cout << "Error: Too few Passers from " << from << endl;
        } else{
            cout << "Error: Player not in Cell from " << from << endl;
        }
    }
    if (error){
        cout << "Error: Too many Passers to " << to << endl;
    }
    else {

    }
}

void Map::SetCell(Cell* cell){
//    typedef struct Cell{
//        char show_char;
//        int kind;
//        int rank;
//        int has_tool;
//        char owner;     // owner = 'N' , means owner is None
//    } Cell;
    for (int i = 0; i < 70; ++i) {
        cell[i].show_char = data[i].show;
        cell[i].kind = data[i].kind;
        cell[i].rank = data[i].rank;
        cell[i].has_tool = data[i].has_tool;
        switch (data[i].has_tool) {
            case OWNER_NULL:
                cell[i].owner = 'N';
                break;
            case OWNER_Q:
                cell[i].owner = 'Q';
                break;
            case OWNER_A:
                cell[i].owner = 'A';
                break;
            case OWNER_S:
                cell[i].owner = 'S';
                break;
            case OWNER_J:
                cell[i].owner = 'J';
                break;
            default:
                cell[i].owner = 'N';
                break;
        }
    }
//    PrintMap();//test
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
void Map::ToolCreat(int poistion, int tollkind){
    if(tollkind==1) {
        // data[poistion].show = '@';
        data[poistion].has_tool = 1;
    }
    else if(tollkind==2){
        // data[poistion].show = '#';
        data[poistion].has_tool = 2;
    }
}
void Map::ToolRemove(int position) {
    data[position].has_tool = 0;
}
//有主地块
void Map::BoughtSpace(owner_enum player, int properties[],int position) {
    data[position].owner = player;
    switch (properties[position]) {
        case 1:
            data[position].base = COTTAGE;
            data[position].kind = COTTAGE;
        break;
        case 2:
            data[position].base = HOUSE;
            data[position].kind = HOUSE;
        break;
        case 3:
            data[position].base = SKYSCRAPER;
            data[position].kind = SKYSCRAPER;
        break;
        default:
            break;
    }

}

