#include <iostream>
#include <map>
#include <cmath>

// include std scope
using std::cout;
using std::endl;
using std::map;

int main(int argc, char const *argv[]){
    
    double epsilon = 10.0; // In Degrees
    epsilon = (2 * epsilon + 180) * M_PI / 180.0; // Convert to Radians

    cout << "Epsilon in Radians: " << epsilon << endl;
    cout << "Epsilon in Degrees: " << epsilon * 180.0 / M_PI << endl;
    cout << "Cosine of Epsilon: " << cos(epsilon) << endl;

    return 0;
}
