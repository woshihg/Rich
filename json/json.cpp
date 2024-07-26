//
// Created by admin on 2024/7/26.
//

#include "json.h"

void read_json(Player use_players[], jsonMap &jsonmap, char users[], char *now_user,const char string[]) {
    char readname[256] = {};
    strcpy(readname, string);
    if(strcmp(string, "") == 0){
        strcpy(readname, "../Test/test.json");
    }

    char *json_data = read_file(string);
    if (json_data == NULL) {
        printf("Unable to read the JSON file.\n");
        return ;
    }

    cJSON *root = cJSON_Parse(json_data);
    if (root == NULL) {
        printf("Error parsing JSON.\n");
        free(json_data);
        return ;
    }
    cJSON* cjson_map = cJSON_GetObjectItem(root, "MAP");
    cJSON* cjson_tool = cJSON_GetObjectItem(cjson_map, "tool");
    int cjson_tool_size = cJSON_GetArraySize(cjson_tool);
    int* tool_cell = (int*)malloc(cjson_tool_size * sizeof(int));
    int* tool_kind = (int*)malloc(cjson_tool_size * sizeof(int));
    for(int i = 0; i < cjson_tool_size; i++)
    {
        cJSON *item = cJSON_GetArrayItem(cjson_tool, i);
        if (cJSON_GetArraySize(item) == 2) {
            tool_cell[i] = cJSON_GetArrayItem(item, 0)->valueint;
            tool_kind[i] = cJSON_GetArrayItem(item, 1)->valueint;
        }
    }

    for(int i = 0; i < CELL_NUMS; i++)
    {
        jsonmap.cells[i].has_tool = 0;
    }
    for(int i=0;i<cjson_tool_size;i++){
        jsonmap.cells[tool_cell[i]].has_tool = tool_kind[i];
    }

    //MAP读取完毕/////////////////////////////////////////////////////////////
    strcpy(users, cJSON_GetObjectItem(root, "users")->valuestring);
    char test[10];
    strcpy(test, users);
    strcpy(now_user, cJSON_GetObjectItem(root, "now_user")->valuestring);
    //users = cJSON_GetObjectItem(root, "users")->valuestring;
    //now_user = cJSON_GetObjectItem(root, "now_user")->valuestring;

    cJSON *players = cJSON_GetObjectItem(root, "players");
    strcpy(users,test);
    if (players == NULL) {
        printf("No players array found.\n");
        cJSON_Delete(root);
        free(json_data);
        return ;
    }

    int player_count = cJSON_GetArraySize(players);

    for (int i = 0; i < player_count; i++) {
        cJSON *player = cJSON_GetArrayItem(players, i);
        if (player == NULL) continue;
        cJSON *properties = cJSON_GetObjectItem(player, "properties");

        use_players[i].alive = cJSON_GetObjectItem(player, "alive")->valueint;
        use_players[i].money = cJSON_GetObjectItem(player, "money")->valueint;
        use_players[i].point = cJSON_GetObjectItem(player, "point")->valueint;
        use_players[i].number = cJSON_GetObjectItem(player, "number")->valueint;
        use_players[i].block = cJSON_GetObjectItem(player, "tool1")->valueint;
        use_players[i].bomb = cJSON_GetObjectItem(player, "tool2")->valueint;
        use_players[i].robot = cJSON_GetObjectItem(player, "tool3")->valueint;
        use_players[i].buff = cJSON_GetObjectItem(player, "buff")->valueint;
        use_players[i]._continue = cJSON_GetObjectItem(player, "continue")->valueint;
        use_players[i].prison = cJSON_GetObjectItem(player, "debuff0")->valueint;
        use_players[i].hospital = cJSON_GetObjectItem(player, "debuff1")->valueint;
        use_players[i].de_continue = cJSON_GetObjectItem(player, "decontinue")->valueint;
        use_players[i].position = cJSON_GetObjectItem(player, "position")->valueint;

        int prop_count = cJSON_GetArraySize(properties);
        use_players[i].properties = (int**)malloc(prop_count * sizeof(int*));
        use_players[i].property_count = prop_count;
        for (int j = 0; j < prop_count; j++) {
            cJSON *property = cJSON_GetArrayItem(properties, j);
            use_players[i].properties[j] = (int*)malloc(2 * sizeof(int));
            if (cJSON_GetArraySize(property) == 2) {
                use_players[i].properties[j][0] = cJSON_GetArrayItem(property, 0)->valueint;
                use_players[i].properties[j][1] = cJSON_GetArrayItem(property, 1)->valueint;
            }
        }
    }
    //players读取完毕/////////////////////////////////////////////////////////////////
    cJSON_Delete(root);
}



