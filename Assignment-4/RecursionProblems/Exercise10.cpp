#include <bits/stdc++.h>

/*

    Exercise 10 (Phone Number Letter Combinations)
    Given a string containing digits from 2 to 9 inclusive, write a function letterCombinations all possible letter combinations 
    that the number, digits,  could represent. Return the answer in any order. 

    The following solutions approaches the problem by going through the input string backwards, starting by the last character
    up to the first character, adding all the possible letters that characters brings to each word so far. The first round
    of letters are pushed to the output array, then a helper function is called to add the rest. This is done iteratively
    for every letter.

    This solution will at max use one (1) array of sizee (n) where n is the total number of combinations possible. As it
    re-uses the current array and updates its members AND pushes new ones to the back.

    If an invalid character is found in the input, skips that character, prints the error in console and skips that character.   

*/

class Solution{

public:

    std::string possible[10] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"}; // all characters represented by the ith number i.e. possible[i] holds all characters for 'ith' phone key

    void printArray(std::vector<std::string> array){

        for(auto& ele : array)
            std::cout<<" "<<ele;
        std::cout<<"\n";

    }

    std::vector<std::string> letterCombinations(std::string input){

        if(input.empty()) return {}; // handle if the string is empty
        int lastchar = std::atoi(&input[input.size()-1]);
        
        std::vector<std::string> output;
        for(int i = 0; i < possible[std::stoi(&input.back())].size(); ++i) // for every letter possible in using the last character of input
            output.push_back(std::string(1,possible[lastchar][i])); // push the very first letters possible with last element of input


        for(int i = input.size()-2; i >= 0; --i)
            helperAdd(input[i],output); // go backwards the input string
        return output;


    }
    void helperAdd(char next, std::vector<std::string>& output){

        if(std::atoi(&next) >= 2 && std::atoi(&next) <= 9){ // validate input
            int n = output.size(); // save size so when we push new possibilities we do not cycle back
            for(int i = 0; i < n; ++i){

                    
                    for(int j = 1; j < possible[std::atoi(&next)].size(); ++j) // for every current possibility, add the new possible combinations
                        output.push_back(possible[std::atoi(&next)][j] + output[i]);
                    output[i] = possible[std::atoi(&next)][0] + output[i]; // update root word with first possibility added to it, the rest will be on the back of the array

            }
        }else{

            std::cout<<"invalid input";
            return;

        }

    }
};
void testing(){ // testing function

    std::string input = "23"; // test input
    Solution sol;
    std::vector<std::string> output = sol.letterCombinations(input);
    sol.printArray(output); // expect output ["ad","ae","af","bd","be","bf","cd","ce","cf"]

}
int main(){

    testing();

    return 0;

}