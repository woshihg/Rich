#include "terminal.h"

char inst_table[INSTRUCTION_NUM][10] = {"Roll", "Sell", "Query", "Help", "Quit","Bomb",
                                            "Block","Robot","Step" ,"Rich","Dump",""};
char test_table[1][10]={"load"};

Rich RichStructure;

void terminal(Player player,char *filename,const int debug){
    char str[INSTRUCTION_MAX_LEN] = {0};
    char flag = 0;
    int parameter_temp = 0;

    while (!flag)
    {
        flag = 1;

        //显示控制台
        Show_Terminal(player);

        //输入命令
        fgets(str, INSTRUCTION_MAX_LEN, stdin);
        sscanf(str, "%s", RichStructure.instruction);

        //分辨测试命令
        if(strcmp(RichStructure.instruction,"load")!=0)
            Player_Instruction(&parameter_temp,&flag,str,debug);
        else
            Test_Instruction(filename,&flag,str);
    }
}

void Show_Terminal(Player player)
{
    switch(player.number)
    {
        case 1:
            printf(COLOR_RED);
            printf("钱夫人>");
            break;
        case 2:
            printf(COLOR_GREEN);
            printf("阿土伯>");
            break;
        case 3:
            printf(COLOR_BLUE);
            printf("孙小美>");
            break;
        case 4:
            printf(COLOR_YELLOW);
            printf("金贝贝>");
            break;
        default:break;
    }
    printf(COLOR_NULL);
}

void Test_Instruction(char *filename,char* flag,char* str)
{
    char result = 0;
    int i = 0;

    result = sscanf(str, "%s %s", RichStructure.instruction, filename);

    if (result != 2 && strcmp(RichStructure.instruction, test_table[0]) == 0)
    {
        *flag=0;
        for (i = 0; i < 256; i++)
        {
            filename[i] = 0;
        }
        printf(LIGHT_CYAN);
        printf("输入错误\n");
        printf(COLOR_NULL);
    }
}

void Player_Instruction(int* parameter_temp,char* flag,char* str,const int debug)
{
    int i=0;
    int result=0;
    result = sscanf(str, "%s %d", RichStructure.instruction, parameter_temp);

    Turn_to_Standard(RichStructure.instruction);

    for (i = 0; i < INSTRUCTION_NUM; i++)
    {
        if (strcmp(RichStructure.instruction, inst_table[i]) == 0)
        {
            RichStructure.parameter = *parameter_temp;
            break;
        }
    }

    //非调试模式下，屏蔽dump指令
    if ((i == INSTRUCTION_NUM && debug == 1) || ((i == INSTRUCTION_NUM - 2 || i == INSTRUCTION_NUM ) && debug != 1))
    {
        INIT_TERMINAL;
        printf(LIGHT_CYAN);
        printf("输入错误\n");
        printf(COLOR_NULL);
    }
    else
    {
        if(strcmp(RichStructure.instruction,"Roll")==0 && result!=1 )
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Roll指令错误，不应有参数\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Sell")==0 && (RichStructure.parameter<0 || RichStructure.parameter>69))
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Sell指令错误，参数范围为0~69\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Block")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Block指令错误，参数范围为-10~10\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Bomb")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Bomb指令错误，参数范围为-10~10\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Robot")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Robot指令错误，不应有参数\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Query")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Query指令错误，不应有参数\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Help")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Help指令错误，不应有参数\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Quit")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Quit指令错误，不应有参数\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Dump")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Dump指令错误，不应有参数\n");
            printf(COLOR_NULL);
        }
    }
}

void Turn_to_Standard(char* instruction)
{
    char i=1;
    if(instruction[0]>=97 && instruction[0]<=122)
    {
        instruction[0]-=32;
    }

    while(instruction[i]!=0)
    {
        if(instruction[i]>=65 && instruction[i]<=90)
        {
            instruction[i]+=32;
        }
        i++;
    }
}