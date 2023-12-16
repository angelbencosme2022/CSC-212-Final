#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

//void computeLPSArray(std::string pat, int M, int lps[]);


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



float time_func(const std::string& s, const std::string& key) {
    clock_t c_start, c_end;

    c_start = clock();
    bool result = KMPSearch(s, key);
    c_end = clock();

    if (result) {
        std::cout << "key is in string " << std::endl;
    } else {
        std::cout << "key is not in string " << std::endl;
    }

    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    return output;
}



// Driver code
    int main(int argv , char* argc[]) {
   std::ifstream inputFile(argc[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argc[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf(); // Read the entire file into the buffer

    inputFile.close();

    std::string dnaStrand = buffer.str();
   std::string  key = "CGT";
float execution_time = time_func(dnaStrand, key);

    std::cout << "Execution time of inString function: " << execution_time << " seconds." << std::endl;

    return 0;
}
