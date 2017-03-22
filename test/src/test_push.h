#ifndef	_TEST_PUSH_H_
#define	_TEST_PUSH_H_
#include "test_redis_op.h"
#include "test_bookInfo.h"




typedef struct _sPadInfo
{
	//	存储redis
	sRedisInfo		itemRedis;
	sRedisInfo		recomRedis;

}sPadInfo;

//	物品信息初始化
int	pad_item_init(sPadInfo* padInfo, const char* ip, unsigned int port);

//	推荐信息初始化
int	pad_recom_init(sPadInfo* padInfo, const char* ip, unsigned int port);

//	填充物品信息
int	pad_item_info(sPadInfo* padInfo, sBookInfo* bookInfo);

//	填充物品协同信息
int pad_icf_info(sPadInfo* padInfo, sItemRec* itemRec);

//	填充用户协同信息
int	pad_ucf_info(sPadInfo* padInfo, sCustomRec* customRec);

//	填充流行度推荐信息
int	pad_pop_info(sPadInfo* padInfo, sPopRec* popRec);



#endif
