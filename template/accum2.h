/*
 * accum2.h
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM2_H__
#define __ACCUM2_H__

#include "accumtraits2.h"

template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const* beg, T const* end)
{
   typedef typename AccumulationTraits<T>::AccT AccT;

   AccT total = AccT();
   while (beg != end)
   {
      total += *beg;
      ++beg;
   }
   return total;
}

#endif /* __ACCUM2_H__ */
