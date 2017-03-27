#ifndef	_TEST_BOOK_INFO_H_
#define	_TEST_BOOK_INFO_H_

/**
 *	功能: 推荐过程中用到的四类型表
 *		1、物品信息
 *		2、物品协同
 *		3、用户协同
 *		4、流行度表
 *
 *uthor	作者: 	丁敬
 *	时间:	2017年3月21日09:41:50
 */

#ifdef __cplusplus
extern "C"{
#endif

//	书籍信息
typedef struct _sBookInfo
{
	//key 9 bit example i_000000001
	char				iKey[24];
	//raw_name
	char				raw_name[40];
	//norm_name
	char				norm_name[40];
	//top_name
	char				top_name[40];
	//raw_author
	char				raw_author[40];
	//norm_author
	char				norm_author[40];
	//Book_icon
	char				item_icon[128];
	//Book_rank
	unsigned short		item_rank;
	//view_count
	unsigned int		view_count;
	//mask_level	是否是禁书
	unsigned short		mask_level;
}sBookInfo;


typedef struct _sKeyAndWeight
{
	char*				recommend[1024];
	unsigned int		weight[1024];
}sKeyAndWeight;

//	物品协同推荐信息
typedef struct _sItemRecom
{
	//key 9 bit example i_000000001
	char				iKey[24];
	sKeyAndWeight		test_method1;		//	同作者
	sKeyAndWeight		test_method2;		//	同分类
	sKeyAndWeight		icf_knn3;
	sKeyAndWeight		icf_knn;
}sItemRec;


//	用户协同推荐信息
typedef struct _sCustomRecom
{
	//key 9 bit example i_000000001
	char				uKey[24];
	sKeyAndWeight		cart_item;
	sKeyAndWeight		ucf_knn3;
	sKeyAndWeight		ucf_knn;
}sCustomRec;

//	流行度推荐信息
typedef struct _sPopRecom
{
	char				pKey[24];
	sKeyAndWeight		popList;

}sPopRec;

#ifdef __cplusplus
}
#endif

#endif










