#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


void partOne()
{
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
    
    cout << "Number increases part one: " << incCounter << endl;
}

void partTwo()
{
    ifstream myfile("input");

    int window = 0;
    int lastWindow = 0;
    int incCounter = 0;
    vector<int> depths;

    std::string inputLine;
    while(getline(myfile, inputLine))
    {
        stringstream converter(inputLine);
        int depth = 0;
        converter >> depth;

        depths.push_back(depth);
    }

    for (int i = 2; i < depths.size(); i++)
    {
        int window = depths[i] + depths[i-1] + depths[i-2];

        if (window > lastWindow && lastWindow != 0)
                incCounter++;

        lastWindow = window;
    }
    
    cout << "Number increases part two: " << incCounter << endl;
}


int main(){
    partOne();
    partTwo();
    return 0;
}
