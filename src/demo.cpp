//demo.cpp
#include <iostream>
#include "prime32.h"

void print(std::string s){
   std::cout << s << "\n";
}

template<typename S>
void print(std::string prefix, S s){
   std::cout << std::boolalpha; 
   std::cout << "\t" << prefix << " ";
   std::cout << s << "\n";
}

template<typename S>
void print(std::string prefix, std::vector<S> v){
   std::cout << std::boolalpha;
   std::cout << "\t" << prefix << " ";
   for(S s : v){
      std::cout << s << " ";
   }
   std::cout << "\n";
}

void blank(){std::cout << "\n";}


int main(){
   
   using namespace prime32;
   using std::vector;
   
   blank();
   print("------prime32 demo------");
   blank();
   
   print("1) sieve and check");
   vector<int> upto20 = sieve(20);
	print("1a)", upto20); //2 3 5 7 11 13 17 19
   print("1b)", check(upto20)); //true true true true true true true true
   print("1c)", check(upto20, "safe")); //false false true true true false false false
   blank();
   
   print("2) any and all");
   vector<int> even = {2, 4, 6, 8, 10};
   print("2a)", any(even)); //true
   print("2b)", any(even, "odd")); //false
   print("2c)", all(even)); //false
   print("2d)", all(even, "odd")); //false
   blank();
   
   print("3) select and remove");
   print("3a)", select(vector<int>{1, 2, 3, 4, 5})); //2 3 5
   print("3b)", select(upto20, "palindromic")); //2 3 5 7 11
   print("3c)", remove(upto20)); //empty
   print("3d)", remove(upto20, "additive")); //13 17 19
   blank();
   
   print("4) first");
   print("4a)", first(8) == upto20); //true
   print("4b)", first(8, "pythagorean")); //5 13 17 29 37 41 53 61
   blank();
   
   print("5) range");
   print("5a)", range(0,300) == range(300)); //true
   print("5b)", range(321, 456, "isolated")); //331 337 353 359 367 373 379 383 389 397 401 409 439 443 449
   blank();
   
   print("6) factoring");
   print("6a)", factoring(42)); //2 3 7
   print("6b)", factoring(23692)); //2 2 5923
   blank();
   
   print("------prime32 demo------");
   blank();
   
}