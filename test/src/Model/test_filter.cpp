#include "test_filter.h"
#include <cstring>
#include <stdlib.h>

enum
{
	OK = 0X00000001,
	ERROR = 0X00000002,
	EXIST = 0x00000003,
	NEXIST = 0x00000004
};


//	填充书架
int	load_bookcaseByKey(Map& map, sRedisInfo* recRedis, char** filter)
{
	if(NULL == recRedis || NULL == filter)
	{
		return ERROR;
	}

	int			i = 0;

	while(NULL != filter[i])
	{
		map.insert(pair<string, string>(filter[i], filter[i]));

		i++;
	}


	return OK;
}

int	load_bookcaseByName(Map& map, sRedisInfo* recRedis, char** filter)
{
	if(NULL == recRedis || NULL == filter)
	{
		return ERROR;
	}

	int			i = 0;
	int			ret = 0;
	char**		pBC = filter;

	while(NULL != pBC[i])
	{
		//	开始数据填充	填充书籍的 key	和	归一化书名
		ret = redis_get_hash_string(recRedis, pBC[i], "norm_name");
		if(ret != OK)
		{
			return ERROR;
		}

//		printf("暑假 %s\n", recRedis ->string);

		map_insert(map, recRedis ->string);

		i++;
	}

	return OK;
}




//	过滤	与参考书籍同名的书籍	支持前几
int filter_bookNameByName(Map& map, sRedisInfo* recRedis, const char* reqBook, char** filter, int* num)
{
	if(NULL == recRedis || NULL == filter)
	{
		return ERROR;
	}

	int			ret = 0;
	int			i = 0;
	int			j = 0;
	char**		pBC = filter;
	char**		pF = filter;

	//	获取参考书籍的书名
	ret = redis_get_hash_string(recRedis, reqBook, "norm_name");
	if(ret != OK)
	{
		return ERROR;
	}

	map_insert(map, recRedis ->string);

	//	开始比较、过滤
	i = 0;
	j = 0;
	while(NULL != pBC[i] && *num > 0)
	{
		ret = redis_get_hash_string(recRedis, pBC[i], "norm_name");
		if(ret != OK)
		{
			return ERROR;
		}

		//	map 中存在不?
		if(map_find(map, recRedis ->string) == EXIST)		//	存在过滤该值
		{
			j = i; 
			while(pF[j + 1] != NULL)
			{
				free(pF[j]);
				pF[j] = pF[j + 1];

				++j;
			}

			pF[j + 1] = NULL;
		}

		map_insert(map, recRedis ->string);

		i++;
	}
	
	//

	return OK;
}

//	过滤	与参考书籍同系列名的书籍	支持前几
int filter_topNameByName(Map& map, sRedisInfo* recRedis, const char* reqBook, char** filter, int* num)
{
	if(NULL == recRedis || NULL == filter)
	{
		return ERROR;
	}

	int			ret = 0;
	int			i = 0;
	int			j = 0;
	char**		pBC = filter;
	char**		pF = filter;

	//	获取参考书籍的书名
	ret = redis_get_hash_string(recRedis, reqBook, "top_name");
	if(ret != OK)
	{
		return ERROR;
	}

	map_insert(map, recRedis ->string);

	//	开始比较、过滤
	i = 0;
	j = 0;
	while(NULL != pBC[i] && *num > 0)
	{
		ret = redis_get_hash_string(recRedis, pBC[i], "top_name");
		if(ret != OK)
		{
			return ERROR;
		}

		//	map 中存在不?
		if(map_find(map, recRedis ->string) == EXIST)		//	存在过滤该值
		{
			j = i; 
			while(pF[j + 1] != NULL)
			{
				free(pF[j]);
				pF[j] = pF[j + 1];

				++j;
			}

			pF[j + 1] = NULL;
		}

		map_insert(map, recRedis ->string);

		i++;
	}
	

	return OK;
}

