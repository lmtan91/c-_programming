/*
 * accumtraits4.h
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUMTRAITS4_H__
#define __ACCUMTRAITS4_H__

template <typename T>
class AccumulationTraits;

template <>
class AccumulationTraits<char>
{
public:
   typedef int AccT;
   static AccT zero()
   {
      return 0;
   }
};

template <>
class AccumulationTraits<short>
{
public:
   typedef int AccT;
   static AccT zero()
   {
      return 0;
   }
};

template <>
class AccumulationTraits<int>
{
public:
   typedef long AccT;
   static AccT zero()
   {
      return 0;
   }
};

template <>
class AccumulationTraits<unsigned int>
{
public:
   typedef unsigned long AccT;
   static AccT zero()
   {
      return 0;
   }
};

template <>
class AccumulationTraits<float>
{
public:
   typedef double AccT;
   static AccT zero()
   {
      return 0;
   }
};

#endif /* __ACCUMTRAITS4_H__ */
