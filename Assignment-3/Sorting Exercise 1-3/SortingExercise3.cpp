#include <bits/stdc++.h>
using namespace std;
// Sorting Exercise 3: Sorted Merge 

/*
        You are given two sorted arrays, A and B, where A has a large enough buffer at the
    end to hold B. Write a method to merge B into A in sorted order in one pass and using O(1) space. 

    void mySort(vector<int>& arrayA, vector<int>& arrayB, int sizeA, int sizeB)
        takes two sorted arrays A and B, as well as the sizes of both arrays. Start the pointers from the end of each
        array, and start filling array A from the back with the greatest element from both pointers. Each interation we
        check if we have already used up all arrayA or arrayB, if so, we use the one that is not done yet.

        Time complexity: O(n)
        Space complexity: O(1)

    void printFinalArray(vector<int>& arrayA)
        helper function to print the final result of merging arrayA and arrayB.
    
        Time complexity: O(n)
        Space complexity: O(1)

    void checkInput(vector<int>& arrayA, vector<int>& arrayB,int sizeA, int sizeB)
        testing function to print the details of the (randomly) generated arrays A and B. prints their size in the console, as well
        as their contents in order to have a visual guide of the generating process.

    void testing()
        testing function to test the functions above. Also generates the size of A and B to guarantee that both are at least of size
        1 and A can fit B. This is to make generating the data simpler, but even if these conditions were not met, edge cases are covered.
        Fills the arrays with positive numbers from 0 to 100. Uses STL sorting to sort both arrays after generating them.

        calls mySort, printFinalArray and checkInput.

    
        

*/
void mySort(vector<int>& arrayA, vector<int>& arrayB, int sizeA, int sizeB){

    if(arrayA.size() < arrayB.size()) swap(arrayA,arrayB);

    int pointerA = sizeA - sizeB - 1, pointerB = sizeB - 1;
    for(int i = sizeA-1; i >= 0; --i){

        if(pointerA < 0) arrayA[i] = arrayB[pointerB--];
        else
        if(pointerB < 0) arrayA[i] = arrayA[pointerA--];
        else
        if(arrayA[pointerA] > arrayB[pointerB]) arrayA[i] = arrayA[pointerA--];
        else arrayA[i] = arrayB[pointerB--];

    }

}
void printFinalArray(vector<int>& arrayA){

    cout<<"Final ArrayA+ArrayB: \n";
    for(int i = 0; i < arrayA.size(); ++i)
        cout<<arrayA[i]<<" ";
    cout<<"\n";    

}
void checkInput(vector<int>& arrayA, vector<int>& arrayB,int sizeA, int sizeB){

    cout<<"ArrayA true size: "<<sizeA-sizeB<<" - total size: "<<sizeA<<"\n";
    cout<<"ArrayB size: "<<sizeB<<"\n";
    cout<<"ArrayA: \n";
    for(int i = 0; i < sizeA; ++i)
        cout<<arrayA[i]<<" ";
    cout<<"\n";
    cout<<"ArrayB: \n";
    for(int i = 0; i < sizeB; ++i)
        cout<<arrayB[i]<<" ";
    cout<<"\n";

}
void testing(){

    int sizeA, sizeB;

    srand(time(0));
    
    
    sizeB = (rand() % 50) + 1;
    sizeA = (rand() % 100) + 1 + sizeB;

    vector<int> arrayA, arrayB;

    for(int i = 0; i < sizeA; ++i)
        arrayA.push_back(rand() % 100);
    for(int i = sizeA-sizeB; i < sizeA; ++i)
        arrayA[i] = -1;
    for(int i = 0; i < sizeB; ++i)
        arrayB.push_back(rand() % 100);

    sort(arrayA.begin(),arrayA.begin()+sizeA-sizeB);
    sort(arrayB.begin(),arrayB.end());

    checkInput(arrayA,arrayB,sizeA,sizeB);

    mySort(arrayA,arrayB,sizeA,sizeB);

    printFinalArray(arrayA);

}
int main(){

    testing();

    return 0;

}