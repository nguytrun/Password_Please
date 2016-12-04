CC = g++ -std=c++11
LFLAGS = -Wall -g
HDRS =  sha256.hpp pwGen.hpp ../catch.hpp
SRCS = sha256.cpp pwGen.cpp
OBJS = sha256.o pwGen.o

all : pwGenTests

pwGenTests: $(OBJS) unitTests.cpp 
	$(CC) $(LFLAGS) $(OBJS) unitTests.cpp -o pwGenTests

$(OBJS): $(SRCS) $(HDRS)
	$(CC) -c $(@:.o=.cpp)

clean:
	\rm *.o pwGenTests
