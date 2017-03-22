#include "test_push.h"
#include <string.h>

enum
{
	OK = 0x00000001,
	ERROR = 0x00000002
};


//	物品信息初始化
int	pad_item_init(sPadInfo* padInfo, const char* ip, unsigned int port)
{
	if(NULL == padInfo || NULL == ip)
	{
		return ERROR;
	}

	int		ret = 0;

	ret = redis_init(&(padInfo ->itemRedis), ip, port);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_conn(&(padInfo ->itemRedis));
	if(ret != OK)
	{
		return ERROR;
	}


	return OK;
}

//	推荐信息初始化
int	pad_recom_init(sPadInfo* padInfo, const char* ip, unsigned int port)
{
	if(NULL == padInfo || NULL == ip)
	{
		return ERROR;
	}

	int		ret = 0;

	//
	ret = redis_init(&(padInfo ->recomRedis), ip, port);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_conn(&(padInfo ->recomRedis));
	if(ret != OK)
	{
		return ERROR;
	}


	return OK;
}

//	填充物品信息
int	pad_item_info(sPadInfo* padInfo, sBookInfo* bookInfo)
{
	if(NULL == padInfo || NULL == bookInfo)
	{
		return ERROR;
	}

	int			ret = 0;
	char		charTmp[32] = {0};
	
	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "raw_name", bookInfo ->raw_name, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "norm_name", bookInfo ->norm_name, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "top_name", bookInfo ->top_name, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "raw_author", bookInfo ->raw_author, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "norm_author", bookInfo ->norm_author, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "item_icon", bookInfo ->item_icon, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	memset(charTmp, 0, 32);
	snprintf(charTmp, 32, "%d", bookInfo ->item_rank);
	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "item_rank", charTmp, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	memset(charTmp, 0, 32);
	snprintf(charTmp, 32, "%d", bookInfo ->view_count);
	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "view_count", charTmp, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	memset(charTmp, 0, 32);
	snprintf(charTmp, 32, "%d", bookInfo ->mask_level);
	ret = redis_insert_hash(&(padInfo ->itemRedis), bookInfo ->iKey, "mask_level", charTmp, NULL);
	if(ret != OK)
	{
		return ERROR;
	}



	return OK;
}

//	填充物品协同信息
int pad_icf_info(sPadInfo* padInfo, sItemRec* itemRec)
{
	if(NULL == padInfo || NULL == itemRec)
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), itemRec ->iKey, "test_method1", buf, NULL);
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), itemRec ->iKey, "test_method2", buf, NULL);
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), itemRec ->iKey, "icf_knn3", buf, NULL);
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), itemRec ->iKey, "icf_knn", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	return OK;
}

//	填充用户协同信息
int	pad_ucf_info(sPadInfo* padInfo, sCustomRec* customRec)
{
	if(NULL == padInfo || NULL == customRec)
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), customRec ->uKey, "cart_item", buf, NULL);
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), customRec ->uKey, "ucf_knn3", buf, NULL);
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), customRec ->uKey, "icf_knn", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}


	return OK;
}


//	填充流行度推荐信息
int	pad_pop_info(sPadInfo* padInfo, sPopRec* popRec)
{
	if(NULL == padInfo || NULL == popRec)
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

	ret = redis_insert_hash(&(padInfo ->recomRedis), popRec ->pKey, "pop_topn", buf, NULL);
	if(ret != OK)
	{
		return ERROR;
	}

	return OK;
}


