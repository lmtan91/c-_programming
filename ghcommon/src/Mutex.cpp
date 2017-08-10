/*
 * Mutex.cpp
 *
 *  Created on: Aug 10, 2017
 *      Author: lia1hc
 */
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include "Mutex.h"

bool Mutex::mInited = false;

Mutex::Mutex( bool recursive )
: mLockedBy( NULL ), mName( NULL ), mRecursive( recursive ), mLockCount( 0 )
{
   create_lock();
}

Mutex::Mutex( const char *name, bool recursive )
: mLockedBy( NULL ), mName( name ), mRecursive( recursive ), mLockCount( 0 )
{
   create_lock();
}

Mutex::~Mutex()
{
   int ret = pthread_mutex_destroy( &mMutex );

   if ( ret )
   {
      if ( ret == EINVAL )
      {
         printf("pthread_mutex_destroy() failed with EINVAL\n");
      }
      else if ( ret == EBUSY )
      {
         printf("pthread_mutex_destroy() failed with EBUSY\n");
      }
      else
      {
         printf("pthread_mutex_destroy() failed with %d\n", ret);
      }
   }
}

int Mutex::Lock()
{
   return TraceLock( "unknown", 0 );
}

int Mutex::TryLock()
{
   return TraceTryLock( "unknown", 0 );
}

int Mutex::Unlock()
{
   return TraceUnlock( "unknown", 0 );
}

int Mutex::TraceLock( const char *file, int line )
{
   int res = pthread_mutex_lock( &mMutex );

   if ( res == EDEADLK )
   {
      printf( "Lock %s already taken at %s:%d\n",
                  mName, mLockFile, mLockLine );
      return res;
   }
   else if (res != 0 )
   {
      printf( "Lock %s failed with error %d at %s:%d\n",
                  mName, res, file, line );
      return res;
   }

   if ( mRecursive and mLockCount == 0 )
   {
      mLockedBy = Thread::GetCurrent();
      mLockFile = file;
      mLockLine = line;
      ++mLockCount;
   }
   else
   {
      mLockedBy = Thread::GetCurrent();
      mLockFile = file;
      mLockLine = line;
   }
   return res;
}

int Mutex::TraceTryLock( const char *file, int line )
{
   int ret = pthread_mutex_trylock( &mMutex );

   if ( ret == 0 )
   {
      if ( mRecursive and mLockCount == 0 )
      {
         mLockedBy = Thread::GetCurrent();
         mLockFile = file;
         mLockLine = line;
         ++mLockCount;
      }
      else
      {
         mLockedBy = Thread::GetCurrent();
               mLockFile = file;
               mLockLine = line;
      }
   }
   return ret;
}

int Mutex::TraceUnlock( const char *file, int line )
{
   Thread* lockedBy = mLockedBy;
   int lockCount = mLockCount;
   if ( mRecursive and --mLockCount <= 0 )
   {
      mLockedBy = NULL;
      mLockCount = 0;
   }
   else
   {
      mLockedBy = NULL;
   }

   int ret = pthread_mutex_unlock( &mMutex );

   // Check to se if user tried to unlock a mutex that they don't own and
   // try ro restore the state
   if ( ret == EPERM )
   {
      printf( "Unlock lock %s that isn't locked by current thread at %s:%d "
            "(held by %s@%s:%d) error %d",
            mName, file, line,
            lockedBy != NULL ? lockedBy->GetName() : "nobody",
                  mLockFile, mLockLine, ret );

      mLockedBy = lockedBy;
      mLockCount = lockCount;
   }
   else if ( ret != 0 )
   {
      printf( "Unlock lock %s failed with error %d at %s:%d\n",
                        mName, ret, file, line);
   }

   return ret;
}

bool Mutex::isLocked()
{
   return ( mLockedBy == Thread::GetCurrent() );
}

const char *Mutex::getOwner()
{
   if ( mLockedBy != NULL )
   {
      return mLockedBy->GetName();
   }
   else
   {
      return NULL;
   }
}

#define GH_PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#define GH_PTHREAD_MUTEX_ERRORCHECK PTHREAD_MUTEX_ERRORCHECK_NP

void Mutex::create_lock()
{
   int ret = 0;

   pthread_mutexattr_t attr;
   pthread_mutexattr_init( &attr );
   if ( mRecursive )
      ret = pthread_mutexattr_settype( &attr, GH_PTHREAD_MUTEX_RECURSIVE );
   else
      ret = pthread_mutexattr_settype( &attr, GH_PTHREAD_MUTEX_ERRORCHECK );

   ret = pthread_mutex_init( &mMutex, &attr );
   if ( ret )
   {
      if ( ret == EAGAIN )
         printf("pthread_mutex_init() failed with EAGAIN\n");
      else if ( ret == EBUSY )
         printf("pthread_mutex_init() failed with EBUSY\n");
      else if ( ret == EINVAL )
         printf("pthread_mutex_init() failed with EINVAL\n");
      else
         printf("pthread_mutex_init() failed with %d\n", ret);
   }

   ret = pthread_mutexattr_destroy( &attr );
   if ( ret )
   {
      if ( ret == EINVAL )
         printf("pthread_mutexattr_destroy() failed with EINVAL\n");
      else
         printf("pthread_mutexattr_destroy() failed with %d\n", ret);
   }
}
