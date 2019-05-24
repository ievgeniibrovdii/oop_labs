#include "ArgzFunctions.h"

int main()
{
	char *argz;
	size_t argz_len;
	char *entry;
	if (argz_create_sep("Programming;is;the;way;to", ';', &argz, &argz_len) == OK)
	{
		printf(" argz_create_sep('Programming;is;the;way;to', ';', &argz, &argz_len):\n\n");

		argz_print(argz, argz_len);

		printf("argz_count(argz, argz_len): %d\n\n", argz_count(argz, argz_len));

		printf("argz_add (&argz, &argz_len, 'success'):\n\n");
		argz_add(&argz, &argz_len, "success");

		argz_print(argz, argz_len);
		printf("argz_len = %d\n\n", argz_len);

		printf("argz_delete (&argz, &argz_len, 'the'):\n\n");
		argz_delete(&argz, &argz_len, "the");

		argz_print(argz, argz_len);
		printf("argz_len = %d\n\n", argz_len);


		printf("argz_insert(&argz, &argz_len, argz + 15, 'good'):\n\n");
		argz_insert(&argz, &argz_len, argz + 15, "good");

		argz_print(argz, argz_len);
		printf("argz_len = %d\n\n", argz_len);

		printf("argz_next: \n\n");
		for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))
			printf("%s\n", entry);
		printf("\n");

		printf("argz_replace(&argz, &argz_len, 'good', 'classical'):\n\n");
		argz_replace(&argz, &argz_len, "good", "classical");

		argz_print(argz, argz_len);
		printf("argz_len = %d\n\n", argz_len);
		
	}
	else {
		exit(1);
	}
	_getch();
	return 0;
}