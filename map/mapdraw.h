//
// Created by 15779 on 24-7-26.
//

#ifndef RICH_MAN_MAPDRAW_H
#define RICH_MAN_MAPDRAW_H

#define COLOR_NULL "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_PURPLE "\033[35m"

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
    RANK_NULL, //无主
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
    char show; //展示的字符
    char* color; //颜色
    kind_enum kind;   //地块种类
    rank_enum rank;   //地段
    int has_tool; //有争议
    owner_enum owner;  //地主
    owner_enum passers[5]{};  //路过的玩家

    MapData();
//    ~MapData();
    void Show_Char() const;
    void Update_Char();
    void Sort_Passers();
    bool If_Passers();
};

class Map {
private:
    MapData data[70];
public:
    Map();
//    ~Map();
    void PrintMap();
    void TXTMap(char* filename);
};


//typedef struct{
//    char show_char; //展示的字�?
//    int kind;   //地块种类
//    int rank;   //
//    int has_tool;
//    char owner;
//}Cell;

//typedef struct{
//    Cell map[70];
//}Map;


#endif //RICH_MAN_MAPDRAW_H
