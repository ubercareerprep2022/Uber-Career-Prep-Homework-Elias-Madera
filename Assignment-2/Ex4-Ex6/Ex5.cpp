#include <bits/stdc++.h>
using namespace std;

// [Trees - Ex5] Exercise: Implement a phone book


/*  PhoneBook interface:
        Contains virutal functions to be implemented for each subclass.
        Size()
        Insert()
        Find()
*/

class PhoneBook{

    public:

        virtual int size() = 0;
        virtual void insert(string name, long long phoneNumber) = 0;
        virtual long long find(string name) = 0;

};

/*  ListPhoneBook class:
        PhoneBookEntry class:
            contains the name, phoneNumber of the entry. Includes constructor.
        forward_list<PhoneBookEntry*> records:
            Singly linked list of pointers to PhoneBookEntries to save the records.
        int booksize:
            variable to store the size of the forward_list.
        int size():
            function that returns booksize.

            Time complexity: O(1)
            Space complexity: O(1)

        void insert(string name, long long phoneNumber):
            creates a node PhoneBookEntry and stores its pointer in the singly linked list. Increments 'booksize' by 1.

            Time complexity: O(1)
            Space complexity: O(1)

        long long find(string name):
            traverses the whole linked list looking for the name, if it finds it, returns the corresponding phoneNumber,
            if not, returns -1

            Time complexity: O(n)
            Space complexity: O(1)

        void deleteListPhoneBook():
            traverses the linked list freeing the memory of all the records, then clears the forward_list.

            Time complexity: O(n)
            Space complexity: O(1)

*/

class ListPhoneBook : public PhoneBook{

    public:

        class PhoneBookEntry{

            public:

                string name;
                long long phoneNumber;
                PhoneBookEntry(string name, long long phoneNumber){

                    this->name = name;
                    this->phoneNumber = phoneNumber;

                }

        };        
        forward_list<PhoneBookEntry*> records;
        int booksize = 0;
        int size(){

            return booksize;

        }
        void insert(string name, long long phoneNumber){

            PhoneBookEntry* temp = new PhoneBookEntry(name,phoneNumber);
            ++booksize;
            records.push_front(temp);

        }
        long long find(string name){

            for(auto x : records){

                if(x->name == name) return x->phoneNumber;

            }

            return -1;

        }
        void deleteListPhoneBook(){

            for(auto x : records){

                delete(x);

            }
            records.clear();

        }



};

/*  BinarySearchTreePhoneBook class:
        RecordsTree class:
            PhoneBookEntry class:
                contains the name, phoneNumber of the entry. Includes constructor.

            void insert(string name, long long phoneNumber):
                creates a PhoneBookEntry and inserts it in the RecordsTree by comparing its key (name) with the current node
                and deciding if it should go the left or right position, until it gets placed.

                Time complexity: O(n) since we could be inserting all of the elements in a sorted order, where the insertion
                would go through all of the nodes so far.
                Space complexity: O(1)

            long long find(string name):
                looks for the given key (name) in the RecordsTree, by comparing the key to the current node and deciding if
                it were to exist, where would it be inside the tree. If we round out of nodes by following the theoretical path,
                the key is not in the tree. Returns -1 if it does not find it.

                Time complexity: O(log(n))
                Space complexity: O(1)

            void deleteBSTPhoneBook():
                Traverses the whole tree breadth first to free the memory of all records.

                Time complexity: O(log(n))
                Space complexity: O(n) since we use a queue to keep track of all the nodes to remove.

            Private PhoneBookEntry* root:
                Represents the root of the tree.

        RecordsTree records:
            BinarySearchTree of PhoneBookEntries to save the records.

        int booksize:
            variable to store the size of the forward_list.

        int size():
            function that returns booksize.

            Time complexity: O(1)
            Space complexity: O(1)

        void insert(string name, long long phoneNumber):
            Applies records.insert(name,phoneNumber). Increments 'booksize' by 1.

            Time complexity: O(log(n))
            Space complexity: O(1)

        long long find(string name):
            Calls records.find(name) and returns it.

            Time complexity: O(log(n))
            Space complexity: O(1)

        void deleteListPhoneBook():
            calls the deleteBSTPhoneBook onto 'records' to free memory.

*/

