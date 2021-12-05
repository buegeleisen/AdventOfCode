#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


struct Board 
{
    int matrix[5][5];
    void setValue(int x, int y, int value);
};

void Board::setValue(int x, int y, int value)
{
    matrix[x][y] = value;
}

void printMatrix(Board board)
{
    for ( int i = 0; i < 5; i++)
    {
        for  ( int j = 0 ; j <5; j++)
        {
            cout << board.matrix[i][j] << " ";
        }
        cout << endl; 
    }
    cout << " " << endl;
}

void partOne()
{
    ifstream myfile("input");
    std::string inputLine;
    
    //read drawn numbers
    getline(myfile, inputLine);
    stringstream ss( inputLine );
    vector<int> numbers;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        numbers.push_back( stoi(substr ));
    }

    //read all boards
    vector<Board> boards;
    int i = 0;
    while (getline(myfile, inputLine))
    {
        Board board;
        if (i == 0)
        {
            //empty line, do nothin
        }
        else
        {
            stringstream ss( inputLine );
            ss >> board.matrix[i-1][0] >> board.matrix[i-1][1] >> board.matrix[i-1][2] >> board.matrix[i-1][3] >> board.matrix[i-1][4];
        }      
        
        i++;
        if ( i == 6 )
        {
            i = 0; 
            boards.push_back(board);
        }
    }


    //check winner
    bool finished = false;
    for ( int i = 0; i < numbers.size(); i++)
    {
        if(!finished)
        {
            for (int y = 0; y < boards.size(); ++y)
            {
                for ( int j = 0; j < 5; j++)
                {
                    for ( int k = 0; k < 5; k++)
                    {
                        if ( boards[y].matrix[j][k] == numbers[i])
                        {
                            Board newBoard = boards[y];
                            newBoard.setValue(j, k, -1);
                            boards.at(y) = newBoard;
                            if ( (boards[y].matrix[0][k] == -1 && boards[y].matrix[1][k] == -1 
                                && boards[y].matrix[2][k] == -1 && boards[y].matrix[3][k] == -1 
                                && boards[y].matrix[4][k] == -1 ) || (boards[y].matrix[j][0] == -1 
                                && boards[y].matrix[j][1] == -1 && boards[y].matrix[j][2] == -1 
                                && boards[y].matrix[j][3] == -1 && boards[y].matrix[j][4] == -1) )
                            {
                                //BINGO
                                cout << "BINGO" << endl;
                                int sum = 0;
                                for ( int x = 0; x < 5; x++)
                                {
                                    for (int z = 0; z < 5; z++)
                                    {
                                        if (boards[y].matrix[x][z] != -1)
                                            sum += boards[y].matrix[x][z];
                                    }
                                }
                                int result = numbers[i] * sum;
                                cout << result << endl;
                                finished = true;
                            }
                        }
                    }
                }
                //printMatrix(boards[y]);
            }
        }
    }
}

void partTwo()
{
    ifstream myfile("input");
    std::string inputLine;
    
    //read drawn numbers
    getline(myfile, inputLine);
    stringstream ss( inputLine );
    vector<int> numbers;
    while( ss.good() )
    {
        string substr;
        getline( ss, substr, ',' );
        numbers.push_back( stoi(substr ));
    }

    //read all boards
    vector<Board> boards;
    int i = 0;
    while (getline(myfile, inputLine))
    {
        Board board;
        if (i == 0)
        {
            //empty line, do nothin
        }
        else
        {
            stringstream ss( inputLine );
            ss >> board.matrix[i-1][0] >> board.matrix[i-1][1] >> board.matrix[i-1][2] >> board.matrix[i-1][3] >> board.matrix[i-1][4];
        }      
        
        i++;
        if ( i == 6 )
        {
            i = 0; 
            boards.push_back(board);
        }
    }


    //check winner
    int boardsCount = boards.size();
    bool finished = false;
    for ( int i = 0; i < numbers.size(); i++)
    {
        if(!finished)
        {
            for (int y = 0; y < boards.size(); ++y)
            {
                for ( int j = 0; j < 5; j++)
                {
                    for ( int k = 0; k < 5; k++)
                    {
                        if ( boards[y].matrix[j][k] == numbers[i])
                        {
                            Board newBoard = boards[y];
                            newBoard.setValue(j, k, -1);
                            boards.at(y) = newBoard;
                            if ( (boards[y].matrix[0][k] == -1 && boards[y].matrix[1][k] == -1 
                                && boards[y].matrix[2][k] == -1 && boards[y].matrix[3][k] == -1 
                                && boards[y].matrix[4][k] == -1 ) || (boards[y].matrix[j][0] == -1 
                                && boards[y].matrix[j][1] == -1 && boards[y].matrix[j][2] == -1 
                                && boards[y].matrix[j][3] == -1 && boards[y].matrix[j][4] == -1) )
                            {
                                //BINGO
                                int sum = 0;
                                for ( int x = 0; x < 5; x++)
                                {
                                    for (int z = 0; z < 5; z++)
                                    {
                                        if (boards[y].matrix[x][z] != -1)
                                            sum += boards[y].matrix[x][z];
                                    }
                                }
                                int result = numbers[i] * sum;
                                if(boardsCount == 1){
                                    finished = true;
                                    cout << "LAST BINGO at number " << numbers[i] <<  endl;
                                    cout << result << endl;
                                    printMatrix(boards[y]);
                                }
                                else{
                                    boardsCount--;
                                }
                                //invalidate board
                                for (int c = 0; c < 5; ++c)
                                {
                                    for (int d = 0; d < 5; ++d)
                                    {
                                        Board invalidationBoard = boards[y];
                                        invalidationBoard.setValue(c, d, -2);
                                        boards.at(y) = invalidationBoard;
                                    }
                                }
                            }
                        }
                    }
                }
                //printMatrix(boards[y]);
            }
        }
    }
}

int main()
{
    
    partOne();
    cout << "-------------" << endl;
    partTwo();
    return 0;
}