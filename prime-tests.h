#ifndef _PRIMETESTS_
#define _PRIMETESTS_

#include <vector>

//using PtToBoolFunc = bool (*)(const int);
//typedef bool (*PtToBoolFunc)(const int);
//const int NA_INTEGER = -2147483648;

namespace PrimeTests{
	//const int MAXINT = 2147483647; largest 32-bit signed int and 105097565th prime
	const int ROOTMAXINT = 46340; //floor of square root of above
	std::vector<int> sievePrimes(const int upper);
	bool isPrime(const int num);
	bool isOddPrime(const int num);
	bool isAdditivePrime(const int num);
	bool isPalindromicPrime(const int num);
	bool isIsolatedPrime(const int num);
	bool isPythagoreanPrime(const int num);
	bool isSafePrime(const int num);
}

#endif
