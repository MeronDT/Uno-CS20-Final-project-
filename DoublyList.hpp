#ifndef DOUBLYLIST_HPP_
#define DOUBLYLIST_HPP_

#include <iostream>
using namespace std;

//Doubly linked list class, in main used to hold list of Players that representated the order of turns
//also used as parent class for deque class

template <typename T>
class DoublyList {
protected:

	struct Node {
		T value;
		Node* next;
		Node* previous;

		Node(T v = T(), Node* n = nullptr)
		: value(v), next(n), previous(n) { }
	};

	////length of Deque, and header/trailer which keep track of the ends
	int length;
	Node* header;
	Node* trailer;

public:
	//default constructor
	DoublyList();
	//copy constructor
	DoublyList(const DoublyList<T>& copyObj);
	//=operator override
	DoublyList<T>& operator=(const DoublyList<T>& rightObj);
	//destructor
	virtual ~DoublyList();
	//add given argument to back of the DoublyList
	virtual void append(const T& elem);
	//removes all elements in DoublyList, resets to initial state;
	virtual void clear();
	//returns the element at the given position
	virtual T getElement(int position) const;
	//returns the length of the DoublyList
	virtual int getLength() const;
	//inserts given Node into DoublyList at given position
	virtual void insert(int position, const T& elem);
	//checks if DoublyList is empty
	virtual bool isEmpty() const;
	//removes Node at given position;
	virtual void remove(int position);
	//virtual void removeValue(const T& elem) override;
	virtual void replace(int position, const T& elem) /*override*/;
	//virtual bool search(const T& elem) const override;


private:
	//copy function
	void copy(const DoublyList<T>& copyObj);
};

#include "DoublyList.tpp"
#endif /* DOUBLYLIST_HPP_ */
