#include "terminal.h"

char inst_table[INSTRUCTION_NUM][10] = {"Roll", "Sell", "Block", "Bomb", "Robot", "Query", "Help", "Quit", "Step"};
char test_table[1][10]={"load"};

Rich RichStructure;

void terminal(char* now_user)
{
    char str[INSTRUCTION_MAX_LEN] = {0};
    char flag = 0;
    char i = 0;
    char result=0;
    int parameter_temp = 0;

    while (!flag)
    {
        flag = 1;

        Show_Terminal(now_user);

        fgets(str, INSTRUCTION_MAX_LEN, stdin);
        result=sscanf(str, "%s %d", RichStructure.instruction, &parameter_temp);

        for (i = 0; i < INSTRUCTION_NUM; i++)
        {
            if (strcmp(RichStructure.instruction, inst_table[i]) == 0)
            {
                RichStructure.parameter = parameter_temp;
                break;
            }
        }

        if (i == INSTRUCTION_NUM)
        {
            INIT_TERMINAL;
            printf("输入指令错误\n");
        }
        else
        {
            if(strcmp(RichStructure.instruction,"Roll")==0 && result!=1 )
            {
                INIT_TERMINAL;
                printf("Roll参数错误，不应有参数\n");
            }
            else if(strcmp(RichStructure.instruction,"Sell")==0 && (RichStructure.parameter<0 || RichStructure.parameter>69))
            {
                INIT_TERMINAL;
                printf("Sell参数错误，参数范围为0~69\n");
            }
            else if(strcmp(RichStructure.instruction,"Block")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
            {
                INIT_TERMINAL;
                printf("Block参数错误，参数范围为-10~10\n");
            }
            else if(strcmp(RichStructure.instruction,"Bomb")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
            {
                INIT_TERMINAL;
                printf("Bomb参数错误，参数范围为-10~10\n");
            }
            else if(strcmp(RichStructure.instruction,"Robot")==0 && result!=1)
            {
                INIT_TERMINAL;
                printf("Robot参数错误，不应有参数\n");
            }
            else if(strcmp(RichStructure.instruction,"Query")==0 && result!=1)
            {
                INIT_TERMINAL;
                printf("Query参数错误，不应有参数\n");
            }
            else if(strcmp(RichStructure.instruction,"Help")==0 && result!=1)
            {
                INIT_TERMINAL;
                printf("Help参数错误，不应有参数\n");
            }
            else if(strcmp(RichStructure.instruction,"Quit")==0 && result!=1)
            {
                INIT_TERMINAL;
                printf("Quit参数错误，不应有参数\n");
            }
        }

    }
}

void Show_Terminal(char* now_user)
{
    switch(now_user[0])
    {
        case 'Q':
            printf("钱夫人>");
            break;
        case 'A':
            printf("阿土伯>");
            break;
        case 'S':
            printf("孙小美>");
            break;
        case 'J':
            printf("金贝贝>");
            break;
        default:break;
    }
}

void Terminal_Test(char *filename)
{
    char str[256] = {0};
    char flag = 0;
    char result = 0;
    char ins[256] = {0};
    int i = 0;

    while (!flag)
    {
        flag = 1;

        fgets(str, 256, stdin);
        result = sscanf(str, "%s %s", ins, filename);

        if (result != 2 || strcmp(ins, test_table[0]) != 0)
        {
            flag = 0;
            for (i = 0; i < 256; i++)
            {
                ins[i] = 0;
                filename[i] = 0;
            }
            printf("输入指令错误\n");
        }
    }
}
