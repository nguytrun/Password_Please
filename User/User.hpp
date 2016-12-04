/******************************************************************************
* C++ Header file for User class
* rev. A
*
* This file declares the member variables, getter/setter methods, and utility
* methods for the User class.
******************************************************************************/

// Library includes
#include <string>
#include <map>

// Application includes
#include "../Account/account.hpp"

#ifndef USER_HPP
#define USER_HPP

class Account;

class User
{
public:
	// Constructor, copy constructor, overloaded assignment operator
	// and destructor
	User();
	User(const User&);
	User& operator=(const User &user);
	~User();

	// security level enum definition and security level
	// getters/setters
	enum sec_level_type{LOW=1, MEDIUM=2, HIGH=3};
	sec_level_type getSecLvl() const;
	std::string getSecLvlString() const;
	void setSecLvl(const int);

	// userName member variable getter/setter
	std::string getUserName() const;
	void setUserName(std::string&);

	// userEmail getter/setter
	std::string getUserEmail() const;
	void setUserEmail(std::string&);

	// userPassword getter and setters: only the hash should ever be
	// be retrieved IAW current best security practices
	std::string getUserPwHash() const;
	void setUserPw(std::string);
	void setUserPw(); // Overloaded setter calls password generator
	bool validateUserPw(std::string);

	// Returns the password policy for the currently selected security level
	void getPasswordPolicy();

	
	// Need help w/ this function - when trying to compile I get the following: 
	std::map<std::string, Account>& getAccounts();
	std::map<std::string, Account> getAccounts() const;
	void createAccount(const std::string&, const std::string&,
										 const std::string&, const int&);
	// Overload if user does not specify a password - will auto-generate one based on security level
	void createAccount(const std::string&, const std::string&,
										 const int&);
	void deleteAccount(const std::string&);
	// Prompt if any account passwords are > 120 days
	void checkAccountPasswords();

	void displayAccounts();
	
private:
	std::map<std::string, Account> accounts;
	std::string userName;
	std::string userEmail;
	std::string hashedUserPassword;
	sec_level_type sec_level;

	// Private methods for username and password validation,
	// only called within user class.
	bool validateUserEmail(const std::string&);
	bool validateUserName(const std::string&);
};

#endif





