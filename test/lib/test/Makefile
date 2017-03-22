CC=gcc
CPP=g++

CFLAGS = -Wall

LDFLAGS = -lm

HEAD= -I ../				\
		-I ../lib/json/		\
		-I ../lib/hiredis/	

TARGET = log_test json_test	redis_test	http_test

log_test_obj = ./log_test.o

json_test_obj = ./json_test.o				\
				../test_json_op.o			\
				../lib/json/cJSON.o

redis_test_obj = ./redis_test.o				\
				 ../test_redis_op.o			\
				 ../lib/hiredis/hiredis.o	\
				 ../lib/hiredis/async.o		\
				 ../lib/hiredis/read.o		\
				 ../lib/hiredis/net.o		\
				 ../lib/hiredis/sds.o

http_test_obj = ./http_test.o				\
				../test_http_op.o


all : $(TARGET)


# 测试 log
log_test : $(log_test_obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(HEAD)

# 测试 json
json_test : $(json_test_obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(HEAD)

# 测试 redis 
redis_test : $(redis_test_obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(HEAD)

# 测试 socket 
http_test : $(http_test_obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(HEAD)







# 依赖
%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(HEAD)

%.o : %.cpp
	$(CPP) -c $(CFLAGS) $< -o $@ $(HEAD)

.PHONY : clean
clean:
	rm -rf $(log_test_obj) $(json_test_obj) $(redis_test_obj) $(http_test_obj)
	rm -rf $(TARGET)
