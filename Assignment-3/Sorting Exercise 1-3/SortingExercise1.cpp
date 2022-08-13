#include <bits/stdc++.h>
using namespace std;

// Sorting Exercise 1: Three Partition Sort

/*
    Given an Array [5, 10, 5, 20, 5, 5, 10], sort them in a single pass.

    Three Partition Sort bases of Quicksort, using swaps to divide the array in three partitions using a pivot.

    void tpdiv(vector<int>& array, int start, int end)
        takes the array to sort and performs the swaps to get three subarrays, where the left subarray holds
        the elements lower than the pivot, the right subarary holds the elements that are greater than the pivot
        and the mid subarray holds the elements that are equal to the pivot. Then performs this recursively to both the
        left and right subarrays.

        Time complexity: O(n^2)
        Space complexity: O(1)
    
    void tpsort(vector<int>& array, int start, int end, int& left, int& right)
        takes the subarray from 'tpdiv' and performs the series of swaps, leaving all elements lower than de pivot on the
        left, and all elements higher, on the right.
    
    void testing()
        function to test above functions.

        

*/
void tpsort(vector<int>& array, int start, int end, int& left, int& right){

    int pivot = array[start];
    left = start, right = end;

    for(int i = left+1 ; i <= end; ++i)
        if(array[i] < pivot)
            swap(array[i],array[left++]);
        else if(array[i] > pivot)
            swap(array[i--],array[right--]);

}
void tpdiv(vector<int>& array, int start, int end){

    if(end <= start) return;
    int left,right;
    tpsort(array,start,end,left,right);
    tpdiv(array,start,--left);
    tpdiv(array,++right,end);


}
void testing(){

    vector<int> array{5,10,5,20,5,5,10}; 

    tpdiv(array,0,array.size()-1);

    for(int i = 0; i < array.size(); ++i) // printing to console
        cout<<array[i]<<" ";
    cout<<"\n";

    // expected output:

    // [5 , 5 , 5 , 5 , 10 , 10 , 20]
    
}
int main(){

    testing();

    return 0;

}