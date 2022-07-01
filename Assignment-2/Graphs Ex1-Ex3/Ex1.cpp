#include <bits/stdc++.h>
using namespace std;

// [Graphs - Ex1] Exercise: Implement a graph using adjacency list 

// GraphNode class with constructor

class GraphNode{
public:
    int data;
    GraphNode(int data){

        this->data = data;

    }


};

/* GraphwithAdhacencyList class:

    Has unordered_map<GraphNode*,forward_list<GraphNode*>> to store the pointers of which a graph is connected to
    This implementation considers undirected graph, meaning an edge from X to Y is bilateral.

    void print()
        goes through the adjacency map and prints all of the keys and elements in the lists of those keys and prints them to console

        Time complexity: O(v+e)
        Space complexity: O(v+e) adjacency map
    void addNode(int key)
        takes a key, makes a new node with it and adds it to the adjacency list

        Time complexity: O(1)
        Space complexity: O(1)
    void removeNode(int key)
        takes a key, goes through the map once to find the node with that key, stores its address. Goes through the whole adjacency
        map to remove references to that node from all lists, removes the node form the map and frees its memory.

        Time complexity: O(v+e)
        Space complexity: O(1)
    void addEdge(int node1, int node2)
        takes two keys of nodes, finds the addresses by going through the adjacency map
        and adds an edge between them. It allows for parallel edges (edges that go and come from the
        same nodes). If it does not find one of the nodes, prints an error message.

        Time complexity: O(v)
        Space complexity: O(1)
    void removeEdge(int node1, int node2)
        takes two keys of nodes, finds the addresses by going through the adjacency map
        and removes an edge between them. If parallel edges are present, removes all of them.
        If it does not find one of the nodes, prints an error message.

        Time complexity: O(v+e)
        Space complexity: O(1)
    forward_list<GraphNode*> getAdjNodes(int key)
        takes a key of a node, goes through the map and returns its forward list of adjacency.
        if node is not found, returns an empty list and prints an error message.

        Time complexity: O(v)
        Space complexity: O(1)
    void deleteGraph()
        frees the memory of all the nodes in the graph and clears the adjacency map.

        Time complexity: O(v+e)
        Space complexity: O(1)

*/
class GraphwithAdhacencyList{
public:
    void print(){

        cout<<"\n";

        for(auto it : adjNodes){

            cout<<it.first->data<<":";
            for(auto i : it.second){

                cout<<" "<<i->data;

            }
            cout<<"\n";

        }

    }
    void addNode(int key){

            GraphNode* newNode = new GraphNode(key);
            adjNodes[newNode];

        }
    void removeNode(int key){

        GraphNode* key1 = NULL;
        for(auto it : adjNodes){

            if(it.first->data == key) key1 = it.first;

        }
        if(key1){

            for(auto it : adjNodes){

                adjNodes[it.first].remove(key1);

            }
            delete(key1);
            adjNodes.erase(key1);

        }else{

            cout<<"Node was not in graph. \n";

        }

    }
    void addEdge(int node1, int node2){
        GraphNode* key1 = NULL;
        GraphNode* key2 = NULL;
        for(auto it : adjNodes){

            if(it.first->data == node1) key1 = it.first;
            if(it.first->data == node2) key2 = it.first;
        }
        if(key1 && key2){

            adjNodes[key1].push_front(key2);
            adjNodes[key2].push_front(key1);

        }else{

            cout<<"One of the keys given is not present in the graph. \n";

        }

    }
    void removeEdge(int node1, int node2){

        GraphNode* key1 = NULL;
        GraphNode* key2 = NULL;
        for(auto it : adjNodes){

            if(it.first->data == node1) key1 = it.first;
            if(it.first->data == node2) key2 = it.first; 

        }
        if(key1 && key2){

            adjNodes[key1].remove(key2);
            adjNodes[key2].remove(key1);

        }else{

            cout<<"One of the nodes does not exist in the graph. \n";

        }

    }
    forward_list<GraphNode*> getAdjNodes(int key){

        for(auto it : adjNodes){

            if(it.first->data == key) return adjNodes[it.first];

        }
        
        cout<<"Given node is not in graph \n";
        return {};

    }
    void deleteGraph(){

        for(auto it : adjNodes){

            it.second.clear();
            delete(it.first);

        }
        adjNodes.clear();

    }
private:
    unordered_map<GraphNode*,forward_list<GraphNode*>> adjNodes;
    
};

// testing function

void testing(){

    GraphwithAdhacencyList obj1;
    
    obj1.addNode(1);
    obj1.addNode(2);
    obj1.addNode(3);
    obj1.addNode(4);
    obj1.addEdge(1,2);
    obj1.addEdge(2,3);
    obj1.addEdge(1,3);

    obj1.print(); // Expected:
    /*
        4:
        3: 1 2
        2: 3 1
        1: 3 2

    */

    obj1.removeEdge(1,3); 

    obj1.print(); // Expected
    /*
        4:
        3: 2
        2: 3 1
        1: 2
    */

    obj1.removeNode(2); 

    obj1.print(); // Expected
    /*

        4:
        3:
        1:

    */

    obj1.removeNode(2); // Expected
    // Node was not in graph.

    obj1.addEdge(2,3); // Expected
    // One of the keys given is not present in the graph.

    obj1.addEdge(1,3);
    obj1.addEdge(1,4);
    forward_list<GraphNode*> test = obj1.getAdjNodes(1);
    for(auto element : test){

        cout<<element->data<<" ";

    }cout<<"\n"; // Expected:
    // 4 3

    obj1.deleteGraph(); // free memory

}
int main(){

    testing();

    return 0; 
}