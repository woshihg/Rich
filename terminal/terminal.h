//
// Created by ASUS on 2024/7/26.
//

#ifndef THE_RICH_TERMINAL_H
#define THE_RICH_TERMINAL_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../json/json.h"

#define INSTRUCTION_NUM         9
#define INSTRUCTION_MAX_LEN     100
#define INIT_TERMINAL           {flag = 0;parameter_temp = 0;}

typedef struct{
    char instruction[INSTRUCTION_MAX_LEN];
    int parameter;
}Rich;

extern Rich RichStructure;

void terminal(Player player);
void Show_Terminal(Player player);
void Terminal_Test(char* filename);

#endif //THE_RICH_TERMINAL_H
