#include <bits/stdc++.h>
using namespace std;

// [Trees - Ex1] Exercise: Printing a tree:

// TreeNode class with constructor

class TreeNode{

    public:

        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int data, TreeNode* left, TreeNode* right){

            this->data = data;
            this->left = left;
            this->right = right;

        }

};

/* Tree class with constructor

        print():

        Prints the tree breadth first using a queue of pointers.

        Time complexity: O(n) where n is the total number of employees in the org
        Space complexity: O(n) where n is the total number of employees in the org

        free():

        Traverses the tree breadth first freeing the memory for all of the nodes.

*/

class Tree {

    public:

        TreeNode* root;
        Tree(TreeNode* root){

            this->root = root;

        }
        void print(){

            queue<TreeNode*> toVisit;
            if(!root){

                return;

            }
            toVisit.push(root);
            while(!toVisit.empty()){

                cout<<toVisit.front()->data<<" ";
                if(toVisit.front()->left){

                    toVisit.push(toVisit.front()->left);

                }
                if(toVisit.front()->right){

                    toVisit.push(toVisit.front()->right);

                }
                toVisit.pop();

            }
            

        }
        void free(){

            TreeNode* temp = root;
            queue<TreeNode*> toVisit;
            if(!root){

                return;

            }
            toVisit.push(root);
            while(!toVisit.empty()){

                if(toVisit.front()->left){

                    toVisit.push(toVisit.front()->left);

                }
                if(toVisit.front()->right){

                    toVisit.push(toVisit.front()->right);

                }
                delete(toVisit.front());
                toVisit.pop();

            }            

        }
    

};
void testing(){

    // creating nodes and tree

    TreeNode* leftChild = new TreeNode(6, NULL, NULL);
    TreeNode* rightChild = new TreeNode(3, NULL, NULL);
    TreeNode* left = new TreeNode(7, NULL , NULL);
    TreeNode* right = new TreeNode(17, leftChild, rightChild);
    TreeNode* root = new TreeNode(1, left, right);
    Tree* tree = new Tree(root);

    // testing functions

        // print tree

            tree->print(); // expected output: 1 7 17 6 3

        // free memory

            tree->free();
            delete(tree);

}
int main(){

    testing();

    return 0;
}