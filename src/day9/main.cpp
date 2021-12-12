#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>


using namespace std;


void partOne()
{
    vector<vector<int>> matrix;
    ifstream myfile("input");
    std::string inputLine;

    while (getline(myfile, inputLine))
    {
        vector<int> thisLine;
        for (char const &c: inputLine) 
        {
            int a = c - '0';
            thisLine.push_back(a);
        }
        matrix.push_back(thisLine);
    }
    int sum = 0;
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if ( i == 0 ) // first row
            {
                if (j == 0) // top left corner
                {
                    int current = matrix[i][j];
                    int bottom = matrix[i+1][j];
                    int right = matrix[i][j+1];
                    if (current < bottom && current < right)
                        sum += current + 1;
                }
                else if (j == matrix[i].size() - 1) // top right corner
                {
                    int current = matrix[i][j];
                    int bottom = matrix[i+1][j];
                    int left = matrix[i][j-1];
                    if (current < bottom && current < left)
                        sum += current + 1;
                }
                else // rest of first row
                {
                    int current = matrix[i][j];
                    int bottom = matrix[i+1][j];
                    int left = matrix[i][j-1];
                    int right = matrix[i][j+1];
                    if (current < bottom && current < left && current < right)
                        sum += current + 1;
                }
            } 
            else if (i == matrix.size() - 1) // last row
            {
                if (j == 0) // bottom left corner
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int right = matrix[i][j+1];
                    if (current < top && current < right)
                        sum += current + 1;
                }
                else if (j == matrix[i].size() - 1) // bottom right corner
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    if (current < top && current < left)
                        sum += current + 1;
                }
                else // rest of last row
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    int right = matrix[i][j+1];
                    if (current < top && current < left && current < right)
                        sum += current + 1;
                }
            }
            else // other rows
            {
                if (j == 0) // left margin
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int right = matrix[i][j+1];
                    int bottom = matrix[i+1][j];
                    if (current < top && current < right && current < bottom)
                        sum += current + 1;
                }
                else if (j == matrix[i].size() - 1) // right margin
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    int bottom = matrix[i+1][j];
                    if (current < top && current < left && current < bottom)
                        sum += current + 1;
                }
                else // rest of current row
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    int bottom = matrix[i+1][j];
                    int right = matrix[i][j+1];
                    if (current < top && current < left && current < bottom && current < right)
                        sum += current + 1;
                }
            }
        }
    }
    cout << sum << endl;
}

int calculateBasin(vector<vector<int>>& matrix, int i, int j, int lock)
{
    //vector<vector<int>> matrix = inputMatrix;
    int counter = 0;
    matrix[i][j] = -1;
    if (i + 1 < matrix.size() && matrix[i+1][j] < 9 && matrix[i+1][j] >= 0 && lock != 2) //expand to the down and call recursively
    {
        ////cout << "step down at " << i+1 << "," << j << endl;
        counter++;
        counter += calculateBasin(matrix, i+1, j, 1);
        
    }
    if (i - 1 >= 0 && matrix[i-1][j] < 9 && matrix[i-1][j] >= 0 && lock != 1) //expand to the up and call recursively
    {
        //cout << "step up at " << i-1 << "," << j << endl;
        counter++;
        counter += calculateBasin(matrix, i-1, j, 2);
        
    }
    if (j + 1 < matrix[i].size() && matrix[i][j+1] < 9 && matrix[i][j+1] >= 0 && lock != 4) // expand to the right and call recursively
    {
        //cout << "step right at " << i << "," << j+1 << endl;
        counter++;
        counter += calculateBasin(matrix, i, j+1, 3);
        
    }
    if (j - 1 >= 0 && matrix[i][j-1] < 9 && matrix[i][j-1] >= 0 && lock != 3)
    {
        //cout << "step left at " << i << "," << j-1 << endl;
        counter++;
        counter += calculateBasin(matrix, i, j-1, 4);
        
    }
    return counter;
}

void partTwo()
{
    vector<vector<int>> matrix;
    ifstream myfile("input");
    std::string inputLine;

    while (getline(myfile, inputLine))
    {
        vector<int> thisLine;
        for (char const &c: inputLine) 
        {
            int a = c - '0';
            thisLine.push_back(a);
        }
        matrix.push_back(thisLine);
    }
    int sum = 0;
    vector<int> basins;
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if ( i == 0 ) // first row
            {
                if (j == 0) // top left corner
                {
                    int current = matrix[i][j];
                    int bottom = matrix[i+1][j];
                    int right = matrix[i][j+1];
                    if (current < bottom && current < right)
                        sum += current + 1;

                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                    
                }
                else if (j == matrix[i].size() - 1) // top right corner
                {
                    int current = matrix[i][j];
                    int bottom = matrix[i+1][j];
                    int left = matrix[i][j-1];
                    if (current < bottom && current < left)
                        sum += current + 1;

                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                }
                else // rest of first row
                {
                    int current = matrix[i][j];
                    int bottom = matrix[i+1][j];
                    int left = matrix[i][j-1];
                    int right = matrix[i][j+1];
                    if (current < bottom && current < left && current < right)
                        sum += current + 1;
                    
                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                }
            } 
            else if (i == matrix.size() - 1) // last row
            {
                if (j == 0) // bottom left corner
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int right = matrix[i][j+1];
                    if (current < top && current < right)
                        sum += current + 1;
                }
                else if (j == matrix[i].size() - 1) // bottom right corner
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    if (current < top && current < left)
                        sum += current + 1;

                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                }
                else // rest of last row
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    int right = matrix[i][j+1];
                    if (current < top && current < left && current < right)
                        sum += current + 1;

                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                }
            }
            else // other rows
            {
                if (j == 0) // left margin
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int right = matrix[i][j+1];
                    int bottom = matrix[i+1][j];
                    if (current < top && current < right && current < bottom)
                        sum += current + 1;

                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                }
                else if (j == matrix[i].size() - 1) // right margin
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    int bottom = matrix[i+1][j];
                    if (current < top && current < left && current < bottom)
                        sum += current + 1;

                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                }
                else // rest of current row
                {
                    int current = matrix[i][j];
                    int top = matrix[i-1][j];
                    int left = matrix[i][j-1];
                    int bottom = matrix[i+1][j];
                    int right = matrix[i][j+1];
                    if (current < top && current < left && current < bottom && current < right)
                        sum += current + 1;

                    int basin = calculateBasin(matrix, i, j, 0);
                    if (basin > 0)
                    {
                        //cout << "Basin: " << basin << endl;
                        basins.push_back(basin);
                    }
                }
            }
        }
    }
    cout << sum << endl;

    vector<int> topThree(3);
    partial_sort_copy(basins.begin(), basins.end(), topThree.begin(), topThree.end(), greater<int>());


    int result = topThree[0] * topThree[1] * topThree[2];
    cout << result << endl;
}



int main()
{
    partOne();
    partTwo();
    return 0;
}