#include "test_http_op.h"
#include "test_json_op.h"

typedef struct _sRequest
{
	char            uKey[24];

	char            iKey[24];

	char			ip[128];
	
	short           isCharge;

	unsigned short	port;

	sSocketInfo		sockInfo;

	

}sRequest;

//	发送 http 请求	并	解析 http 请求
int	bkRec_sendAndGet(sRequest* request, char** bkResAuthorRec, char** bkResCartRec, char** bkResGuessRec);

//	结果对比	完全匹配
int	bkRec_compRes_equal(char** localVal, char** servVal);

//	结果对比	包含与否
int bkRec_compRes_contain(char** localVal, char** servVal);
