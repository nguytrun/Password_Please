/***********************************************************
 **CLASS:            ACCOUNT
 **
 **DESCRIPTION:      CPP FILE
 **
 **Has data elements for the following
 **information:  account name, username, password, date
 **created for account
 ***********************************************************/

#include "account.hpp"

/************************************************************
 **Function:            Account()
 **Description: Default Constructor
 **Parameters:  None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
Account::Account() {

}


/************************************************************
 **Function:            Account(string, string)
 **Description:  Constructor
 **Parameters:  String(Account Name), String(User Name)
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
Account::Account(string a, string b, int c) {
	
    setAccountName(a);
    setUserName(b);
    setSecurityLevel(c);
	ignore = 0;
}


/************************************************************
 **Function:            getAccountName()
 **Description:  Returns Account Name
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
string Account::getAccountName() {

	return accountName;

}

/************************************************************
 **Function:            getUserName()
 **Description:  Returns User Name
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
string Account::getUserName() {

	return userName;

}

/************************************************************
 **Function:            getSecurityLevel()
 **Description:  Returns Security Level
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
int Account::getSecurityLevel() {
    
    return securityLevel;
    
}

/************************************************************
 **Function:            getPassword()
 **Description:  Returns current password
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
string Account::getPassword() {

	return password;

}


/************************************************************
 **Function:            setAccountName(string)
 **Description:  Sets string to accountName
 **Parameters:   String
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
void Account::setAccountName(string s) {

	accountName = s;

}


/************************************************************
 **Function:            setUserName(string)
 **Description:  Sets User Name
 **Parameters:   String
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
void Account::setUserName(string j) {

	userName = j;

}

/************************************************************
 **Function:            setSecurityLevel(int)
 **Description:  Sets Security Level
 **Parameters:   Int
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
void Account::setSecurityLevel(int i) {
    
    securityLevel = i;
    
}

/************************************************************
 **Function:            setPassword(string)
 **Description:  Calls verifyPassword() within method, before
 **assigning password a string value
 **Parameters:   Int
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
void Account::setPassword(string d) {
  
    int pass;               //true/false variable
    pass = verifyPassword(d);
    if(pass)
    {
        password = d;
		genTime = time(NULL);
		setPwAge(0);
        cout << "Congratulations, you set a new password!" << endl;
    }
    else
    {
        cout << "Password " << d << "did not pass verification &";
        cout << " count not be set!" << endl;
    }
    
}

/************************************************************
 **Function:            verifyPassword(string)
 **Description:  Checks password is acceptable based on 
 **certain level of security.  If securityLevel is already
 **set, then a password was generated from user story #5
 **and it was just assigned to the securityLevel member
 **variable.  If it is not set yet, then the password will 
 **be manually created/added by the user, therefore this
 **method determines what securityLevel should get assigned
 **to the password.  If it passes security level determination
 **between 1-3, it is assigned and 1 is returned.  If not, 0
 **is returned. 
 **Parameters:   Int
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
int Account::verifyPassword(string a) {
    
    if(securityLevel == 1 || securityLevel == 2 || securityLevel == 3)
    {
        return 1;
    }
    else if(islower(a.at(0)) && islower(a.at(1)))
    {
        securityLevel = 1;
        return 1;
    }
    else if(isupper(a.at(0)))
    {
        securityLevel = 2;
        return 1;
    }
    else if(isupper(a.at(0)) && isupper(a.at(1)))
    {
        securityLevel = 3;
        return 1;
    }
    else
    {
        return 0;
    }
}


/************************************************************
 **Function:            operator==()
 **Description:  Overload comparison operator
 **Parameters:   Account object, Account object
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
bool operator==(Account acc1, Account acc2) {

	return(acc1.getAccountName() == acc2.getAccountName() &&
	       acc1.getUserName() == acc2.getUserName());

}
void Account::setIgnore() {
	ignore = 1;  
}

void Account::setPwAge(int x) {
	time_t curTime;
	curTime = time(NULL);
	genTime = curTime - (x*86400);
      
}

int Account::getPwAge() {
	int days;
	time_t curTime;
	curTime = time(NULL);
	days = (curTime-genTime)/86400;
	return days;
	
}

int Account::verifyPwAge() {
	int days;
	time_t curTime;
	curTime = time(NULL);
	days = (curTime-genTime)/86400;
	if (ignore == 0)
	{
		if (days >= 120)
		{
			cout <<  "Password age has exceeded or is equal to 120, please change passwords" << endl;
			return 1;
		
		}
			return 0;
		
	}
	return 0;
}
