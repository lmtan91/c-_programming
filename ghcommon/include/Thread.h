/*
 * Thread.h
 *
 *  Created on: Aug 7, 2017
 *      Author: lia1hc
 */

#ifndef _GH_THREAD_H_
#define _GH_THREAD_H_

#include <stdlib.h>


class Thread
{
public:

   /**
    * Create a thread
    * @param name       thread name
    * @param priority   priority of thread
    */
   Thread( const char *name, int priority = 0 );

   /**
    * Destroy a thread. This cannot be called from thread itself
    */
   virtual ~Thread();

   /**
    * Start a thread
    */
   int32_t Start();

   /**
    * This will inform thread to stop.  If your class doesn't override OnStop
    * this will cause the thread to exit immidatly by calling pthread_cancel.
    */
   void Stop();

   /**
    * Get a thread name
    */
   const char *GetName() { return mName; }

   /**
    * Block the calling thread until this thread exits.
    * Unless the underlying join fails, in which case, it returns the
    * error code immediately, and proceeds, without waiting for the
    * thread to join.
    */
   int Join();

   bool operator==( const Thread &t );

   static void Exit();

   /**
    *
    */
   static void Destroy();

   static Thread *GetCurrent();

   /**
    * Init the thread system. Called once at startup before any threads are
    * created.
    */
   static void Init();

   static const int kThreadNameLen = 32;

protected:
   /**
    * Called from the context if the thread after it has been started. When
    * this function exits the thread will stop and Join will return.
    */
   virtual void OnStart() {}

   /**
    * Called by Stop so that the thread can be informed to exit. This differs
    * based on what the thread is doing
    */
   virtual void OnStop();
private:
   Thread( pthread_t thread, const char *name );

   char                 mName[kThreadNameLen];
   bool                 mJoined;
   bool                 mSystemThread;
   int                  mPrio;
   pthread_t            mThread;

   static pthread_key_t mThreadKey;
   static bool          mInited;

   static void *start_thread( void* arg );
   static void thread_key_destructor( void* arg );
};

template<class T>
class Runnable : public Thread
{
public:
   typedef void (T::*thread_main_type)();

   Runnable( const char *name, T *object, thread_main_type thread_main, bool hard_stop = false, int priority = 0 )
   : Thread( name, priority ), mObject( object ), mFunc( thread_main ), mStop( false ), mHardStop( hard_stop )
   {
      if ( hard_stop == true )
      {
         abort();
      }
   }

   bool CheckStop() { return mStop; }
private:

   void OnStart() { (mObject->*mFunc)(); }
   void OnStop() { if ( mHardStop ) Thread::OnStop(); else mStop = true; }

   T*                mObject;
   thread_main_type  mFunc;
   bool              mStop;
   bool              mHardStop;
};

__BEGIN_DECLS

const char *GetThreadName();

__END_DECLS

#endif /* _GH_THREAD_H_ */
