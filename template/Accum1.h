/*
 * Accum1.h
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUM1_H__
#define __ACCUM1_H__

template <typename T>
inline
T accum(T const* beg, T const* end)
{
   T total = T();
   while (beg != end)
   {
      total += *beg;
      ++beg;
   }
   return total;
}


#endif /* __ACCUM1_H__ */
