#pragma once
#include <vector>
#include <functional>

class btree
{
private:

public:
	btree();
	~btree();

	struct node{
		int value;
		node* left = nullptr;
		node* right = nullptr;

		explicit node(int value) : value(value) {};
	};

	node* insert(node* root, int val);
	node* find(node* root, int value);
	node* find_parent(node* root, node* target);
	node* find_successor(node* root, node* target);
	node* remove(node* root, node* target);
	size_t size(node* root);
	size_t size_iterative(node* root);
	size_t depth(node* root);
	size_t depth_iterative(node* root);
	bool balanced_naive(node* root);
	bool balanced(node* root);
	bool find_path(node* root, node* target, std::vector<node*>* path);
	node* lca(node* root, node* x, node* y);
	node* lca_recursive(node* root, node* x, node* y);
	node* lca_iterative(node* root, node* x, node* y);
	void inorder(node* root, std::function<void(node*)>visit);
	void postorder(node* root, std::function<void(node*)> visit);
	void preorder(node* root, std::function<void(ndoe*)> visit);
	node* reconstruct_tree(const std::_Vector_iterator<int>& inorder, const std::vector<int>& preorder);

};

