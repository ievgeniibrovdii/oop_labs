#include "Scanner.h"
/* Function writes data about scanners from file .csv to file .db .
First byte of file .db is numbers of scanners in this file
Every scanner in file .db has it's own id
Return 1 if all is ok, and 0 if error*/
int create_db(const char* csv, const char *db) {
	FILE *db_f, *csv_f;
	SCAN_INFO sc, tmp;
	int flds_nmb;
	int rec_nmb = 0;
	int repeat;
	int i = 0;

	if ((csv_f = fopen(csv, "r")) == NULL) {
		return 0;
	}
	if ((db_f = fopen(db, "wb+")) == NULL) {
		return 0;
	}
	while (!feof(csv_f)) {
		fscanf(csv_f, "%[A-z0-9];%[A-z0-9];%d;%f;%d;%d\n", &(sc.manufacturer), &(sc.model), &(sc.year), &(sc.price), &(sc.x_size), &(sc.y_size));
		rec_nmb++;
	}

	rewind(csv_f);
	fwrite(&rec_nmb, sizeof(int), 1, db_f);
	while (1) {
		
		flds_nmb = fscanf(csv_f, "%[A-z0-9];%[A-z0-9];%d;%f;%d;%d\n", &(sc.manufacturer), &(sc.model), &(sc.year), &(sc.price), &(sc.x_size), &(sc.y_size));
		if (flds_nmb == -1)
			break;
		rewind(db_f);
		repeat = 0;
		while (fread(&tmp, sizeof(SCAN_INFO), 1, db_f)) {
			if ((tmp.manufacturer == sc.manufacturer) && (tmp.model == sc.model) && (tmp.year == sc.year) && (tmp.price == sc.price) && (tmp.x_size == sc.x_size) && (tmp.y_size == sc.y_size)) {
				repeat = -1;
			}
		}
		if (repeat == 0) {
			sc.id = i;
			fwrite(&sc, sizeof(SCAN_INFO), 1, db_f);
		}
		i++;
	}

	fclose(db_f);
	fclose(csv_f);

	return 1;
}

/* Function creates index file to file db on current field_name.
All indexes in .idx file are attached to current scanner in db file.
Scanners are sorted by field_name. 
Function returns 0 if error and 1 if all is good*/
int make_index(const char *db, const char *field_name) {
	FILE *db_f, *idx;
	SCAN_INFO sc;
	SCAN_INFO* rs_sort;
	int i = 0, j = 0, rec_nmb = 0;
	char* idx_file;
	char ros[5] = ".idx\0";
	
	idx_file = concat(field_name, ros);

	if ((db_f = fopen(db, "rb")) == NULL) {
		return 0;
	}

	if ((idx = fopen(idx_file, "w")) == NULL) {
		fclose(db_f);
		return 0;
	}

	fread(&rec_nmb, sizeof(int), 1, db_f);
	rs_sort = (SCAN_INFO*)malloc(rec_nmb * sizeof(SCAN_INFO));
	for (i = 0; i < rec_nmb; i++) {
		fread(rs_sort+i, sizeof(SCAN_INFO), 1, db_f);
	}
	
	if (field_name == "manufacturer") { 
	qsort(rs_sort, rec_nmb, sizeof(SCAN_INFO), cmp_manufacturer); 
	for (i = 0; i < rec_nmb; i++)
	{
		fseek(db_f, sizeof(int), SEEK_SET);
		for (j = 0; j < rec_nmb; j++)
		{
			fread(&sc, sizeof(SCAN_INFO), 1, db_f);
			if ((rs_sort + i) != NULL && strcmp(sc.manufacturer, (rs_sort+i)->manufacturer) == 0 && strcmp(sc.model, (rs_sort+i)->model) == 0)
			{
				fprintf(idx, "%d ", j);
			}
		}
	}
}

	else if (field_name == "model") { 
	qsort(rs_sort, rec_nmb, sizeof(SCAN_INFO), cmp_model); 
	for (i = 0; i < rec_nmb; i++)
	{
		fseek(db_f, sizeof(int), SEEK_SET);
		for (j = 0; j < rec_nmb; j++)
		{
			fread(&sc, sizeof(SCAN_INFO), 1, db_f);
			if ((rs_sort+i) != NULL && strcmp(sc.model, (rs_sort+i)->model) == 0)
			{
				fprintf(idx, "%d ", j);
			}
		}
	}
	}
	else if (field_name =="year"){ 
	qsort(rs_sort, rec_nmb, sizeof(SCAN_INFO), cmp_year); 
	for (i = 0; i < rec_nmb; i++)
	{
		fseek(db_f, sizeof(int), SEEK_SET);
		for (j = 0; j < rec_nmb; j++)
		{
			fread(&sc, sizeof(SCAN_INFO), 1, db_f);
			if (cmp_int(sc.year, (rs_sort+i)->year) == 0 && strcmp(sc.model, (rs_sort+i)->model) == 0)
			{
				fprintf(idx, "%d ", j);
			}
		}
	}
	}
	else if (field_name == "price"){ 
	qsort(rs_sort, rec_nmb, sizeof(SCAN_INFO), cmp_price);
	for (i = 0; i < rec_nmb; i++)
	{
		fseek(db_f, sizeof(int), SEEK_SET);
		for (j = 0; j < rec_nmb; j++)
		{
			fread(&sc, sizeof(SCAN_INFO), 1, db_f);
			if (cmp_float(sc.price, (rs_sort+i)->price) == 0 && strcmp(sc.model, (rs_sort+i)->model) == 0)
			{
				fprintf(idx, "%d ", j);
			}
		}
	}
	}
	else if (field_name == "x_size"){
	qsort(rs_sort, rec_nmb, sizeof(SCAN_INFO), cmp_x_size);
	for (i = 0; i < rec_nmb; i++)
	{
		fseek(db_f, sizeof(int), SEEK_SET);
		for (j = 0; j < rec_nmb; j++)
		{
			fread(&sc, sizeof(SCAN_INFO), 1, db_f);
			if (cmp_int(sc.x_size, (rs_sort+i)->x_size) == 0 && strcmp(sc.model, (rs_sort+i)->model) == 0)
			{
				fprintf(idx, "%d ", j);
			}
		}
	}
	}
	else if (field_name == "y_size"){
	qsort(rs_sort, rec_nmb, sizeof(SCAN_INFO), cmp_y_size); 
	for (i = 0; i < rec_nmb; i++)
	{
		fseek(db_f, sizeof(int), SEEK_SET);
		for (j = 0; j < rec_nmb; j++)
		{
			fread(&sc, sizeof(SCAN_INFO), 1, db_f);
			if (cmp_int(sc.y_size, (rs_sort+i)->y_size) == 0 && strcmp(sc.model, (rs_sort+i)->model) == 0)
			{
				fprintf(idx, "%d ", j);
			}
		}
	}
	}
	
	free(rs_sort);
	fclose(idx);
	fclose(db_f);

	return 1;
}

