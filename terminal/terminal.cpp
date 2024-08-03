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

        //��ʾ����̨
        Show_Terminal(player);

        //��������
        fgets(str, INSTRUCTION_MAX_LEN, stdin);
        sscanf(str, "%s", RichStructure.instruction);

        //�ֱ��������
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
            printf("Ǯ����>");
            break;
        case 2:
            printf(COLOR_GREEN);
            printf("������>");
            break;
        case 3:
            printf(COLOR_BLUE);
            printf("��С��>");
            break;
        case 4:
            printf(COLOR_YELLOW);
            printf("�𱴱�>");
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
        printf("�������\n");
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

    //�ǵ���ģʽ�£�����dumpָ��
    if ((i == INSTRUCTION_NUM && debug == 1) || ((i == INSTRUCTION_NUM - 2 || i == INSTRUCTION_NUM ) && debug != 1))
    {
        INIT_TERMINAL;
        printf(LIGHT_CYAN);
        printf("�������\n");
        printf(COLOR_NULL);
    }
    else
    {
        if(strcmp(RichStructure.instruction,"Roll")==0 && result!=1 )
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Rollָ����󣬲�Ӧ�в���\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Sell")==0 && (RichStructure.parameter<0 || RichStructure.parameter>69))
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Sellָ����󣬲�����ΧΪ0~69\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Block")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Blockָ����󣬲�����ΧΪ-10~10\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Bomb")==0 && (RichStructure.parameter<-10 || RichStructure.parameter>10))
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Bombָ����󣬲�����ΧΪ-10~10\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Robot")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Robotָ����󣬲�Ӧ�в���\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Query")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Queryָ����󣬲�Ӧ�в���\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Help")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Helpָ����󣬲�Ӧ�в���\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Quit")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Quitָ����󣬲�Ӧ�в���\n");
            printf(COLOR_NULL);
        }
        else if(strcmp(RichStructure.instruction,"Dump")==0 && result!=1)
        {
            INIT_TERMINAL;
            printf(LIGHT_CYAN);
            printf("Dumpָ����󣬲�Ӧ�в���\n");
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