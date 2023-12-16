#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

/**
 * This function returns the maximum of two integers.
 
 * @param a first integer
 * @param b second integer
 
 * @return The greater of the two input integers (a and b)
 */
int max(int a, int b){
    // comparing the value of a and b
    if(a > b){
        //if a is greater return a
        return a;
    }
    // if is not greater return b
    return b;
}


/**
 * This function is part of the Boyer-Moore string search algorithm and is used to precompute a "bad character" table. The table is used to determine the shift distance when a mismatch occurs during the search.
 
 * @param key The search pattern (substring).
 * @param keysize The size (length) of the search pattern.
 * @param badchar[256] An array representing the bad character table. It is used     to store the rightmost occurrence of each character in the search pattern. 
 
 * @return The function does not return a value; it just fills the badchar array
 */
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

/**
 * This function is part of the Boyer-Moore string search algorithm and is used to precompute a "good suffix" table. The table is used to determine the shift distance when a mismatch occurs during the search.
 
 * @param key The search pattern (substring).
 * @param keysize The size (length) of the search pattern.
 * @param badchar[256]  An array representing the good suffix shift table. It is used to store information about the potential shifts for the pattern when a mismatch occurs.
 
 * @return The function does not return a value; it just fills the goodSuffix array
 */
void good_suffix(std::string key, int keySize, int goodSuffix[]) {
    int i, j;

    //initialize the good suffix array with zeros
    for(i = 0; i <= keySize; i++){
        goodSuffix[i] = 0;
    }

    //start from the right end of the pattern
    i = keySize;
    j = keySize + 1;

    //set the initial value for the first position in the array
    goodSuffix[i] = j;

    while(i > 0){
        //move left until we find a mismatch or reach the beginning of the pattern
        while(j <= keySize && key[i - 1] != key[j - 1]) {
            //update the good suffix shift for this position
            if (goodSuffix[j] == 0) {
                goodSuffix[j] = j - i;
            }
            j = goodSuffix[j]; //move j to the next value in the array
        }

        //move to the left in both the pattern and the good suffix array
        i--;
        j--;

        //update the good suffix shift for the current position in the array
        goodSuffix[i] = j;
    }
}

/**
 * This function implements the Boyer-Moore string search algorithm to determine whether a given key is present in the data string.
 
 * @param Data  The text string in which the search is performed.
 * @param key The pattern (substring) to search for in the data string.
 
 * @return Returns true if the key is found in the data string; otherwise, returns false.
 */

bool BoyerMoore(std::string data, std::string key){
    //initalize variables for the size of the key, size of the data, our badchar array, and the good suffix array;
    int m = key.size(), n = data.size(), badchar[256], goodSuffix[m + 1];
    //assemble the badchar array 
    bad_character(key, m, badchar);
    //assemble the good suffix array
    good_suffix(key, m, goodSuffix);
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
        int goodSuffixShift = 0;

        if (i < m - 1) {
            goodSuffixShift = goodSuffix[i + 1];
        }

        shift += max(1, max(badCharShift, goodSuffixShift));
        
    }

    return false;
}




float time_func(const std::string& data, const std::string& key) {
    clock_t c_start, c_end;

    // Record the start time
    c_start = clock();
    // Perform the substring search using BoyerMoore function
    bool result = BoyerMoore(data, key);
    // Record the end time
    c_end = clock();
     // Print the result of the search
    if (result) {
        std::cout << "key is in string " << std::endl;
    } else {
        std::cout << "key is not in string " << std::endl;
    }
     // Calculate and return the execution time in seconds
    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    return output;
}

int main(int argc, char* argv[]){
    std::ifstream file(argv[1]);

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

    std::string key = "CGT";
    float execution_time = time_func(data, key);

    std::cout << "Execution time of the Boyer Moore Algorithm: " << execution_time << " seconds." << std::endl;
    return 0;


}
