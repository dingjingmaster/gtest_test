#ifndef _TEST_JSON_H_  
#define _TEST_JSONH_  
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

/**
 *	程序功能: 	对 json 进行浅封装 提高程序健壮性
 *	程序调用:
 *		json 打包: 初始化 ---> json 打包回调 ---> 释放
 *		json 解析: 初始化 ---> json 解析回调 ---> 释放
 *	
 *	返回值:
 *		成功:	0x00000001
 *		失败:	0x00000002
 *
 *	作者: 丁敬
 *	时间: 2017年3月17日11:23:37
 */

typedef struct _sJsonInfo
{
	void*			dataIn;
	unsigned int	dataInLen;
	void*			dataOut;
	unsigned int	dataOutLen;

}sJsonInfo;

//	json 回调
typedef int(*json_operation_back)(sJsonInfo* jsonData, void* arg);


//	json	初始化
int json_init(sJsonInfo* jsonData, const char* data, unsigned int dataLen);

//	json	打包
int	json_package(json_operation_back package, sJsonInfo* jsonData, void* arg);

//	json	解析
int json_parse(json_operation_back parse, sJsonInfo* jsonData, void* arg);

//	json	释放
int json_free(sJsonInfo* jsonData);



#ifdef __cplusplus
}
#endif

#endif
