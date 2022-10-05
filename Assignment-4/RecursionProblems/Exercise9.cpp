#include <bits/stdc++.h>

// Exercise 9 (Collatz Conjecture)

/*

    This solution approaches the problem by going through every number between low inclusive and high inclusive, and calls
    for the helper function. Then, we check if our current number has been reached (or looked for) before. If it is not present
    in our 'prev' hashmap, it has not. So we calculate the answer and move to the next number (divide by two or apply formula if odd).

    Then, save the answer and return the prev value of the hashmap corresponding to the number.

*/

class Solution{

    public:

        std::vector<std::pair<int,int>> CollatzConjecture(int low, int high, std::vector<std::pair<int,int>>& output){

            if(low > high){

                std::swap(low,high);
                CollatzConjecture(low,high,output);

            }

            for(int i = low; i <= high; ++i){

                int steps = helper(i);
                output.push_back({steps,i});

            }



        }

        std::unordered_map<int,int> prev;

        int helper(int i){

            if(i == 1) return 0;

            if(prev.find(i) == prev.end()){

                prev[i] = (i % 2 == 0) ? helper(i/2)+1 : helper(3*i+1)+1;

            }

            return prev[i];
            

        }


};
void printArrayElement(std::vector<std::pair<int,int>>& array,int k){

    if(k >= array.size() || k < 0) return;
    std::cout<<array[k-1].second<<"\n";

}
void testing(){

    Solution example;
    std::vector<std::pair<int,int>> array;
    
    example.CollatzConjecture(12,15,array);
    std::sort(array.begin(),array.end());
    int k = 2;
    printArrayElement(array,k);

}
int main(){

    testing();

    return 0;

}