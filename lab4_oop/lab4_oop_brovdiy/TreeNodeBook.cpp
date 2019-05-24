#include "TreeNodeBook.h"
#include <cstring>
#include <stdio.h>

CTreeNode::CTreeNode()
{
	m_Bookid = 0;
	m_Author[0] = '\0';
	m_Title[0] = '\0';
	m_Year = 0;
	m_Quantity = 0;
	left = NULL;
	right = NULL;
}

CTreeNode::CTreeNode(char *str)
{
	left = NULL;
	right = NULL;

	if (str == NULL)
	{
		m_Bookid = 0;
		m_Author[0] = '\0';
		m_Title[0] = '\0';
		m_Year = 0;
		m_Quantity = 0;
		return;
	}	
}

CTreeNode::CTreeNode(const CTreeNode &nd)
{
	m_Bookid = nd.m_Bookid;
	strcpy(m_Author, nd.m_Author);
	strcpy(m_Title, nd.m_Title);
	m_Year = nd.m_Year;
	m_Quantity = nd.m_Quantity;
	left = NULL;
	right = NULL;
}

CTreeNode::~CTreeNode(void){}