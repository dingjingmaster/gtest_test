GTEST_DIR = ./

USER_DIR = ./test/

TEST_MODE = $(USER_DIR)/lib/test/

CC = gcc

CPP = g++

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h 				\
                $(GTEST_DIR)/include/gtest/internal/*.h

CHEAD = -I $(USER_DIR)/lib/lib/json/						\
		-I $(USER_DIR)/lib/lib/hiredis/						\
		-I $(USER_DIR)/lib/									\
		-I $(USER_DIR)/src/Model/							\
		-I $(USER_DIR)/src/

CLIBS = -lm

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


TARGET = recom_test model_test

REPLY_BASE = $(USER_DIR)/lib/test_http_op.o					\
			 $(USER_DIR)/lib/test_json_op.o					\
			 $(USER_DIR)/lib/test_log_op.o					\
			 $(USER_DIR)/lib/test_redis_op.o				\
			 $(USER_DIR)/lib/lib/json/cJSON.o				\
			 $(USER_DIR)/lib/lib/hiredis/hiredis.o			\
			 $(USER_DIR)/lib/lib/hiredis/net.o				\
			 $(USER_DIR)/lib/lib/hiredis/read.o				\
			 $(USER_DIR)/lib/lib/hiredis/sds.o				\
			 $(USER_DIR)/lib/lib/hiredis/async.o			\
			 $(USER_DIR)/src/Model/test_filter.o			\
			 $(USER_DIR)/src/Model/test_pushAndPull.o		\
			 $(USER_DIR)/src/Model/test_print.o				\
			 $(USER_DIR)/src/Model/test_bkRec.o				\
			 $(USER_DIR)/src/gtest.a				


RECOM_TEST_OBJ = $(USER_DIR)/src/main.o						\
				 $(USER_DIR)/src/test_301.o					\


all : $(TARGET)


recom_test : $(RECOM_TEST_OBJ) $(REPLY_BASE)
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(CHEAD)

model_test:
	cd $(TEST_MODE) && make


%.o : %.cpp
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ $(CHEAD)

%.o : %.c
	$(CC) $(CFLAGS)-c $< -o $@ $(CHEAD) $(CLIBS)


gtest-all.o : $(GTEST_SRCS_)
	$(CPP) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

$(USER_DIR)/src/gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^



.PHONY : clean
clean :
	cd $(TEST_MODE) && make clean
	rm -fr $(TARGET)
	rm -fr $(GTEST_DIR)*.o
	rm -fr $(RECOM_TEST_OBJ)
	rm -fr $(REPLY_BASE)
	clear