//	过滤	用户书架 	支持前几
int filter_cartByName(Map& map, sRedisInfo* recRedis, char** filter, int* num)
{
	if(NULL == recRedis || NULL == filter)
	{
		return ERROR;
	}

	int			ret = 0;
	int			i = 0;
	int			j = 0;
	char*		tmp = NULL;
	char**		pBC = filter;
	char**		pF = filter;

	//	开始比较、过滤
	i = 0;
	j = 0;
	while(NULL != pBC[i] && *num > 0)
	{
		ret = redis_get_hash_string(recRedis, pBC[i], "norm_name");
		if(ret != OK)
		{
			return ERROR;
		}

		//	map 中存在不?
		if(map_find(map, recRedis ->string) == EXIST)		//	存在过滤该值
		{
			j = i; 
			tmp = pF[j];

			while(pF[j + 1] != NULL)
			{
				pF[j] = pF[j + 1];

				++j;
			}
				
			free(tmp);

			pF[j + 1] = NULL;
		}

		map_insert(map, recRedis ->string);

		i++;
	}
	




	return OK;
}

//	过滤	禁书	支持前几
int filter_banBook(sRedisInfo* recRedis, char** filter, int* num)
{
	if(NULL == recRedis || NULL == filter)
	{
		return ERROR;
	}

	int			ret = 0;
	int			i = 0;
	int			j = 0;
	char*		tmp = NULL;
	char**		pBC = filter;
	char**		pF = filter;


	//	开始比较、过滤
	i = 0;
	j = 0;
	while(NULL != pBC[i] && *num > 0)
	{
		ret = redis_get_hash_interger(recRedis, pBC[i], "mask_level");
		if(ret != OK)
		{
			return ERROR;
		}

		//	map 中存在不?
		if(recRedis ->interger == 1)		//	禁书 过滤该值
		{
			j = i; 
			tmp = pF[j];
			while(pF[j + 1] != NULL)
			{
				pF[j] = pF[j + 1];

				++j;
			}
			
			free(tmp);
			pF[j + 1] = NULL;
		}

		i++;
	}


	return OK;
}


//	过滤	封面页	支持前几
int filter_coverBook(sRedisInfo* recRedis, char** filter, int* num)
{
	if(NULL == recRedis || NULL == filter)
	{
		return ERROR;
	}

	int			ret = 0;
	int			i = 0;
	int			j = 0;
	char*		tmp = NULL;
	char**		pBC = filter;
	char**		pF = filter;


	//	开始比较、过滤
	i = 0;
	j = 0;
	while(NULL != pBC[i] && *num > 0)
	{
		ret = redis_get_hash_string(recRedis, pBC[i], "item_icon");
		if(ret != OK)
		{
			return ERROR;
		}

		if(strlen(recRedis ->string) == 0)		//	封面页链接 长度 0
		{
			j = i; 
			tmp = pF[j];
			while(pF[j + 1] != NULL)
			{
				pF[j] = pF[j + 1];

				++j;
			}
			
			free(tmp);
			pF[j + 1] = NULL;
		}

		i++;
	}


	return OK;
}

//	过滤	XXX 推荐中 已推荐的
int filter_resResByName(sRedisInfo* recRedis, char** filter1, char**filter2)
{
	if(NULL == recRedis || NULL == filter1 || NULL == filter2)
	{
		return ERROR;
	}

	int					i = 0;
	int					j = 0;
	int					k = 0;
	int					ret = 0;
	char*				tmp = NULL;
	char				buf[32] = {0};

	//
	while(NULL != filter1[i])
	{
		ret = redis_get_hash_string(recRedis, filter1[i], "norm_name");
		if(ret != OK)
		{
			return ERROR;
		}
		memset(buf, 0, 32);
		strncpy(buf, recRedis ->string, 32);

		for(j = 0; 	NULL != filter2[j]; ++j)
		{
			ret = redis_get_hash_string(recRedis, filter2[j], "norm_name");
			if(ret != OK)
			{
				return ERROR;
			}

			if(strcmp(buf, recRedis ->string) == 0)
			{
				k = i; 
				tmp = filter1[k];
				while(filter1[k + 1] != NULL)
				{
					filter1[j] = filter1[k + 1];

					++k;
				}

				free(tmp);
				filter1[k + 1] = NULL;
			}
		}

		i++;
	}
	
	return OK;
}


int	map_find(Map& map, const char* key)
{
	if(NULL == key)
	{
		return ERROR;
	}

	string	kBuf = key;
	//
	Map::iterator it = map.find(kBuf);
	if(it != map.end())
	{
		return EXIST;
	}
	else
	{
		return NEXIST;
	}

	return OK;
}


int	map_insert(Map& map, const char* key)
{
	if(NULL == key)
	{
		return ERROR;
	}

	map.insert(pair<string, string>(key, key));
	

	return OK;
}












