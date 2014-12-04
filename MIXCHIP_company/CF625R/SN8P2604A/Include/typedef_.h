#ifndef		_TYPEDEF_H_
#define 	_TYPEDEF_H_

typedef unsigned char u8;
typedef unsigned char const uc8;
typedef volatile unsigned char vu8;
typedef volatile unsigned char const vuc8;

typedef unsigned long u16;
typedef unsigned long const uc16;
typedef volatile unsigned long vu16;
typedef volatile unsigned long const vuc16;

typedef enum { FALSE = 0, TRUE = !FALSE} bool;
typedef enum { RESET = 0, SET = !RESET } FlagStatus;
typedef enum { DISABLE = 0, ENABLE = !DISABLE } FunctionalState;
typedef enum { ERROR = 0, SUCCESS = !ERROR } ErrorStatus;

#endif