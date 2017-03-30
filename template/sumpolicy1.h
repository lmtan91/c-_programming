/*
 * sumpolicy1.h
 *
 *  Created on: Mar 29, 2017
 *      Author: lia1hc
 */

#ifndef __SUMPOLICY1_H__
#define __SUMPOLICY1_H__

class SumPolicy
{
public:
    template <typename T1, typename T2>
    static void accumulate(T1& total, T2 const & value)
    {
       total += value;
    }
};



#endif /* __SUMPOLICY1_H__ */
