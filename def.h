// Eugene Sokolov
// Compilers ECE466
// def.h

#ifndef _DEF_H
#define _DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define HASH_PRIME 101

#define MAX_STRING_LENGTH 4096 

#define FILE_SCOPE 0
#define FUNCTION_SCOPE 1
#define BLOCK_SCOPE 2
#define PROTOTYPE_SCOPE 3

#define NAMESPACE_LABELS 0
#define NAMESPACE_TAGS 1
#define NAMESPACE_STRUCT_DEF 2
#define NAMESPACE_OTHER 3

#define LEFT 1
#define NEXT 2
#define RIGHT 3

enum number_type{
        TYPE_INT,
        TYPE_LONG,
        TYPE_LONGLONG,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_LONGDOUBLE,
};

enum sign_type{
	TYPE_UNSIGNED,
        TYPE_SIGNED
};

enum storage_class {
        STORE_AUTO,
        STORE_EXTERN,
        STORE_REGISTER,
        STORE_STATIC,
	STORE_TYPEDEF
};

enum scalar_type{
        SCALAR_INT,
        SCALAR_CHAR,
        SCALAR_DOUBLE
};

#endif
