#include "prime32.h"

using prime32::PtToBoolFunc;

namespace{
   const int MAXINT = 2147483647;

   int findNextPrime(const int num, const PtToBoolFunc primeFunc){
      const int NA_INTEGER = -1;
      if(num == MAXINT){
         return NA_INTEGER;
      }
      if(num<2 && primeFunc(2)){
         return 2;
      }
      int num2 = (num <= 2) ? 2 : num;
      int nextOdd = (num2%2 == 1) ? (num2 + 2) : (num2 + 1);
      while(nextOdd < MAXINT){
         if(primeFunc(nextOdd)){
            return nextOdd;
         }
         nextOdd += 2;
      }
      return primeFunc(MAXINT) ? MAXINT : NA_INTEGER;
   }
}


PtToBoolFunc prime32::selectPrimeFunc(std::string type){
   if(lookup.count(type) == 0){
      throw std::invalid_argument("String  argument is not a recognised prime type");
   }
   return lookup.at(type);
}


std::vector<bool> prime32::check(const std::vector<int> & nums, std::string type){
   std::vector<bool> result(nums.size());
   std::transform(nums.begin(), nums.end(), result.begin(), selectPrimeFunc(type));
   return result;
}


bool prime32::any(const std::vector<int> & nums, std::string type){
   return std::any_of(nums.begin(), nums.end(), selectPrimeFunc(type));
}


bool prime32::all(const std::vector<int> & nums, std::string type){
   return std::all_of(nums.begin(), nums.end(), selectPrimeFunc(type));
}


std::vector<int> prime32::select(const std::vector<int> & nums, std::string type){
   std::vector<int> result;
   std::copy_if(nums.begin(), nums.end(), back_inserter(result), selectPrimeFunc(type));
   return result;
}


std::vector<int> prime32::remove(const std::vector<int> & nums, std::string type){
   std::vector<int> result;
   std::remove_copy_if(nums.begin(), nums.end(), back_inserter(result), selectPrimeFunc(type));
   return result;
}


std::vector<int> prime32::first(const int n, std::string type){
   if(n <= 0){
      if(n == 0){
         return std::vector<int>(0);
      }
      throw std::range_error("n cannot be negative");
   }
   const int MAXNPRIME = 105097565;
   //we can't have more than MAXNPRIME 32-bit primes
   int n2 = (n<=MAXNPRIME) ? n : MAXNPRIME;
   std::vector<int> primes(n2);
   const auto primeFunc = selectPrimeFunc(type);
   int found = 0;
   if(primeFunc(2)){
      primes[found++] = 2;
   }
   int current = 3;
   while(found<n && current<MAXINT){
      if(primeFunc(current)){
         primes[found++] = current;
      }
      current += 2;
   }
   if(found < n2){
      //Treat MAXINT as special case to avoid current overflowing
      if(primeFunc(MAXINT)){
         primes[found++] = MAXINT;
      }
      //if we've specified too many we need to return smaller vector
      if(found < n2){
         primes.resize(found);
      }
   }
   return primes;
}


std::vector<int> prime32::range(const int lower, const int upper, std::string type){
   if(lower > upper){
       throw std::range_error("Lower limit cannot be greater than upper limit");
   }
   
   std::vector<int> primes;
   
   if(upper < 2){
      return primes;
   }
   
   const auto primeFunc = selectPrimeFunc(type);
   
   if(lower <= 2){
      if(primeFunc(2)){
         primes.push_back(2);
      }
   }
   int start = (lower<=3) ? 3 : (lower%2==1 ? lower : lower+1);
   int end = (upper<MAXINT) ? upper : MAXINT-1; //need to avoid overflow
   for(int i = start; i<=end; i+=2){
      if(primeFunc(i)){
         primes.push_back(i);
      }
   }
   if(upper == MAXINT && primeFunc(MAXINT)){ //edge case
      primes.push_back(MAXINT);
   }
   return primes;
}


std::vector<int> prime32::range(const int upper, std::string type){
   return range(0, upper, type);
}


std::vector<int> prime32::factoring(const int num){
   
   const auto primeFunc = selectPrimeFunc("unfiltered");
   std::vector<int> result;
   if(num <= 1){
      return result;
   }
   if(primeFunc(num)){
      result.push_back(num);
      return result;
   }
   
   int current = num;
   int cPrime = 2; //first prime is 2
   int counter = 0;

   while(true){
      while(current%cPrime == 0){
         counter++;
         current /= cPrime;
      }
      if(counter == 0){
         cPrime = findNextPrime(cPrime, primeFunc);
      }
      else{
         result.insert(result.end(), counter, cPrime);
         if(current > 1){
            cPrime = primeFunc(current) ? current : findNextPrime(cPrime, primeFunc);
            counter = 0;
         } else{
            break;
         }
      }
   }

   return result;
}
