/*
 * stack9test.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: lia1hc
 *  inclusion model
 */

#include <iostream>
#include "StackDef.h"

int main(void)
{
   Stack<int> intStack;
   intStack.push(17);
   std::cout << intStack.top() << std::endl;
   intStack.pop();

   return 0;
}
