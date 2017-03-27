#include "test_301.h"


//	信息初始化
int	test_301_init(sTestInfo* testInfo)
{
	if(NULL == testInfo)
	{
		return ERROR;
	}

	int		ret = 0;


	memset(testInfo, 0, sizeof(sTestInfo));

	//	物品 redis 初始化
	ret = push_redis_init(&(testInfo ->itemRedis), "127.0.0.1", 7689);
	if(OK != ret)
	{
		return ERROR;
	}

	//	推荐 redis 初始化
	ret = push_redis_init(&(testInfo ->recRedis), "127.0.0.1", 7690);
	if(OK != ret)
	{
		return ERROR;
	}

	//	分配内存空间	同作者	同分类	猜你喜欢	各 128
	testInfo ->resAuthorRec = (char**) malloc (sizeof(char*) * 128);
	testInfo ->resCartRec = (char**) malloc (sizeof(char*) * 128);
	testInfo ->resGuessRec = (char**) malloc (sizeof(char*) * 128);

	memset(testInfo ->resAuthorRec, 0, sizeof(char*) * 128);
	memset(testInfo ->resCartRec, 0, sizeof(char*) * 128);
	memset(testInfo ->resGuessRec, 0, sizeof(char*) * 128);

	//	返回信息分配内存空间	同作者	同分类	猜你喜欢	各 128
	testInfo ->bkResAuthorRec = (char**) malloc (sizeof(char*) * 128);
	testInfo ->bkResCartRec = (char**) malloc (sizeof(char*) * 128);
	testInfo ->bkResGuessRec = (char**) malloc (sizeof(char*) * 128);

	memset(testInfo ->bkResAuthorRec, 0, sizeof(char*) * 128);
	memset(testInfo ->bkResCartRec, 0, sizeof(char*) * 128);
	memset(testInfo ->bkResGuessRec, 0, sizeof(char*) * 128);

	//	推荐服务
	strncpy(testInfo ->requestInfo.ip, "127.0.0.1", 128);
	testInfo ->requestInfo.port = 6021;

	return OK;
}


