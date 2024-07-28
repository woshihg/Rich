#include <iostream>
#include <cstring>
#include "json/json.h"
#include "map/mapdraw.h"
#include "money/money.h"
#include "terminal/terminal.h"
#include "player/player.h"
#include "tool/tool.h"
#include "giftroom/gift.h"

void After_Walk(Player *use_players, Map *map, Cell *cell, int route_num,int relative_move = 0);

int main(int argc, char *argv[])
{
    jsonMap jsonmap;
    char users[10];

    Player use_players[4] = {0};
    Cell cell[70] = {0};

    char filename[256] = {};    // jsonWrite
    char now_user[2] = "Q";
    system("");
    int playerNum = 0;
    if (argc == 1) {
        strcpy(filename, "../user.json");
        read_json(use_players, jsonmap, users, now_user, "../user.json");
        playerNum = (int)strlen(users);
        playerNum = Player_Init(use_players, now_user);
        Set_Init_Money(use_players);
        use_players[0].bomb = 5;
        use_players[0].block = 5;
        use_players[0].robot = 5;
    } else {
        strcpy(filename, argv[1]);
        read_json(use_players, jsonmap, users, now_user, filename);
        playerNum = (int)strlen(users);
    }

    Map map(users,use_players,cell);
    int flag_ifquit = 0;

    while(!flag_ifquit) {
        int flag_ifwalk = 1;
        int flag_ifover = 0;
        int flag_ifshop = 1;
        int flag_ifusetoll =1;
        int route_num = Find_Player_Num(use_players, now_user, playerNum);
        int if_continue = 0;
        if_continue = Player_Route_Start(use_players, now_user, &map, cell, playerNum);
        map.data[use_players[route_num].position].Remove_Passer((owner_enum)use_players[route_num].number);//轮次开始的时候让人显示到上层
        map.data[use_players[route_num].position].Add_Passer((owner_enum)use_players[route_num].number);
        map.SetCell(cell);
        if (if_continue == 1) {
            printf("%s", now_user);
            printf(" skip\n");
            Route_Num_Change(use_players, now_user, playerNum);
            continue;
        } else {
          while (!flag_ifover && !flag_ifquit) {
              //输入命令
              map.PrintMap();
              terminal(use_players[route_num],filename);
              if (strcmp(RichStructure.instruction, "Sell") == 0) {
                  sell_house(&(use_players[route_num]),&map,RichStructure.parameter);
              }else
              if (strcmp(RichStructure.instruction, "Query") == 0) {
                  printf("@ Player : ");
                  printf("%c\n", now_user[0]);
                  printf("\tMoney : ");
                  printf("%d\n", use_players[route_num].money);
                  printf("\tPoint : ");
                  printf("%d\n", use_players[route_num].point);
                  printf("You have %d set(s) of property altogether.Details as follows",use_players[route_num].property_count);
                  //printf("\tProperties details: ");
                  for(int j =0; j<70; j++) {
                      if (use_players[route_num].properties[j]) {
                          printf(" [Position: %d Level: %d]",j,use_players[route_num].properties[j] - 1);
                      }
                  }
                  printf("\n");
                  printf("\tBlock : ");
                  printf("%d\n", use_players[route_num].block);
                  printf("\tBomb : ");
                  printf("%d\n", use_players[route_num].bomb);
                  printf("\tRobot : ");
                  printf("%d\n", use_players[route_num].robot);
                  printf("\tRich Man Power : ");
                  printf("%d %d\n", use_players[route_num].buff, use_players[route_num]._continue);
              }else
              if (strcmp(RichStructure.instruction, "Quit") == 0) {
                  flag_ifquit = 1;
              }else

              if (strcmp(RichStructure.instruction, "Step") == 0) {
                  After_Walk(use_players, &map, cell, route_num,RichStructure.parameter);
                  flag_ifover = 1;
              }else
              if (strcmp(RichStructure.instruction, "Roll") == 0) { // init初始化地图和用户
                  After_Walk(use_players, &map, cell, route_num,roll_dice());
                  flag_ifover = 1;
              }else
              if(strcmp(RichStructure.instruction, "Help") == 0) {
                  printf("\033[3;30;47mYou can use the following commands.\033[m\n");
                  printf(COLOR_PURPLE);
                  printf("Roll: Dice roll command. Walk randomly for 1~6 steps.\n");
                  printf(COLOR_RED);
                  printf("\033[3;30;45mSell n: You can sell your property in location n for twice the total cost of the investment\033[m\n");
                  printf(BROWN);
                  printf("Block n: Place a barricade in relative position n to block the player.\n");
                  printf(LIGHT_CYAN);
                  printf("Bomb n: Place a bomb in relative position n to damage the player\n");
                  printf("Robot: Clear the tools for a certain path ahead\n");
                  printf(LIGHT_GRAY);
                  printf("Query: Display your assets\n");
                  printf("Quit: Exit the game\n");
                  printf(COLOR_NULL);
              }else{
                  Tool_Use(use_players, &map, route_num,RichStructure.parameter);
              }
              if(Is_Arrive_GiftRoom(&use_players[route_num]))
              {
                  Choose_Gift(&use_players[route_num]);
              }
              write_json(use_players, jsonmap, users, now_user, filename);
          }
        }
      Route_Num_Change(use_players, now_user, playerNum);
    }
    return 0;
}

void After_Walk(Player *use_players, Map *map, Cell *cell, int route_num,int relative_move) {
    int skip = 0;
    int real_pos = (use_players[route_num].position + relative_move) % 70;
    if (map->data[real_pos].owner != use_players[route_num].number && map->data[real_pos].owner != OWNER_NULL) {
        printf("You have steped into  someone else's property.Please pay the rent cost.\n");
        pay_rentment(use_players, map,&use_players[route_num],cell, real_pos);
        printf("Now You have %d money left\n",use_players[route_num].money);
        if (use_players[route_num].alive == 0){
            skip = 1;
        }
    }
    int tool_flag =tool_to_hospital(&use_players[route_num], map,
                                    use_players[route_num].position,
                                    use_players[route_num].position + relative_move);
    if(tool_flag == 0 || skip)
    {
        skip =1;
    }
    else
    {
        map->PlayerGoto((owner_enum) use_players[route_num].number,
                        use_players[route_num].position,
                       use_players[route_num].position + tool_flag);
        use_players[route_num].position += tool_flag;
    }
    use_players[route_num].position %= 70;
    if (!skip)
    {
        step_cell_logit(use_players, &use_players[route_num], map, cell);
    }
    map->SetCell(cell);
//  map.PrintMap();
    if(use_players[route_num].position == 49){
        use_players[route_num].prison = true;
        use_players[route_num].de_continue = 2;
        printf("You are in prison!\n");
    }else
    if (use_players[route_num].position == 28) {
        PlayerTool(&(use_players[route_num]));
    }
}
