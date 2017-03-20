/*
 * Stack4.h
 *
 *  Created on: Mar 20, 2017
 *      Author: lia1hc
 *  nontype class template parameters
 */

#include <stdexcept>

template <typename T, int MAXSIZE>
class Stack
{
public:
   Stack();

   void push(T const&);

   void pop();

   T top() const;

   bool empty() const
   {
      return (mNumElems == 0);
   }

   bool full() const
   {
      return (mNumElems == MAXSIZE);
   }

private:
   T mElems[MAXSIZE];
   int mNumElems;
};


template <typename T, int MAXSIZE>
Stack<T, MAXSIZE>::Stack() : mNumElems(0)
{

}

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::push(T const& t)
{
   if (mNumElems == MAXSIZE)
   {
      throw std::out_of_range("Stack<>::push(): stack is full");
   }
   mElems[mNumElems] = t;
   mNumElems++;
}

template <typename T, int MAXSIZE>
void Stack<T, MAXSIZE>::pop()
{
   if (mNumElems <= 0)
   {
      throw std::out_of_range("Stack<>::pop(): stack is empty");
   }
   --mNumElems;
}

template <typename T, int MAXSIZE>
T Stack<T, MAXSIZE>::top() const
{
   if (mNumElems <= 0)
   {
      throw std::out_of_range("Stack<>::pop(): stack is empty");
   }
   return mElems[mNumElems - 1];
}
