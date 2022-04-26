# RamseySAT

# Ramsey(4-e,7)

# Usage
You may need to recompile these files using G++.

## .out File Generators
These generates .out files which are all the clauses of the CNF but doesn't include the CNF header.
### 3SymBreakRamsey(4-e,7)
This generates a k=3 (for all triples containing 1) + Shatter symmetry break for R(4-e,7) using unary adder
```
3SymBreakRamsey(4-e,7).exe N K1 
```
where N is the number of vertices and K1 is the degree of the vertex 1 

### BinAdderSymmmetryBreak3Ramsey
This generates a k=3 (for all triples containing 1) + Shatter symmetry break for R(4,5) using binary adder
```
BinAdderSymmmetryBreak3Ramsey.exe N K1 
```
where N is the number of vertices and K1 is the degree of the vertex 1 

### NewSymmetryBreak3Ramsey
This generates a k=3 (for all triples containing 1) + Shatter symmetry break for R(4,5) using unary adder
```
NewSymmetryBreak3Ramsey.exe N K1 
```
where N is the number of vertices and K1 is the degree of the vertex 1 

### NewSymmetryBreakRamsey
This generates a k=2 (for all pairs) + Shatter symmetry break for R(4,5) using unary adder
```
NewSymmetryBreakRamsey.exe N K1 
```
where N is the number of vertices and K1 is the degree of the vertex 1 

### OnlySymmetryBreak
This generates an only Shatter symmetry break for any graph
```
OnlySymmetryBreak.exe N
```
where N is the number of vertices

### Ramsey(4-e,7)28Base
This generates a k=3 (for all triples containing 1) + Shatter symmetry break for R(4-e,7) using unary adder. It does it for N=17 where the neighbourhood of 11 is 1 to 10 with 5 disjoint edges, and the antineighbour hood of 11 is vertices 12-17 with edges (12-13), (14-15) and the rest are non-edges.
```
Ramsey(4-e,7)28Base.exe 
```

### Ramsey(4-e,7)28Triangles
WARNING: Generates 120 .out files, which may not be desired. 

This generates a k=3 (for all triples containing 1) + Shatter symmetry break for R(4-e,7) using unary adder. It generates, for all 0 <= K_3 <= K_2 <= K_1 <= 7, a .out with a triangle with degrees K1,K2,K3 for the three vertices. The rest of the points are in the antineighbourhood of the triangle and are made vertices 1 to N - 3 - K1 - K2 - K3. We only enforce k=3 and Shatter on the submatrix of the adjacency array of edges between vertices 1 to N - 3 - K1 - K2 - K3. 
```
Ramsey(4-e,7)28Triangles.exe 
```

## .out to .cnf Conversion
```toCNF.exe <filename.out>```
Converts filename.out into filename.cnf by creating a CNF header 

## checkGraph
Change the parameters N and inString as well as the for loops at the bottom. The input format must be the same as the SAT solver output, so edges are labeled 1,2,3,..., N choose 2 and have a sign in front denoting whether they're an edge or not. The first line is the number of such graphs.

This checks if all graphs satisfy Ramsey conditions, or outputs the first index which fails.

``` checkGraph.exe```

## EnumerateAll
Old version of all-sat which adds blocking clauses to the .out file and then reconverts to CNF and reruns.

``` EnumerateAll.exe <coreString> N```

where coreString denotes the string before the .out and N is the number of vertices.

One also needs to change the commands with the directory of cadical. 

## ExtractSolutions
Old version of all-sat which extracts solutions from the .out file from the blocking clauses

It looks at all clauses of appropriate length and numbers from 1 to N choose 2 and then flips all signs.
If it finds one of these clauses, and no more for the next 4 lines, it resets as it's probably not a blocking clause.

It then outputs all of these to a `<filename>Graphs.txt` file with the first line being the number of graphs in this file followed by each line being the graph obtained from flipping the signs of the blocking clause.

```ExtractSolutions.exe <filename.out> N```

where N is the number of vertices. 
