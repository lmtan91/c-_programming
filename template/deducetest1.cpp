/*
 * deducetest1.cpp
 *
 *  Created on: Mar 23, 2017
 *      Author: lia1hc
 */


//#include "Array.h"
#include <iostream>
int main()
{

   //int g = max(1, 2.0);
   int x = 17;
   int y = 7;
   const int *p = &x;
   std::cout << *p << std::endl;
   x = 13;
   std::cout << *p << std::endl;
   p = &y;
   std::cout << *p << std::endl;

   int * const q = &x;
   std::cout << *q << std::endl;
   *q = y;
   std::cout << *q << std::endl;

   return 0;
}

