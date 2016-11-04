#ifndef _PRIME32_
#define _PRIME32_

#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>

#include "prime-checks.h"

namespace prime32{
   
   using PtToBoolFunc = decltype(checkers::isPrime)*;
   

   const std::map<std::string, PtToBoolFunc> lookup = {
            {"unfiltered", checkers::isPrime},
            {"odd", checkers::isOddPrime},
            {"additive", checkers::isAdditivePrime},
            {"palindromic", checkers::isPalindromicPrime},
            {"isolated", checkers::isIsolatedPrime},
            {"pythagorean", checkers::isPythagoreanPrime},
            {"safe", checkers::isSafePrime},
   };

   PtToBoolFunc selectPrimeFunc(std::string type);
   std::vector<bool> check(const std::vector<int> & nums, const std::string type="unfiltered");
   bool any(const std::vector<int> & nums, const std::string type="unfiltered");
   bool all(const std::vector<int> & nums, std::string type="unfiltered");
   std::vector<int> select(const std::vector<int> & nums, std::string type="unfiltered");
   std::vector<int> remove(const std::vector<int> & nums, std::string type="unfiltered");
   std::vector<int> first(const int n, std::string type="unfiltered");
   std::vector<int> range(const int lower, const int upper, std::string type="unfiltered");
   std::vector<int> range(const int upper, std::string type="unfiltered");
   std::vector<int> factoring(const int num);

}

#endif