//Only run this if you're really really bored

#define CATCH_CONFIG_MAIN

#include "tests.h"

using namespace prime32;
using namespace testHelpers;
using std::vector;


TEST_CASE("Verifying sieve returns only primes", "[sieve]"){
   vector<int> allPrimes = sieve(MAXINT);
   REQUIRE(all(allPrimes) == true);
}