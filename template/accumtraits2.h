/*
 * accumtraits2.h
 *
 *  Created on: Mar 28, 2017
 *      Author: lia1hc
 */

#ifndef __ACCUMTRAITS2_H__
#define __ACCUMTRAITS2_H__

template <typename T>
class AccumulationTraits;

template <>
class AccumulationTraits<char>
{
public:
   typedef int AccT;
};

template <>
class AccumulationTraits<short>
{
public:
   typedef int AccT;
};

template <>
class AccumulationTraits<int>
{
public:
   typedef long AccT;
};

template <>
class AccumulationTraits<unsigned int>
{
public:
   typedef unsigned long AccT;
};

template <>
class AccumulationTraits<float>
{
public:
   typedef double AccT;
};

#endif /* __ACCUMTRAITS2_H__   */
