/* Account class unit test file */
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

// Library includes


// Header includes
#include "account.hpp"
#include "../catch.hpp"

// Application includes


// Begin tests
TEST_CASE("Test getters and setters not including passwords" , "[gettersetter]")
{
	Account testAccount1 = Account("account1", "user1",1);
	
	SECTION("Test paramaterized constructor")
	{
		REQUIRE( testAccount1.getAccountName() == "account1" );
		REQUIRE( testAccount1.getUserName() == "user1");
		REQUIRE( testAccount1.getSecurityLevel() == 1);
	}

	SECTION("Test individual getter/setters (not including password)")
	{
		testAccount1.setAccountName("NewAccountName");
		REQUIRE( testAccount1.getAccountName() == "NewAccountName" );

		testAccount1.setUserName("NewUserName");
		REQUIRE( testAccount1.getUserName() == "NewUserName" );

		testAccount1.setSecurityLevel(2);
		REQUIRE( testAccount1.getSecurityLevel() == 2 );
	}
}

TEST_CASE("Test password verification and getter/setter", "[verifyPassword]")
{
	Account testAccount1 = Account("account1", "user1",1);
	REQUIRE( testAccount1.getSecurityLevel() == 1);

	// Password should be at least 10 characters long
	REQUIRE( testAccount1.verifyPassword("123456789") != 1 );
	REQUIRE( testAccount1.verifyPassword("1234567890") == 1 );
	
	// Security level set to medium
	testAccount1.setSecurityLevel(2);
	REQUIRE( testAccount1.getSecurityLevel() == 2);

	// Password must be at least 15 characters long
	// with one capital letter and one number
	REQUIRE( testAccount1.verifyPassword("abcdefg") != 1 );
	REQUIRE( testAccount1.verifyPassword("012345678901234") != 1 );
	REQUIRE( testAccount1.verifyPassword("password1234567") != 1 );
	REQUIRE( testAccount1.verifyPassword("passWord1234567") == 1 );
	REQUIRE( testAccount1.verifyPassword("PassW0rd") != 1 );
	REQUIRE( testAccount1.verifyPassword("PassW0rdsAreSuperDooperCrazyl0ngSometimes") == 1 );
	REQUIRE( testAccount1.verifyPassword("passw0rdssometimesareprettylonganddontpass") != 1 );
	REQUIRE( testAccount1.verifyPassword("AndSometimesTheyresooperdooperLongbutarentquitesecureEnough") != 1 );

	// Security level set to high
	testAccount1.setSecurityLevel(3);
	REQUIRE( testAccount1.getSecurityLevel() == 3);

	// Password must include all previous requirements plus:
	// be 20 characters long and include at least one special character
	// Run through all previous tests plus some new ones
	REQUIRE( testAccount1.verifyPassword("abcdefg") != 1 );
	REQUIRE( testAccount1.verifyPassword("012345678901234") != 1 );
	REQUIRE( testAccount1.verifyPassword("password1234567") != 1 );
	REQUIRE( testAccount1.verifyPassword("passWord1234567") != 1 );
	REQUIRE( testAccount1.verifyPassword("PassW0rd") != 1 );
	REQUIRE( testAccount1.verifyPassword("PassW0rdsAreSuperDooperCrazyl0ngSometimes") != 1 );
	REQUIRE( testAccount1.verifyPassword("passw0rdssometimesareprettylonganddontpass") != 1 );
	REQUIRE( testAccount1.verifyPassword("AndSometimesTheyresooperdooperLongbutarentquitesecureEnough") != 1 );
	REQUIRE( testAccount1.verifyPassword("andF!nallyw3f1ndon3thatworks!") == 1 );
	REQUIRE( testAccount1.verifyPassword("th1sOne$houldworktoo") == 1 );
}