/*==============================================================================
  * JetHead Proprietary
  * Copyright 2006 JetHead Development, Inc.
  * UNPUBLISHED WORK
  * ALL RIGHTS RESERVED
  *
  * This software is the confidential and proprietary information of
  * JetHead Development, Inc. ("Proprietary Information").  Any use,
  * reproduction, distribution or disclosure of the software or Proprietary
  * Information, in whole or in part, must comply with the terms of the license
  * agreement, nondisclosure agreement or contract entered into with
  * JetHead providing access to this software.
  *============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "gh_types.h"
#include "gh_memory.h"
#include "List++.h"
#include "Mutex.h"

#define PTR_SIZE (sizeof(void*))
#define ALIGN_SIZE( size ) ( ( (size) + PTR_SIZE - 1 ) / PTR_SIZE * PTR_SIZE )
#define NODE_SIZE (ALIGN_SIZE( sizeof( ObjInfo ) ))
#define MAGIC_ALLOCED 0xfeedbeef
#define MAGIC_FREED 0xdeadbeef

#define PTR_SIZE (sizeof(void*))
#define ALIGN_SIZE( size ) ( ( (size) + PTR_SIZE - 1 ) / PTR_SIZE * PTR_SIZE )
#define NODE_SIZE (ALIGN_SIZE( sizeof( ObjInfo ) ))
#define MAGIC_ALLOCED 0xfeedbeef
#define MAGIC_FREED 0xdeadbeef

GCHeap *GCHeap::defaultHeap = NULL;

GCHeap::GCHeap() 
	: mCurrentSize(0),
	  mMaxSize(0),
	  mNumTotalAllocations(0),
	  mNumCurrentAllocations(0)
	  
{
}

GCHeap::~GCHeap()
{
	printf( "waiting for others to complete\n" );
	
	printf( "Total number of allocations: %d\n", mNumTotalAllocations );
	printf( "Max size of heap: %d\n", mMaxSize );
	
	if ( !mObjects.empty() )
	{
		printf( "LEAKED, %d objects, totaling %d bytes\n", mNumCurrentAllocations, mCurrentSize );
		printf( "The following objects have been leaked\n" );
		dumpList();
	}
}
	
GCHeap::ObjInfo *GCHeap::alloc( size_t size, const char *file, int line )
{
	void *ptr = ::malloc( size + NODE_SIZE );
	ObjInfo *obj = new( ptr ) ObjInfo;
	obj->magic = MAGIC_ALLOCED;
	obj->ptr = (void*)((uint8_t*)ptr + NODE_SIZE);
	obj->size = size;
	obj->refCnt = 0;
	obj->heap = this;
	obj->file = file;
	obj->line = line;
	//strncpy( obj->thread_name, Thread::GetCurrent()->GetName(), Thread::kThreadNameLen );
	//obj->thread_name[ Thread::kThreadNameLen - 1 ] = '\0';
	Mutex::EnterCriticalSection();
	mObjects.push_front( obj );
		
	mCurrentSize += size;
	if ( mCurrentSize > mMaxSize )
		mMaxSize = mCurrentSize;
	
	mNumTotalAllocations++;
	mNumCurrentAllocations++;
	Mutex::ExitCriticalSection();
	
	return obj;
}

void GCHeap::free( ObjInfo *info )
{
	if ( info->magic != MAGIC_ALLOCED )
	{
		if ( info->magic == MAGIC_FREED )
			printf( "Looks like a double freeing of memory. [alloc@%s:%d]\n", info->file, info->line );
		else
			printf( "Memory corruption detected or deleting an object with"
			      " a non-virtual destructor. [alloc@%s:%d]\n", info->file, info->line );
	}

	if ( info->refCnt != 0 )
	{
		printf( "Ref Count not 0, probably deleting an object that is ref counted."
		      " [alloc@%s:%d]\n", info->file, info->line );
	}
	
	Mutex::EnterCriticalSection();
	mCurrentSize -= info->size;	
	mNumCurrentAllocations--;
	
	info->remove();
	Mutex::ExitCriticalSection();
	info->magic = MAGIC_FREED;
	::free( info );
}

GCHeap::ObjInfo *GCHeap::find( void *ptr )
{
	Mutex::EnterCriticalSection();
	ObjInfo *obj = mObjects.getHead();
	while ( obj != NULL )
	{
		if ( ptr >= obj->ptr && (uint8_t*)ptr < (uint8_t*)obj->ptr + obj->size )
		{
			Mutex::ExitCriticalSection();
			return obj;
		}
		
		obj = mObjects.next( obj );
	}

	Mutex::ExitCriticalSection();
	
	return NULL;
}

GCHeap::ObjInfo *GCHeap::quick_find( void *ptr )
{
	ObjInfo *obj = (ObjInfo*)((uint8_t*)ptr - NODE_SIZE);
	return obj;
}

void GCHeap::dumpList()
{
	Mutex::EnterCriticalSection();
	ObjInfo *obj = mObjects.getHead();

	while ( obj != NULL )
	{
		if ( obj->magic == MAGIC_ALLOCED )
			printf( "  [alloc@%s:%d, size %d]\n", obj->file, obj->line, obj->size );
		else
			printf( "  corrupted!!! [alloc@%s:%d]\n", obj->file, obj->line );
	
		obj = mObjects.next( obj );
	}
	printf("Items allocated  = %d\n", mNumCurrentAllocations);
	Mutex::ExitCriticalSection();
}

#ifdef GCHEAP_ENABLED

void *operator new( size_t size ) throw (std::bad_alloc)
{
	GCHeap::InitCheck();
	GCHeap::ObjInfo *info = GCHeap::defaultHeap->alloc( size, "non-gh_new", 0 );
	return info->ptr;
}

void *operator new[]( size_t size ) throw (std::bad_alloc)
{
	GCHeap::InitCheck();
	GCHeap::ObjInfo *info = GCHeap::defaultHeap->alloc( size, "non-gh_new[]", 0 );
	return info->ptr;
}

void *operator new( size_t size, const char *file, int line )
{
	GCHeap::InitCheck();
	GCHeap::ObjInfo *info = GCHeap::defaultHeap->alloc( size, file, line );
	return info->ptr;
}

void *operator new[]( size_t size, const char *file, int line )
{
	GCHeap::InitCheck();
	GCHeap::ObjInfo *info = GCHeap::defaultHeap->alloc( size, file, line );
	return info->ptr;
}

void operator delete( void *p ) throw ()
{
	if ( p == NULL )
		return;
	
	GCHeap::ObjInfo *info = GCHeap::quick_find( p );
	info->heap->free( info );
}

void operator delete[]( void *p ) throw ()
{
	if ( p == NULL )
		return;
	
	GCHeap::ObjInfo *info = GCHeap::quick_find( p );
	info->heap->free( info );
}

// These two delete operator are specifically for the case of a constructor
//  that throws and exception.  In this case we need a delete operator
//  that matched the prototype of the "placement" new.
//
//  See: http://www.parashift.com/c++-faq-lite/dtors.html#faq-11.14

void operator delete( void *p, const char *file, int line )
{
	if ( p == NULL )
		return;

	GCHeap::ObjInfo *info = GCHeap::quick_find( p );
	info->heap->free( info );
}

void operator delete[]( void *p, const char *file, int line )
{
	if ( p == NULL )
		return;

	GCHeap::ObjInfo *info = GCHeap::quick_find( p );
	info->heap->free( info );
}

#else

void *operator new( size_t size ) throw (std::bad_alloc)
{
	return ::malloc(size);
}

void *operator new[]( size_t size ) throw (std::bad_alloc)
{
	return ::malloc(size);
}

void *operator new( size_t size, const char *file, int line )
{
	return ::malloc(size);
}

void *operator new[]( size_t size, const char *file, int line )
{
	return ::malloc(size);
}

void operator delete( void *p ) throw ()
{
	if ( p == NULL )
		return;
	
	free(p);
}

void operator delete[]( void *p ) throw ()
{
	if ( p == NULL )
		return;

	free(p);
}

// These two delete operator are specifically for the case of a constructor
//  that throws and exception.  In this case we need a delete operator
//  that matched the prototype of the "placement" new.
//
//  See: http://www.parashift.com/c++-faq-lite/dtors.html#faq-11.14

void operator delete( void *p, const char *file, int line )
{
	if ( p == NULL )
		return;

	free(p);
}

void operator delete[]( void *p, const char *file, int line )
{
	if ( p == NULL )
		return;

	free(p);
}

#endif
