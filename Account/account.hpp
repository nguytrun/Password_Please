/***********************************************************
**CLASS:            ACCOUNT
**
**DESCRIPTION:      HPP FILE
**
**Has data elements for the following
**information:  account name, username, password, date
**created for account
***********************************************************/

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include "../PasswordGenerator/pwGen.hpp"
#include "../PasswordGenerator/sha256.hpp"

//using namespace std;

class Account {
	
	private:
        //MEMBER VARIABLES
		std::string accountName;
		std::string userName;
		struct password pw;
        int securityLevel;                   //1 being the lowest and 3 being the highest,
                                             //chosen by  user in user story #5 for system
                                             //generated password.  0 meaning
                                             //it has NOT been pre-determined and user manually
                                             //created password
        char* dateCreated;

	public:
        //CONSTRUCTORS
		Account();
        Account(std::string, std::string, int optional=2);        //dateCreated will be set within this constructor
		
		//Account( Account&);
		//Account& operator=( Account&);
		
		/*
        **GET METHODS
        */
		std::string getAccountName();
		std::string getUserName();
		std::string getPassword();
		struct password getPwStruct();
        int getSecurityLevel();
		std::string getSecLvlStr();
		time_t getPwTimeCreated();
		int getPwAge();
		void getPasswordPolicy();

        /*
        **SET METHODS
        */
		void setAccountName(std::string);
		void setUserName(std::string);
        void setSecurityLevel(int);
		void setPassword(std::string);
		void setPassword();
		int verifyPassword(std::string);
		//Strictly for demonstration purposes:
		void setPwAge(double);

        /*
		**OVERLOAD OPERATOR
		*/
        friend bool operator==(Account , Account);

};

#endif
