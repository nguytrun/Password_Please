#include <string>
#include <ctime>
#ifndef PW_H
#define PW_H

struct password {
	std::string password_key;
	std::string password_hash;
	time_t genDate;
};

std::string pwGen(const int pwLength);

struct password pwGen_Wrapper(const char* input, int& valid_arg);

#endif 

