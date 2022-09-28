#include <bits/stdc++.h>

/*

A binary tree is height-balanced if for every node, the depths of the two subtrees never differ by more than one.
Given an integer array nums that is sorted in ascending order, convert it into a height-balanced binary search tree.

generateInput()
    generates the input array of random non descending order.
HeightBST
    first starts at the middle element, adds it to the array, then pushes to the queue the left sub array and right subarray
    in order to do it recursively. Pushes the middle value for every case. In case where the left pointer is greater
    than the right pointer, push INT_MIN. IN_MIN will later be printed as null
printArray
    prints an array of elements, if an element is INT_MIN, prints null
testing()
    calls the functions generate input, HeightBST and prints array.

*/
std::vector<int> generateInput(){

    std::vector<int> ans;
    ans.push_back(rand() % 10);
    for(int i = 0; i < 6; ++i)
        ans.push_back(ans.back() + rand()%10);

    return ans;

}
std::vector<int> HeightBST(std::vector<int>& input){

    std::vector<int> ans;
    std::queue<std::pair<int,int>> toadd;
    int mid,s,e;
    for(toadd.push({0,input.size()-1}); !toadd.empty() ; toadd.pop()){


        s = toadd.front().first;
        e = toadd.front().second;
        if(s > e){
          ans.push_back(INT_MIN);
          continue;
        }
        mid = (s+e)/2;
        ans.push_back(input[mid]);

        toadd.push({s,mid-1});
        toadd.push({mid+1,e});

    }

    return ans;

}
void printArray(std::vector<int>& input){

    for(auto& element : input)
        if(element == INT_MIN) std::cout<<" NULL";
        else std::cout<<" "<<element;
    std::cout<<"\n";

}
void testing(){

    srand(time(0));
    std::vector<int> input = generateInput();
    printArray(input);
    std::vector<int> output = HeightBST(input);
    printArray(output);

}
int main(){

    testing();

    return 0;

}
