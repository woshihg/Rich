#include "terminal.h"

char inst_table[INSTRUCTION_NUM][10] = {"Roll", "Sell", "Tool", "Query", "Help", "Quit",
                                            "Step"};
char test_table[1][10]={"load"};

Rich RichStructure;

void terminal(Player player,char *filename)
{
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
            Player_Instruction(&parameter_temp,&flag,str);
        else
            Test_Instruction(filename,&flag,str);
    }
}

void Show_Terminal(Player player)
{
    switch(player.number)
    {
        case 1:
            printf("Q>");
            break;
        case 2:
            printf("A>");
            break;
        case 3:
            printf("S>");
            break;
        case 4:
            printf("J>");
            break;
        default:break;
    }
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
        printf("Error : input wrong\n");
    }
}

void Player_Instruction(int* parameter_temp,char* flag,char* str)
{
    int i=0;
    int result=0;
    result = sscanf(str, "%s %d", RichStructure.instruction, parameter_temp);
    for (i = 0; i < INSTRUCTION_NUM; i++)
    {
        if (strcmp(RichStructure.instruction, inst_table[i]) == 0)
        {
            RichStructure.parameter = *parameter_temp;
            break;
        }
    }

    if (i == INSTRUCTION_NUM)
    {
        INIT_TERMINAL;
        printf("Error : input wrong\n");
    }
    else
    {
        if(strcmp(RichStructure.instruction,"Roll")==0 && result!=1 )
        {
            INIT_TERMINAL;
            printf("Roll error，should no parameter\n");
        }
        else if(strcmp(RichStructure.instruction,"Sell")==0 && (RichStructure.parameter<0 || RichStructure.parameter>69))
        {
            INIT_TERMINAL;
            printf("Sell error，should be 0~69\n");
        }
        else if(strcmp(RichStructure.instruction,"Block")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
        {
            INIT_TERMINAL;
            printf("Block error，should be -10~10\n");
        }
        else if(strcmp(RichStructure.instruction,"Bomb")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
        {
            INIT_TERMINAL;
            printf("Bomb error，should be -10~10\n");
        }
        else if(strcmp(RichStructure.instruction,"Robot")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf("Robot error，should no parameter\n");
        }
        else if(strcmp(RichStructure.instruction,"Query")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf("Query error，should no parameter\n");
        }
        else if(strcmp(RichStructure.instruction,"Help")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf("Help error，should no parameter\n");
        }
        else if(strcmp(RichStructure.instruction,"Quit")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf("Quit error，should no parameter\n");
        }
    }
}