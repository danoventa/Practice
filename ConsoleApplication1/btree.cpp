#include "stdafx.h"
#include "btree.h"


btree::btree()
{
}


btree::~btree()
{
}

btree::node* insert(btree::node* root, int val){
	if (nullptr == root){
		return new btree::node(val);
	}
	if (val < root->value){
		root->left = insert(root->left, val);
	}
	else {
		root->right = insert(root->right, val);
	}
	return root;
}

btree::node* find(btree::node* root, int value){
	if (nullpr == root || root->value == value){
		return root;
	}
	if (value < root->value){
		return find(root->left, value);
	}
	return find(root->right, value);
}

btree::node* find_parent(btree::node* root, btree::node* target){
	if (root == target){
		return nullptr;
	}
	while (root->left != target && root->right != target){
		if (target->value < root->value){
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return root;
}

btree::node* find_successor(btree::node* root, node* target){
	auto successor = target->right;
	if (nullptr != successor->left){
		while (nullptr != successor->left){
			successor = successor->left;
		}
		return successor;
	}
	do {
		if (nullptr != successor) {
			target = successor;
		}
		successor = find_parent(root, target);
	} while (nullptr != successor && successor->right == target);
	return successor;
}

btree::node* remove(btree::node* root, btree::node* target){
	if (nullptr != target->left && nullptr != target->right){
		btree::node* next = find_successor(root, target);
		int data = next->value;
		remove(root, next);
		target->value = data;
		return root;
	}
	if (nullptr != target->left || nullptr != target->right){
		btree::node* temp = target->left ? target->left : target->right;
		target->value = temp->value;
		target->left = temp->left;
		target->right = temp->right;
		delete temp;
		return root;
	}
	if (root == target){
		delete root;
		return nullptr;
	}
	btree::node* parent = find_parent(root, target);
	if (parent->left == target){
		parent->left = nullptr;
	}
	else{
		parent->right = nullptr;
	}
	delete target;
	return root;
}

size_t size(btree::node* root){
	if (nullptr == root){
		return 0;
	}
	return 1 + size(root->left) + size(root->right);
}

size_t size_iterative(btree::node* root){
	if (nullptr == root) return 0;
}