class BinarySearchTreePhoneBook : public PhoneBook{

    public:

        class RecordsTree{

            public: 

                class PhoneBookEntry{

                    public:

                        string name;
                        long long phoneNumber;
                        PhoneBookEntry* left = NULL;
                        PhoneBookEntry* right = NULL;
                        PhoneBookEntry(string name, long long phoneNumber){

                            this->name = name;
                            this->phoneNumber = phoneNumber;

                        }

                };
                void insert(string name, long long phoneNumber){

                    PhoneBookEntry* temp = new PhoneBookEntry(name,phoneNumber);

                    if(!root){

                        root = temp;

                    }else{

                        PhoneBookEntry* curr = root;
                        while(curr){

                            if((temp->name) > (curr->name)){

                                if(curr->right){ 

                                    curr = curr->right;
                                
                                }
                                else{

                                    curr->right = temp;
                                    break;

                                }

                            }else{

                                if(curr->left){ 
                                    
                                    curr = curr->left;

                                }
                                else{

                                    curr->left = temp;
                                    break;

                                }

                            }

                        } 

                    }

                }
                long long find(string name){

                    PhoneBookEntry* curr = root;
                    while(curr){

                        if(curr->name == name){

                            return (curr->phoneNumber);

                        }
                        if(name > curr->name){

                            curr = curr->right;

                        }else{

                            curr = curr->left;

                        }

                    }

                    return -1;

                }
                void deleteBSTPhoneBook(){

                    PhoneBookEntry* curr = root;
                    queue<PhoneBookEntry*> toRemove;
                    toRemove.push(curr);
                    while(!toRemove.empty()){

                        if(toRemove.front()->left) toRemove.push(toRemove.front()->left);
                        if(toRemove.front()->right) toRemove.push(toRemove.front()->right);
                        delete(toRemove.front());
                        toRemove.pop();

                    }
                    root = NULL;

                }
            
            private:

                PhoneBookEntry* root = NULL;
        };
        RecordsTree records;
        int booksize = 0;
        int size(){

            return booksize;

        }
        void insert(string name, long long phoneNumber){

            records.insert(name,phoneNumber);
            ++booksize;

        }
        long long find(string name){

            return records.find(name);

        }
        void deleteBSTPhoneBook(){

            records.deleteBSTPhoneBook();

        }
};

// testing function

void testing(){

    // creating ListPhoneBook and inserting values:

    ListPhoneBook Book1;
    Book1.insert("ABC",1111111111);
    Book1.insert("XYZ",9999999999);
    Book1.insert("DEF",2222222222);
    cout<<Book1.size()<<"\n"; // expected output: 3
    cout<<Book1.find("ABC")<<"\n"; // expected output: 1111111111
    cout<<Book1.find("XYZ")<<"\n"; // expected output: 9999999999
    cout<<Book1.find("PQR")<<"\n\n"; // expected output: -1

    // freing memory

    Book1.deleteListPhoneBook();

    //creating BinarySearchTreePhoneBook:

    BinarySearchTreePhoneBook Book2;
    Book2.insert("ABC",1111111111);
    Book2.insert("XYZ",9999999999);
    Book2.insert("DEF",2222222222);
    cout<<Book2.size()<<"\n";   // expected 3
    cout<<Book2.find("ABC")<<"\n"; // expected output: 1111111111
    cout<<Book2.find("XYZ")<<"\n";// expected output: 9999999999
    cout<<Book2.find("PQR")<<"\n\n";    // expected output: -1

    // freeing memory

    Book2.deleteBSTPhoneBook();
}
int main(){

    testing();

    return 0;
}