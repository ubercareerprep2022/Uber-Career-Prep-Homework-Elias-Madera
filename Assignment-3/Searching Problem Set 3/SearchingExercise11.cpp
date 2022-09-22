#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 11: Add-and-Search Words

/*

    The trick that we are going to use is implementing a trie, but whenever the string we are looking for, we consider ALL the available
    paths from the current node we are sitting on. So first, go through the first character and see if we are able to reach it from our
    root node, if is a dot, we are going to have to push all possible paths into our next level queue. After pushing a possible path, we check
    if we are in our last index, if we are, this means that we just need to check for the isEnd boolean value to check if its a possible path
    as it may be a prefix of a given word and not a given word per se.

    Time complexity: O(v+e)
    Space complexity: O(v+e)

*/

class TrieNode{
    public:
        map<char,TrieNode*> adj;
        bool isEnd = false;
        TrieNode(){



        }


};
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
void addWord(string str,TrieNode* root){

    while(str != ""){

        char next = str.front();
        str.erase(0,1);
        
        if(!root->adj[next])
            root->adj[next] = new TrieNode();
        root = root->adj[next];
        

    }
    root->isEnd = true;

}
bool search(string str,TrieNode* root){

    if(str.size() == 0) return root->isEnd;
    int index = 0;
    queue<TrieNode*> poss;
    queue<TrieNode*> nextposs;
    poss.push(root);

    while(!poss.empty() || !nextposs.empty() && index < str.size()){

        while(!poss.empty()){

            if(str[index] != '.'){

                if(poss.front()->adj.find(str[index]) != poss.front()->adj.end()){

                    nextposs.push(poss.front()->adj[str[index]]);
                    if(index == str.size()-1 && nextposs.back()->isEnd)
                        return true;

                }


            }else{

                for(auto& ele : poss.front()->adj){

                    nextposs.push(ele.second);
                    if(index == str.size()-1 && nextposs.back()->isEnd)
                        return true;                    

                }

            }
            poss.pop();

        }
        

        poss = nextposs;
        nextposs = queue<TrieNode*>();
        ++index;

    }

    return false;

}
void testing(){

    TrieNode* root = new TrieNode();
    addWord("bad",root);
    addWord("dad",root);
    addWord("mad",root);
    cout<<search("pad",root)<<"\n"; // expected 0
    cout<<search("bad",root)<<"\n"; // expected 1
    cout<<search(".ad",root)<<"\n"; // expected 1
    cout<<search("b..",root)<<"\n"; // expected 1
    cout<<search("...",root)<<"\n"; // expected 1
    cout<<search("..f",root)<<"\n"; // expected 0
    deleteTrie(root);
    


}
int main(){

    testing();

    return 0;

}