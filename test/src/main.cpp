#include <iostream>
#include <stdio.h>
#include "gtest/gtest.h"

extern "C"
{
	#include "test_301.h"
}

//	声明变量;
sTestInfo*	testInfo = (sTestInfo*)malloc(sizeof(sTestInfo));

//	301 测试
TEST(fore_book_test_301, init_data)
{
	EXPECT_EQ(OK, test_301_init(testInfo)) ;
}

TEST(fore_book_test_301, padding_data)
{
	EXPECT_EQ(OK, test_301_pad(testInfo));
}


GTEST_API_ int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	system("clear");
	puts("\n\n");
	std::cout << "\t\t自动化测试开始..." << std::endl;
	puts("\n");
	sleep(1);
	

















	return RUN_ALL_TESTS();
}
