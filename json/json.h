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
#include <string>
#include <vector>
#include <algorithm>



// jsonMap's size
# define CELL_NUMS 70

typedef struct Player{
    int number{};            // Player's unique identifier
    bool alive{};            // Indicates if the player is alive
    int money{};             // Player's current amount of money
    int point{};             // Player's current points
    int block{};             // Number of roadblocks the player has
    int bomb{};              // Number of bombs the player has
    int robot{};             // Number of robots the player has
    bool buff{};             // Indicates if the player has an active buff
    int _continue{};         // Number of turns the player have Rich-Man-Power
    bool prison{};           // Indicates if the player is in prison
    bool hospital{};         // Indicates if the player is in the hospital
    int de_continue{};       // the number of turns the player have to stay in prison or hospital
    int position{};          // Player's current position on the game board
    int properties[70]={0};  // Array representing properties owned by the player
    int property_count{};    // Total number of properties the player owns
} Player;

typedef struct Cell{
    char show_char;
    int kind;
    int rank;
    int has_tool;
    //int house_scale; //The scale of house, 0 for empty ground, 1 for hut, 3 for skyscraper
    int sum_invested_money; //The sum of money invested to the cell, convinient for selling the property on the cell
    char owner;     // owner = 'N' , means owner is None
} Cell;

typedef struct jsonMap{
    Cell cells[CELL_NUMS];
} jsonMap;



int findNthSmallestNumPos(const std::string& str, int n);
int jsonWrite(const char *filename);
void read_json(Player use_players[], jsonMap &jsonmap, char users[], char *now_user, const char string[]);
void replaceString(char* str, const char* from, const char* to);
int write_file(const char *filename, const char *data);
char *read_file(const char *filename);
void write_json(Player use_players[], jsonMap &use_map, char users[], char *now_user, const char string[]);


#endif //THE_RICH_JSON_H
