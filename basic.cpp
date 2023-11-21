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

    if (result) {
        std::cout << "key is in string " << std::endl;
    } else {
        std::cout << "key is not in string " << std::endl;
    }

    float output = 1.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    return output;
}



    int main(int argv , char* argc[]) {
    std::ifstream inputFile(argc[1]);
    std::string dnaStrand;
    std::string line;
    while (std::getline(inputFile, line)) {
        dnaStrand += line;
    }
    inputFile.close();
    std::string key = "CGT";
    float execution_time = time_func(dnaStrand, key);

    std::cout << "Execution time of inString function: " << execution_time << " seconds." << std::endl;

    return 0;
}
