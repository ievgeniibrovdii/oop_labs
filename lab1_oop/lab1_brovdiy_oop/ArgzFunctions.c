#include "ArgzFunctions.h"

/*
The argz_create_sep function converts the null-terminated string string into an
argz vector (returned in argz and argz len) by splitting it into elements at every
occurrence of the character sep.
*/
error_t argz_create_sep(const char *string, int sep, char **argz, size_t *argz_len) {
	int i = 0;
	*argz_len = strlen(string) + 1;
	*argz = malloc(*argz_len * sizeof(char));
	
	if (strlen(string) == NULL) { return ERROR; }
	if (sep > 255 || sep < 0) { return ERROR; }
	
	for (i = 0; i < *argz_len; i++) {
			if (string[i] == sep) { *(*argz + i) = '\0'; }
			else { (*argz)[i] = string[i]; }
	}

	return OK;
}

//Function returns the number of elements in the argz vector.
size_t argz_count(const char *argz, size_t arg_len) {
	size_t i = 0;
	size_t count = 0;
	for (i = 0; i < arg_len; i++) {
		if (*(argz + i) == '\0') {
			count++;
		}
	}
	return count;
}

//The argz_add function adds the string str to the end of the argz vector 
error_t argz_add(char **argz, size_t *argz_len, const char *str) {
	int i = 0;
	char *ptr = NULL;
	char *tmp = *argz;
	int lenstr = strlen(str);
	char *vec = (char*)malloc((*argz_len + lenstr + 1) * sizeof(char));
	
	if (str == NULL) { return ERROR; }
	
	while (ptr = argz_next(*argz, *argz_len, ptr)) {
		strcpy(vec + i, ptr);
		i += strlen(ptr) + 1;
	}
	strcpy(vec + *argz_len, str);
	
	*argz = vec;
	*argz_len = *argz_len + lenstr + 1;
	free(tmp);
	return OK;
}

/*If entry points to the beginning of one of the elements in the argz vector *argz,
the argz_delete function will remove this entry and reallocate *argz, modifying *argz and *argz_len accordingly.
Note that as destructive argz functions usually reallocate their argz argument,
pointers into argz vectors such as entry will then become invalid.
*/
void argz_delete(char **argz, size_t *argz_len, char *entry) {
	int i = 0;
	char *ptr = NULL;
	char *tmp;
	const int len_entry = strlen(entry);
	char *vec = (char*)malloc((*argz_len - len_entry) * sizeof(char));
	
	if (entry == NULL) { return; }
	
	while (ptr = argz_next(*argz, *argz_len, ptr)) {
		if (strcmp(ptr, entry) != 0) {
			strcpy(vec + i, ptr);
			i += strlen(ptr) + 1;
		}
	}
	tmp = *argz;
	*argz = vec;
	*argz_len = *argz_len - len_entry - 1;
	free(tmp);
}

/*
The argz_insert function inserts the string entry into the argz vector *argz at a point just before the existing
element pointed to by before, reallocating *argz and updating *argz and *argz_len. If before is 0, entry is added
to the end instead (as if by argz_add). Since the first element is in fact the same as *argz, passing in *argz as
the value of before will result in entry being inserted at the beginning.
*/
error_t argz_insert(char **argz, size_t *argz_len, char *before, const char *entry) {
	int len_entry = strlen(entry);
	char *vec = (char*)malloc((*argz_len + len_entry + 1) * sizeof(char));
	char * ptr = NULL;
	int i = 0;
	char *tmp;
	if (before == NULL) { return ERROR; }
	if (entry == NULL) { return ERROR; }
	if (*argz == NULL) { return ERROR; }
	
	while (ptr = argz_next(*argz, *argz_len, ptr)) {
		if (strcmp(ptr, before) != 0) {
			strcpy(vec + i, ptr);
			i += strlen(ptr) + 1;
		}
		else {
			strcpy(vec + i, entry);
			i += strlen(ptr) + 2;
			strcpy(vec + i, ptr);
			i += strlen(ptr) + 1;
		}
	}

	tmp = *argz;
	*argz = vec;
	*argz_len = *argz_len + len_entry + 1;
	free(tmp);
	return OK;
}

/*
The argz_next function provides a convenient way of iterating over the elements in the argz vector argz.
It returns a pointer to the next element in argz after the element entry, or 0 if there are no elements following entry.
If entry is 0, the first element of argz is returned.
*/
char * argz_next(char *argz, size_t argz_len, const char *entry) {
	char *p;
	if (entry == NULL)
		return argz;
	for (p = entry; p <= argz + argz_len; p++)
	{
		if (p == argz + argz_len - 1)
			return NULL;
		else
			if (*p == '\0')
				return p + 1;
	}
	return NULL;
}

/*
Replace the string str in argz with string with, reallocating argz as
necessary.
*/
error_t argz_replace(char **argz, size_t *argz_len, const char *str, const char *with) {
	int i = 0;
	char *tmp;
	int len_str = strlen(str);
	int len_with = strlen(with);
	char *hp = *argz, *Pstr = NULL, *ptr = NULL;
	char *vec = (char*)malloc((*argz_len - len_str + len_with) * sizeof(char));
	
	if ((str == NULL) || (with == NULL)) { return ERROR; }
	if (*argz == NULL) { return ERROR; }
	
	while (hp < *argz + *argz_len)
	{
		Pstr = strstr(hp, str);

		if (Pstr == NULL)
		{
			hp += strlen(hp) + 1;
			continue;
		}
		else break;
	}
	if (Pstr == NULL) { return ERROR; }

	
	
	while (ptr = argz_next(*argz, *argz_len, ptr)) {
		if (strcmp(ptr, str) != 0) {
			strcpy(vec + i, ptr);
			i += strlen(ptr) + 1;
		}
		else {
			strcpy(vec + i, with);
			i += len_with + 1;
			strcpy(vec + i, ptr);
		}
	}
	tmp = *argz;
	*argz = vec;
	
		*argz_len = *argz_len - len_str + len_with;
	
	free(tmp);
	return OK;
}

/*prints argz vector */
void argz_print(const char *argz, size_t argz_len) {
	int i = 0;
	if (argz == NULL) { return; }
	for ( i = 0; i < argz_len; ++i)
	{
		if (argz[i] == '\0')
			printf("\\0\n");
		else
			printf("%c", argz[i]);
	}
	printf("\n\n ");
}
