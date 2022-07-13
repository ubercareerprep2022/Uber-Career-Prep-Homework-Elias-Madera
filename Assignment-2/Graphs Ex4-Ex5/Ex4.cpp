#include <bits/stdc++.h>
using namespace std;

// [Graphs - Ex4] Exercise: Minimum number of edges between two nodes of a Graph

// GraphNode class with constructor 

/* GraphwithAdhacencyList class:

    Has unordered_map<GraphNode*,forward_list<GraphNode*>> to store the pointers of which a node is connected to
    This implementation considers the graph is undirected, meaning an edge from X to Y is bilateral.

    (All other functions are from part Ex1)

    int minNumberOfEdges(int key1, int key2)
        takes to values as the keys to find the minimum number of edges between them. First goes through
        the adjacency list and finds the node with the first key's address, if it does not find it, returns -1.

        then performs a breadth first search starting from the first node looking for a node with the key vale 'key2'.
        Uses a queue of pairs of GraphNode* and 'int' where the 'int' of a pair represents the minimum number of edges
        to get to it starting from the first node. If a matching node is found, returns the number of edges, if not, returns
        -1.

        Time complexity: O(v+e)
        Space complexity: O(v)

*/

class GraphNode{
public:
    int data;
    GraphNode(int data){

        this->data = data;

    }


};
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
    int minNumberOfEdges(int key1, int key2){

        GraphNode* start = NULL;
        for(auto it : adjNodes){ // look for starting node

            if(it.first->data == key1) start = it.first;

        }

        if(!start) return -1; // if not found, return -1

        unordered_map<GraphNode*,bool> visited;
        queue<pair<GraphNode*,int>> toVisit;

        visited[start] = true;

        // perform bfs

        for(toVisit.push({start,0}); !toVisit.empty(); toVisit.pop()){


            if(toVisit.front().first->data == key2){

                return toVisit.front().second;

            }

            for(auto adjacentNode : adjNodes[toVisit.front().first]){

                if(!visited[adjacentNode]){

                    visited[adjacentNode] = true;
                    toVisit.push({adjacentNode,toVisit.front().second+1}); // push the address to visit and the number of edges to current node + 1

                }

            }

        } 

        return -1; // fallback if it does not find a path

    }

private:
    unordered_map<GraphNode*,forward_list<GraphNode*>> adjNodes;
    
};
void testing(){

    GraphwithAdhacencyList obj1; // initialize graph

    // add nodes to the graph

    for(int i = 0; i < 7; ++i) obj1.addNode(i);

    // add edges to the graph

    obj1.addEdge(0,1);
    obj1.addEdge(1,2);
    obj1.addEdge(0,2);
    obj1.addEdge(0,4);
    obj1.addEdge(2,5);
    obj1.addEdge(6,4);
    obj1.addEdge(3,4);
    obj1.addEdge(5,4);

    // testing

    cout<<obj1.minNumberOfEdges(1,5)<<"\n"; // expected: 2
    cout<<obj1.minNumberOfEdges(6,1)<<"\n"; // expected: 3
    cout<<obj1.minNumberOfEdges(1,8)<<"\n"; // expected: -1

    // free memory

    obj1.deleteGraph();
    
}
int main(){

    testing();

    return 0;

}