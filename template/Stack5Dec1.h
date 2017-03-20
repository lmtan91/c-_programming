/*
 * Stack5Dec1.h
 *
 *  Created on: Mar 20, 2017
 *      Author: lia1hc
 */

#ifndef __STACK5DEC1_H__
#define __STACK5DEC1_H__

#include <deque>

template <typename T>
class Stack
{
public:
   void push(T const&);
   void pop();
   T top() const;
   bool empty() const
   {
      return elems.empty();
   }

   template <typename T2>
   Stack<T>& operator=(Stack<T2> const&);
private:
   std::deque<T> elems;
};

template <typename T>
void Stack<T>::push(T const& t)
{
   elems.push_back(t);
}

template <typename T>
void Stack<T>::pop()
{
   elems.pop_back();
}

template <typename T>
T Stack<T>::top() const
{
   return elems.back();
}

template <typename T>
template <typename T2>
Stack<T>& Stack<T>::operator =(Stack<T2> const& op2)
{
   if ((void *)this == (void *)&op2)
   {
      return *this;
   }

   elems.clear();

   Stack<T2> tmp(op2);
   while(!tmp.empty())
   {
      elems.push_front(tmp.top());
      tmp.pop();
   }
   return *this;
}


#endif /* __STACK5DEC1_H__ */
