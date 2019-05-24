#include "ListNode.h"
#include <cstring>

ListNode::ListNode()
{
	prev = NULL;
	next = NULL;
	data = NULL;
}

ListNode::ListNode(char *_data)
{
	prev = NULL;
	next = NULL;

	if (_data == NULL)
	{
		data = NULL;
		return;
	}

	data = new char[strlen(_data) + 1];
	strcpy(data, _data);
}

ListNode::~ListNode(void)
{
	delete[] data;
}