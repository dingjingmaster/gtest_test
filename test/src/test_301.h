#ifndef	_TEST_301_PAD_
#define _TEST_301_PAD_

#include "test_push.h"

enum
{
	OK = 0x00000001,
	ERROR = 0x00000002
};

typedef struct _sRequest
{
	//
}sRequest;

typedef struct _sTestInfo
{
	//	填充需要
	sPadInfo		redisInfo;

	sRequest		requestInfo;




}sTestInfo;


//	书籍信息	sBookInfo		bookInfo;

//	用户协同推荐	sItemRec		itemRec;

//	用户协同推荐	sCustomRec		

//	流行度推荐		sPopRec


//	信息初始化
int	test_301_init(sTestInfo* testInfo);

//	数据填充
int	test_301_pad(sTestInfo *testInfo);

//	数据拉取
int	test_301_pull(sTestInfo *testInfo);

#endif
