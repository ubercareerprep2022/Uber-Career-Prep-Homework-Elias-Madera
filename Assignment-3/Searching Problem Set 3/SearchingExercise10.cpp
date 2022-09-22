#include <bits/stdc++.h>
using namespace std;

// Searching Exercise 10: Valid Words

/*

    Given a dictionary and a character array, print all valid words that are possible using characters from the array.

    First, we create a hashmap with all the characters and repetitions we are able to use. Then go through all the dictionary words
    and check if the number of every character needed can be covered using the hashmap of the available characters, go through the whole array
    this way.

    Time complexity: O(n*k) where n is the size of the array and k the size of the words
    Space complexity: O(k)

*/

vector<string> getValidWords(vector<string>& dict, vector<char>& arr){

    unordered_map<char,int> have,current;
    vector<string> ans;
    bool valid = true;
    for(auto& character : arr)
        have[character]++;
    for(int i = 0; i < dict.size(); ++i){

        current.clear();
        valid = true;

        for(int j = 0; j < dict[i].size(); ++j){

            current[dict[i][j]]++;

        }
        for(auto& element : current){

            if(have[element.first] < element.second){

                valid = false;
                break;

            }

        }
        if(valid)
            ans.push_back(dict[i]);

    }

    return ans;

}
void testing(){

    vector<string> dict{"go","bat","me","eat","goal","boy","run"};
    vector<char> arr{'e','o','b','a','m','g','l'};

    vector<string> validWords = getValidWords(dict,arr);

    cout<<"All valid words are: \n";
    for(auto& word : validWords)
        cout<<" "<<word;
    cout<<"\n";
}
int main(){

    testing();

    return 0;

}