int	test_301_pad(sTestInfo* testInfo)
{
	if(NULL == testInfo)
	{
		return ERROR;
	}

	int				ret = 0;
	int				i = 0;
	char*			iKeyBuf = NULL;
	char*			raw_name = NULL;
	char*			norm_name = NULL;
	char*			top_name = NULL;
	char*			raw_author = NULL;
	char*			norm_author = NULL;
	sBookInfo*		book = NULL;
	sItemRec*		itemRec = NULL;
	sCustomRec*		customRec = NULL;
	sPopRec*		popRec = NULL;


	book = (sBookInfo*)malloc(sizeof(sBookInfo));
	itemRec = (sItemRec*)malloc(sizeof(sItemRec));
	customRec = (sCustomRec*)malloc(sizeof(sCustomRec));
	popRec = (sPopRec*)malloc(sizeof(sPopRec));


	iKeyBuf = (char*)malloc(32);
	raw_name = (char*)malloc(40);
	norm_name = (char*)malloc(40);
	top_name = (char*)malloc(40);
	raw_author = (char*)malloc(40);
	norm_author = (char*)malloc(40);

	//	免费书籍填充	0 - 99 基本信息 
	for(i = 0; i < 100; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i);
		snprintf(raw_name, 40, "raw_name_%03d", i);
		snprintf(norm_name, 40, "norm_name_%03d", i);
		snprintf(top_name, 40, "top_name_%03d", i);
		snprintf(raw_author, 40, "raw_author_%03d", i);
		snprintf(norm_author, 40, "norm_author%03d", i);

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, "http://www.baidu.com/aa.png", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 0;	

		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}

	//	没有书名
	for(i = 0; i < 10; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i + 100);
		snprintf(raw_name, 40, " ");
		snprintf(norm_name, 40, "norm_name_%03d", i + 100);
		snprintf(top_name, 40, "top_name_%03d", i + 100);
		snprintf(raw_author, 40, "raw_author_%03d", i + 100);
		snprintf(norm_author, 40, "norm_author%03d", i + 100);

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, "http://www.baidu.com/aa.png", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 0;	


		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}

	//	没有归一化书名 
	for(i = 0; i < 10; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i + 110);
		snprintf(raw_name, 40, "raw_name_%03d", i + 110);
		snprintf(norm_name, 40, " ");
		snprintf(top_name, 40, "top_name_%03d", i + 110);
		snprintf(raw_author, 40, "raw_author_%03d", i + 110);
		snprintf(norm_author, 40, "norm_author%03d", i + 110);

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, "http://www.baidu.com/aa.png", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 0;	

		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}


	//	没有同系列名
	for(i = 0; i < 10; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i + 120);
		snprintf(raw_name, 40, "raw_name_%03d", i + 120);
		snprintf(norm_name, 40, "norm_name_%03d", i + 120);
		snprintf(top_name, 40, " ");
		snprintf(raw_author, 40, "raw_author_%03d", i + 120);
		snprintf(norm_author, 40, "norm_author%03d", i + 120);

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, "http://www.baidu.com/aa.png", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 0;	

		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}

	//	没有作者名 
	for(i = 0; i < 10; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i + 130);
		snprintf(raw_name, 40, "raw_name_%03d", i + 130);
		snprintf(norm_name, 40, "norm_name_%03d", i + 130);
		snprintf(top_name, 40, "top_name_%03d", i + 130);
		snprintf(raw_author, 40, " ");
		snprintf(norm_author, 40, "norm_author%03d", i + 130);

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, "http://www.baidu.com/aa.png", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 0;	

		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}

	//	没有归一化作者名
	for(i = 0; i < 10; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i + 140);
		snprintf(raw_name, 40, "raw_name_%03d", i + 140);
		snprintf(norm_name, 40, "norm_name_%03d", i + 140);
		snprintf(top_name, 40, "top_name_%03d", i + 140);
		snprintf(raw_author, 40, "raw_author_%03d", i + 140);
		snprintf(norm_author, 40, " ");

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, "http://www.baidu.com/aa.png", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 0;	

		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}

	//	没有	封面图片 
	for(i = 0; i < 10; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i + 150);
		snprintf(raw_name, 40, "raw_name_%03d", i + 150);
		snprintf(norm_name, 40, "norm_name_%03d", i + 150);
		snprintf(top_name, 40, "top_name_%03d", i + 150);
		snprintf(raw_author, 40, "raw_author_%03d", i + 150);
		snprintf(norm_author, 40, "norm_author%03d", i + 150);

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, " ", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 0;	

		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}

	//	是禁书
	for(i = 0; i < 10; ++i)
	{
		memset(book, 0, sizeof(sBookInfo));
		memset(iKeyBuf, 0, sizeof(iKeyBuf));
		memset(raw_name, 0, sizeof(raw_name));
		memset(norm_name, 0, sizeof(norm_name));
		memset(top_name, 0, sizeof(top_name));
		memset(raw_author, 0, sizeof(raw_author));
		memset(norm_author, 0, sizeof(norm_author));

		snprintf(iKeyBuf, 32, "i_000000%03d", i + 160);
		snprintf(raw_name, 40, "raw_name_%03d", i + 160);
		snprintf(norm_name, 40, "norm_name_%03d", i + 160);
		snprintf(top_name, 40, "top_name_%03d", i + 160);
		snprintf(raw_author, 40, "raw_author_%03d", i + 160);
		snprintf(norm_author, 40, "norm_author%03d", i + 160);

		strncpy(book ->iKey, iKeyBuf, 32);
		strncpy(book ->raw_name, raw_name, 40);
		strncpy(book ->norm_name, norm_name, 40);
		strncpy(book ->top_name, top_name, 40);
		strncpy(book ->raw_author, raw_author, 40);
		strncpy(book ->norm_author, norm_author, 40);
		strncpy(book ->item_icon, "http://www.baidu.com/aa.png", 128);
		book ->item_rank = 1;
		book ->view_count = i + 1000;
		book ->mask_level = 1;	

		//padding data to redis0
		ret = push_item_info(&(testInfo ->itemRedis), book);
		if(ret != OK)
		{
			return ERROR;
		}
	}

	/***************	推荐信息	********************/



	//	书架中的书籍
	char*			carte_itm_1 = (char*)malloc(24);
	char*			carte_itm_2 = (char*)malloc(24);
	char*			carte_itm_3 = (char*)malloc(24);
	char*			carte_itm_4 = (char*)malloc(24);

	//	物品推荐的付费书籍	
	char*			u_knn3_1 = (char*)malloc(24);
	char*			u_knn3_2 = (char*)malloc(24);
	char*			u_knn3_3 = (char*)malloc(24);
	char*			u_knn3_4 = (char*)malloc(24);
	
	//	物品推荐的免费书籍
	char*			u_knn_1 = (char*)malloc(24);
	char*			u_knn_2 = (char*)malloc(24);
	char*			u_knn_3 = (char*)malloc(24);
	char*			u_knn_4 = (char*)malloc(24);


	/********		物品协同		*********/
	char*			i_knn3_1 = (char*)malloc(24);
	char*			i_knn3_2 = (char*)malloc(24);
	char*			i_knn3_3 = (char*)malloc(24);
	char*			i_knn3_4 = (char*)malloc(24);

	char*			i_knn_1 = (char*)malloc(24);
	char*			i_knn_2 = (char*)malloc(24);
	char*			i_knn_3 = (char*)malloc(24);
	char*			i_knn_4 = (char*)malloc(24);

	char*			method1_1 = (char*)malloc(24);
	char*			method1_2 = (char*)malloc(24);
	char*			method1_3 = (char*)malloc(24);
	char*			method1_4 = (char*)malloc(24);

	char*			method2_1 = (char*)malloc(24);
	char*			method2_2 = (char*)malloc(24);
	char*			method2_3 = (char*)malloc(24);
	char*			method2_4 = (char*)malloc(24);

	//	用户协同
	memset(customRec, 0, sizeof(sCustomRec));

	memset(carte_itm_1, 0, 24);
	memset(carte_itm_2, 0, 24);
	memset(carte_itm_3, 0, 24);
	memset(carte_itm_4, 0, 24);
	memset(u_knn3_1, 0, 24);
	memset(u_knn3_2, 0, 24);
	memset(u_knn3_3, 0, 24);
	memset(u_knn3_4, 0, 24);
	memset(u_knn_1, 0, 24);
	memset(u_knn_2, 0, 24);
	memset(u_knn_3, 0, 24);
	memset(u_knn_4, 0, 24);


	//	用户 1 推荐 测试免费推荐结果
	strncpy(customRec ->uKey, "u_000000001", 24);				//	用户 1 	
	strncpy(testInfo ->requestInfo.uKey, "u_000000001", 24);	//	用户 1 	

	strncpy(carte_itm_1, "i_000000002", 24);
	strncpy(carte_itm_2, "i_000000003", 24);
	strncpy(carte_itm_3, "i_000000004", 24);
	strncpy(carte_itm_4, "i_000000005", 24);
	
	customRec ->cart_item.recommend[0] = carte_itm_1;
	customRec ->cart_item.weight[0] = 0;
	customRec ->cart_item.recommend[1] = carte_itm_2;
	customRec ->cart_item.weight[1] = 0;
	customRec ->cart_item.recommend[2] = carte_itm_3;
	customRec ->cart_item.weight[2] = 0;
	customRec ->cart_item.recommend[3] = carte_itm_4;
	customRec ->cart_item.weight[3] = 0;

	//	付费书籍
	strncpy(u_knn3_1, "i_000000006", 24);
	strncpy(u_knn3_2, "i_000000007", 24);
	strncpy(u_knn3_3, "i_000000008", 24);
	strncpy(u_knn3_4, "i_000000009", 24);
	
	customRec ->ucf_knn3.recommend[0] = u_knn3_1;
	customRec ->ucf_knn3.weight[0] = 0;
	customRec ->ucf_knn3.recommend[1] = u_knn3_2;
	customRec ->ucf_knn3.weight[1] = 0;
	customRec ->ucf_knn3.recommend[2] = u_knn3_3;
	customRec ->ucf_knn3.weight[2] = 0;
	customRec ->ucf_knn3.recommend[3] = u_knn3_4;
	customRec ->ucf_knn3.weight[3] = 0;

	//	免费书籍
	strncpy(u_knn_1, "i_000000010", 24);
	strncpy(u_knn_2, "i_000000011", 24);
	strncpy(u_knn_3, "i_000000012", 24);
	strncpy(u_knn_4, "i_000000013", 24);
	
	customRec ->ucf_knn.recommend[0] = u_knn_1;
	customRec ->ucf_knn.weight[0] = 0;
	customRec ->ucf_knn.recommend[1] = u_knn_2;
	customRec ->ucf_knn.weight[1] = 0;
	customRec ->ucf_knn.recommend[2] = u_knn_3;
	customRec ->ucf_knn.weight[2] = 0;
	customRec ->ucf_knn.recommend[3] = u_knn_4;
	customRec ->ucf_knn.weight[3] = 0;

	ret = push_ucf_info(&(testInfo ->recRedis), customRec);
	if(ret != OK)
	{
		return ERROR;
	}


	//	物品 1 推荐
	memset(itemRec, 0, sizeof(itemRec));

	memset(i_knn3_1, 0, 24);
	memset(i_knn3_2, 0, 24);
	memset(i_knn3_3, 0, 24);
	memset(i_knn3_4, 0, 24);
	memset(i_knn_1, 0, 24);
	memset(i_knn_2, 0, 24);
	memset(i_knn_3, 0, 24);
	memset(i_knn_4, 0, 24);
	memset(method1_1, 0, 24);
	memset(method1_2, 0, 24);
	memset(method1_3, 0, 24);
	memset(method1_4, 0, 24);
	memset(method2_1, 0, 24);
	memset(method2_2, 0, 24);
	memset(method2_3, 0, 24);
	memset(method2_4, 0, 24);
	
	strncpy(itemRec ->iKey, "i_000000001", 24);					//	物品1
	strncpy(testInfo ->requestInfo.iKey, "i_000000001", 24);	//	物品1

	strncpy(method1_1, "i_000000014", 24);
	strncpy(method1_2, "i_000000015", 24);
	strncpy(method1_3, "i_000000016", 24);
	strncpy(method1_4, "i_000000017", 24);

	strncpy(method2_1, "i_000000018", 24);
	strncpy(method2_2, "i_000000019", 24);
	strncpy(method2_3, "i_000000020", 24);
	strncpy(method2_4, "i_000000021", 24);

	strncpy(i_knn3_1, "i_000000022", 24);
	strncpy(i_knn3_2, "i_000000023", 24);
	strncpy(i_knn3_3, "i_000000024", 24);
	strncpy(i_knn3_4, "i_000000025", 24);
	
	strncpy(i_knn_1, "i_000000026", 24);
	strncpy(i_knn_2, "i_000000027", 24);
	strncpy(i_knn_3, "i_000000028", 24);
	strncpy(i_knn_4, "i_000000029", 24);

	itemRec ->test_method1.recommend[0] = method1_1;
	itemRec ->test_method1.weight[0] = 0;
	itemRec ->test_method1.recommend[1] = method1_2;
	itemRec ->test_method1.weight[1] = 0;
	itemRec ->test_method1.recommend[2] = method1_3;
	itemRec ->test_method1.weight[2] = 0;
	itemRec ->test_method1.recommend[3] = method1_4;
	itemRec ->test_method1.weight[3] = 0;

	itemRec ->test_method2.recommend[0] = method2_1;
	itemRec ->test_method2.weight[0] = 0;
	itemRec ->test_method2.recommend[1] = method2_2;
	itemRec ->test_method2.weight[1] = 0;
	itemRec ->test_method2.recommend[2] = method2_3;
	itemRec ->test_method2.weight[2] = 0;
	itemRec ->test_method2.recommend[3] = method2_4;
	itemRec ->test_method2.weight[3] = 0;

	itemRec ->icf_knn3.recommend[0] = i_knn3_1;
	itemRec ->icf_knn3.weight[0] = 0;
	itemRec ->icf_knn3.recommend[1] = i_knn3_2;
	itemRec ->icf_knn3.weight[1] = 0;
	itemRec ->icf_knn3.recommend[2] = i_knn3_3;
	itemRec ->icf_knn3.weight[2] = 0;
	itemRec ->icf_knn3.recommend[3] = i_knn3_4;
	itemRec ->icf_knn3.weight[3] = 0;

	itemRec ->icf_knn.recommend[0] = i_knn3_1;
	itemRec ->icf_knn.weight[0] = 0;
	itemRec ->icf_knn.recommend[1] = i_knn3_2;
	itemRec ->icf_knn.weight[1] = 0;
	itemRec ->icf_knn.recommend[2] = i_knn3_3;
	itemRec ->icf_knn.weight[2] = 0;
	itemRec ->icf_knn.recommend[3] = i_knn3_4;
	itemRec ->icf_knn.weight[3] = 0;
	

	ret = push_icf_info(&(testInfo ->recRedis), itemRec);
	if(ret != OK)
	{
		return ERROR;
	}


	return OK;
}

