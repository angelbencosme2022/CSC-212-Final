#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

//void computeLPSArray(std::string pat, int M, int lps[]);

/**
 * This function performs a pattern search using the Knuth-Morris-Pratt (KMP) algorithm. It determines whether a given pattern pat is present in the input text txt.
 
 * @param txt The input text where the pattern search is performed.
 * @param pat The pattern (substring) to search for in the input text.
 
 * @return  Returns true if the pattern is found in the text; otherwise, returns false
 */

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

/**
 * This function is a helper function used in the Knuth-Morris-Pratt (KMP) algorithm. It computes the Longest Prefix Suffix (LPS) array, which represents the length of the longest proper prefix that is also a suffix for each position in the pattern pat.
 
 * @param M  The size (length) of the pattern.
 * @param pat The pattern (substring) for which the LPS array is computed.
 * @param lps  An array to store the computed LPS values for each position in the pattern.

 * @return Doesn't return anything, but the function modifies the lps array in place.
 */

void computeLPSArray(std::string pat, int M, int lps[]) {
    // Initialize length of the previous longest prefix suffix and
    // sets the first value in the LPS array to 0
    int len = 0;
    lps[0] = 0;

    // Start iterating from the second character of the pattern
    int i = 1;
    while (i < M) {
        // If the current character matches the character at the previous length
        if (pat[i] == pat[len]) {
            // Increment length and assign it to the current position in the LPS array
            len++;
            lps[i] = len;
             // Move to the next character in both pattern and LPS array
            i++;
        } else {
             // If there is a mismatch and the length is not 0
            if (len != 0) {
                // Update length to the value at the previous position in the LPS array
                len = lps[len - 1];
            } else {
                // If the length is 0, assign 0 to the current position in the LPS array
                lps[i] = 0;
                // Move to the next character in the pattern
                i++;
            }
        }
    }
}

/**
 * Measure the execution time of the Knuth-Morris-Pratt (KMP) search algorithm for finding the presence of a key in a given string.
 
 * @param s  The input string where the search is performed.
 * @param key The pattern (substring) to search for in the input string.

 * @return The execution time in seconds.
 */

float time_func(const std::string& s, const std::string& key) {
    // Variables to store the start and end times using clock()
    clock_t c_start, c_end;
    
     // Record the start time
    c_start = clock();
     // Perform the Knuth-Morris-Pratt (KMP) search and store the result
    bool result = KMPSearch(s, key);
     // Record the end time
    c_end = clock();

    // Output whether the key is found in the string or not
    if (result) {
        std::cout << "key is in string " << std::endl;
    } else {
        std::cout << "key is not in string " << std::endl;
    }

    // Calculate the execution time in seconds and store it in 'output'
    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;

    // return the execution time
    return output;
}



/**
 * The main function reads a text file specified in the command-line arguments, processes the content to form a single string (data), and then measures the execution time of the KMP string search algorithm for a predefined key in the obtained data.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of strings representing the command-line arguments.
 
 * @return   Return status indicating the termination status of the program. And prints execution time.
 */
    int main(int argv , char* argc[]) {
        // Open the input file specified in the command-line arguments
        std::ifstream inputFile(argc[1]);
        // Check if the file is successfully opened
        if (!inputFile.is_open()) {
            // Display an error message if the file cannot be opened
            std::cerr << "Error opening file: " << argc[1] << std::endl;
            return 1;
        }

     // Read the entire content of the file into a stringstream buffer
    std::stringstream buffer;
    buffer << inputFile.rdbuf(); 
    // Close the input file
    inputFile.close();
        
    // Extract the DNA strand from the buffer as a string
    std::string dnaStrand = buffer.str();
         // Specify the substring (key) to search for using the Knuth-Morris-Pratt (KMP) algorithm
   std::string  key = "CGT";
         // Measure the execution time of the Knuth-Morris-Pratt (KMP) search algorithm
float execution_time = time_func(dnaStrand, key);
    // Output the execution time
    std::cout << "Execution time of inString function: " << execution_time << " seconds." << std::endl;

    return 0;
}
