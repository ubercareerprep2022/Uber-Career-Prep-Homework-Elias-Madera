#include <bits/stdc++.h>
using namespace std;

// OLD FROM PART 4: Node structure with constructors that allow creating nodes that point to other nodes

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

/* 
    Part 5: Reverse a Linked List
        Implement reverseLinkedList() which takes in a linked list and returns a new linked list with the same elements in reverse order.
    The following solution considers the reversed linked list as a new list, so the function itself does not return a copy of the reversed linked list,
    since we do not store any extra copies of the linked list given, we can have constant space complexity in the iterative reverse. The following solution
    does not allow to reverse a linked list with a loop / cycle.

    void reverseListIteratively():
        
        Iterates through the linked list reversing the pointers to the next node for each node in the list, no extra memory needed.

        Time complexity: O(n) where n is the size of the list.
        Space complexity: O(1)

    void reverseListStack():

        Iterates through the list once to push all elements into a stack, then iterates through the list a second time and assigns
        each node's value to that of the top of the stack, then pops the inserted element and moves to the next node.

        Time complexity: O(n) where n is the size of the list.
        Space complexity: O(n) where n is the size of the list, since we store the data in a stack.

    void reverseListRecursion(Node* head):

        Receives a pointer to the head of a linked list. 
        Recursively pushes the current node data in a dequeue, calls reverseListRecursion() on the remaining nodes, after these functions return
        assigns the front of the dequeue's value to the current node, pops the front of the dequeue.

        Time complexity: O(n) where n is the size of the list.
        Space complexity: O(n) where n is the size of the list, since we store the data in a dequeue.

    OLD FROM PART 4: LinkedList structure with the following functions:

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
    void reverseListIteratively(){
        
        if(size() && !isCycle){

            Node* Last = NULL;
            Node* current = head;
            Node* next = current->next;
            while(current){

                next = current->next;
                current->next = Last;
                Last = current;
                current = next;



            }
            head = Last;
        }

    }
    void reverseListStack(){

        stack<int> dataStack;
        if(size() && !isCycle){

            Node* current = head;
            while(current){

                dataStack.push(current->data);
                current = current->next;

            }

            current = head;

            while(current){

                current->data = dataStack.top();
                dataStack.pop();
                current = current->next;

            }

        }

    }
    deque<int> rlRecursionData;
    void reverseListRecursion(Node* head){

        if(size() && !isCycle){

            if(head){

                rlRecursionData.push_front(head->data);
                reverseListRecursion(head->next);
                head->data = rlRecursionData.back();
                rlRecursionData.pop_back();

            }
            

        }

    }
};
void testing(){

    Linkedlist testList;
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    

        // Filling list:

            testList.push(node1);
            testList.push(node2);
            testList.push(node3);
            testList.push(node4);

        // Expected: 1->2->3->4->NULL

            testList.printList();
        
    testList.reverseListIteratively();
    
        // Expected: 4->3->2->1->NULL

            testList.printList();

    testList.reverseListStack();

        // Expected: 1->2->3->4->NULL

            testList.printList();

    testList.reverseListRecursion(testList.head);

        // Expected: 4->3->2->1->NULL
        
            testList.printList();
    

    // Free memory:
    
        testList.deleteList();

    

}
int main(){

    testing();

    return 0;
}