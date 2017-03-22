#include <stdio.h>
#include "test_http_op.h"

int main()
{
	sSocketInfo		sockInfo;

	http_init(&sockInfo, "127.0.0.1", 6021);
	http_sendRequest(&sockInfo, "/recomm.json?recommType=301&uid=000000001&udid=&count=20&charge=1&reqGid=000000001");
	http_recvData(&sockInfo);
	printf("%s\n", sockInfo.recvBuf);

	http_free(&sockInfo);
	

	return 0;
}
