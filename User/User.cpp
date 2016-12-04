/******************************************************************************
* User class implementation file
******************************************************************************/

// Library includes (some reincluded of explicitness)
#include <algorithm>
#include <iostream>
#include <map>
#include <string>


// Class header file includes
#include "User.hpp"

// Application includes
#include "../PasswordGenerator/pwGen.hpp"
#include "../PasswordGenerator/sha256.hpp"
#include "../Account/account.hpp" 

/* Function: User()
 * Description: Constructor for the User class; initializes all values so that
 * they may be initialized elswhere by the appplication. The default security
 * level is set to medium.
 */
User::User() : sec_level(MEDIUM)
{ }

/* Function: User(const User &user)
 * Param user: Constant reference to User object to be coppied
 * Description: Copy constructor for the user class.
 */
User::User(const User &user)
{
	userName = user.getUserName();
	userEmail = user.getUserEmail();
	hashedUserPassword = user.getUserPwHash();
	sec_level = user.getSecLvl();
	accounts = user.getAccounts();
	
}

/* Function: operator=(const User &user)
 * Param user: Constant reference to User object to be copied
 * Description: Overloaded assignment operator for the user class.
 */
User& User::operator=(const User &user)
{
	userName = user.getUserName();
	userEmail = user.getUserEmail();
	hashedUserPassword = user.getUserPwHash();
	sec_level = user.getSecLvl();
	accounts = user.getAccounts();

	return *this;
}

/* Function: ~User()
 * Description: Destructor for dynamically allocated members of the
 * User class.
 */
User::~User()
{
	// This method is empty
}

/* Function: getSecLvl
 * Return: the enum value of the currently selected user security level
 * Description: Returns the const enum value of the security level. This method
 * is used when the security level is retrieved internal and not to be
 * displayed to the user
 */
User::sec_level_type User::getSecLvl() const { return sec_level; }

/* Function: gteSecLvlString()
 * Return: the string value of the currently selected security level
 * Description: Returns the value of the currently selected user security level
 * as a string
 */
std::string User::getSecLvlString() const
{
	sec_level_type curSecLvl = getSecLvl();
	switch (curSecLvl)
	{
		case LOW:
			return "low";
			break;
		case MEDIUM:
			return "medium";
			break;
		case HIGH:
			return "high";
			break;
		default:
			return "ERROR";
	}
}

/* Function: setSecLvl
 * Param sec_level: the security level that the user has selected
 * Description: Sets the object's security level to the level specified by the 
 * user
 */
void User::setSecLvl(const int secLvl)
{
	sec_level = static_cast<sec_level_type>(secLvl);
}

/* Function: getUserName
 * Description: returns the username of the user.
 */
std::string User::getUserName() const { return userName; }

/* Function: setUserName
 * Param userNameIn
 * Description: Checks that the passed userName is unique by calling 
 * verifyUserName set the userName member variable to the passed string
 */
void User::setUserName(std::string &userNameIn)
{
	while(!validateUserName(userNameIn))
	{
		//TODO: this should eventually be sent to somewhere other than stdout
		std::cout << "*That username is taken. Please choose another one: ";
		std::cin >> userNameIn;
	}

	userName = userNameIn;
}

/* Function: getUserEmail
 * Return: the user's email
 * Description: Return's the user's email 
 */
std::string User::getUserEmail() const
{
	return userEmail;
}

/* Function: setUserEmail
 * Param email: the email that userEmail is to be set to
 * Description: Calls validateEmail to make sure email is a valid email
 * and sets the userEmail member variable
 */
void User::setUserEmail(std::string &email)
{
	while(!validateUserEmail(email))
	{
		std::cout << "*That doesn't look like an email. Please try a different one: ";
		std::cin >> email;
	}

	userEmail = email;
}

/* Function: getUserPwHash
 * Return: the hashed password associated with this user account
 * Description: Returns the hashed user password associated with the user account
 */
std::string User::getUserPwHash() const
{
	return hashedUserPassword;
}

/* Function: setUserPw(std::string&)
 * Param password: The string that will be used to create the hashed user password
 * Description: Calls validate password to ensure that the desired password 
 * conforms to the policy defined by the currently selected security level. Then
 * hashes the string passed using SHA256 hashing and sets the hashedUserPassword.
 */
void User::setUserPw(std::string password)
{
	while(!validateUserPw(password))
	{
		std::cout << "*Invalid password. Try again." << std::endl;
		std::cout << "Your password must: " << std::endl;
		getPasswordPolicy();
		std::cout << "Enter New Password: ";
		std::cin >> password;
	}

	hashedUserPassword = sha256(password);
}

/* Function: setUserPw()
 * Description: Overloaded setter method Takes the current selected security
 * level and uses the password generator to generate a new password and sets
 * the hashedUserPassword.
 */
void User::setUserPw()
{
	int valid = 0;

	password pwStruct;

	if(getSecLvl() > 0)
		pwStruct = pwGen_Wrapper(getSecLvlString().c_str(), valid);
	else
		pwStruct = pwGen_Wrapper("low", valid);

	// Since this password will not be stored in the User class, customer must 
	// have it displayed to them at least once. 
	std::cout << "Your new password is: " << pwStruct.password_key << std::endl;

	hashedUserPassword = pwStruct.password_hash;
}

/* Function: getPasswordPolicy
 * Return: the password policy
 * Description: Returns the password policy for the currently selected security
 * level.
 */
