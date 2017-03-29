/*
 * accum6.h
 *
 *  Created on: Mar 29, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM6_H__
#define __ACCUM6_H__

#include "sumpolicy1.h"
#include "accumtraits4.h"

template <typename T, typename Policy = SumPolicy,
          typename Traits = AccumulationTraits<T> >
class Accum
{
public:
   typedef typename Traits::AccT AccT;
   static AccT accum(T const* beg, T const* end)
   {
      AccT total = Traits::zero();
      while (beg != end)
      {
         Policy::accumulate(total, *beg);
         ++beg;
      }
      return total;
   }
};

#endif /* __ACCUM6_H__ */
