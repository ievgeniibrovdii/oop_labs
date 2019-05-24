#include "Scanner.h"

int main() {
	RECORD_SET* rs;
	printf("\t\t create_db: \n\n");
	create_db("Scanners.csv", "Scanners.db");
	print_db("Scanners.db");
	reindex("Scanners.db");
	
	printf("\t\t add_scanner: \n\n");
	add_scanner("Scanners.db", "Asus;AS1055;2009;99.99;210;297");
	print_db("Scanners.db");

	printf("\t\t del_scanner: \n\n");
	del_scanner("Scanners.db", 4);
	print_db("Scanners.db");
	
	printf("\t get_recs_by_index(\"Scanners.db\", \"manufacturer\"): \n\n");
	rs = get_recs_by_index("Scanners.db", "manufacturer");
	print_rec_set(rs);
	
	printf("\t select(\"Scanners.db\", \"year\", \"2007\"): \n\n");
	rs = select("Scanners.db", "year", "2007");
	print_rec_set(rs);
	
	free(rs);
	_getch();
	return 0;
}
