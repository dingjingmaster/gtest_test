#ifndef _TEST_REDIS_OP_H_
#define _TEST_REDIS_OP_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "hiredis.h"

/**
 *	函数功能:	对 redis 进行一层浅封装，提高程序的健壮性
 *	程序调用:
 *
 *
 * 	返回值:		
 * 		成功		返回 OK(0x00000001)
 * 		失败		返回 ERROR(0x00000002)
 * 		没找到		返回 NOTFIND(0X00000003)
 *
 *	作者:	丁敬
 *	时间:	2017年3月17日14:32:27
 */

typedef struct _sRedisInfo
{
	char				ip[128];
	char*				string;
	int					strLen;
	int					interger;
	unsigned int		port;
	redisContext*		conn;
	redisReply*			reply;

}sRedisInfo;

/********************		定义回调		*****************/
//	获取 redis 所有数据的回调函数
typedef int(*redis_get_back)(sRedisInfo* redisInfo, void* arg);

//	插入操作的回调函数
typedef int(*redis_insert_back)(sRedisInfo* redisInfo, const char* iKey, const char* key, const char* value, void* arg);


/********************		函数声明		*****************/
//	redis 信息初始化
int redis_init(sRedisInfo* redisInfo, const char* ip, const unsigned int port);

//	连接 redis
int redis_conn(sRedisInfo* redisInfo);

//	清空 redis
int redis_flushall(sRedisInfo* redisInfo);

//	释放 redis
int redis_free(sRedisInfo* redisInfo);

//	获取 redis 指定信息
int redis_get_hash_data(sRedisInfo* redisInfo, void* arg, redis_get_back getAll);

//	redis 数据插入 支持重载	 可以传入自己的 回调函数
int redis_insert_hash_cb(sRedisInfo* redisInfo, const char* iKey, const char* key, const char* value, void* arg, redis_insert_back insertBack);

//	插入操作
int redis_insert_hash(sRedisInfo* redisInfo, const char* iKey, const char* key, const char* value, void* arg);

//	获取 redis 指定字段 字符串	
int redis_get_hash_string(sRedisInfo* redisInfo, const char* iKey, const char* key);

//	释放 redis 指定字段 字符串	
int redis_free_hash_string(sRedisInfo* redisInfo);

//	获取 redis 指定字段 数字	
int redis_get_hash_interger(sRedisInfo* redisInfo, const char* iKey, const char* key);



#ifdef __cplusplus
}
#endif

#endif
