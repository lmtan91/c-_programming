/*
 * mainStack.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: lmtan91
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include "Stack.h"

using namespace std;
int main()
{
   try
   {
      Stack<int> intStack;
      Stack<string> stringStack;

      intStack.push(7);
      cout << intStack.top() << endl;

      stringStack.push("hello world!");
      cout << stringStack.top() << endl;
      stringStack.pop();
      stringStack.pop();
   }
   catch(exception const& ex)
   {
      cerr << "Exception: " << ex.what() << std::endl;
      return EXIT_FAILURE; // exit program with ERROR status
   }
   return 0;
}
