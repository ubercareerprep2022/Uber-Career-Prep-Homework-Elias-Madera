#include <bits/stdc++.h>
using namespace std;

// [Graphs - Ex3] Exercise: BFS Traversal

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

    (All other functions are from part Ex1)

    void bfs(int key)
        takes a key of a node in the graph, looks for a node with that key as data and finds its address. If it
        did not find it, prints an error message. If found, creates a bool map and a graphNode* queue in order
        to store the next nodes to visit if it has not already, then performs bfs printing the data of every
        visited node.

        two major assumptions this implementation considers is, the graph may not be connected, so nodes that are not
        connected with the starting node will not be printed, even if they exist in the graph; and the dfs
        will "prioritize" the edges by recently added, so it will go through the ones added later first.

        Time complexity: O(v+e)
        Space complexity: O(v)

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
    void bfs(int key){

        GraphNode* start = NULL;
        for(auto it : adjNodes){

            if(it.first->data == key) start = it.first;

        }
        if(!start){

            cout<<"key does not belong to a node of the graph. \n";
            return;

        }
        unordered_map<GraphNode*,bool> visited;
        queue<GraphNode*> toVisit;
        visited[start] = true;
        for(toVisit.push(start); !toVisit.empty(); toVisit.pop()){

            cout<<toVisit.front()->data<<" ";

            
            for(auto adjacentNode : adjNodes[toVisit.front()]){

                if(!visited[adjacentNode]){
                    
                    toVisit.push(adjacentNode);
                    visited[adjacentNode] = true;

                }

            }

        }
        cout<<"\n";

        
    }

private:
    unordered_map<GraphNode*,forward_list<GraphNode*>> adjNodes;
    
};

// testing function

void testing(){

   GraphwithAdhacencyList obj1;

    // create graph

    obj1.addNode(1);
    obj1.addNode(2);
    obj1.addNode(3);
    obj1.addNode(0);
    
    obj1.addEdge(0,1);
    obj1.addEdge(3,3);
    obj1.addEdge(2,3);
    obj1.addEdge(2,0);

    obj1.bfs(2); // expected:
    // 2 0 1 3

   obj1.deleteGraph(); // free memory

}
int main(){

    testing();

    return 0; 
}