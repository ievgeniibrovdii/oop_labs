#pragma once
#pragma warning (disable:4047)
#pragma warning (disable:4101)
#pragma warning (disable:4024)
#pragma warning (disable:4244)
#pragma warning (disable:4090)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <conio.h>
#include <string.h>
#include <fcntl.h>

typedef struct {
	int id;//унікальний ідентифікатор
	char manufacturer[127];// виготовлювач
	char model[127];// найменування моделі
	int year;	 // рік виготовлення
	float price;// ціна
	int x_size;// горизонтальний розмір області сканування
	int y_size;// вертикальний розмір області сканування
} SCAN_INFO;

typedef struct {
	int rec_nmb;//number of records
	SCAN_INFO *recs;//records 
}RECORD_SET;


int create_db(const char* csv, const char *db);
int make_index(const char *db, const char *field_name);
RECORD_SET * get_recs_by_index(const char *dba, char *indx_field);
void reindex(const char *db);
void del_scanner(const char *db, int id);
void add_scanner(const char *db, const char* scanner_str);
void print_db(const char *db);
RECORD_SET* select(const char *db, const char *field, const char *value);
void print_rec_set(RECORD_SET *rs);


int cmp_manufacturer(const void *val1, const void *val2);
int cmp_model(const void *val1, const void *val2);
int cmp_year(const void *val1, const void *val2);
int cmp_price(const void *val1, const void *val2);
int cmp_x_size(const void *val1, const void *val2);
int cmp_y_size(const void *val1, const void *val2);

int cmp_int(int a, int b);
int cmp_float(float a, float b);

char* concat(char *s1, char *s2);