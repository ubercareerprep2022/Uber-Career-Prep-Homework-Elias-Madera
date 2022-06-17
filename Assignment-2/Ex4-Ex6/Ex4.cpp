#include <bits/stdc++.h>
using namespace std;

// [Trees - Ex4] Exercise: Implement a binary search tree

/* BinarySearchTree class:

        class Node: 
            Node class with constructor, holds a key, a left and a right pointer.
        void insert(key):
            inserts key into the BinarySearchTree by creating a node with it and comparing its value against the current node
            to determine the location of it.

            Time complexity: O(log(n))
            Space complexity: O(1)
            
        bool find(key):
            takes key and looks it up in the BinarySearchTree by comparing the value against the current node to determine the position
            where it should be located if it exists.

            Time complexity:O(log(n))
            Space complexity: O(1)
        
        void freeMemory():
            traverses de BinarySearchTree breadth first to remove each of its elements and freeing their memory by pushing them in a queue

            Time complexity: O(n)
            Space complexity: O(n)
        
        void print():
            traverses de BinarySearchTree breadth first to print each of its elements' keys by pushing them in a queue

            Time complexity: O(n)
            Space complexity: O(n)



*/

class BinarySaerchTree{

    public:

        class Node{

            public:

                int key;
                Node* left = NULL;
                Node* right = NULL;
                Node(int key){

                    this->key = key;

                }

        };
        void insert(int key){

            Node* temp = new Node(key);

            if(!root){

                root = temp;

            }else{

                Node* curr = root;
                while(curr){

                    if((temp->key) > (curr->key)){

                        if(curr->right){

                            curr = curr->right;

                        }else{

                            curr->right = temp;
                            break;

                        }

                    }else{

                        if(curr->left){

                            curr = curr->left;

                        }else{

                            curr->left = temp;
                            break;

                        }

                    }

                }

            }

        }
        bool find(int key){

            Node* temp = root;

            while(temp){

                if(key == temp->key){

                    return true;

                }
                if(temp->key < key){

                    temp = temp->right;

                }else{

                    temp = temp->left;

                }

            }

            return false;

        }
        void freeMemory(){

            Node* temp = root;
            queue<Node*> toRemove;
            toRemove.push(temp);

            while(!toRemove.empty()){

                if(toRemove.front()->left) toRemove.push(toRemove.front()->left);
                if(toRemove.front()->right) toRemove.push(toRemove.front()->right);
                delete(toRemove.front());
                toRemove.pop();

            }
            root = NULL;

        }
        void print(){

            Node* temp = root;
            queue<Node*> toRemove;
            toRemove.push(temp);

            while(!toRemove.empty()){

                if(toRemove.front()->left) toRemove.push(toRemove.front()->left);
                if(toRemove.front()->right) toRemove.push(toRemove.front()->right);
                cout<<toRemove.front()->key<<" - ";
                toRemove.pop();

            }            

        }
    
    private:

        Node* root = NULL;
};

// testing function

void testing(){

    // creating tree and inserting values:

    BinarySaerchTree Tree1;
    Tree1.insert(16);
    Tree1.insert(10);
    Tree1.insert(21);
    Tree1.insert(7);
    Tree1.insert(13);
    Tree1.insert(18);
    Tree1.insert(29);
    Tree1.insert(99);

    // testing functions

        cout<<"Print tree elements: \n";
        Tree1.print(); // used only to verify correct insertion
        cout<<"\nfind(1) returns: "<<Tree1.find(1); // expected output: false (0)
        cout<<"\nfind(99) returns: "<<Tree1.find(99); // expected output: true (1)

    // free memory

        Tree1.freeMemory();

}
int main(){

    testing();

    return 0;
}