//	301 数据拉取
int test_301_pull(sTestInfo *testInfo)
{
	if(NULL == testInfo)
	{
		return ERROR;
	}

	int			ret = 0;

	//	免费测试
	testInfo ->requestInfo.isCharge = 0;


	//	拉取数据	用户书架
	ret = pull_cart_info(&(testInfo ->recRedis), testInfo ->requestInfo.uKey, testInfo ->cartInfo);

	//	拉取数据	作者推荐
	ret = pull_method1_info(&(testInfo ->recRedis), testInfo ->requestInfo.iKey, testInfo ->resAuthorRec);

	//	拉取数据	类别推荐
	ret = pull_method2_info(&(testInfo ->recRedis), testInfo ->requestInfo.iKey, testInfo ->resCartRec);

	//	拉取数据	读了本书的人还看过		物品协同 + 用户协同 + 同类推荐
	ret = pull_iknn_info(&(testInfo ->recRedis), testInfo ->requestInfo.iKey, testInfo ->resGuessRec);

	ret = pull_uknn_info(&(testInfo ->recRedis), testInfo ->requestInfo.uKey, testInfo ->resGuessRec);

	ret = pull_method2_info(&(testInfo ->recRedis), testInfo ->requestInfo.iKey, testInfo ->resGuessRec);

	return OK;
}

