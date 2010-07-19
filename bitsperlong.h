#if !defined HAVE_BITSPERLONG_H__
#define      HAVE_BITSPERLONG_H__

//#include "bits/bitsperlong.h"  // this file

#if !defined BITS_PER_LONG  // could be defined using -DBITS_PER_LONG=value
#include <climits>

#if  ( 4294967295UL==ULONG_MAX )  // long is 32bit
#  define  BITS_PER_LONG  32
#  define  LOG2_BITS_PER_LONG  5
#else
#  if  ( 18446744073709551615UL==ULONG_MAX )  // long is 64 bit
#    define  BITS_PER_LONG  64
#    define  LOG2_BITS_PER_LONG  6
#  else
#    define  BITS_PER_LONG  128  // ... assume long is 128 bit
#    define  LOG2_BITS_PER_LONG  7
#    error 'several functions are not implemented for 128bit long'
// contact me and I might fix it
#  endif //   ( 18446744073709551615UL==ULONG_MAX )
#endif //   ( 4294967295UL==ULONG_MAX )

#endif //  !defined BITS_PER_LONG

#define  BYTES_PER_LONG  (BITS_PER_LONG/8)

#if !defined BITS_PER_LONG_LONG  // could be defined using -DBITS_PER_LONG_LONG=value

#define  BITS_PER_LONG_LONG  64  // default (if ULONG_LONG_MAX is not defined)
#define  LOG2_BITS_PER_LONG_LONG  6

#endif //  !defined BITS_PER_LONG_LONG

#define  BYTES_PER_LONG_LONG  (BITS_PER_LONG_LONG/8)

#endif //  !defined HAVE_BITSPERLONG_H__
