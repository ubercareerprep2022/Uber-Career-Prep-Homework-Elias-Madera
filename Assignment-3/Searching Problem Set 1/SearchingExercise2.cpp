#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 2: Find Element

/*

    The solution assumes that the input is not empty, if it is, returns the fallback value of '-1'.
    Looks for the target value in a sorted rotated array. Starts of by testing if the mid point of the current subarray is the target,
    if it is, returns the INDEX of the value, if it is not, checks if the left subarray from start to mid is sorted and the value is in those
    values, goes to the left, if left is sorted but target not inbounds of those values goes to the opposite side. Checks for the same condition
    to the right.

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
int findElement(vector<int>& inputData, int target){

    int s = 0, e = inputData.size()-1, mid;
    while(s <= e){

        mid = s + (e-s)/2;

        if(inputData[mid] == target) return mid;

        if(inputData[s] <= inputData[mid])
            if(target >= inputData[s] && target <= inputData[mid])
                e = mid-1;
            else s = mid+1;
        else
            if(target >= inputData[mid] && target <= inputData[e])
                s = mid+1;
            else e = mid-1;
    }

    return -1;

}
void printArray(vector<int>& inputData){

    for(auto& element : inputData)
        cout<<" "<<element;
    cout<<"\n";

}
void testing(){

    vector<int> inputData = generateData();
    int target = inputData[rand()%10];
    cout<<"The array: "; printArray(inputData);
    cout<<"Found target: "<<target<<" at position: "<<findElement(inputData,target)<<"\n";

}
int main(){

    testing();

    return 0;

}