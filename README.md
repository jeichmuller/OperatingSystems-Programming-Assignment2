# OperatingSystems-Programming-Assignment2

Programming Assignment #2 for Operating Systems

Jay Eichmuller


Run using:

$ gcc -o bankers_algorithm main.c
$ ./bankers_algorithm

Files Included
main.c : holds the fucntions
input.txt : gives input for the main.c to run

Assignment is implementation of Banker's algorithm. Given input, the file reads in that input into allocation, max, and available matrix. With the input the program determines if system is in a safe state, and if so it will print a safe sequence.

Using the example `input.txt` file:
```
3 2 2
0 1 1
2 1 1
3 2 2
2 2 2
1 0 2
6 3 4
4 3 3
8 4 5
7 6 3
5 2 4
```
The input file should be formatted :
Available resources A B C
Allocation for P0
Allocation for P1
Allocation for P2
Allocation for P3
Allocation for P4
Max demaind for P0
Max demaind for P1
Max demaind for P2
Max demaind for P3
Max demaind for P4

Example output would be :
```
The system is in a safe state.
Safe sequence: P1 P2 P0 P3 P4
```
