#ifndef _PRIME32TESTHELPERS_
#define _PRIME32TESTHELPERS_

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>


namespace testHelpers{
   std::vector<int> getIntsFromFile(const std::string fName);
   bool allEqual(const std::vector<int> v1, const std::vector<int> v2);
   bool allEqual(const std::vector<bool> v1, const std::vector<bool> v2);
   std::vector<bool> intToBool(const std::vector<int> v1); 
   std::vector<int> sequence(const int first, const int last, const int step = 1);
}

#endif