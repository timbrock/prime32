#ifndef _PRIME32CHECKERS_
#define _PRIME32CHECKERS_

#include <vector>

static_assert(sizeof(int)>=4, "int needs to be at least 32 bits");

namespace prime32{
   std::vector<int> sieve(const int upper);
   namespace checkers{
      bool isPrime(const int num);
      bool isOddPrime(const int num);
      bool isAdditivePrime(const int num);
      bool isPalindromicPrime(const int num);
      bool isIsolatedPrime(const int num);
      bool isPythagoreanPrime(const int num);
      bool isSafePrime(const int num);
   }
}

#endif
