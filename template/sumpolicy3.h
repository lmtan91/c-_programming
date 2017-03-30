/*
 * sumpolicy3.h
 *
 *  Created on: Mar 30, 2017
 *      Author: lia1hc
 */

#ifndef __SUMPOLICY3_H__
#define __SUMPOLICY3_H__

template<bool use_conpound_op = true>
class SumPolicy
{
public:
   template <typename T1, typename T2>
   static void accumulate(T1& total, T2 const & value)
   {
      total += value;
   }
};

template <>
class SumPolicy<false>
{
public:
   template <typename T1, typename T2>
   static void accumulate(T1& total, T2 const & value)
   {
      total = total + value;
   }
};

#endif /* __SUMPOLICY3_H__ */
