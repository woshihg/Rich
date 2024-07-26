//
// Created by admin on 2024/7/26.
//
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "init.h"
void game_init()
{
    char input[100];
    int cash = 10000;
    int tempCash;
    char extra;
    int result;

    while (1) {
        printf("请输入初始金额\n");
        if (fgets(input, 100, stdin) == NULL) {
            // 处理输入错误或结束的情况
            printf("输入错误\n");
            continue;
        }

        // 检查是否只是回车（输入长度为1），若是，则使用默认值
        if (input[0] == '\n') {
            break;
        }
        result = sscanf(input, "%d%c", &tempCash, &extra);
        if (result != 2) {
            printf("输入金额\n");
            continue;
        }
        if (tempCash >= 1000 && tempCash <= 50000 && (extra == ' ' || extra == '\n')) {
            int valid = 1;
            // Check for any non-space characters after the number
            for (char *p = input; *p; p++) {
                if (*p != ' ' && (*p < '0' || *p > '9') && *p != '\n') {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                cash = tempCash; // 如果有效输入，则更新cash的值
                break;
            }
        }
        printf("输入金额有误\n");
    }


    printf("初始金额为：%d\n", cash);


}