/*
 * ebco2.cpp
 *
 *  Created on: Apr 10, 2017
 *      Author: lia1hc
 */

#include <iostream>

class Empty
{
   typedef int Int;
};

class EmptyToo : public Empty
{

};

class NonEmpty : public Empty, public EmptyToo
{

};

int main()
{
   std::cout << "sizeof(Empty):     " << sizeof(Empty)
         << '\n';
   std::cout << "sizeof(EmptyToo):  " << sizeof(EmptyToo)
         << '\n';
   std::cout << "sizeof(NonEmpty):  " << sizeof(NonEmpty)
         << '\n';
}
