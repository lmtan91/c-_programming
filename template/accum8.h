/*
 * accum8.h
 *
 *  Created on: Mar 30, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM8_H__
#define __ACCUM8_H__

#include "accumtraits4.h"
#include "sumpolicy2.h"
template <typename T, template<typename, typename> class Policy = SumPolicy,
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
         Policy<AccT,T>::accumulate(total, *beg);
         ++beg;
      }
      return total;
   }
};

#endif /* __ACCUM8_H__ */
