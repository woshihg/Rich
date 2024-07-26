//
// Created by ASUS on 2024/7/26.
//

#ifndef THE_RICH_TERMINAL_H
#define THE_RICH_TERMINAL_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define INSTRUCTION_NUM         9
#define INSTRUCTION_MAX_LEN     100

typedef struct{
    char instruction[INSTRUCTION_MAX_LEN];
    int parameter;
}Rich;

#endif //THE_RICH_TERMINAL_H
