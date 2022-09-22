#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 6: Find if subset

/*
    The idea is to go through the whole array 1 and insert the elements of it into a hashset. Then, go through the whole array 2 and 
    check that for every element in array 2 there it exists in the hashset of existing elements in array 1. If all elements of array 2
    are present in array 1, array 2 is a subset of array1.

    Time complexity: O(n+m) where n and m are the sizes of the arrays
    Space complexity: O(n+m)
*/

bool isSubset(vector<int>& array1, vector<int>& array2){

    unordered_set<int> a1Has;

    for(auto& element : array1)
        a1Has.insert(element);
    
    for(auto& element : array2){

        if(a1Has.find(element) == a1Has.end()) return false;

    }

    return true;

}
void generateInput(vector<int>& array1, vector<int>& array2){

    unordered_set<int> inArray;
    int n;
    for(int i = 0; i < 8; ++i){

        n = rand()%10;
        while(inArray.find(n) != inArray.end()){

            ++n;
            n%=10;

        }
        array1.push_back(n);
        inArray.insert(n);
        
    }
    inArray.clear();
    for(int i = 0; i < 3; ++i){

        n = rand()%10;
        while(inArray.find(n) != inArray.end()){

            ++n;
            n%=10;

        }
        array2.push_back(n);
        inArray.insert(n);
        
    }
        

}
void printArray(vector<int>& array){

    cout<<"{";
    for(auto& element : array)
        cout<<" "<<element;
    cout<<"}";
    cout<<"\n";

}
void testing(){

    srand(time(0));
    vector<int> array1;
    vector<int> array2;
    generateInput(array1,array2);
    cout<<"array2"; printArray(array2); cout<<"is "; if(!isSubset(array1,array2)) cout<<"NOT "; cout<<"a subarray of array1"; printArray(array1);
    

}
int main(){

    testing();

    return 0;

}