//
// Created by admin on 2024/7/26.
//

#ifndef THE_RICH_JSON_H
#define THE_RICH_JSON_H
#include "cJSON.h"
#include <cstring>
#include <cstdio>
int jsonWrite(const char *filename);
void replaceString(char* str, const char* from, const char* to);
#endif //THE_RICH_JSON_H
