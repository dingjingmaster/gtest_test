#include "test_json_op.h"
#include <stdio.h>
#include <string.h>

typedef struct _SPackage
{
	char	name[54];
	char	sex[8];
	int		age;

}sPackage;

int json_parse_test(sJsonInfo* jsonData)
{
	cJSON*	root = NULL;
	root = cJSON_Parse(jsonData ->dataIn);

	cJSON* name = cJSON_GetObjectItem(root, "姓名:"); 
	cJSON* sex = cJSON_GetObjectItem(root, "性别:"); 
	cJSON* age = cJSON_GetObjectItem(root, "年龄:"); 

	sPackage* buf = (sPackage*)malloc(sizeof(sPackage));

	strcpy(buf ->name, name ->valuestring);
	strcpy(buf ->sex, sex ->valuestring);
	buf ->age = age ->valueint;

	jsonData ->dataOut = buf;
	jsonData ->dataOutLen = sizeof(sPackage);


	return 1;
}

int json_package_test(sJsonInfo* jsonData)
{
	cJSON*	root = NULL;

	sPackage* tmp = (sPackage*)(jsonData ->dataIn);

	root = cJSON_CreateObject();
	
	cJSON* name = cJSON_CreateString(tmp ->name);
	cJSON* sex = cJSON_CreateString(tmp ->sex);
	cJSON* age = cJSON_CreateNumber(tmp ->age);

	cJSON_AddItemToObject(root, "姓名:", name);
	cJSON_AddItemToObject(root, "性别:", sex);
	cJSON_AddItemToObject(root, "年龄:", age);

	char* buf = cJSON_Print(root);

	jsonData ->dataOutLen = strlen(buf) + 1;

	jsonData ->dataOut = malloc(jsonData ->dataOutLen);
	memset(jsonData ->dataOut, 0, jsonData ->dataOutLen);

	strncpy(jsonData ->dataOut, buf, jsonData ->dataOutLen);

	return 1;
}

int main()
{
	sPackage	student;
	sJsonInfo	jsonPack;
	sJsonInfo	jsonParse;

	memset(&student, 0, sizeof(sPackage));
	strncpy(student.name, "张三", 54);
	strncpy(student.sex, "男", 8);
	student.age = 25;

	// json 打包测试
	json_init(&jsonPack);
	
	jsonPack .dataIn = (void*)&student;
	jsonPack .dataInLen = sizeof(student);

	json_package(json_package_test, &jsonPack, NULL);

	// json 打包结果输出
	printf("%s\n", (char*)(jsonPack .dataOut));

	// json 解析
	json_init(&jsonParse);

	jsonParse.dataIn = jsonPack.dataOut;
	jsonParse.dataInLen = jsonPack.dataOutLen;
	
	json_package(json_parse_test, &jsonParse, NULL);


	printf("姓名:%s\n性别:%s\n年龄:%d\n", ((sPackage*)(jsonParse.dataOut)) ->name, ((sPackage*)(jsonParse.dataOut))->sex, ((sPackage*)(jsonParse.dataOut))->age);

	// 释放
	json_free(&jsonPack);
	json_free(&jsonParse);


	return 0;
}
