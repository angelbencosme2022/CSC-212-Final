#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

/** 
 * This function performs a substring search in the input string to determine
 * if the specified key is present.
 * 
 * @param s The input string to search.
 * @param key The substring to look for in the input string.
 * @return True if the key is found in the string, false otherwise.
 */
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

/** 
 * This function measures the execution time of the inString function, which checks if a substring (key) is present in a given string (s). The execution time is returned in seconds.
 * 
 * @param s The input string to search.
 * @param key The substring to look for in the input string.
 * @return  The execution time of the search operation in seconds.
 */

float time_func(const std::string& s, const std::string& key) {
    clock_t c_start, c_end;

     // Record the start time
    c_start = clock();
    // Perform the substring search using inString function
    bool result = inString(s, key);
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

/*
 * 
 * This main function is designed to be executed from the command line, taking the path to an input file as a command-line argument. It reads the DNA strand from the file, performs a substring search using the time_func function, and outputs the execution time of the search.
 
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 
 * @return   Return status indicating the termination status of the program (0 for successful execution, 1 for errors).
 */


int main(int argv , char* argc[]) {
    // Open the input file
    std::ifstream inputFile(argc[1]);
    // initializing variables we will need 
    std::string dnaStrand;
    std::string line;

    // Read the DNA strand from the file
    while (std::getline(inputFile, line)) {
        dnaStrand += line;
    }
    
    // Close the input file
    inputFile.close();
    
    // Specify the substring (key) to search for
    std::string key = "CGT";
    
     // Measure the execution time of the inString function
    float execution_time = time_func(dnaStrand, key);

    // Output the execution time
    std::cout << "Execution time of inString function: " << execution_time << " seconds." << std::endl;

    // Exit successfully
    return 0;
}
