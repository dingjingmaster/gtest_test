#include "test_json_op.h"

enum
{
	OK = 0X00000001,
	ERROR = 0X00000002
};


//	json	初始化
int json_init(sJsonInfo* jsonData, const char* data, unsigned int dataLen)
{
	if((NULL == jsonData || NULL == data || dataLen < 0) && (NULL == jsonData ->dataIn))
	{
		return ERROR;
	}

	if(0 == dataLen)
	{
		dataLen = (unsigned int)strlen(data);
	}

	jsonData ->dataIn = malloc(dataLen + 1);
	memset(jsonData ->dataIn, 0, dataLen + 1);
	strncpy(jsonData ->dataIn, data, dataLen);
	jsonData ->dataInLen = dataLen;
	jsonData ->dataOut = NULL;
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
	ret = package(jsonData, arg);
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
	ret = parse(jsonData, arg);
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
		return OK;
	}

	if(NULL != jsonData ->dataOut)
	{
		free(jsonData ->dataOut);
		jsonData ->dataOutLen = 0;
	}

	if(NULL != jsonData ->dataIn)
	{
		free(jsonData ->dataIn);
		jsonData ->dataInLen = 0;
	}

	return OK;
}



