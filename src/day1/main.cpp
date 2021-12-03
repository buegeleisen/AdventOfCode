#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(){
    ifstream myfile("input");

    int depth = 0;
    int lastDepth = 0;
    int incCounter = 0;

    std::string inputLine;
    while(getline(myfile, inputLine))
    {
        stringstream converter(inputLine);

        converter >> depth;

        if (depth > lastDepth && lastDepth != 0)
            incCounter++;

        lastDepth = depth;
    }
    
    cout << "Number increases: " << incCounter << endl;
    return 0;
}
