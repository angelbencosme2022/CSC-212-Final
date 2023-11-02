#include <iostream>
#include <string>

bool inString(std::string s , std::string key){
    for(int i = 0; i <= s.length() - key.length(); i++){
        if(s[i] == key[0]){
            for(int j = 1; j <= key.length(); j++){
                if(s[i+j] != key[j]){
                    break;
                }
                return true;
        }
        }
    }
    return false;
}
int main(int argv , char* argc[]){
    std::string s , key;
    s = argc[1];
    key = argc[2];
    if(inString(s,key)){
        std::cout << key << " is in " << s << std::endl;
    }
    else{
        std::cout << key << " is not in " << s << std::endl;
    }


    return 0;
}