/*
 * accumtraits3.h
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUMTRAITS3_H__
#define __ACCUMTRAITS3_H__


template <typename T>
class AccumulationTraits;

template <>
class AccumulationTraits<char>
{
public:
   typedef int AccT;
   static AccT const zero = 0;
};

template <>
class AccumulationTraits<short>
{
public:
   typedef int AccT;
   static AccT const zero = 0;
};

template <>
class AccumulationTraits<int>
{
public:
   typedef long AccT;
   static AccT const zero = 0;
};

#endif /* __ACCUMTRAITS3_H__ */
