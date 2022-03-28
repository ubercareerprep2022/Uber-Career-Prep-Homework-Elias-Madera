#include <bits/stdc++.h>
using namespace std;

    // both implementations make use of 'template', to allow the use of generic types in the structures.

template <typename dataType> struct myQueue{

    /*

    Queue class from scratch (does not use the language’s standard stack or queue library/package methods).

    This implementation allows any data type, not just integers, but the data type must be specified when
    declaring the queue.

    This implementation uses C++ vectors, because they provide a simple dynamic size container, so we give up memory and
    reallocation time in exchange of fast element access and size handling.

    It has the following functions:

    enqueue(data) : enqueues that value at the back of the queue : does not return anything 
    Time complexity: O(1)

    dequeue() : removes the value at the front of the queue : if there was a value to be removed, returns that value, if not,
    an error message is shown to the user
    Time complexity: O(1)

    rear() : if there is at least one value in the queue, returns the value at the rear of the queue, if not, an error message is shown
    to the user
    Time complexity: O(1)

    front() : if there is at least one value in the queue, returns the value at the front of the queue, if not, an error message is shown
    to the user
    Time complexity: O(1)

    isEmpty() : checks if queue is empty, if it is returns true, else returns false (1 and 0 in C++)
    Time complexity: O(1)

    size() : returns the size of the queue
    Time complexity: O(1)

    */

    int currentPointer = 0; // value that works as a pointer to dequeue items in the queue
    vector<dataType> dataVector; // vector to store our data
    
    void enqueue(dataType data){

        dataVector.push_back(data);

    }

    // since removing or erasing items in a vector is expensive in time, I went with the option of having a value that stores
    // the current element that is still in the queue, when an item is removed from the queue, the pointer moves to the right
    // in the vector. This means the value is still stored and the memory is allocated for it, but we have a constant time when dequeueing items.

    dataType dequeue(){

        dataType dequeuedItem;

        if(dataVector.size()-currentPointer == 0){
            cout<<"dequeue error: queue is empty"<<endl;
        }else{
            dequeuedItem = dataVector[currentPointer++];
        }

        return dequeuedItem;      

    }
    dataType rear(){

        dataType rearValue;

        if(dataVector.size()-currentPointer){
            rearValue = dataVector.back();
        }else{
            cout<<"rear error: queue is empty"<<endl;
        }

        return rearValue;

    }
    dataType front(){

        dataType frontValue;

        if(dataVector.size()-currentPointer){
            frontValue = dataVector[currentPointer];
        }else{
            cout<<"front error: queue is empty";
        }

        return frontValue;

    }
    int size(){

        int queueSize = 0;

        queueSize = dataVector.size()-currentPointer;

        return queueSize;

    }
    bool isEmpty(){

        bool queueEmpty = true;

        if(dataVector.size()-currentPointer){
            queueEmpty = false;
        }

        return queueEmpty;

    }

    

};
template <typename dataType> struct myStack{
    
    /*

    Stack class from scratch (does not use the language’s standard stack or queue library/package methods).

    This implementation allows any data type, not just integers, but the data type must be specified when
    declaring the stack.

    This implementation uses C++ vectors, because they provide a simple dynamic size container, so we give up memory and
    reallocation time in exchange of fast element access and size handling.

    It has the following functions:

    push(data) : pushes that value on top of the stack : does not return anything 
    Time complexity: O(1)

    pop() : removes the top value of the stack : if there was a value to be removed, returns that value, if not,
    an error message is shown to the user
    Time complexity: O(1)

    top() : if there is at least one value in the stack, returns the value at the top of the stack, if not, an error message is shown
    to the user
    Time complexity: O(1)

    isEmpty() : checks if stack is empty, if it is returns true, else returns false (1 and 0 in C++)
    Time complexity: O(1)

    size() : returns the size of the stack
    Time complexity: O(1)

    minValue() : if there is at least one value in the stack, returns the minimum value in the stack, if not, an
    error message is shown to the user.
    Time complexity: O(1)

    */

    vector<pair<dataType,dataType> > dataVector; // vector of pairs of ints to store the item's value and minimum value up until that point of the stack
    dataType min;

    void push(dataType data){

        if(dataVector.size()){
            if(data < min){
                min = data;
            }
        }else{
            min = data;
        }
        dataVector.push_back({data,min});

    }
    dataType pop(){

        dataType deletedValue;

        if(dataVector.size()){
            deletedValue = dataVector.back().first;
            dataVector.pop_back();
        }else{
            cout<<"pop error: stack is empty"<<endl;
        }

        return deletedValue;

    }
    dataType top(){

        dataType topValue;

        if(dataVector.size()){
            topValue = dataVector.back().first;
        }else{
            cout<<"top error: Stack is empty"<<endl;
        }

        return topValue;

    }
    bool isEmpty(){

        bool stackEmpty = false;

        if(!dataVector.size()){
            stackEmpty = true;
        }

        return stackEmpty;

    }
    int size(){

        int stackSize;

        stackSize = dataVector.size();

        return stackSize;

    }

    // minValue returns the minimum value in the stack in O(1) time, since we only have to access our value that
    // is already in the dataVector

    dataType minValue(){

        dataType stackMin;
        
        if(dataVector.size()){
            stackMin = dataVector.back().second;
        }else{
            cout<<"minValue error: stack is empty"<<endl;
        }

        return stackMin;

    }

};
void testStack(){
    
    // function that tests example cases for myStack

    // case 1: int stack

    myStack<int> intStack;

    for(int i = 3; i > 0; --i){
        intStack.push(i);
        cout<<"Pushed value: "<<i<<endl;
    }

    cout<<"Min value in stack: "<<intStack.minValue()<<endl;
    cout<<"Popped value: "<<intStack.pop()<<endl;
    cout<<"Min value in stack: "<<intStack.minValue()<<endl;
    cout<<"Size of stack: "<<intStack.size()<<endl;
    cout<<"Is stack empty: "<<intStack.isEmpty()<<endl;
    cout<<"Top of stack: "<<intStack.top()<<endl;
    cout<<"Popped value: "<<intStack.pop()<<endl;
    cout<<"Popped value: "<<intStack.pop()<<endl;
    cout<<"Popped value: "<<intStack.pop()<<endl;
    cout<<"Is stack empty: "<<intStack.isEmpty()<<endl<<endl;

    // case 2: string stack

    myStack<string> stringStack;

    stringStack.push("b");
    cout<<"Pushed value: 'b'"<<endl;
    cout<<"Min value in stack: "<<stringStack.minValue()<<endl;
    stringStack.push("a");
    cout<<"Pushed value: 'a'"<<endl;
    cout<<"Min value in stack: "<<stringStack.minValue()<<endl;
    stringStack.push("aaaaa");
    cout<<"Pushed value: 'aaaaa'"<<endl;
    cout<<"Min value in stack: "<<stringStack.minValue()<<endl;
    cout<<"Popped value: "<<stringStack.pop()<<endl;
    cout<<"Popped value: "<<stringStack.pop()<<endl;
    cout<<"Top of stack: "<<stringStack.top()<<endl;
    cout<<"Min value in stack: "<<stringStack.minValue()<<endl;
    cout<<"Is stack empty: "<<stringStack.isEmpty()<<endl;


}
void testQueue(){

    // function that tests example cases for myQueue

    // case 1: int queue

    myQueue<int> intQueue;
    for(int i = 3; i > 0; --i){
        intQueue.enqueue(i);
        cout<<"Queued value: "<<i<<endl;
    }

    cout<<"Front of queue: "<<intQueue.front()<<endl;
    cout<<"Dequeue value: "<<intQueue.dequeue()<<endl;
    cout<<"Front of queue: "<<intQueue.front()<<endl;
    cout<<"Size of queue: "<<intQueue.size()<<endl;
    cout<<"Is queue empty: "<<intQueue.isEmpty()<<endl;
    cout<<"Rear of queue: "<<intQueue.rear()<<endl;
    cout<<"Dequeue value: "<<intQueue.dequeue()<<endl;
    cout<<"Dequeue value: "<<intQueue.dequeue()<<endl;
    cout<<"Dequeue value: "<<intQueue.dequeue()<<endl;
    cout<<"Is queue empty: "<<intQueue.isEmpty()<<endl<<endl;

    // case 2: string queue

    myQueue<string> stringQueue;

    cout<<"Queued value: b"<<endl;
    stringQueue.enqueue("b");
    cout<<"Queued value: a"<<endl;
    stringQueue.enqueue("a");
    cout<<"Rear value: "<<stringQueue.rear()<<endl;
    cout<<"Queued value: aaaaa"<<endl;
    stringQueue.enqueue("aaaaa");
    cout<<"Front value: "<<stringQueue.front()<<endl;
    cout<<"Size of queue: "<<stringQueue.size()<<endl;
    cout<<"Dequeued value: "<<stringQueue.dequeue()<<endl;
    cout<<"Size of queue: "<<stringQueue.size()<<endl;
    cout<<"Front of queue: "<<stringQueue.front()<<endl;
    cout<<"Is queue empty: "<<stringQueue.isEmpty()<<endl<<endl;

}
void testingExamples(){

    testStack();
    cout<<endl;
    testQueue();

}
int main(){

    testingExamples();

    return 0;
}