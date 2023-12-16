#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>




//void computeLPSArray(std::string pat, int M, int lps[]);

/*
* Perform Knuth-Morris-Pratt (KMP) pattern search for occurrences of a pattern 'pat'
within a text 'txt'. The function prints the number of occurrences and their positions.

* @param txt The input text where the search is performed.
* @param pat The pattern (substring) to search for in the input text.

// Returns: nothing (void)
*/    
void KMPSearch(const std::string &txt, const std::string &pat) {
    int M = pat.size();
    int N = txt.size();

    std::vector<int> indexes;
    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
    // Indices for traversing the text (i) and pattern (j)
    int i = 0; 
    int j = 0;
    // Iterate through the text while there is a possibility of finding the pattern
    while ((N - i) >= (M - j)) {
        // If characters match, increment both text and pattern indices
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        // If the entire pattern is matched, record the starting index
        if (j == M) {
           indexes.push_back(i-j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
             // If a mismatch occurs, adjust pattern index based on LPS array
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
     // Output the number of occurrences
  std::cout << pat << " found " << indexes.size() << " time(s)" << std::endl;
      // Output the positions of pattern occurrences
    bool firstIndex = true;
    for (auto index : indexes){
        if(firstIndex){
            std::cout << pat << " found at : " << std::endl;
            firstIndex = false;
        }
        // Calculate row and column positions based on a hypothetical 80-character width
        std::cout << "Row " << (index/ 80) + 1 << " Column " << (index + 1) % 80 << std::endl;

    }
}


/*
* This function fills the Longest Prefix Suffix (LPS) array for the given pattern 'pat'.

* @param pat The pattern for which the Longest Prefix Suffix (LPS) array is computed.
* @param M The size of the pattern.
* @param lps An array to store the resulting LPS values.

// Returns: nothing (void)
*/ 
void computeLPSArray(std::string pat, int M, int lps[]) {
    // Initialize length of the previous longest prefix suffix
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < M) 
      // If characters match, increment both pattern index and LPS index
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            // If a mismatch occurs and there was a previous matching prefix,
            // update 'len' based on the previous LPS value.
            if (len != 0) {
                len = lps[len - 1];
            } else {
                // If no matching prefix found, set LPS value to 0 and move to the next character
                lps[i] = 0;
                i++;
            }
        }
    }
}


//function to find the max of two ints
int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

/*
* This function initializes the bad character array for the Boyer-Moore string searching algorithm.

* @param key The pattern for which the bad character array is initialized.
* @param keysize The size of the pattern.
* @param badchar An array to store the bad character shift values.

// Returns: nothing (void)
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

/*
* This function implements the Boyer-Moore string searching algorithm to find all occurrences of a pattern in a given text.

* @param key The pattern to be searched in the text.
* @param data The text in which occurrences of the pattern are searched.

// Returns: nothing (void)
*/ 
void BoyerMoore(std::string data, std::string key){
    //initalize variables for the size of the key, size of the data, and our badchar array;
    std::vector<int> indexes;
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
           indexes.push_back(shift);
        }

        //we havent found out key in data, so we shift to the last occurance of              the letter that broke our comparison/bad character 
        int badCharShift = i - badchar[data[shift + i]];
        shift += max(1, badCharShift);
        
    } 
      // Output the results
    std::cout << key << " found " << indexes.size() << " time(s)" << std::endl;
    bool firstIndex = true;
    for (auto index : indexes){
        if(firstIndex){
            std::cout << key << " found at : " << std::endl;
            firstIndex = false;
        }
        std::cout << "Row " << (index/ 80) + 1 << " Column " << (index + 1) % 80 << std::endl;

    }
}

/*
* This function implements a basic string searching algorithm to find all occurrences of a pattern in a given text.

* @param s The text in which occurrences of the pattern are searched.
* @param key The pattern to be searched in the text.

// Returns: nothing (void)
*/ 
void basic(std::string s, std::string key) {
    // Initialize variables for counting occurrences and storing starting indices
    int count = 0;
    int count = 0;
    std::vector<int> indexes;
    // Iterate through the text using a basic string searching algorithm
    for (int i = 0; i <= s.length() - key.length(); i++) {
        if (s[i] == key[0]) {
            bool match = true;
            // Nested loop to compare the key to an instance in the text
            for (int j = 1; j < key.length(); j++) {
                if (s[i + j] != key[j]) {
                    match = false;
                    break;
                }
            }
             // If a match is found, add the starting index to the vector
            if (match) {
                indexes.push_back(i);
            }
        }
    }
    
    // Output the results
   std::cout << key << " found " << indexes.size() << " time(s)" << std::endl;
    bool firstIndex = true;
    for (auto index : indexes){
        if(firstIndex){
            std::cout << key << " found at : " << std::endl;
            firstIndex = false;
        }
        std::cout << "Row " << (index/ 80) + 1 << " Column " << (index + 1) % 80 << std::endl;

    }
}


/*
* This function Calls different string searching functions based on the specified algorithm.

* @param s The text in which occurrences of the pattern are searched.
* @param key The pattern to be searched in the text.
*@param function The algorithm/function name to be used for string searching.

// Returns true if the specified function is valid and executed successfully, false otherwise.
*/ 
bool callFunctions(const std::string& s, const std::string& key , std::string function) {
    // Check the specified function and call the corresponding string searching algorithm
   if(function == "Basic" || function == "basic"){
        basic(s,key);
   }
    else if(function == "KMP" || function == "kmp"){
        KMPSearch(s,key);
   }
   else if(function == "Boyer-Moore" || "Boyer Moore"){
        BoyerMoore(s,key);
   }

   else{
        // Print an error message for an invalid function
    std::cout << "Invalid function!" << std::endl;
   }
}

/*
* This function executes string searching algorithms based on user input.

* @param  argc The number of command-line arguments.
* @param argv An array containing command-line arguments.

// Returns 0
*/ 
int main(int argc, char* argv[]){
      // Open the specified file and prompt the user to choose a string searching function
    std::ifstream file(argv[1]);
    std::cout << "Pick which function to use : Basic , KMP , or Boyer-Moore" << std::endl;
    std::string function;
    std::cin >> function;
    std::cout << std::endl;

        // Check if the file is successfully opened

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

     // Read the content of the file into the 'data' string
    std::string line, data;
      while (std::getline(file, line)) {
        data += line;
    }
    // Extract the search key from command-line arguments
    std::string key = argv[2];
    // Call the selected string searching function based on user input
     callFunctions(data, key , function);

    return 0;
    
}
