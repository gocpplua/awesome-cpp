#define CATCH_CONFIG_MAIN
#include "../3thParty/catch2/catch.hpp"

#include "../src/util/instance.h"

static int Factorial( int number ) {
   return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
// return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}

TEST_CASE( "Factorial of 0 is 1 (fail)", "[single-file]" ) {
    REQUIRE( Factorial(0) == 0 );
    REQUIRE( Factorial(0) == 2 );
}

TEST_CASE("Instance", "instance"){
  REQUIRE(Singleton<int>::getInstance() == Singleton<int>::getInstance());
  REQUIRE(Singleton<int>::getInstance() != (int*)Singleton<double>::getInstance());
}