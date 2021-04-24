#pragma once

#include <functional>
#include <vector>
#include <iterator>

// Comparator has to compare keys
template <class Key, class Value, class Comparator = std::less<Key>>
class SplayTree
{
private:
	struct Node;
public:
	using Pair = std::pair<Key, Value>;

	struct Iterator;

	SplayTree();
	SplayTree(const std::initializer_list<Pair>& lst);
	SplayTree(const SplayTree& tree);

	~SplayTree();

	Iterator find(const Key& key);

	Iterator insert(const Pair& p);
	Iterator insert(const Key& key, const Value& value);

	void erase(const Key& key);

	size_t size() const;

	void clear();

	Value& operator[] (const Key& key);

private:
	Node* m_root;

	struct Node {
		Node();
		Node(const Pair& p) : Node(p.first, p.second) {}
		Node(const Key& akey, const Value& avalue);
		Node(const Node& node);

		~Node();

		Node* leftChild;
		Node* rightChild;
		Node* parent;

		Key key;
		Value value;
	};

	static Node* find(Node* node, const Key& key);
	

	static Node* min(Node* node);
	static Node* max(Node* node);

	static Node* prev(Node* node);
	static Node* next(Node* node);

	static Node* rotateL(Node* node);
	static Node* rotateR(Node* node);
	static Node* splay(Node* node);

	static std::pair<Node*, Node*> split(Node* node, const Key& key);
	static Node* merge(Node* left, Node* right); // In the right tree has to be an element with key greater than left->key

	static size_t size(Node* node);

public:
	struct Iterator {
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::pair<std::reference_wrapper<const Key>, std::reference_wrapper<const Value>>;
		using reference = std::pair<std::reference_wrapper<const Key>, std::reference_wrapper<Value>>;
		using pointer = Node*;
		using difference_type = ptrdiff_t;

		pointer ptr;

		Iterator(pointer p = NULL) : ptr(p) {}
		Iterator(const Iterator& it) : ptr(it.ptr) {}

		value_type operator* () const {
			return { ptr->key, ptr->value };
		}

		reference operator* () {
			return { ptr->key, ptr->value };
		}

		Iterator& operator++ () {
			ptr = SplayTree::next(ptr);
			return *this;
		}

		Iterator& operator-- () {
			ptr = SplayTree::prev(ptr);
			return *this;
		}

		bool operator== (const Iterator& other) const {
			return ptr == other.ptr;
		}

		bool operator!= (const Iterator& other) const {
			return ptr != other.ptr;
		}
	};

