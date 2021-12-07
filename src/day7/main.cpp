#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;

int findMax(vector<int> numbers)
{
    int max = 0;
    for (int number : numbers)
    {
        if (number > max)
            max = number;
    }
    return max;
}

int findMin(vector<int> numbers, int max)
{
    int min = max;
    for (int number : numbers)
    {
        if (number < min)
            min = number;
    }
    return min;
}

int calculateDistance(int pos, int dest)
{
    int distance = 0;
    if(pos > dest)
        distance = pos - dest;
    else
        distance = dest - pos;

    return distance;
}

int calculateDistanceNew(int pos, int dest)
{
    int distance = 0;
    int steps = 0;
    if(pos > dest)
    {
        steps = pos - dest;
        for (int i = 1; i  <= steps; i++)
        {
            distance += i * 1;
        }
    }
        
    else
    {
        steps = dest - pos;
        for (int i = 1; i  <= steps; i++)
        {
            distance += i * 1;
        }
    }

    return distance;
}



void partOne()
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

    int max = findMax(numbers);
    int min = findMin(numbers, max);
    int bestDistanceSum = -1;
    int bestPosition = 0;
    for (int i = min; i <= max; ++i)
    {
        int distanceSum = 0;
        for(int j = 0; j < numbers.size(); ++j)
        {
            distanceSum += calculateDistance(i, numbers[j]);
        }
        if (distanceSum < bestDistanceSum || bestDistanceSum == -1 )
        {
            bestDistanceSum = distanceSum;
            bestPosition = i;
        }
        //cout << distanceSum << " at " << i << endl;
    }

    cout << bestDistanceSum << " at " << bestPosition << endl;
}


void partTwo()
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

    int max = findMax(numbers);
    int min = findMin(numbers, max);
    int bestDistanceSum = -1;
    int bestPosition = 0;
    for (int i = min; i <= max; ++i)
    {
        int distanceSum = 0;
        for(int j = 0; j < numbers.size(); ++j)
        {
            distanceSum += calculateDistanceNew(i, numbers[j]);
        }
        if (distanceSum < bestDistanceSum || bestDistanceSum == -1 )
        {
            bestDistanceSum = distanceSum;
            bestPosition = i;
        }
        //cout << distanceSum << " at " << i << endl;
    }

    cout << bestDistanceSum << " at " << bestPosition << endl;
}

int main()
{
    partOne();
    partTwo();
    return 0;
}