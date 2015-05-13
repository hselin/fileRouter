#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

#endif


#if 0
// Copyright (c) 1993-2006 David R. Cheriton, all rights reserved.

#ifndef TAC_TYPES_H
#define TAC_TYPES_H
/*
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long U32;
typedef unsigned long long U64;
typedef long S32;
*/

#include <typeinfo>

#ifdef _MSC_VER
  #include "vs_stdint.h"
#else
  #include <stdint.h>
#endif

typedef uint8_t U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t S8;
typedef int16_t S16;
typedef int32_t S32;
typedef int64_t S64;

#include <math.h>
//#define endOfTime INFINITY
//#define beginningOfTime -INFINITY

#ifdef _MSC_VER // math.h does not define INFINITY in Visual Studio
  #define INFINITY HUGE_VAL
#endif

#include <iostream>
#include <sstream>
#include <string>

#include <assert.h>

#define unlikely( cond ) __builtin_expect((cond),0)
#define likely( cond ) __builtin_expect((cond),1)
// Hints for the branch predictor -- cond is a conditional expression
#define hidden__ __attribute__ ((visibility ("hidden")))
// Tag a declaration so that it gets the 'hidden' ELF tag -- not
// exported outside the current .so
#define thread_local __thread

namespace Fwk {

typedef double Seconds;
typedef double UnixTime;

const Seconds beginningOfTime = -INFINITY;
const Seconds endOfTime = INFINITY;

typedef std::istream Istream;
typedef std::ostream Ostream;
typedef std::istringstream IstringStream;
typedef std::ostringstream OstringStream;
typedef std::string String;

typedef U32 Bytes;

class Attribute;
class Dir;
class TeeStream;

class Activity;
extern Activity * CurrentActivity_;
// Managed by activityManager
// this should be replaced with a per-thread variable.
class RootNotifiee;
class LogMsg;

template< class T > U32
hash( T const & t ) {
   return t.hash();
}

// You should probably not use this unless you have a really good
// reason because doubles do not make good collection keys.
inline U32 hash( double d ) {
   return *(U32*)(&d);
}

inline U32
hash( U32 t ) {
   return t;
}
inline U32
hash( U8 t ) {
   return t;
}
inline U32
hash( U16 t ) {
   return t;
}

inline U32
hash( int t ) {
   return t;
}

static inline double epsilon() { return 0.000001; }

String demangle( std::type_info const & );

template< typename T >
String typeName() {
   return demangle( typeid(T) );
}

template< typename T >
String typeName( T const & t ) {
   return demangle( typeid(t) );
}

}

#endif
#endif