int cmp_int(int a, int b) {
	return (a < b ? -1 : (a > b ? 1 : 0));
}
int cmp_float(float a, float b) {
	return (a < b ? -1 : (a > b ? 1 : 0));
}
char* concat(char *s1, char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1);
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

int cmp_manufacturer(const void *val1, const void *val2)
{
	return strcmp(((SCAN_INFO*)val1)->manufacturer, ((SCAN_INFO*)val2)->manufacturer) >= 0 && strcmp(((SCAN_INFO*)val1)->model, ((SCAN_INFO*)val2)->model) >= 0;
}
int cmp_model(const void *val1, const void *val2)
{
	return strcmp(((SCAN_INFO*)val1)->model, ((SCAN_INFO*)val2)->model);
}
int cmp_year(const void *val1, const void *val2)
{
	return ((SCAN_INFO*)val1)->year - ((SCAN_INFO*)val2)->year;
}
int cmp_price(const void *val1, const void *val2)
{
	return (int)(((SCAN_INFO*)val1)->price - ((SCAN_INFO*)val2)->price);
}
int cmp_x_size(const void *val1, const void *val2)
{
	return ((SCAN_INFO*)val1)->x_size - ((SCAN_INFO*)val2)->x_size;
}
int cmp_y_size(const void *val1, const void *val2)
{
	return ((SCAN_INFO*)val1)->y_size - ((SCAN_INFO*)val2)->y_size;
}

/*Function creates index file on all scanners by field_name*/
void reindex(const char *db) {
	make_index(db, "manufacturer");
	make_index(db, "model");
	make_index(db, "year");
	make_index(db, "price");
	make_index(db, "x_size");
	make_index(db, "y_size");
}

