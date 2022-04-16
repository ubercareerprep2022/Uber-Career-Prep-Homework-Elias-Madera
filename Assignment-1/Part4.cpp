#include <bits/stdc++.h>
using namespace std;

// node structure with constructors that allow creating nodes that point to other nodes

struct Node{

    int data;
    Node* next;
    Node(int inputData, Node* inputNext){
        data = inputData;
        next = inputNext;
    }
    Node(int inputData){
        data = inputData;
        next = NULL;
    }
    Node(){
        data = 0;
        next = NULL;
    }
    
};

/* LinkedList structure with the following functions:

    void push(Node* node):
    
        Pushes given node to the end of the list, if that node points to other nodes (a different list), adds all following nodes
        to the list as well. Supports circular linked list and checks for loops when inserting nodes. Does not allow pushing when
        the list is circular (or has a loop).

        Time complexity: O(n(log(n))) where n is the max between the size of the list and the pushed list, since we have to
                        lookup each node in our map to check if there is a loop in the list in a O(log(n)) worst case.
                        Sets have the same time complexity in C++, unsorted maps have an average of O(1) but worst of O(n^2).

        Space complexity: O(n) where n is the amount of pushed nodes (including the ones linked to the original pushed one),
                        since we store them in a hashmap to detect loops.

    int pop():

        Pops the last node in the list, if the list is circulas or has a loop, pops last inserted node (which created the loop),
        but does not keep the loop, instead, points last element to NULL, breaking the loop. Does not delete memory allocated to
        the popped node, but stops considering it in the list, so the nodes have to be deleted manually, this allows for nodes to
        be popped but reinserted later. Returns the popped node's data.

        Time complexity: O(n) where n is the size of the list
        Space complexity: O(1)

    void insert(int index, Node* node):

        Inserts a node at the given index if 0 < index <= sizeOfTheList and only if the inserted the node points to NULL, this
        way, the list keeps its order, but allows for insertion at any point of it. It does not allow inserting when the list is
        circular, as there is no strict order for the index.

        Time complexity: O(n) where n is the size of the list
        Space complexity: O(1) different from the push() function, we do not lookup our map since we only allow to insert nodes
                                that point to NULL

    void remove(int index):

        Removes a node at the given index if 0 < index < sizeOfTheList. If the removed node is being pointed at as a reference
        later in the list (creating a loop), the function changes the reference to it to NULL, and links the last and next nodes
        to the removed one to keep the order of the linked list.

        ex: 5<-10<-15       if the removed node was 10, because it is being pointed at later in the list by 5, 5 would point to NULL,
            L> î            and 15 would point to 5, removing the loop.

        becomes: NULL<-5<-15

        Time complexity: O(n) where n is the size of the list
        Space complexity: O(1)

    Node* elementAt(int index):

        Returns element at index if 0 < index < sizeOfTheList. If the index is out of range, displays the error and returns NULL.

        Time complexity: O(n) where n is the size of the list
        Space complexity: O(1)
    
    int size(): 
    
        Returns the size of the list. 

        Time complexity: O(1)
        Space complexity: O(1)

    void printList():

        Inserts the list in a graphic way in a string, using "->" to indicate links and includes if the list has a cycle or if it ends at NULL.

        Time complexity: O(n) where n is the size of the list.
        Space complexity: O(1)
    
    void deleteList():

        Deletes the memmory allocation on the heap for all the nodes in the linkedlist.

        Time complexity: O(n) where n is the size of the list.
        Space complexity: O(1)

    bool hasCycle():

        returns if the list has a cycle (is looped).

        Time complexity: O(1)
        Space complexity: O(1)

    bool isPalindrome():

        returns if the list is a palindrome by inserting the elements in 2 dequeues.

        Time complexity: O(n) where n is the size of the list.
        Space complexity: O(n) , which could be lowered to O(1) by reversing the linked list in position, but I could not figure how to return
                                it to its original position after calling the function.

*/

struct Linkedlist{

