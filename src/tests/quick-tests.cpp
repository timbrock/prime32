#define CATCH_CONFIG_MAIN

#include "tests.h"

using namespace prime32;
using namespace testHelpers;
using std::vector;

const vector<int> dataStore = getIntsFromFile(path + "store-data.txt");
const vector<int> input = getIntsFromFile(path + "input-data.txt");
const vector<int> output = getIntsFromFile(path + "output-data.txt");
const vector<int> dataMillion = getIntsFromFile(path + "million-data.txt");
const vector<int> dataAdditive = getIntsFromFile(path + "additive-data.txt");
const vector<int> dataIsolated = getIntsFromFile(path + "isolated-data.txt");
const vector<int> dataPythagorean = getIntsFromFile(path + "pythagorean-data.txt");
const vector<int> dataSafe = getIntsFromFile(path + "safe-data.txt");
const vector<int> dataPalindromic = getIntsFromFile(path + "palindromic-data.txt");


TEST_CASE("Preliminary checks on input data pass size tests", "[data]"){
   REQUIRE(dataStore.size() == 4792);
   REQUIRE(input.size() == 1000000);
   REQUIRE(output.size() == 1000000);
   REQUIRE(dataMillion.size() == 78498);
   REQUIRE(dataAdditive.size() == 14);
   REQUIRE(dataIsolated.size() == 99);
   REQUIRE(dataPythagorean.size() == 42);
   REQUIRE(dataSafe.size() == 37);
   REQUIRE(dataPalindromic.size() == 33);
}

TEST_CASE("Primes are sieved", "[sieve]"){
   REQUIRE(allEqual(sieve(20), vector<int>{2,3,5,7,11,13,17,19}) == true);
   REQUIRE(allEqual(sieve(46340), dataStore) == true);
   REQUIRE(allEqual(sieve(1000000), dataMillion) == true);
}


