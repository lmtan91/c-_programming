/*
 * isclasst.h
 *
 *  Created on: Apr 3, 2017
 *      Author: lia1hc
 */

#ifndef __ISCLASST_H__
#define __ISCLASST_H__

template <typename T>
class IsClassT
{
private:
   typedef char One;
   typedef struct
   {
      char a[2];
   } Two;
   template<typename C> static One test(int C::*);
   template<typename C> static Two test(...);

public:
   enum
   {
      Yes = sizeof(IsClassT<T>::test<T>(0)) == 1
   };
   enum
   {
      No = !Yes
   };
};



#endif /* __ISCLASST_H__ */
