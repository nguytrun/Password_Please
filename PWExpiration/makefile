CC = g++ -std=c++11
LFLAGS = -Wall -g
HDRS = account.hpp catch.hpp 
SRCS = account.cpp 
OBJS = account.o

all : newtest

newtest: $(OBJS) newtest.cpp 
	$(CC) $(LFLAGS) $(OBJS) newtest.cpp -o newtest


clean:
	\rm *.o newtest