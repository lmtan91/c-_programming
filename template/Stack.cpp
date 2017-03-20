/*
 * Stack.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: lmtan91
 */

#include "Stack.h"

template <typename T>
void Stack<T>::push(T const& elem)
{
   mElems.push_back(elem);
}

template <typename T>
void Stack<T>::pop()
{
   if (mElems.empty())
   {
      throw out_of_range("Stack<>::pop(): empty stack");
   }
   mElems.pop_back();
}

template <typename T>
T Stack<T>::top() const
{
   if (mElems.empty())
   {
      throw out_of_range("Stack<>::pop(): empty stack");
   }
   return mElems.back();
}
