#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>


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

float time_func(const std::string& s, const std::string& key) {
    clock_t c_start, c_end;

    c_start = clock();
    bool result = inString(s, key);
    c_end = clock();

    // if (result) {
    //     std::cout << key << " is in " << s << std::endl;
    // } else {
    //     std::cout << key << " is not in " << s << std::endl;
    // }

    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    return output;
}



int main() {
    std::string dnaStrand;
    // Create a long DNA strand
    for(int i = 0; i < 5000; i++){
        dnaStrand+= "CG";

    }
    dnaStrand+= "T";
    //this makes a worst case scenario
    //

    std::ofstream myFile;
    myFile.open("text_case_4.txt");
    myFile << dnaStrand << '\n';
    // i am trying to add a string to a file , but when I add it doesn't make a new line each times
    // this is to make test cases for all the functions
    myFile.close();
    std::string key = "CGT";

    float execution_time = time_func(dnaStrand, key);
    std::cout << "Execution time of inString function: " << execution_time << " seconds." << std::endl;

    return 0;
}
