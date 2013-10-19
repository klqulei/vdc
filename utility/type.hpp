#ifndef _V_TYPE_H_
#define _V_TYPE_H_

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <assert.h>
#include <stdarg.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <stdarg.h>
#include <time.h>

#ifndef  V_TYPE
#define V_TYPE
typedef  unsigned char u8;
typedef  char s8;
typedef  unsigned short u16;
typedef  short s16;
typedef  unsigned int  u32;
typedef  int s32;
typedef  long long s64;
typedef  unsigned long long u64;

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;

typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef int INT;
typedef double DATE;

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef signed long long    INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned long long  UINT64, *PUINT64;

#ifndef TRUE 
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#endif /* V_TYPE */



#endif /* _VDC_UTILITY_H_ */
