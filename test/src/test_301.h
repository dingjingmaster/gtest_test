#ifndef	_TEST_301_PAD_
#define _TEST_301_PAD_

#include "test_filter.h"

#ifdef __cplusplus
extern "C"
{
#include "test_print.h"
#include "test_pushAndPull.h"
#include "test_bkRec.h"
#endif

#ifdef __cplusplus
}
#endif


enum
{
	OK = 0x00000001,
	ERROR = 0x00000002
};

/*
typedef struct _sRequest
{
	//	用户 id 
	char			uKey[24];
	//	物品 id
	char			iKey[24];

	//	是否免费
	int				isCharge;
	//
}sRequest;
*/

typedef struct _sTestInfo
{
	//	填充需要的 redis 信息
	sRedisInfo		itemRedis;
	sRedisInfo		recRedis;
	sRequest		requestInfo;

	//	拉取得数据	书架	同作者	同分类	猜你喜欢
	char**			cartInfo;
	char**			resAuthorRec;
	char**			resCartRec;
	char**			resGuessRec;

	//	返回的数据	同作者	同分类	猜你喜欢
	char**			bkResAuthorRec;
	char**			bkResCartRec;
	char**			bkResGuessRec;

}sTestInfo;


//	信息初始化
int	test_301_init(sTestInfo* testInfo);

//	数据填充
int	test_301_pad(sTestInfo *testInfo);

//	数据拉取	301 的策略
int	test_301_pull(sTestInfo *testInfo);

//	推荐策略
int	test_301_filter(sTestInfo* testInfo);

//	结果
int	test_301_result(sTestInfo* testInfo);

#endif
