#include <iostream>
#include <map>

// include std scope
using std::cout;
using std::endl;
using std::map;

int main(int argc, char const *argv[]){
    
    cout << "Hello, World!" << endl;
    map<unsigned int, unsigned int> dict;

    dict[1] = 1;
    dict[2] = 2;

    cout << "dict[1]: " << dict[1] << endl;

    return 0;
}
