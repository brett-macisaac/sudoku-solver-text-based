
#include <iostream>

#include"SudokuBoard.h"


/*
* The entry-point function.
*/
int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "No sudoku file was specified. Please run the program again with a command line parameter that corresponds to a sudoku file (see README).\n";
        return EXIT_FAILURE;
    }

    // Create the sudoku.
    SudokuBoard l_sudoku(argv[1]);

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

    return EXIT_SUCCESS;
}
