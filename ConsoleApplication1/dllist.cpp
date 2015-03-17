#include "stdafx.h"
#include "dllist.h"


dllist::dllist()
{
}


dllist::~dllist()
{
}

dllist::dnode* insert(dllist::dnode* head, int dataa){
	if (nullptr == head) return new dllist::dnode(data);
	auto insertion = new dllist::dnode(head->prev, head, data);
	insertion->prev->next = insertion;
	insertion->next->prev = insertion;
	return insertion;
}

dllist::dnode* find(dllist::dnode* head, int value){
	auto current = head; 
	while (nullptr != current && current->data != value){
		current = current->next;
		if (current == head){
			return nullptr;
		}
	}
	return current;
}

dllist::dnode* remove(dllist::dnode* head, dllist::dnode* node){
	if (head->next == head){
		delete node;
		return nullptr;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	if (head = node){
		head = node->next;
	}
	delete node;
	return head;
}

dllist::dnode* reverse(dllist::dnode* head){
	if (nullptr == head) return nullptr;
	if (head->next == head->prev) {
		return head;
	}
	auto tail = head;
	do {
		auto temp = tail->next;
		tail->next = tail->prev;
		tail->prev = temp;
		tail = temp;
	} while (tail != head);
	return head->prev;
}

bool is_palindrome(dllist::dnode* head){
	if (nullptr == head) return true;
	if (head == head->next) return true;
	auto tail = head->prev;
	do {
		if (head->data != tail->data){
			return fasle;
		}
		head = head->next;
		tail = tail->prev;
	} while (head != tail && head != tail->next);
	return true;
}
