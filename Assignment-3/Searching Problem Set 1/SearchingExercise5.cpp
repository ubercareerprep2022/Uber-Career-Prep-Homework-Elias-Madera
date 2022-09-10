#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 5: Search value in mxn Matrix

/*

    This solution is an efficient algorithm to determine if a value is present in a sorted matrix where every value of the row is greater
    than the last value of that row and each value of the column is greater than the last value of that column.

    First start at the top right of the matrix, or i = 0 and j = columns-1. Then, compare the value to our target value, if we find it,
    return true. If our value is lower than the target value, we will want to move 'up' the row i++ since that will be a greater value.
    If we are higher than our target value, we will want to move a column 'down' --j, to get the next lower value.

    Do this until we either find the target value or fall out of bounds, in which case we can return false.

    The solution assumes the matrix is sorted and non empty.

    Time complexity: O(n+m)
    Space complexity: O(1)

*/
void generateInput(vector<vector<int>>& matrix){

    vector<int> row;
    row.push_back(rand() % 10);

    int rows = rand() % 6, columns = (rand() % 10) + 1;
    for(int i = 0; i < columns; ++i)
        row.push_back(row.back()+rand()%5);
    int j = 0;
    matrix.push_back(row);
    for(int i = 0; i < rows; ++i){

        row.clear();
        row.push_back(matrix[j][0]+rand()%5);
        for(int k = 1; k < matrix[0].size(); ++k)
            row.push_back(max(matrix[j][k],row.back())+(rand()%3));
        ++j;
        matrix.push_back(row);

    }


}
void printMatrix(vector<vector<int>>& matrix){

    for(int i = 0; i < matrix.size(); ++i){
        for(int j = 0; j < matrix[0].size(); ++j)
            cout<<" "<<matrix[i][j];
        cout<<"\n";
    }

}
bool searchValue(vector<vector<int>>& matrix, int target){

    int i = 0, j = matrix[0].size()-1;
    while(i < matrix.size() && j >= 0){

        if(matrix[i][j] == target) return true;
        if(matrix[i][j] < target) ++i;
        else --j;

    }

    return false;

}
void testing(){

    srand(time(0));
    vector<vector<int>> matrix;
    generateInput(matrix);
    printMatrix(matrix);
    int target = rand() % 25;
    cout<<"Target: "<<target<<" is "; if(!searchValue(matrix,target)) cout<<"NOT "; cout<<"in the matrix\n";



}
int main(){

    testing();

    return 0;

}