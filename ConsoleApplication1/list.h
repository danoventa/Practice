#pragma once

#include <oistream>

class list
{
private:

public:
	list();
	~list();

	struct node
	{
		node* next;
		int data;

		explicit node(int data) : node(nullptr, data) {}
		node(node* head, int data) : next(head), data(data){}
	}; 

	// insert
	node* insert(node* head, int data);
	node* insert_sorted(node* head, int data);

	// find
	node* find(node* head, int value);

	// remove
	node* remove(node* head, node* traget);

	// selection
	node* mid_by_counting(node* head);
	node* mid(node* head);
	node* kth_from_end(node* head, size_t k);

	//modification
	node* remove_values(node* head, int value);
	node* reverse(node* head);

	// check
	bool equals(node* x, node* y);
	node* merge(node* h1, node* h2);
	bool is_palindrome(node* head);
	bool detect_loop(node* head);

	// For circular linked lists
	node* circular_insert(node* head, int data);
	node* circular_find(node* head, int value);
	node* circular_remove(node* head, node* target);


};

