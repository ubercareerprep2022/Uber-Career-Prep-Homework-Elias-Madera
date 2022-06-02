#include <bits/stdc++.h>
using namespace std;

// [Trees - Ex3] Exercise: Printing the number of levels

// Employee class with constructor

class Employee{

    public:

        string name;
        string title;
        vector<Employee*> directReports;
        Employee(string name, string title){

            this->name = name;
            this->title = title;

        }


};

/* OrganizationStructure class with constructor

        printNumLevels():

        Traverses the org level by level by pushing of all the current level employees' direct reports to an auxiliary deque,
        pops them of the main deque, and adds 1 to the 'levels' value (current level), after that, pushes the auxiliary deque
        (which has the next level's employees) to the main deque.

        Time complexity: O(n) where n is the total number of employees in the org
        Space complexity: O(n) where n is the total number of employees in the org

*/

class OrganizationStructure{

    public:

        Employee* ceo;
        OrganizationStructure(Employee* ceo){

            this->ceo = ceo;

        }
        void printLevelByLevel(){

            deque<Employee*> toVisit,nextToVisit;
            
            if(!ceo){

                return;

            }
            toVisit.push_back(ceo);
            while(!toVisit.empty()){

                while(!toVisit.empty()){

                    for(int i = 0; i < toVisit.front()->directReports.size(); ++i){

                        nextToVisit.push_back(toVisit.front()->directReports[i]);

                    }

                    cout<<"Name: "<<toVisit.front()->name<<", Title: "<<toVisit.front()->title<<"\n";
                    toVisit.pop_front();

                }
                cout<<"\n";
                while(!nextToVisit.empty()){

                    toVisit.push_back(nextToVisit.front());
                    nextToVisit.pop_front();

                }
                
                

            }


        }
        void free(){

            queue<Employee*> toVisit;
            if(!ceo){

                return;

            }
            toVisit.push(ceo);
            while(!toVisit.empty()){

                for(int i = 0; i < toVisit.front()->directReports.size(); ++i){

                    toVisit.push(toVisit.front()->directReports[i]);

                }
                delete(toVisit.front());
                toVisit.pop();

            }

        }
        void printNumLevels(){

            deque<Employee*> toVisit,nextToVisit;
            int levels = 0;
            
            if(!ceo){

                cout<<levels<<"\n";
                return;

            }
            toVisit.push_back(ceo);
            while(!toVisit.empty()){

                while(!toVisit.empty()){

                    for(int i = 0; i < toVisit.front()->directReports.size(); ++i){

                        nextToVisit.push_back(toVisit.front()->directReports[i]);

                    }

                    toVisit.pop_front();

                }
                ++levels;
                while(!nextToVisit.empty()){

                    toVisit.push_back(nextToVisit.front());
                    nextToVisit.pop_front();

                }
                
                

            }
            cout<<levels<<"\n";

        }

};
void testing(){

    // creating org and employees

    Employee* K = new Employee("K","Intern");

    Employee* J = new Employee("J","Sales Representative");
    J->directReports.push_back(K);
    Employee* F = new Employee("F","Engineer");
    Employee* G = new Employee("G","Engineer");
    Employee* H = new Employee("H","Engineer");
    
    Employee* I = new Employee("I","Director");
    I->directReports.push_back(J);
    Employee* D = new Employee("D","Manager");
    D->directReports.insert(D->directReports.end(),{F,G,H});
    Employee* E = new Employee("E","Manager");

    Employee* B = new Employee("B","CFO");
    B->directReports.push_back(I);
    Employee* C = new Employee("C","CTO");
    C->directReports.insert(C->directReports.end(),{D,E});

    Employee* A = new Employee("A","CEO");
    A->directReports.insert(A->directReports.end(),{B,C});

    OrganizationStructure* org1 = new OrganizationStructure(A);

    // testing functions

        // print number of levels
            cout<<"Structure of the org: \n";
            org1->printLevelByLevel(); // print tree for visualization
            cout<<"Number of levels in the org: "; 
            org1->printNumLevels(); // expected output: 5

        // free memory
        
            org1->free();
            delete(org1);

}
int main(){

    testing();

    return 0;    
}