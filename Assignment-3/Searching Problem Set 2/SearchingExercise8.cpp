#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 8: Bonus Question

// Given an array of size n and an integer k, return the count of distinct numbers in all windows of size k.

/*

    The approach that I used is to first count the first window of k elements, save the repetitions of the numbers in a hashmap,
    the size of the hashmap will represent the unique elements in the window. The next window can be viewed as moving our right
    pointer to the right and start pointer to the right, after doing so, we update our hashmap to consider one less iteration of
    the left-1 letter and consider one more iteration of the right+1 letter.

    A very importan thing to remember is to remove the key from our hashmap once it hits zero, since we cant to keep the map size as
    the number of dinstinct elements for the current window.

    Time complexity: O(n)
    Space complexity: O(n)

*/


int distinctNumsIn(vector<int>& array, int k){

    if(k == 0) return 0;
    int res = 0;
    unordered_map<int,int> inWindow;

    for(int i = 0; i < k; ++i)
        inWindow[array[i]]++;
    
    res+=inWindow.size();

    int s = 0, e = k-1;
    while(e+1 < array.size()){

        inWindow[array[++e]]++;
        if(--inWindow[array[s++]] == 0) inWindow.erase(array[s-1]);
        res+=inWindow.size();        

    }

    return res;

        

}
void printArray(vector<int>& array){

    cout<<"{ ";
    for(int i = 0; i < array.size(); ++i)
        cout<<" "<<array[i];

    cout<<"} ";

}
void generateInput(vector<int>& array, int n){

    for(int i = 0; i < n; ++i)
        array.push_back(rand()%15);

}
void testing(){

    srand(time(0));
    vector<int> array;
    int n = (rand()%10) + 10;
    int k = (rand()%100) % n;
    generateInput(array,n);

    cout<<"There are "<<distinctNumsIn(array,k)<<" distinct numbers in all windows sized "<<k<<" in the array "; printArray(array);

}
int main(){

    testing();

    return 0;

}