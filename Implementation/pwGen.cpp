/************************************************************************
 * Implementation file of password generator
 * **********************************************************************/
#include "pwGen.hpp"
#include "sha256.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <random>

/* *****************************************************************************************
 * pwGen
 * Purpose: Generate a  password of variable length
 * Input: Integer specifying length of password to be generated
 * Output: 10-digit string of randomly generated characters between decimal values 33 and 126
 * ****************************************************************************************/ 
std::string pwGen(const int pwLength) {

	std::string password;
	// Range of valid characters for the password
	std::uniform_int_distribution<int> range_of_chars(33, 126);
	// Use truly random, slower-generating device
	std::random_device rng("/dev/urandom");
	std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i=0; i<pwLength; i++) {
		char letter = (char)range_of_chars(rng) ;
		password += letter;
	}

	// Ensure password policies
	if(password.length() >= 15) {
		std::uniform_int_distribution<int> insertPosition(0, password.length());
		int upperPos,
			symbolPos,
			digitPos;
		if(!std::any_of(password.begin(), password.end(), isupper)) {
			std::uniform_int_distribution<int> upperChars(65,90);
			char char_to_insert = upperChars(rng);
			upperPos = insertPosition(rng);
			password[upperPos] = char_to_insert;
		}
		if(!std::any_of(password.begin(), password.end(), isdigit)) {
			std::uniform_int_distribution<int> digits(0,9);
			char digit = (char)digits(rng);
			do {
				digitPos = insertPosition(rng);
			} while (digitPos != upperPos);
			password[digitPos] = digit;
		}
		if(!(password.find_first_not_of(alpha) != std::string::npos) ) {
			//Determine which set of symbols to draw from:
			// 33-47, 58-64, 91-96, 123-126
			std::uniform_int_distribution<int> first_set(33,47); 
		    std::uniform_int_distribution<int> second_set(58,64); 
		    std::uniform_int_distribution<int> third_set(91,96); 
		    std::uniform_int_distribution<int> fourth_set(123-126);
			std::uniform_int_distribution<int> choice(0,3);
			int chosen_set = choice(rng);
			char symbol;
			switch(chosen_set) {
				case 0:
					symbol = (char)first_set(rng);
					break;
				case 1:
					symbol = (char)second_set(rng);
					break;
				case 2:
					symbol = (char)third_set(rng);
					break;
				case 3:
					symbol = (char)fourth_set(rng);
					break;
				}
			// Ensure it doesn't overwrite a unique uppercase or digit position
			do {
				 symbolPos = insertPosition(rng);
			} while ( (symbolPos != upperPos) && (symbolPos != digitPos) );
			password[symbolPos] = symbol;
		}

	}

	return password;
}

/* *****************************************************************************************
 * pwGen_Wrapper
 * Purpose: Returns a password struct full of a newly generated password,
 * its hash, and its time created
 * Input: Security Level, reference to int
 * Output: Password struct, int reference indicating success or failure
 * ****************************************************************************************/ 
struct password pwGen_Wrapper(const char* sec_level, int& invalid) {

	struct password pw;
	invalid = 0;
	
	// Convert std::string to c-string for case conversion
	//const char *sec_cstring = sec_level.c_str();
	std::string sec_levels[] = {"low", "medium", "high"};
	std::string sec_choice;
	int pw_length[] = {10, 15, 20};
	int security_level;
	int equal = 0;

	for (int i=0; i < strlen(sec_level); i++)
		sec_choice += tolower(sec_level[i]);
	
	
	// Ensure command line argument was one of "low", "medium" or "high"
	for (int j=0; j < 3; j++) {
		if (!sec_choice.compare(sec_levels[j])) { // Means strings are equal
			security_level = pw_length[j];
			equal = 1;
		}
	}

	// If arguments are invalid
	if (!equal) {
		std::cerr << "Please specify a valid security level: {low, medium, high}" << std::endl;
		invalid = 1;
		return pw;
	}

	// Generate the password
	pw.password_key = pwGen(security_level);
	// Generate a SHA256 hash
	pw.password_hash = sha256(pw.password_key);

	// Get date of password generation for use in Password Expiration function
	pw.genDate = time(NULL); 

	return pw;

}
