#include "primes.h"

std::vector<int> PrimeTests::sievePrimes(const int upper){
	
   using IntVector = std::vector<int>;
   
   if(upper<2){
	  return IntVector();
   }
   
   std::vector<bool> sieveArray = std::vector<bool>(upper+1); //defaults to false
   sieveArray[1] = false;
   sieveArray[2] = true;
   
   int nPossPrimes = (upper+1)/2;
   
   if(upper>=3){
	  
	  for(int i=3; i<=upper; i+=2){ //set odd to true
		 sieveArray[i] = true;
	  }
	  
	  int p = 3;
	  int pSquared = p*p;
	  while(pSquared <= upper){
		 if(sieveArray[p]){
			const int pTwo = 2*p;
			for(int i=pSquared; i<=upper; i+=pTwo){
			   //check isn't already false before altering and decrementing
			   if(sieveArray[i]){ 
				  sieveArray[i] = false;
				  nPossPrimes--;
			   }
			}
		 }
		 p += 2;
		 pSquared = p*p;
	  }
   }
   
   const int nPrimes = nPossPrimes; //our number of primes is now fixed;
   IntVector primes = IntVector(nPrimes);
   int counter = 0;
   
   for(int i=0; i<=upper; i++){
	  if(sieveArray[i]){
		 primes[counter] = i;
		 counter++;
		 if(counter == nPrimes){
			break;
		 }
	  }
   }
   
   return primes;
}


bool PrimeTests::isPrime(const int num){
   static const auto primeStore = sievePrimes(ROOTMAXINT);
	
   if(num%2==0 || num<2){
	  return num==2 ? true: false;
   }
   
   bool mightBePrime = true;
   const int nPrimeStore = primeStore.size();
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



bool PrimeTests::isOddPrime(const int num){
   return (num%2==1) && isPrime(num);
}


bool PrimeTests::isAdditivePrime(const int num){
   
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


bool PrimeTests::isPalindromicPrime(const int num){
   //if num isn't a prime it's not a palindromic prime;
   if(!isPrime(num)){
	  return false;
   }
   //if num only has one digit must be a palindromic prime
   if(num<10){
	  return true;
   }
   
   //http://stackoverflow.com/questions/4806167/reverse-the-position-of-integer-digits
   int fromTop = num;
   int fromBottom = 0;
   
   while(fromTop > 0){
	   fromBottom = 10*fromBottom + (fromTop%10);
	   fromTop /= 10;
   }
   
   return fromBottom == num;
}


bool PrimeTests::isIsolatedPrime(const int num){
   //last item should never be evaluated for MAXINT as MAXINT-2 not prime
   return isPrime(num) && !isPrime(num-2) && !isPrime(num+2);
}


bool PrimeTests::isPythagoreanPrime(const int num){
   return num%4==1 && isPrime(num);
}


bool PrimeTests::isSafePrime(const int num){
   return (num%2==1) && isPrime((num-1)/2) && isPrime(num);
}
