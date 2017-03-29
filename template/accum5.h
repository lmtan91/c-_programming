/*
 * accum5.h
 *
 *  Created on: Mar 29, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM5_H__
#define __ACCUM5_H__

#include "accumtraits4.h"

template <typename T, typename AT = AccumulationTraits<T> >
class Accum
{
public:
   static typename AT::AccT accum(T const* beg, T const* end)
   {
      typename AT::AccT total = AT::zero();
      while (beg != end)
      {
         total += *beg;
         ++beg;
      }
      return total;
   }
};


#endif /* __ACCUM5_H__ */
