#ifndef DEQUE_HPP_
#define DEQUE_HPP_

#include "DoublyList.hpp"
#include <iostream>
using namespace std;

//Doubly Linked List based circular queue, called a deque, like was discussed in lecture.
//Circular and has Nodes that link both ways
//Used to represent the gameDeck in main.cpp (Similar names may have been part of the reasoning why)

template <typename T>
class Deque: public DoublyList<T>{
private:
	struct Node {
		T value;
		Node* next;
		Node* previous;

		Node(T v = T(), Node* n = nullptr)
		: value(v), next(n), previous(n) { }
	};

	//length of Deque, and header/trailer which keep track of the ends
	int length;
	Node* header;
	Node* trailer;

public:
	//default constructor
	Deque();
	//destructor
	virtual ~Deque();
    //return the element at the back of the deque
    T back() const;
    //return the element at the front of the deque
    T front() const;
    //remove all elements in the deque, reseting to initial state
    void clear();
    //remove the front element from the deque
    void dequeueFront();
    //remove the back element from the deque
    void dequeueBack();
    //add the argument to the back of the deque
    void enqueueFront(const T&);
    //add the argument to the back of the deque
    void enqueueBack(const T&);
    //return the current length of the queue
    int getLength() const;
    //checks if the queue currently empty
    bool isEmpty() const;

};

#include "Deque.tpp"
#endif /* DEQUE_HPP_ */
