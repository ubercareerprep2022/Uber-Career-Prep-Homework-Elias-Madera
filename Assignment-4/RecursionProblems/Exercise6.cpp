#include <bits/stdc++.h>

/*

    You are climbing a staircase. It takes n steps to reach the top. Each time you can either climb 1 or 2 steps

    long long climbStairs1(int n)
        Takes the input of the n step, and returns the ways to reach it. This solution assumes it takes 0 steps to reach step 0, as there
        is no way of taking 1 or 2 steps to reach 0. Solution 1 uses non optimized recursion, for the value of climbStairs1(n) computes
        climbStairs1(n-1) and climbStairs2(n-2) recursively. This is repeats computations.

        Time complexity: O(2^n)
        Space complexity: O(n)

        we can optimize it by using memoization, saving the answer to the N case every time we compute it. This would lower the time
        complexity to: O(n)

    long long climbStairs2(int n)
        Takes the input of the n step, and return they ways to reach it. This solution assumes it takes 0 steps to reach step 0, as there
        is no way of taking 1 or 2 steps to reach step 0. Solution 2 uses a space and time optimized solution. We only save the past and past
        the past answers to our N case, starting at 1. We then add the two values and save it in a temp value. Then update past and past past
        values.

        finally, return temp value which stores the current answer for the N case.

        Time complexity: O(n)
        Space complexity: O(1)

    This program also counts the time it takes for each solution to compute the answer. For n = 40, solution 1 takes 500 milliseconds and solution 2 takes 0
    microseconds.

*/

long long climbStairs1(unsigned int n){

    // base cases

    if(n == 0) return 0;
    if(n == 1) return 1;
    if(n == 2) return 2;

    // a(n) = a(n-1) + a(n-2)

    return climbStairs1(n-1)+climbStairs1(n-2);


}
long long climbStairs2(unsigned int n){

    // base case

    if(n == 0) return 0;

    long long p1 = 0,p2=1,temp;

    for(int i = 1; i <= n; ++i){

        temp = p1+p2; // current is = past + past past.
        p1 = p2; // past = current
        p2 = temp; // past past = past

    }

    return temp;

}
void testing(){

    auto start = std::chrono::high_resolution_clock::now();

    std::cout<<"climbStairs1(40) : "<<climbStairs1(40)<<"\n";

    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start);

    std::cout<<"Recursion one took: "<<duration.count()<<" milliseconds\n";

    start = std::chrono::high_resolution_clock::now();

    std::cout<<"climbStairs2(40) :  "<<climbStairs2(40)<<"\n";

    finish = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

    std::cout<<"Recursion two took: "<<duration2.count()<<" microseconds\n";

}
int main(){

    testing();

    return 0;

}
