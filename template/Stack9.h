/*
 * Stack9.h
 *
 *  Created on: Mar 21, 2017
 *      Author: lia1hc
 */

#ifndef __STACK9_H__
#define __STACK9_H__

#include <vector>

template <typename T>
class Stack
{
public:
   Stack();
   void push(T const&);
   void pop();
   T top() const;
private:
   std::vector<T> elems;
};

#endif /* __STACK9_H__ */
