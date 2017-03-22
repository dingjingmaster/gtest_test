#include "test_redis_op.h"

#include <stdio.h>


enum
{
	OK = 0x00000001,
	ERROR = 0x00000002
};


int main(void)
{
	int				ret = 0;
	sRedisInfo		redisInfo;

	ret = redis_init(&redisInfo, "127.0.0.1", 7689);
	if(ret == ERROR)
	{
		return ERROR;
	}

	ret = redis_conn(&redisInfo);
	if(ret == ERROR)
	{
		return ERROR;
	}

	ret = redis_insert_hash(&redisInfo, "ww", "test1", "test11", NULL);
	ret = redis_insert_hash(&redisInfo, "ww", "test2", "test22", NULL);
	ret = redis_insert_hash(&redisInfo, "ww", "test3", "3", NULL);
	if(ret == ERROR)
	{
		return ERROR;
	}

	ret = redis_get_hash_string(&redisInfo, "ww", "test1");
	if(ret == ERROR)
	{
		return ERROR;
	}

	printf("str = %s\n", redisInfo.string);

	redis_free_hash_string(&redisInfo);

	ret = redis_get_hash_interger(&redisInfo, "ww", "test3");

	printf("integer = %d\n", redisInfo.interger);

	return 0;
}
