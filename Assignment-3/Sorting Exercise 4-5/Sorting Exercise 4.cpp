#include <bits/stdc++.h>
using namespace std;

// Sorting Exercise 4: Group Anagrams

/*

    This solution assumes the following:
        -The input array given is sorted.
        -K is a much smaller value than N
        -Anagrams NEED to be sorted within their anagram group
        -Order of the anagrams does not matter

    void performSort(vector<string>% inputArray)

        goes through the whole input array while sorting a copy of the current word to use as a key.
        pushes the word to the hashmap with that key.
        go through the input array again and replace original input with new input.

        Time complexity: O(n*k*log(k))
        Space complexity: O(n)

*/

vector<string> getInput(){

    vector<string> input;

    vector<string> group1{"ana","aan","naa"};
    vector<string> group2{"test","sett","estt","etst"};
    vector<string> group3{"uber","rube","ebur"};

    while(group1.size() || group2.size() || group3.size()){

        if(group1.size()){

            input.push_back(group1.back());
            group1.pop_back();

        }
        if(group2.size()){

            input.push_back(group2.back());
            group2.pop_back();

        }
        if(group3.size()){

            input.push_back(group3.back());
            group3.pop_back();

        }

    }

    sort(input.begin(),input.end());

    return input;

}
void performSort(vector<string>& inputArray){


    unordered_map<string,vector<string>> anagrams;
    string key;

    for(auto& word : inputArray){ // O(n*k*(log(k))

        key = word;
        sort(key.begin(),key.end()); // O(k*log(k))
        anagrams[key].push_back(word); // O(1)

    }
    int i = inputArray.size()-1;
    for(auto& key : anagrams){

        for(auto& word : key.second){

            inputArray[i--] = word;

        }

    }


}
void printArray(vector<string>& inputArray){

    for(int i = 0; i < inputArray.size(); ++i)
       cout<<inputArray[i]<<" ";

}
void testing(){

    vector<string> inputArray = getInput();
    performSort(inputArray);
    printArray(inputArray);

}
int main(){

    testing();

    return 0;

}
