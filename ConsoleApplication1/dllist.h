#pragma once
class dllist
{
private:

public:
	dllist();
	~dllist();

	struct dnode {
		dnode* prev;
		dnode* next;
		int data;

		explicit dnode(int data) : dnode(this, this, data) {}
		dnode(dnode *prev, dnode*next, int data) : prev(prev), next(next), data(data) {}
	};

	dnode* insert(dnode* head, int data);
	dnode* find(dnode* head, int value); 
	dnode* remove(dnode* head, dnode* node);
	dnode* reverse(dnode* head);
	dnode* is_palindrome(dnode* head);

};

