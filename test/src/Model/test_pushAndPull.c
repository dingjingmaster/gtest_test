#include "test_pushAndPull.h"
#include <string.h>
#include <stdlib.h>

enum
{
	OK = 0x00000001,
	ERROR = 0x00000002
};


//	信息初始化
int	push_redis_init(sRedisInfo* redisInfo, const char* ip, unsigned int port)
{
	if(NULL == redisInfo || NULL == ip)
	{
		return ERROR;
	}

	int		ret = 0;

	ret = redis_init(redisInfo, ip, port);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_conn(redisInfo);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_flushall(redisInfo);
	if(ret != OK)
	{
		return ERROR;
	}


	return OK;
}


//	填充物品信息
int	push_item_info(sRedisInfo* redisInfo, sBookInfo* bookInfo)
{
	if(NULL == redisInfo || NULL == bookInfo)
	{
		return ERROR;
	}

	int			ret = 0;
	char		charTmp[32] = {0};
	
	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "raw_name", bookInfo ->raw_name, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "norm_name", bookInfo ->norm_name, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "top_name", bookInfo ->top_name, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "raw_author", bookInfo ->raw_author, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "norm_author", bookInfo ->norm_author, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "item_icon", bookInfo ->item_icon, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	memset(charTmp, 0, 32);
	snprintf(charTmp, 32, "%d", bookInfo ->item_rank);
	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "item_rank", charTmp, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	memset(charTmp, 0, 32);
	snprintf(charTmp, 32, "%d", bookInfo ->view_count);
	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "view_count", charTmp, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	memset(charTmp, 0, 32);
	snprintf(charTmp, 32, "%d", bookInfo ->mask_level);
	ret = redis_insert_hash(redisInfo, bookInfo ->iKey, "mask_level", charTmp, NULL);
	if(ret != OK)
	{
		return ERROR;
	}



	return OK;
}

//	填充物品协同信息
int push_icf_info(sRedisInfo* redisInfo, sItemRec* itemRec)
{
	if(NULL == redisInfo || NULL == itemRec)
	{
		return ERROR;
	}

	int					ret = 0;
	int					i = 0;
	char				buf[4096] = {0};
	char				temp[40] = {0};
	sKeyAndWeight*		pTmp = NULL;

	//	同作者推荐列表
	pTmp = &(itemRec ->test_method1);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, itemRec ->iKey, "test_method1", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	//	同分类推荐列表
	pTmp = &(itemRec ->test_method2);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, itemRec ->iKey, "test_method2", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	//	付费物品协同推荐列表
	pTmp = &(itemRec ->icf_knn3);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, itemRec ->iKey, "icf_knn3", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	//	免费物品协同推荐列表
	pTmp = &(itemRec ->icf_knn);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, itemRec ->iKey, "icf_knn", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	return OK;
}

//	填充用户协同信息
int	push_ucf_info(sRedisInfo* redisInfo, sCustomRec* customRec)
{
	if(NULL == redisInfo || NULL == customRec)
	{
		return ERROR;
	}

	int					ret = 0;
	int					i = 0;
	char				buf[4096] = {0};
	char				temp[40] = {0};
	sKeyAndWeight*		pTmp = NULL;

	//	书架列表
	pTmp = &(customRec ->cart_item);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, customRec ->uKey, "cart_item", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	//	付费用户协同推荐列表
	pTmp = &(customRec ->ucf_knn3);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, customRec ->uKey, "ucf_knn3", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	//	免费用户协同推荐列表
	pTmp = &(customRec ->ucf_knn);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, customRec ->uKey, "ucf_knn", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}


	return OK;
}


