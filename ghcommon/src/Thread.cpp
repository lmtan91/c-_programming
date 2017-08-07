/*
 * Thread.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: lia1hc
 */
#include <string.h>
#include <pthread.h>

#include "Thread.h"
#include "GlobalConstructor.h"

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

   }
}

int32_t Thread::Start()
{
   int32_t rc = 0;
   pthread_attr_t attrs;
   struct sched_param prio;

   prio.sched_priority = sched_get_priority_max( SCHED_RR );

   // TODO
   //printf("Creating Thread %s\n", GetName());

   pthread_attr_init( &attrs );

   if ( mPrio > 0 && geteuid() == 0 )
   {
      pthread_attr_setschedpolicy( &attrs, SCHED_RR );
      pthread_attr_setschedparam( &attrs, &prio );
   }

   rc = pthread_create( &mThread, &attrs, start_thread, (void *)this );
   if ( rc != 0 )
   {

   }
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

void Thread::OnStop()
{
   pthread_cancel( mThread );
}

