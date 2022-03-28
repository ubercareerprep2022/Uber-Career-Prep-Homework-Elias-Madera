#include <bits/stdc++.h>
using namespace std;
void printArray(vector<pair<int,int> > Example){

    /*

    Function that takes a vector of pairs of integers and prints it in the console.

    */

    cout<<"Output array: [";
    while(!Example.empty()){

        cout<<"("<<Example.back().first<<", "<<Example.back().second;
        if(Example.size() > 1){

            cout<<"), ";

        }else{

            cout<<")";

        }
        Example.pop_back();

    }
    cout<<"]"<<endl<<endl;

}
vector<pair<int,int> > pairsThatEqualSum(vector<int> inputArray, int targetSum){

    /*

    Function hat takes an array of integers and a target integer and returns an array of pairs (i.e., an array of tuples)
    where each pair contains two numbers from the input array and the sum of each pair equals the target integer.

    The following solution assumes:

    1.-Data fits in an integer variable.
    2.-Only a unique pair is counted as a solution/sum of the target integer.
    3.-A pair (a,b) is not different from pair (b,a).

    */

    sort(inputArray.begin(),inputArray.end());

    int inputArraySize = inputArray.size();
    int start = 0;
    int end = inputArraySize-1;
    vector<pair<int,int> > outputArray; // vector of pairs of integers to store the answer pairs

    // go through the input array and check if first + last position = 'targetSum'

    while(start < end){

        if(inputArray[start]+inputArray[end] == targetSum){
            
            if(!outputArray.size()){ // if there are no pairs so far, push back pair to 'outputArray'

                outputArray.push_back({inputArray[start],inputArray[end]});

            }else{

                if((outputArray.back().first != inputArray[start]) && (outputArray.back().second != inputArray[end])){ // if there is, check if the answer is already in vector before pushing back

                    outputArray.push_back({inputArray[start],inputArray[end]});

                }

            }
            --end;

        }else{

            if(inputArray[start]+inputArray[end] > targetSum){ // if current sum is higher than 'targetSum', move end to the left to get next lowest sum

                --end;

            }else{ // if current sum is lower than 'targetSum', move start to the right to get next highest sum

                ++start;

            }

        }

    }

    // time complexity: O(nlog(n)) | "n" = size of inputArray
    // space complexity: O(n)

    return outputArray;

}
bool isStringPermutation(string str1, string str2){

    /*

    Function hat takes two Strings as parameters and returns a Boolean denoting
    whether the first string is a permutation of the second string.

    The following solution assumes:

    1.-String1 is a permutation of String2 if all elements in String1 are also in String2.
    2.-String1 does not need to have all elements of String2 to be a permutation.
    3.-Repeated elements/letters in String1 must appear at least the same amount of times in String2 to be a permutation.
    4.-An empty String1 is a permutation of String2
    5.-Uppercase letters are considered different from their lowercase counterparts.

    */

    bool ans = true; // bool variable for storing the answer to return
    map<char,int> str2Elements; // map that contains all elements in 'str2' and their repetitions
    int str1Size, str2Size;

    str1Size = str1.size();
    str2Size = str2.size();

    // for each appearance of all elements of 'str2', add 1 to the map value of that element's key 
    
    for(int i = 0; i < str2Size; ++i){

        ++str2Elements[str2[i]];

    }

    // go thorugh the first string and check if the map value for that element's key is greater than 0, if it is, remove 1 from the value
    // if value is 0, element is present in 'str1' more times than in 'str2', therefore, it can't be a permutation

    for(int i = 0; i < str1Size; ++i){

        if(str2Elements[str1[i]] > 0){

            --str2Elements[str1[i]]; 

        }else{ 

            ans = false; 

        }

    }

    // time complexity: O(nlog(n)) | "n" = maximum between the size of 'str1' and 'str2'
    // space complexity: O(n)

    return ans; // since c++ handles booleans as "0" or "not 0", the function will return "0" if false or "1" if ture
}
void testingExamples(){

    cout<<"isStringPermutation:"<<endl;
    cout<<"'asdf', 'fsda': "<<isStringPermutation("asdf","fsda")<<endl;
    cout<<"'asdf', 'fsa': "<<isStringPermutation("asdf","fsa")<<endl;
    cout<<"'asdf', 'fsax': "<<isStringPermutation("asdf","fsax")<<endl;
    cout<<"'', 'aaaa': "<<isStringPermutation("","aaaa")<<endl;
    cout<<"'aaa', 'a': "<<isStringPermutation("aaa","a")<<endl;
    cout<<"'', '': "<<isStringPermutation("","")<<endl;
    cout<<"'abc', 'abcde': "<<isStringPermutation("abc","abcde")<<endl<<endl;

    cout<<"pairsThatEqualSum:"<<endl;
    cout<<"Input array: [1,2,3,4,5], target sum: 5"<<endl;
    vector<pair<int,int> > Example = pairsThatEqualSum({1,2,3,4,5},5);
    printArray(Example);
    cout<<"Input array: [1,1,2,2,3,3,4,4,5,5], target sum: 7"<<endl;
    Example = pairsThatEqualSum({1,1,2,2,3,3,4,4,5,5},7);
    printArray(Example);
    cout<<"Input array: [-1,2], target sum: 1"<<endl;
    Example = pairsThatEqualSum({-1,2},1);
    printArray(Example);
    cout<<"Input array: [1,2,3], target sum: 0"<<endl;
    Example = pairsThatEqualSum({1,2,3},0);
    printArray(Example);
    cout<<"Input array: [3,3,4,4], target sum: 6"<<endl;
    Example = pairsThatEqualSum({3,3,4,4},6);
    printArray(Example);



}
int main(){

    testingExamples();

    return 0;
}