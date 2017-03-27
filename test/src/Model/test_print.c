#include "test_print.h"
#include <string.h>

enum
{
	OK = 0x00000001,
	ERROR = 0x00000002
};

int	test_print(const char* title, char** local, char** serv)
{
	if(NULL == local || NULL == serv)
	{
		return ERROR;	
	}

	int			i = 0;
	int			j = 0;
	char		tmp[32] = {0};
	char		buf[4096] = {0};

	if(NULL != title)
	{
		printf("\n%s\n", title);
	}

	memset(buf, 0, 4096);
	j = 0;
	for(i = 0; NULL != local[i]; ++i)
	{
		memset(tmp, 0, 32);
		if(5 == j)
		{
			snprintf(tmp, 32, "\n\t  %s\t", local[i]);
			j = 0;
		}
		else
		{
			snprintf(tmp, 32, "%s\t", local[i]);
		}

		strcat(buf,tmp);

		++j;
	}

	printf("本地模拟: %s\n", buf);

	memset(buf, 0, 4096);
	j = 0;
	for(i=0; NULL != serv[i]; ++i)
	{
		memset(tmp, 0, 32);
		if(5 == j)
		{
			snprintf(tmp, 32, "\n\t  i_%s\t", serv[i]);
			j = 0;
		}
		else
		{
			snprintf(tmp, 32, "i_%s\t", serv[i]);
		}

		strcat(buf,tmp);

		++j;
	}
	
	printf("返回结果: %s\n", buf);

	return OK;
}


int	test_print_recList(const char* title, char** list)
{
	if(NULL == list)
	{
		return ERROR;
	}

	if(NULL != title)
	{
		printf("\n%s\n", title);
	}

	int		i = 0;
	for(i = 0; NULL != list[i]; ++i)
	{
		printf("%s\n", list[i]);
	}


	return OK;
}














