#ifndef __INTEGER_H__
#define __INTEGER_H__

typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

#if defined(__GNUC__)
typedef signed long long int s64;
typedef unsigned long long int u64;
#else //defined(__GNUC__)
typedef signed __int64 s64;
typedef unsigned __int64 u64;
#endif //defined(__GNUC__)

#endif //__INTEGER_H__
