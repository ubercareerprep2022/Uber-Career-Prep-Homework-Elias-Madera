#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 7: Determine two elements sum X

/*
    This solution uses the aproach of remembering past received elements and checking if we have received the counterpart to our current
    number that it would take in order to get X.

    If our current number is Y, then for every instance of Y we check if we have received X-Y before. This can be done via a hashmap.

    Time complexity: O(n)
    Space complexity: O(n)

*/

bool twoElementsSumX(vector<int>& arrayA, int x){

    unordered_map<int,int> items;
    for(auto& element : arrayA){

        items[element]++;
        if(items[x-element])
            return true;

    }
    return false;
}
void generateInput(vector<int>& array, int n){

    for(int i = 0; i < n; ++i)
        array.push_back(rand()%10);

}
void printArray(vector<int>& array){

    cout<<"{";
    for(auto& element : array)
        cout<<" "<<element;
    cout<<"} \n";

}
void testing(){

    srand(time(0));

    vector<int> arrayA;
    int x = rand()%10,n = (rand()%10)+10;

    generateInput(arrayA,n);

    cout<<"array A"; printArray(arrayA); cout<<"does "; if(!twoElementsSumX(arrayA,x)) cout<<"NOT "; cout<<"contain two numbers that sum to "<<x<<"\n";


}
int main(){

    testing();

    return 0;

}