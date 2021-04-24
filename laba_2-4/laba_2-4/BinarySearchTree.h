#pragma once

#include <functional>
#include <vector>
#include <iostream>
#include <list>
#include <iterator>

template <class Value, class Comparator = std::less<Value>>
class BinarySearchTree
{
private:
	struct Node;
public:
	using value_type = Value;

	struct Iterator;

	BinarySearchTree();
	template <class Iter>
	BinarySearchTree(const Iter& begin, const Iter& end);
	BinarySearchTree(const std::initializer_list<Value>& lst);
	BinarySearchTree(const BinarySearchTree& tree) : BinarySearchTree(tree.m_root) {}
	~BinarySearchTree();

	Iterator find(const Value& value) const;
	bool has(const Value& value) const;
	void insert(const Value& value);
	void erase(const Value& value);

	size_t size() const;
	void print() const;
	uint8_t height() const;
	
	std::vector<Value> findInRange(const Value& min, const Value& max) const;
	void eraseRange(const Value& min, const Value& max);
	std::pair<BinarySearchTree, BinarySearchTree> split(const Value& value) const;

	template <class Iter>
	static Node* fromSortedRecursive(Iter& head, int length);
	template <class Iter>
	static BinarySearchTree fromSorted(const Iter& begin, const Iter& end);
	static BinarySearchTree merge(const BinarySearchTree& left, const BinarySearchTree& right);

	void clear();

private:
	struct Node {
		value_type value;
		Node* parent;
		Node* leftChild;
		Node* rightChild;

		Node(const Value& avalue, Node* aparent = NULL, Node* aleftChild = NULL, Node* arightChild = NULL);
		Node(const Node& anode);

		Node* min() const;
		Node* max() const;

		Node* prev() const;
		Node* next() const;

		void rotateR();
		void rotateL();

		void balance();

		void setHeight();
		uint8_t height() const;
		int8_t bfactor() const;

		size_t size() const;

		void findInRange(const Value& min, const Value& max, std::vector<Value>& found) const;

		void erase();

		void clear();

	private:
		uint8_t _height;
	};

	BinarySearchTree(const Node* root);

	Node* m_root = NULL;
	size_t m_size = 0;

public:
	struct Iterator {
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = Value;
		using reference = Value&;
		using pointer = Node*;
		using difference_type = ptrdiff_t;

		pointer ptr = NULL;

		Iterator(pointer p = NULL) : ptr(p) {}
		Iterator(const Iterator& it) : ptr(it.ptr) {}

		reference operator* () { 
			return ptr->value;
		}
		
		Iterator& operator++ () { 
			ptr = ptr->next();
			return *this;
		}

