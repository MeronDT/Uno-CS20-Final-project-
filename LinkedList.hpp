#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include "List.hpp"
#include <iostream>
using namespace std;

//Recursive implementation of LinkedList class, inheriting from the List class
//Used within Player class to contain a hand of cards

template <typename T>
class LinkedList : public List<T> {
    protected:
        struct Node {
            T value;
            Node* next;

            Node(T v = T(), Node* n = nullptr)
            : value(v), next(n) { }
        };

        // a pointer to the front of the list
        Node* head;


    private:
        //copy function into this
        void copy(const LinkedList<T>&);

        //Helper functions to make the implementation recursive
        void appendRec(Node*, Node*);
        void clearRec(Node*, Node*);
        void copyRec(Node*, Node*);
        T getElementRec(int, Node*) const;
        void insertRec(int, Node*, Node*, Node*);
		void removeRec(int, Node*, Node*);
		void replaceRec(int, Node*, const T&);

    public:
		//default constructor
		LinkedList();
		//copy constructor
		LinkedList(const LinkedList<T>&);
		//overloaded operator=
		LinkedList<T>& operator=(const LinkedList<T>&);
		//destructor
		virtual ~LinkedList();
		//add the argument to the end of the list
		virtual void append(const T&) override;
		//remove all elements in the LinkedList, resets to initial state
		virtual void clear() override;
		//returns the element at the given position
		virtual T getElement(int) const override;
		//returns the current length of the list
		virtual int getLength() const override;
		//insert the given element at the given position
		virtual void insert(int, const T&) override;
		//checks if the list currently empty
		virtual bool isEmpty() const override;
		//removes the element at the given position
		virtual void remove(int) override;
		//replace the element at the given position with value given
		virtual void replace(int, const T&) override;

};

#include "LinkedList.tpp"
#endif /* LINKEDLIST_HPP_ */
