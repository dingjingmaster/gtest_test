#ifndef _TEST_HTTP_OP_H_
#define _TEST_HTTP_OP_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 *	函数功能:	tcp 客户端，向服务器发送 http 请求
 *
 *
 */

typedef struct _sSocketInfo
{
	int				fd;
	char*			recvBuf;

}sSocketInfo;

//初始化socket连接
int http_init(sSocketInfo* sockInfo, char* ip, unsigned short port);

//发送数据
int http_sendRequest(sSocketInfo* sockInfo, const char* sendReq);

//接收数据
int http_recvData(sSocketInfo* sockInfo);

//释放内存
int http_free(sSocketInfo* sockInfo);

#ifdef __cplusplus
}
#endif
#endif
