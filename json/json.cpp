//
// Created by admin on 2024/7/26.
//

#include <filesystem>
#include "json.h"

void read_json(Player use_players[], jsonMap &jsonmap, char users[], char *now_user,const char string[]) {
    char readname[256] = {};
    strcpy(readname, string);
    if(strcmp(string, "") == 0){
        strcpy(readname, "../Test/test0/user.json");
    }
    char *json_data = read_file(readname);
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

    //MAP��ȡ���/////////////////////////////////////////////////////////////
    strcpy(users, cJSON_GetObjectItem(root, "users")->valuestring);
    char test[10];
    strcpy(test, users);
    strcpy(now_user, cJSON_GetObjectItem(root, "now_user")->valuestring);
    if(strcmp(now_user, "1") == 0) {
        strcpy(now_user, "Q");
    }else if(strcmp(now_user, "2") == 0) {
        strcpy(now_user, "A");
    }else if(strcmp(now_user, "3") == 0) {
        strcpy(now_user, "S");
    }else if(strcmp(now_user, "4") == 0) {
        strcpy(now_user, "J");
    }
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
//        use_players[i].properties = (int**)malloc(prop_count * sizeof(int*));
        use_players[i].property_count = prop_count;
        for (int j = 0; j < prop_count; j++) {
            cJSON *property = cJSON_GetArrayItem(properties, j);
//            use_players[i].properties[j] = (int*)malloc(2 * sizeof(int));
            if (cJSON_GetArraySize(property) == 2) {
//                use_players[i].properties[j][0] = cJSON_GetArrayItem(property, 0)->valueint;
//                use_players[i].properties[j][1] = cJSON_GetArrayItem(property, 1)->valueint;
                int a = cJSON_GetArrayItem(property, 0)->valueint;
                int b = cJSON_GetArrayItem(property, 1)->valueint;
                use_players[i].properties[a] = b + 1;
                if(use_players[i].number== 1) {
                    jsonmap.cells[a].owner = 'Q';
                }else if(use_players[i].number== 2) {
                    jsonmap.cells[a].owner = 'A';
                }else if(use_players[i].number== 3) {
                    jsonmap.cells[a].owner = 'S';
                }else if(use_players[i].number== 4) {
                    jsonmap.cells[a].owner = 'J';
                }
            }
        }
    }
    //players��ȡ���/////////////////////////////////////////////////////////////////
    cJSON_Delete(root);
}

int findNthSmallestNumPos(const std::string& str, int n) {
    std::vector<std::pair<int, int>> nums; // pair of number and its position

    // Extract numbers and their positions
    for (int i = 0; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            nums.push_back({str[i] - '0', i});
        }
    }

    // Sort in ascending order
    std::sort(nums.begin(), nums.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first < b.first;
    });

    // Check if n is valid
    if (n > 0 && n <= nums.size()) {
        return nums[n - 1].second;
    } else {
        return -1; // Invalid n
    }
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

//����ʵ���϶��Ǿ�̬�Ĵ洢��
void write_json(Player use_players[], jsonMap &use_map, char users[], char *now_user, const char name_string[256]) {
    char resultname[256] = {};
    strcpy(resultname, name_string);

    if(strcmp(name_string, "") == 0){
        strcpy(resultname, "result.json");
    }else{
        replaceString(resultname, "user", "result");
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

    //���������ʹ��forѭ�������޸�

    cJSON_AddItemToObject(map, "tool", tool);
    cJSON_AddStringToObject(root, "users", users);

    if(strcmp(now_user, "Q") == 0) {
        cJSON_AddStringToObject(root, "now_user", "1");
    }else if(strcmp(now_user, "A") == 0) {
        cJSON_AddStringToObject(root, "now_user", "2");
    }else if(strcmp(now_user, "S") == 0) {
        cJSON_AddStringToObject(root, "now_user", "3");
    }else if(strcmp(now_user, "J") == 0) {
        cJSON_AddStringToObject(root, "now_user", "4");
    }
    cJSON* players = cJSON_CreateArray();
    cJSON *temp_player = nullptr;
    char *string = nullptr;
    if (players != nullptr) {
        cJSON_AddItemToObject(root, "players", players);

        for (int j = 0; j < strlen(users); ++j) {
            temp_player = cJSON_CreateObject();
            if (temp_player == nullptr) {
                goto end;
            }
            int index = findNthSmallestNumPos(users, j + 1);
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
            if (properties == nullptr) {
                goto end;
            }
            cJSON_AddItemToObject(temp_player, "properties", properties);
            //���������ʹ��forѭ�������޸�
            for(int i=0;i<70;i++){
                if(use_players[index].properties[i]!=0){
                    cJSON* temp = cJSON_CreateArray();
                    cJSON_AddItemToArray(temp, cJSON_CreateNumber(i));
                    cJSON_AddItemToArray(temp, cJSON_CreateNumber(use_players[index].properties[i]-1));
                    cJSON_AddItemToArray(properties, temp);
                }
            }
        }

        string = cJSON_Print(root);
        if (string == nullptr) {
            fprintf(stderr, "Failed to print monitor.\n");
        }
    }
    end:
    cJSON_Delete(root);
    //return string;
    write_file(resultname, string);
}

int write_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0; // ����0��ʾ���ļ�ʧ��

    size_t length = strlen(data);
    size_t written = fwrite(data, 1, length, file);
    fclose(file);

    // ���ʵ��д����ֽ��������ݳ�����ȣ��򷵻�1�����򷵻�0��ʾд��ʧ��
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
//    // �����ʵ����͵�cJSON�
//    root = cJSON_CreateObject();
//    // ����ӵ�ָ���Ķ���
//    cJSON_AddItemToObject(root, "map", temp1 = cJSON_CreateObject());
//    cJSON_AddItemToObject(temp1, "username", cJSON_CreateString("admin"));
//    cJSON_AddItemToObject(temp1, "password", cJSON_CreateString("123456"));
//    cJSON_AddNumberToObject(temp1, "type", 0);
//    cJSON_AddItemToObject(temp1, "time", cJSON_CreateString("2020-11-05 12:34:56"));
//
//    char str[3][10] = {"Ikaros", "Nymph", "Astleya"};
//    int num[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
//    // �����ʵ����͵�cJSON�
//    temp2 = cJSON_CreateArray();
//    for (i = 0; i < 3; i++)
//    {
//        // ����ӵ�ָ���Ķ���
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
//    // ���ļ�
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
//    // ɾ��һ��cJSONʵ���������ʵ�塣
//    cJSON_Delete(root);
//    return 1;
//}
