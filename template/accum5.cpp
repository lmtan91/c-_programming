/*
 * accum4.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#include "accum5.h"
#include <iostream>

int main()
{
   int num[]={1,2,3,4,5};
   std::cout << "the average value of the integer values is "
   << Accum<int>::accum(&num[0], &num[5]) / 5
   << '\n';

   char name[] = "templates";
   int length = sizeof(name)-1;

   std::cout << "the average value of the characters in \""
   << name << "\" is "
   << Accum<char>::accum(&name[0], &name[length]) / length
   << '\n';
}


