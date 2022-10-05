
#include <iostream>

#include"SudokuBoard.h"

/* Ideas
    * Add an input constructor to the SudokuBoard that removes the need to use a text file. Add a flag that indicates
      whether to use the input constructor or the file.

*/

/*
    * The program's entry-point function.

    * Notes:
        (a). Simply place the name of the file that contains the sudoku you wish to solve into the constructor.
         
*/
int main()
{
    // (a). Create the sudoku.
    SudokuBoard l_sudoku("sudoku_33_2.txt");

    // Output the (unsolved) sudoku.
    std::cout << "Unsolved:\n" 
              << l_sudoku;

    if (!l_sudoku.IsValid()) // If the sudoku isn't valid.
    {
        std::cout << "\nThe given sudoku does not adhere to the rules of sudoku.\n";
    }
    else if (l_sudoku.Solve()) // If the sudoku was successfully solved.
    {
        // Output the (solved) sudoku.
        std::cout << "\nSolved:\n"
                  << l_sudoku;
    }
    else // If the sudoku couldn't be solved.
    {
        std::cout << "\nThe given sudoku has no solution.\n";
    }

}
