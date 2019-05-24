#include <iostream>
#include "BinTreeBook.h"
#include <cstring>

using namespace std;

// default constructor
CBinTree::CBinTree() {
	root = NULL;
	nd_nmb = 0;
}
// default destructor
CBinTree::~CBinTree() {
	destroy_tree(root);
}

// function read data from csv file to the tree, return 1 if success and 0 if error
int CBinTree::read_csv(const char *csv) {
	FILE *csv_f;
	nd_nmb = 0;
	int i = 0;
	CTreeNode node;
	char str[512];
	if ((csv_f = fopen(csv, "r")) == NULL) {
		return 0;
	}
	
	while(fgets(str, 512, csv_f)){
		sscanf(str, "%d;%[A-z0-9];%[A-z0-9];%d;%d", &(node.m_Bookid), &(node.m_Title), &(node.m_Author), &(node.m_Year), &(node.m_Quantity));
		add_book(str);
	}
	fclose(csv_f);
	return 1;
}

/* function that build the tree according to data from csv file, the return type is void,
function adds book to the tree (creates a tree node) */
void CBinTree::add_book(const CTreeNode &node, CTreeNode **root) {
	if (node.m_Title == NULL || node.m_Author==NULL || node.m_Year==NULL || node.m_Quantity==NULL) return;
	if (node.m_Bookid < 0) return;
	if (!*root) {
		*root = new CTreeNode(node);
		return;
	}
	if (node.m_Bookid < (*root)->m_Bookid) {
		add_book(node, &(*root)->left);
	}
	else if (node.m_Bookid > (*root)->m_Bookid) {
		add_book(node, &(*root)->right);
	}
}

// function delete node in the tree, returns the pointer to deleted node
CTreeNode* CBinTree::DelNode(CTreeNode **root, int id) {
	if (*root == NULL)
		return NULL;
	if (id < 0)
		return NULL;
	if ((*root)->m_Bookid == id) {
		if ((*root)->left == NULL && (*root)->right == NULL) {
			delete *root;
			return NULL;
		}
		if ((*root)->left != NULL && (*root)->right == NULL) {
			CTreeNode *ptrnode = (*root)->left;
			delete (*root);
			return ptrnode;
		}
		if ((*root)->left == NULL && (*root)->right != NULL) {
			CTreeNode *ptrnode = (*root)->right;
			delete (*root);
			return ptrnode;
		}
		(*root)->m_Bookid = Most_Right((*root)->left);
		(*root)->left = DelNode(&(*root)->left, (*root)->m_Bookid);
		return *root;
	}

	if (id < (*root)->m_Bookid) {
		(*root)->left = DelNode(&(*root)->left, id);
		return *root;
	}
	if (id > (*root)->m_Bookid) {
		(*root)->right = DelNode(&(*root)->right, id);
		return *root;
	}
	return NULL;
}

// function is seaching more right node in the tree, returns a id information in the node 
int CBinTree::Most_Right(CTreeNode *root) {
	if (root == NULL) return -1;
	while (root->right != NULL) 
		root = root->right;
		return root->m_Bookid;
}

// function that prints the tree
void CBinTree::Print_the_Tree(CTreeNode *root, direction ord) {
	if (root) {
		if (ord == UP)
			Print_the_Tree(root->left, ord);
		else Print_the_Tree(root->right, ord);
		
		printf("\t%d;%s;%s;%d;%d\n", root->m_Bookid, root->m_Title, root->m_Author, root->m_Year, root->m_Quantity);
		if (ord == UP)
			Print_the_Tree(root->right, ord);
		else Print_the_Tree(root->left, ord);
	}
}

// function parsing the string, returns a node with parsing data
CTreeNode CBinTree::pars(const char* str) {
	CTreeNode node;
	if (str == NULL) {
		node.m_Bookid = -1;
		return node;
	}
	sscanf(str, "%d;%[A-z0-9];%[A-z0-9];%d;%d", &(node.m_Bookid), &(node.m_Title), &(node.m_Author), &(node.m_Year), &(node.m_Quantity));
	return node;
}

// function check availability of current book in the library (tree)
int CBinTree::availability_book(const char *book_name, CTreeNode *root) {
	if (book_name == NULL) return 0;
	if (root) {
		availability_book(book_name, root->left);
		if (strcmp(root->m_Title, book_name)==0) {
			printf("\nThe book \"%s\" is available in %d copies\n", book_name, root->m_Quantity);
			return 1;
		}
		availability_book(book_name, root->right);
	}
}

// function highlight some memory and returns pointer to this part of memory
CTreeNode* CBinTree::memory_move() {
	CTreeNode* set = (CTreeNode*)malloc(nd_nmb * sizeof(CTreeNode));
	return set;
}

// function returns the pointer to author's books set (record set)
CTreeNode* CBinTree::get_authors_books(const char* author, CTreeNode* root, int i, CTreeNode* set) {
	if (author == NULL)
		return NULL;
	if (set == NULL)
		return NULL;
	if (root) {
		get_authors_books(author, root->left, i, set);
		if (strcmp(root->m_Author, author) == 0) {
			strcpy(set[i].m_Title, root->m_Title);
			strcpy(set[i].m_Author, root->m_Author);
			set[i].m_Bookid = root->m_Bookid;
			set[i].m_Quantity = root->m_Quantity;
			set[i].m_Year = root->m_Year;
		}
		else set[i].m_Bookid = -1;
		i++;
		get_authors_books(author, root->right, i, set);
	}
	return set;
}

// function prints an author's books set (record set)
void CBinTree::print_author_books_set(CTreeNode* recs) {
	int i = 0;
	if (recs == NULL)
		return;
	//printf("nd_nmb = %d\n\n", nd_nmb);
	for (i = 0; i < nd_nmb; i++) {
		
		if (recs[i].m_Bookid != -1)
			printf("\t%d;%s;%s;%d;%d\n", recs[i].m_Bookid, recs[i].m_Title, recs[i].m_Author, recs[i].m_Year, recs[i].m_Quantity);
	}
}

// function destroys the tree
void CBinTree::destroy_tree(CTreeNode *node) {
	if (node) {
		destroy_tree(node->left);
		destroy_tree(node->right);
		delete node;
	}
	else return;
}