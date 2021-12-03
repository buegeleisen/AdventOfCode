#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


enum Commands {
    forwardd,
    down,
    up
};

Commands resolve( string input )
{
    if (input == "forward") return forwardd;
    if (input == "down") return down;
    if (input == "up") return up;
    return up;
}


void partOne()
{
    ifstream myfile("input");

    int depth = 0;
    int horizontalPos = 0;
    int downcounter = 0;
    int upcounter = 0;

    string inputCommand;
    int inputSteps;
    while(myfile >> inputCommand >> inputSteps)
    {
        Commands command = resolve(inputCommand);
        switch (command)
        {
            case forwardd:
                horizontalPos += inputSteps;
                break;
            case down:
                depth += inputSteps;
                downcounter += inputSteps;
                break;
            case up:
                depth -= inputSteps;
                upcounter += inputSteps;
                break;
        }
    }

    int multiplicate = depth * horizontalPos;

    int alternative = (downcounter - upcounter) * horizontalPos;
    
    cout << "Final position - Depth: " << depth << ", Horizontal: " << horizontalPos << " - Multipicate: " << multiplicate << " or " << alternative << endl;
}

void partTwo()
{
    ifstream myfile("input");

    int depth = 0;
    int horizontalPos = 0;
    int aim = 0;


    string inputCommand;
    int inputSteps;
    while(myfile >> inputCommand >> inputSteps)
    {
        Commands command = resolve(inputCommand);
        switch (command)
        {
            case forwardd:
                horizontalPos += inputSteps;
                depth += aim * inputSteps;
                break;
            case down:
                aim += inputSteps;
                break;
            case up:
                aim -= inputSteps;
                break;
        }
    }

    int multiplicate = depth * horizontalPos;


    
    cout << "Final position - Depth: " << depth << ", Horizontal: " << horizontalPos << " - Multipicate: " << multiplicate << endl;

}


int main(){
    partOne();
    partTwo();
    return 0;
}
