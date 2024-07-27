//
// Created by admin on 2024/7/26.
//

#ifndef THE_RICH_JSON_H
#define THE_RICH_JSON_H
#include "cJSON.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <cstdio>


// jsonMap's size
# define CELL_NUMS 70

typedef struct Player{
    int number{};
    bool alive{};
    int money{};
    int point{};
    int block{};
    int bomb{};
    int robot{};
    bool buff{};
    int _continue{};
    bool prison{};
    bool hospital{};
    int de_continue{};
    int position{};
    int properties[70]={0};
    int property_count{};
} Player;

typedef struct Cell{
    char show_char;
    int kind;
    int rank;
    int has_tool;
    int house_scale; //The scale of house, 0 for empty ground, 1 for hut, 3 for skyscraper
    int sum_invested_money; //The sum of money invested to the cell, convinient for selling the property on the cell
    char owner;     // owner = 'N' , means owner is None
} Cell;

typedef struct jsonMap{
    Cell cells[CELL_NUMS];
} jsonMap;




int jsonWrite(const char *filename);
void read_json(Player use_players[], jsonMap &jsonmap, char users[], char *now_user, const char string[]);
void replaceString(char* str, const char* from, const char* to);
int write_file(const char *filename, const char *data);
char *read_file(const char *filename);
void write_json(Player use_players[], jsonMap &use_map, char users[], char *now_user, const char string[]);


#endif //THE_RICH_JSON_H
