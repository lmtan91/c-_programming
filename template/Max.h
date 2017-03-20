/*
 * Max.h
 *
 *  Created on: Mar 18, 2017
 *      Author: lmtan91
 */

#ifndef __MAX_H__
#define __MAX_H__

template <typename T>
inline T const& max(T const& a, T const& b)
{
   return a > b ? a : b;
}



#endif /* __MAX_H__ */
