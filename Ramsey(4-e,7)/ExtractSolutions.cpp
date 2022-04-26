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
#include <stdexcept>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

vector<string> split(const string &text, char sep) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos) {
        if (end != start) {
          tokens.push_back(text.substr(start, end - start));
        }
        start = end + 1;
    }
    if (end != start) {
       tokens.push_back(text.substr(start));
    }
    return tokens;
}

bool isCorrectLine(string str, int numEdges){
   vector<string> tokens = split(str, ' ');

   if(tokens.size() != numEdges + 1){
      return false;
   }
   for(int i=1;i<=numEdges; i++){
      if(stoi(tokens[i-1]) != i && stoi(tokens[i-1]) != -1 * i) return false;
   }
   return true;
}

string flipSigns(string str){
   string out = "";
   vector<string> tokens = split(str, ' ');
   for(int i=0;i<tokens.size(); i++){
      out.append(to_string(-1 * stoi(tokens[i])));
      out.append(" ");
   }
   return out;
}

int main(int argc, char *argv[])
{
   //Takes in arguments ./-.exe fileName N
   if(argc<3){
      throw 1;
   }

   int numSolns = 0;
   ofstream out;

   string outname=argv[1];
   outname.erase(outname.find(".out"), outname.length());
   outname.append("Graphs.txt");

   int N = stoi(argv[2]);

   int numEdges = N * (N-1) / 2;

   string iFileName = argv[1];

   out.open(outname.c_str());

   string output = "";

   ifstream iFile(iFileName.c_str());       
   string temp;

   int counterFail = 2;

   while (getline(iFile,temp)) 
   {
      
      if (isCorrectLine(temp, numEdges)) {
         output.append(flipSigns(temp));
         output.append("\n");
         counterFail = 2;
         numSolns++;
      } else if(counterFail-- < 0){
         output = "";
         counterFail = 4;
         numSolns = 0;
      }
   }

   out << numSolns << endl;

   out << output << endl;

   out.close();

   iFile.close();

   return 0;

}