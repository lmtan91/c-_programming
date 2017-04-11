/*
 * pow3b.h
 *
 *  Created on: Apr 11, 2017
 *      Author: lia1hc
 */

#ifndef __POW3B_H__
#define __POW3B_H__

template <int N>
class Pow3
{
public:
   static int const result = 3 * Pow3<N-1>::result;
};

template <>
class Pow3<0>
{
public:
   static int const result = 1;
};



#endif /* __POW3B_H__ */