/*Function deletes current scanner in db file,
also function calls reindex()*/
void del_scanner(const char *db, int id) {
	FILE *db_f, *del;
	SCAN_INFO sc;
	int rec_nmb, i;
	int new_nmb = 0;
	int flds;
	if ((db_f = fopen(db, "rb+")) == NULL) {
		exit(1);
	}
	if ((del = fopen("del.db", "wb+")) == NULL) {
		fclose(db_f);
		exit(1);
	}
	fread(&rec_nmb, sizeof(int), 1, db_f);
	new_nmb = rec_nmb - 1;
	fwrite(&new_nmb, sizeof(int), 1, del);
	for (i = 0; i < rec_nmb; i++) {
		fread(&sc, sizeof(SCAN_INFO), 1, db_f);
		if (sc.id != id) {
			fwrite(&sc, sizeof(SCAN_INFO), 1, del);
		}
	}
	fclose(db_f);
	db_f = fopen(db, "wb");
	rewind(del);
	fread(&new_nmb, sizeof(int), 1, del);
	fwrite(&new_nmb, sizeof(int), 1, db_f);
	while (fread(&sc, sizeof(SCAN_INFO), 1, del)) {
		fwrite(&sc, sizeof(SCAN_INFO), 1, db_f);
	}
	fclose(db_f);
	fclose(del);
	reindex("Scanners.db");
}

/*Function adds current scanner in db file,
also function calls reindex()*/
void add_scanner(const char *db, const char* scanner_str) {
	FILE *db_f, *dop;
	int new_nmb, rec_nmb;
	SCAN_INFO sc;
	int i;
	int id = 0;
	if ((db_f = fopen(db, "ab+")) == NULL) {
		return;
	}
	if((dop = fopen("dop.db", "wb+"))==NULL){
		fclose(db_f);
		return;
	}
	fread(&rec_nmb, sizeof(int), 1, db_f);
	new_nmb = rec_nmb + 1;
		while(fread(&sc, sizeof(SCAN_INFO), 1, db_f))
		id = sc.id;
		id++;
		sc.id = id;
	sscanf(scanner_str,"%[A-z0-9];%[A-z0-9];%d;%f;%d;%d" , &(sc.manufacturer), &(sc.model), &(sc.year), &(sc.price), &(sc.x_size), &(sc.y_size));
	fwrite(&sc, sizeof(SCAN_INFO), 1, db_f);
	fclose(db_f);

	db_f = fopen(db, "rb");
	fread(&rec_nmb, sizeof(int), 1, db_f);
	fwrite(&new_nmb, sizeof(int), 1, dop);
	while(fread(&sc, sizeof(SCAN_INFO), 1, db_f))
		fwrite(&sc, sizeof(SCAN_INFO), 1, dop);
	fclose(db_f);

	db_f = fopen(db, "wb");
	rewind(dop);
	fread(&new_nmb, sizeof(int), 1, dop);
	fwrite(&new_nmb, sizeof(int), 1, db_f);
	while (fread(&sc, sizeof(SCAN_INFO), 1, dop)) {
		fwrite(&sc, sizeof(SCAN_INFO), 1, db_f);
	}
	fclose(dop);
	fclose(db_f);
	reindex("Scanners.db");
}

/*Function returns pointer to record set of scanners in db file which are attached 
to currents indexes in file .idx.
Returns NULL pointer if error */
RECORD_SET * get_recs_by_index(const char *dba, char *indx_field) {
	RECORD_SET *rset;
	FILE *db_f, *idx;
	int i = 0, j = 0, number = 0;
	char ros[5] = ".idx\0";
	char* idx_file = concat(indx_field, ros);
	if ((db_f = fopen(dba, "rb")) == NULL)
		return NULL;
	if ((idx = fopen(idx_file, "rb")) == NULL)
	{
		fclose(db_f);
		return NULL;
	}
	if ((rset = (RECORD_SET*)malloc(sizeof(int) + sizeof(SCAN_INFO*))) == NULL)
	{
		fclose(db_f);
		fclose(idx);
		return NULL;
	}

	fread(&(rset->rec_nmb), sizeof(int), 1, db_f);
	
	if (rset->rec_nmb > 0)
	{
		if ((rset->recs = (SCAN_INFO*)malloc(rset->rec_nmb * sizeof(SCAN_INFO))) == NULL)
		{
			free(rset);
			fclose(db_f);
			fclose(idx);
			return NULL;
		}
		for (i = 0; i < rset->rec_nmb; i++)
		{
			fscanf(idx, "%d ", &j);
			fseek(db_f, sizeof(int), SEEK_SET);
			fseek(db_f, j * sizeof(SCAN_INFO), SEEK_CUR);
			fread(rset->recs + i, sizeof(SCAN_INFO), 1, db_f);
		}
	}
	free(idx_file);
	fclose(db_f);
	fclose(idx);
	return rset;
}

