#include "test_redis_op.h"
#include "test_log_op.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum
{
	OK = 0x00000001,
	ERROR = 0x00000002,
	NOTFIND = 0x00000003
};


//	redis 信息初始化
int redis_init(sRedisInfo* redisInfo, const char* ip, const unsigned int port)
{
	if(NULL == redisInfo || NULL == ip)
	{
		return ERROR;
	}

	memset(redisInfo, 0, sizeof(sRedisInfo));

	strncpy(redisInfo ->ip, ip, strlen(ip));
	redisInfo ->port = port;

	return OK;
}


//	redis连接
int redis_conn(sRedisInfo* redisInfo)
{
	if(NULL == redisInfo)
	{
		return ERROR;
	}

	redisInfo ->conn = redisConnect(redisInfo ->ip, redisInfo ->port);
	if (redisInfo ->conn->err)
	{
		redisFree(redisInfo ->conn);

    	return ERROR;
  	}

	return OK;
}

//	清空 redis
int redis_flushall(sRedisInfo* redisInfo)
{
	if(NULL == redisInfo)
	{
		LOG("传入参数为空!!!");

		return ERROR;
	}

	redisInfo ->reply = redisCommand(redisInfo ->conn, "flushall");
	if(NULL == redisInfo ->reply)
	{
		LOG("redis command error\n\n");
	}
	
	if(redisInfo ->reply != NULL)
	{
		freeReplyObject(redisInfo ->reply);
		redisInfo ->reply = NULL;
	}
	

	return OK;
}

//	释放 redis
int redis_free(sRedisInfo* redisInfo)
{
	if(NULL == redisInfo)
	{
		return ERROR;
	}
	
	if(redisInfo ->conn != NULL)
	{
		redisFree(redisInfo ->conn);
		redisInfo ->conn = NULL;
	}

	if(redisInfo ->reply != NULL)
	{
		freeReplyObject(redisInfo ->reply);
		redisInfo ->reply = NULL;
	}

	if(redisInfo ->string != NULL)
	{
		free(redisInfo ->string);
		redisInfo ->string = NULL;
	}

	return OK;
}

//	获取信息，回调
int redis_get_hash_data(sRedisInfo* redisInfo, void* arg, redis_get_back getAll)
{
	if(NULL == getAll || NULL == redisInfo)
	{
		return ERROR;
	}
	(*getAll)(redisInfo, arg);

	return OK;
}


//	支持重载的 redis 插入操作
int redis_insert_hash_cb(sRedisInfo* redisInfo, const char* iKey, const char* key, const char* value, void* arg, redis_insert_back insertBack)
{
	if(NULL == redisInfo || NULL == iKey || NULL == key || NULL == value)
	{
		return ERROR;
	}

	insertBack(redisInfo, iKey, key, value, arg);

	return OK;
}

//	插入操作
int redis_insert_hash(sRedisInfo* redisInfo, const char* iKey, const char* key, const char* value, void* arg)
{
	if(NULL == redisInfo || NULL == iKey || NULL == key)
	{
		return ERROR;
	}

	if(NULL == redisInfo ->conn)
	{
		return ERROR;
	}

	redisInfo ->reply = (redisReply*) redisCommand(redisInfo ->conn, "HSET %s %s %s", iKey, key, value);

	//释放
	freeReplyObject(redisInfo ->reply);

	return OK;
}


//	获取 redis 指定字段的值	
int redis_get_hash_string(sRedisInfo* redisInfo, const char* iKey, const char* key)
{
	if(NULL == redisInfo || NULL == iKey || NULL == key)
	{
		return ERROR;
	}

	if(NULL == redisInfo ->conn)
	{
		return ERROR;
	}
	
	size_t					eles = 0;
	size_t					len = 0;
	int						ret = 0;

	redisInfo ->reply = (redisReply*) redisCommand(redisInfo ->conn, "HGET %s %s", iKey, key);
	eles = redisInfo ->reply ->elements;
	len = redisInfo ->reply ->len;

	if(len > 0)
	{
		redisInfo ->string = (char*)malloc(len);
		memset(redisInfo ->string, 0, len);
		strncpy(redisInfo ->string, redisInfo ->reply ->str, len);

		ret = OK;
	}
	else
	{
		ret = NOTFIND;
	}

	//释放
	freeReplyObject(redisInfo ->reply);

	return ret;
}

//	释放 redis 指定字段 字符串	
int redis_free_hash_string(sRedisInfo* redisInfo)
{
	if(NULL == redisInfo)
	{
		return ERROR;
	}

	if(NULL == redisInfo ->string)
	{
		free(redisInfo ->string);
		redisInfo ->string = NULL;
	}

	return OK;
}



//	获取 redis 指定字段 数字	
int redis_get_hash_interger(sRedisInfo* redisInfo, const char* iKey, const char* key)
{
	if(NULL == redisInfo || NULL == iKey || NULL == key)
	{
		return ERROR;
	}

	size_t					len = 0;
	int						ret = 0;

	if(NULL == redisInfo ->conn)
	{
		return ERROR;
	}
	
	redisInfo ->reply = (redisReply*) redisCommand(redisInfo ->conn, "HGET %s %s", iKey, key);
	len = redisInfo ->reply ->len;

	if(len > 0)
	{
		redisInfo ->interger = atoi(redisInfo ->reply ->str);
		ret = OK;
	}
	else
	{
		ret = NOTFIND;
	}

	//释放
	freeReplyObject(redisInfo ->reply);

	return OK;
}


