/*
 * stack5test.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: lia1hc
 */

#include <iostream>
#include "Stack5Dec1.h"

int main()
{
   Stack<int> intStack;
   Stack<float> flStack;

   intStack.push(17);
   intStack.push(12);

   flStack = intStack;

   std::cout << flStack.top() << std::endl;
   flStack.pop();
   std::cout << flStack.top() << std::endl;
   flStack.pop();
}


