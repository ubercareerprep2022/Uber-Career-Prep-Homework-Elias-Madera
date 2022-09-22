#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 9: Prefix Length

/*

    The approach here is to create a trie from given words, starting with a root node, that will contain all the first letters
    received from all words and assign them a new TrieNode. So first, when adding words to the trie, we will add 1 to the words
    with that prefix counter to every prefix in our path. Then, we go through the path when going through the prefix given and whenever
    we reach the end of the prefix we are looking for, we can just access the value of the words with prefix value from the node.

    Time complexity: O(k) where k is the lenght of the prefix
    Space complexity: O(n*m) where n is the lenght of the longest word and m the number of words, assuming all characters are unique.

*/

class TrieNode{
    public:
        map<char,TrieNode*> adj;
        int strWithP = 0;
        TrieNode(){



        }
};
void addToTrie(TrieNode* root, string str){

    while(str != ""){

        char next = str.front();
        str.erase(0,1);
        
        if(!root->adj[next])
            root->adj[next] = new TrieNode();
        root = root->adj[next];
        root->strWithP++;

    }

}
int getStringsPrefix(TrieNode* root, string str){

    while(str != ""){

        char next = str.front();
        str.erase(0,1);
        if(!root->adj[next])
            return 0;
        root = root->adj[next];

    }

    return root->strWithP;

}
void deleteTrie(TrieNode* root){

    queue<TrieNode*> toDelete;
    queue<TrieNode*> nextToD;
    toDelete.push(root);

    for( ; !toDelete.empty() || !nextToD.empty() ; ){
        for( ; !toDelete.empty() ; toDelete.pop() ){

            for(auto& ele : toDelete.front()->adj){

                nextToD.push(ele.second);

            }
            delete(toDelete.front());

        }
        toDelete = nextToD;
        nextToD = queue<TrieNode*>();
    }

}
void testing(){

    srand(time(0));
    string str = "abbg";
    int k = rand()%str.size();
    vector<string> input{"abba","abbb","abbc","abbd","abaa","abca"};
    TrieNode* root = new TrieNode();

    for(int i = 0; i < input.size(); ++i)
        addToTrie(root,input[i]);
    cout<<"There are: "<<getStringsPrefix(root,str.substr(0,k))<<" strings that start with the first "<<k<<" letters of the prefix "<<str<<"\n";

    deleteTrie(root);


}
int main(){

    testing();

    return 0;

}