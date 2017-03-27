#ifndef	_TEST_FILTER_H_
#define	_TEST_FILTER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "test_redis_op.h"
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif
#include <iostream>
#include <map>
#include <string>

/**
 *	功能:过滤
 *
 */

using namespace std;


typedef map<string, string> Map;

//	填充书架	key
int	load_bookcaseByKey(Map& map, sRedisInfo* recRedis, char** filter);

//	填充书架	name
int	load_bookcaseByName(Map& map, sRedisInfo* recRedis, char** filter);

//	过滤	与参考书籍同名的书籍	支持前几
int filter_bookNameByName(Map& map, sRedisInfo* recRedis, const char* reqBook, char** filter, int* num);

//	过滤	与参考书籍同系列名的书籍	支持前几
int filter_topNameByName(Map& map, sRedisInfo* recRedis, const char* reqBook, char** filter, int* num);

//	过滤	用户书架 	支持前几
int filter_cartByName(Map& map, sRedisInfo* recRedis, char** filter, int* num);

//	过滤	禁书	支持前几
int filter_banBook(sRedisInfo* recRedis, char** filter, int* num);

//	过滤	封面页	支持前几
int filter_coverBook(sRedisInfo* recRedis, char** filter, int* num);

//	过滤	XXX 推荐中 已推荐的		filter2 不变	filter1 改变
int filter_resResByName(sRedisInfo* recRedis, char** filter1, char**filter2);

int	map_find(Map& map, const char* key);

int	map_insert(Map& map, const char* key);


#endif
