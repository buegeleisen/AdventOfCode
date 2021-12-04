#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void partOne()
{
    ifstream myfile("input");

    vector<vector<int>> matrix;
    int line = 0;
    
    std::string inputLine;
    while(getline(myfile, inputLine))
    {
        vector<int> thisLine;
        for (char const &c: inputLine) 
        {
            int a = c - '0';
            thisLine.push_back(a);
        }
        matrix.push_back(thisLine);
    }

    string gammaString = "";
    string epsilonString = "";
    for (int i = 0; i < matrix[0].size(); ++i)
    {
        int oneCount = 0;
        int nilCount = 0;

        for (int j = 0; j < matrix.size(); ++j)
        {
            int check = matrix[j][i];
            if (check == 0) 
                nilCount++;
            else
                oneCount++;
        }

        if (oneCount > nilCount)
        {
            gammaString += "1";
            epsilonString += "0";
        }
        else
        {
            gammaString += "0";
            epsilonString += "1";
        }
    }

    int gamma = stoi(gammaString, nullptr, 2);
    int epsilon = stoi(epsilonString, nullptr, 2);
    int consumption = gamma * epsilon;

    cout << "Gamma: " << gamma << endl;
    cout << "Epsilon: " << epsilon << endl;
    cout << "Consumption: " << consumption << endl;
}


void partTwo()
{
    ifstream myfile("input");

    vector<vector<int>> matrix;
    int line = 0;
    vector<string> eliminators;

    std::string inputLine;
    while(getline(myfile, inputLine))
    {
        vector<int> thisLine;
        for (char const &c: inputLine) 
        {
            int a = c - '0';
            thisLine.push_back(a);
        }
        matrix.push_back(thisLine);
        eliminators.push_back(inputLine);
    }


    //create oxy String
    vector<string> remaindersOxy = eliminators;
    int index = 0;
    char leader;
    while(remaindersOxy.size() > 1)
    {
       
        int nilCounter = 0;
        int oneCounter = 0;
        for (int i = 0; i < remaindersOxy.size(); ++i)
        {
            if (remaindersOxy[i][index] == '0')
                nilCounter++;
            else
                oneCounter++;
            
            if (nilCounter > oneCounter)
                leader = '0';
            else 
                leader = '1';
        }

        for (auto it = remaindersOxy.begin(); it != remaindersOxy.end(); it++)
        {
            string test = *it; 
            if (test[index] != leader)
                remaindersOxy.erase(it--);
                /*for (string element : remaindersOxy)
                    cout << element << " " ;
                cout << endl;*/
        }
        index++;
    }


    //create co2 String
    vector<string> remaindersCO = eliminators;
    index = 0;
    
    while(remaindersCO.size() > 1)
    {
       
        int nilCounter = 0;
        int oneCounter = 0;
        for (int i = 0; i < remaindersCO.size(); ++i)
        {
            if (remaindersCO[i][index] == '0')
                nilCounter++;
            else
                oneCounter++;
            
            if (oneCounter >= nilCounter)
                leader = '0';
            else 
                leader = '1';
        }

        for (auto it = remaindersCO.begin(); it != remaindersCO.end(); it++)
        {
            string test = *it; 
            if (test[index] != leader)
                remaindersCO.erase(it--);
                /*for (string element : remaindersCO)
                    cout << element << " " ;
                cout << endl;*/
        }
        index++;
    }

    //calculate Life Support Rating
    int oxygen = stoi(remaindersOxy[0], nullptr, 2);
    int coTwo = stoi(remaindersCO[0], nullptr, 2);
    int lsr = oxygen * coTwo;

    cout << "Oxygen Generator: " << oxygen << endl;
    cout << "CO2 Scrubber: " << coTwo << endl;
    cout << "Life Support: " << lsr << endl;

}

int main(){
    partOne();
    partTwo();
    
    return 0;
}
