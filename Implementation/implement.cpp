/* **********************************************************************
 * Implementation file for functions to be used in main() driver program
 * demonstrating adding, deleting, and editing accounts.
 * TODO: 
 * 		- Write log-in and create account menus/wrappers
 * 		- Write main() with hardcoded values with pre-existing accounts (some with expired passwords)
 * 		- Wrapper/menu to edit security level on account
 * 		- Write larger wrapper for all of these to be placed in main()
 * **********************************************************************/
#include "implement.hpp"
#include "User.hpp"
#include "account.hpp"
#include "sha256.hpp"
#include <map>

using namespace std;

// Safely get input
int getNumIn()
{
	int intSelect;
	string strSelect;
	getline(cin, strSelect);
	// Safely get input with sstream
	stringstream(strSelect) >> intSelect;
	return intSelect;
}
/* ***************************************************************
 * Function: selectAccount
 * Returns: int of the account selected by user to edit
 * Description: Displays accounts to user, asking them to select an account to edit
 * ***************************************************************/
Account& selectAccount(User& user) {
	// Get number of accounts user has
	map<string, Account> &the_accounts = user.getAccounts();
	int numAccounts = the_accounts.size();
	auto &userAccounts =  user.getAccounts();
	map<string, Account>::iterator targetAccount;
	string choice,
		   cancelString("CANCEL");

	// Ensure semi-valid input
	do {
		cout << "Choose which of the accounts you would like to edit:" << endl;
		user.displayAccounts();
		cout <<  "****CANCEL****" << endl;
		
		getline(cin, choice);
 
		// Find the matching account in the account map, if find failed userAccounts.end() is returned
		targetAccount = userAccounts.find(choice);

		if ( targetAccount == userAccounts.end() && choice != "CANCEL" )
				cout << "Could not find account '" << choice << "'. Please select an existing account " 
				 << " or type 'CANCEL.'" << endl;

			} while ( targetAccount == userAccounts.end() && choice.compare(cancelString) != 0  );
	return targetAccount->second;
}


/* ***************************************************************
 * Function: editPassword
 * Returns: the updated user
 * Description: Takes the account name the user wants to edit and sets a new password
 * ***************************************************************/
void editPassword(User& user, Account& accountToEdit) {
	int choice;
	
	// If any integer besides {1, 2}, exit
	while ( choice > 3 || choice < 1) {
		cout << "Please select from the following options: " << endl;
		cout << "1. Enter your own password" << endl;
		cout << "2. Automatically generate a password (based on account security level)" << endl;
		cout << "3. Exit" << endl;
		cout << "Current Account Security Level: " << accountToEdit.getSecLvlStr() << endl;
	
		choice = getNumIn();
	}

	switch(choice) {
		case 1: {
			string password;
			accountToEdit.getPasswordPolicy();
			getline(cin, password);
			accountToEdit.setPassword(password);
			break;
				}

		case 2:
			accountToEdit.setPassword();
			break;
		
		default:
			cout << "Returning to main menu" << endl;
	}
}


/* ***************************************************************
 * Function: editAccounts
 * Returns: the User, either updated or the same, if no modifications are made.
 * Description: Provides a menu for the user to edit their accounts' usernames, passwords, 
 * the options to add or delete accounts.  
 * ***************************************************************/
		
void editAccounts(User& user) {
	int choice = 0;


	cout << "============Edit Accounts==============" << endl;

	while (choice > 3 || choice < 1) {
		cout << "Please choose from the following menu options." << endl;
		cout << "1. Edit an account" << endl;
		cout << "2. Add account" << endl;
		cout << "3. Exit" << endl;

		choice = getNumIn();
	}

	if(choice == 1) 
	{
			// Determine which account user wants to edit
			Account& accountToEdit = selectAccount(user);
			int choice2 = 0;
			while (choice2 > 3 || choice2 < 1 ) {
				cout << "Editing " << accountToEdit.getAccountName() 
						 << ": Please select from the following." << endl;
				cout << "1. Edit Username" << endl;
				cout << "2. Edit Password" << endl;
				cout << "3. Delete account '" << accountToEdit.getAccountName() << "'" << endl;
				choice2 = getNumIn();
			}
			switch(choice2) {
				case 1:
					editUsername(user, accountToEdit);
					break;
				case 2:
					editPassword(user, accountToEdit);
					break;
				case 3:
					user.deleteAccount(accountToEdit.getAccountName());
					break;
				}
	}
	else if(choice == 2) {
			addAccount(user);
	}
	else
	{
		cout << "Exiting." << endl;
	}
}

/* ***************************************************************
 * Function: editUsername
 * Returns: the User object
 * Description: Gets a new username for the specified account
 * ***************************************************************/
void editUsername(User& user, Account& accountToEdit) {
	string newUsername;
	cout << "Current username for " << accountToEdit.getAccountName() << ": "
		<< accountToEdit.getUserName() << endl;
	cout << "Please enter a new username.\n: ";
	// Get user input
	getline(cin, newUsername);
	accountToEdit.setUserName(newUsername);
}

