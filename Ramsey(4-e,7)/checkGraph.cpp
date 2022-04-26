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
#include <random>
#include <map>
#include <array>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair
int indices[100][100];
vector<pi> allEdges;
vector<vector<pi>> graphs;
vector<vector<pi>> reg4;
vector<vector<pi>> reg5;

int adj[100][100];

int getIndex(pi K)
{
  return indices[K.first][K.second];
  // auto it = find(v.begin(), v.end(), K);
  // if (it != v.end())
  //   return it - v.begin();
  // else
  //   return -1;
}

int getIndex2(vector<int> v, int K)
{
  auto it = find(v.begin(), v.end(), K);
  if (it != v.end())
    return it - v.begin();
  else
    return -1;
}

//Helper to get index of B_(i,j)
int indexB(int i, int j, int n, int k, int start)
{
  return start + i * k + j;
}

// Helper Function to return A <=> AND((X_i)s)
void encodeIff(int A, vector<int> X){
    
    for(int x:X){
      cout << -1 * A << " " << x << " " << 0 << "\n";
    }
    
    cout << A << " ";
    for(int x:X){
      cout << -1 * x << " ";
    } 
    cout << 0 << "\n";
}

//Unary Adder
//Also, we need room to write additional n * k variables which is indexed from start, start+1, ..., start+n*k-1, last k bits from start + (n-1)*k to end represent the final sum
//The unary bit B_(i,j), for which i encodes we are summing up to X_(Xs[i]) and the largest j with bit 1 represents the sum so far, so 1111 represents 4
//We do index start + i * k + j as the bit B_(i,j)
void unaryAdderWithPredicate(int n, int k, vector<int> Xs, int start, string pred)
{
  //This writes all, for i in range (0,n), not X_(Xs[i]) or B_(i,0)
  for (int i = 0; i < n; i++)
  {
    cout << pred << "-" << Xs[i] << " " << indexB(i, 0, n, k, start) << " " << 0 << "\n";
  }

  //This ensures that we never write a 1 in the top row until column i, where X_(Xs[i]) is the first 1
  for (int i = 0; i < n; i++)
  {
    if (i == 0)
    {
      cout << pred << Xs[i] << " "
           << "-" << indexB(i, 0, n, k, start) << " " << 0 << "\n";
    }
    else
    {
      cout << pred << "-" << indexB(i, 0, n, k, start) << " " << indexB(i - 1, 0, n, k, start) << " " << Xs[i] << " " << 0 << "\n";
    }
  }

  //This writes that all B_(0,j), j>=1
  for (int j = 1; j < k; j++)
  {
    cout << pred << "-" << indexB(0, j, n, k, start) << " " << 0 << "\n";
  }

  //This writes the propagation forwards, so if we have a 1 in a row, all future columns will have a 1 in that row
  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < k; j++)
    {
      cout << pred << "-" << indexB(i - 1, j, n, k, start) << " " << indexB(i, j, n, k, start) << " " << 0 << "\n";
    }
  }

  //This ensures that we add an extra 1 to column i if X_(Xs[i]) is a 1
  for (int i = 1; i < n; i++)
  {
    for (int j = 1; j < k; j++)
    {
      cout << pred << "-" << Xs[i] << " "
           << "-" << indexB(i - 1, j - 1, n, k, start) << " " << indexB(i, j, n, k, start) << " " << 0 << "\n";
    }
  }

  //This ensures that we propagate zeros forwards for rows >=1 unless we need to add
  for (int i = 1; i < n; i++)
  {
    for (int j = 1; j < k; j++)
    {
      cout << pred << "-" << indexB(i, j, n, k, start) << " " << indexB(i - 1, j, n, k, start) << " " << indexB(i - 1, j - 1, n, k, start) << " " << 0 << "\n";
      cout << pred << "-" << indexB(i, j, n, k, start) << " " << indexB(i - 1, j, n, k, start) << " " << Xs[i] << " " << 0 << "\n";
    }
  }

  //This checks to ensure that no overflow occurs (sum >=k)
  for (int i = 1; i < n; i++)
  {
    cout << pred << "-" << Xs[i] << " "
         << "-" << indexB(i - 1, k - 1, n, k, start) << " " << 0 << "\n";
  }
}