TEST_CASE("Checkers work correctly", "[checkers]"){
   
   using namespace checkers;
   
   SECTION("isPrime returns correct bool for a range of edge cases"){
      REQUIRE(isPrime(-10) == false);
      REQUIRE(isPrime(0) == false);
      REQUIRE(isPrime(1) == false);
      REQUIRE(isPrime(2) == true);
      REQUIRE(isPrime(3) == true);
      REQUIRE(isPrime(7) == true);
      REQUIRE(isPrime(11) == true);
      REQUIRE(isPrime(13) == true);
      REQUIRE(isPrime(MAXINT - 1) == false);
      REQUIRE(isPrime(MAXINT) == true);
   }
   
   SECTION("isOddPrime returns correct bool for a range of edge cases"){
      REQUIRE(isOddPrime(-10) == false);
      REQUIRE(isOddPrime(0) == false);
      REQUIRE(isOddPrime(1) == false);
      REQUIRE(isOddPrime(2) == false);
      REQUIRE(isOddPrime(3) == true);
      REQUIRE(isOddPrime(7) == true);
      REQUIRE(isOddPrime(11) == true);
      REQUIRE(isOddPrime(13) == true);
      REQUIRE(isOddPrime(MAXINT - 1) == false);
      REQUIRE(isOddPrime(MAXINT) == true);
   }
   
   SECTION("isAdditivePrime returns correct bool for a range of edge cases"){
      REQUIRE(isAdditivePrime(-10) == false);
      REQUIRE(isAdditivePrime(0) == false);
      REQUIRE(isAdditivePrime(1) == false);
      REQUIRE(isAdditivePrime(2) == true);
      REQUIRE(isAdditivePrime(3) == true);
      REQUIRE(isAdditivePrime(7) == true);
      REQUIRE(isAdditivePrime(11) == true);
      REQUIRE(isAdditivePrime(13) == false);
      REQUIRE(isAdditivePrime(MAXINT - 1) == false);
      REQUIRE(isAdditivePrime(MAXINT) == false);
   }
   
    SECTION("isIsolatedPrime returns correct bool for a range of edge cases"){
      REQUIRE(isIsolatedPrime(-10) == false);
      REQUIRE(isIsolatedPrime(0) == false);
      REQUIRE(isIsolatedPrime(1) == false);
      REQUIRE(isIsolatedPrime(2) == true);
      REQUIRE(isIsolatedPrime(3) == false);
      REQUIRE(isIsolatedPrime(7) == false);
      REQUIRE(isIsolatedPrime(11) == false);
      REQUIRE(isIsolatedPrime(13) == false);
      REQUIRE(isIsolatedPrime(MAXINT - 1) == false);
      REQUIRE(isIsolatedPrime(MAXINT) == true);
   }
   
    SECTION("isPythagoreanPrime returns correct bool for a range of edge cases"){
      REQUIRE(isPythagoreanPrime(-10) == false);
      REQUIRE(isPythagoreanPrime(0) == false);
      REQUIRE(isPythagoreanPrime(1) == false);
      REQUIRE(isPythagoreanPrime(2) == false);
      REQUIRE(isPythagoreanPrime(3) == false);
      REQUIRE(isPythagoreanPrime(7) == false);
      REQUIRE(isPythagoreanPrime(11) == false);
      REQUIRE(isPythagoreanPrime(13) == true);
      REQUIRE(isPythagoreanPrime(MAXINT - 1) == false);
      REQUIRE(isPythagoreanPrime(MAXINT) == false);
   }
   
    SECTION("isSafePrime returns correct bool for a range of edge cases"){
      REQUIRE(isSafePrime(-10) == false);
      REQUIRE(isSafePrime(0) == false);
      REQUIRE(isSafePrime(1) == false);
      REQUIRE(isSafePrime(2) == false);
      REQUIRE(isSafePrime(3) == false);
      REQUIRE(isSafePrime(7) == true);
      REQUIRE(isSafePrime(11) == true);
      REQUIRE(isSafePrime(13) == false);
      REQUIRE(isSafePrime(MAXINT - 1) == false);
      REQUIRE(isSafePrime(MAXINT) == false);
   }
   
    SECTION("isPalindromicPrime returns correct bool for a range of edge cases"){
      REQUIRE(isPalindromicPrime(-10) == false);
      REQUIRE(isPalindromicPrime(0) == false);
      REQUIRE(isPalindromicPrime(1) == false);
      REQUIRE(isPalindromicPrime(2) == true);
      REQUIRE(isPalindromicPrime(3) == true);
      REQUIRE(isPalindromicPrime(7) == true);
      REQUIRE(isPalindromicPrime(11) == true);
      REQUIRE(isPalindromicPrime(13) == false);
      REQUIRE(isPalindromicPrime(MAXINT - 1) == false);
      REQUIRE(isPalindromicPrime(MAXINT) == false);
   }
   
}


TEST_CASE("The default type, unfiltered, works correctly", "[defaulttype]"){
   vector<bool> comparator = intToBool(output);
   REQUIRE(allEqual(check(input), comparator) == true);
   REQUIRE(allEqual(check(input, "unfiltered"), comparator) == true);
}


TEST_CASE("any correctly identifies when vector contains primes", "[any]"){
   REQUIRE(any(sequence(-30,1)) == false);
   REQUIRE(any(sequence(-30,30)) == true);
   REQUIRE(any(sequence(4,30,2)) == false);
   REQUIRE(any(sequence(2,30,2)) == true);
   REQUIRE(any(vector<int>{MAXINT}) == true); 
}


TEST_CASE("all correctly identifies when vector only contains primes", "[all]"){
   REQUIRE(all(sequence(-30,1)) == false);
   REQUIRE(all(sequence(-30,30)) == false);
   REQUIRE(all(sequence(4,30,2)) == false);
   REQUIRE(all(sequence(2,30,2)) == false);
   REQUIRE(all(vector<int>{MAXINT}) == true);
   REQUIRE(all(dataStore) == true);
}


