#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
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




float time_func(const std::string& data, const std::string& key) {
    clock_t c_start, c_end;

    c_start = clock();
    bool result = BoyerMoore(data, key);
    c_end = clock();

    if (result) {
        std::cout << "key is in string " << std::endl;
    } else {
        std::cout << "key is not in string " << std::endl;
    }

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