char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char*)malloc(length + 1);

    if (data) {
        fread(data, 1, length, file);
        data[length] = '\0';
    }
    fclose(file);

    return data;
}

//这里实际上都是静态的存储方
void write_json(Player use_players[], jsonMap &use_map, char users[], char *now_user, const char name_string[256]) {
    char resultname[256] = {};
    strcpy(resultname, name_string);

    if(strcmp(name_string, "") == 0){
        strcpy(resultname, "../Test/result.json");
    }else{
        replaceString(resultname, "test", "result");
    }

    cJSON* root = cJSON_CreateObject();
    cJSON* map = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "MAP", map);

    cJSON* tool = cJSON_CreateArray();

    for (int i = 0; i < CELL_NUMS; i++) {
        if (use_map.cells[i].has_tool != 0) {
            cJSON* temp = cJSON_CreateArray();
            cJSON_AddItemToArray(temp, cJSON_CreateNumber(i));
            cJSON_AddItemToArray(temp, cJSON_CreateNumber(use_map.cells[i].has_tool));
            cJSON_AddItemToArray(tool, temp);
        }
    }

    //案例，最后使用for循环进行修改

    cJSON_AddItemToObject(map, "tool", tool);
    cJSON_AddStringToObject(root, "users", users);
    cJSON_AddStringToObject(root, "now_user", now_user);
    cJSON* players = cJSON_CreateArray();
    cJSON *temp_player = NULL;
    char *string = NULL;
    if (players != NULL) {
        cJSON_AddItemToObject(root, "players", players);

        for (int index = 0; index < strlen(users); ++index) {
            temp_player = cJSON_CreateObject();
            if (temp_player == NULL) {
                goto end;
            }
            cJSON_AddItemToArray(players, temp_player);
            cJSON_AddItemToObject(temp_player, "alive", cJSON_CreateNumber(use_players[index].alive));
            cJSON_AddItemToObject(temp_player, "money", cJSON_CreateNumber(use_players[index].money));
            cJSON_AddItemToObject(temp_player, "point", cJSON_CreateNumber(use_players[index].point));
            cJSON_AddItemToObject(temp_player, "number", cJSON_CreateNumber(use_players[index].number));
            cJSON_AddItemToObject(temp_player, "tool1", cJSON_CreateNumber(use_players[index].block));
            cJSON_AddItemToObject(temp_player, "tool2", cJSON_CreateNumber(use_players[index].bomb));
            cJSON_AddItemToObject(temp_player, "tool3", cJSON_CreateNumber(use_players[index].robot));
            cJSON_AddItemToObject(temp_player, "buff", cJSON_CreateNumber(use_players[index].buff));
            cJSON_AddItemToObject(temp_player, "continue", cJSON_CreateNumber(use_players[index]._continue));
            cJSON_AddItemToObject(temp_player, "debuff0", cJSON_CreateNumber(use_players[index].prison));
            cJSON_AddItemToObject(temp_player, "debuff1", cJSON_CreateNumber(use_players[index].hospital));
            cJSON_AddItemToObject(temp_player, "decontinue", cJSON_CreateNumber(use_players[index].de_continue));
            cJSON_AddItemToObject(temp_player, "position", cJSON_CreateNumber(use_players[index].position));
            cJSON *properties = cJSON_CreateArray();
            if (properties == NULL) {
                goto end;
            }
            cJSON_AddItemToObject(temp_player, "properties", properties);
            cJSON_AddItemToObject(temp_player, "property_count", cJSON_CreateNumber(use_players[index].property_count));
            //案例，最后使用for循环进行修改
            for (int i = 0; i < use_players[index].property_count; i++) {
                cJSON *temp = cJSON_CreateArray();
                cJSON_AddItemToArray(temp, cJSON_CreateNumber(use_players[index].properties[i][0]));
                cJSON_AddItemToArray(temp, cJSON_CreateNumber(use_players[index].properties[i][1]));
                cJSON_AddItemToArray(properties, temp);
            }
        }
        string = cJSON_Print(root);
        if (string == NULL) {
            fprintf(stderr, "Failed to print monitor.\n");
        }
    }
    end:
    cJSON_Delete(root);
    //return string;
    write_file("data1.json", string);
}