/*Function returns pointer to record set in db file in which field_name is equal value.
Returns NULL pointer if error*/
RECORD_SET* select(const char *db, const char *field, const char *value) {
	FILE *db_f;
	RECORD_SET *rset;
	SCAN_INFO sc;
	SCAN_INFO *vec;
	int i;
	int rec_nmb;
	int value_int;
	float value_float;
	sc.id = -1;
	i = 0;
	value_int = atoi(value);
	value_float = atof(value);

	if ((db_f = fopen(db, "rb")) == NULL)
	{
		return NULL;
	}
	if ((rset = (RECORD_SET*)malloc(sizeof(int) + sizeof(SCAN_INFO*))) == NULL)
	{
		fclose(db_f);
		return NULL;
	}
	fread(&(rset->rec_nmb), sizeof(int), 1, db_f);
	if ((rset->recs = (SCAN_INFO*)malloc(rset->rec_nmb * sizeof(SCAN_INFO))) == NULL)
	{
		free(rset);
		fclose(db_f);
		return NULL;
	}
	vec = (SCAN_INFO*)malloc(rset->rec_nmb * sizeof(SCAN_INFO));

	if (rset->rec_nmb > 0)
	{
		if (field == "manufacturer") {
			for (i = 0; i < rset->rec_nmb; i++)
			{
				fread(&vec[i], sizeof(SCAN_INFO), 1, db_f);
				if (strcmp(value, vec[i].manufacturer) == 0) {
					rset->recs[i] = vec[i];
				}
				else {
					rset->recs[i].id = sc.id;
				}
				
			}
		}

		else if (field =="model") {
			for (i = 0; i < rset->rec_nmb; i++)
			{
				fread(&vec[i], sizeof(SCAN_INFO), 1, db_f);
				if (strcmp(value, vec[i].model) == 0) {
					rset->recs[i] = vec[i];
				}
				else {
					rset->recs[i].id = sc.id;
				}

			}
		}
		else if (field  =="year") {
			for (i = 0; i < rset->rec_nmb; i++)
			{
				fread(&vec[i], sizeof(SCAN_INFO), 1, db_f);
				if (cmp_int(value_int, vec[i].year)==0) {
					rset->recs[i] = vec[i];
				}
				else {
					rset->recs[i].id = sc.id;
				}
			}
		}

		else if (field == "price") {
			for (i = 0; i < rset->rec_nmb; i++)
			{
				fread(&vec[i], sizeof(SCAN_INFO), 1, db_f);
				if (cmp_float(value_float, vec[i].price) == 0) {
					rset->recs[i] = vec[i];
				}
				else {
					rset->recs[i].id = sc.id;
				}
			}
		}
		
		else if (field == "x_size") {
			for (i = 0; i < rset->rec_nmb; i++)
			{
				fread(&vec[i], sizeof(SCAN_INFO), 1, db_f);
				if (cmp_int(value_int, vec[i].x_size) == 0) {
					rset->recs[i] = vec[i];
				}
				else {
					rset->recs[i].id = sc.id;
				}
			}
		}

		else if (field == "y_size") {
			for (i = 0; i < rset->rec_nmb; i++)
			{
				fread(&vec[i], sizeof(SCAN_INFO), 1, db_f);
				if (cmp_int(value_int, vec[i].y_size) == 0) {
					rset->recs[i] = vec[i];
				}
				else {
					rset->recs[i].id = sc.id;
				}
			}
		}
	}

	fclose(db_f);
	return rset;
}

/*Function prints records which are attached to RECORD_SET* (prints pointer RECORD_SET) 
Return type is void */
void print_rec_set(RECORD_SET *rs) {
	int i;
	if (rs == NULL) return;
	else if (rs->rec_nmb > 0) {
		//printf("%d", rs->rec_nmb);
		for (i = 0; i < rs->rec_nmb; i++)
		{
			if(rs->recs[i].id != -1)
			printf("\t%d;%s;%s;%d;%.2f;%d;%d\n", rs->recs[i].id, rs->recs[i].manufacturer, rs->recs[i].model, rs->recs[i].year, rs->recs[i].price, rs->recs[i].x_size, rs->recs[i].y_size);
		}
	}
	printf("\n\n");
}

/*Function prints file .db
Return type is void*/
void print_db(const char *db) {
	FILE *db_f;
	SCAN_INFO sc;
	int rec_nmb, i;
	if ((db_f = fopen(db, "rb")) == NULL) {
		exit(1);
	}
	fread(&rec_nmb, sizeof(int), 1, db_f);
	printf("%d", rec_nmb);
	while (fread(&sc, sizeof(SCAN_INFO), 1, db_f)) {
		printf("\t%d;%s;%s;%d;%.2f;%d;%d\n", sc.id, sc.manufacturer, sc.model, sc.year, sc.price, sc.x_size, sc.y_size);
	}
	printf("\n\n");
	fclose(db_f);
}