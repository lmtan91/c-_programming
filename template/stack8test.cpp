/*
 * stack8test.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: lmtan91
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Stack8.h"

int main()
{
   try
   {
      Stack<int> intStack;
      Stack<float> floatStack;

      intStack.push(17);
      intStack.push(12);

      floatStack.push(13.13);

      floatStack = intStack;

      std::cout << floatStack.top() << std::endl;
      floatStack.pop();
      std::cout << floatStack.top() << std::endl;
      floatStack.pop();
      std::cout << floatStack.top() << std::endl;
      floatStack.pop();
   }
   catch (std::exception const& ex)
   {
      std::cerr << "Exception: " << ex.what() << std::endl;
   }

   Stack<int, std::vector> vStack;
   vStack.push(17);
   vStack.push(12);
   std::cout << vStack.top() << std::endl;
   vStack.pop();
   return 0;
}
