/*******************************************************************************
 *  Description:
 *      default constructor creates Deque objects
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      creates new deque object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
Deque<T>::Deque()
:length(0), header(new Node()), trailer(new Node()) { }

/*******************************************************************************
 *  Description:
 *      destructor removes anything that may cause data leaks
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
Deque<T>::~Deque()
{
	clear();
	delete header;
	header = nullptr;
	delete trailer;
	trailer = nullptr;

}

/*******************************************************************************
 *  Description:
 *      accesses the last element of the deque. Useful for easily adding objects
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
T Deque<T>::back() const{
    if(isEmpty()){
    	throw string("Error: Deque is empty");
    }
    else{
    	return trailer->value;
    }
}

/*******************************************************************************
 *  Description:
 *      accesses the first element of the deque. Useful for easily adding objects.
 *      Similar to back() function within class.
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
T Deque<T>::front() const{
    if(isEmpty()){
    	throw string("Error: Deque is empty");
    }
    else{
    	return header->value;
    }
}


/*******************************************************************************
 *  Description:
 *      function used by destructor to clear deque. removes all elements from deque
 *      and returns it to the initial state.
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(n)
*******************************************************************************/
template <typename T>
void Deque<T>::clear(){
	Node* head = header;
	Node* n = header->next;

	while(head->next != trailer){
			n = n->next;
			delete head->next;
			head->next = n;
	}

	//reset to normal
	header->next = trailer;
	header->previous = trailer;
	trailer->next = header;
	trailer->previous = header;
}

/*******************************************************************************
 *  Description:
 *      Remove element from the front of the deque. useful for easily removing elements
 *      in main.cpp
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
void Deque<T>::dequeueFront(){
    if (isEmpty()) {
        throw string("Error: Deque is empty");
    }

    Node* prev = header;
    header = header->next;
    delete prev;
    this->length--;
    header->previous = trailer;

    if(header == nullptr){
    	trailer = nullptr;
    }
}


/*******************************************************************************
 *  Description:
 *      Remove element from the back of the deque. useful for easily removing elements
 *      in main.cpp
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
void Deque<T>::dequeueBack(){
    if (isEmpty()) {
        throw string("Error: Deque is empty");
    }

    Node* prev = trailer;
    trailer = trailer->previous;
    delete prev;
    this->length--;
    trailer->next = header;

    if(header == nullptr){
    	trailer = nullptr;
    }
}

/*******************************************************************************
 *  Description:
 *      Adds element to the back of the deque
 *
 *  Input(s):
 *      const T& elem, element that will be added to back of deque
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
void Deque<T>::enqueueFront(const T& elem){
	Node* n = new Node(elem);

	if(isEmpty()){
		header = n;
		trailer = n;
	}
	else{
		header->previous = n;
		n->next = header;
		header = n;
		n->previous = trailer;
		trailer->next = n;
	}

	this->length++;
}

/*******************************************************************************
 *  Description:
 *      Adds element to the front of the deque
 *
 *  Input(s):
 *      const T& elem, element that will be added to front of deque
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
void Deque<T>::enqueueBack(const T& elem){
    Node* n = new Node(elem);

    if(isEmpty()) {
    	header = n;
    	trailer = n;
    }
    else{
    	trailer->next = n;
    	n->previous = trailer;
    	trailer = n;
    	n->next = header;
    	header->previous = n;
    }

    this->length++;
}

/*******************************************************************************
 *  Description:
 *      accesses length of deque, the amount of elements in it
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      int, containing the amount of elements in deque
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
int Deque<T>::getLength() const{
	return this->length;
}

/*******************************************************************************
 *  Description:
 *      Checks if deque is empty. If there are no elements it's empty, if there are any it is not
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      bool, true means there are no element(s) in the deque and false means there are element(s) in the deque.
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
bool Deque<T>::isEmpty() const{
	if(getLength() > 0){
		return false;
	}
	else{
		return true;
	}
}
