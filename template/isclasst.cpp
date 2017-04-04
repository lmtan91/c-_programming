/*
 * isclasst.cpp
 *
 *  Created on: Apr 3, 2017
 *      Author: lia1hc
 */

#include <iostream>
#include "isclasst.h"

class MyClass
{
};

struct MyStruct
{
};

union MyUnion
{
};

void myfunc()
{
}

enum E{e1}e;

// check by passing
template <typename T>
void check()
{
   if (IsClassT<T>::Yes)
   {
      std::cout << " IsClassT " << std::endl;
   }
   else
   {
      std::cout << " !IsClassT " << std::endl;
   }
}

// check by passing type as function call argument
template <typename T>
void checkT(T)
{
   check<T>();
}

int main()
{
   std::cout << "int: ";
   check<int>();

   std::cout << "MyClass: ";
   check<MyClass>();

   std::cout << "MyStruct: ";
   MyStruct s;
   checkT(s);

   std::cout << "MyUnion: ";
   check<MyUnion>();

   std::cout << "enum: ";
   checkT(e);

   std::cout << "myfunc():";
   checkT(myfunc);
}
