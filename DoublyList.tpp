/*******************************************************************************
 *  Description:
 *      default constructor creates DoublyList objects
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      creates new DoublyList object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
DoublyList<T>::DoublyList()
: header(new Node()), trailer(new Node())
{
	//sets header points to trailer and vice versa
	header->next = trailer;
	trailer->previous = header;
	this->length = 0;
}

/*******************************************************************************
 *  Description:
 *      copy constructor, creates new DoublyList object by copying another one
 *
 *  Input(s):
 *      const DoublyList<T>& copyObj)
 *
 *  Output:
 *      creates new DoublyList object
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node()), trailer(new Node())
{
	//calls copy function
	copy(copyObj);
}

/*******************************************************************************
 *  Description:
 *		=operator override function, allows = to be used better with DoublyLists
 *
 *  Input(s):
 *      const DoublyList<T>& rightObj, object that another object of DoublyList
 *      copies the values of
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj){
	//run clear function then copy function
	if(this != &rightObj){
		clear();
		copy(rightObj);
	}
	return *this;
}

/*******************************************************************************
 *  Description:
 *		destructor, deleted values that could cause memory leaks
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
DoublyList<T>::~DoublyList(){
	//calls clear function, leaves header & trailer
	clear();
	delete header;
	delete trailer;
	header = nullptr;
	trailer = nullptr;
}

/*******************************************************************************
 *  Description:
 *		adds object to back of DoublyList
 *
 *  Input(s):
 *      const T& elem, element that will be added to end of DoublyList
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void DoublyList<T>::append(const T& elem){
	Node* n = new Node(elem);

	//check if header links to trailer and trailer links to header (empty list)
	if(header->next == trailer && trailer->previous == header){
		header->next = n;
		n->previous = header;
		n->next = trailer;
		trailer->previous = n;
	}
	else{
		Node* m = trailer->previous;

		n->previous = m;
		n->next = trailer;
		trailer->previous = n;
		m->next = n;
	}

	this->length++;
}

/*******************************************************************************
 *  Description:
 *		function used in destructor and other functions, removes all values in the DoublyList
 *		and resets it to the initial state.
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
void DoublyList<T>::clear(){
	Node* head = header;
	Node* n = header->next;
	//until its just header and trailer
	while(head->next != trailer){
		n = n->next;
		delete head->next;
		head->next = n;
	}

	//setting header->next might be unnecessary (already done in loop)
	header->next = trailer;
	trailer->previous = header;
	header->previous = nullptr;
	trailer->next = nullptr;

	this->length = 0;
}

/*******************************************************************************
 *  Description:
 *		copy function, copied values of one DoublyList to another;
 *
 *  Input(s):
 *      const DoublyList<T>& copyObj, object that will be copied off of.
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj){
	this->length = copyObj->length;

	if(this->length > 0){
		Node* n = new Node(header->next);
		Node* copyN = new Node(copyObj->header->next);

		while(copyN->next != trailer){
			n->value = copyN->value;
			n->previous = copyN->previous;
			n->next = copyN->next;
			n = n->next;
			copyN = copyN->next;
		}

		//copy last element before trailer because while stops right before trailer
		n->value = copyN->value;
		n->previous = copyN->previous;
		n->next = copyN->next;
		n->next = trailer;
		trailer->previous = n;
	}
	//when empty just connect header and trailer
	else{
		header->next = trailer;
		trailer->previous = header;
		header->previous = nullptr;
		trailer->next = nullptr;
	}

}

/*******************************************************************************
 *  Description:
 *		accesses element at a given position. Allows for easy usage of things inside
 *		the DoublyList
 *
 *  Input(s):
 *      int position, given position of element in DoublyList that will be returned;
 *
 *  Output:
 *      T, element that is at the given position in the DoublyList
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
T DoublyList<T>::getElement(int position) const{
	if (position < 0 || position >= this->length) {
		throw string("getElement: error, position out of bounds");
	}

	Node* n = nullptr;

	if(position <= (this->length)/2){
		n = header->next;
		for(int i = 0; i < position; i++){
			n = n->next;
		}
	}
	else if(position > (this->length)/2){
		n = trailer->previous;
		for(int i = this->length - 1; i > position; i--){
			n = n->previous;
		}
	}

	return n->value;
}
/*******************************************************************************
 *  Description:
 *		returns the length of the DoublyList, or number of elements inside it.
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      int, length of DoublyList, which is number of elements inside of it.
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
int DoublyList<T>::getLength() const{
	return this->length;
}

template <typename T>
void DoublyList<T>::insert(int position, const T& elem){
	if (position < 0 || position >= this->length) {
		throw string("insert: error, position out of bounds");
	}

	Node* n = new Node(elem);
	Node* beforeNode = nullptr;
	Node* afterNode = nullptr;

	if(position <= (this->length)/2){
		beforeNode = header->next;
		afterNode = header->next;
		for(int i = 0; i < position - 1; i++){
			beforeNode = beforeNode->next;
			afterNode = afterNode->next;
		}
		//adjust node to be after target position
		afterNode = afterNode->next;
	}
	else if(position > (this->length)/2){
		beforeNode = trailer->previous;
		afterNode = trailer->previous;
		for(int i = this->length -1 ; i > position; i--){
			beforeNode = beforeNode->previous;
			afterNode = afterNode->previous;
		}
		//adjust node to be after target position
		beforeNode = beforeNode->previous;
	}

	//connect new node to surrounding nodes, previous node at position is after node
	beforeNode->next = n;
	n->previous = beforeNode;
	n->next = afterNode;
	afterNode->previous = n;

	this->length++;
}

/*******************************************************************************
 *  Description:
 *		checks if DoublyList is empty by looking at if there are any element(s) inside it
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      bool, tells whether DoublyList is empty or not.
 *      true ,means it is empty and there are no elements inside it
 *      false, means it is not empty and there are ekement(s) inside it.
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
bool DoublyList<T>::isEmpty() const{
	if(this->length == 0){
		return true;
	}
	else{
		return false;
	}
}

/*******************************************************************************
 *  Description:
 *		removes element from DoublyList at given position
 *
 *  Input(s):
 *      int position, given position of element that will be removed
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void DoublyList<T>::remove(int position){
	if (position < 0 || position >= this->length) {
		throw string("remove: error, position out of bounds");
	}

	Node* n = nullptr;

	if(position <= (this->length)/2){
		n = header->next;
		for(int i = 0; i < position; i++){
			n = n->next;
		}
	}
	else if(position > (this->length)/2){
		n = trailer->previous;
		for(int i = this->length - 1; i > position; i--){
			n = n->previous;
		}
	}

	//might not be enough linking after?
	Node* post = n->next;
	Node* pre = n->previous;
	post->previous = pre;
	pre->next = post;


	delete n;
	this->length--;
}

/*******************************************************************************
 *  Description:
 *		replaces element at given position, with new element of given value.
 *
 *  Input(s):
 *      int position, the position in the DoublyList that the element will be removed from
 *      const T& elem, given element to replace the old element
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
template <typename T>
void DoublyList<T>::replace(int position, const T& elem){
	if (position < 0 || position >= this->length) {
		throw string("replace: error, position out of bounds");
	}

	Node* n = nullptr;

	if(position <= (this->length)/2){
		n = header->next;
		for(int i = 0; i < position; i++){
			n = n->next;
		}
	}
	else if(position > (this->length)/2){
		n = trailer->previous;
		for(int i = this->length - 1; i > position; i--){
			n = n->previous;
		}
	}

	n->value = elem;
}
