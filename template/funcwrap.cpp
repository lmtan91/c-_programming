/*
 * funcwrap.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: lia1hc
 */

#include <vector>
#include <iostream>
#include <cstdlib>

// wrapper for function pointers to function objects
template<int (*FP)()>
class FunctionReturningIntWrapper {
  public:
    int operator() () {
       std::cout << "Enter FunctionReturningIntWrapper:operator()" << '\n';
        return FP();
    }
};

// example function to wrap
int random_int()
{
   std::cout << "Enter random_int()" << std::endl;
    return std::rand();  // call standard C function
}

// client that uses function object type as template parameter
template <typename FO>
void initialize (std::vector<int>& coll)
{
   std::cout << "Enter initialize" << std::endl;
    FO fo;  // create function object
    std::cout << "Enter initialize: create function object" << std::endl;
    for (std::vector<int>::size_type i=0; i<coll.size(); ++i) {
        coll[i] = fo();  // call function for function object
        std::cout << "Enter initialize: call function for function object" << std::endl;
    }
}

int main()
{
    // create vector with 10 elements
    std::vector<int> v(10);

    // (re)initialize values with wrapped function
    initialize<FunctionReturningIntWrapper<random_int> >(v);

    // output elements
    for (std::vector<int>::size_type i=0; i<v.size(); ++i) {
        std::cout << "coll[" << i << "]: " << v[i] << std::endl;
    }
}


