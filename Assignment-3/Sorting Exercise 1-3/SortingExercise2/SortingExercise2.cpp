#include <bits/stdc++.h>
using namespace std;
// Sorting Exercise 2: External Sort

/*
    Given a large array containing a million entries, sort them by loading only 100 entries at a time in memory.

    The idea is to use external sorting in order to read the large input from external memory, a text file in this case.
    -First, we take a 100 entries 'chunk' of our total input, merge sort it and output a temporary text file as a sorted 'array'.
    -Continue doing this to all the 'chunks', by reading 100 entries, sorting them, and now, instead of outputting a text file
    we compare with the current sorted array so far, and sort them in O(n+m) time and O(1) space by using two pointers and comparing
    their smalles elements.
    -Each time, update the sorted array so far text file. 
    -This will allow us to sort a 1 million entry input reading 100 entries maximum at a time at any point of the program.

    The time complexity of the whole algorithm is O( k * n * log(n) ), where k is the number of chunks, and n the total
    number of items in a chunk. Sorting the chunk of size n will take n*log(n), we do this for the k chunks available.

    Space complexity: O(n)

    functions: 
        void merge(vector<int>& chunk, int start, int mid, int end)
            takes a vector of 100 entries 'chunk' and sorts it by comparing the two pointers of the array.

            Time complexity: O(n(log(n)))
            Space complexity: O(n)

        void mergeSort(vector<int>& chunk, int start, int end)
            calls recursively to mergeSort the left and right subarrays of the current array of mergeSort.

        void outputTempFile(vector<int>& chunk, int chunkNumber)
            verifies it this is the first sorted chunk to be outputted to a file, if it is, creates the file and returns. if it
            is not, it merges both, the current sorted chunk, and the sorted array so far and outputs the result to a new text file.
            Also removes old text file.

            Time complexity: O(n(log(n)))
            Space complexity: O(n)

        void renameOutput(string filename)
            auxiliary function to rename the output file to 'output.txt'.
        
        void getChunks()
            reads from the ifstream buffer and pushes the first 100 entries to the array, if not enough entries are available, returns.
            calls mergeSort and outputTempFile after every chunk is processed.

            Time complexity: O(m)
            Space complexity: O(m)
            where 'm' is the size of the chunk

        void void sortData()
            calls for the getChunks function.

        void generateData()
            generates test data and outputs it as a text file, creates sizeOfInput entries from 0 to 100

        void testing()
            function that starts the timer for the random number generation and calls the main functions generateData() and sortData()
*/
const int sizeOfInput = 10000; // constant to replace to change input size, mainly for testing.
void merge(vector<int>& chunk, int start, int mid, int end){

    int left = start, right = mid+1;

    vector<int> temp(end-start+1);

    for(int i = start, k = 0; i <= end; ++i, ++k){

        if(left >= mid+1) temp[k] = chunk[right++];
        else if(right >= end+1) temp[k] = chunk[left++];
        else if(chunk[left] < chunk[right]) temp[k] = chunk[left++];
        else temp[k] = chunk[right++];

    }

    for(int i = start; i <= end; ++i)
        chunk[i] = temp[i-start];

}
void mergeSort(vector<int>& chunk, int start, int end){

    if(end <= start) return;

    int mid = start + (end-start) / 2;
    mergeSort(chunk,start,mid);
    mergeSort(chunk,mid+1,end);

    merge(chunk,start,mid,end);

}
void outputTempFile(vector<int>& chunk, int chunkNumber){

    if(chunkNumber <= 1){

        ofstream output("chunk"+to_string(chunkNumber)+".txt");
        for(int i = 0; i < chunk.size(); ++i)
            output <<chunk[i]<<"\n";
        output.close();

    }else{

        ifstream sortedchunk("chunk"+to_string(chunkNumber-1)+".txt");
        ofstream output("chunk"+to_string(chunkNumber)+".txt");
        string curr;
        int k = 0, value;

        while(k < chunk.size() || sortedchunk){

            if(sortedchunk){

                getline(sortedchunk,curr);
                if(curr == ""){

                    sortedchunk.close();
                    continue;

                }
                value = stoi(curr);
                while(k < chunk.size() && chunk[k] < value){

                    output<<chunk[k++]<<"\n";

                }
                output<<value<<"\n";

            }else{

                output<<chunk[k++]<<"\n";

            }

        }

        sortedchunk.close();
        output.close();

        string filename = "chunk"+to_string(chunkNumber-1)+".txt";

        remove(filename.c_str());

    }
    

}
void renameOutput(string filename){

    rename(filename.c_str(),"output.txt");

}
void getChunks(){

    int chunkNumber = 1;
    ifstream input("input.txt");
    vector<int> chunk;
    string curr;

    while(input){
        while(chunk.size() < 100 && input){

            getline(input,curr);
            if(curr == ""){

                input.close();
                renameOutput("chunk"+to_string(chunkNumber-1)+".txt");
                return;

            }
            chunk.push_back(stoi(curr));
            
        }
        mergeSort(chunk,0,chunk.size()-1);
        outputTempFile(chunk,chunkNumber++);
        chunk.clear();
        
    }

    input.close();

}
void sortData(){
    
    getChunks();

}
void generateData(){

    ofstream output("input.txt");
    for(int i = 0; i < sizeOfInput; ++i)
        output<<rand() % 100<<"\n";
    output.close();  

}
void testing(){

    srand(time(0));

    generateData();
    sortData();

}
int main(){

    testing();

    return 0;

}