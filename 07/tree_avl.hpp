#pragma once

#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>
#include <utility>


enum class Exception
{
	NoRoot,
	NoKey
};


template<
	class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T>> 
>
class TreeAVL 
{
public:
	using Pair = const std::pair<Key, T>;
	struct Node 
	{
	public:
		Node() = default;
		Node(const Key& key, const T& val, size_t curDepth)
		: key_(key), value_(val), depth(curDepth) { }
		Node(Pair elem, Allocator& allocator)
		: allocator_(allocator)
		{
			Pair* pair = allocator.alloc();
			pair->first = elem.first;
			pair->second = elem.second;
		}
		~Node()
		{
			allocator_.deallocate();
		}
		Node* left = nullptr;
		Node* right = nullptr;
		Key key_;
		T value_;
		size_t depth;
	private:
		Allocator allocator_;
	};

	// TreeAVL() = default;
	//~TreeAVL()
	
	const T& operator[](const Key& k) const;
	const T& at(const Key& k) const;
	T& operator[](const Key& k);
	T& at(const Key& k);

	void insert(const std::pair<Key, T>& elem) //noexcept
	{
		size_t curDepth = static_cast<size_t>(log2(size_ + 1));
		Node* new_node = new Node(elem.first, elem.second, curDepth);

		if (root == nullptr) root = new_node;
		else insert(root, new_node);

		++size_;
		//rebalance();
	}

	void erase(const Key& key)
	{
		if (root == nullptr) throw Exception::NoRoot;

		clearStack();
		erase(root, key);
		nodeCounter = 0;
	}

	Node* find(const T& v)
	{
		if (root == nullptr) throw Exception::NoRoot;
		return find(root, v);
	}


	bool empty() const { return root == nullptr; } 
	size_t size() const { return size_; }


	void print() {
		print(root);
		std::cout << std::endl;
	}
	

private:
	Node* root = nullptr;

	size_t size_ = 0;
	size_t nodeCounter = 0;

	Allocator allocator_ = Allocator();
	std::stack<Node*> lastTwoNodes;

	void clearStack()
	{
		while(!lastTwoNodes.empty())
			lastTwoNodes.pop();
	}

	void insert(Node* node, Node* new_node) //noexcept
	{
		if (node == nullptr)
		{
			node = new_node;
			return;
		}

		if ( new_node->key_ < node->key_ )
		{
			if (node->left == nullptr) {
				node->left = new_node;
				return;
			}
			else insert(node->left, new_node);
		}
		else
		{
			if (node->right == nullptr) {
				node->right = new_node;
				return;
			}
			else insert(node->right, new_node);
		}
	}


	void erase(Node* node, Key key)
	{
		
		if (lastTwoNodes.size() > 2)
		{
			Node* prev = lastTwoNodes.top();
			lastTwoNodes.pop();
			Node* prevPrev = lastTwoNodes.top();
			lastTwoNodes.pop();
			clearStack();
			lastTwoNodes.push(prevPrev);
			lastTwoNodes.push(prev);
		}
		nodeCounter++;
		
		if (node->key_ == key)
		{
			if (node->left == nullptr && node->right == nullptr)
				allocator_.deallocate(node);
			else
			{
				Node* parent = lastTwoNodes.top();
				insert(parent, node->left);
				insert(parent, node->right);
			}
			return;
		}

		if (nodeCounter == size_) throw Exception::NoKey;

		if ( key < node->key_ )
		{
			lastTwoNodes.push(node);
			erase(node->left, key);
		} 
		else
		{
			lastTwoNodes.push(node);
			erase(node->right, key);
		}
	}

	Node* find(Node* node, const T& v) 
	{
		if (node == nullptr)     return nullptr;
		if (node->value == v)    return node;
		if (find(node->left, v)) return node->left;
		
		return find(node->right, v);
	}

	void print(Node* node) {
		if (node) {
			std::cout << '[' << node->key_ << ", " << node->value_ << ']' << '\n';
			std::cout << "left : ";	
			print(node->left);
			std::cout << "right : ";
			print(node->right);
		}
	}
};

