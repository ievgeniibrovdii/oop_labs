#pragma once

class CTreeNode {
	int m_Bookid;
	char m_Author[127];
	char m_Title[127];
	int m_Year;
	int m_Quantity;
	CTreeNode *left;
	CTreeNode *right;
public:
	friend class CBinTree;
	CTreeNode();
	CTreeNode(const CTreeNode &nd);
	CTreeNode(char*);
	~CTreeNode(void);
};