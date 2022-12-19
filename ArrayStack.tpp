/*******************************************************************************
 *  Description:
 *      creates ArrayStack object
 *
 *  Input(s):
 *      int i, maximum size of buffer inside ArrayStack
 *
 *  Output:
 *      creates new ArrayStack object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
ArrayStack<T>::ArrayStack(int i)
: buffer(new T[i]), maxSize(i) { }

/*******************************************************************************
 *  Description:
 *      creates Arraystack through copying another Arraystack
 *
 *  Input(s):
 *      ArrayStack<T>& copyObj, the Arraystack that is going to be copied
 *
 *  Output:
 *      creates new ArrayStack object
 *
 *  Asymptotic Analysis:
 *  O(n)
*******************************************************************************/
template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& copyObj) {
    copy(copyObj);
}

/*******************************************************************************
 *  Description:
 *      = operator overload, changes the meaning of the = operator to work when used
 *      with Arraystacks
 *
 *  Input(s):
 *      ArrayStack<T>& rightObj, the Arraystack that will be used to copy from
 *
 *  Output:
 *      creates new ArrayStack object
 *
 *  Asymptotic Analysis:
 *  O(n)
*******************************************************************************/
template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

/*******************************************************************************
 *  Description:
 *      destructor, gets rid of any dyanimc memory that may cause memory leaks
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
ArrayStack<T>::~ArrayStack() {
    clear();
}

/*******************************************************************************
 *  Description:
 *      function that will be used in destructor, gets rid of dynamic memory to prevent
 *      any possibly memory leaks
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
void ArrayStack<T>::clear() {
    delete[] buffer;
    buffer       = nullptr;
    this->length = 0;
}

/*******************************************************************************
 *  Description:
 *      copy function that will be used in the copy constructor, copies values from
 *      inputed ArrayStack into a different ArrayStack
 *
 *  Input(s):
 *      const ArrayStack<T>& copyObj, Arraystack that will be copied from
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(n)
*******************************************************************************/
template <typename T>
void ArrayStack<T>::copy(const ArrayStack<T>& copyObj) {
    this->length = copyObj.length;
    maxSize      = copyObj.maxSize;
    buffer       = new T[maxSize];

    for (int i = 0; i < copyObj.length; i++) {
        buffer[i] = copyObj.buffer[i];
    }
}

/*******************************************************************************
 *  Description:
 *      function that returns the length of ArrayStack, used a lot in loops with
 *      Arraystacks
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      int of the amount of objects in the Arraystack
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
int ArrayStack<T>::getLength() const {
    return this->length;
}

/*******************************************************************************
 *  Description:
 *      function that returns the max size of the buffer, useful in knowing how
 *      full the buffer is
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      int of the max amount of objects that can go into the Arraystack
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
int ArrayStack<T>::getMaxSize() const {
    return maxSize;
}

/*******************************************************************************
 *  Description:
 *      function checks if Arraystack has any objects in it
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      bool saying whether there are object(s) inside the Arraystack.
 *      true means there are no object(s), and false means there are object(s)
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
bool ArrayStack<T>::isEmpty() const {
    return this->length == 0;
}

/*******************************************************************************
 *  Description:
 *      function that checks if buffer has reached the max amount of objects possible
 *      inside of it
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      bool saying whether the buffer has reached it's max or not.
 *      true means it has reached the max, false means it has not reached the max
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
bool ArrayStack<T>::isFull() const {
    return this->length == maxSize;
}
/*******************************************************************************
 *  Description:
 *      Accesses the object at the top of the Arraystack, useful for changing that
 *      object
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      the object which is at the top of the Arraystack.
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
T ArrayStack<T>::peek() const {
    if (isEmpty()) {
        throw string("peek: error, stack is empty, cannot access the top");
    }

    return buffer[this->length - 1];
}

/*******************************************************************************
 *  Description:
 *      function that removes the top object of the Arraystack, replaces it if it is not
 *      empty.
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
void ArrayStack<T>::pop() {
    if (isEmpty()) {
        throw string("pop: error, stack is empty, avoiding underflow");
    }

    this->length--;
}

/*******************************************************************************
 *  Description:
 *      adds object to the top of Arraystack. useful for adding new instances to the stack.
 *
 *  Input(s):
 *      const T& elem, the object that is being added to the Arraystack.
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
template <typename T>
void ArrayStack<T>::push(const T& elem) {
    if (isFull()) {
        throw string("push: error, stack is full, avoiding overflow");
    }

    if (buffer == nullptr) {
        buffer = new T[maxSize];
    }

    buffer[this->length++] = elem;
}
