#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "pwGen.hpp"
#include "sha256.hpp"

#define LOW_SEC 10
#define MED_SEC 15
#define HI_SEC 20

TEST_CASE( "Password and hashes are generated accurately", "[all]") { 
	int invalid;

	struct password weak_pw = pwGen_Wrapper("low", invalid);
	struct password med_pw = pwGen_Wrapper("medium", invalid);
	struct password strong_pw = pwGen_Wrapper("high", invalid);

	SECTION( "Testing Passwords" ) {
		REQUIRE( weak_pw.password_key.length() == LOW_SEC);
		REQUIRE( med_pw.password_key.length() == MED_SEC);
		REQUIRE( strong_pw.password_key.length() == HI_SEC);
		pwGen_Wrapper("nonsense", invalid);
		REQUIRE( invalid == 1);
		pwGen_Wrapper("MEDIUM", invalid);
		REQUIRE( invalid == 0 );
	}

	SECTION( "Testing hashes") {
		REQUIRE( sha256("h311oTestinG#$") == "1e8feeafca13a5ce367ebb0d3d817e16031ee1c0debd72e9d09c352e000a934a");
		REQUIRE( sha256(weak_pw.password_key) == weak_pw.password_hash);
		REQUIRE( sha256(med_pw.password_key) == med_pw.password_hash);
		REQUIRE( sha256(strong_pw.password_key) == strong_pw.password_hash);
		REQUIRE( weak_pw.password_hash.length() == 64);
		REQUIRE( med_pw.password_hash.length() == 64);
		REQUIRE( strong_pw.password_hash.length() == 64);
	}

}


