*v0.1.0*

# prime32
***prime32*** is a small C++ library that provides functions for finding and dealing with primes numbers that fit in a 32-bit signed int (that is, integers less than or equal to 2,147,483,647).

## Installation
To compile on UNIX/Linux/OSX..., `cd` into the root directory and run `make`. This creates, among other things, a library archive *prime32.a*.  `#include` the *prime32.h* header file (in the inc *directory*) in your source code. For example:

``` c++
//myapp.cpp
#include <iostream>
#include "path/to/prime32/inc/prime32.h"

int main(){
  auto primes = prime32::sieve(1000);
  for(int val : primes){
    std::cout << val << "\n"; //prints out all prime numbers <= 1000
  }
}
```

Then, when you compile your source code, mark *prime32.a* (in the *lib* directory) as a dependency and use the C++11 flag (or later). For example:

``` bash
g++ -std=c++11 -o myapp myapp.cpp path/to/prime32/lib/prime32.a
```

## Functions
***prime32*** contains 9 primary functions plus a few helper functions. The primary functions (all in the `prime32` namespace) are:
* `sieve`: returns a vector of all prime numbers up to (and including) the integer value passed in. (The function uses a [sieve of Erastothenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes) algorithm, hence the name.)
* `check`: takes a vector of integers and returns a vector of Booleans denoting whether the corresponding input element is or is not a prime.
* `any`: takes a vector of integers and returns true if the vector contains any prime numbers.
* `all`: like `any`, except only returns true if all elements of the input vector are prime numbers.
* `select`: returns a vector of integers containing only the elements of its integer vector input that are prime.
* `remove`: returns a vector of integers containing only the elements of its integer-vector input that are *not* prime.
* `first`: returns a vector of integers containing the first *n* prime numbers where *n* is the integer value supplied as first argument. If *n* is larger than the number of primes less than or equal to 2,147,483,647, all primes up to and including 2,147,483,647 will be returned. In this case, `first(n).size()` will be less than *n*.
* `range`: returns a vector of integers containing all integers between its first and second arguments (inclusive). The first argument must be less than or equal to the second argument. The function is overloaded so that only the upper bound needs to be supplied, with the lower bound assumed to be 0 if omitted. In this case it is usually faster to use `sieve`.
* `factoring`: returns a vector of integers that holds, in ascending order, the [prime factors](https://en.wikipedia.org/wiki/Fundamental_theorem_of_arithmetic) of the supplied integer argument. If the argument is less than 2 then an empty integer vector is returned.

Each of these functions except for `sieve` and `factoring` take an optional final string argument that specifies the [type of prime number](https://en.wikipedia.org/wiki/List_of_prime_numbers) under consideration. Specifically:
* **unfiltered**: the same as no argument. Will `check` for, `select`, etc any prime number of any kind.
* **odd**: prime numbers that are odd. Essentially the same as **unfiltered**, except for the number 2.
* **additive**: prime numbers whose digits (in base 10) sum to a prime number.
* **palindromic**: prime numbers whose (base 10) digits read the same forwards and backwards.
* **isolated**: prime numbers that do not have a prime number ±2 away from them. For example, 2 and 23 are safe primes, 3 and 5 are not.
* **pythagorean**: prime numbers such that when 1 is subtracted from them and that number is divided by 4, the result is an integer. For example, 5 and 13 are pythagorean primes, 2 and 23 are not.
* **safe**: prime numbers such that when 1 is subtracted from them and that number is divided by 2, the result is another prime number. For example, 11 and 23 are safe primes, 3 and 13 are not.

The declarations for these functions are all found in *prime32.h* in the *inc* folder:

``` c++
//prime32.h
//headers omitted
namespace prime32{
   //some uninteresting stuff omitted
   std::vector<bool> check(const std::vector<int> & nums, const std::string type="unfiltered");
   bool all(const std::vector<int> & nums, std::string type="unfiltered");
   std::vector<int> remove(const std::vector<int> & nums, std::string type="unfiltered");
   std::vector<int> first(const int n, std::string type="unfiltered");
   std::vector<int> range(const int lower, const int upper, std::string type="unfiltered");
   std::vector<int> range(const int upper, std::string type="unfiltered");
   std::vector<int> factoring(const int num);
}
```

## Usage
The code below, which can be found in the *src* directory and compiled and executed using `make demo` from the root directory, illustrates some simple usage of all these functions.

``` c++
//demo.cpp
#include <iostream>
#include "../prime32.h"

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
```
