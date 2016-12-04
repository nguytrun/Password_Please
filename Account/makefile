all: cart unittest

cart: accountMain.o account.o
	g++ --std=c++11 ../PasswordGenerator/sha256.cpp ../PasswordGenerator/pwGen.cpp accountMain.o account.o -o account

unittest: account.cpp unitTests.cpp
	g++ --std=c++11 account.cpp ../User/User.cpp ../PasswordGenerator/pwGen.cpp ../PasswordGenerator/sha256.cpp unitTests.cpp -o accountUnitTest

accountMain.o: accountMain.cpp
	g++ --std=c++11 -c accountMain.cpp

account.o: account.cpp account.hpp
	g++ --std=c++11 -c account.cpp

clean:
	rm *.o account
