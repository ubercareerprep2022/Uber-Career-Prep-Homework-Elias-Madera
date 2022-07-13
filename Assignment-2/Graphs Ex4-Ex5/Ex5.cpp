#include <bits/stdc++.h>
using namespace std;

// [Graphs - Ex5] Exercise: Loop in a Directed Graph:

// GraphNode class with constructor 

/* GraphwithAdhacencyList class:

    Has unordered_map<GraphNode*,forward_list<GraphNode*>> to store the pointers of which a node is connected to
    This implementation considers the graph is DIRECTED, meaning an edge from X to Y is NOT bilateral.

    (All other functions are from part Ex1)

    bool canFinishCourses(vector<vector<int>>& prerequisites):
        takes a vector of pairs of numbers where the pair A,B represents an edge from A to B. Builds the graph based
        on the prerequisites. Performs a dfs in every connected component. While traversing through the DFS each node
        is set an ID of 2, if at any point of the traversal a node with ID of 2 is reached, this means the graph has a loop
        and return false.

        After traversing a connected component sets all of the visited nodes an ID of 1 to indicated they are visited, but
        not a part of the current loop.

        Keeps looking for nodes that have the default ID of 0, meaning they are part of a component that has not been visited.
        If no loop is found, returns true.

        Time complexity: O(v+e)
        Space complexity: O(v) the adjacency list is not considered extra memory.

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
    bool canFinishCourses(vector<vector<int>>& prerequisites){

        map<int,bool> created;

        // create graph

        for(int i = 0; i < prerequisites.size(); ++i){

            if(!created[prerequisites[i][0]]){

                addNode(prerequisites[i][0]);
                created[prerequisites[i][0]] = true;
            } 
            if(!created[prerequisites[i][1]]){

                addNode(prerequisites[i][1]);
                created[prerequisites[i][1]] = true;

            }
            
            addEdge(prerequisites[i][0],prerequisites[i][1]);

        }

        map<GraphNode*,int> visited;
        stack<GraphNode*> dfs;
        queue<GraphNode*> changeID;

        // go through all components

        for(auto node : adjNodes){

            if(!visited[node.first]){ // if visited ID is 0

                for(dfs.push(node.first); !dfs.empty(); ){

                    GraphNode* current = dfs.top();
                    dfs.pop();
                    visited[current] = 2; // mark ID as 2 (node part of current traversal)
                    changeID.push(current); // remember visited nodes to change their IDs back to 1 when traversal is over

                    for(auto adjacentNode : adjNodes[current]){

                        if(visited[adjacentNode] == 2) return false; // if ID 2 is found we've found a loop
                        else{

                            if(!visited[adjacentNode]) dfs.push(adjacentNode); // push the rest of the component nodes that have not been visited ( have ID 0 strictly )

                        }

                    }

                }

                for(; !changeID.empty(); changeID.pop()) visited[changeID.front()] = 1; // change back IDs



            }

        }

        return true;

    }

private:
    unordered_map<GraphNode*,forward_list<GraphNode*>> adjNodes;
    
};
void testing(){

    // create graph and test case

    GraphwithAdhacencyList graph1,graph2,graph3,graph4;
    vector<vector<int>> testCase;

    // testing functions

    cout<<graph1.canFinishCourses(testCase)<<"\n"; // expected: true (or 1 in C++)

    testCase.push_back({0,0});

    cout<<graph2.canFinishCourses(testCase)<<"\n"; // expected: false (or 0)

    testCase.pop_back();
    testCase.push_back({0,1});
    testCase.push_back({1,2});
    testCase.push_back({2,4});
    testCase.push_back({2,3});
    
    cout<<graph3.canFinishCourses(testCase)<<"\n"; // expeceted: true 

    testCase.push_back({3,0});

    cout<<graph4.canFinishCourses(testCase)<<"\n"; // expected: false 

    // free memory

    graph1.deleteGraph();
    graph2.deleteGraph();
    graph3.deleteGraph();
    graph4.deleteGraph();
    
}
int main(){

    testing();

    return 0;

}