		Iterator& operator-- () {
			ptr = ptr->prev();
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

template<class Value, class Comparator>
BinarySearchTree<Value, Comparator>::Node::Node(
	const Value& avalue,
	BinarySearchTree<Value, Comparator>::Node* aparent,
	BinarySearchTree<Value, Comparator>::Node* aleftChild, 
	BinarySearchTree<Value, Comparator>::Node* arightChild
)
{
	value = avalue;
	parent = aparent;
	leftChild = aleftChild;
	rightChild = arightChild;

	_height = 1;
}

template<class Value, class Comparator>
BinarySearchTree<Value, Comparator>::Node::Node(const Node& anode)
{
	value = anode.value;
	parent = NULL;

	if (anode.leftChild) {
		leftChild = new Node(*anode.leftChild);
		leftChild->parent = this;
	}
	else {
		leftChild = NULL;
	}

	if (anode.rightChild) {
		rightChild = new Node(*anode.rightChild);
		rightChild->parent = this;
	}
	else {
		rightChild = NULL;
	}

	_height = anode._height;
}

template<class Value, class Comparator>
BinarySearchTree<Value, Comparator>::BinarySearchTree()
{
	m_root = NULL;
	m_size = 0;
}

template<class Value, class Comparator>
BinarySearchTree<Value, Comparator>::BinarySearchTree(const std::initializer_list<Value>& lst)
{
	m_root = 0;
	m_size = 0;

	for (const Value& val : lst) {
		insert(val);
	}
}

template<class Value, class Comparator>
BinarySearchTree<Value, Comparator>::BinarySearchTree(const BinarySearchTree<Value, Comparator>::Node* root)
{
	if (root) {
		m_root = new Node(*root);
		m_size = m_root->size();
	}
	else {
		m_root = NULL;
		m_size = 0;
	}
}

template<class Value, class Comparator>
BinarySearchTree<Value, Comparator>::~BinarySearchTree()
{
	clear();
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator>::Iterator 
BinarySearchTree<Value, Comparator>::find(const Value& value) const
{
	for (
		Node* current = m_root;
		current != NULL;
		current = Comparator()(current->value, value) ? current->rightChild : current->leftChild
	) {
		if (current->value == value) return Iterator(current);
	}

	return end();
}

template<class Value, class Comparator>
bool BinarySearchTree<Value, Comparator>::has(const Value& value) const
{
	return find(value) != end();
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::insert(const Value& value)
{

	Node* prev = NULL;
	Node* current = m_root;

	if (!current) {
		m_root = new Node(value);
		m_size++;
		return;
	}

	for (
		;
		current != NULL;
		prev = current,
		current = Comparator()(current->value, value) ? current->rightChild : current->leftChild
	) {
		if (current->value == value) return;
	}

	m_size++;

	if (Comparator()(prev->value, value)) {
		prev->rightChild = new Node(value);
		prev->rightChild->parent = prev;
	}
	else {
		prev->leftChild = new Node(value);
		prev->leftChild->parent = prev;
	}

	prev->balance();

	if (m_root && m_root->parent) {
		m_root = m_root->parent;
	}
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::erase(const Value& value)
{
	Node* current = m_root;

	for (
		;
		!(current == NULL || current->value == value);
		current = Comparator()(current->value, value) ? current->rightChild : current->leftChild
	) { }

	if (!(current && current->value == value)) return;
	
	current->erase();
	if (!--m_size) m_root = NULL;
	if (m_root && m_root->parent) {
		m_root = m_root->parent;
	}
}

template<class Value, class Comparator>
size_t BinarySearchTree<Value, Comparator>::size() const
{
	return m_size;
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::print() const
{
	if (!m_root) {
		std::cout << "Binary search tree is empty";
	}

	for (const Value& el : *this) {
		std::cout << el << " ";
	}

	std::cout << std::endl;
}

template<class Value, class Comparator>
uint8_t BinarySearchTree<Value, Comparator>::height() const
{
	return m_root ? m_root->height() : 0;
}

template<class Value, class Comparator>
std::vector<Value> BinarySearchTree<Value, Comparator>::findInRange(const Value& min, const Value& max) const
{
	std::vector<Value> vec;
	if (!Comparator()(max, min) && m_root) m_root->findInRange(min, max, vec);
	return vec;
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::eraseRange(const Value& min, const Value& max)
{
	for (const Value& el : findInRange(min, max)) {
		erase(el);
	}
}

template<class Value, class Comparator>
std::pair< BinarySearchTree<Value, Comparator>, BinarySearchTree<Value, Comparator>> 
BinarySearchTree<Value, Comparator>::split(const Value& value) const
{
	for (
		Node* current = m_root;
		current != NULL;
		current = Comparator()(current->value, value) ? current->rightChild : current->leftChild
		) {
		if (current->value != value) continue;

		return { fromSorted(begin(), Iterator(current)), fromSorted(Iterator(current), end()) };
	}

	return { BinarySearchTree(), BinarySearchTree() };
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator> 
BinarySearchTree<Value, Comparator>::merge(const BinarySearchTree& left, const BinarySearchTree& right)
{
	std::list<Value> mergedList;
	
	auto lit = left.begin();
	auto rit = right.begin();

	while (lit != left.end() && rit != right.end()) {
		if (Comparator()(*lit, *rit)) {
			mergedList.push_back(*lit);
			++lit;
		}
		else {
			mergedList.push_back(*rit);
			++rit;
		}
	}

	if (lit != left.end()) {
		do {
			mergedList.push_back(*lit);
			++lit;
		} while (lit != left.end());
	}
	else {
		do {
			mergedList.push_back(*rit);
			++rit;
		} while (rit != right.end());
	}

	return fromSorted(mergedList.begin(), mergedList.end());
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::clear()
{
	if (!m_root) return;
	m_root->clear();
	m_root = NULL;
	m_size = 0;
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator>::Iterator BinarySearchTree<Value, Comparator>::begin() const
{
	return Iterator(m_root ? m_root->min() : NULL);
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator>::Iterator BinarySearchTree<Value, Comparator>::end() const
{
	return Iterator(NULL);
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator>::Node* 
BinarySearchTree<Value, Comparator>::Node::min() const
{
	if (!leftChild) return const_cast<Node*>(this);
	return leftChild->min();
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator>::Node*
BinarySearchTree<Value, Comparator>::Node::max() const
{
	if (!rightChild) return const_cast<Node*>(this);
	return rightChild->max();
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator>::Node*
BinarySearchTree<Value, Comparator>::Node::prev() const
{
	if (leftChild) return leftChild->max();

	Node* p = parent;
	for (
		Value current = value;
		p != NULL && p->leftChild && p->leftChild->value == current;
		current = p->value, p = p->parent
	) { }

	return p;
}

template<class Value, class Comparator>
typename BinarySearchTree<Value, Comparator>::Node*
BinarySearchTree<Value, Comparator>::Node::next() const
{
	if (rightChild) return rightChild->min();

	Node* p = parent;
	for (
		Value current = value;
		p != NULL && p->rightChild && p->rightChild->value == current;
		current = p->value, p = p->parent
	) { }

	return p;
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::Node::rotateR()
{
	Node* left = leftChild;
	leftChild = left->rightChild;
	if (leftChild) leftChild->parent = this;
	left->rightChild = this;

	if (parent) {
		if (parent->rightChild == this) {
			parent->rightChild = left;
		}
		else {
			parent->leftChild = left;
		}
	}
	left->parent = parent;
	parent = left;
	
	setHeight();
	left->setHeight();
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::Node::rotateL()
{
	Node* right = rightChild;
	rightChild = right->leftChild;
	if (rightChild) rightChild->parent = this;
	right->leftChild = this;

	if (parent) {
		if (parent->rightChild == this) {
			parent->rightChild = right;
		}
		else {
			parent->leftChild = right;
		}
	}
	right->parent = parent;
	parent = right;

	setHeight();
	right->setHeight();
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::Node::balance()
{
	setHeight();
	
	if (bfactor() == 2) {
		if (leftChild->bfactor() < 0) {
			leftChild->rotateL();
		}

		rotateR();

		return;
	}

	if (bfactor() == -2) {
		if (rightChild->bfactor() > 0) {
			rightChild->rotateR();
		}

		rotateL();

		return;
	}

	if (parent) parent->balance();
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::Node::setHeight()
{
	uint8_t leftHeight = 0;
	uint8_t rightHeigth = 0;

	if (leftChild) {
		leftHeight = leftChild->height();
	}

	if (rightChild) {
		rightHeigth = rightChild->height();
	}

	_height = (leftHeight < rightHeigth ? rightHeigth : leftHeight) + 1;
}

template<class Value, class Comparator>
uint8_t BinarySearchTree<Value, Comparator>::Node::height() const
{
	return _height;
}

template<class Value, class Comparator>
inline int8_t BinarySearchTree<Value, Comparator>::Node::bfactor() const
{
	return static_cast<int8_t>(leftChild ? leftChild->height() : 0) - (rightChild ? rightChild->height() : 0);
}

template<class Value, class Comparator>
inline size_t BinarySearchTree<Value, Comparator>::Node::size() const
{
	size_t s = 1;
	if (leftChild) s += leftChild->size();
	if (rightChild) s += rightChild->size();

	return s;
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::Node::findInRange(const Value& min, const Value& max, std::vector<Value>& found) const
{
	if (Comparator()(value, min)) {
		if (rightChild) rightChild->findInRange(min, max, found);
		return;
	}
	if (Comparator()(max, value)) {
		if (leftChild) leftChild->findInRange(min, max, found);
		return;
	}

	found.push_back(value);

	if (leftChild) leftChild->findInRange(min, max, found);
	if (rightChild) rightChild->findInRange(min, max, found);
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::Node::erase()
{
	if (!(leftChild || rightChild)) {
		if (parent) {
			if (parent->leftChild == this) {
				parent->leftChild = NULL;
			}
			else {
				parent->rightChild = NULL;
			}

			parent->balance();
		}

		delete this;
		return;
	}

	if (leftChild && rightChild) {
		if (bfactor() > 0) {
			Node* predecessor = prev();
			value = predecessor->value;

			predecessor->erase();
			return;
		}

		Node* successor = next();
		value = successor->value;

		successor->erase();
		return;
	}

	if (leftChild) {
		if (parent) {
			leftChild->parent = parent;
			if (parent->leftChild == this) {
				parent->leftChild = leftChild;
			}
			else {
				parent->rightChild = leftChild;
			}

			parent->balance();

			delete this;
			return;
		}

		// Workaround to not change the m_root
		Node* predecessor = prev();
		value = predecessor->value;

		predecessor->erase();
		return;
	}
	
	if (parent) {
		rightChild->parent = parent;
		if (parent->leftChild == this) {
			parent->leftChild = rightChild;
		}
		else {
			parent->rightChild = rightChild;
		}

		parent->balance();

		delete this;
		return;
	}

	Node* successor = next();
	value = successor->value;

	successor->erase();
	return;
}

template<class Value, class Comparator>
void BinarySearchTree<Value, Comparator>::Node::clear()
{
	if (leftChild) leftChild->clear();
	if (rightChild) rightChild->clear();

	delete this;
}

template<class Value, class Comparator>
template<class Iter>
BinarySearchTree<Value, Comparator>::BinarySearchTree(const Iter& begin, const Iter& end)
{
	m_size = 0;
	m_root = NULL;

	for (Iter it = begin; it != end; ++it) {
		insert(*it);
	}
}

template<class Value, class Comparator>
template<class Iter>
typename BinarySearchTree<Value, Comparator>::Node* BinarySearchTree<Value, Comparator>::fromSortedRecursive(Iter& head, int length)
{
	if (length <= 0) return NULL;

	Node* left = fromSortedRecursive(head, length / 2);

	Node* root = new Node(*head);
	root->leftChild = left;

	if (root->leftChild) root->leftChild->parent = root;

	++head;

	root->rightChild = fromSortedRecursive(head, length - length / 2 - 1);
	if (root->rightChild) root->rightChild->parent = root;

	root->setHeight();

	return root;
}

template<class Value, class Comparator>
template<class Iter>
typename BinarySearchTree<Value, Comparator> BinarySearchTree<Value, Comparator>::fromSorted(const Iter& begin, const Iter& end)
{
	Iter it = begin;
	return BinarySearchTree(fromSortedRecursive(it, std::distance(begin, end)));
}
