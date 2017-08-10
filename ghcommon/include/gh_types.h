
/**
 *	@file gh_types.h
 *	@brief Standard include for types
 *
 *	This file can be included to define ISO C99 integer types and
 *	ISO C boolean types in both user and kernel space code.
 */
#ifndef _JH_TYPES_H_
#define _JH_TYPES_H_

#define JH_ARRAY_SIZE( array ) (int)( sizeof( array ) / sizeof( array[ 0 ] ) )

#ifdef __KERNEL__
#error "This version of gh_types.h is meant for userspace builds only."
#endif


#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>

#ifdef PLATFORM_DARWIN
typedef off_t gh_off64_t;
#else
typedef __off64_t gh_off64_t;
#endif

#endif // _JH_TYPES_H_

