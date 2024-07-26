#include <iostream>
#include <cstring>
#include "json/json.h"
int main(int argc, char *argv[])
{
    char filename[256] = {};
    strcpy(filename, argc > 1 ? argv[1] : "init.json");
    jsonWrite(filename);
}