//We want to write an encoding for =K on n variables in the vector Xs (so X_1, X_3, X_4, X_7, X_9) for example would be (1,3,4,7,9)
//Also, we need room to write additional b * (k+1) variables which is indexed from start, start+1, ..., start+(n-1)*k-1
//The unary bit B_(i,j), for which i encodes we are summing up to X_(Xs[i]) and the largest j with bit 1 represents the sum so far
//We do index start + i * k + j as the bit B_(i,j)
//This is done using the Sinz sequential encoding for <=k in addition to ensuring that we never "add" when it's not necessary
//Adds predicate in front of each clause
void encodeEqualsKWithPredicate(int n, int k, vector<int> Xs, int start, string pred)
{
  //We don't do anything for n=0
  if (n == 0)
    return;
  //This means the variables start + (n-1) * (k+1) to start + n * (k+1) - 1 are the final sum in unary
  unaryAdderWithPredicate(n, k + 1, Xs, start, pred);

  //This checks if the final sum is exactly k and not k+1
  cout << pred << -1 * (start + (n - 1) * (k + 1) + k) << " " << 0 << "\n";
  if (k != 0)
  {
    cout << pred << start + (n - 1) * (k + 1) + k - 1 << " " << 0 << "\n";
  }
}

void encodeEqualsKWithoutPredicate(int n, int k, vector<int> Xs, int start)
{
  encodeEqualsKWithPredicate(n, k, Xs, start, "");
}

//I'm going to create helper variables H_i = Xs[i] AND Ys[i]
//Then, we just need to check if the helper variables sum to l if b is true (b would usually be if an edge exists or not), else its m
//Uses n * (l+2) new variables
void encodeDotProdEqualsKOrL(int b, int n, int l, vector<int> Xs, vector<int> Ys, int start)
{

  //Creating n helper variables
  for (int i = 0; i < n; i++)
  {
    cout << -1 * (start + i) << " " << Xs[i] << " " << 0 << "\n";
    cout << -1 * (start + i) << " " << Ys[i] << " " << 0 << "\n";
    cout << (start + i) << " " << -1 * Xs[i] << " " << -1 * Ys[i] << " " << 0 << "\n";
  }

  vector<int> helpers;
  for (int i = 0; i < n; i++)
  {
    helpers.PB(start + i);
  }

  string pred = to_string(-1 * b).append(" ");
  //Uses another n * (l+1) variables
  encodeEqualsKWithPredicate(n, l, helpers, start + n, pred);
}

//Encodes that Xs is lexicographically before Ys
//l is the length of the array
//Uses additional variables start to start+l-2 to represent whether xi = yi
//Uses additional variables start+l-1 to start+2*l-2 to represent whether xi <= yi
//Uses additional variables start+2*l-1 to start+3*l-3 to represent whether start and ... and start+i are true
//In total, uses 3 * l - 2 additional variables
void writeLexicoWithPred(vector<int> Xs, vector<int> Ys, int l, int start, string pred)
{
  //Writes the additional variables representing xi = yi
  for (int i = 0; i < l - 1; i++)
  {
    cout << pred <<  -1 * Xs[i] << " " << -1 * Ys[i] << " " << (start + i) << " " << 0 << "\n";
    cout << pred << -1 * Xs[i] << " " << Ys[i] << " " << -1 * (start + i) << " " << 0 << "\n";
    cout << pred << Xs[i] << " " << -1 * Ys[i] << " " << -1 * (start + i) << " " << 0 << "\n";
    cout << pred << Xs[i] << " " << Ys[i] << " " << (start + i) << " " << 0 << "\n";
  }

  //Writes the additional variables representing xi <= yi
  for (int i = 0; i < l; i++)
  {
    cout << pred << -1 * Xs[i] << " " << Ys[i] << " " << -1 * (start + l - 1 + i) << " " << 0 << "\n";
    cout << pred << Xs[i] << " " << (start + l - 1 + i) << " " << 0 << "\n";
    cout << pred << -1 * Ys[i] << " " << (start + l - 1 + i) << " " << 0 << "\n";
  }

  //Writes the additional variables representing start and ... and start + i
  for (int i = 0; i < l - 1; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      cout << pred << -1 * (start + 2 * l - 1 + i) << " " << start + j << " " << 0 << "\n";
    }
    cout << pred << (start + 2 * l - 1 + i) << " ";
    for (int j = 0; j <= i; j++)
    {
      cout << -1 * (start + j) << " ";
    }
    cout << 0 << "\n";
  }

  //Write that x1 <= y1
  cout << pred << start + l - 1 << " " << 0 << "\n";

  //Write that if x1 = y1 and x2 = y2 and ... and xi = yi then xi+1 <= yi+1
  for (int i = 1; i < l; i++)
  {
    cout << pred << -1 * (start + 2 * l - 1 + (i - 1)) << " " << start + l - 1 + i << " " << 0 << "\n";
  }
}

