#pragma once

#include <iostream>
#include <iterator>

template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T>> >
class TreeAVL {
public:

	struct Node {
	public:
		Node() = default;
		Node(const Key& key, const T& val) : key_(key), value_(val) { }

		Node* left = nullptr;
		Node* right = nullptr;
		Key key_;
		T value_;
		unsigned int height;
	};
	

	const T& operator[](const Key& k) const;
	const T& at(const Key& k) const;
	T& operator[](const Key& k);
	T& at(const Key& k);

	void insert(const std::pair<Key, T>& elem) {
		
	}

	Node* find(const T& v) {

	}


	bool empty() const { return root == nullptr; } 
	size_t size() const { return size_; }


	void print() {
		
	}
	

private:
	Node* root = nullptr;
	size_t size_;


	Node* find(Node* node, const T& v) {
		
	}

	void insert(Node* node, const std::pair<Key, T>& elem) {
		
	}

	void print(Node* node) {
		if (node) {
			std::cout << '[' << node->key_ << ", " << node->value_ << ']' << ' '; 	
			print(node->left);
			print(node->right);
		}
	}
};

