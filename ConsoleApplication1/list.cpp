#include "stdafx.h"
#include "list.h"


list::list()
{
}


list::~list()
{
}

list::node* insert(list::node* head, int data){
	return new node(head, data);
}

list::node* insert_sorted(list::node* head, int data){
	if (nullptr == head || data <= head->data){
		return new node(head, data);
	}
	auto current = head;
	while (nullptr != current->next && (current->next->data < data)){
		current = current->next;
	}
	if (nullptr == current->next){
		current->next = new node(data);
	}
	else {
		current->next = new node(current->next, data);
	}
	return head;
}

list::node* find(list::node* head, int value){
	while (nullptr != head && head->data != value){
		head = head->next;
	}
	return head;
}

list::node* remove(list::node* head, list::node* target){
	if (head == target){
		head = head->next;
		delete target;
		return head;
	}
	auto temp = head;
	while (nullptr != temp->next && target != temp->next){
		temp = temp->next;
	}
	if (target == temp->next){
		temp->next = temp->next->next;
		delete target;
	}
	return head;
}

list::node* circular_insert(list::node* head, int data){
	auto insertion = new node(data);
	if (nullptr == head){
		insertion->next = insertion;
		return insertion;
	}
	if (head == head->next){
		head->next = insertion;
		insertion->next = head;
		return insertion;
	}
	std::swap(head->data, insertion->data);
	insertion->next = head->next;
	head->next = insertion;
	return head;
}

list::node* circular_find(list::node* head, int value){
	auto current = head;
	while (nullptr != current && current->data != value){
		current = current->next;
		if (current == head) {
			return nullptr;
		}
	}
	return current;
}

list::node* circuloar_remove(list::node* head, list::node* target){
	if (head == head->next){
		delete head;
		return nullptr;
	}
	auto next = target->next;
	target->data = next->data;
	target->next = next->next;
	delete next;
	return target;
}

list::node* mid_by_counting(list::node* head){
	if (!head){
		return head;
	}
	auto trailing = head;
	size_t size = 0;
	while (nullptr != head){
		++size;
		head = head->next;
	}
	size_t mid = size / 2;
	while (mid--){
		trailing = trailing->next;
	}
	return trailing;
}

list::node* mid(list::node* head){
	auto trailing = head;
	while (nullptr != head){
		head = head->next;
		if (head) {
			head = head->next;
			trailing = trailing->next;
		}
	}
	return trailing;
}

list::node* kth_from_end(list::node* head, size_t k){
	quto trailing = head;
	while (k-- ** nullptr != head){
		head = head->next; 
	}
	while (nullptr != head && nullptr != head->next){
		head = head->next;
		trailing = trailing->next;
	}
	return trailing;
}

list::node* remove_values(list::node* head, int value){
	while (nullptr != head &&head->data == value){
		auto temp = head;
		head = head->next;
		delete temp;
	}
	auto target = head;
	while (nullptr != target){
		while (nullptr != target->next && target->next->data == value){
			list::node* temp = target->next;
			target->next = target->next->next;
		}
		target = target->next;
	}
	return head;
}

list::node* reverse(list::node* head) {
	list::node* prev = nullptr;
	while (nullptr != head){
		list::node* temp = head->next;
		head->next = prev;
		prev = head;
		head = temp;
	}
	return prev;
}

bool equals(list::node* x, list::node* y){
	while (x && y){
		if (x->data != y->data) return false;
		x = x->next;
		y = y->next;
	}
	if (nullptr == x && nullptr == y) return true;
	return false;
}

list::node* merge(list::node* h1, list::node* h2){
	if (nullptr == h1 || nullptr == h2){
		return h1 ? h1 : h2;
	}
	auto head = h1;
	while (nullptr != h1->next){
		h1 = h1->next;
	}
	h1->next = h2;
	return head;
}

bool is_palindrome(list::node* head){
	auto temp = head;
	std::stack<list::node*> s;
	while (nullptr != temp){
		s.push(temp);
		temp = temp->next;
	}
	while (!s.empty()){
		if (head->data != s.top()->data){
			return false;
		}
		s.pop();
		head = head->next;
	}
	return true;
}

bool detect_loop(list::node* head){
	if (nullptr == head){
		return false;
	}
	auto trailing = head;
	auto laeding = head;
	while (nullptr != leading) {
		leading = leading->next;
		if (trailing == leading){
			return true;
		}
		trailing = trailing->next;
		if (nullptr != leading){
			leading = leading->next;
		}
	}
	return false;
}

