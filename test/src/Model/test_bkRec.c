#include "test_bkRec.h"
#include <string.h>

enum
{
	OK = 0x00000001,
	ERROR = 0x00000002

};

typedef struct _sBack301
{
	char**			bkResAuthorRec;
	char**			bkResCartRec;
	char**			bkResGuessRec;

}sBack301;


//	301 解析
int json_parse_301(sJsonInfo* jsonData, void* arg);



//	发送 http 请求	并	解析 http 请求
int	bkRec_sendAndGet(sRequest* request, char** bkResAuthorRec, char** bkResCartRec, char** bkResGuessRec)
{
	if(NULL == request || NULL == bkResAuthorRec || NULL == bkResCartRec || NULL == bkResGuessRec)
	{
		return ERROR;
	}

	int			ret = 0;
	char		uid[32] = {0};
	char		reqGid[32] = {0};
	char		send[2048] = {0};
	sJsonInfo	jsonData;
	sBack301	back301;

	memset(uid, 0, 32);
	memset(reqGid, 0, 32);
	memset(send, 0, 2048);

	sscanf(request ->uKey, "u_%s", uid);
	sscanf(request ->iKey, "i_%s", reqGid);

	snprintf(send, 2048, "/recomm.json?recommType=301&uid=%s&udid=&count=20&charge=%d&reqGid=%s", uid, request ->isCharge, reqGid);

	ret = http_init(&(request ->sockInfo), request ->ip, request ->port);
	ret = http_sendRequest(&(request ->sockInfo), send);
	ret = http_recvData(&(request ->sockInfo));

	//	json 初始化
	ret = json_init(&jsonData, request ->sockInfo.recvBuf, 0);

	//	传出参数	设置
	back301.bkResAuthorRec = bkResAuthorRec;
	back301.bkResCartRec = bkResCartRec;
	back301.bkResGuessRec = bkResGuessRec;

	//	json 解析	301
	ret = json_parse(json_parse_301, &jsonData, (void*)&back301);


	ret = json_free(&jsonData);


	ret = http_free(&(request ->sockInfo));

	return OK;
}


int json_parse_301(sJsonInfo* jsonData, void* arg)
{
	if(NULL == jsonData)
	{
		return ERROR;
	}

	int				i = 0;
	int				keyLen = 0;
	char*			keyBuf = NULL;
	char*			pTmp = NULL;
	cJSON*  		root = NULL;
	cJSON*			author = NULL;
	cJSON*			cate = NULL;
	cJSON*			guess = NULL;
	sBack301*		back301 = NULL;

	//	去掉 http 返回 头部
	pTmp = jsonData ->dataIn;
   	while(*pTmp != '\0')
	{
		if(*pTmp == '\n' && *(pTmp - 2) == '\n' )
		{
			pTmp ++;
			break;
		}
		
		pTmp ++;
	}

	//	开始 json 解析
	root = cJSON_Parse(pTmp);

	//	传出参数
	back301 = (sBack301*)arg;

	//	同作者	推荐解析
	author = cJSON_GetObjectItem(root, "authorRecGids");
	i = 0;
	for(; NULL != author ->child; author ->child = author ->child ->next)
	{
		keyLen = strlen(author ->child ->valuestring) + 1;
		keyBuf = (char*)malloc(keyLen);
		memset(keyBuf, 0, keyLen);
		strncpy(keyBuf, author ->child ->valuestring, keyLen);
		back301 ->bkResAuthorRec[i] = keyBuf;
		++i;
	}

	//	同分类	推荐解析
	cate = cJSON_GetObjectItem(root, "categoryRecGids");
	i = 0;
	for(; NULL != cate ->child; cate ->child = cate ->child ->next)
	{
		keyLen = strlen(cate ->child ->valuestring) + 1;
		keyBuf = (char*)malloc(keyLen);
		memset(keyBuf, 0, keyLen);
		strncpy(keyBuf, cate ->child ->valuestring, keyLen);
		back301 ->bkResCartRec[i] = keyBuf;
		++i;
	}

	//	看了又看	推荐解析
	guess = cJSON_GetObjectItem(root, "guessResGids");
	i = 0;
	for(; NULL != guess ->child; guess ->child = guess ->child ->next)
	{
		keyLen = strlen(guess ->child ->valuestring) + 1;
		keyBuf = (char*)malloc(keyLen);
		memset(keyBuf, 0, keyLen);
		strncpy(keyBuf, guess ->child ->valuestring, keyLen);
		back301 ->bkResGuessRec[i] = keyBuf;
		++i;
	}

	return OK;
}

//	结果对比	完全匹配
int	bkRec_compRes_equal(char** localVal, char** servVal)
{
	int 			i = 0;
	char			keyBuf[32] = {0};


	if(localVal != NULL && servVal != NULL)
	{
		for(i = 0; localVal[i] != NULL; ++i)
		{
			memset(keyBuf, 0, 32);
			snprintf(keyBuf, 32, "i_%s", servVal[i]);
			if(0 != strcmp(localVal[i], keyBuf))
			{
				return ERROR;
			}
		}

		return OK;
	}
	else if(NULL == localVal && NULL == servVal)
	{
		return OK;
	}


	return ERROR;
}


//	是否包含关系
int bkRec_compRes_contain(char** localVal, char** servVal)
{
	int				i = 0;
	int				j = 0;
	char*			keyBuf = NULL;

	keyBuf = (char*)malloc(32);

	if(localVal != NULL && servVal != NULL)
	{
		for(i = 0; servVal[i] != NULL; ++i)
		{
			memset(keyBuf, 0, 32);
			snprintf(keyBuf, 32, "i_%s", servVal[i]);

			//	服务端 数据 分别和比较
			for(j = 0; NULL != localVal[j]; ++j)
			{
				if(0 == strcmp(keyBuf, localVal[j]))
				{
					//	找到 则 正常退出
					break;
				}
				else
				{
					//	没有找到(直到最后一个元素都没有找到) 则 直接返回错误 
					if(NULL == localVal[j + 1])
					{
						return ERROR;
					}
				
				}
			}
		}

		return OK;
	}
	else if(NULL == localVal && NULL == servVal)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}
}