/* ***************************************************************
 * Function: addAccount
 * Returns: the User object
 * Description: Adds an account for the user to add,
 * inputting username, password, and security level
 * ***************************************************************/
void addAccount(User &user) {
	int secLvl;
	string secLvls[] = {"low", "medium", "high"};
	string newAcctName,
		   newAcctUsername,
		   newAcctPw,
		   newAcctSecLvl;

	cout << "Please enter the name of this account (this is strictly for your own records): ";
	getline(cin, newAcctName);
	cout << "Account name set to: " << newAcctName << endl;
	cout << "Please enter the username for this account: ";
	getline(cin, newAcctUsername);
	cout << "Account username set to: " << newAcctUsername;
	while (!newAcctSecLvl.compare(secLvls[0]) && 
			!newAcctSecLvl.compare(secLvls[1]) &&
		   	!newAcctSecLvl.compare(secLvls[2]) ) {
		cout << "Please set a security level, either \"low\", \"medium\", or \"high\": ";
		getline(cin, newAcctSecLvl);
	}
	if (newAcctSecLvl.compare(secLvls[0]) == 0)
		secLvl = 1;
	else if (newAcctSecLvl.compare(secLvls[1]) == 0)
		secLvl = 2;
	else 
		secLvl = 3;

	// Create account and check if it was successful, returning to menu if not
	int numAccounts = user.getAccounts().size();
	user.createAccount(newAcctName, newAcctUsername, secLvl);
	if (numAccounts == user.getAccounts().size()) {
		cout << "Account creation failed. Returning to main menu" << endl;
		return;
	}

	auto &userAccounts = user.getAccounts();
	auto targetAccount = userAccounts.find(newAcctName);
	editPassword(user, targetAccount->second);
}


/* ***************************************************************
 * Function: logIn
 * Returns: int indicating (un)successful log in 
 * Description: Log in to a pre-existing account (hard-coded in main
 * or fetched from database in full implementation
 * ***************************************************************/
int logIn(User& test_user) {
	string usernameIn;
	string enteredPw;

	while(usernameIn.compare(test_user.getUserName()) && usernameIn.compare("quit")) {
		cout << "\nPlease enter your username, or type \"quit\" to exit: ";
		getline(cin, usernameIn);
	}
	if (usernameIn.compare("quit") == 0)
		return 0;
	else {
		cout << "Enter your password: ";
		getline(cin, enteredPw);
		string hash = sha256(enteredPw);
		// TODO: for testing, putting in a hardcoded password
		if (sha256(enteredPw).compare(test_user.getUserPwHash()) == 0 ) {
			cout << "Log in successful!" << endl;
			test_user.checkAccountPasswords();
			return 1;
		}
	}

	cout << "Invalid password" << endl;
	return 0;
}


/* ***************************************************************
 * Function: createUserAccount
 * Returns: a newly created User object
 * Description: Create a new User Account if customer does not
 * want to log in. Customer populates with Username, Security level,
 * and password (custom, or auto-generated)
 * ***************************************************************/
User createUserAccount() {
	int choice, secChoice, pwChoice;
	string password;
	string mainAccountName;

	while (choice != 1 ) {
		cout << "Please enter a username for your Password Please account: " << endl;
		getline(cin, mainAccountName);
		cout << "Your name is: " << mainAccountName << endl;
		cout << "If this is correct, press 1. If this is incorrect, press any other number.";
		choice = getNumIn();
	}

	while (secChoice != 1  && secChoice != 2 && secChoice != 3) { 
		cout << "Please enter a security level: " << endl;
		cout << "1. Low" << endl;
		cout << "2. Medium" << endl;	
		cout << "3. High" << endl;
		secChoice = getNumIn();
	}

	User user;
	user.setSecLvl(secChoice);
	user.setUserName(mainAccountName);

	while (pwChoice != 1 && pwChoice != 2) {
		cout << "If you would like to enter your own password, press 1. Otherwise, press 2 to automatically generate one." << endl;
		pwChoice = getNumIn();
	}

	switch(pwChoice) {
		case 1:
			cout << "Please enter your password: ";
			getline(cin, password);
		    user.setUserPw(password);	
			break;
		case 2:
			cout << "Automatically generating your password...";
			user.setUserPw();
			break;
	}
	cout << "Account successfully created." << endl;

	return user;
}

/* ***************************************************************
 * Function: mainMenu
 * Returns: 
 * Description: Simple menu to be called from main(), gives option
 * to edit accounts, view them, or exit.
 * ***************************************************************/
void mainMenu(User &user) {
	int choice;

	while (choice != 3) {
		cout << "\nPlease select from the following menu options: " << endl;
		cout << "1. View Accounts" << endl;
		cout << "2. Edit, Add, or Delete Accounts" << endl;
		cout << "3. Exit application" << endl;
		choice = getNumIn();

		switch(choice) {
			case 1:
				user.displayAccounts();
				break;
			case 2:
				editAccounts(user);
				break;
			case 3:
				break;
			default:
				cout << "Invalid selection" << endl;
		}
	}
}
	
