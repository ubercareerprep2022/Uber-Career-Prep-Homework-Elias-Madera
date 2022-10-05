#include <bits/stdc++.h>

// Exercise 8 (Well-formed Parentheses)

/*

    This solution approaches the problem by considering the two cases for any string of correct parentheses.
    1.- We may have parentheses available to open
    2.- We do not have parentheses available to open

    So we have our current string, and int canOpen, canClose and the output vector.
    We check if the current string can open the parentheses
    Then check if we can close a parantheses
    Then check if we can't open or close (we are done) and push the answer.

    Call the function recursively for every case.


*/

class Solution{

    public:

        
        static void WellFormedParentheses(std::string curr, int canOpen, int canClose, std::vector<std::string>& answer){

            if(canOpen) WellFormedParentheses(curr+"(",canOpen-1,canClose+1,answer);
            if(canClose) WellFormedParentheses(curr+")",canOpen,canClose-1,answer);

            if(!canOpen && !canClose){

                answer.push_back(curr);
                return;

            } 

        }

};
void printArray(std::vector<std::string> array){

    for(auto& ele : array)
        std::cout<<" '"<<ele<<"' ";
    std::cout<<"\n";

}
void testing(){

    
    int n = 3;
    std::vector<std::string> answer;
    Solution::WellFormedParentheses("",n,0,answer);
    printArray(answer);

}
int main(){

    
    testing();

    return 0;

}