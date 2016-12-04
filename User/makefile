CC = g++ -std=c++11
LFLAGS = -Wall -g
HDRS =  ../PasswordGenerator/sha256.hpp ../PasswordGenerator/pwGen.hpp ../Account/account.hpp ../catch.hpp User.hpp
SRCS = ../PasswordGenerator/sha256.cpp ../PasswordGenerator/pwGen.cpp ../Account/account.cpp User.cpp
OBJS = sha256.o pwGen.o account.o User.o

all : userTests

userTests: $(OBJS) unitTests.cpp 
	$(CC) $(LFLAGS) $(OBJS) unitTests.cpp -o userTests

$(OBJS): $(SRCS) $(HDRS)
	$(CC) -c ../PasswordGenerator/sha256.cpp
	$(CC) -c ../PasswordGenerator/pwGen.cpp
	$(CC) -c ../Account/account.cpp
	$(CC) -c User.cpp

clean:
	\rm *.o userTests