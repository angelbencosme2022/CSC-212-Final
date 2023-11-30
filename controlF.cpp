#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>




void computeLPSArray(std::string pat, int M, int lps[]);

// Prints occurrences of pat[] in txt[]
// kmp 

void KMPSearch(const std::string &txt, const std::string &pat) {
    int M = pat.size();
    int N = txt.size();

    std::vector<int> indexes;
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
           indexes.push_back(i-j);
            j = lps[j - 1];
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

  std::cout << pat << " found " << indexes.size() << " time(s)" << std::endl;
    bool firstIndex = true;
    for (auto index : indexes){
        if(firstIndex){
            std::cout << pat << " found at : " << std::endl;
            firstIndex = false;
        }
        std::cout << "Row " << (index/ 80) + 1 << " Column " << (index + 1) % 80 << std::endl;

    }
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

        //we havent found out key in data, so we shift to the last occurance of the letter that broke our comparison/bad character 
        int badCharShift = i - badchar[data[shift + i]];
        shift += max(1, badCharShift);
        
    }   
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


void basic(std::string s, std::string key) {
    int count = 0;
    std::vector<int> indexes;
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
                indexes.push_back(i);
            }
        }
    }
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



bool callFunctions(const std::string& s, const std::string& key , std::string function) {

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
    std::cout << "Invalid function!" << std::endl;
   }
}






int main(int argc, char* argv[]){
    std::ifstream file(argv[1]);
    std::cout << "Pick which function to use : Basic , KMP , or Boyer-Moore" << std::endl;
    std::string function;
    std::cin >> function;
    std::cout << std::endl;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }
    
    std::string line, data;
      while (std::getline(file, line)) {
        data += line;
    }

    std::string key = argv[2];
     callFunctions(data, key , function);

    return 0;


}
