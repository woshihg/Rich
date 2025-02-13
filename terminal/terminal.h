//
// Created by ASUS on 2024/7/26.
//

#ifndef THE_RICH_TERMINAL_H
#define THE_RICH_TERMINAL_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../json/json.h"
#include "../map/mapdraw.h"

#define INSTRUCTION_NUM         12
#define INSTRUCTION_MAX_LEN     256
#define INIT_TERMINAL           {*flag = 0;parameter_temp = 0;}

typedef struct{
    char instruction[INSTRUCTION_MAX_LEN];
    int parameter;
}Rich;

extern Rich RichStructure;

void terminal(Player player,char *filename,const int debug);
void Show_Terminal(Player player);
void Player_Instruction(int* parameter_temp,char* flag,char* str,const int debug);
void Test_Instruction(char *filename,char* flag,char* str);
void Turn_to_Standard(char* instruction);
#endif //THE_RICH_TERMINAL_H
