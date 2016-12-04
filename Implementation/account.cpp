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
#include <cmath>

/************************************************************
 **Function:            Account()
 **Description: Default Constructor
 **Parameters:  None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
Account::Account(): securityLevel(2)
{ }

/************************************************************
 **Function:            Account(std::string, std::string)
 **Description:  Constructor
 **Parameters:  String(Account Name), String(User Name)
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
Account::Account(std::string a, std::string b, int c) {
	
    setAccountName(a);
    setUserName(b);
    setSecurityLevel(c);
}


// Copy constructor
/*
Account::Account(Account &account)
{
	accountName = account.getAccountName();
	accountName = account.getUserName();
	pw = account.getPwStruct();
	securityLevel = account.getSecurityLevel();
}
*/

/* Function: operator=(const User &user)
 * Param user: Constant reference to Account object to be copied
 * Description: Overloaded assignment operator for the account class.
 */
/*
Account& Account::operator=(Account &account)
{
	accountName = account.getAccountName();
	userName = account.getUserName();
	securityLevel = account.getSecurityLevel();
	pw = account.getPwStruct();

	return *this;
}
*/

/************************************************************
 **Function:            getAccountName()
 **Description:  Returns Account Name
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
std::string Account::getAccountName()  {

	return accountName;

}

/************************************************************
 **Function:            getUserName()
 **Description:  Returns User Name
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
std::string Account::getUserName()  {

	return userName;

}

/************************************************************
 **Function:            getSecurityLevel()
 **Description:  Returns Security Level
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
int Account::getSecurityLevel()  {
    
    return securityLevel;
    
}

/************************************************************
 **Function:            getSecLvlStr()
 **Description:  Returns String "low", "medium", or ""high"
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
std::string Account::getSecLvlStr() {
    int secLevel = getSecurityLevel();
	std::string secLvlStr;
	switch(secLevel) {
		case 1:
			secLvlStr = "low";
			break;
		case 2:
			secLvlStr = "medium";
			break;
		case 3:
			secLvlStr = "high";
			break;

		default:
			secLvlStr = "ERROR: Invalid Security Level";
	}

	return secLvlStr;

    
    
}

/************************************************************
 **Function:            getPwStruct() 
 **Description:  Returns entire password struct
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
struct password Account::getPwStruct()  { return pw; }

/************************************************************
 **Function:            getPassword()
 **Description:  Returns current password
 **Parameters:   None
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
std::string Account::getPassword() {

	return pw.password_key;

}

/* Function: getPasswordPolicy
 * Return: the password policy
 * Description: Returns the password policy for the currently selected security
 * level.
 */
void Account::getPasswordPolicy()
{
	int curSecLvl = getSecurityLevel();
	switch(curSecLvl)
	{
		case 1:
			// The password must be at least 10 characters long
			std::cout << "- Must be at least 10 characters long" << std::endl;
			break;
		case 2:
			// The password must be at least 15 characters long
			// with at least one capital letter and at least one
		 	// number
			std::cout << "- Must be at least 15 characters long" << std::endl;
			std::cout << "- Contain at least one upper case letter" << std::endl;
			std::cout << "- Contain at least one digit" << std::endl;
			break;
		case 3:
			// The password must be at least 20 characters long
			// with at least one capital letter, one digit, and
			// one special character
			std::cout << "- Must be at least 20 characters long" << std::endl;
			std::cout << "- Contain at least one upper case letter" << std::endl;
			std::cout << "- Contain at least one digit" << std::endl;
			std::cout << "- Contain at least one symbol" << std::endl;
			break;
		default:
			std::cout << "ERROR in getPasswordPolicy" << std::endl;
	}
}


/************************************************************
 **Function:            setAccountName(std::string)
 **Description:  Sets std::string to accountName
 **Parameters:   String
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
void Account::setAccountName(std::string s) {

	accountName = s;

}


/************************************************************
 **Function:            setUserName(std::string)
 **Description:  Sets User Name
 **Parameters:   String
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
void Account::setUserName(std::string j) {

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
   	if ( i < 1 || i > 3)
	   std::cout << "Invalid security level. Must be 1, 2, or 3." << std::endl;
	else	
		securityLevel = i;
    
}

/************************************************************
 **Function:            setPassword(std::string)
 **Description:  Calls verifyPassword() within method, before
 **assigning password a std::string value
 **Parameters:   Int
 **Pre-Conditions:  N/A
 **Post-Conditions: N/A
 ***********************************************************/
