#pragma once

template<class T> class Node {
public:
	T data;
	Node* next;
	Node(T val, Node* nxt = nullptr) {
		data = val;
		next = nxt;
	}
};

template<class T> class List {
private:
	Node<T>* first;
public:
	List() {
		first = nullptr;
	}
	List(const List& lst) : List() {
		Node<T>* current = nullptr;
		for (iterator it = lst.begin(); it != end(); ++it) {
			current = insert_after(it->data, current);
		}
	}
	~List() {
		iterator it = begin();
		while (it != end()) {
			iterator nit(it->next);
			delete* it;
			it = nit;
		}
	}
	Node<T>* getFirst() {
		return first;
	}
	T front() {
		return first->data;
	}
	bool empty() {
		return first == nullptr;
	}
	void clear() {
		iterator it = begin();
		while (it != end()) {
			iterator nit(it->next);
			delete* it;
			it = nit;
		}
		first = nullptr;
	}
	Node<T>* insert_after(T data, Node<T>* n) {
		if (n == nullptr) return push_front(data);
		Node<T>* pnn = new Node<T>(data, n->next);
		n->next = pnn;
		return pnn;
	}
	void erase_after(Node<T>* n) {
		if (n == nullptr) pop_front();
		Node<T>* rem = n->next;
		n->next = rem->next;
		delete rem;
	}
	Node<T>* push_front(T data) {
		Node<T>* pnn = new Node<T>(data, first);
		first = pnn;
		return pnn;
	}
	void pop_front() {
		Node<T>* rem = first;
		first = rem->next;
		delete rem;
	}
	class iterator {
	private:
		Node<T>* current;
	public:
		iterator() {
			current = first;
		}
		iterator(Node<T>* pnode) {
			current = pnode;
		}
		iterator(const iterator& it) {
			current = it.current;
		}
		Node<T>*& operator*() {
			return current;
		}
		Node<T>* operator->() {
			return current;
		}
		iterator operator++() {
			current = current->next;
			return current;
		}
		bool operator==(iterator it) {
			return it.current == current;
		}
		bool operator!=(iterator it) {
			return !(it == *this);
		}
	};
	iterator begin() const {
		iterator it(first);
		return it;
	}
	iterator end() const {
		iterator it(nullptr);
		return it;
	}
};