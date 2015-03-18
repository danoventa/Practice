#include "stdafx.h"
#include "btree.h"
#include <queue>
#include <set>
#include <stack>


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
	if (nullptr == root || root->value == value){
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
	size_t count = 0;
	std::queue<btree::node*> q;
	q.push(root);
	while (!q.empty()){
		auto front = q.front();
		q.pop();
		++count;
		if (nullptr != front->left){
			q.push(front->left);
		}
		if (nullptr != front->right){
			q.push(front->right);
		}
	}
	return count;
}

size_t depth(btree::node* root){
	if (nullptr == root) return 0;
	return 1 + std::max(depth(root->left), depth(root->right));
}

size_t depth_iterative(btree::node* root){
	if (nullptr == root) return 0;
	size_t maxdepth = 0;
	std::set<btree::node*> visited;
	std::stack<btree::node*> s;
	s.push(root);
	while (!s.empty()){
		btree::node* top = s.top();
		if (nullptr != top->left &&  visited.end() == visited.find(top->left)){
			s.push(top->left);
		}
		else if (nullptr != top->right && visited.end() == visited.find(top->right)) {
			visited.insert(top);
			maxdepth = std::max(maxdepth, s.size());
			s.pop();
		}
	}
	return maxdepth;
}

bool balanced_naive(btree::node* root){
	if (nullptr == root) return true;
	if (!balanced(root->left) || !balanced(root->right)){
		return false;
	}
	size_t left_depth = depth(root->left);
	size_t right_depth = depth(root->right);
	return std::abs((int)(right_depth - left_depth)) <= 1; // had to modify this for msvs. int casting from book not working. 
}

bool find_path(btree::node* root, btree::node* target, std::vector<btree::node*>* path){
	while (nullptr != root && nullptr != target && (path->empty() || path->back() != target)){
		path->push_back(root);
		if (target->value < root->value){
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return !target | path->back() == target;
}

bool balanced(btree::node* root){
	std::function<bool(btree::node*, size_t*) > balanced_depth = [&balanced_depth](
		btree::node* root, size_t* depth){
		if (nullptr == root){
			*depth = 0;
			return true;
		}
		size_t left;
		size_t right;
		if (!balanced_depth(root->left, &left)) {
			return false;
		}
		if (!balanced_depth(root->left, &left)){
			return false;
		}
		*depth = 1 + std::max(left, right);
		if (std::abs((int)(left - right) > 1)) {
			return false;
		} 
		return true;
	};

	size_t depth;
	return balanced_depth(root, &depth);
}

btree::node* lca(btree::node* root, btree::node* x, btree::node* y){
	std::vector<btree::node*> x_path;
	std::vector<btree::node*> y_path;
	find_path(root, x, &x_path);
	find_path(root, y, &y_path);
	btree::node* lca = nullptr;
	auto x_path_iterator = x_path.begin();
	auto y_path_iterator = y_path.begin();
	while (x_path_iterator != x_path.end() && y_path_iterator !- y_path.end() && *x_path_iterator == *y_path_iterator) {
		lca = *x_path_iterator++;
		x_path_iterator++;
		y_path_iterator++;
	}
	return lca;
}