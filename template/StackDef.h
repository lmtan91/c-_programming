/*
 * StackDef.h
 *
 *  Created on: Mar 21, 2017
 *      Author: lia1hc
 */

#ifndef __STACKDEF_H__
#define __STACKDEF_H__

#include "Stack9.h"

template <typename T>
void Stack<T>::push(T const& elem)
{
   elems.push_back(elem);
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

#endif /* __STACKDEF_H__ */
