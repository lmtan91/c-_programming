/*
 * accum3.h
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM4_H__
#define __ACCUM4_H__

#include "accumtraits4.h"

template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const* beg, T const* end)
{
   typedef typename AccumulationTraits<T>::AccT AccT;

   AccT total = AccumulationTraits<T>::zero();
   while (beg != end)
   {
      total += *beg;
      ++beg;
   }
   return total;
}

#endif /* __ACCUM4_H__ */
