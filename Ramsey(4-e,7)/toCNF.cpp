#include <algorithm>
#include <bitset>
#include <iterator>
#include <math.h>
#include <new>
#include <numeric>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <array>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
 
#define F first
#define S second
#define PB push_back
#define MP make_pair

int main(int argc, char *argv[])
{
    //Takes in arguments ./-.exe filename
    if(argc<2){
        throw 1;
    }

    freopen(argv[1],"r",stdin);

    string outname=argv[1];
    outname.erase(outname.find(".out"), outname.length());
    outname.append(".cnf");

    freopen(outname.c_str(), "w", stdout);

    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);

    int zeros=0;
    int maximum = 0;

    cout << "c  " << outname << endl;
    cout << "c" << endl;
    
    string outputFirst = "";
    string outputSecond = "";

    string currLine = "";
    int currVar = 0;

    string temp;

    while(cin >> temp){
        if(temp.compare("0")==0){
            if(currVar ==1){
                currLine.append("0\n");
                outputFirst.append(currLine);
                currLine = "";
                currVar = 0;
            }
            else{
                currLine.append("0\n");
                outputSecond.append(currLine);
                currLine = "";
                currVar = 0;
            }
            zeros++;
        }
        else{
            maximum = max(maximum, abs(stoi(temp)));
            currLine.append(temp);
            currLine.append(" ");
            currVar++;
        }
    }

    cout << "p cnf " << maximum << " " << zeros << endl;
    cout << outputFirst.append(outputSecond);

    return 0;
}