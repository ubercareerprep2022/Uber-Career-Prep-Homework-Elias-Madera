#include <bits/stdc++.h>
using namespace std;
/*

    Problem 5: Minimum Path Sum
    Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
    
    Note: You can only move either down or right at any point in time.


    This solution assumes that negative numbers ( and answers are possible, and that the lower path (even if negative) should be the 
    correct answer ).

    We first start by verifying that our input is valid, if it is not, returns INT_MIN as fallback value.

    We will have a MinCostToMap to store previously computed values with a pair of integers as a key, the key being the index in the
    grid to which the answer belongs. We set the value of the trivial answer for 0,0 to be the grids value at 0,0. With the help of a helper
    function (MinCostTo) we retrieve the minimum cost to get to a coordinate.

    MinCostTo will check if the answer has been computed previously, if we havent, we compute it by getting the minimum from the top cell
    and left cell ( only two paths to current cell ) plus our current value. We do not return the answer immediately but rather store it
    in our MinCostToMap.

    MinimumPathSum returns the minimum path sum to get to the cell n-1,m-1.

*/
class MinimumPathSumSol{

    public:

        map<pair<int,int>,int> MinCostToMap; // Map to store the previously computed values

        int MinimumPathSum(vector<vector<int>>& grid){

            MinCostToMap.clear(); // make sure map is clear before starting

            if(!grid.size() || !grid[0].size()) return INT_MIN; // if input is invalid return INT_MIN as fallback value.

            MinCostToMap[{0,0}] = grid[0][0]; // trivial answer for [0,0] is their value.

            return MinCostTo(grid.size()-1,grid[0].size()-1,grid);

        }

        int MinCostTo(int i, int j, vector<vector<int>>& grid){

            if(i < 0 || j < 0) return INT_MAX; // if we are out of bounds default INT_MAX (use other available path )

            if(MinCostToMap.find({i,j}) == MinCostToMap.end()){

                MinCostToMap[{i,j}] = min(MinCostTo(i-1,j,grid),MinCostTo(i,j-1,grid)) + grid[i][j]; // if we have not computed the answer, it will be the lower from coming from our top and left plus our value.

            }
            
            return MinCostToMap[{i,j}]; // return stored answer, this way it can be reused in the future.

        }

};
void printGrid(vector<vector<int>>& grid){

    for(int i = 0; i < grid.size(); ++i){

        for(int j = 0; j < grid[0].size(); ++j){

            cout<<" "<<grid[i][j];

        }
        cout<<"\n";

    }

}
void testing(){

    vector<vector<int>> grid{
        {1,3,1},
        {1,5,1},                // create input grid
        {4,2,1},
    };

    MinimumPathSumSol Sol1;
    cout<<"Given the grid: \n";
    printGrid(grid);
    cout<<"The minimum path sum is : "<<Sol1.MinimumPathSum(grid)<<"\n"; // expected value 7 | PASSED

    vector<vector<int>> grid2{
        {1,-3,1},
        {1,-5,1},                // create input grid
        {4,-2,1},
    };

    cout<<"Given the grid: \n";
    printGrid(grid2);
    cout<<"The minimum path sum is : "<<Sol1.MinimumPathSum(grid2)<<"\n"; // expected value -8 | PASSED

}
int main(){

    testing();

}