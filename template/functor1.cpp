/*
 * functor1.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: lia1hc
 */

#include <iostream>

class ConstantIntFunctor
{
private:
   int value;
public:
   ConstantIntFunctor(int c) : value(c)
   {
   }

   int operator() () const
   {
      return value;
   }
};

void client(ConstantIntFunctor const& cif)
{
   std::cout << "calling back functor yields " << cif() <<'\n';
}

int main()
{
   ConstantIntFunctor seven(7);
   ConstantIntFunctor fortytwo(42);
   client(seven);
   client(fortytwo);
}
