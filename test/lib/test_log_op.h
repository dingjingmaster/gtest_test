#ifndef _LOG_H_  
#define _LOG_H_  
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LOG(error) 										\
	printf("%s, %s, %s, %d, %s\n",	__FILE__,			\
					__FUNCTION__, 						\
					__DATE__,							\
					__LINE__,							\
					error);

#ifdef __cplusplus
}

#endif

#endif
