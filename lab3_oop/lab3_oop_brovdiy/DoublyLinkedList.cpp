#include <iostream>
#include "DoublyLinkedList.h"
#include <cstring>

using namespace std;

DoublyLinkedList::DoublyLinkedList()
{
	head = NULL;
	tail = NULL;
	nd_size = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	clear();
}

int DoublyLinkedList::size()
{
	return nd_size;
}

bool DoublyLinkedList::empty()
{
	return head == NULL;
}

void DoublyLinkedList::clear()
{
	if (head == NULL)
		return;

	while (head->next != NULL)
	{
		head = head->next;
		delete head->prev;
	}

	delete head;

	nd_size = 0;
	head = NULL;
	tail = NULL;
}

void DoublyLinkedList::push_back(const ListNode &nd)
{
	if (nd.data == NULL) return;
	if (head == NULL)
	{
		nd_size += 1;
		head = new ListNode(nd.data);
		tail = head;
		return;
	}
	nd_size += 1;
	tail->next = new ListNode(nd.data);
	tail->next->prev = tail;
	tail = tail->next;
}

void DoublyLinkedList::push_front(const ListNode &nd)
{
	ListNode *Node = new ListNode(nd.data);

	if (nd.data == NULL) return;
	if (head == NULL)
	{
		head = Node;
		tail = head;
		return;
	}

	head->prev = Node;
	Node->next = head;
	head = Node;
	nd_size += 1;
}

void DoublyLinkedList::pop_front()
{
	if (head == NULL)
		return;

	if (head->next == NULL)
	{
		delete head;
		head = NULL;
		tail = NULL;
		return;
	}

	head = head->next;
	delete head->prev;
	head->prev = NULL;
	nd_size -= 1;
}

void DoublyLinkedList::pop_back()
{
	if (tail == NULL)
		return;

	if (tail->prev == NULL)
	{
		delete tail;
		tail = NULL;
		head = NULL;
		return;
	}

	tail = tail->prev;
	delete tail->next;
	tail->next = NULL;
	nd_size -= 1;
}

void DoublyLinkedList::insert_ord(const ListNode &nd)
{
	ListNode *curr, *Node = new ListNode(nd.data);
	if (nd.data == NULL) return;
	if (head == NULL || strcmp(nd.data, head->data) <= 0)
	{
		push_front(*Node);
		return;
	}
	nd_size++;
	curr = head->next;

	while (curr != NULL)
	{
		if (strcmp(curr->data, nd.data) >= 0)
		{
			Node->next = curr;
			Node->prev = curr->prev;
			curr->prev->next = Node;
			curr->prev = Node;
			return;
		}

		curr = curr->next;
	}

	push_back(*Node);
}

void DoublyLinkedList::sort()
{
	int i = 0;
	int j = 0;
	ListNode *temp = head, *p;
	if (this->head == this->tail)
		return;

	for (i = 0; i < nd_size -1; i++) {
		for (j = 0; j < nd_size - i - 1; j++) {
			if (strcmp(temp->data, temp->next->data) > 0){
				if (temp != head)
					temp->prev->next = temp->next;
				if (temp == head)
					head = temp->next;
				if (temp->next != tail)
					temp->next->next->prev = temp;
				if (temp->next == tail)
					tail = temp;
				p = temp->next->next;
				temp->next->next = temp->next->prev;
				temp->next->prev = temp->prev;
				temp->prev = temp->next;
				temp->next = p;
		}
			else temp = temp->next;
		}
		temp = head;
	}
}

bool DoublyLinkedList::insert_after(char *dat, const ListNode &nd)
{
	ListNode *curr = head, *Node;
	if (dat == NULL) return false;
	if (nd.data == NULL) return false;
	if (head == NULL)
		return false;
	nd_size++;
	while (curr->next != NULL)
	{
		if (strcmp(curr->data, dat) == 0)
		{
			Node = new ListNode(nd.data);
			Node->prev = curr;
			Node->next = curr->next;
			curr->next->prev = Node;
			curr->next = Node;
			return true;
		}

		curr = curr->next;
	}

	if (strcmp(tail->data, dat) == 0)
	{
		push_back(*(new ListNode(nd.data)));
		return true;
	}

	return false;
}

void DoublyLinkedList::operator=(const DoublyLinkedList &dl)
{
	ListNode *res = dl.head;

	if (this == &dl)
		return;

	this->clear();

	while (res != NULL)
	{
		this->push_back(*(new ListNode(res->data)));
		res = res->next;
	}
}

