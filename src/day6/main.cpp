#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <thread>

using namespace std;

struct Lanternfish
{
    int timer;
    //bool hasWaited;
};

void partOne(int days)
{
    ifstream myfile("input");
    std::string inputLine;
    
    //read fish population
    getline(myfile, inputLine);
    stringstream ss( inputLine );
    vector<int> numbers;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        numbers.push_back( stoi(substr ));
    }

    vector<Lanternfish> lanterns;
    for (int number : numbers )
    {
        Lanternfish fish = {number/*, true*/};
        lanterns.push_back(fish);
    }

    for (int i = 0; i  < days; ++i)
    {
        int newFish = 0;
        for (Lanternfish& lantern : lanterns) // wow, such pass by reference
        {
            if (lantern.timer == 0)
            {
                newFish++;
                lantern.timer = 6;
            }
            else
            {
                lantern.timer--;
            }
        }

        for (int j = 0; j < newFish; ++j)
        {
            Lanternfish fish = {8};
            lanterns.push_back(fish);
        }
    }

    cout <<  lanterns.size() << endl;
}

void partTwo(int days)
{
    ifstream myfile("input");
    std::string inputLine;
    
    //read fish population
    getline(myfile, inputLine);
    stringstream ss( inputLine );
    vector<int> numbers;
    long long int fishtimer[9] = {};
    //vector<long long int> fishtimer;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        numbers.push_back( stoi(substr ));
        fishtimer[stoi(substr)]++;
        
    }


    for(int i = 0; i < days; ++i)
    {
        long long int fishZero = fishtimer[0];
        for (int j = 0; j < 8; ++j)
        {
            fishtimer[j] = fishtimer[j + 1];
        }
        fishtimer[6] += fishZero;
        fishtimer[8] = fishZero;
    }

    long long int sum = 0;
    for (int k = 0; k < (sizeof(fishtimer) / sizeof(fishtimer[0])); ++k)
    {

        sum += fishtimer[k];
    }
    
    cout << sum << endl;
}

int main()
{
    partOne(80);
    partTwo(256);

//f(t)=330.0183e0.0871t
//f(t)=330.0357e0.0871t
//f(t)=330.4057e0.0871t

    return 0;
}