#define CATCH_CONFIG_MAIN
#include "../3thParty/catch2/catch.hpp"


static int Factorial( int number ) {
   return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
// return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}

TEST_CASE( "Factorial of 0 is 1 (fail)", "[single-file]" ) {
    REQUIRE( Factorial(0) == 0 );
    REQUIRE( Factorial(0) == 2 );
}