	Iterator begin() const;
	Iterator end() const;
};

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::SplayTree()
{
	m_root = NULL;
}

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::SplayTree(const std::initializer_list<Pair>& lst)
{
	for (const Pair& p : lst) {
		insert(p);
	}
}

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::SplayTree(const SplayTree& tree)
{
	if (tree.m_root) {
		m_root = new Node(*tree.m_root);
	}
	else {
		m_root = NULL;
	}
}

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::~SplayTree()
{
	clear();
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Iterator SplayTree<Key, Value, Comparator>::find(const Key& key)
{
	Node* found = find(m_root, key);
	if (found) m_root = found;
	return Iterator(found ? (found->key == key ? found : NULL) : NULL);
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Iterator SplayTree<Key, Value, Comparator>::insert(const Pair& p)
{
	auto children = split(m_root, p.first);
	m_root = new Node(p.first, p.second);

	m_root->leftChild = children.first;
	if (m_root->leftChild) m_root->leftChild->parent = m_root;

	m_root->rightChild = children.second;
	if (m_root->rightChild) m_root->rightChild->parent = m_root;

	return Iterator(m_root);
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Iterator SplayTree<Key, Value, Comparator>::insert(const Key& key, const Value& value)
{
	return insert({ key, value });
}

template<class Key, class Value, class Comparator>
void SplayTree<Key, Value, Comparator>::erase(const Key& key)
{
	auto subtrees = split(m_root, key);
	m_root = merge(subtrees.first, subtrees.second);
}

template<class Key, class Value, class Comparator>
size_t SplayTree<Key, Value, Comparator>::size() const
{
	return m_root ? size(m_root) : 0;
}

template<class Key, class Value, class Comparator>
void SplayTree<Key, Value, Comparator>::clear()
{
	if (!m_root) return;
	delete m_root;
	m_root = NULL;
}

template<class Key, class Value, class Comparator>
Value& SplayTree<Key, Value, Comparator>::operator[](const Key& key)
{
	Iterator it = find(key);
	if (it != end()) return (*it).second.get();

	return (*insert({ key, Value() })).second.get();
}

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::Node::Node()
{
	leftChild = NULL;
	rightChild = NULL;
	parent = NULL;
}

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::Node::Node(const Key& akey, const Value& avalue)
{
	leftChild = NULL;
	rightChild = NULL;
	parent = NULL;

	key = akey;
	value = avalue;
}

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::Node::Node(const Node& node)
{
	if (node.leftChild) {
		leftChild = new Node(*node.leftChild);
		leftChild->parent = this;
	}
	else {
		leftChild = NULL;
	}

	if (node.rightChild) {
		rightChild = new Node(*node.rightChild);
		rightChild->parent = this;
	}
	else {
		rightChild = NULL;
	}

	parent = NULL;

	key(node.key);
	value(node.value);
}

template<class Key, class Value, class Comparator>
SplayTree<Key, Value, Comparator>::Node::~Node()
{
	if (leftChild) delete leftChild;
	if (rightChild) delete rightChild;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::find(Node* node, const Key& key)
{
	if (!node) return node;

	if (node->key == key) {
		return splay(node);
	}

	if (node->key < key && node->rightChild) {
		return find(node->rightChild, key);
	}

	if (node->key > key && node->leftChild) {
		return find(node->leftChild, key);
	}

	return splay(node);
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::min(Node* node)
{
	if (!node) return NULL;
	if (node->leftChild) return min(node->leftChild);
	return node;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::max(Node* node)
{
	if (!node) return NULL;
	if (node->rightChild) return max(node->rightChild);
	return node;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::prev(Node* node)
{
	if (node->leftChild) return max(node->leftChild);

	Node* current = node->parent;
	for (; current && Comparator()(node->key, current->key); current = current->parent) {}

	return current;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::next(Node* node)
{
	if (node->rightChild) return min(node->rightChild);

	Node* current = node->parent;
	for (; current && Comparator()(current->key, node->key); current = current->parent) {}

	return current;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::rotateL(Node* node)
{
	Node* right = node->rightChild;
	if (!right) return node;

	node->rightChild = right->leftChild;
	if (node->rightChild) node->rightChild->parent = node;

	right->parent = node->parent;
	if (node->parent) {
		if (node->parent->rightChild == node) {
			node->parent->rightChild = right;
		}
		else {
			node->parent->leftChild = right;
		}
	}

	node->parent = right;
	right->leftChild = node;

	return right;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::rotateR(Node* node)
{
	Node* left = node->leftChild;
	if (!left) return node;

	node->leftChild = left->rightChild;
	if (node->leftChild) node->leftChild->parent = node;

	left->parent = node->parent;
	if (node->parent) {
		if (node->parent->leftChild == node) {
			node->parent->leftChild = left;
		}
		else {
			node->parent->rightChild = left;
		}
	}

	node->parent = left;
	left->rightChild = node;

	return left;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::splay(Node* node)
{
	if (!(node && node->parent)) return node;

	if (node->parent->leftChild == node) {
		return splay(rotateR(node->parent));
	}

	return splay(rotateL(node->parent));
}

template<class Key, class Value, class Comparator>
std::pair<typename SplayTree<Key, Value, Comparator>::Node*, typename SplayTree<Key, Value, Comparator>::Node*> 
SplayTree<Key, Value, Comparator>::split(Node* node, const Key& key)
{
	if (!node) return { NULL, NULL };

	node = find(node, key);
 
	if (node->key == key) {
		if (node->leftChild) node->leftChild->parent = NULL;
		if (node->rightChild) node->rightChild->parent = NULL;
		std::pair<Node*, Node*> p = { node->leftChild, node->rightChild };

		node->leftChild = NULL;
		node->rightChild = NULL;
		delete node;

		return p;
	}

	if (node->key > key) {
		Node* left = node->leftChild;
		if (left) left->parent = NULL;
		node->leftChild = NULL;
		return { left, node };
	}

	Node* right = node->rightChild;
	if (right) right->parent = NULL;
	node->rightChild = NULL;
	return { node, right };
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Node* SplayTree<Key, Value, Comparator>::merge(Node* left, Node* right)
{
	if (!left) return right;
	if (!right) return left;

	right = find(right, left->key); // Getting min from the right tree
	right->leftChild = left;
	left->parent = right;
	return right;
}

template<class Key, class Value, class Comparator>
size_t SplayTree<Key, Value, Comparator>::size(Node* node)
{
	return (node->leftChild ? size(node->leftChild) : 0) + (node->rightChild ? size(node->rightChild) : 0) + 1;
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Iterator SplayTree<Key, Value, Comparator>::begin() const
{
	return Iterator(min(m_root));
}

template<class Key, class Value, class Comparator>
typename SplayTree<Key, Value, Comparator>::Iterator SplayTree<Key, Value, Comparator>::end() const
{
	return Iterator(NULL);
}
