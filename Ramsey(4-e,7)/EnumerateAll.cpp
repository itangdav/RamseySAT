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
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

int main(int argc, char *argv[])
{
  //Takes in arguments ./-.exe coreString N
  if (argc < 3)
  {
    throw 1;
  }

  ofstream out;

  string coreString = argv[1];

  int N = stoi(argv[2]);

  int numEdges = N * (N - 1) / 2;

  string outname = "\'";
  outname.append(coreString);
  outname.append(".out\'");

  string outname2 = outname;
  outname2.erase(outname2.find(".out\'"), outname2.length());
  outname2.append(".cnf\'");

  string outname3 = "\'";
  outname3.append(coreString);
  outname3.append("proof.txt\'");

  string openName = "";
  openName.append(coreString);
  openName.append(".out");

  string iFileName = "";
  iFileName.append(coreString);
  iFileName.append("proof.txt");

  bool run = true;
  

  while (run)
  {

    system(("./toCNF.exe " + outname).c_str());
    system(("../../cadical/build/cadical " + outname2 + " -w " + outname3).c_str());

    out.open(openName.c_str(), ios::app);

    string newClause = "";

    ifstream iFile(iFileName.c_str());
    string temp;

    bool done = false;

    while (getline(iFile, temp) && !done)
    {

      if (temp.find("UNSATISFIABLE") != std::string::npos)
      {
        run = false;
        break;
      }
      else
      {
        std::stringstream lineStream(temp);
        std::string token;
        while (lineStream >> token)
        {
          char *p;
          long converted = strtol(token.c_str(), &p, 10);
          if (*p)
          {
          }
          else
          {
            newClause.append(to_string(-1 * converted));
            newClause.append(" ");
            if (converted == numEdges || converted == -numEdges)
            {
              done = true;
              break;
            }
          }
        }
      }
    }

    newClause.append("0");

    out << newClause << endl;

    out.close();

    iFile.close();
  }

  return 0;
}