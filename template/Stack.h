/*
 * Stack.h
 *
 *  Created on: Mar 18, 2017
 *      Author: lmtan91
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <vector>
#include <stdexcept>

using namespace std;
template <typename T>
class Stack
{
public:
   void push(T const&);
   void pop();
   T top() const;
   bool empty() const
   {
      return mElems.empty();
   }

private:
   vector<T> mElems;
};

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

#endif /* __STACK_H__ */
