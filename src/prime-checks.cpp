#include "prime-checks.h"

namespace prime32{
   
   std::vector<int> sieve(const int upper){

      if(upper<2){
         return std::vector<int>();
      }

      const int MAXINT = 2147483647; //maximum 32-bit signed integer (is prime)
      const int ROOTMAXINT = 46340; //floor of square root of ^
      const int PENPRIME = 2147483629; //largest prime below MAXINT

      int lim = upper>=PENPRIME ? PENPRIME : upper; //treat MAXINT as special case to avoid integer overflow
      std::vector<bool> sieveArray(lim+1); //defaults to false
      sieveArray[2] = true; //treat 2 as a special case

      if(lim>=3){

         for(int i=3; i<=lim; i+=2){ //set odd to true
            sieveArray[i] = true;
         }
         
         int p = 3;
         int pSquared = p*p;
         while(pSquared <= lim){
            if(sieveArray[p]){
               const int pTwo = 2*p;
               for(int i=pSquared; i<=lim; i+=pTwo){
                  if(sieveArray[i]){
                     sieveArray[i] = false;
                  }
                  if(i>(MAXINT-pTwo)){ //avoid any integer overflow issues for large lim
                     break;
                  }
               }
            }
            p += 2;
            if(p > ROOTMAXINT){ //if p > ROOTMAXINT, p*p would overflow
               break;
            }
            pSquared = p*p;
         }
      }
            
      std::vector<int> primes;
      for(int i=0; i<=lim; i++){
         if(sieveArray[i]){
            primes.push_back(i);
         }
      }

      if(upper == MAXINT){ //special case, see top of function
         primes.push_back(MAXINT);
      }

      return primes;
   }


   bool checkers::isPrime(const int num){

      if(num%2==0 || num<2){
         return num==2 ? true: false;
      }

      //floor of square root of maximum unsigned 32-bit integer
      static const int ROOTMAXINT = 46340;
      static const auto primeStore = sieve(ROOTMAXINT);
      static const int nPrimeStore = primeStore.size();

      bool mightBePrime = true;

      for(int j=1; j<nPrimeStore; j++){ //can skip j=1 -> 2 since covered already
         const int prime = primeStore[j];
         if((prime*prime) > num){ //We have a prime
            break;
         }
         if(num%prime == 0){ //We have a composite
            mightBePrime = false;
            break;
         }
      }
      return mightBePrime;
   }


   bool checkers::isOddPrime(const int num){
      return (num%2==1) && isPrime(num);
   }


   bool checkers::isAdditivePrime(const int num){

      //if num isn't a prime it's not an additive prime;
      if(!isPrime(num)){
         return false;
      }
      //if num only has one digit must be an additive prime
      if(num<10){
         return true;
      }

      int sumDigits = 0;
      int current = num;

      while (current > 0) {
         sumDigits += current%10;
         current /= 10;
      }

      return isPrime(sumDigits);
   }


   bool checkers::isPalindromicPrime(const int num){
      //Quick checks
      if(num>999727999){
         return false;
      }
      if(num<10){
         if(num<2){
            return false;
         }
         if(num==2 || num==3 || num==5 || num==7){ //only primes below 10
            return true;
         }
         return false;
      }
      if(num%2==0 || num%5==0){ //2 and 5 only primes ending in 2 and 5
         return false;
      }

      //http://stackoverflow.com/questions/4806167/reverse-the-position-of-integer-digits
      int fromTop = num;
      int fromBottom = 0;

      while(fromTop > 0){
         fromBottom = 10*fromBottom + (fromTop%10);
         fromTop /= 10;
      }

      return fromBottom==num ? isPrime(num) : false;
   }


   bool checkers::isIsolatedPrime(const int num){
      if(num == 2147483647){ //special case, avoid overflow
         return true;
      }
      return isPrime(num) && !isPrime(num-2) && !isPrime(num+2);
   }


   bool checkers::isPythagoreanPrime(const int num){
      return num%4==1 && isPrime(num);
   }


   bool checkers::isSafePrime(const int num){
      return (num%2==1) && isPrime((num-1)/2) && isPrime(num);
   }
   
}
