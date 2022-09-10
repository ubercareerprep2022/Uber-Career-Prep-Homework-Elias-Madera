#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 4: Median of Sorted Arrays

/*

    This solution assumes none of the arrays are empty. The idea of the algorithm is to try the possibilities of dividing the arrays
    for the median. Given that two arrays with total size 10, will have a median in the 4th index, which is the total size / 2 floored.

    This way we first try with the half of the smaller array, and check if we have a found the correct 'cut' in the array. If we have, we
    return the median which will be the maximum of the left pointers of the cut of the two arrays and the minimum of the right pointers.

    If we have not found a correct cut, we will decide to take either more or less items from the smaller array. If the cut value
    of the small array is greater than the right value of the second array, we will take less items from the array, thus making the end
    equal to our cut - 1.
    Else we will want to take more elements, thus making our start our cut + 1.
    There will always be a median to the arrays so keep the algorithm running until we find our currect cut (or we hit a bound of the small array)
    in which case we will get INT_MAX or INT_MIN values that will complete our conditionals.

    Time complexity: O(log(n+m)) where n and m are the sizes of the arrays
    Space complexity: O(1)

*/

int floorD(int a, int b) {
    int d = a / b;


    return d * b == a ? d : d - ((a < 0) ^ (b < 0));
}
void generateInput(vector<int>& array){

    array.push_back(rand()%100);
    int size = rand()%3;
    for(int i = 0; i < size; ++i)
        array.push_back(array.back()+(rand()%10));

}
double getMedianOfArray(int start, int end, vector<int>& array){

    double median = 0;

    median+=array[(start+end)/2];
    if((end-start)+1 % 2 == 0){
        median+=array[((start+end)/2)+1];
        median/=2;
    }

    return median;

}
void printArray(vector<int>& array,int start, int end){

    for(int i = start ; i <= end; ++i)
        cout<<" "<<array[i];
    cout<<"\n";

}
double findMedian(vector<int>& array1, vector<int>& array2){

    if(getMedianOfArray(0,array1.size()-1,array1) == getMedianOfArray(0,array2.size()-1,array2)) return getMedianOfArray(0,array2.size()-1,array2);

    int size = array1.size() + array2.size();

    if(array1.size() > array2.size())
        swap(array1,array2);

    int s = 0, e = array1.size()-1, m, m2;
    int left1,right1,left2,right2;

    while(true){

        m = floorD((s+e),2);
        m2 = (floorD(size,2))-m-2;

        left1 = (m >= 0) ? array1[m] : INT_MIN;
        right1 = (m+1 < array1.size()) ? array1[m+1] : INT_MAX;
        left2 = (m2 >= 0) ? array2[m2] : INT_MIN;
        right2 = (m2+1 < array2.size()) ? array2[m2+1] : INT_MAX;

        if(left1 <= right2 && left2 <= right1){

            if(size % 2)
                return min(right1,right2);
            else
                return (double)(max(left1,left2)+min(right1,right2)) / (double)2;
            

        }else if(left1 > right2)
        e = m-1;
        else s = m+1;

    }

}
void testing(){

    srand(time(0));
    vector<int> array1,array2;
    generateInput(array1);
    generateInput(array2);
    cout<<"Array 1: \n"; printArray(array1,0,array1.size()-1);
    cout<<"Array 2: \n"; printArray(array2,0,array2.size()-1);
    cout<<findMedian(array1,array2);

}
int main(){

    testing();

    return 0;

}