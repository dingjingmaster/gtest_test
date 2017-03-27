#include "test_http_op.h"
#include "test_log_op.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

enum
{
	OK = 0x00000001,
	ERROR = 0x00000002
};


int http_init(sSocketInfo* sockInfo, char* ip, unsigned short port)
{
	if(NULL == sockInfo || NULL == ip )
	{
		LOG("error: clieInfo is NULL\n");
		return ERROR;
	}

	int						ret;
	struct sockaddr_in 		server_addr;

	// socket
	sockInfo->fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockInfo -> fd <= 0)
	{
		LOG("error: socket\n");

		return ERROR;
	}

	// connect
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	inet_aton(ip, &(server_addr.sin_addr));
	server_addr.sin_port = htons(port); 

	int a = sizeof(server_addr);
	
	ret = connect(sockInfo->fd, (struct sockaddr*)&server_addr, a);
	if(ret == -1)
	{
		LOG("error: connect\n");

		return ERROR;
	}

	return OK;
}

//	发送请求
int http_sendRequest(sSocketInfo* sockInfo, const char* sendReq)
{
	if(NULL == sockInfo || NULL == sendReq)
	{
		LOG("error: parameter error\n");

		return ERROR;
	}

	char	sendBuf[4096] = {0};
	int		ret = 0;

	snprintf(sendBuf, 4096, "GET %s HTTP/1.1\r\n%s%s%s",								\
			sendReq,																	\
			"Pragma: no-cache\r\nCache-Control: no-cache\r\n",							\
			"User-Agent: Mozilla/4.04[en](Win95;I;Nav)\r\n",							\
			"Content-Type: application/x-www-form-urlencoded\r\n\r\n");

	ret = write(sockInfo ->fd, sendBuf, strlen(sendBuf));
	if(ret == -1)
	{
		return ERROR;
	}

	return OK;
}


int http_recvData(sSocketInfo* sockInfo)
{
	if(NULL == sockInfo)
	{
		LOG("传入错误参数");
		return ERROR;
	}
	char	recvBuf[4096] = {0};
	char*	buf = NULL;
	int		len = 0;

	read(sockInfo ->fd, recvBuf, 4096);

	len = strlen(recvBuf) + 1;
	buf = (char*)malloc(len);

	memset(buf, 0, len);
	strncpy(buf, recvBuf, len);
	sockInfo ->recvBuf = buf;

	return OK;
}


int http_free(sSocketInfo* sockInfo)
{
	if(NULL == sockInfo)
	{
		return ERROR;
	}

	if(NULL == sockInfo ->recvBuf)
	{
		free(sockInfo ->recvBuf);
		sockInfo ->recvBuf = NULL;
	}

	return OK;
}













