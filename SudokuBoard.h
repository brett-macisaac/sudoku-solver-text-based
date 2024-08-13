#pragma once

#include<iostream>
#include<fstream>
#include<stdexcept>

#include"Array2D.h"


/*
* An abstraction of a sudoku board. 
*/
class SudokuBoard
{

private:

    // The grid that defines the numbers that comprise the sudoku puzzle.
    Array2D<unsigned int> f_grid;

    // The width of a box in the grid.
    unsigned int f_width_box;

    // The height of a box in the grid.
    unsigned int f_height_box;

    // The dimension (width/height) of the grid.
    // Intended to be equal to f_width_box * f_height_box.
    // Having the value as a field removes the need to calculate it or use the GetWidth/GetHeight methods of f_grid.
    unsigned int f_size_grid;


    // The default value of f_size_grid.
    static const unsigned int S_SIZE_GRID_DEFAULT = 9;

    // The default value of f_width_box.
    static const unsigned int S_WIDTH_BOX_DEFAULT = 3;

    // The default value of f_height_box.
    static const unsigned int S_HEIGHT_BOX_DEFAULT = 3;

    // The maximum value of f_width_box.
    static const unsigned int S_WIDTH_BOX_MAX = 7;

    // The maximum value of f_height_box.
    static const unsigned int S_HEIGHT_BOX_MAX = 7;

    // The value used for empty cells in the grid.
    static const unsigned int S_VALUE_EMPTY_CELL = 0;


public:

    SudokuBoard();

    SudokuBoard(const char* p_file);

    SudokuBoard(unsigned int p_width_box, unsigned int p_height_box);

    SudokuBoard(unsigned int p_width_box, unsigned int p_height_box, const char* p_file);


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
    * Places the value p_value at the position defined by p_row and p_col and returns whether or not it's a valid 
      placement.
    */
    bool PlaceValue(int p_value, int p_row, int p_col, bool l_if_wrong_remove = false);


    friend std::istream& operator>>(std::istream& p_istream, SudokuBoard& p_board);

    friend std::ostream& operator<<(std::ostream& p_ostream, SudokuBoard& p_board);


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
    bool IsCellValid(int p_row, int p_col);

    /* Auxiliary of Solve_BackTracking
    * Assigns to p_row and p_col the values which correspond to the location of the 'earliest' empty cell of f_grid. In 
      this context, the 'earliest' empty cell is the one at the lowest column/vertical position of the lowest row.
    * If an empty cell is assigned, true is returned; if an empty cell isn't assigned, meaning one couldn't be found,
      false is returned.
    */
    bool AssignNextEmptyCell(int& p_row, int& p_col);
};
