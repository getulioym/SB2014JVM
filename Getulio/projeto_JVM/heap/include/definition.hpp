#ifndef DEFINITION
#define DEFINITION

#include <stdio.h>
#include <stdint.h>


#define TYPE_BYTE	'B'
#define TYPE_CHAR	'C'
#define TYPE_SHORT	'S'
#define TYPE_INT	'I'
#define TYPE_LONG	'J'
#define TYPE_FLOAT	'F'
#define TYPE_DOUBLE	'D'
#define TYPE_BOOL	'Z'
#define TYPE_CLASS	'L'
#define TYPE_ARRAY	'['

#define ACC_PUBLIC		0x0001
#define ACC_PRIVATE		0x0002
#define ACC_PROTECTED	0x0004
#define ACC_STATIC		0x0008
#define ACC_FINAL		0x0010
#define ACC_SUPER		0x0020
#define ACC_BRIDGE		0x0040
#define ACC_VORATILE	0x0040
#define ACC_VARARGS		0x0080
#define ACC_NATIVE		0x0100
#define ACC_INTERFACE	0x0200
#define ACC_ABSTRACT	0x0400
#define ACC_STRICT		0x0800
#define ACC_SYNTHETIC	0x1000
#define ACC_ENUM		0x4000

typedef uint8_t		u1;
typedef uint16_t	u2;
typedef uint32_t	u4;


#endif
