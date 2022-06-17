#include <bits/stdc++.h>
using namespace std;

// [Trees - Ex6] Exercise: Unsorted lists v.s. Binary search trees

/*

    This file uses a copy of the classes used previously for Ex5 to keep everything in one file.

*/

// PhoneBook interface

class PhoneBook{

    public:

        virtual int size() = 0;
        virtual void insert(string name, long long phoneNumber) = 0;
        virtual long long find(string name) = 0;

};

// ListPhoneBook

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

// BinarySearchTreePhoneBook

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

/* listPhoneBookTesting():

    testing function of ListPhoneBook

*/
void listPhoneBookTesting(){

    ListPhoneBook testBook; 
    ifstream input ("data.csv"); // open file to read
    string entryID,entryPN; // store name and Phone
    int insertCount=0, findCount=0; // counters to keep track of calls
    auto start = chrono::high_resolution_clock::now(); // internal clock started
    if(input.is_open()){

        while(getline(input,entryID,',')){ // collect all info and store it safely

            getline(input,entryPN);
            long long entryPhone = stoll(entryPN);
                
            testBook.insert(entryID,entryPhone);
            ++insertCount;
        }
        


    }else cout<<"Error opening input file \n";
    auto stop = chrono::high_resolution_clock::now(); // clock finish to check time
    auto insertionTime = chrono::duration_cast<chrono::milliseconds>(stop-start); // total time of inserting, in milliseconds
    ifstream search ("search.txt");

    start = chrono::high_resolution_clock::now(); // new clock to finish insertion
    if(search.is_open()){

        while(getline(search,entryID)){

            if(testBook.find(entryID) == -1){

                cout<<"Could not find ID: "<<entryID<<"\n";
                break;

            }else ++findCount;

        }

    }else cout<<"Error opening search file \n"; // new clock finished find calls.
    stop = chrono::high_resolution_clock::now(); // stop clock
    auto findTime = chrono::duration_cast<chrono::milliseconds>(stop-start); // duration milliseconds

    // benchmarks

    cout<<"Insertion took: "<<insertionTime.count()<<" milliseconds. \n";
    cout<<"The size of the PhoneBook is "<<testBook.size()<<"\n";
    cout<<"find() was called "<<findCount<<" times. \n";
    cout<<"Search took: "<<findTime.count()<<" milliseconds. \n";
    
    testBook.deleteListPhoneBook(); // traverses the ListPhoneBook free memory.
    input.close(); // close file
    search.close(); // close file

}
/* bstPhoneBookTesting():

    testing function of BinarySearchTreePhoneBook

*/
void bstPhoneBookTesting(){

    BinarySearchTreePhoneBook testBook; // store records
    ifstream input ("data.csv"); 
    string entryID,entryPN; // store name and Phone
    int insertCount=0, findCount=0; // counters to keep track of calls
    auto start = chrono::high_resolution_clock::now(); // start clock
    if(input.is_open()){

        while(getline(input,entryID,',')){ // get all lines

            getline(input,entryPN);
            long long entryPhone = stoll(entryPN);
                
            testBook.insert(entryID,entryPhone);    // insert the items
            ++insertCount;
        }
        


    }else cout<<"Error opening input file \n";
    auto stop = chrono::high_resolution_clock::now(); // stop clock insert bstPhoneBook
    auto insertionTime = chrono::duration_cast<chrono::milliseconds>(stop-start); // duration in milliseconds
    ifstream search ("search.txt"); // open file

    start = chrono::high_resolution_clock::now(); // start clock now
    if(search.is_open()){

        while(getline(search,entryID)){ // get all lines from search

            if(testBook.find(entryID) == -1){

                cout<<"Could not find ID: "<<entryID<<"\n"; // if ID wasn't found, breaks and prints a message.
                break;

            }else ++findCount;

        }

    }else cout<<"Error opening search file \n"; 
    stop = chrono::high_resolution_clock::now(); // stop clock
    auto findTime = chrono::duration_cast<chrono::milliseconds>(stop-start); // find entime in milliseconds
    if((testBook.size()) < 1000){

        cout<<"find() was called: "<<testBook.size();

    }else

    // benchmarks

    cout<<"Insertion took: "<<insertionTime.count()<<" milliseconds. \n";
    cout<<"The size of the PhoneBook is "<<testBook.size()<<"\n";
    cout<<"find() was called "<<findCount<<" times. \n";
    cout<<"Search took: "<<findTime.count()<<" milliseconds. \n";
    
    testBook.deleteBSTPhoneBook(); // traverses the tree to free memory
    input.close(); // close file
    search.close(); // close file

}
// void testing():
    /*
        1.- What is the output of your program when you use a ListPhoneBook?

        ----------------------------------------- 
        Output of ListPhoneBook: 
        ----------------------------------------- 
        Insertion took: 2123 milliseconds. 
        The size of the PhoneBook is 1000000
        find() was called 1000 times.
        Search took: 24453 milliseconds.
        ----------------------------------------- 

        2.- What is the output of your program when you use a BinarySearchTreePhoneBook?

        ----------------------------------------- 
        Output of BinarySearchTreePhoneBook:
        -----------------------------------------
        Insertion took: 3853 milliseconds. 
        The size of the PhoneBook is 1000000
        find() was called 1000 times.
        Search took: 3 milliseconds.
        ----------------------------------------- 

        3.- Why is there a difference in the running times for the two implementations?

        The seconds method: Binary Search Tree, for each iteration of the alogirthm of comparing, discards
        half of the total number of nodes in order to find a key in all the nodes. This means that the program runs
        in log(n) time, where n is the total number of nodes. Which turns out pretty significant for a 10^6 nodes.
        24 seconds vs 3 milliseconds.

        an interesting observation is the increased insertion time in the BST compared to the list, since the list
        can insert in O(1) time while BST is O(n) worst.

    */
void testing(){

    cout<<"----------------------------------------- \n";
    cout<<"Output of ListPhoneBook: \n";
    cout<<"----------------------------------------- \n";
    listPhoneBookTesting();
    cout<<"----------------------------------------- \n";
    cout<<"Output of BinarySearchTreePhoneBook: \n";
    cout<<"----------------------------------------- \n";
    bstPhoneBookTesting();
    cout<<"----------------------------------------- \n";
}
int main(){

    testing(); // testing output:

    return 0;
}