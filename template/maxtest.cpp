/*
 * maxtest.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: lmtan91
 *  This test is for function template example
 */

#include <iostream>
#include <string>
#include "Max.h"

int main()
{
   int i = 42;
   std::cout << "max(7,i): " << ::max(7,i) << std::endl;
   double f1 = 3.4;
   double f2 = -6.7;
   std::cout << "max(f1,f2): " << ::max(f1,f2) << std::endl;
   std::string s1 = "mathematics";
   std::string s2 = "math";
   std::cout << "max(s1,s2): " << ::max(s1,s2) << std::endl;
}
