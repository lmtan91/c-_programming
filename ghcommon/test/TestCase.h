/*
 * TestCase.h
 *
 *  Created on: Aug 11, 2017
 *      Author: lia1hc
 */

#ifndef TEST_TESTCASE_H_
#define TEST_TESTCASE_H_

#include <string>
#include <stdarg.h>
#include "Thread.h"

class TestCase
{
public:
   TestCase( const char *thread_name ) : mThread( thread_name, this, &TestCase::Run )
   {
   }

   virtual ~TestCase() {}

   bool Start()
   {
      if ( mTestName == "" )
      {
         printf( "Bad Test Case, please call SetTestName in TestCase's constructor\n");
         return false;
      }

      printf( "Running test %s:", mTestName.c_str() );
      fflush( stdout );

      mThread.Start();
      mThread.Join();

      if ( not mTestComplete )
      {
         printf( " FAILED\nBad Test Case, must call TestPassed or TestFailed before returning\n" );
         return false;
      }

      return mTestPassed;
   }

   const char *GetTestName()
   {
      return mTestName.c_str();
   }

protected:
   void SetTestName( const char *name )
   {
      mTestName = name;
   }

   void TestPassed()
   {
      printf( " PASSED\n" );
      mTestComplete = true;
      mTestPassed = true;
   }

   void TestFailed( const char *fmt, ... )
   {
      va_list params;

      va_start( params, fmt );

      printf( " FAILED\n" );
      vprintf( fmt, params );
      printf("\n");
      mTestComplete = true;
      mTestPassed = false;
      Thread::Exit();
   }

   virtual void Run() = 0;
private:
   bool                    mTestComplete;
   bool                    mTestPassed;
   std::string             mTestName;
   Runnable<TestCase>      mThread;
};

#endif /* TEST_TESTCASE_H_ */
