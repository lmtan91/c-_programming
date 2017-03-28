/*
 * accum3.h
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM3_H__
#define __ACCUM3_H__

#include "accumtraits3.h"

template <typename T>
inline
typename AccumulationTraits<T>::AccT accum(T const* beg, T const* end)
{
   typedef typename AccumulationTraits<T>::AccT AccT;

   AccT total = AccumulationTraits<T>::zero;
   while (beg != end)
   {
      total += *beg;
      ++beg;
   }
   return total;
}

#endif /* __ACCUM3_H__ */