void User::getPasswordPolicy()
{
	sec_level_type curSecLvl = getSecLvl();
	switch(getSecLvl())
	{
		case LOW:
			// The password must be at least 10 characters long
			std::cout << "- Must be at least 10 characters long" << std::endl;
			break;
		case MEDIUM:
			// The password must be at least 15 characters long
			// with at least one capital letter and at least one
		 	// number
			std::cout << "- Must be at least 15 characters long" << std::endl;
			std::cout << "- Contain at least one upper case letter" << std::endl;
			std::cout << "- Contain at least one digit" << std::endl;
			break;
		case HIGH:
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

/* Function: getAccounts
 * Return: A vector of pointers to accounts
 * Description: Returns a reference to the vector holding all accounts
 * associated with the user.
 */
std::map<std::string, Account>& User::getAccounts() 
{
	return accounts;
}

std::map<std::string, Account> User::getAccounts() const 
{
	return accounts;
}

/* Function: createAccount
 * Return: returns the account that was created
 * Description: Dynamically create a new account with user input information
 * and put it in the accounts vector
 */
void User::createAccount(const std::string &accName, const std::string &accUserName, 
												 const std::string &accPsswd, const int& scLvl)
{
	Account newAccount = Account(accName, accUserName, scLvl);

	// set the account password
	newAccount.setPassword(accPsswd);

	// insert the new account into the accounts set.
	// If an identical account already exists in the set, the insert will be 
	// rejected
	auto accPair = std::make_pair(accName, newAccount);
	auto inserted = accounts.insert(accPair); 
	//std::pair<std::string, Account> accPair = std::make_pair(accName, newAccount);
	//std::pair<std::map<std::string, Account>::iterator, bool>inserted = accounts.insert(accPair); 

	if(!inserted.second)
	{	
		std::cout << "An identical account already exists. " << 
								 "Create account failed" << std::endl;
	}
}

/* Function: createAccount 
 * Return: returns the account that was created
 * Description: Overload to dynamically create a new account with user input information
 * and put std::it in the accounts vector, used if password not supplied
 */
void User::createAccount(const std::string &accName, const std::string &accUserName, 
												 const int& scLvl)
{
	Account newAccount = Account(accName, accUserName, scLvl);

	// set the account password
	newAccount.setPassword();

	// insert the new account into the accounts set.
	// If an identical account already exists in the set, the insert will be 
	// rejected
	auto accPair = std::make_pair(accName, newAccount);
	auto inserted = accounts.insert(accPair); 
	//std::pair<std::string, Account> accPair = std::make_pair(accName, newAccount);
	//std::pair<std::map<std::string, Account>::iterator, bool>inserted = accounts.insert(accPair); 

	if(!inserted.second)
	{	
		std::cout << "An identical account already exists. " << 
								 "Create account failed" << std::endl;
	}
}

/* Function: deleteAccount
 * Return: returns the account object, with the specified element removed
 * Description: Takes a string of the account name to delete from the account object
 */
void User::deleteAccount(const std::string& accountName) { 
	// If erase() returns 0, this means it did not remove an element
	if (!accounts.erase(accountName))
		std::cout << accountName << " could not be removed." << std::endl;
	else
		std::cout << accountName << " removed from the your accounts." << std::endl;
}

/* Function: checkAccountPasswords
 * Returns: none
 * Description: Prints to std-O series of messages if any 
 * account passwords exceed 120 days in length.
 * */
void User::checkAccountPasswords() {
	std::map<std::string, Account>::iterator accountsItr = accounts.begin();
	for (; accountsItr != accounts.end(); ++accountsItr) {
 		if (accountsItr->second.getPwAge() > 120) {
  			std::cout << "Password for Account: " << accountsItr->second.getAccountName()
		  << " has expired.\nIt is recommended to change it." << std::endl;
			std::cout << "============================================================" << std::endl;
		}
	}

}

/* Function: displayAccounts
 * Returns: none
 * Description: Iterates through User accounts, listing the account names, usernames, and passwords associated
 */
void User::displayAccounts() {
	
	if (accounts.empty()) 
		std::cout << "No accounts to display!" << std::endl;
	else {
		std::map<std::string, Account>::iterator accountsItr = accounts.begin();
		std::cout << "======================================\n";
			for (; accountsItr != accounts.end(); ++accountsItr) {
					std::cout << "Account: " << accountsItr->first << std::endl;
					std::cout << "Username: " << accountsItr->second.getUserName() << std::endl;
					std::cout << "Password: " << accountsItr->second.getPassword() << std::endl;
					std::cout << "======================================\n";
			}
	}
}

/* Function: validateUserEmail
 * Param email: the email string to be tested
 * Return: boolean pass/fail
 * Description: Make sure that the string passed follows the standard format for an
 * email (ie has an @symbol and at least one '.' after the @)
 */
bool User::validateUserEmail(const std::string &email)
{
	// Test if the string contains '@' and that it's not the first character
	int atPos = email.find("@");
	if(atPos > 0)
	{
		// Test if the string contains at least one '.' after the '@'
		if(email.find(".", atPos) != std::string::npos)
			return 1;
	}

	return 0;
}

/* Function: validateUesrName
 * Param userName: the string userName to be tested
 * Return: bool pass/fail
 * Description: checks to make sure that the username does not already exist
 */
bool User::validateUserName(const std::string &userName)
{
	// TODO: Create an object set template class and a userNames
	// typedef to that class. 
	
	return 1;
}

/* Function: validateUserPw
 * Param password: the password string to be tested
 * Return: bool pass/fail
 * Description: Checks the passed string against the password policy of
 * the currently selected security level.
 */
bool User::validateUserPw(std::string password)
{
	std::string alphanumeric = 
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	sec_level_type curSecLvl = getSecLvl();
	switch(curSecLvl)
	{
		case LOW:
			// The password must be at least 10 characters long
			if(password.length() >= 10)
				return 1;
			break;

		case MEDIUM:
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

		case HIGH:
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
			std::cout << "ERROR in validateUserPw" << std::endl;
	}

	return 0;
}
