Sudoku Solver by recursive backtracking

ALGORITHM:
1. Enumerate all empty cells in typewriter order(left to right, top to bottom).

2. The 'current cell' is the first cell in the enumeration.

3. Enter a 1 into the current cell. if this violates the sudoku condition, try entering a 2, then a 3, and so forth, until
  a.] The entry does not violate the sudoku condition
  b.] You have reached 9 and still violates the sudoku condition.
  
4. In case a: If the current cell was the last enumerated one, then the puzzle is solved. If not, then go back to Step 2 with the 'current cell' being the next cell.
- In case b: If the current cell is the first cell in the enumeration, then the sudoku puzzle does not have a solution. If not, then erase the 9 from the current cell, call the previous cell in the enumeration the new 'current cell', and continue with Step 3
