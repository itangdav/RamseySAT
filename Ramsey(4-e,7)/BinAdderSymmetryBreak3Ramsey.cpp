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


// Binary Incrementer 5 bit 
// Increments Xs into Ys if bit C is true assuming no carry/overflow from 5 bits
void fiveBitBinaryIncrementerWithPredicate(vector<int> Xs, vector<int> Ys, int C, string pred)
{
  if(Xs.size() != Ys.size() || Xs.size() != 5){
    throw 1;
  }
  cout << pred << -1 * Xs[3] << " " << -1 * Xs[2] << " " << -1 * Ys[3] << " " << Ys[2] << " " << 0 << "\n";
  cout << pred << Xs[3] << " " << -1 * Xs[2] << " " << Ys[3] << " " << Ys[2] << " " << 0 << "\n";
  cout << pred << Xs[1] << " " << C << " " << -1 * Ys[1] << " " << 0 << "\n";
  cout << pred << -1 * Xs[2] << " " << -1 * Xs[1] << " " << -1 * Xs[0] << " " << -1 * C << " " << -1 * Ys[2] << " " << 0 << "\n";
  cout << pred << Xs[4] << " " << Xs[2] << " " << -1 * Ys[4] << " " << 0 << "\n";
  cout << pred << Xs[2] << " " << -1 * Xs[1] << " " << -1 * Xs[0] << " " << -1 * C << " " << Ys[2] << " " << 0 << "\n";
  cout << pred << -1 * Xs[1] << " " << C << " " << Ys[1] << " " << 0 << "\n";
  cout << pred << -1 * Xs[4] << " " << -1 * Xs[3] << " " << -1 * Ys[4] << " " << Ys[3] << " " << 0 << "\n";
  cout << pred << Xs[3] << " " << Xs[2] << " " << -1 * Ys[3] << " " << 0 << "\n";
  cout << pred << Xs[4] << " " << -1 * Ys[4] << " " << -1 * Ys[2] << " " << 0 << "\n";
  cout << pred << Xs[2] << " " << Xs[1] << " " << -1 * Ys[2] << " " << 0 << "\n";
  cout << pred << Xs[1] << " " << -1 * Xs[0] << " " << -1 * C << " " << Ys[1] << " " << 0 << "\n";
  cout << pred << Xs[4] << " " << -1 * Xs[3] << " " << Ys[4] << " " << Ys[3] << " " << 0 << "\n";
  cout << pred << -1 * Xs[2] << " " << Xs[1] << " " << Ys[2] << " " << 0 << "\n";
  cout << pred << Xs[1] << " " << -1 * Ys[1] << " " << -1 * Ys[0] << " " << 0 << "\n";
  cout << pred << Xs[2] << " " << -1 * Ys[2] << " " << -1 * Ys[1] << " " << 0 << "\n";
  cout << pred << Xs[3] << " " << -1 * Ys[3] << " " << -1 * Ys[2] << " " << 0 << "\n";
  cout << pred << Xs[4] << " " << -1 * Ys[4] << " " << -1 * Ys[3] << " " << 0 << "\n";
  cout << pred << -1 * Xs[0] << " " << C << " " << Ys[0] << " " << 0 << "\n";
  cout << pred << Xs[0] << " " << -1 * C << " " << Ys[0] << " " << 0 << "\n";
  cout << pred << Xs[0] << " " << C << " " << -1 * Ys[0] << " " << 0 << "\n";
  cout << pred << -1 * Xs[1] << " " << Ys[1] << " " << -1 * Ys[0] << " " << 0 << "\n";
  cout << pred << -1 * Xs[2] << " " << Ys[2] << " " << -1 * Ys[1] << " " << 0 << "\n";
  cout << pred << -1 * Xs[4] << " " << Ys[4] << " " << 0 << "\n";
}

