GTEST_DIR = ./

USER_DIR = ./test/

CC = gcc

CPP = g++

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

CHEAD = -I $(USER_DIR)/lib/lib/json/					\
		-I $(USER_DIR)/lib/lib/hiredis/					\
		-I $(USER_DIR)/lib/

CLIBS = -lm

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


TARGET = recom_test

REPLY_BASE = $(USER_DIR)/lib/test_http_op.o				\
			 $(USER_DIR)/lib/test_json_op.o				\
			 $(USER_DIR)/lib/test_log_op.o				\
			 $(USER_DIR)/lib/test_redis_op.o			\
			 $(USER_DIR)/lib/lib/json/cJSON.o			\
			 $(USER_DIR)/lib/lib/hiredis/hiredis.o		\
			 $(USER_DIR)/lib/lib/hiredis/net.o			\
			 $(USER_DIR)/lib/lib/hiredis/read.o			\
			 $(USER_DIR)/lib/lib/hiredis/sds.o			\
			 $(USER_DIR)/lib/lib/hiredis/async.o	

RECOM_TEST_OBJ = $(USER_DIR)/src/main.o					\
				 $(USER_DIR)/src/gtest.a				\
				 $(USER_DIR)/src/test_301.o				\
				 $(USER_DIR)/src/test_push.o			\


#all : $(TARGET)



recom_test : $(RECOM_TEST_OBJ) $(REPLY_BASE)
	$(CPP) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(CHEAD)



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
	rm -fr $(TARGET) $(GTEST_DIR)*.o $(RECOM_TEST_OBJ) $(REPLY_BASE)	