// We'll create a tuple of the number of ((1,1)s + (1,0)s, (0,1)s)
// Return the start to end indices of these tuples in unary as a vector<vector<int>> 
// Uses a total of 2n*n + n variables
vector<vector<int>> encodePairSumsWithPredicate(vector<int> AEdges, vector<int> BEdges, int start, string pred)
{
  int n = AEdges.size();
  
  // First, we get the number of 1s in AEdges at start + (n-1)*n to start + n*n - 1
  unaryAdderWithPredicate(n,n,AEdges,start,pred);
  vector<int> AEdgesOnes;
  for(int i=start+(n-1)*n; i<start + n * n; i++){
    AEdgesOnes.PB(i);
  }
  
  // We reset the start
  start += n * n;
  
  // Define helpers to be number of (0,1)s
  vector<int> helpers;
  for(int i=0; i<n;i++){
    helpers.PB(start + i);
  }
  
  // Encode helpers[i] <=> not AEdges[i] and BEdges[i]
  for(int i=0; i<n; i++){
    vector<int> Xis;
    Xis.PB(-1 * AEdges[i]);
    Xis.PB(BEdges[i]);
    encodeIff(helpers[i], Xis);
  }

  // Increment start again
  start += n;

  // Get sum of helpers 
  unaryAdderWithPredicate(n,n,helpers,start,pred);
  vector<int> zeroOnes;
  for(int i=start+(n-1)*n; i<start + n * n; i++){
    zeroOnes.PB(i);
  }

  vector<vector<int>> output;
  output.PB(AEdgesOnes);
  output.PB(zeroOnes);
  return output;
}


void neighGraph(vector<pi> graph)
{
  for (pi a : graph)
  {
    cout << a.first * a.second << " " << 0 << endl;
  }
}

//Encodes that all n variables are all not true
void writeRamseyK(vector<int> Xs)
{
  for (int i = 0; i < Xs.size(); i++)
  {
    cout << -1 * Xs[i] << " ";
  }
  cout << 0 << "\n";
}

//Encodes that all but one of the n variables are all not true
void writeRamseyKminusE(vector<int> Xs)
{
  for (int j = 0; j < Xs.size(); j++){
    for (int i = 0; i < Xs.size(); i++)
    {
      if(i==j){
        cout << Xs[i] << " ";
      }
      else{
        cout << -1 * Xs[i] << " ";
      }
    }
    cout << 0 << "\n";
  }
}

//Encodes that all variables are all not false
void writeRamseyI(vector<int> Xs)
{
  for (int i = 0; i < Xs.size(); i++)
  {
    cout << Xs[i] << " ";
  }
  cout << 0 << "\n";
}

//Encodes that all but one of the n variables are all not false
void writeRamseyIminusE(vector<int> Xs)
{
  for (int j = 0; j < Xs.size(); j++){
    for (int i = 0; i < Xs.size(); i++)
    {
      if(i==j){
        cout << -1 * Xs[i] << " ";
      }
      else{
        cout << Xs[i] << " ";
      }
    }
    cout << 0 << "\n";
  }
}


