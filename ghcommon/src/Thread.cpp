/*
 * Thread.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: lia1hc
 */
#include <string.h>
#include <pthread.h>

#include "Thread.h"
#include "gh_memory.h"
#include "GlobalConstructor.h"
#include "Mutex.h"

pthread_key_t Thread::mThreadKey;
bool Thread::mInited = false;

pthread_mutex_t Mutex::mCriticalSection;

GLOBAL_CONSTRUCT( &Thread::Init );

void *Thread::start_thread( void* arg )
{
   Thread *thread = (Thread*)arg;

   pthread_setspecific( mThreadKey, thread );

   // TODO
   printf( "started pid %d tid %d\n", getpid(), (uint32_t)pthread_self() );
   thread->OnStart();

   return NULL;
}

Thread::Thread( const char *name, int priority ) : mJoined( false ),
mSystemThread( true )
{
   strncpy(mName, name, kThreadNameLen);
   mName[ kThreadNameLen - 1 ] = '\0';
   mPrio = priority;
}

Thread::Thread( pthread_t thread, const char *name ) : mJoined( false),
      mSystemThread( true )
{
   if ( name == NULL )
   {
      snprintf( mName, kThreadNameLen, "t0x%lx", thread );
   }
   else
   {
      strncpy(mName, name, kThreadNameLen);
      mName[ kThreadNameLen - 1 ] = '\0';
   }

   pthread_setspecific( mThreadKey, this );
}

/**
 * Only join if this is a user thread
 */
Thread::~Thread()
{
   if ( not mSystemThread )
   {
      Join();
   }
}

void Thread::Init()
{
   if ( !mInited )
   {
      if ( pthread_key_create(&mThreadKey, &thread_key_destructor) != 0 )
      {
         printf( "Failed to create pthread key\n");
      }

      mInited = true;

      new Thread( pthread_self(), "main" );
      Mutex::Init();
   }
}

void Thread::Destroy()
{
   mInited = false;

   Mutex::Destroy();
   //TOTO
   //TimerManager::destroyManager();
}

void Thread::thread_key_destructor( void *arg )
{
   Thread *t = reinterpret_cast<Thread*>( arg );
   if ( t->mSystemThread )
   {
      delete t;
   }
}

Thread *Thread::GetCurrent()
{
   Thread *t = reinterpret_cast<Thread*>( pthread_getspecific( mThreadKey ) );
   if ( t == NULL )
   {
      t = gh_new Thread( pthread_self(), NULL );
   }

   return t;
}

bool Thread::operator==( const Thread &t )
{
   return mThread == t.mThread;
}

int Thread::Join()
{
   int ret = 0;

   if ( !mJoined )
   {
      if ( *this == *GetCurrent() )
      {
         printf("Thread %s attempting to join self: THIS WOULD DEADLOCK\n", GetName());
         return -1;
      }

      ret = pthread_join( mThread, NULL );
      if ( ret == 0 )
         mJoined = true;
      else
         printf("pthread_join(%s) FAILED with error %d\n", GetName(), ret);
   }

   return ret;
}

void Thread::Exit()
{
   pthread_exit( NULL );
}

int32_t Thread::Start()
{
   int32_t rc = 0;
   pthread_attr_t attrs;
   struct sched_param prio;

   prio.sched_priority = sched_get_priority_max( SCHED_RR );

   //TODO
   printf("Creating Thread %s\n", GetName());

   pthread_attr_init( &attrs );

   if ( mPrio > 0 && geteuid() == 0 )
   {
      pthread_attr_setschedpolicy( &attrs, SCHED_RR );
      pthread_attr_setschedparam( &attrs, &prio );
   }

   rc = pthread_create( &mThread, &attrs, start_thread, (void *)this );
   if ( rc != 0 )
   {
      printf("Error from pthread_create() is [%d]\n", rc);
   }
   printf("Thread create %d\n", rc);

   /*
    * Destroying the attributes previously allocated by pthread_attr_init;
    * if not destroyed may result in a memory leak
    */
   pthread_attr_destroy( &attrs );

   return rc;
}

void Thread::Stop()
{
   OnStop();
}

static const char gUnknownThread[] = "Unknown";

const char *GetThreadName()
{
   Thread *t = Thread::GetCurrent();

   if ( t == NULL )
   {
      return gUnknownThread;
   }
   return t->GetName();
}

void Thread::OnStop()
{
   pthread_cancel( mThread );
}

