#include "terminal.h"

char inst_table[INSTRUCTION_NUM][10] = {"Roll", "Sell", "Block", "Bomb", "Robot", "Query", "Help", "Quit", "Step"};

Rich RichSrtucture;

void terminal()
{
    char str[INSTRUCTION_MAX_LEN] = {0};
    char flag = 0;
    char i = 0;
    int parameter_temp = 0;

    while (!flag)
    {
        flag = 1;

        fgets(str, INSTRUCTION_MAX_LEN, stdin);
        sscanf(str, "%s %d", RichSrtucture.instruction, &parameter_temp);

        for (i = 0; i < INSTRUCTION_NUM; i++)
        {
            if (strcmp(RichSrtucture.instruction, inst_table[i]) == 0)
            {
                RichSrtucture.parameter = parameter_temp;
                break;
            }
        }

        if (i == INSTRUCTION_NUM)
        {
            flag = 0;
            parameter_temp = 0;
            printf("输入指令错误\n");
        }
    }
}
