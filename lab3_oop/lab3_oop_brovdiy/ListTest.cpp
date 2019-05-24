#include <iostream>
#include <conio.h>
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
	DoublyLinkedList *List1 = new DoublyLinkedList(), *List2 = new DoublyLinkedList();
	cout << "---------List1-----------------------------------\n\n";
	List1->push_back(*(new ListNode("5")));
	List1->push_back(*(new ListNode("2")));
	List1->push_back(*(new ListNode("0")));
	List1->push_back(*(new ListNode("7")));
	List1->print();
	cout << "\n\n-------Push_front(0)--and--Pop_back()------------\n\n";
	List1->push_front(*(new ListNode("0")));
	List1->pop_back();
	List1->print();
	cout << "\n\n--------Push_back(6,3,1)-------------------------\n\n";
	List1->push_back(*(new ListNode("6")));
	List1->push_back(*(new ListNode("3")));
	List1->push_back(*(new ListNode("1")));
	List1->print();
	
	cout << "\n\n------List1--after--sorting----------------------\n\n";
	List1->sort();
	List1->print();
	cout << "\n\n--------Unique-----------------------------------\n\n";
	List1->unique();
	List1->print();

	cout << "\n\n--------Insert_ord(4)----------------------------\n\n";
	List1->insert_ord(*(new ListNode("4")));
	List1->print();

	cout << "\n\n--------Insert_after(2, -1)----------------------\n\n";
	List1->insert_after("2", *(new ListNode("-1")));
	List1->print();

	cout << "\n\n---------List2-------\n\n";
	List2->push_back(*(new ListNode("1")));
	List2->push_back(*(new ListNode("3")));
	List2->push_back(*(new ListNode("4")));
	List2->print();

	cout << "\n\n--------Assign(List2,1,1)--to--List1--------------\n\n";
	List1->assign(*List2, 1, 1);
	List1->print();
	
	cout << "\n\n---------List2_backward----------------------------\n\n";
	List2->print_bkw();
	cout << "\n\n--------List1->splice(0, List2)--------------------\n\n";
	List1->splice(0, *List2);
	List1->print();

	cout << "\n\n--------List1->erase(0),(1),(2),(3)----------------\n\n";
	List1->erase("0");
	List1->erase("1");
	List1->erase("2");
	List1->erase("3");
	List1->print();

	cout << "\n\n------List1--after--sorting------------------------\n\n";
	List1->sort();
	List1->print();
	
	_getch();
	return 0;
}