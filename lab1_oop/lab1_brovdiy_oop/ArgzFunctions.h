/************************************************************************
*file: ArgzFunctions.h
*purpose: declarations for argz functions, types, constants
*author: Brovdiy Ievgeniy
*written: 25/09/2017
*last modified: 10/10/2017
*************************************************************************/

#pragma once
#pragma warning (disable:4047)
#pragma warning (disable:4018)
#pragma warning (disable:4019)
#pragma warning (disable:4090)
#include <stddef.h> // for  size_t
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
typedef enum { OK, ERROR } error_t;

/* function prototypes */

error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len);
size_t argz_count(const char *argz, size_t arg_len);
error_t argz_add(char **argz, size_t *argz_len, const char *str);
void argz_delete(char **argz, size_t *argz_len, char *entry);
error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry);
char * argz_next(char *argz, size_t argz_len, const char *entry);
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with);
void argz_print(const char *argz, size_t argz_len);


