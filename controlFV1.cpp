#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <chrono>


//to run this function:
  //g++ -std=c++11 controlFV1.cpp -o controlF
  //./controlF fileName  functionChoice key
//next version should like ask for upper or lower case
// also probably change the inputs from the command line to std::cin , and give the user the options
//also need to change the string search functions so that they print what line and space the key was found
//both time functions work

//start of kmp functions
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

//end of kmp functions

//start of Boyer-Moore
//function to find the max of two ints

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
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
        //if i < 0, weve found an instance of our key. we can return true
        if (i < 0) {
            return true;
        }
        //we havent found out key in data, so we shift to the last occurance of the letter that broke our comparison/bad character 
        int badCharShift = i - badchar[data[shift + i]];
        shift += max(1, badCharShift);
        
    }

    return false;
}

//end of Boyer-Moore

// start of basic function
bool inString(std::string s, std::string key) {
    for (int i = 0; i <= s.length() - key.length(); i++) {
        if (s[i] == key[0]) {
            bool match = true;
            for (int j = 1; j < key.length(); j++) {
                if (s[i + j] != key[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }
    return false;
}

//end of basic function

// float time_func(const std::string& s, const std::string& key , std::string function) {
//     clock_t c_start, c_end;

//     if(function == "basic"){
//     c_start = clock();
//     bool result = inString(s, key);
//     c_end = clock();
//      if (result) {
//         std::cout << "key is in string " << std::endl;
//     } else {
//         std::cout << "key is not in string " << std::endl;
//     }
//     }

//     else if (function == "kmp"){
//         c_start = clock();
//         bool result = KMPSearch(s, key);
//         c_end = clock();
//          if (result) {
//         std::cout << "key is in string " << std::endl;
//     } else {
//         std::cout << "key is not in string " << std::endl;
//     }
//     }

//       else if (function == "boyer"){
//         c_start = clock();
//         bool result = BoyerMoore(s, key);
//         c_end = clock();

//          if (result) {
//         std::cout << "key is in string " << std::endl;
//     } else {
//         std::cout << "key is not in string " << std::endl;
//     }
//     }
//     else{
//         std::cout << "invalid function call" << '\n';
//     }

   

//     float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
//     return output;
// }



float time_func(const std::string& s, const std::string& key, const std::string& function) {
    // Using the high_resolution_clock for accurate timing
    auto start_time = std::chrono::high_resolution_clock::now();

    if (function == "basic") {
        bool result = inString(s, key);
        if (result) {
            std::cout << "key is in string " << std::endl;
        } else {
            std::cout << "key is not in string " << std::endl;
        }
    } else if (function == "kmp") {
        bool result = KMPSearch(s, key);
        if (result) {
            std::cout << "key is in string " << std::endl;
        } else {
            std::cout << "key is not in string " << std::endl;
        }
    } else if (function == "boyer") {
        bool result = BoyerMoore(s, key);
        if (result) {
            std::cout << "key is in string " << std::endl;
        } else {
            std::cout << "key is not in string " << std::endl;
        }
    } else {
        std::cout << "invalid function call" << '\n';
    }

    // Measure the duration
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    float output = 1.0 * duration.count() / 1e6; // Convert microseconds to seconds
    return output;
}



int main(int argc, char* argv[]){
    std::ifstream file(argv[1]);
    std::string function = argv[2];

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    
    std::string line, data;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string val;
        while (iss >> val) {
            data.append(val);
        }
    }

    std::string key = argv[3];
    std::cout << data.size() << std::endl;
    float execution_time = time_func(data, key , function);

    std::cout << "Execution time of the Boyer Moore Algorithm: " << execution_time << " seconds." << std::endl;
    return 0;


}