//Encodes that all variables are equal
void writeEqual(vector<int> Xs)
{
  for (int i = 0; i < Xs.size()-1; i++)
  {
    cout << Xs[i] << " " << -1 * Xs[i+1] << " 0" << "\n";
    cout << -1 * Xs[i] << " " << Xs[i+1] << " 0" << "\n";
  }
}


string vectorToString(vector<int> v){
  string str = "[";
  bool first = true;
  for(int x : v){
    if(!first){
      str+=", ";
    } else{
      first = false;
    }
    str += to_string(x);     
  }
  str += "]";
  return str;
}

int main(int argc, char *argv[])
{
  int N = 20;
  

  //Offset edges by 1
  allEdges.PB(MP(-1, -1));

  int tempCounter = 1;

  for (int i = 1; i < N; i++)
  {
    for (int j = i + 1; j <= N; j++)
    {
      allEdges.PB(MP(i, j));
      indices[i][j]=tempCounter;
      indices[j][i]=tempCounter;
      tempCounter++;
    }
  }


  string inString = "";
  inString.append("temp(4-e,6)20");
  inString.append(".txt");

  freopen(inString.c_str(), "r", stdin);

  int tt;
  cin >> tt;

  for (int t = 0; t < tt; t++)
  {

    // vector<pi> edges;
    // for (int i = 1; i <= N; i++)
    // {
    //   for (int j = 1; j <= N; j++)
    //   {
    //     int temp;
    //     cin >> temp;
    //     adj[i-1][j-1] = temp;
    //   }
    // }

    for(int i=0; i<N;i++){
        for(int j=i+1; j<N;j++){
            int temp;
            cin >> temp;
            if (temp > 0){
                adj[i][j] = 1;
                adj[j][i] = 1;
            } else{
                adj[i][j] = 0;
                adj[j][i] = 0;
            }
        }
    }
    int temp;
    cin >> temp;



    // Checks R4-e,7 goodness

    int vs[7];

    for (vs[0] = 1; vs[0] <= N; vs[0]++)
    {
      for (vs[1] = vs[0] + 1; vs[1] <= N; vs[1]++)
      {
        for (vs[2] = vs[1] + 1; vs[2] <= N; vs[2]++)
        {
          for (vs[3] = vs[2] + 1; vs[3] <= N; vs[3]++)
          {
            for (vs[4] = vs[3] + 1; vs[4] <= N; vs[4]++)
            {
              for (vs[5] = vs[4] + 1; vs[5] <= N; vs[5]++)
              {
                for (vs[6] = vs[5] + 1; vs[6] <= N; vs[6]++)
                {
                  int edgeCount = 0;
                  for(int i=0;i<7;i++){
                    for(int j=i+1;j<7;j++){
                      if(adj[vs[i]-1][vs[j]-1] == 1){
                          edgeCount++;
                      }      
                    }
                  }
                  if(edgeCount == 0){
                      cout << t << " FAILED I7 " << endl;
                      for (int i=0; i<7; i++){
                          cout << vs[i] << " ";

                      }
                      cout << endl;
                      return 0;
                  }
                }
              }
            }
          }
        }
      }
    }

    for (vs[0] = 1; vs[0] <= N; vs[0]++)
    {
      for (vs[1] = vs[0] + 1; vs[1] <= N; vs[1]++)
      {
        for (vs[2] = vs[1] + 1; vs[2] <= N; vs[2]++)
        {
          for (vs[3] = vs[2] + 1; vs[3] <= N; vs[3]++)
          {
            int edgeCount = 0;
            for(int i=0;i<4;i++){
            for(int j=i+1;j<4;j++){
              if(adj[vs[i]-1][vs[j]-1] == 1){
                edgeCount++;
              }      
            }
            }
            if(edgeCount >= 4*3/2-1){
              cout << t << " FAILED K4-e " << endl;
              return 0;
            }
          }
        }
      }
    }
  }

  return 0;
}