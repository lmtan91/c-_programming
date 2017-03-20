/*
 * Stack7Dec1.h
 *
 *  Created on: Mar 20, 2017
 *      Author: lia1hc
 */

#ifndef __STACK7DEC1_H__
#define __STACK7DEC1_H__

#include <deque>

template <typename T,
          template <typename ELEM> class CONT = std::deque >
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

private:
   CONT<T> elems;
};



#endif /* __STACK7DEC1_H__ */
