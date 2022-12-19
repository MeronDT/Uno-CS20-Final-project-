/*******************************************************************************
 *  Description:
 *      default constructor creates LinkedList objects
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      creates new LinkedList object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
LinkedList<T>::LinkedList()
: head(nullptr) { }

/*******************************************************************************
 *  Description:
 *      copy constructor, creates a new LinkedList by copying another one
 *
 *  Input(s):
 *      const LinkedList<T>& copyObj, LinkedList that is being copied by the new
 *      LinkedList.
 *
 *  Output:
 *      creates new LinkedList object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyObj) {
	copy(copyObj);
}

/*******************************************************************************
 *  Description:
 *      operator= overload, allows for LinkedLists to use = operator better
 *
 *  Input(s):
 *      const LinkedList<T>& rightObj, object that will have it's values copied by
 *      another LinkedList
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

/*******************************************************************************
 *  Description:
 *      destructor deletes all things that may cause memory leak
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
}

/*******************************************************************************
 *  Description:
 *      adds new given element to the end of the LinkedList
 *
 *  Input(s):
 *      const T& elem, given element that will be added to end of LinkedList
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void LinkedList<T>::append(const T& elem){
	 Node* n = new Node(elem);
	 appendRec(n, head);
	 this->length++;
}

template <typename T>
void LinkedList<T>::appendRec(Node* n, Node* curr){
	//base case empty list
	if (head == nullptr){
		head = n;
	}

	//base case end of list
	else if (curr->next == nullptr){
		curr->next = n;
	}

	//recursive case
	else {
		appendRec(n, curr->next);
	}

}

/*******************************************************************************
 *  Description:
 *     	deletes all the elements within the LinkedList and resets it to the initial state
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void LinkedList<T>::clear(){
	Node* prev = nullptr;
	clearRec(prev, head);

	head = nullptr;
}
template <typename T>
void LinkedList<T>::clearRec(Node* prev, Node* head){
	//base case empty list
	if(head == nullptr){
		delete prev;
		this->length = 0;
	}

	//recursive case
	else {
		delete prev;
		clearRec(head, head->next);
	}
}

/*******************************************************************************
 *  Description:
 *      copy function used in copy constructor, copies values from given LinkedList
 *      into another LinkedList
 *
 *  Input(s):
 *      const LinkedList<T>& copyObj, given LinkedList which is copied from
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& copyObj){
	this->length = copyObj.length;
	head = nullptr;

	if(this->length > 0){
		head = new Node(copyObj.head->value);
		copyRec(head, copyObj.head->next);
	}
}
template <typename T>
void LinkedList<T>::copyRec(Node* myCurr, Node* copyCurr){
	//base case
	if(copyCurr == nullptr){
		return;
	}

	//recursive case
	else{
		Node* n = new Node(copyCurr->value);
		myCurr->next = n;
		copyRec(n, copyCurr->next);
	}
}

/*******************************************************************************
 *  Description:
 *      accesses element from given position in LinkedList
 *
 *  Input(s):
 *      int position, the given position of the target element which is returned
 *
 *  Output:
 *      T, element at given position in LinkedList;
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
T LinkedList<T>::getElement(int position) const{
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }
    return getElementRec(position, head);
}
template <typename T>
T LinkedList<T>::getElementRec(int num, Node* curr) const{
    // base case
    if (num == 0){
        return curr->value;
    }

    //recursive case
    else {
    	return getElementRec(num - 1, curr->next);
    }

}

/*******************************************************************************
 *  Description:
 *      returns the length, the amount of elements in the LinkedList
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      int, length of LinkedList, based on how many elements are inside it
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
int LinkedList<T>::getLength() const{
	return this->length;
}

/*******************************************************************************
 *  Description:
 *      placing element into the given position, without removing or placcing other
 *      elements in the LinkedList
 *
 *  Input(s):
 *      int position, given position that the new element will be placed at
 *      const T& elem, given element to be inserted at the given position
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void LinkedList<T>::insert(int position, const T& elem){
	if (position < 0 || position >= this->length) {
		throw string("insert: error, position out of bounds");
	}

	Node* n    = new Node(elem);
	Node* prev = nullptr;

	insertRec(position, n, prev, head);
	this->length++;
}
template <typename T>
void LinkedList<T>::insertRec(int num, Node* n, Node* prev, Node* curr){
	//base case empty list
	if(num == 0 && prev == nullptr){
		head = n;
	    n->next = curr;
	}

	//base case reached position
	else if(num == 0){
		prev->next = n;
		n->next = curr;
	}

	//recursive case
	else{
		insertRec(num - 1, n, curr, curr->next);
	}
}

/*******************************************************************************
 *  Description:
 *      checks if LinkedList is empty by seeing if elements are inside it
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      bool, true means it is empty no elements in inside, & false means it is not empty
 *      and there are element(s) inside;
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
bool LinkedList<T>::isEmpty() const{
	return this->length == 0;
}

/*******************************************************************************
 *  Description:
 *      remove element at given position inside LinkedList
 *
 *  Input(s):
 *      int position, the given position of element to be removed
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void LinkedList<T>::remove(int position){
	if (position < 0 || position >= this->length) {
		throw string("remove: error, position out of bounds");
	}

	Node* prev = nullptr;

	removeRec(position, prev, head);
	this->length--;
}
template <typename T>
void LinkedList<T>::removeRec(int num, Node* prev, Node* curr){
	//comprehensive base case
	if(num == 0){
		if(head->next == nullptr){
			delete head;
			head = nullptr;
		}
		else if(curr == head){
			head = head->next;
			delete curr;
		}
		else{
			prev->next = curr->next;
			delete curr;
		}
	}

	//recursive case
	else{
		removeRec(num - 1, curr, curr->next);
	}
}

/*******************************************************************************
 *  Description:
 *      Takes element at given position in LinkedList and replaces it with given value
 *
 *  Input(s):
 *      int position, given position in LinkedList where exchange happens
 *      const T& value, value that will be placed in that position
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void LinkedList<T>::replace(int position, const T& value){
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }

    replaceRec(position, head, value);
}
template <typename T>
void LinkedList<T>::replaceRec(int position, Node* curr, const T& value){
    // base case
    if (position == 0){
    	curr->value = value;
    }

    // Recursive case
    replaceRec(position - 1, curr->next, value);

}

