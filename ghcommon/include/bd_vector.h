/*
 * bd_vector.h
 *
 *  Created on: Aug 14, 2017
 *      Author: lia1hc
 */

#ifndef INCLUDE_BD_VECTOR_H_
#define INCLUDE_BD_VECTOR_H_

#include <stdlib.h>
#include <stdint.h>
#include <memory>

namespace Bodhi
{
   template <typename T>
   class vector
   {
   public:
      static const unsigned int DEFAULT_ALLOCATION = 32;

      vector()
      : mAllocated(DEFAULT_ALLOCATION),
        mData((T*)(new uint8_t[sizeof(T) * mAllocated])),
        mSize(0)
      {

      }
   private:
      unsigned int mAllocated;
      T* mData;
      unsigned int mSize;

   };
};

#endif /* INCLUDE_BD_VECTOR_H_ */
