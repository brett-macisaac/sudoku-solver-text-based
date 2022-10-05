#pragma once

#include<iostream>
#include<fstream>
#include<stdexcept>

#include"Array2D.h"


class SudokuBoard
{

private:

    Array2D<unsigned int> f_grid;

    // The width of a box in the grid.
    unsigned int f_width_box;

    // The height of a box in the grid.
    unsigned int f_height_box;

    // The dimension (width/height) of the grid.
    // == f_width_box * f_height_box: having the value as a field removes the need to calculate it or use the GetWidth/GetHeight methods of f_grid, which avoids unnecessary confusion.
    unsigned int f_size_grid;


    static const unsigned int S_SIZE_GRID_DEFAULT = 9;

    static const unsigned int S_WIDTH_BOX_DEFAULT = 3;

    static const unsigned int S_HEIGHT_BOX_DEFAULT = 3;

    static const unsigned int S_WIDTH_BOX_MAX = 7;

    static const unsigned int S_HEIGHT_BOX_MAX = 7;

    static const unsigned int S_VALUE_EMPTY_CELL = 0;


public:

    SudokuBoard();

    SudokuBoard(const char* a_file);

    SudokuBoard(unsigned int a_width_box, unsigned int a_height_box);

    SudokuBoard(unsigned int a_width_box, unsigned int a_height_box, const char* a_file);




    bool Solve();

    void EmptyBoard();

    /*
        * Returns whether or not the board adheres to the rules of sudoku.
    */
    bool IsValid();

    /*
        * Returns whether or not the board has been solved.
    */
    bool IsSolved();

    /*
        * Places the value a_value at the position defined by a_row and a_col and returns whether or not it's a valid 
          placement.
    */
    bool PlaceValue(int a_value, int a_row, int a_col, bool l_if_wrong_remove = false);
    


    friend std::istream& operator>>(std::istream& a_istream, SudokuBoard& a_board);

    friend std::ostream& operator<<(std::ostream& a_ostream, SudokuBoard& a_board);


private:

    /* Auxiliary of Solve
        * This method tries to solve the sudoku using the backtracking technique.
        * An assumption is that the sudoku is valid to begin with: i.e. the method assumes that none of the pre-filled 
          cells violate the rules of sudoku.
    */
    bool Solve_BackTracking();

    /* Auxiliary of IsValid, IsSolved, PlaceValue
        * This method returns whether or not the cell adheres to the rules of sudoku. 
    */
    bool IsCellValid(int a_row, int a_col);

    /* Auxiliary of Solve_BackTracking
        * Assigns to a_row and a_col the values which correspond to the location of the 'earliest' empty cell of f_grid.
          In this context, the 'earliest' empty cell is the one at the lowest column/vertical position of the lowest row.
    */
    bool AssignNextEmptyCell(int& a_row, int& a_col);
};
