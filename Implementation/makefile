CC = g++ -std=c++11
HDRS =  sha256.hpp pwGen.hpp account.hpp User.hpp implement.hpp
SRCS = sha256.cpp pwGen.cpp account.cpp User.cpp implement.cpp
OBJS = sha256.o pwGen.o account.o User.o implement.o

all: main
	
main: $(OBJS) main.cpp
	$(CC) $(OBJS) main.cpp -o pwPlease

$(OBJS): $(SRCS) $(HDRS)
	$(CC) -c $(@:.o=.cpp)

clean:
	rm *.o pwPlease

