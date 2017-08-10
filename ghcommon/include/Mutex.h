/*
 * Mutex.h
 *
 *  Created on: Aug 10, 2017
 *      Author: lia1hc
 */

#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>
#include "Thread.h"

class Mutex
{

public:

   /**
    *
    */
   Mutex( bool recursive = false );
   /**
    *
    */
   Mutex( const char *name, bool recursive = false );
   /**
    * Mutex destruction
    */
   ~Mutex();

   /**
    *
    */
   int Lock();

   /**
    *
    */
   int TraceTryLock( const char *file, int line );

   /**
    *
    */
   int TraceUnlock( const char *file, int line );

   /**
    *
    */
   int TraceLock( const char *file, int line );
   /**
    *
    */
   int TryLock();

   /**
    *
    */
   int Unlock();


   /**
    *
    */
   bool isLocked();

   /**
    * Init
    */
   static void Init()
   {
      if ( not mInited )
      {
         mInited = true;
         pthread_mutex_init( &mCriticalSection, NULL );
      }
   }

   /**
    * getOwner
    */
   const char *getOwner();
   /**
    * ExitCriticalSection
    */
   static void ExitCriticalSection();

   /**
    * EnterCriticalSection
    */
   static void EnterCriticalSection();
   /**
    * Destroy
    */
   static void Destroy();
private:
   /**
    * Create lock
    */
   void create_lock();

   Thread                  *mLockedBy;

   /**
    * This supposed to be the file name where the lock was last grabbed
    */
   const char              *mLockFile;

   /**
    * This supposed to be the line number in the file where the lock was last grabbed
    */
   int                     mLockLine;

   pthread_mutex_t         mMutex;
   const char              *mName;
   bool                    mRecursive;

   int                     mLockCount;

   static pthread_mutex_t  mCriticalSection;
   static bool             mInited;
};

#endif /* _MUTEX_H_ */
