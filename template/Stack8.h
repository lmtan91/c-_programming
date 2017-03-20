/*
 * Stack8.h
 *
 *  Created on: Mar 20, 2017
 *      Author: lia1hc
 */

#ifndef __STACK8_H__
#define __STACK8_H__

#include <deque>
#include <stdexcept>
#include <allocator>

template <typename T,
          template <typename ELEM,
                    typename = std::allocator<ELEM> >
                    class CONT = std::deque>
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
   template <typename T2,
            template <typename ELEM2,
                      typename = std::allocator<ELEM2> >
                      class CONT2>
   Stack<T, CONT>& operator=(Stack<T2, CONT2> const&);

private:
   CONT<T> elems;
};


#endif /* __STACK8_H__ */
