/*
 * funcptr.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: lia1hc
 */

#include <iostream>
#include <typeinfo>

void foo()
{
   std::cout << "foo() called" << std::endl;
}

// FooT is a function type,
// the same type as that of function foo()
typedef void FooT();

int main()
{
   // direct call
   foo();

   std::cout << "Types of foo: " << typeid(foo).name()
             << '\n';
   std::cout << "Types of FooT: "<< typeid(FooT).name()
                << '\n';

   FooT* pf = foo;   // implicit conversion(decay)
   pf();             // indirect call through pointer
   (*pf)();          // equivalent to pf();

   // print type of pf
    std::cout << "Types of pf:   " << typeid(pf).name()
              << '\n';

    FooT& rf = foo;     // no implicit conversion
    rf();               // indirect call through reference

    // print type of rf
     std::cout << "Types of rf:   " << typeid(rf).name()
               << '\n';
}
