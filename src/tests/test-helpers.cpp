#include "test-helpers.h"

std::vector<int> testHelpers::getIntsFromFile(const std::string fName){
   std::ifstream input;
   input.open(fName);
   if (!input){
      throw std::invalid_argument("File not found.");
   }
   std::vector<int> data;
   int val;
   while(input >> val){
      data.push_back(val);
   }
   input.close();
   return data;
}


bool testHelpers::allEqual(const std::vector<int> v1, const std::vector<int> v2){
   if(v1.size() != v2.size()){
      return false;
   }
   return std::equal(v1.begin(), v1.end(), v2.begin());
}

bool testHelpers::allEqual(const std::vector<bool> v1, const std::vector<bool> v2){
   if(v1.size() != v2.size()){
      return false;
   }
   return std::equal(v1.begin(), v1.end(), v2.begin());
}

std::vector<bool> testHelpers::intToBool(const std::vector<int> v1){
   const int n = v1.size();
   std::vector<bool> out(n);
   for(int i=0; i<n; i++){
      if(v1[i]>0){
         out[i] = true;
      }
   }
   return out;
}

std::vector<int> testHelpers::sequence(const int first, const int last, const int step){
   if(first > last){
      std::range_error("first cannot be greater than last");
   }
   std::vector<int> out;
   for(int i=first; i<= last; i+=step){
      out.push_back(i);
   }
   return out;  
}