TEST_CASE("select returns a vector containing only the primes in its dataStore", "[select]"){
   REQUIRE(allEqual(select(sequence(-1,4)), vector<int>{2,3}) == true);
   REQUIRE(allEqual(select(sequence(2,1000,2)), vector<int>{2}) == true);
   REQUIRE(allEqual(select(sequence(4,1000,2)), vector<int>(0)) == true);
   REQUIRE(select(dataStore).size() == dataStore.size());
}


TEST_CASE("remove returns a vector without the primes in its input", "[remove]"){
   REQUIRE(allEqual(remove(sequence(-1,4)), vector<int>{-1,0,1,4}) == true);
   REQUIRE(allEqual(remove(sequence(2,1000,2)), sequence(4,1000,2)) == true);
   REQUIRE(allEqual(remove(sequence(4,1000,2)), sequence(4,1000,2)) == true);
   REQUIRE(remove(dataStore).size() == 0);
}


TEST_CASE("first finds the first n primes", "[first]"){
   REQUIRE(first(0).size() == 0);
   REQUIRE(first(1)[0] == 2);
   REQUIRE(allEqual(first(5), vector<int>{2,3,5,7,11})  == true);
   REQUIRE(allEqual(first(dataStore.size()), dataStore) == true);
}


TEST_CASE("range finds primes in specified range", "[range]"){
   REQUIRE(range(-MAXINT,1).size() == 0);
   REQUIRE(allEqual(range(0,20), vector<int>{2,3,5,7,11,13,17,19})  == true);
   REQUIRE(allEqual(range(0,20), range(20))  == true);
   REQUIRE(allEqual(range(46341), dataStore)  == true);
   REQUIRE(allEqual(range(197,221), vector<int>{197,199,211})  == true);
   REQUIRE(allEqual(range(17,23), vector<int>{17,19,23})  == true);
   REQUIRE(allEqual(range(MAXINT-1,MAXINT), vector<int>{MAXINT})  == true);
   REQUIRE(allEqual(range(1000000,1000100), vector<int>{1000003,1000033,1000037,1000039,1000081,1000099})  == true);
}


TEST_CASE("filtered primes behave correctly", "[filtered]"){
   REQUIRE(first(1,"odd")[0] == 3);
   REQUIRE(all(dataAdditive,"additive") == true);
   REQUIRE(all(dataIsolated,"isolated") == true);
   REQUIRE(all(dataPythagorean,"pythagorean") == true);
   REQUIRE(all(dataSafe,"safe") == true);
   REQUIRE(all(dataPalindromic,"palindromic") == true);
}


TEST_CASE("factoring finds unique prime factors of an integer", "[factoring]"){
   REQUIRE(factoring(-1).size() == 0);
   REQUIRE(factoring(0).size() == 0);
   REQUIRE(factoring(0).size() == 0);
   REQUIRE(allEqual(factoring(6978231), vector<int>{3,3,3,3,3,13,47,47})  == true);
   REQUIRE(allEqual(factoring(MAXINT-2), vector<int>{5,19,22605091})  == true);
   REQUIRE(allEqual(factoring(4194304), vector<int>(22,2))  == true);
   REQUIRE(allEqual(factoring(46343), vector<int>{11,11,383})  == true);
   REQUIRE(allEqual(factoring(MAXINT), vector<int>{MAXINT})  == true);
}


TEST_CASE("The type argument isn't ignored", "[type]"){
   REQUIRE(check(sequence(2,2),"odd")[0] == false);
   REQUIRE(any(sequence(2,10,2),"odd") == false);
   REQUIRE(all(sequence(2,2),"odd") == false);
   REQUIRE(select(sequence(2,10,2),"odd").size() == 0);
   REQUIRE(allEqual(remove(sequence(2,10,2),"odd"), sequence(2,10,2)) == true);
   REQUIRE(first(1,"odd")[0] == 3);
   REQUIRE(range(1,20,"odd")[0] == 3);
   REQUIRE(range(20,"odd")[0] == 3);
}


TEST_CASE("All these tests (correctly) throw exceptions", "[errors]"){
   REQUIRE_THROWS(selectPrimeFunc("notafunc"));
   REQUIRE_THROWS(first(-10));
   REQUIRE_THROWS(range(600,1));
}