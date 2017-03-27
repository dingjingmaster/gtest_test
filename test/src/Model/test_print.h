#ifndef _TEST_PRINT_H_
#define _TEST_PRINT_H_
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

//	本地 与 服务端 结果对比打印
int	test_print(const char* title, char** local, char** serv);

//	仅答应某一推荐列表
int	test_print_recList(const char* title, char** list);


#ifdef __cplusplus
}
#endif

#endif
