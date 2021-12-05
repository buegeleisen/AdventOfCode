#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

struct Point
{
    int x, y;
};

struct Line
{
    Point start;
    Point end;
};


void printLines(vector<Line> lines)
{
    for(Line line : lines)
    {
        cout << line.start.x << "," << line.start.y << " -> " << line.end.x << "," << line.end.y << endl;
    }
}



tuple<int, int> findMax(vector<Line> lines)
{
    int maxX = 0;
    int maxY = 0;
    for(Line line : lines)
    {
        if (line.start.x > maxX )
            maxX = line.start.x;
        if (line.start.y > maxY )
            maxY = line.start.y;
        if (line.end.x > maxX)
            maxX = line.end.x;
        if (line.end.y > maxY)
            maxY = line.end.y;
    }
    return make_tuple(maxX, maxY);
}

void partOne()
{   
    vector<Line> lines;
    ifstream myfile("input");
    std::string inputLine;
    while(getline(myfile, inputLine))
    {
        string coords = regex_replace(inputLine, std::regex(" -> "), ",");
        stringstream ss(coords);
        string substr;
        getline( ss, substr, ',' );
        Line line;
        line.start.x = stoi(substr);
        getline( ss, substr, ',' );
        line.start.y = stoi(substr);
        getline( ss, substr, ',' );
        line.end.x = stoi(substr);
        getline( ss, substr, ',' );
        line.end.y = stoi(substr);
        lines.push_back(line);
    }
    tuple<int, int> maxima = findMax(lines);

    //create matrix
    char matrix[get<1>(maxima)+1][get<0>(maxima)+1];
    for(int i = 0; i < get<1>(maxima)+1; ++i)
    {
        for (int j = 0; j < get<0>(maxima)+1; ++j)
        {
            matrix[i][j] = '.';
            //cout << matrix[i][j];
        }
        //cout << endl;
    }
    int dangerCounter = 0;
    for (Line line : lines)
    {
        int start = 0;
        int end = 0;
        //vertical
        if(line.start.x == line.end.x)
        {
            if (line.start.y > line.end.y)
            {
                start = line.end.y;
                end = line.start.y;
            }
            else
            {
                end = line.end.y;
                start = line.start.y;
            }

            for (int i = start; i <= end; ++i)
            {
                if(matrix[i][line.start.x] == '.')
                    matrix[i][line.start.x] = '1';
                else
                {
                    int value = matrix[i][line.start.x] - '0';
                    value++;
                    matrix[i][line.start.x] = '0' + value;
                    if (value == 2)
                        dangerCounter++;
                }
            }
        }
        else if(line.start.y == line.end.y) //horizontal
        {
            if (line.start.x > line.end.x)
            {
                start = line.end.x;
                end = line.start.x;
            }
            else
            {
                end = line.end.x;
                start = line.start.x;
            }

            for (int i = start; i <= end; ++i)
            {
                if(matrix[line.start.y][i] == '.')
                    matrix[line.start.y][i] = '1';
                else
                {
                    int value = matrix[line.start.y][i] - '0';
                    value++;
                    matrix[line.start.y][i] = '0' + value;
                    if (value == 2) 
                        dangerCounter++;
                }
            }
        }
    }

    for(int i = 0; i < get<1>(maxima) +1; ++i)
    {
        for (int j = 0; j < get<0>(maxima) +1; ++j)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << dangerCounter << endl;
}

void partTwo()
{   
    vector<Line> lines;
    ifstream myfile("input");
    std::string inputLine;
    while(getline(myfile, inputLine))
    {
        string coords = regex_replace(inputLine, std::regex(" -> "), ",");
        stringstream ss(coords);
        string substr;
        getline( ss, substr, ',' );
        Line line;
        line.start.x = stoi(substr);
        getline( ss, substr, ',' );
        line.start.y = stoi(substr);
        getline( ss, substr, ',' );
        line.end.x = stoi(substr);
        getline( ss, substr, ',' );
        line.end.y = stoi(substr);
        lines.push_back(line);
    }
    tuple<int, int> maxima = findMax(lines);

    //create matrix
    char matrix[get<1>(maxima)+1][get<0>(maxima)+1];
    for(int i = 0; i < get<1>(maxima)+1; ++i)
    {
        for (int j = 0; j < get<0>(maxima)+1; ++j)
        {
            matrix[i][j] = '.';
        }
    }
    int dangerCounter = 0;
    for (Line line : lines)
    {
        int start = 0;
        int end = 0;
        //vertical
        if(line.start.x == line.end.x)
        {
            if (line.start.y > line.end.y)
            {
                start = line.end.y;
                end = line.start.y;
            }
            else
            {
                end = line.end.y;
                start = line.start.y;
            }

            for (int i = start; i <= end; ++i)
            {
                if(matrix[i][line.start.x] == '.')
                    matrix[i][line.start.x] = '1';
                else
                {
                    int value = matrix[i][line.start.x] - '0';
                    value++;
                    matrix[i][line.start.x] = '0' + value;
                    if (value == 2)
                        dangerCounter++;
                }
            }
        }
        else if(line.start.y == line.end.y) //horizontal
        {
            if (line.start.x > line.end.x)
            {
                start = line.end.x;
                end = line.start.x;
            }
            else
            {
                end = line.end.x;
                start = line.start.x;
            }

            for (int i = start; i <= end; ++i)
            {
                if(matrix[line.start.y][i] == '.')
                    matrix[line.start.y][i] = '1';
                else
                {
                    int value = matrix[line.start.y][i] - '0';
                    value++;
                    matrix[line.start.y][i] = '0' + value;
                    if (value == 2) 
                        dangerCounter++;
                }
            }
        }
        else if(line.start.x != line.end.x && line.start.y != line.end.y) //diagonal
        {
            cout << "diagonal" << endl;
            int startX = line.start.x;
            int endX = line.end.x;
            int startY = line.start.y;
            int endY = line.end.y;
            
            int topBorder = startX > endX ? startX : endX;
            int lowBorder = startX > endX ? endX : startX;
            for (int i = lowBorder; i <= topBorder; ++i)
            {
                cout << "Point: " << startX << "," << startY << endl;
                if(matrix[startY][startX] == '.')
                    matrix[startY][startX] = '1';
                else
                {
                    int value = matrix[startY][startX] - '0';
                    value++;
                    matrix[startY][startX] = '0' + value;
                    if (value == 2) 
                        dangerCounter++;
                }
                if (startY < endY)
                    startY++;
                else 
                    startY--;
                if (startX < endX)
                    startX++;
                else 
                    startX--;
            }
        }
    }

    for(int i = 0; i < get<1>(maxima) +1; ++i)
    {
        for (int j = 0; j < get<0>(maxima) +1; ++j)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << dangerCounter << endl;
}

int main()
{
    partOne();
    partTwo();
    return 0;
}