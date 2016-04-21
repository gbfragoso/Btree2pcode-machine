# Btree2pcode-machine
Evolution of previous approaches of pcode utilization

# Compiling
gcc -o btree2pcode btree2pcode.c

# Running
./btree2pcode filename numValues

* filename: Name of file (Must be in same folder of btree2pcode.c)
* numValues: Number of values in input file (include 0, see next section)

# Input
This program accepts as input a comma-separated text file that represents the nodes of a binary tree. The root is the first value, left nodes (2 * pos + 1) and right nodes (2 * pos+2), where pos is the position of father in array.

Example:

![btree](https://upload.wikimedia.org/wikipedia/commons/thumb/f/f7/Binary_tree.svg/192px-Binary_tree.svg.png)

The input file for tree above is: 2,7,5,2,6,0,9,0,0,5,11,0,0,4 (Note 0's to fill the empty nodes)

# Assumptions
* Your tree has nodes on right position
* A postorder search on that tree will return a valid Reverse Polish Notation.

# Example 
```
run: ./btree2pcode input.txt 9
input: *,~,6,+,0,0,0,10,5
RPN: 10 5 + ~ 6 *
Output:

Inst       Level           Arg             Top             Counter         Stack
INT        0               9               0               1               0 0 0 0 0 0 0 0 0 
LIT        0               10              10              2               0 0 0 0 0 0 0 0 0 10 
STO        0               0               0               3               10 0 0 0 0 0 0 0 0 
LIT        0               5               5               4               10 0 0 0 0 0 0 0 0 5 
STO        0               1               0               5               10 5 0 0 0 0 0 0 0 
LOD        0               1               5               6               10 5 0 0 0 0 0 0 0 5 
LOD        0               0               10              7               10 5 0 0 0 0 0 0 0 5 10 
OPR        0               2               15              8               10 5 0 0 0 0 0 0 0 15 
STO        0               2               0               9               10 5 15 0 0 0 0 0 0 
LOD        0               2               15              10              10 5 15 0 0 0 0 0 0 15 
OPR        0               1               -15             11              10 5 15 0 0 0 0 0 0 -15 
STO        0               2               0               12              10 5 -15 0 0 0 0 0 0 
LIT        0               6               6               13              10 5 -15 0 0 0 0 0 0 6 
STO        0               3               0               14              10 5 -15 6 0 0 0 0 0 
LOD        0               3               6               15              10 5 -15 6 0 0 0 0 0 6 
LOD        0               2               -15             16              10 5 -15 6 0 0 0 0 0 6 -15 
OPR        0               4               -90             17              10 5 -15 6 0 0 0 0 0 -90 
STO        0               4               0               18              10 5 -15 6 -90 0 0 0 0 
OPR        0               0               -1              -15    
```
