/* User class unit test file */
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

// Library includes
#include <string>

// Header file includes
#include "User.hpp"
#include "../catch.hpp"

// Application includes
#include "../Account/account.hpp"
#include "../PasswordGenerator/pwGen.hpp"
#include "../PasswordGenerator/sha256.hpp"

/* 
 * Not yet implemented in User class:
 * Test that a user can remove/delete an account
 * Test that a user cannot have the same username/email as any other user
 * Test that a user must change their password after a certain number of days
 * Test that a user cannot make a password at medium or high level that does not 
 * include any lower case letters
 * Test that a username, email, or password cannot include any escapes like \n 
 */

TEST_CASE("Test getter/setter methods", "[gettersetters]")
{
	User testUser = User();
	
	SECTION("Test Security Level getter/setters")
	{
		testUser.setSecLvl(2);
		REQUIRE( testUser.getSecLvl() == User::sec_level_type::MEDIUM );
		REQUIRE( testUser.getSecLvlString() == "medium" );
		testUser.setSecLvl(1);
		REQUIRE( testUser.getSecLvl() == User::sec_level_type::LOW );
		REQUIRE( testUser.getSecLvlString() == "low" );
	}

	SECTION("Test userName getter/setter")
	{
		std::string userName = "newUserName";
		testUser.setUserName(userName);
		REQUIRE( testUser.getUserName() == "newUserName" );
		userName = "newerUserName";
		testUser.setUserName(userName);
		REQUIRE( testUser.getUserName() == "newerUserName" );
	}

	SECTION("Test userEmail getter/setter")
	{
		std::string email = "newUser@gmail.com";
		testUser.setUserEmail(email);
		REQUIRE( testUser.getUserEmail() == "newUser@gmail.com" );
		email = "newerUser@happyemail.com";
		testUser.setUserEmail(email);
		REQUIRE( testUser.getUserEmail() == "newerUser@happyemail.com" );
	}

	SECTION("Test password getter/setters")
	{
		//low security, password verification testing is done elswhere
		testUser.setSecLvl(1);

		SECTION("Test paramaterized password setter")
		{
			testUser.setUserPw("password123");
			REQUIRE( testUser.getUserPwHash() == sha256("password123") );
			REQUIRE( testUser.getUserPwHash() != "password123" );
		}

		SECTION("Test overloaded password setter")
		{
			// since the password generator is tested elsewhere, we will
			// only test for password uniqueness here.
			User testUser2 = User();
			testUser.setSecLvl(1);

			testUser.setUserPw();
			testUser2.setUserPw();

			REQUIRE(testUser.getUserPwHash() != testUser2.getUserPwHash());
		}
	}


	SECTION("Test accounts getter/creator")
	{
		// Test that a user can have 0 accounts
		REQUIRE( testUser.getAccounts().empty() == 1 );

		std::string accountName = "accountName";
		std::string newAccountName = "newAccountName";
		std::string userName = "testuser";
		std::string psswd = "password123";
		User::sec_level_type sclvl = User::sec_level_type::LOW;

		// Test that an account is created from createAccount and put in the set
		testUser.createAccount(accountName, userName, psswd, sclvl);
		REQUIRE( testUser.getAccounts().size() == 1 );

		// Test that an identical account cannot be created and stored
		testUser.createAccount(accountName, userName, psswd, sclvl);
		REQUIRE( testUser.getAccounts().size() == 1 );

		// Test that one or more accounts may be created
		testUser.createAccount(newAccountName, userName, psswd, sclvl);
		REQUIRE( testUser.getAccounts().size() == 2 );

		// Test that information stored in each account is accurate
		REQUIRE( testUser.getAccounts().find(accountName) 
						 != testUser.getAccounts().end() );
		REQUIRE( testUser.getAccounts().find(newAccountName) 
						 != testUser.getAccounts().end() );
	}
	

}

TEST_CASE("Test that user password adhere's to password policy", "[validatepw]")
{
	User testUser = User();

	// Security level set to low
	testUser.setSecLvl(1);
	REQUIRE( testUser.getSecLvl() == User::sec_level_type::LOW );

	// Password should be at least 10 characters long
	REQUIRE( testUser.validateUserPw("123456789") != 1 );
	REQUIRE( testUser.validateUserPw("1234567890") == 1 );
	
	// Security level set to medium
	testUser.setSecLvl(2);
	REQUIRE( testUser.getSecLvl() == User::sec_level_type::MEDIUM );

	// Password must be at least 15 characters long
	// with one capital letter and one number
	REQUIRE( testUser.validateUserPw("abcdefg") != 1 );
	REQUIRE( testUser.validateUserPw("012345678901234") != 1 );
	REQUIRE( testUser.validateUserPw("password1234567") != 1 );
	REQUIRE( testUser.validateUserPw("passWord1234567") == 1 );
	REQUIRE( testUser.validateUserPw("PassW0rd") != 1 );
	REQUIRE( testUser.validateUserPw("PassW0rdsAreSuperDooperCrazyl0ngSometimes") == 1 );
	REQUIRE( testUser.validateUserPw("passw0rdssometimesareprettylonganddontpass") != 1 );
	REQUIRE( testUser.validateUserPw("AndSometimesTheyresooperdooperLongbutarentquitesecureEnough") != 1 );

	// Security level set to high
	testUser.setSecLvl(3);
	REQUIRE( testUser.getSecLvl() == User::sec_level_type::HIGH );

	// Password must include all previous requirements plus:
	// be 20 characters long and include at least one special character
	// Run through all previous tests plus some new ones
	REQUIRE( testUser.validateUserPw("abcdefg") != 1 );
	REQUIRE( testUser.validateUserPw("012345678901234") != 1 );
	REQUIRE( testUser.validateUserPw("password1234567") != 1 );
	REQUIRE( testUser.validateUserPw("passWord1234567") != 1 );
	REQUIRE( testUser.validateUserPw("PassW0rd") != 1 );
	REQUIRE( testUser.validateUserPw("PassW0rdsAreSuperDooperCrazyl0ngSometimes") != 1 );
	REQUIRE( testUser.validateUserPw("passw0rdssometimesareprettylonganddontpass") != 1 );
	REQUIRE( testUser.validateUserPw("AndSometimesTheyresooperdooperLongbutarentquitesecureEnough") != 1 );
	REQUIRE( testUser.validateUserPw("andF!nallyw3f1ndon3thatworks!") == 1 );
	REQUIRE( testUser.validateUserPw("th1sOne$houldworktoo") == 1 );
}

TEST_CASE("Test that user can add and delete accounts", "[addDelete]") {
	std::string accountName = "accountName";
	std::string newAccountName = "newAccountName";
	std::string userName = "testuser";
	std::string psswd = "password123";
	int secLvl = 2;
	User testUser;

	testUser.createAccount(accountName, userName, psswd, secLvl);
	REQUIRE(testUser.getAccounts().size() > 0);
	testUser.deleteAccount(accountName);
	REQUIRE(testUser.getAccounts().size() == 0);
}

