#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 1: Find Minimum

/*

    This solutions assumes the inputData array is not empty, and looks for the minimum value in a sorted rotated array.
    First check if our current subarray is already sorted, if it is, we return the minimum of the start of value of current
    subarray and the minimum value so far seen.
    Else we compare the mid point value with the start, if the elements are sorted to the left, the pivot must be in the right half,
    as if it were in the left side, it would not be sorted. After moving the start or end of our subarray, continue looking for the minimum.

    Time complexity: O(log(n))
    Space complexity: O(1)

*/
vector<int> generateData(){

    srand(time(0));

    vector<int> data,temp;
    int pivot = rand() % 10;
    data.push_back(rand() % 100);

    for(int i = 0; i < 9; ++i)
        data.push_back((rand() % 100)+data.back());
    
    temp = data;

    for(int i = 0; i < 10; ++i)
        data[(i+pivot)%10] = temp[i];
    

    return data;

}
int findMin(vector<int>& inputData){

    int s = 0, e = inputData.size()-1, mid;
    int ans = INT_MAX;

    if(inputData.empty()){

        cout<<"Input array is empty \n";
        return -1;

    }

    while(s <= e){

        mid = s + (e-s)/2;
        ans = min(ans,inputData[mid]);

        if(inputData[s] <= inputData[e])
            return min(ans,inputData[s]);
        
        if(inputData[mid] < inputData[s])
            e = mid-1;
        else s = mid+1;

    }

}
void printArray(vector<int>& inputData){

    for(auto& element : inputData)
        cout<<" "<<element;
    cout<<"\n";

}
void testing(){

    vector<int> inputData = generateData();
    cout<<"The array:"; printArray(inputData);
    cout<<"has the minimum value: "<<findMin(inputData);

}
int main(){

    testing();

    return 0;

}