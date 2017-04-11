/*
 * pow3.h
 *
 *  Created on: Apr 11, 2017
 *      Author: lia1hc
 */

#ifndef __POW3_H__
#define __POW3_H__

template <int N>
class Pow3
{
public:
   enum
   {
      result = 3 * Pow3<N-1>::result
   };
};

template <>
class Pow3<0>
{
public:
   enum
   {
      result = 1
   };
};

#endif /* __POW3_H__ */
