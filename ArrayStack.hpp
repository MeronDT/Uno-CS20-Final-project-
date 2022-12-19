#ifndef ARRAY_STACK_HPP
#define ARRAY_STACK_HPP

#include "Stack.hpp"
#include <iostream>
using namespace std;

//Array based Stack class used to Represent Card pile in main.cpp


template <typename T>
class ArrayStack : public Stack<T> {
    private:
        //array containing the elements
        T* buffer;
        //max number of elements in buffer
        int maxSize;
        //copy the state of the argument stack to `this`
        void copy(const ArrayStack<T>&);

    public:
        //constructor with the maximum size as the argument
        ArrayStack(int i = 108);
        //copy constructor
        ArrayStack(const ArrayStack<T>&);
        //overloaded assignment operator for =
        ArrayStack<T>& operator=(const ArrayStack<T>&);
        //destructor
        virtual ~ArrayStack();
        //removes all elements in stack, resets to default
        virtual void clear() override;
        //returns length of stack
        virtual int getLength() const override;
        //returns the maximum size of the stack
        int getMaxSize() const;
        //checks if stack is empty
        virtual bool isEmpty() const override;
        //determine if the stack is currently full
        bool isFull() const;
        //returns the element at the top of the stack
        virtual T peek() const override;
        //removes the top element from the stack
        virtual void pop() override;
        //adds the argument to the top of the stack
        virtual void push(const T&) override;
};

#include "ArrayStack.tpp"
#endif
