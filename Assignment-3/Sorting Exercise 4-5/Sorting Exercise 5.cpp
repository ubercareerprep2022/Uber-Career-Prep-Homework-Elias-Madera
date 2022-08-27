#include <bits/stdc++.h>
using namespace std;

// Sorting Exercise 5: Peaks and Valleys

/*

    void merge() and void mergeSort() are my implementation of merge sort used to sort the array in non descending order.

        time complexity: O(n(log(n)))
        space complexity: O(n)

    void sortPeakValley(vector<int>& inputArray)
        takes an array of integers, calls for the merge sort on it and then takes the highest element from the array and stores
        it in a temporary array. Continues to alternate between minimum and maximum unused values.

        time complexity: O(n(log(n)))
        space complexity: O(n)

    void printArray(vector<int>& inputArray)
        takes an array and prints it into console.

*/

void merge(vector<int>& inputA, int start, int mid, int end){

    int left = start, right = mid+1;

    vector<int> temp(end-start+1);

    for(int i = start, k = 0; i <= end; ++i, ++k){

        if(left >= mid+1) temp[k] = inputA[right++];
        else if(right >= end+1) temp[k] = inputA[left++];
        else if(inputA[left] < inputA[right]) temp[k] = inputA[left++];
        else temp[k] = inputA[right++];

    }

    for(int i = start; i <= end; ++i)
        inputA[i] = temp[i-start];

}
void mergeSort(vector<int>& inputA, int start, int end){

    if(end <= start) return;

    int mid = start + (end-start) / 2;
    mergeSort(inputA,start,mid);
    mergeSort(inputA,mid+1,end);

    merge(inputA,start,mid,end);

}
void sortPeakValley(vector<int>& inputArray){

    mergeSort(inputArray,0,inputArray.size()-1);
    vector<int> temp;
    for(int i = 0,j=inputArray.size()-1; i <= j;){

        temp.push_back(inputArray[j--]);
        if(i+1 <= j)
            temp.push_back(inputArray[i++]);

    }

    inputArray = temp;

}
void printArray(vector<int>& inputArray){

    for(int i = 0; i < inputArray.size(); ++i){

        cout<<inputArray[i]<<" ";

    }cout<<"\n";

}
void testing(){

    // testing functions:

     vector<int> inputArray{5,1,2,3,3};
     sortPeakValley(inputArray);
     printArray(inputArray);

        // expected output: 5 1 3 2 3

     inputArray = {8,2,3,4,4,5,2,3};
     sortPeakValley(inputArray);
     printArray(inputArray);

        // expected output: 8 2 5 2 4 3 4 3

}
int main(){

    testing();

    return 0;

}