void Account::setPassword(std::string d) {
    
    int pass;               //true/false variable
    pass = verifyPassword(d);
    if(pass)
    {
        pw.password_key = d;
        std::cout << "Congratulations, you set a new password!" << std::endl;
		pw.genDate = time(0);

    }
    else
    {
        std::cout << "Password " << d << " did not pass verification and";
        std::cout << " could not be set!" << std::endl;
    }
    
}

/************************************************************
 **Function:            setPassword()
 **Description:  Function overload if user wants to automatically
** generate a password.
 **assigning password a std::string value
 **Parameters:   Valid security level (from 1-3)
 **Pre-Conditions:  N/A
 **Post-Conditions: Password members set
 ***********************************************************/
void Account::setPassword() {
	int invalid = 0;

	if(getSecurityLevel() > 0 && getSecurityLevel() < 4) {
		pw = pwGen_Wrapper(getSecLvlStr().c_str(), invalid);
		std::cout << "Your new (or default) password for this account is: " << pw.password_key << std::endl;
		pw.genDate = time(0);
		}
	else std::cout << "Invalid security level" << std::endl;
}

// *Note: Changing this function to instead determine whether an inputted password is valid or not,
// rather than taking a password as is and assigning it a security level.

/************************************************************
 **Function:            verifyPassword(std::string)
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
/*
int Account::verifyPassword(std::string a) {
    
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
*/

/*********************************************************
 * Function:		verifyPassword(std::string)
 * Description: Ensure user password conforms to criteria
 * for the given security level they desire.
 * Parameters: std::string they desire for their password
 * Pre-Conditions: Valid security level (from 1-3)
 * Post-Conditions: N/A
 * ******************************************************/
int Account::verifyPassword(std::string password)
{
	std::string alphanumeric = 
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	int curSecLvl = getSecurityLevel();
	switch(curSecLvl)
	{
		case 1:
			// The password must be at least 10 characters long
			if(password.length() >= 10)
				return 1;
			break;

		case 2:
			// The password must be at least 15 characters long
			// with at least one capital letter and at least one
		 	// number
			if(password.length() >= 15)
			{
				// Must contain one capital letter
				if(password.find_first_of(alphanumeric.substr(26,26)) != 
					 std::string::npos)
				{
					// Must contain one digit
					if(password.find_first_of(alphanumeric.substr(52,10)) !=
					   std::string::npos)
						return 1;
				}
			}
			break;

		case 3:
			// The password must be at least 20 characters long
			// with at least one capital letter, one digit, and
			// one special character

			if(password.length() >= 20)
			{
				// Must contain captial letter
				if(password.find_first_of(alphanumeric.substr(26,26)) != 
					 std::string::npos)
				{
					// Must contain one digit
					if(password.find_first_of(alphanumeric.substr(52,10)) !=
					   std::string::npos)
					{
						if(password.find_first_not_of(alphanumeric) != std::string::npos)
							return 1;
					}
				}
			}
			break;

		default:
			std::cout << "ERROR in verifyPassword" << std::endl;
	}

	return 0;
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

/************************************************************
 **Function:            getPwTimeCreated()
 **Description:  Returns # of seconds elapsed from epoch until 
 **password was created.
 **Parameters:   N/A
 **Pre-Conditions:  Password Created
 **Post-Conditions: N/A
 ***********************************************************/
time_t Account::getPwTimeCreated() { return pw.genDate; }

/************************************************************
 **Function:            getPwAge()
 **Description:  Returns # of days elapsed since password 
 **creation.
 **Parameters:   N/A
 **Pre-Conditions:  Password Created
 **Post-Conditions: N/A
 ***********************************************************/
int Account::getPwAge() {
	int days_elapsed;
	double seconds_elapsed;
	time_t now = time(NULL);
	seconds_elapsed = difftime(now, getPwTimeCreated());
	// Concvert seconds to days
	days_elapsed = (int)floor( ( (seconds_elapsed / 60.0) / 60.0) / 24.0);
}


void Account::setPwAge(double numSeconds) {
	pw.genDate = numSeconds;
}

