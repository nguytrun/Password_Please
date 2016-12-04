#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "implement.hpp"
#include "sha256.hpp"
#include "User.hpp"

// TODO: hard code time in on passwords to demonstrate expiration feature

int main() {
	
	// Redirect stdout for now, until main program begins
	int dev_null = open("/dev/null", O_WRONLY);
	int stdOut = dup(STDOUT_FILENO);
	if (dup2(dev_null, STDOUT_FILENO) == -1) 
		perror("Dup2");

	double expireSeconds = 0;

	std::string UserName("testUser"), UserEmail("testUser@gmail.com"), UserPw("ThisIsaTestPa$$word5!");
	User test_user;
	test_user.setUserName(UserName); 
	test_user.setUserEmail(UserEmail);
   	test_user.setUserPw(UserPw);
	
	// Hard code some values
	std::vector<std::string> accountNames{"Gmail", "Facebook", "MSN", "Amazon" };
	std::vector<std::string> accountUsernames{"osu_sadSack22", "socially_n33dy", "news_forIE_users", "monopolyVictim"}; 
	// Now add these into the test user's list of accounts
	for (int i=0; i < accountNames.size(); i++) 
		test_user.createAccount(accountNames[i], accountUsernames[i], (i%3)+1);
	
	// Hardcode time on a few passwords to be expired to demonstrate prompt
	auto &accounts = test_user.getAccounts();	
	auto itr  = accounts.find(accountNames[1]);
	itr->second.setPwAge(expireSeconds);
	itr  = accounts.find(accountNames[3]);
	itr->second.setPwAge(expireSeconds);
	
	// Redirect stdout back to screen
	if (dup2(stdOut, STDOUT_FILENO) == -1) {
		perror("Dup2");
		exit(EXIT_FAILURE);
	}
	
	std::cout << "For testing purposes, we have already created a fake user account populated with "
		<< "accounts. The username is: \"testUser\"  and its password is: \"ThisIsaTestPa$$word55!\" " << std::endl; 

	std::cout << "\nWelcome!\n";

	//Switch to 0 when not testing
	int choice = 0;

	while (choice > 3 || choice < 1) {
		std::cout << "Please select one of the following options:" << std::endl; 
		std::cout << "1. Log in to existing account" << std::endl;
		std::cout << "2. Create a new account" << std::endl;
		std::cout << "3. Exit the application" << std::endl;

		choice = getNumIn();
	}

	int loggedIn;
	switch(choice) {
		case 1:
			loggedIn = logIn(test_user);
			if (loggedIn) 
				mainMenu(test_user);
			break;
		case 2: {
			User user = createUserAccount();
			mainMenu(user);
				}
			break;
		
		default:
			std::cout << "Exiting the application..." << std::endl;
	}

	return 0;
}
