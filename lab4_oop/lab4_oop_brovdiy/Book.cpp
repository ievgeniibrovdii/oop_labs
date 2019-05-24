#include <iostream>
#include <conio.h>
#include "BinTreeBook.h"

using namespace std;

int main()
{
	CBinTree book;
	CTreeNode* rs;
	int available;
	cout << " Read from csv to the tree: \n";
	printf("|-----------------------------------------------------|\n");
	book.read_csv("Book.csv"); 
	book.Print_the_Tree(UP); 
	
	cout << endl << " Delete book: \n";
	printf("|-----------------------------------------------------|\n");
	book.DelNode(7);
	book.Print_the_Tree(UP);
	
	cout << "\n Add book :\n";
	printf("|-----------------------------------------------------|\n");
	book.add_book("12;Consuello;GeorgeSand;1842;19");
	book.Print_the_Tree(UP);

	cout << "\n Availability book: \n";
	printf("|-----------------------------------------------------|\n");
	available = book.availability_book("Consuello");
	printf("Books available: %d \n", available);
	
	cout << "\n\n Get Author's books :\n";
	printf("|-----------------------------------------------------|\n");
	rs = book.get_authors_books("Bulgakov"); 
	book.print_author_books_set(rs);
	free(rs);
	_getch();
	return 0;
}