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
using namespace std;

class Account {
	
	private:
        //MEMBER VARIABLES
		string accountName;
		string userName;
		string password;
		time_t genTime;
		int ignore;
        int securityLevel;                   //1 being the lowest and 3 being the highest,
                                             //chosen by  user in user story #5 for system
                                             //generated password.  0 meaning
                                             //it has NOT been pre-determined and user manually
                                             //created password
        char* dateCreated;

	public:
        //CONSTRUCTORS
		Account();
        Account(string, string, int);        //dateCreated will be set within this constructor
		
		/*
        **GET METHODS
        */
		string getAccountName();
		string getUserName();
		string getPassword();
        int getSecurityLevel();
		int getPwAge();

        /*
        **SET METHODS
        */
		void setAccountName(string);
		void setUserName(string);
        void setSecurityLevel(int);
		void setPassword(string);
		void setgenTime(int);
		void setPwAge(int);
		void setIgnore();
		int verifyPassword(string);
		int verifyPwAge();

        /*
		**OVERLOAD OPERATOR
		*/
        friend bool operator==(Account , Account);

};

#endif
