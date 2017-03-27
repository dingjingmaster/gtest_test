#ifndef	_TEST_PUSH_H_
#define	_TEST_PUSH_H_
#include "test_redis_op.h"
#include "test_bookInfo.h"


//	物品信息初始化
int	push_redis_init(sRedisInfo* redisInfo, const char* ip, unsigned int port);

//	填充物品信息
int	push_item_info(sRedisInfo* redisInfo, sBookInfo* bookInfo);

//	填充物品协同信息
int push_icf_info(sRedisInfo* redisInfo, sItemRec* itemRec);

//	填充用户协同信息
int	push_ucf_info(sRedisInfo* redisInfo, sCustomRec* customRec);

//	填充流行度推荐信息
int	push_pop_info(sRedisInfo* redisInfo, sPopRec* popRec);

//	获取 同作者 信息 追加的方式
int pull_method1_info(sRedisInfo* redisInfo, const char* iKey, char** method1);

//	获取 同分类 信息 追加的方式
int pull_method2_info(sRedisInfo* redisInfo, const char* iKey, char** method2);

//	获取 icf_knn3 信息 追加的方式
int pull_iknn3_info(sRedisInfo* redisInfo, const char* iKey, char** iknn3);

//	获取 icf_knn 信息 追加的方式
int pull_iknn_info(sRedisInfo* redisInfo, const char* iKey, char** iknn);

//	获取 ucf_knn3 信息 追加的方式
int pull_uknn3_info(sRedisInfo* redisInfo, const char* uKey, char** uknn3);

//	获取 ucf_knn 信息 追加的方式
int pull_uknn_info(sRedisInfo* redisInfo, const char* uKey, char** uknn);

//	获取 cart_item 信息 追加的方式
int pull_cart_info(sRedisInfo* redisInfo, const char* uKey, char** cart);

#endif
