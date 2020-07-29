# Sudoku Solver with Klee
This program utilizes Klee, an open source constraint solver, to find the solution to a sudoku puzzle. 

### Requirements
This program is compiled with clang and needs the user to download klee as well (More information can be found on Klee's official Github: https://klee.github.io/
)

### Implementation
Simply run the .c file with the appropriate compilers

`clang k_sudoku.c` --> this will output a .bc file

And then run

`klee k_sudoku.bc` 

### Output
The output is a bunch of klee files. The one that we are interested in is the one that had an assert error, which tells when when Klee got the accurate input of numbers that solves our Sudoku Puzzle. Our Klee file tells us we should input *43598251* in to the 0 spaces in our puzzle. And if we look at our original puzzle, that's the correct answer!
