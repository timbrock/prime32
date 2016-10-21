#include <iostream>
//#include <vector>
#include "primetests.h"

int main(){
	using namespace PrimeTests;
	for(int i=0; i<200; i++){
		if(isPythagoreanPrime(i)){
			std::cout << "i = " << i << ".\n";			
		}
	}
}