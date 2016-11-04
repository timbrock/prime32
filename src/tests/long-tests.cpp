#define CATCH_CONFIG_MAIN

#include "tests.h"

using namespace prime32;
using namespace testHelpers;
using std::vector;


const vector<int> top11 = getIntsFromFile(path + "top11-data.txt");

TEST_CASE("Preliminary checks on input data pass size tests", "[data]"){
   REQUIRE(top11.size() == 11);
}

TEST_CASE("Sieve correctly identifies the number of 32-bit primes and the values of the largest 11", "[sieve]"){
   vector<int> allPrimes = sieve(MAXINT);
   REQUIRE(allPrimes.size() == 105097565);
   vector<int> last11(allPrimes.end() - 11, allPrimes.end());
   REQUIRE(allEqual(last11, top11) == true);
}

TEST_CASE("range matches sieve (up to at least 100 million)", "[range]"){
   int hundredMn = 100000000;
   vector<int> sieved = sieve(hundredMn);
   vector<int> ranged = range(0,hundredMn);
   REQUIRE(allEqual(sieved, ranged) == true);
}

TEST_CASE("first matches sieve (up to at least 100 million)", "[first]"){
   int hundredMn = 100000000;
   vector<int> sieved = sieve(hundredMn);
   vector<int> firstLot = first(5761455);
   REQUIRE(allEqual(sieved, firstLot) == true);
}