#include "test_json_op.h"

enum
{
	OK = 0X00000001,
	ERROR = 0X00000002
};


//	json	初始化
int json_init(sJsonInfo* jsonData)
{
	if(jsonData == NULL)
	{
		return ERROR;
	}

	jsonData ->dataIn = 0;
	jsonData ->dataInLen = 0;
	jsonData ->dataOut = 0;
	jsonData ->dataOutLen = 0;

	return OK;
}

//	json	打包
int	json_package(json_operation_back package, sJsonInfo* jsonData, void* arg)
{
	if(package == NULL || jsonData == NULL)
	{
		return ERROR;
	}

	int		ret = 0;
	ret = package(jsonData);
	if(ret != OK)
	{
		return ERROR;
	}

	return OK;
}

//	json	解析
int json_parse(json_operation_back parse, sJsonInfo* jsonData, void* arg)
{
	if(parse == NULL)
	{
		return ERROR;
	}

	int		ret = 0;
	ret = parse(jsonData);
	if(ret != OK)
	{
		return ERROR;
	}

	return OK;
}

//	json	释放
int json_free(sJsonInfo* jsonData)
{
	if(jsonData == NULL)
	{
		return ERROR;
	}

	free(jsonData ->dataOut);
	jsonData ->dataOutLen = 0;

	return OK;
}