//	过滤
int	test_301_filter(sTestInfo* testInfo)
{
	if(NULL == testInfo)
	{
		return ERROR;
	}

	int			ret = 0;
	int			num = 0;
	Map 		map1;
	Map 		map2;
	Map 		map3;


	//	装入书架
	ret = load_bookcaseByName(map1, &(testInfo ->itemRedis), testInfo ->cartInfo);
	
	//	作者推荐过滤		过滤 与 reqGid 同书名
//	num = 128;
//	ret = filter_bookNameByName(map1, &(testInfo ->itemRedis), testInfo ->requestInfo.iKey, testInfo ->resAuthorRec, &num);

	//	作者推荐过滤		过滤 与 reqGid 同系列名
//	num = 128;
//	ret = filter_topNameByName(map1, &(testInfo ->itemRedis), testInfo ->requestInfo.iKey, testInfo ->resAuthorRec, &num);

	//	作者推荐过滤		过滤 用户书架
	num = 128;
	ret = filter_cartByName(map1, &(testInfo ->itemRedis), testInfo ->resAuthorRec, &num);

	//	作者推荐过滤		过滤	禁书 前 5
	num = 5;
	ret = filter_banBook(&(testInfo ->recRedis), testInfo ->resAuthorRec, &num);

	
	//	装入书架
	ret = load_bookcaseByName(map2, &(testInfo ->itemRedis), testInfo ->cartInfo);

	//	读了本书的人还看过 过滤		过滤	与	reqGid	同书名
//	num = 128;
//	ret = filter_bookNameByName(map2, &(testInfo ->itemRedis), testInfo ->requestInfo.iKey, testInfo ->resGuessRec, &num);

	//	读了本书的人还看过 过滤		过滤	与	reqGid	同系列名
//	num = 128;
//	ret = filter_topNameByName(map2, &(testInfo ->itemRedis), testInfo ->requestInfo.iKey, testInfo ->resGuessRec, &num);

	//	读了本书的人还看过 过滤		过滤	用户书架
	num = 128;
	ret = filter_cartByName(map2, &(testInfo ->itemRedis), testInfo ->resGuessRec, &num);

	//	读了本书的人还看过 过滤		过滤	禁书 前 5
	num = 5;
	ret = filter_banBook(&(testInfo ->recRedis), testInfo ->resGuessRec, &num);

	//	读了本书的人还看过 过滤		过滤	作者推荐中已推荐的
	ret = filter_resResByName(&(testInfo ->recRedis), testInfo ->resGuessRec, testInfo ->resAuthorRec);


	//	装入书架
	ret = load_bookcaseByName(map3, &(testInfo ->itemRedis), testInfo ->cartInfo);

	//	类别推荐过滤		过滤 与 reqGid	同书名
//	num = 128;
//	ret = filter_bookNameByName(map3, &(testInfo ->itemRedis), testInfo ->requestInfo.iKey, testInfo ->resCartRec, &num);

	//	类别推荐过滤		过滤 与 reqGid	同系列名
//	num = 128;
//	ret = filter_topNameByName(map3, &(testInfo ->itemRedis), testInfo ->requestInfo.iKey, testInfo ->resCartRec, &num);

	//	类别推荐过滤		过滤 用户书架
	num = 128;
	ret = filter_cartByName(map3, &(testInfo ->itemRedis), testInfo ->resCartRec, &num);

	//	类别推荐过滤		过滤 禁书
	num = 128;
	ret = filter_banBook(&(testInfo ->recRedis), testInfo ->resCartRec, &num);

	//	类别推荐过滤		过滤 作者推荐中已推荐
	ret = filter_resResByName(&(testInfo ->recRedis), testInfo ->resCartRec, testInfo ->resAuthorRec);

	//	类别推荐过滤		过滤 看了又中已推荐
	ret = filter_resResByName(&(testInfo ->recRedis), testInfo ->resCartRec, testInfo ->resGuessRec);

	return OK;
}

int	test_301_result(sTestInfo* testInfo)
{
	if(NULL == testInfo)
	{
		return ERROR;
	}

	int			ret = 0;
	int			authorRet = 0;
	int			cartRet = 0;
	int			guessRet = 0;

	//	获取与解析服务端数据
	ret = bkRec_sendAndGet(&(testInfo ->requestInfo), testInfo ->bkResAuthorRec, testInfo ->bkResCartRec, testInfo ->bkResGuessRec);
	if(OK != ret)
	{
		return ERROR;
	}

	//	结果比较	作者推荐比较
	authorRet = bkRec_compRes_equal(testInfo ->resAuthorRec, testInfo ->bkResAuthorRec);
	
	//	结果比较	类别推荐比较
	cartRet = bkRec_compRes_contain(testInfo ->resCartRec, testInfo ->bkResCartRec);

	//	结果比较	读本书的人还看过比较
	guessRet = bkRec_compRes_equal(testInfo ->resGuessRec, testInfo ->bkResGuessRec);


	if((OK == authorRet) && (OK == cartRet) && (OK == guessRet))
	{
		return OK;
	}

	return ERROR;
}


























