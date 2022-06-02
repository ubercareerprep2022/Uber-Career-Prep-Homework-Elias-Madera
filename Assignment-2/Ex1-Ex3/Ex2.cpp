#include <bits/stdc++.h>
using namespace std;

// [Trees - Ex2] Exercise: Printing a tree level by level

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

        printLevelByLevel():
        Prints the org level by level. First pushes all current level employees' direct reports to an auxiliary deque,
        then prints and pops each employee at the current level, after that pushes all of the current level employees'
        direct reports (that are already in the auxiliary deque) to the main deque, finally prints a blank line to separate
        the levels.
        
        free():
        Traverses de org breadth first freeing the memory of all the employees.

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

        // print org level by level

            org1->printLevelByLevel(); 
        
            /* expected output:
            
                Name: A, Title: CEO

                Name: B, Title: CFO
                Name: C, Title: CTO

                Name: I, Title: Director
                Name: D, Title: Manager
                Name: E, Title: Manager

                Name: J, Title: Sales Representative
                Name: F, Title: Engineer
                Name: G, Title: Engineer
                Name: H, Title: Engineer

                Name: K, Title: Sales Intern

            */

        // free memory
        
            org1->free();
            delete(org1);

}
int main(){

    testing();

    return 0;    
}