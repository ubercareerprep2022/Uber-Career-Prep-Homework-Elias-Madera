#include <bits/stdc++.h>
using namespace std;
/*

    Problem 4: Unique Paths II
    A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
    The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
    Now consider if some obstacles are added to the grids. How many unique paths would there be?

    The following approach assumes that the end and start can be obstacles and thus the answer for those cases should be 0.

    We first star tby checking if the given obstacle grid is a valid obstacle grid by verifying it is not empty.
    Define the ways to getTo the 0,0 position as 1 (which may be overwritten if the start is an obstacle by checking FIRST if it is an obstacle)
    Instead of returning a value after we calculate it, store it in a hashmap that uses the coordinates of the answer as a key {i,j} where i is the row and j is the column
    Calculate the answer with waysTo helper function of n-1,m-1

    For every waysTo call we check if we are out of bounds or an obstacle, in which cases we return 0.
    if we have previously computed the answer we return it, if we haven't, we compute it by calling the ways to get from the cell above and to the left of our current one.

*/
class UniquePathsSol{
    public:
        map<pair<int,int>,int> waysToGetTo;
        int waysTo(int i, int j, vector<vector<int>>& oG){

            if(i < 0 || j < 0) return 0; // are we out of bounds?
            if(oG[i][j]) return 0; // are we an obstacle?

            if(waysToGetTo.find({i,j}) == waysToGetTo.end()) // have we not computed the answer before?
                waysToGetTo[{i,j}] = waysTo(i-1,j,oG) + waysTo(i,j-1,oG); // then compute it and save it, not returning yet
            
            return waysToGetTo[{i,j}]; // return stored answer for this cell


        }
        int UniquePathsII(vector<vector<int>>& oG){

            if(!oG.size() || !oG[0].size()) return -1; // if there is an empty matrix or vector (invalid input)
            int n = oG.size(), m = oG[0].size();
            if(oG[n-1][m-1] || oG[0][0]) return 0; // if either start or end is an obstacle

            waysToGetTo[{0,0}] = 1; // default ways to get to the start

            waysToGetTo[{n-1,m-1}] = waysTo(n-1,m-1,oG); // store it in case we want to use it later.
            return waysToGetTo[{n-1,m-1}];

        }
};
void printMatrix(vector<vector<int>> matrix){

    if(!matrix.size() || !matrix[0].size()){

        cout<<"Invalid matrix";
        return;

    }

    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix[0].size(); ++j)
            cout<<matrix[i][j]<<" ";
        cout<<"\n";
    }

}
void testing(){

    vector<vector<int>> obstacleGrid{
        {0,0,0},
        {0,1,0},  // Generate example input
        {0,0,0}
    };

    UniquePathsSol Solution; 
    int res = Solution.UniquePathsII(obstacleGrid);
    cout<<"Answer to the grid: \n";
    printMatrix(obstacleGrid);
    cout<<"is: "<<res<<"\n";

}

int main(){

    testing();

    return 0;

}