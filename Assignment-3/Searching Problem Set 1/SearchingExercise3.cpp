#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 3: Implement pow(x, n)

/*

    This solution assumes that the exponents are integers and can be negative values.
    Go through the N value and decompose it in smaller x^ exponents where the exponents are multiples of 2, so 10 would be
    2^2 * 2^8. One way to figure this out is going through the bits of the N number, in this case 1010 and if a bit is on that means
    the answer should multiply times that value of exponent. Do this until we are done with the absolute value of n. If n was negative, then
    return 1/pow(x,N) which is the answer we calculated, without a need of recalculation.

    Time complexity: O(log2(n))
    Space complexity: O(1)

*/

double myPow(int x, int n){

   double ans = 1;
   long long absn = abs(n);
    while(absn > 0){


        if(absn % 2) ans*=x;
        x *= x;
        absn/=2;

    }
    if(n < 0) return (double)1/ans;
    else return ans;

}
void testing(){

    int x,n;
    x = 2;
    n = 3;
    cout<<myPow(x,n);

}
int main(){

    testing();

    return 0;

}