//
// Created by 15779 on 24-7-26.
//

#ifndef RICH_MAN_MAPDRAW_H
#define RICH_MAN_MAPDRAW_H

#include "../json/json.h"
#define COLOR_NULL "\033[0m"
#define COLOR_RED "\033[31m"    //Ǯ����
#define COLOR_GREEN "\033[32m"  //������
#define COLOR_YELLOW "\033[33m" //�𱴱�
#define COLOR_BLUE "\033[34m"   //��С��
#define COLOR_PURPLE "\033[35m"
#define COLOR_LIGHT_GRAY  "\033[0;37m"
#define COLOR_CYAN "\033[36m"
#define WHITE        "\033[1;37m"
#define LIGHT_CYAN   "\033[1;36m"
#define BROWN        "\033[0;33m"
#define Red_background_black_word      "\033[1;30;41m"
#define COLOR_SPARK_YELLOW "\033[30;43m"
#define CELL_MAX_PLAYER 4


typedef enum{
    START, //���
    SPACE, //�յ�
    COTTAGE, //é��
    HOUSE, //��
    SKYSCRAPER, //Ħ���¥
    TOOLSHOP, //������ 
    GIFTSHOP, //��Ʒ
    MAGICSHOP, //ħ��
    HOSPITAL, //ҽԺ
    PRISON, //����
    MINERAL, //���
}kind_enum;

typedef enum{
    RANK_NULL,
    RANK_200,
    RANK_500,
    RANK_300,
}rank_enum;

typedef enum{
    OWNER_NULL, //����
    OWNER_Q, //Ǯ����
    OWNER_A, //������
    OWNER_S, //��С��
    OWNER_J, //�𱴱�
}owner_enum;



class MapData {
public:
    char base; //չʾ���ַ�
    char show{};
    char* color; //��ɫ
    kind_enum kind;   //�ؿ�����
    rank_enum rank;   //�ض�
    int has_tool;
    owner_enum owner;  //����
    int passer_num;  //·�����������
    owner_enum passers[CELL_MAX_PLAYER]{};  //·�������

    MapData();
//    ~MapData();

    void Update_Char();
    void Show_Char() ;
    void Sort_Passers();
    int Add_Passer(owner_enum passer);
    int Remove_Passer(owner_enum passer);
};

class Map {
public:
    explicit Map(char* users,Player* players_data, Cell* cell);
//    ~Map();
    void PrintMap();
    void SetCell(Cell* cell);
    void TXTMap(char* filename);
    void PlayerGoto(owner_enum player,int from,int to);
    void PlayerCreate(owner_enum player,int to);
    void ToolCreat(int poistion, int tollkind);
    void ToolRemove(int position);
    void BoughtSpace(owner_enum player, int properties[],int position);
    void RemoveSpace(int position);
    void ReadCell(Cell* cell);
    MapData data[70];
};

#endif //RICH_MAN_MAPDRAW_H
