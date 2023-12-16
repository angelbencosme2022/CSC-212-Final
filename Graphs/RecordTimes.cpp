
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

/*
* Compares two numbers and find the largest one

* param@ a The first integer
* param@ b The second integer

* Returns true if the substring is found, otherwise returns false.
*/

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

/*
* This function iterates through the input string to find occurrences of the specified substring.

* param@ s The input string to search within.
* param@ key The substring to search for in the input string.

* Returns true if the substring is found, otherwise returns false.
*/

bool inString(std::string s, std::string key) {
        // Iterate through the input string up to the point where the remaining length is equal to or greater than the length of the substring to be searched.
    for (int i = 0; i <= s.length() - key.length(); i++) 
    // Check if the current character in the input string matches the first character of the substring.
        if (s[i] == key[0]) {
            bool match = true;
            // If a mismatch is found, set the match flag to false and break out of the loop.
            for (int j = 1; j < key.length(); j++) {
                // If a mismatch is found, set the match flag to false and break out of the loop.
                if (s[i + j] != key[j]) {
                    match = false;
                    break;
                }
            }
            // If the match flag is true at this point, the entire substring is found.
            if (match) {
                return true;
            }
        }
    }
    // If no match is found after iterating through the entire string, return false.
    return false;
}


void bad_character(std::string key, int keySize, int badchar[256]){
    //initialize badchar with -1, a non ascii value
    for(int i = 0; i < 256; i++){
        badchar[i] = -1;
    }
    //process the key so that we can tell the distance from the last prefix
    for(int i = 0; i < keySize; i++){
        int ascii = (int) key[i];
        badchar[ascii] = i;
    }

}

bool BoyerMoore(std::string data, std::string key){
    //initalize variables for the size of the key, size of the data, and our badchar array;
    int m = key.size(), n = data.size(), badchar[256];
    //assemble the badchar array 
    bad_character(key, m, badchar);
    //initalize shift, this will be used to find the next worthy comparison
    int shift = 0;
    //sort through the data 
    while (shift <= (n - m)) {
        //i is initalized to go through the key
        int i = m - 1;
        //this nested while loop will be used to compare our key to an instance in data
        while (i >= 0 && key[i] == data[shift + i]) {
            //loop will break if the comparison is wrong, or...
            i--;
        }
        //if i < 0, we've found an instance of our key. we can return true
        if (i < 0) {
            return true;
        }
        //we havent found out key in data, so we shift to the last occurance of the letter that broke our comparison/bad character 
        int badCharShift = i - badchar[data[shift + i]];
        shift += max(1, badCharShift);
        
    }

    return false;
}



void computeLPSArray(std::string pat, int M, int lps[]);

// Prints occurrences of pat[] in txt[]
bool KMPSearch(std::string txt, std::string pat) {
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            //std::cout << "Found pattern at index " << i - j << std::endl;
            return true;
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return false;
}

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(std::string pat, int M, int lps[]) {
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/*
* Measures the execution time of a string search algorithm on a given string.It records the starting time, executes the search algorithm, records the ending time,  and calculates the elapsed time in seconds.

* param@ s The input string on which the search algorithm will be applied.
* param@ key The substring or pattern to search for in the input string.
* param@ function he search algorithm to use. Supported values are "basic" for a basic search,"kmp" for the Knuth-Morris-Pratt algorithm, and "boyer" for the Boyer-Moore algorithm.

* Returns The execution time of the search algorithm in seconds.
*/
float time_func(const std::string& s, const std::string& key , std::string function) {
    clock_t c_start, c_end;
// Depending on the specified search algorithm, execute the corresponding search function.
    if(function == "basic"){
        c_start = clock();
        bool result = inString(s, key);
        c_end = clock();
    }

    else if (function == "kmp"){
        c_start = clock();
        bool result = KMPSearch(s, key);
        c_end = clock();
    }

    else if (function == "boyer"){
        c_start = clock();
        bool result = BoyerMoore(s, key);
        c_end = clock();

    }
    else{
        // If an invalid search algorithm is specified, print an error message.
        std::cout << "invalid function call" << '\n';
    }

   
     // Calculates the elapsed time in seconds and returns the result.
    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    return output;
}

/*
* Measures the execution time of a string search algorithm on a given string.It records the starting time, executes the search algorithm, records the ending time,  and calculates the elapsed time in seconds.

* param@ argc The number of command-line arguments.
* param@ argv An array of command-line arguments.

* Returns 0
*/
   int main(int argc, char* argv[]){
// Extracts the specified search algorithm from command-line arguments
    std::string function = argv[1];
 // Initializes empty strings to store the input data and key for each iteration.
    std::string s = "";
// Creates separate output files for each search algorithm.
    std::ofstream basic_File("basicfilename");
    std::ofstream kmp_File("kmpfilename");
    std::ofstream boyer_File("boyerfilename");
    

    std::string key = "CGT";
  // Iterates over a range of input sizes (doubling the size at each iteration).
    for(int i = 0; i < 50000; i++){
    // Measures the execution time of the specified search algorithm for the             current input size.
        float execution_time = time_func(s, key , function);
        
         // Writes the execution time and input size to the corresponding output file.
        if(function == "basic"){ 
            basic_File << i*2 << ", " << execution_time << std::endl; //switch to writing to file 
        }else if(function == "kmp"){
            kmp_File << i*2 << ", " << execution_time << std::endl; //switch to writing to file 
        }else if(function == "boyer"){
             boyer_File << i*2 << ", " << execution_time << std::endl;
        }
        // Doubles the size of the input string by appending "CG" at each iteration.
        s += "CG";
    
    }
    
    return 0;

