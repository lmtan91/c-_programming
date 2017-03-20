/*
 * stack3test.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: lmtan91
 */

#include <iostream>
#include <deque>
#include <cstdlib>
#include "Stack3.h"

int main()
{
   try
   {
      // stack of ints
      Stack<int> intStack;
      Stack<double, std::deque<double> > dblStack;

      intStack.push(7);
      std::cout << intStack.top() << endl;
      intStack.pop();

      dblStack.push(17.12);
      std::cout << dblStack.top() << endl;
      dblStack.pop();
      dblStack.pop();
   }
   catch (std::exception const& ex)
   {
      std::cerr << "Exception: " << ex.what() << std::endl;
      return EXIT_FAILURE;
   }
}
