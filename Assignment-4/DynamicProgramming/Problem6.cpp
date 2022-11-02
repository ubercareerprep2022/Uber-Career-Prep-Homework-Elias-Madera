#include <bits/stdc++.h>
using namespace std;
/*

    Problem 6: 0-1 Knapsack
    Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. 
    In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items 
    respectively. Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that 
    sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item or don’t 
    pick it (0-1 property).

    This solution assumes that the input is given sorted by weights, and a subset can not contain repeated elements from the set it is
    a subset from.

    We will have a map of maps, using two keys, a weight and the values unlocked to compute the answer.
    Default the answers to using 0 weight or 0 values as 0.
    Then, for every value given, we will try to include it for every weight, if we can not, the solution with that unlocked value
    is the same as the not unlucked one.
    If we can include it, we get the maximum from the weight-currentWeight + current value, or the last (value not unlocked) answer.

    This way, we calculate for every weight and value the answer. Making the solution's time complexity O(W * N).
    where W is the weight and N the number of weights/values.

*/
class Solution{

public:

    map<int,map<int,int> > prev; // ans[weight][valuesUnlocked]

    Solution(){};

    int Knapsack(vector<int>& val, vector<int>& wt, int w){
    
        for(int i = 0; i <= w; ++i)
            prev[i][0] = 0;

        for(int i = 0; i < val.size(); ++i)
            prev[0][i] = 0;

        for(int i = 0; i < val.size(); ++i){

            for(int j = 1; j <= w; ++j){

                if(wt[i] <= j){ // if we can fit it

                    prev[j][i+1] = max(prev[j][i],prev[j-wt[i]][i] + val[i]); // calculate the possible answer

                }else{

                    prev[j][i+1] = prev[j][i]; // if we cant, re use previous answer.

                }

            }

        }

        return prev[w][val.size()]; // return the answer with W weight and all values unlocked.
        
    };


};
void testing(){

    vector<int> val {6,6,10,12,1};
    vector<int> wt  {1,1,2,3,4};

    Solution sol;
    cout<<sol.Knapsack(val,wt,5)<<"\n";

    // expected 24 [PASSED]

}
int main(){

    testing();

    return 0;

}