#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>


using namespace std;

size_t intersectionSize(const string& a, const string& b)
{
    string tmp;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(tmp));
    return tmp.size();
}

vector<string>::const_iterator findByIntersectionSize(const vector<string>& v, const string& other, int size)
{
    return find_if(v.begin(), v.end(), [&](const auto& s) { return intersectionSize(s, other) == size; });
}


void partOne()
{
    ifstream myfile("input");
    std::string inputLine;
    vector<string> outputs;
    vector<string> inputs;

    //read lines
    while (getline(myfile, inputLine))
    {        
        stringstream ss( inputLine );
        
        // fill vector of input codes
        string substr;
        getline( ss, substr, '|' );
        inputs.push_back( substr );

        //fill vector of output codes  
        getline(ss, substr, '|');
        outputs.push_back(substr);
        cout << inputs.size() << " | " << outputs.size() << endl;
    }
    int uniqueCntr = 0;

    for ( string output : outputs)
    {
        stringstream ss( output );
        while(ss.good())
        {
            string substr;
            getline( ss, substr, ' ' );
            if (substr.size() == 2 || substr.size() == 4 || substr.size() == 3 || substr.size() == 7) //check for 1, 4, 7, 8
                uniqueCntr++;
        }
    }
    cout << uniqueCntr << endl;
}

void partTwo()
{
    ifstream myfile("input");
    std::string inputLine;
    int sum = 0;

    //read lines
    while (getline(myfile, inputLine))
    {        
        stringstream ss( inputLine );
        
        // get input string
        string input;
        getline( ss, input, '|' );

        //get output string 
        string output;
        getline(ss, output, '|');


        //determine solutions
        unordered_map<string, int> solutions;
        unordered_map<int, string> solutionsReversed;
        vector<string> unknown5, unknown6;
        stringstream st( input );
        while(st.good())
        {
            string substr;
            getline( st, substr, ' ' );
            sort(substr.begin(), substr.end());
            
            switch(substr.size()) //save known digits
            {
                case 2: 
                    solutions[substr] = 1;
                    solutionsReversed[1] = substr;
                    break;
                case 4:
                    solutions[substr] = 4;
                    solutionsReversed[4] = substr;
                    break;
                case 3:
                    solutions[substr] = 7;
                    solutionsReversed[7] = substr;
                    break;
                case 7:
                    solutions[substr] = 8;
                    solutionsReversed[8] = substr;
                    break;
                case 5:
                    unknown5.push_back(substr);
                    break;
                case 6:
                    unknown6.push_back(substr);
                    break;
            }
        }

        //determine 3 - intersects on 3 lines with 7 (full 7 inside 3)
        auto it = findByIntersectionSize(unknown5, solutionsReversed[7], 3);
        solutions[*it] = 3;
        solutionsReversed[3] = *it;
        unknown5.erase(it);

        //unknown5: 5, 2; unknown6: 0, 6, 9

        // determine 5 - intersects 4 on 3 lines (2 only has 2 intersections with 4)
        it = findByIntersectionSize(unknown5, solutionsReversed[4], 3);
        solutions[*it] = 5;
        solutionsReversed[5] = *it;
        unknown5.erase(it);

        //determine 2 - rest of unknown5
        solutions[unknown5[0]] = 2;
        solutionsReversed[2] = unknown5[0];

        //determine 9 - has 5 intersections with 3 (0 and 6 only have 4)
        it = findByIntersectionSize(unknown6, solutionsReversed[3], 5);
        solutions[*it] = 9;
        solutionsReversed[9] = *it;
        unknown6.erase(it);

        //determine 6 - 6 has 5 intersections with 5 (0 only has 4, 9 would have had 5)
        it = findByIntersectionSize(unknown6, solutionsReversed[5], 5);
        solutions[*it] = 6;
        solutionsReversed[6] = *it;
        unknown6.erase(it);

        //determine 0 - rest of unkown6
        solutions[unknown6[0]] = 0;
        solutionsReversed[0] = unknown6[0];


        //determine ouput
        stringstream stt( output );
        string result;
        string substr;
        getline( stt, substr, ' ' );
        while(stt.good())
        {
            string substr;
            getline( stt, substr, ' ' );
            sort(substr.begin(), substr.end());
            //cout << substr << " translates to " << solutions[substr] << endl;
            result += to_string(solutions[substr]);
        } 
        cout << result << endl;   
        sum += stoi(result);

        /*cout << "solutionsReversed: " << solutionsReversed.size() << endl;
        cout << "1: " << solutionsReversed[1] << endl;
        cout << "4: " << solutionsReversed[4] << endl;
        cout << "7: " << solutionsReversed[7] << endl;
        cout << "8: " << solutionsReversed[8] << endl;
        cout << "3: " << solutionsReversed[3] << endl;
        cout << "5: " << solutionsReversed[5] << endl;
        cout << "2: " << solutionsReversed[2] << endl;
        cout << "9: " << solutionsReversed[9] << endl;
        cout << "0: " << solutionsReversed[0] << endl;
        cout << "6: " << solutionsReversed[6] << endl;
        */                  
    }    
    cout << "final sum: " << sum << endl;
}

int main()
{
    partOne();
    partTwo();
    return 0;
}