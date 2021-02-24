#include <iostream>
#include "utlist.h"
#include <ctime>

template<class T> void printList(List<T> lst) {
	for (List<T>::iterator it = lst.begin(); it != lst.end(); ++it) {
		std::cout << it->data;
	}
	std::cout << std::endl;
}

template<class T> void removeLastInstance(List<T>& lst, T data) {
	Node<T>* prev = nullptr; bool first = false;
	if (lst.getFirst()->data == data) first = true;
	for (Node<int>* current = lst.getFirst(); current->next != nullptr; current = current->next) {
		if (current->next->data == data) {
			prev = current;
		}
	}
	if (prev == nullptr) {
		if (!first) {
			std::cout << "No instance of data found\n";
			return;
		}
	}
	lst.erase_after(prev);
}

int main()
{
	srand(time(NULL));
	List<int> lst;
	Node<int>* current = nullptr;
	for (int i = 0; i < 10; i++) {
		current = lst.insert_after(rand() % 5, current);
	}
	printList(lst);
	removeLastInstance(lst, 4);
	printList(lst);
}
//---------------------------------------------------------------------------
