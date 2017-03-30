/*
 * sumpolicy2.h
 *
 *  Created on: Mar 30, 2017
 *      Author: lia1hc
 */

#ifndef __SUMPOLICY2_H__
#define __SUMPOLICY2_H__

template <typename T1, typename T2>
class SumPolicy
{
public:
   static void accumulate(T1& total, T2 const & value)
   {
      total += value;
   }
};



#endif /* __SUMPOLICY2_H__ */