//Binary Adder 5 bit
//Also, we need room to write additional n * 5 variables which is indexed from start, start+1, ..., start+5*n-1, last 5 bits from start + 5*(n-1) to end represent the final sum
void fiveBitBinaryAdderWithPredicate(vector<int> Xs, int start, string pred)
{
  int n = Xs.size();
  vector<int> prev;
  for(int i=0; i<5;i++){
    prev.PB(start+i);
  }
  for(int i=1;i<5;i++){
    cout << -1 * prev[i] << " " << 0 << "\n";
  }
  cout << -1 * prev[0] << " " << Xs[0] << " " << 0 << "\n";
  cout << prev[0] << " " << -1 * Xs[0] << " " << 0 << "\n";
  start += 5;
  for(int i=1;i<n;i++){
    vector<int> next;
    for(int i=0; i<5;i++){
      next.PB(start+i);
    }
    fiveBitBinaryIncrementerWithPredicate(prev, next, Xs[i], pred);
    start += 5;
    prev = next;
  }
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


// We'll create a tuple of the number of ((1,_)s, (0,1,_)s, (1,1,_)s, (0,0,1)s, (0,1,1)s,(1,0,1)s,(1,1,1)s)
// Return the start to end indices of these tuples in unary as a vector<vector<int>> 
// Uses a total of 7n*5 + 6n variables
vector<vector<int>> encodeTripleSumsWithPredicate(vector<int> AEdges, vector<int> BEdges, vector<int> CEdges, int start, string pred)
{
  int n = AEdges.size();
  
  // First, we get the number of 1s in AEdges at start + (n-1)*n to start + n*n - 1
  fiveBitBinaryAdderWithPredicate(AEdges,start,pred);
  vector<int> AEdgesOnes;
  // We have to flip the bits
  for(int i=start+5*n-1; i>=start + (n-1) * 5; i--){
    AEdgesOnes.PB(i);
  }
   
  // --------------------------------------------------------------------
 
  // We reset the start
  start += n * 5;
  
  // Define helpers to be number of (0,1)s
  vector<int> helpers1;
  for(int i=0; i<n;i++){
    helpers1.PB(start + i);
  }
  
  // Encode helpers1[i] <=> not AEdges[i] and BEdges[i]
  for(int i=0; i<n; i++){
    vector<int> Xis;
    Xis.PB(-1 * AEdges[i]);
    Xis.PB(BEdges[i]);
    encodeIff(helpers1[i], Xis);
  }

  // Increment start again
  start += n;

  // Get sum of helpers 
  fiveBitBinaryAdderWithPredicate(helpers1,start,pred);
  vector<int> zeroOnes;
  // We have to flip the bits
  for(int i=start+5*n-1; i>=start + (n-1) * 5; i--){
    zeroOnes.PB(i);
  }
  
  // --------------------------------------------------------------------

  // We reset the start
  start += n * 5;
  
  // Define helpers to be number of (1,1)s
  vector<int> helpers2;
  for(int i=0; i<n;i++){
    helpers2.PB(start + i);
  }
  
  // Encode helpers2[i] <=> AEdges[i] and BEdges[i]
  for(int i=0; i<n; i++){
    vector<int> Xis;
    Xis.PB(AEdges[i]);
    Xis.PB(BEdges[i]);
    encodeIff(helpers2[i], Xis);
  }

  // Increment start again
  start += n;

  // Get sum of helpers 
  fiveBitBinaryAdderWithPredicate(helpers2,start,pred);
  vector<int> oneOnes;
  // We have to flip the bits
  for(int i=start+5*n-1; i>=start + (n-1) * 5; i--){
    oneOnes.PB(i);
  }
  
  // --------------------------------------------------------------------

  // We reset the start
  start += n * 5;
  
  // Define helpers to be number of (0,0,1)s
  vector<int> helpers3;
  for(int i=0; i<n;i++){
    helpers3.PB(start + i);
  }
  
  // Encode helpers3[i] <=> not AEdges[i] and not BEdges[i] and CEdges[i]
  for(int i=0; i<n; i++){
    vector<int> Xis;
    Xis.PB(-1 * AEdges[i]);
    Xis.PB(-1 * BEdges[i]);
    Xis.PB(CEdges[i]);
    encodeIff(helpers3[i], Xis);
  }

  // Increment start again
  start += n;

  // Get sum of helpers 
  fiveBitBinaryAdderWithPredicate(helpers3,start,pred);
  vector<int> zeroZeroOnes;
  // We have to flip the bits
  for(int i=start+5*n-1; i>=start + (n-1) * 5; i--){
    zeroZeroOnes.PB(i);
  }

  // --------------------------------------------------------------------

  // We reset the start
  start += n * 5;
  
  // Define helpers to be number of (0,1,1)s
  vector<int> helpers4;
  for(int i=0; i<n;i++){
    helpers4.PB(start + i);
  }
  
  // Encode helpers4[i] <=> not AEdges[i] and BEdges[i] and CEdges[i]
  for(int i=0; i<n; i++){
    vector<int> Xis;
    Xis.PB(-1 * AEdges[i]);
    Xis.PB(BEdges[i]);
    Xis.PB(CEdges[i]);
    encodeIff(helpers4[i], Xis);
  }

  // Increment start again
  start += n;

  // Get sum of helpers 
  fiveBitBinaryAdderWithPredicate(helpers4,start,pred);
  vector<int> zeroOneOnes;
  // We have to flip the bits
  for(int i=start+5*n-1; i>=start + (n-1) * 5; i--){
    zeroOneOnes.PB(i);
  }

  // --------------------------------------------------------------------

  // We reset the start
  start += n * 5;
  
  // Define helpers to be number of (1,0,1)s
  vector<int> helpers5;
  for(int i=0; i<n;i++){
    helpers5.PB(start + i);
  }
  
  // Encode helpers5[i] <=> AEdges[i] and not BEdges[i] and CEdges[i]
  for(int i=0; i<n; i++){
    vector<int> Xis;
    Xis.PB(AEdges[i]);
    Xis.PB(-1 * BEdges[i]);
    Xis.PB(CEdges[i]);
    encodeIff(helpers5[i], Xis);
  }

  // Increment start again
  start += n;

  // Get sum of helpers 
  fiveBitBinaryAdderWithPredicate(helpers5,start,pred);
  vector<int> oneZeroOnes;
  // We have to flip the bits
  for(int i=start+5*n-1; i>=start + (n-1) * 5; i--){
    oneZeroOnes.PB(i);
  }

  // --------------------------------------------------------------------

  // We reset the start
  start += n * 5;
  
  // Define helpers to be number of (1,1,1)s
  vector<int> helpers6;
  for(int i=0; i<n;i++){
    helpers6.PB(start + i);
  }
  
  // Encode helpers6[i] <=> AEdges[i] and BEdges[i] and CEdges[i]
  for(int i=0; i<n; i++){
    vector<int> Xis;
    Xis.PB(AEdges[i]);
    Xis.PB(BEdges[i]);
    Xis.PB(CEdges[i]);
    encodeIff(helpers6[i], Xis);
  }

  // Increment start again
  start += n;

  // Get sum of helpers 
  fiveBitBinaryAdderWithPredicate(helpers6,start,pred);
  vector<int> oneOneOnes;
  // We have to flip the bits
  for(int i=start+5*n-1; i>=start + (n-1) * 5; i--){
    oneOneOnes.PB(i);
  }

  // --------------------------------------------------------------------

  // Add to an output vector

  vector<vector<int>> output;
  output.PB(AEdgesOnes);
  output.PB(zeroOnes);
  output.PB(oneOnes);
  output.PB(zeroZeroOnes);
  output.PB(zeroOneOnes);
  output.PB(oneZeroOnes);
  output.PB(oneOneOnes);

  return output;
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

//Encodes that all variables are all not false
void writeRamseyI(vector<int> Xs)
{
  for (int i = 0; i < Xs.size(); i++)
  {
    cout << Xs[i] << " ";
  }
  cout << 0 << "\n";
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
  //Takes in arguments ./-.exe N K1
  if (argc < 3)
  {
    throw 1;
  }

  int N = stoi(argv[1]);
  // K1 number of 1s to the right of row 1
  int K1 = stoi(argv[2]);

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


  string outname = "";
  outname.append("Ramsey(4,5)BinAddSymBreak3");
  outname.append("(");
  outname.append(to_string(N));
  outname.append(",");
  outname.append(to_string(K1));
  outname.append(")");
  outname.append(".out");

  freopen(outname.c_str(), "w", stdout);

  int counter = ((N * (N - 1)) / 2) + 1;


  // Get the encodePairSums of (1,2,3)
  int a = 1;
  int b = 2;
  int c = 3;
  vector<int> oneEdges;
  vector<int> twoEdges;
  vector<int> threeEdges;
  // First assert 1,2,3 is an I3
  cout << -1 << " " << 0 << endl;
  cout << -1 * getIndex(MP(1,3)) << " " << 0 << endl;
  cout << -1 * getIndex(MP(2,3)) << " " << 0 << endl;


  // First assert (1,N-K1+1) to (1,N) are edges and rest are non-edges

  for(int j=3; j<=N; j++){
    if(j < N - K1 + 1){
      cout << -1 * getIndex(MP(1,j)) << " " << 0 << endl;
    } else {
      cout << getIndex(MP(1,j)) << " " << 0 << endl;
    }
  } 

  for (int v = 1; v <= N; v++)
  {
    if (v != a && v != b && v != c)
    {
      for (int eN = 1; eN < allEdges.size(); eN++)
      {
        if (eN != 1)
        {
          if ((allEdges[eN].first == a && allEdges[eN].second == v) || (allEdges[eN].first == v && allEdges[eN].second == a))
          {
            oneEdges.PB(eN);
          }
          if ((allEdges[eN].first == b && allEdges[eN].second == v) || (allEdges[eN].first == v && allEdges[eN].second == b))
          {
            twoEdges.PB(eN);
          }
          if ((allEdges[eN].first == c && allEdges[eN].second == v) || (allEdges[eN].first == v && allEdges[eN].second == c))
          {
            threeEdges.PB(eN);
          }
        }
      }
    }
  }




  vector<vector<int>> oneTwoThree = encodeTripleSumsWithPredicate(oneEdges, twoEdges, threeEdges, counter, "");
  counter += 7 * (N-3) * 5 + 6 * (N-3);  

  vector<int> oneTwoThreeTripleSums;
  oneTwoThreeTripleSums.insert(oneTwoThreeTripleSums.end(), oneTwoThree[0].begin(),oneTwoThree[0].end());
  oneTwoThreeTripleSums.insert(oneTwoThreeTripleSums.end(), oneTwoThree[1].begin(),oneTwoThree[1].end());
  oneTwoThreeTripleSums.insert(oneTwoThreeTripleSums.end(), oneTwoThree[2].begin(),oneTwoThree[2].end());


  //Encoding Lexicographic condition
  for (int eNum = 1; eNum < allEdges.size(); eNum++)
  {
    int a = allEdges[eNum].first;
    int b = allEdges[eNum].second;
    vector<int> AEdges;
    vector<int> BEdges;
    for (int v = 1; v <= N; v++)
    {
      if (v != a && v != b)
      {
        for (int eN = 1; eN < allEdges.size(); eN++)
        {
          if (eN != eNum)
          {
            if ((allEdges[eN].first == a && allEdges[eN].second == v) || (allEdges[eN].first == v && allEdges[eN].second == a))
            {
              AEdges.PB(eN);
            }
            if ((allEdges[eN].first == b && allEdges[eN].second == v) || (allEdges[eN].first == v && allEdges[eN].second == b))
            {
              BEdges.PB(eN);
            }
          }
        }
      }
    }
    //Only need to encoding stuff if the vector is non-empty
    if (AEdges.size() > 0)
    {
      //Lexicographic ordering between each group that isn't the last group
      writeLexicoWithPred(AEdges, BEdges, AEdges.size(), counter, "");
      counter += 3 * AEdges.size() - 2;
    }
  }


  // Encode Triple Symbreak

  for (int a = 1; a <= N; a++){
    for (int b = 1; b <= N; b++){
      for (int c = 1; c <= N; c++){
        if(a == b || b == c || a == c){
          continue;
        }
        if(a == 1 || b == 1 || c == 1){
          vector<int> AEdges;
          vector<int> BEdges;
          vector<int> CEdges;
          string pred = "";
          pred.append(to_string(getIndex(MP(a,b)))+" ");
          pred.append(to_string(getIndex(MP(b,c)))+" ");
          pred.append(to_string(getIndex(MP(a,c)))+" ");
          for (int v = 1; v <= N; v++)
          {
            if (v != a && v != b && v != c)
            {
              AEdges.PB(getIndex(MP(a,v)));
              BEdges.PB(getIndex(MP(b,v)));
              CEdges.PB(getIndex(MP(c,v)));
            }
          }
          vector<vector<int>> ABC = encodeTripleSumsWithPredicate(AEdges, BEdges, CEdges, counter, "");
          counter += 7 * (N-3) * 5 + 6 * (N-3);

          vector<int> ABCTripleSums;
          for(int i=0; i<3;i++){
            ABCTripleSums.insert(ABCTripleSums.end(), ABC[i].begin(), ABC[i].end());
          }
          if(ABCTripleSums.size() != oneTwoThreeTripleSums.size()){
            throw 1;
          }
          writeLexicoWithPred(oneTwoThreeTripleSums, ABCTripleSums,ABCTripleSums.size(), counter,pred);
          counter += 3 * ABCTripleSums.size() - 2;
        }
        
      }
    }
  }
  
  // Encodes R4,5 goodness

  int vs[6];

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
            vector<int> Xs;
            for (int i = 0; i < 5; i++)
            {
              for (int j = i + 1; j < 5; j++)
              {
                Xs.PB(getIndex(MP(vs[i], vs[j])));
              }
            }
            writeRamseyI(Xs);
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
          vector<int> Xs;
          for (int i = 0; i < 4; i++)
          {
            for (int j = i + 1; j < 4; j++)
            {
              Xs.PB(getIndex(MP(vs[i], vs[j])));
            }
          }
          writeRamseyK(Xs);
        }
      }
    }
  }

  return 0;
}