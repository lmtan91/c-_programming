/*
 * bd_vector.h
 *
 *  Created on: Aug 14, 2017
 *      Author: lia1hc
 */

#ifndef INCLUDE_BD_VECTOR_H_
#define INCLUDE_BD_VECTOR_H_

#include <stdio.h>

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
         printf("vector 0\n");
      }

      explicit vector(unsigned allocated)
      : mAllocated(allocated),
        mData((T*)(new uint8_t[sizeof(T) * mAllocated])),
        mSize(0)
      {
         printf("vector 1\n");
      }

      vector(const vector<T>& rhs)
      : mAllocated(0),
        mData(NULL),
        mSize(0)
      {
         *this = rhs;
      }

      ~vector()
      {
         if(mData)
         {
            clear();

            delete[] (uint8_t*)mData;
            mData = NULL;
         }
      }

      T& operator [] (unsigned int ind)
      {
         if (ind >= mSize)
            return *(T*)NULL;

         return mData[ind];
      }

      const T& operator [] (unsigned int ind) const
      {
         if (ind >= mSize)
            return *(T*)NULL;

         return mData[ind];
      }

      vector<T>& operator = (const vector<T>& rhs)
      {
         clear();

         if (mAllocated < rhs.mSize)
         {
            sizeup(rhs.mSize);
         }
         for (unsigned int i = 0; i < rhs.mSize; i++)
         {
            new (mData + i) T(rhs.mData[i]);
         }

         mSize = rhs.mSize;
         return *this;
      }

      void push_back(const T& val)
      {
         printf("push_back\n");
         if (mSize == mAllocated)
         {
            sizeup();
         }
         new(mData + mSize) T(val);

         mSize++;
      }

      void erase(unsigned int ind)
      {
         if (ind >= mSize)
            abort();

         for (unsigned int i = ind; i < mSize - 1; i++)
         {
            mData[mSize - 1].~T();
            mSize--;
         }
      }

      void reserve(unsigned int size)
      {
         if (mAllocated < size)
         {
            sizeup(size);
         }
      }

      void resize(unsigned int newSize)
      {
         if (mAllocated < newSize)
         {
            if (newSize < mAllocated * 2)
            {
               sizeup();
            } else {
               sizeup(newSize);
            }
         }

         for (unsigned int i = newSize; i < mSize; i++)
         {
            mData[i].~T();
         }

         for (unsigned int i = mSize; i < newSize; i++)
         {
            new(mData + i) T();
         }
         mSize = newSize;
      }

      unsigned int size() const { return mSize; }

      bool empty() const { return mSize == 0; }

      void clear()
      {
         for (unsigned int i = 0; i < mSize; i++)
         {
            mData[i].~T();
         }
         mSize = 0;
      }
   private:
      void sizeup(unsigned int newSize = 0)
      {
         printf("sizeup\n");
         if (newSize == 0)
         {
            if (mAllocated)
            {
               newSize = mAllocated * 2;
            } else {
               newSize = DEFAULT_ALLOCATION;
            }
         }

         T* temp = (T*)(new uint8_t[sizeof(T) * newSize]);

         if (mData)
         {
            for (unsigned int i = 0; i < mSize; i++)
            {
               new(temp + i) T(mData[i]);
               mData[i].~T();
            }
            delete[] (uint8_t*)mData;
         }
         mData = temp;
         mAllocated = newSize;
      }

      unsigned int mAllocated;
      T* mData;
      unsigned int mSize;

   };
};

#endif /* INCLUDE_BD_VECTOR_H_ */
