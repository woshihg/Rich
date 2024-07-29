//
// Created by 15779 on 24-7-26.
//

#ifndef RICH_MAN_MAPDRAW_H
#define RICH_MAN_MAPDRAW_H

#include "../json/json.h"
#define COLOR_NULL "\033[0m"
#define COLOR_RED "\033[31m"    //钱夫人
#define COLOR_GREEN "\033[32m"  //阿土伯
#define COLOR_YELLOW "\033[33m" //金贝贝
#define COLOR_BLUE "\033[34m"   //孙小美
#define COLOR_PURPLE "\033[35m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"
#define LIGHT_CYAN   "\033[1;36m"
#define BROWN        "\033[0;33m"
#define Red_background_black_word      "\033[1;30;41m"
#define CELL_MAX_PLAYER 4


typedef enum{
    START, //起点
    SPACE, //空地
    COTTAGE, //茅屋
    HOUSE, //洋房
    SKYSCRAPER, //摩天大楼
    TOOLSHOP, //道具屋 
    GIFTSHOP, //礼品
    MAGICSHOP, //魔法
    HOSPITAL, //医院
    PRISON, //监狱
    MINERAL, //矿地
}kind_enum;

typedef enum{
    RANK_NULL,
    RANK_200,
    RANK_500,
    RANK_300,
}rank_enum;

typedef enum{
    OWNER_NULL, //无主
    OWNER_Q, //钱夫人
    OWNER_A, //阿土伯
    OWNER_S, //孙小美
    OWNER_J, //金贝贝
}owner_enum;



class MapData {
public:
    char base; //展示的字符
    char show{};
    char* color; //颜色
    kind_enum kind;   //地块种类
    rank_enum rank;   //地段
    int has_tool;
    owner_enum owner;  //地主
    int passer_num;  //路过的玩家数量
    owner_enum passers[CELL_MAX_PLAYER]{};  //路过的玩家

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
