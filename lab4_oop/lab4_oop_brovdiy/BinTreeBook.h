#pragma once
#pragma warning (disable:4715)
#include "TreeNodeBook.h"
typedef enum {UP, DOWN} direction;


class CBinTree {
	CTreeNode *root;
	int nd_nmb;
public:
	CBinTree(void);								
	~CBinTree(void);							
	
	int read_csv(const char *csv);

	void add_book(const char* str) {
		CTreeNode node = pars(str);
		add_book(node, &root);
		nd_nmb++;
	}

	void DelNode(int id) {
		DelNode(&root, id);
		nd_nmb--;
	}

	void Print_the_Tree(direction ord) {
		Print_the_Tree(root, ord);
	}
	
	int availability_book(char* book_name) {
		if(availability_book(book_name, root)==1)
		return 1;
		else return 0;
	}

	CTreeNode* get_authors_books(const char* author) {
		return get_authors_books(author, root, 0, memory_move());
	}
	void print_author_books_set(CTreeNode* recs);
	void destroy_tree(CTreeNode *node);
private:
	int Most_Right(CTreeNode *root);
	CTreeNode pars(const char*);
	CTreeNode* DelNode(CTreeNode **root, int id);
	void add_book(const CTreeNode &node, CTreeNode **root);
	int availability_book(const char*, CTreeNode* root);
	CTreeNode* get_authors_books(const char* author, CTreeNode* root, int i, CTreeNode* set);
	void Print_the_Tree(CTreeNode *root, direction ord);
	CTreeNode* memory_move();
};
