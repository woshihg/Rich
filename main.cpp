#include <iostream>
#include <cstring>
#include "cJSON.h"
int main(void)
{
    FILE *fp = NULL;
    int i = 0;
    char filename[20] = "data.json";

    cJSON *root = NULL, *temp1 = NULL, *temp2 = NULL, *temp3 = NULL;
    // �����ʵ����͵�cJSON�
    root = cJSON_CreateObject();
    // ����ӵ�ָ���Ķ���
    cJSON_AddItemToObject(root, "admin", temp1 = cJSON_CreateObject());
    cJSON_AddItemToObject(temp1, "username", cJSON_CreateString("admin"));
    cJSON_AddItemToObject(temp1, "password", cJSON_CreateString("123456"));
    cJSON_AddNumberToObject(temp1, "type", 0);
    cJSON_AddItemToObject(temp1, "time", cJSON_CreateString("2020-11-05 12:34:56"));

    char str[3][10] = {"Ikaros", "Nymph", "Astleya"};
    int num[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // �����ʵ����͵�cJSON�
    temp2 = cJSON_CreateArray();
    for (i = 0; i < 3; i++)
    {
        // ����ӵ�ָ���Ķ���
        cJSON_AddItemToArray(temp2, temp3 = cJSON_CreateObject());
        cJSON_AddStringToObject(temp3, "username", str[i]);
        cJSON_AddStringToObject(temp3, "password", "666");
        cJSON_AddNumberToObject(temp3, "type", i);
        cJSON_AddItemToObject(temp3, "other", cJSON_CreateIntArray(num[i], 3));
    }
    cJSON_AddItemToObject(root, "user", temp2);

    char *out = cJSON_Print(root);
    puts(out);

    int len = 0;
    len = strlen(out);
    // ���ļ�
    fp = fopen(filename, "w");
    if(NULL == fp)
    {
        printf("create %s failed\n", filename);
        return 0;
    }
    fwrite(out, len, 1, fp);
    fclose(fp);
    out = NULL;

    // ɾ��һ��cJSONʵ���������ʵ�塣
    cJSON_Delete(root);
}