void DoublyLinkedList::merge(DoublyLinkedList &dl)
{
	if (this == &dl)
		return;

	while (dl.head != NULL)
	{
		this->push_back(*(new ListNode(dl.head->data)));
		dl.pop_front();
	}

	this->sort();
}

void DoublyLinkedList::erase(char *dat)
{
	ListNode *curr, *val;
	if (dat == NULL) return;
	if (head == NULL)
		return; 

	while (strcmp(dat, head->data) == 0)
	{
		pop_front();
		if (head == NULL) return;
	}

	curr = head->next;

	while (curr->next != NULL)
	{
		if (strcmp(dat, curr->data) == 0)
		{
			nd_size--;
			val = curr->next;
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			delete curr;
			curr = val;
			continue;
		}

		curr = curr->next;
	}

	if (strcmp(dat, tail->data) == 0)
		pop_back();
}

void DoublyLinkedList::unique()
{
	ListNode *curr = head, *val;
	if (head == NULL) return;
	if (nd_size <= 1)
		return;
	while (curr->next != NULL)
	{
		if (strcmp(curr->data, curr->next->data) == 0)
		{
			nd_size--;
			val = curr->next->next;
			delete curr->next;
			curr->next = val;
			if (val != NULL) val->prev = curr;
			continue;
		}

		curr = curr->next;
	}
}

void DoublyLinkedList::assign(DoublyLinkedList &dl, int first, int last)
{
	int i;
	ListNode *curr = dl.head, *val;

	if (first < 0 || last > dl.nd_size - 1)
		return;

	if (&dl == NULL) return;

	for (i = 0; i < first; i++)
		curr = curr->next;

	for (; i <= last; i++)
	{
		this->push_back(*(new ListNode(curr->data)));
		if (curr == dl.head)
		{
			curr = curr->next;
			dl.pop_front();
			continue;
		}
		else if (curr == dl.tail)
		{
			dl.pop_back();
			return;
		}
	
		val = curr->next;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete curr;
		curr = val; 
	}
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl)
{
	ListNode *val = this->head, *end = this->tail, *curr = dl.head;
	int i;

	if (where < 0 || where - 1 > this->nd_size || this == &dl)
		return;

	this->tail = NULL;

	for (i = 0; i < where; i++)
	{
		this->tail = val;
		val = val->next;
	}

	if (this->tail == NULL)
		this->head = NULL;

	while (curr != NULL)
	{
		this->push_back(*(new ListNode(curr->data)));
		curr = curr->next;
	}

	this->tail->next = val;
	if (val != NULL) val->prev = this->tail;
	this->tail = end;
}

void DoublyLinkedList::splice(int where, const DoublyLinkedList &dl, int first, int last)
{
	ListNode *val = this->head, *end = this->tail, *curr = dl.head;
	int i;

	if (where < 0 || where - 1 > this->nd_size || first < 0 || last - 1 > dl.nd_size || this == &dl)
		return;

	this->tail = NULL;

	for (i = 0; i < where; i++)
	{
		this->tail = val;
		val = val->next;
	}

	if (this->tail == NULL)
		this->head = NULL;

	for (i = 0; i < first; i++)
		curr = curr->next;

	while (curr != NULL && i <= last)
	{
		this->push_back(*(new ListNode(curr->data)));
		curr = curr->next;
		i++;
	}

	this->tail->next = val;
	if (val != NULL) val->prev = this->tail;
	this->tail = end;
}

void DoublyLinkedList::print()
{
	int i = 0;
	ListNode *curr;
	cout <<  endl << "nd_size = " << nd_size << endl << endl;
	if (empty()==true)
	{
		cout << "List is empty" << endl;
		return;
	}

	for (curr = head; curr != NULL; curr = curr->next)
	{
		if (curr->next == NULL)
			cout <<  curr->data;
		 else cout << curr->data << " -> ";
	}
}

void DoublyLinkedList::print_bkw()
{
	int i = nd_size - 1;
	ListNode *curr;

	if (empty()==true)
	{
		cout << "List is empty" << endl;
		return;
	}

	for (curr = tail; curr != NULL; curr = curr->prev)
	{
		
		if (curr->prev == NULL)
			cout << curr->data;
		 else cout << curr->data << " <- ";
	}
}