#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "account.hpp"


TEST_CASE( "Time Expiration Date","[expiration]" ) {
	Account testAccount1 = Account("account1", "user1",1);
	testAccount1.setPassword("Please");
	SECTION("Constructor Verify")
	{
		REQUIRE( testAccount1.verifyPwAge() == 0);
	}
    
	Account testAccount2 = Account("account2","user2",1);
	Account testAccount3 = Account("account3","user3",1);
	testAccount1.setPwAge(119);
	SECTION("Under 119")
	{
		REQUIRE( testAccount1.verifyPwAge() == 0);
	}
	
	testAccount2.setPwAge(120);
	
	SECTION("On 120")
	{
		REQUIRE( testAccount2.verifyPwAge() == 1);
	}
	testAccount3.setPwAge(121);
	
	SECTION("Over 120")
	{
		REQUIRE( testAccount3.verifyPwAge() == 1);
	}
	
	testAccount1.setPwAge(125);
	SECTION("Reset over 120")
	{
		REQUIRE( testAccount1.verifyPwAge() == 1);
	}
	
	testAccount1.setIgnore();
	SECTION("set ignore")
	{
		REQUIRE( testAccount1.verifyPwAge() == 0);
	}
	
}