int write_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0; // 返回0表示打开文件失败

    size_t length = strlen(data);
    size_t written = fwrite(data, 1, length, file);
    fclose(file);

    // 如果实际写入的字节数与数据长度相等，则返回1，否则返回0表示写入失败
    return written == length;
}

void replaceString(char* str, const char* from, const char* to) {
    int fromLen = strlen(from);
    int toLen = strlen(to);

    char* pos = str;
    while ((pos = strstr(pos, from)) != nullptr) {
        memmove(pos + toLen, pos + fromLen, strlen(pos + fromLen) + 1);
        memcpy(pos, to, toLen);
        pos += toLen;
    }
}



//int jsonWrite(const char *filename)
//{
//    FILE *fp = NULL;
//    int i = 0;
//    char resultname[256] = {};
//    strcpy(resultname, filename);
//    replaceString(resultname, "test", "result");
//    cJSON *root = NULL, *temp1 = NULL, *temp2 = NULL, *temp3 = NULL;
//    // 创建适当类型的cJSON项。
//    root = cJSON_CreateObject();
//    // 将项附加到指定的对象。
//    cJSON_AddItemToObject(root, "map", temp1 = cJSON_CreateObject());
//    cJSON_AddItemToObject(temp1, "username", cJSON_CreateString("admin"));
//    cJSON_AddItemToObject(temp1, "password", cJSON_CreateString("123456"));
//    cJSON_AddNumberToObject(temp1, "type", 0);
//    cJSON_AddItemToObject(temp1, "time", cJSON_CreateString("2020-11-05 12:34:56"));
//
//    char str[3][10] = {"Ikaros", "Nymph", "Astleya"};
//    int num[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//    // 创建适当类型的cJSON项。
//    temp2 = cJSON_CreateArray();
//    for (i = 0; i < 3; i++)
//    {
//        // 将项附加到指定的对象。
//        cJSON_AddItemToArray(temp2, temp3 = cJSON_CreateObject());
//        cJSON_AddStringToObject(temp3, "username", str[i]);
//        cJSON_AddStringToObject(temp3, "password", "666");
//        cJSON_AddNumberToObject(temp3, "type", i);
//        cJSON_AddItemToObject(temp3, "other", cJSON_CreateIntArray(num[i], 3));
//    }
//    cJSON_AddItemToObject(root, "user", temp2);
//
//    char *out = cJSON_Print(root);
//    puts(out);
//
//    int len = 0;
//    len = strlen(out);
//    // 打开文件
//    fp = fopen(filename, "w");
//    if(NULL == fp)
//    {
//        printf("create %s failed\n", filename);
//        return 0;
//    }
//    fwrite(out, len, 1, fp);
//    fclose(fp);
//    out = NULL;
//
//    // 删除一个cJSON实体和所有子实体。
//    cJSON_Delete(root);
//    return 1;
//}
