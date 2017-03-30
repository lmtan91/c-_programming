/*
 * accum0.h
 *
 *  Created on: Mar 30, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM0_H__
#define __ACCUM0_H__

#include <iterator>

template <typename Iter>
inline typename std::iterator_traits<Iter>::value_type
accum(Iter start, Iter end)
{
   typedef typename std::iterator_traits<Iter>::value_type VT;

   VT total = VT();
   while (start != end)
   {
      total += *start;
      ++start;
   }
   return total;
}

#endif /* __ACCUM0_H__ */