//	填充流行度推荐信息
int	push_pop_info(sRedisInfo* redisInfo, sPopRec* popRec)
{
	if(NULL == redisInfo || NULL == popRec)
	{
		return ERROR;
	}

	int					ret = 0;
	int					i = 0;
	char				buf[4096] = {0};
	char				temp[40] = {0};
	sKeyAndWeight*		pTmp = NULL;

	//	书架列表
	pTmp = &(popRec ->popList);
	memset(buf, 0, 4096);
	for(i = 0; ; ++i)
	{
		if(pTmp ->recommend[i] == NULL)
		{
			break;
		}

		memset(temp, 0, 40);
		snprintf(temp, 40, "%s\t%d\t", pTmp ->recommend[i], pTmp ->weight[i]);
		strncat(buf, temp, 40);
	}

	ret = redis_insert_hash(redisInfo, popRec ->pKey, "pop_topn", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	return OK;
}


//	获取 method1 信息
int pull_method1_info(sRedisInfo* redisInfo, const char* iKey, char** method1)
{
	if(NULL == redisInfo || NULL == iKey || NULL == method1)
	{
		return ERROR;
	}

	int		ret = 0;
	int		i = 0;			//不要改
	int		j = 0;
	int		strLen = 0;
	char*	strBuf = NULL;

	char*	pHead = NULL;
	char*	pEnd = NULL;

	//	找到 method1 的最后一个元素
	while(NULL != method1[i])
	{
		++i;
	}

	//	获取 redis 中同作者推荐信息
	ret = redis_get_hash_string(redisInfo, iKey, "test_method1");
	if(ret != OK)
	{
		return ERROR;
	}

	pEnd = redisInfo ->string;
	pHead = pEnd;
	while('\0' != pEnd[j])
	{
		if(*pEnd == '\t')
		{
			strLen = pEnd - pHead + 1;
			strBuf = (char*)malloc(strLen);
			memset(strBuf, 0, strLen);

			strncpy(strBuf, pHead, strLen - 1);
			method1[i] = strBuf;
			
			pEnd += 3;
			pHead = pEnd;
			++i;
		}

		pEnd++;	
	}
	method1[i + 1] = NULL;

	return OK;
}

//	获取 method2 信息
int pull_method2_info(sRedisInfo* redisInfo, const char* iKey, char** method2)
{
	if(NULL == redisInfo || NULL == iKey || NULL == method2)
	{
		return ERROR;
	}

	int		ret = 0;
	int		i = 0;			//不要改
	int		j = 0;
	int		strLen = 0;
	char*	strBuf = NULL;

	char*	pHead = NULL;
	char*	pEnd = NULL;

	//	找到 method2 的最后一个元素
	while(NULL != method2[i])
	{
		++i;
	}

	//	获取 redis 中同作者推荐信息
	ret = redis_get_hash_string(redisInfo, iKey, "test_method2");
	if(ret != OK)
	{
		return ERROR;
	}

	pEnd = redisInfo ->string;
	pHead = pEnd;
	while('\0' != pEnd[j])
	{
		if(*pEnd == '\t')
		{
			strLen = pEnd - pHead + 1;
			strBuf = (char*)malloc(strLen);
			memset(strBuf, 0, strLen);

			strncpy(strBuf, pHead, strLen - 1);
			method2[i] = strBuf;
			
			pEnd += 3;
			pHead = pEnd;
			++i;
		}

		pEnd++;	
	}
	method2[i + 1] = NULL;

	return OK;
}

//	获取 icf_knn3 信息
int pull_iknn3_info(sRedisInfo* redisInfo, const char* iKey, char** iknn3)
{
	if(NULL == redisInfo || NULL == iKey || NULL == iknn3)
	{
		return ERROR;
	}

	int		ret = 0;
	int		i = 0;			//不要改
	int		j = 0;
	int		strLen = 0;
	char*	strBuf = NULL;

	char*	pHead = NULL;
	char*	pEnd = NULL;

	//	找到 method2 的最后一个元素
	while(NULL != iknn3[i])
	{
		++i;
	}

	//	获取 redis 中同作者推荐信息
	ret = redis_get_hash_string(redisInfo, iKey, "icf_knn3");
	if(ret != OK)
	{
		return ERROR;
	}

	pEnd = redisInfo ->string;
	pHead = pEnd;
	while('\0' != pEnd[j])
	{
		if(*pEnd == '\t')
		{
			strLen = pEnd - pHead + 1;
			strBuf = (char*)malloc(strLen);
			memset(strBuf, 0, strLen);

			strncpy(strBuf, pHead, strLen - 1);
			iknn3[i] = strBuf;
			
			pEnd += 3;
			pHead = pEnd;
			++i;
		}

		pEnd++;	
	}
	iknn3[i + 1] = NULL;

	return OK;
}

//	获取 icf_knn 信息
int pull_iknn_info(sRedisInfo* redisInfo, const char* iKey, char** iknn)
{
	if(NULL == redisInfo || NULL == iKey || NULL == iknn)
	{
		return ERROR;
	}

	int		ret = 0;
	int		i = 0;			//不要改
	int		j = 0;
	int		strLen = 0;
	char*	strBuf = NULL;

	char*	pHead = NULL;
	char*	pEnd = NULL;

	//	找到 method2 的最后一个元素
	while(NULL != iknn[i])
	{
		++i;
	}

	//	获取 redis 中同作者推荐信息
	ret = redis_get_hash_string(redisInfo, iKey, "icf_knn");
	if(ret != OK)
	{
		return ERROR;
	}

	pEnd = redisInfo ->string;
	pHead = pEnd;
	while('\0' != pEnd[j])
	{
		if(*pEnd == '\t')
		{
			strLen = pEnd - pHead + 1;
			strBuf = (char*)malloc(strLen);
			memset(strBuf, 0, strLen);

			strncpy(strBuf, pHead, strLen - 1);
			iknn[i] = strBuf;
			
			pEnd += 3;
			pHead = pEnd;
			++i;
		}

		pEnd++;	
	}
	iknn[i + 1] = NULL;

	return OK;
}


//	获取 ucf_knn3 信息
int pull_uknn3_info(sRedisInfo* redisInfo, const char* uKey, char** uknn3)
{
	if(NULL == redisInfo || NULL == uKey || NULL == uknn3)
	{
		return ERROR;
	}

	int		ret = 0;
	int		i = 0;			//不要改
	int		j = 0;
	int		strLen = 0;
	char*	strBuf = NULL;

	char*	pHead = NULL;
	char*	pEnd = NULL;

	//	找到 最后一个元素
	while(NULL != uknn3[i])
	{
		++i;
	}

	//	获取 redis 中同作者推荐信息
	ret = redis_get_hash_string(redisInfo, uKey, "ucf_knn3");
	if(ret != OK)
	{
		return ERROR;
	}

	pEnd = redisInfo ->string;
	pHead = pEnd;
	while('\0' != pEnd[j])
	{
		if(*pEnd == '\t')
		{
			strLen = pEnd - pHead + 1;
			strBuf = (char*)malloc(strLen);
			memset(strBuf, 0, strLen);

			strncpy(strBuf, pHead, strLen - 1);
			uknn3[i] = strBuf;
			
			pEnd += 3;
			pHead = pEnd;
			++i;
		}

		pEnd++;	
	}
	uknn3[i + 1] = NULL;

	return OK;
}

//	获取 ucf_knn 信息
int pull_uknn_info(sRedisInfo* redisInfo, const char* uKey, char** uknn)
{
	if(NULL == redisInfo || NULL == uKey || NULL == uknn)
	{
		return ERROR;
	}

	int		ret = 0;
	int		i = 0;			//不要改
	int		j = 0;
	int		strLen = 0;
	char*	strBuf = NULL;

	char*	pHead = NULL;
	char*	pEnd = NULL;

	//	找到 的最后一个元素
	while(NULL != uknn[i])
	{
		++i;
	}

	//	获取 redis 中同作者推荐信息
	ret = redis_get_hash_string(redisInfo, uKey, "ucf_knn");
	if(ret != OK)
	{
		return ERROR;
	}

	pEnd = redisInfo ->string;
	pHead = pEnd;
	while('\0' != pEnd[j])
	{
		if(*pEnd == '\t')
		{
			strLen = pEnd - pHead + 1;
			strBuf = (char*)malloc(strLen);
			memset(strBuf, 0, strLen);

			strncpy(strBuf, pHead, strLen - 1);
			uknn[i] = strBuf;
			
			pEnd += 3;
			pHead = pEnd;
			++i;
		}

		pEnd++;	
	}
	uknn[i + 1] = NULL;

	return OK;
}


//	获取 cart_item 信息
int pull_cart_info(sRedisInfo* redisInfo, const char* uKey, char** cart)
{
	if(NULL == redisInfo || NULL == uKey || NULL == cart)
	{
		return ERROR;
	}

	int		ret = 0;
	int		i = 0;			//不要改
	int		j = 0;
	int		strLen = 0;
	char*	strBuf = NULL;

	char*	pHead = NULL;
	char*	pEnd = NULL;

	//	找到 的最后一个元素
	while(NULL != cart[i])
	{
		++i;
	}

	//	获取 redis 中同作者推荐信息
	ret = redis_get_hash_string(redisInfo, uKey, "cart_item");
	if(ret != OK)
	{
		return ERROR;
	}

	pEnd = redisInfo ->string;
	pHead = pEnd;
	while('\0' != pEnd[j])
	{
		if(*pEnd == '\t')
		{
			strLen = pEnd - pHead + 1;
			strBuf = (char*)malloc(strLen);
			memset(strBuf, 0, strLen);

			strncpy(strBuf, pHead, strLen - 1);
			cart[i] = strBuf;
			
			pEnd += 3;
			pHead = pEnd;
			++i;
		}

		pEnd++;	
	}
	cart[i + 1] = NULL;

	return OK;
}