    Node* head = NULL;
    Node* cycle = NULL;
    bool isCycle = false;
    map<Node*,int> pushedNodes;
    void push(Node* node){

        Node* current;

        if(!isCycle){
        
            if(!pushedNodes.size()){

                head = node;
                pushedNodes[node] = 1;

                Node* temp = node;
                while(temp->next && !isCycle){

                    if(pushedNodes[temp->next]){

                        cycle = temp->next;
                        isCycle = true;
                        break;
                        
                    }
                    
                    temp = temp->next;
                    pushedNodes[temp] = 1;

                }
                
            }else{

                current = head;
                while(current->next){

                    current = current->next;

                }

                current->next = node;
                if(pushedNodes[node]){

                    cycle = node;
                    isCycle = true;

                }
                pushedNodes[node] = 1;
                Node* temp = node;
                while(temp->next && !isCycle){

                    if(pushedNodes[temp->next]){

                        cycle = temp->next;
                        isCycle = true;
                        break;
                        
                    }
                    
                    temp = temp->next;
                    pushedNodes[temp] = 1;

                }

            }

        }else{

            cout<<"List has cycle, node can't be pushed at the end of the list"<<endl;

            delete(node);

        }

    }
    int pop(){
        
        int poppedValue = 0;
        Node* current;

        if(!pushedNodes.size()){
            cout<<"List is empty, no element popped"<<endl;
        }else{

            if(pushedNodes.size() == 1){

                poppedValue = head->data;
                pushedNodes.erase(head);
                cycle = NULL;
                isCycle = false;             

            }else{

                current = head;
                int i = 0;

                while(current->next->next && i < ((int)pushedNodes.size()-2) ){

                    current = current->next;
                    ++i;

                }

                Node* temp;
                temp = current->next;
                poppedValue = temp->data;
                current->next = NULL;
                cycle = NULL;
                isCycle = false;
                pushedNodes.erase(temp);

            }
        }

        return poppedValue;
    }
    void insert(int index, Node* node){

        if(!node->next){

            if(!index){

                node->next = head;
                head = node;
                pushedNodes[node] = 1;

            }else{

                if(index == pushedNodes.size() && isCycle){

                    cout<<"Node can not be inserted at the end of list, since it has a cycle"<<endl;

                }else{

                    if(index <= pushedNodes.size() && index > 0){

                        Node* current;
                        current = head;

                        for(int i = 0; i < index-1; ++i){

                            current = current->next; 

                        }

                        node->next = current->next;
                        current->next = node;
                        pushedNodes[node] = 1;


                    }else{

                        cout<<"Index not in range"<<endl;

                    }

                }

            }

        }else{

            if(pushedNodes[node]){

                cout<<"Node can not be inserted at index, because it is already in the list."<<endl;

            }else{

            cout<<"Node can not be inserted at index, because it points to another node."<<endl;

            }
        }

    }
    void remove(int index){

        if(index < pushedNodes.size() && index >= 0){

            if(!index){

                Node* temp;
                temp = head;
                head = temp->next;
                temp->next = NULL;
                pushedNodes.erase(temp);

                if(isCycle){

                    temp = head;
                    while(temp->next != cycle){

                        temp = temp->next;

                    }
                    temp->next = NULL;
                    isCycle = false;
                    cycle = NULL;

                }

            }else{

                Node* current;
                current = head;

                if(index == pushedNodes.size()-1){

                    pop();

                }else{

                    for(int i = 0; i < index-1; ++i){

                        current = current->next;

                    }

                    if(isCycle){

                        if(current->next == cycle){

                            current->next = cycle->next;

                            while(current->next != cycle){

                                current = current->next;

                            }

                            pushedNodes.erase(current->next);
                            current->next = NULL;
                            isCycle = false;
                            cycle = NULL;

                        }else{

                            Node* temp;
                            temp = current->next;
                            pushedNodes.erase(temp);
                            current->next = temp->next;

                        }

                    }else{

                        Node* temp;
                        temp = current->next;
                        pushedNodes.erase(temp);
                        current->next = temp->next;

                    }

                }
            }

        }else{

            cout<<"Index not in range"<<endl;

        }

    }
    Node* elementAt(int index){

        Node* ans = NULL;

        if(!index){

            ans = head;

        }else{

            if(index < pushedNodes.size() && index > 0){

                ans = head;

                for(int i = 0; i < index; ++i){

                    ans = ans->next;

                }

            }

        }

        return ans;

    }
    int size(){

        return pushedNodes.size();

    }
    void printList(){

        string stringList = "";

        Node* current = head;
        int i = 0;
        int cycleIndex = 0;
        while(current && i < pushedNodes.size()){

            stringList += to_string(current->data) + "->";
            current = current->next;
            ++i;

        }

        if(!current){

            stringList += "NULL";

        }else{

            stringList += to_string(current->data) + "(cycle)";

        }        

        cout<<stringList<<endl;

    }
    void deleteList(){

        Node* current = head;
        Node* temp;
        for(int i = 0; i < pushedNodes.size(); ++i){

            temp = current;
            current = current->next;
            delete(temp);

        }

    }
    bool hasCycle(){

        return isCycle;

    }
    bool isPalindrome(){

        bool ans = true;

        deque<int> half1, half2;
        Node* current = head;

        int i = 0;
        while(current){

            if(i < size()/2){
                half1.push_back(current->data);
            }else{
                half2.push_front(current->data);
            }
                current = current->next;
            ++i;
            
        }
        for(int i = 0; i < size()/2; ++i){

            if(half1.front() != half2.front()){
                ans = false;
            }

        }


        return ans;

    }
};
void testing(){

// Tests:

    Linkedlist testList;
    Node* node1 = new Node(5);
    Node* node2 = new Node(10);
    Node* node3 = new Node(15);
    Node* node4 = new Node(20,node3);

    // testPushBackAddsOneNode:

        testList.push(node1);
        testList.push(node2);

        // Expected output: 5->10->NULL

        cout<<"testPushBackAddsOneNode: ";
        testList.printList();

    // testPopBackRemovesCorrectNode:

        testList.pop();

        // Expected output: 5->NULL

        cout<<"testPopBackRemovesCorrectNode: ";
        testList.printList();

    // testEraseRemovesCorrectNode:

        testList.remove(0);

        // Expected output: NULL

        cout<<"testEraseRemovesCorrectNode: ";
        testList.printList();

    // testEraseDoesNothingIfNoNode:

        cout<<"testEraseDoesNothingIfNoNode: ";
        testList.remove(3);

        // Expected output: "Index out of range"

    // testElementAtReturnNode:

        testList.push(node3);
        Node* pointer = testList.elementAt(0);

        // Expected output: 15

        cout<<"testElementAtReturnNode: "<<pointer->data<<endl;

    // testElementAtReturnsNoNodeIfIndexDoesNotExist:

        Node* testPointer = testList.elementAt(10);
        
        if(!testPointer){
            cout<<"testElementAtReturnsNoNodeIfIndexDoesNotExist: Returned NULL"<<endl;
        }else{
            cout<<"testElementAtReturnsNoNodeIfIndexDoesNotExist: Returned "<<testPointer;
        }

        // Expected output: testElementAtReturnsNoNodeIfIndexDoesNotExist: Returned NULL

    // testSizeReturnsCorrectSize:

        // Expected output: 1

        cout<<"testSizeReturnsCorrectSize: "<<testList.size()<<endl;

// Extra tests:

    // isPalindrome:

        // Expected output: 1 (True)

        cout<<"isPalindrome: "<<testList.isPalindrome()<<endl;

    // hasCycle:

        testList.push(node4);

        // Expected output: 1 (True)

        cout<<"hasCycle: "<<testList.hasCycle()<<endl;

// Delete pointers:

        delete(node1);
        delete(node2);

}
int main(){

    testing();

    return 0;
}