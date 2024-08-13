
#include"SudokuBoard.h"


SudokuBoard::SudokuBoard()
    : f_grid(S_SIZE_GRID_DEFAULT, S_SIZE_GRID_DEFAULT), f_width_box(S_WIDTH_BOX_DEFAULT),
      f_height_box(S_HEIGHT_BOX_DEFAULT), f_size_grid(S_SIZE_GRID_DEFAULT)
{
    EmptyBoard();
}

SudokuBoard::SudokuBoard(const char* p_file)
    : f_grid(S_SIZE_GRID_DEFAULT, S_SIZE_GRID_DEFAULT), f_width_box(S_WIDTH_BOX_DEFAULT),
      f_height_box(S_HEIGHT_BOX_DEFAULT), f_size_grid(S_SIZE_GRID_DEFAULT)
{
    std::ifstream l_file_input(p_file);

    if (!l_file_input.good())
        return;

    l_file_input >> *this;

    l_file_input.close();
}

SudokuBoard::SudokuBoard(unsigned int p_width_box, unsigned int p_height_box)
    : f_width_box(p_width_box), f_height_box(p_height_box)
{
    if (f_width_box > S_WIDTH_BOX_MAX || f_height_box > S_HEIGHT_BOX_MAX)
    {
        f_width_box = S_WIDTH_BOX_DEFAULT;
        f_height_box = S_HEIGHT_BOX_DEFAULT;
    }

    f_size_grid = f_width_box * f_height_box;

    f_grid.ChangeDimensions(f_size_grid, f_size_grid);
}

SudokuBoard::SudokuBoard(unsigned int p_width_box, unsigned int p_height_box, const char* p_file)
    : f_width_box(p_width_box), f_height_box(p_height_box)
{
    if (f_width_box > S_WIDTH_BOX_MAX || f_height_box > S_HEIGHT_BOX_MAX)
    {
        f_width_box = S_WIDTH_BOX_DEFAULT;
        f_height_box = S_HEIGHT_BOX_DEFAULT;
        f_size_grid = S_SIZE_GRID_DEFAULT;
    }
    else
    {
        f_size_grid = f_width_box * f_height_box;
    }

    int l_size_grid = f_width_box * f_height_box;

    f_grid.ChangeDimensions(l_size_grid, l_size_grid);

    std::ifstream l_file_input(p_file);

    l_file_input >> *this;

    l_file_input.close();
}


bool SudokuBoard::Solve()
{
    if (!IsValid())
    { return false; }

    return Solve_BackTracking();
}

void SudokuBoard::EmptyBoard()
{
    f_grid.SetAllTo(S_VALUE_EMPTY_CELL);
}

/*
* Returns whether or not the board adheres to the rules of sudoku.
*/
bool SudokuBoard::IsValid()
{
    for (int row = 0; row < f_size_grid; ++row)
    {
        for (int col = 0; col < f_size_grid; ++col)
        {
            if (!IsCellValid(row, col))
            { return false; }
        }

    }

    return true;
}

/*
* Returns whether or not the board has been solved.
*/
bool SudokuBoard::IsSolved()
{
    for (int row = 0; row < f_size_grid; ++row)
    {
        for (int col = 0; col < f_size_grid; ++col)
        {
            if (f_grid.ValueRowCol(row, col) == S_VALUE_EMPTY_CELL || !IsCellValid(row, col))
            { return false; }
        }

    }

    return true;
}


std::istream& operator>>(std::istream& p_istream, SudokuBoard& p_board)
{
    // The width and height of each box.
    int l_width_box;
    int l_height_box;

    // Get the width and height.
    p_istream >> l_width_box >> l_height_box;

    // If the current board isn't compatible with the given dimensions, change it's dimensions.
    if (l_width_box != p_board.f_width_box || l_height_box != p_board.f_height_box)
    {
        p_board.f_width_box = l_width_box;
        p_board.f_height_box = l_height_box;

        p_board.f_size_grid = p_board.f_width_box * p_board.f_height_box;
        p_board.f_grid.ChangeDimensions(p_board.f_size_grid, p_board.f_size_grid);
    }

    p_istream >> p_board.f_grid;

    return p_istream;
}

/*
* Notes:
    (a). When all of the values are single digits (max value is at most 9), each value occupies one character and each
            box is horizontally separated by one character from the others in its row.
            '(p_board.f_size_grid / p_board.f_width_box)' is the number of boxes per row; therefore, this value minus 1
            is the number of box divider characters per row.
    (b). When the maximum value is more than one digit (is equal to at least 10), each value must occupy two characters
            in order for the sudoku to be easily read; in addition, rather than each value being placed right next to
            each other, a space separates them, as otherwise two or more two-digit numbers placed right next to each other
            would appear as one long number. Because of the extra spacing within the boxes, they must be horizontally 
            separated by more than one space.

*/
std::ostream& operator<<(std::ostream& p_ostream, SudokuBoard& p_board)
{
    // The number of boxes per row.
    int l_num_boxes_in_row = p_board.f_height_box;

    // The width of each row (not incl. the borders).
    int l_width_output;
    if (p_board.f_size_grid < 10)
    {
        // (a).
        l_width_output = p_board.f_size_grid + 4 * (l_num_boxes_in_row - 1) + 2;
    }
    else
    {
        // The number of boxes per row.
        int l_num_boxes_in_row = p_board.f_height_box;

        // (b).
        l_width_output = l_num_boxes_in_row * ( 2 + 3 * (p_board.f_width_box - 1) ) + 4 * (l_num_boxes_in_row - 1) + 2;
    }

    for (int row = 0; row < p_board.f_size_grid; ++row)
    {
        // If on the first row, output the top border.
        if (row == 0)
        {
            p_ostream << '|';
            for (int i = 0; i < l_width_output; ++i)
            { p_ostream << '='; }
            p_ostream << '|';
            p_ostream << std::endl;
        }

        // A flag that, when true, indicates that a row of boxes was just finished.
        bool l_is_new_box_row = row % p_board.f_height_box == 0;

        // Separate the boxes vertically.
        if (row != 0 && l_is_new_box_row)
        { 
            p_ostream << '|';
            for (int i = 0; i < l_width_output; ++i)
            { p_ostream << '='; }
            p_ostream << '|';
            p_ostream << std::endl; 
        }

        for (int col = 0; col < p_board.f_size_grid; ++col)
        {
            // The value associated with the coordinates.
            int l_value = p_board.f_grid.ValueRowCol(row, col);

            // A flag that, when true, indicates that l_value is the first value of a box for this row.
            bool l_is_new_box = col % p_board.f_width_box == 0;

            // Separate the boxes horizontally.
            if (col != 0 && l_is_new_box)
            {  p_ostream << " || "; }

            // Left border.
            if (col == 0)
            { p_ostream << '|'; }

            // Padding from the left border.
            if (col == 0)
            { p_ostream << ' '; }

            // The value.
            if (p_board.f_size_grid < 10) // If there are no two-digit values.
            {
                p_ostream << l_value;
            }
            else
            {
                if (l_is_new_box)
                {
                    if (l_value >= 10) // If the value is a two-digit number.
                    {
                        p_ostream << l_value;
                    }
                    else
                    {
                        p_ostream << ' ' << l_value;
                    }
                }
                else
                {
                    if (l_value >= 10) // If the value is a two-digit number.
                    {
                        p_ostream << ' ' << l_value;
                    }
                    else
                    {
                        p_ostream << "  " << l_value;
                    }
                }

            }

            // Padding from the right border.
            if (col == p_board.f_size_grid - 1)
            { p_ostream << ' '; }

            // Right border.
            if (col == p_board.f_size_grid - 1)
            { p_ostream << '|'; }

        }

        // If on the last row, output the bottom border.
        if (row == p_board.f_size_grid - 1)
        {
            p_ostream << std::endl;
            p_ostream << '|';
            for (int i = 0; i < l_width_output; ++i)
            { p_ostream << '='; }
            p_ostream << '|';
            p_ostream << std::endl;
        }
        else
        {
            // Go to a new line for each row.
            p_ostream << std::endl;
        }

    }

    return p_ostream;
}



/* Auxiliary of Solve

* Notes: 
    (a). All possible values may not need to be iterated over; it could even be the case that only value is
         considered for this cell. In other words, iterate over at most all values.
    (b). Note that it's not necessarily the case that the sudoku cannot be solved with the current value at the cell
         (l_row, l_col), rather that this cannot occur on the current 'branch' of the recursive program.
    (c). If the current Solve_BackTracking call is the top/first one, this means that the sudoku cannot be
         solved: i.e. it's an impossible puzzle.
*/
bool SudokuBoard::Solve_BackTracking()
{
    // Variables to store the (empty) cell being considered by this Solve_BackTracking call.
    int l_row;
    int l_col;

    // Get the next empty cell; if a cell cannot be assigned, this means all cells are filled, which would imply that the sudoku is solved.
    if (!AssignNextEmptyCell(l_row, l_col))
    { return true; }

    // (a). Iterate over (at most) all possible values.
    for (int value = 1; value <= f_size_grid; ++value)
    {
        // Try to place the value; if it cannot be placed, continue to the next value.
        if (!PlaceValue(value, l_row, l_col, true))
        { continue; }

        // Execute a recursive call; if this call returns true, then the sudoku must be solved; therefore, return true.
        if (Solve_BackTracking())
        { return true; }

        // (b). If this line is reached, this means the sudoku cannot be solved with the current value. 
        f_grid.ValueRowCol(l_row, l_col) = S_VALUE_EMPTY_CELL;
    }

    // (c). Return false so that the previous Solve_BackTracking call knows to try a different value.
    return false;
}

/* Auxiliary of Solve_BackTracking
*/
bool SudokuBoard::PlaceValue(int p_value, int p_row, int p_col, bool l_if_wrong_remove /*= false*/)
{
    f_grid.ValueRowCol(p_row, p_col) = p_value;

    if (IsCellValid(p_row, p_col))
    { return true; }

    if (l_if_wrong_remove)
    { f_grid.ValueRowCol(p_row, p_col) = S_VALUE_EMPTY_CELL; }

    return false;
}

/* Auxiliary of Solve, IsBoardValid
*/
bool SudokuBoard::IsCellValid(int p_row, int p_col)
{
    int l_value = f_grid.ValueRowCol(p_row, p_col);

    // A cell can always be empty.
    if (l_value == S_VALUE_EMPTY_CELL)
    { return true; }

    // Check if the value is equal to any within its row.
    for (int col = 0; col < f_size_grid; ++col)
    {
        if (col == p_col)
        { continue; }

        if (l_value == f_grid.ValueRowCol(p_row, col))
        { return false; }
    }

    // Check if the value is equal to any within its column.
    for (int row = 0; row < f_size_grid; ++row)
    {
        if (row == p_row)
        { continue; }

        if (l_value == f_grid.ValueRowCol(row, p_col))
        { return false; }
    }

    // Check if the value is equal to any other within its box.
    // Each box can be define by four values: a pair of min/max values for the rows and columns.

    // Get the min and max row for the box at (p_col, p_row).
    int l_index_row_min = p_row - p_row % f_height_box;
    int l_index_row_max = l_index_row_min + (f_height_box - 1);

    // Get the min and max column for the box at (p_col, p_row).
    int l_index_col_min = p_col - p_col % f_width_box;
    int l_index_col_max = l_index_col_min + (f_width_box - 1);

    // Check if the value is equal to any within its box.
    for (int row = l_index_row_min; row < l_index_row_max; ++row)
    {
        for (int col = l_index_col_min; col < l_index_col_max; ++col)
        {
            if (row == p_row && col == p_col)
            { continue; }

            if (l_value == f_grid.ValueRowCol(row, col))
            { return false; }
        }

    }

    // If this point is reached, all of the conditions/rules have been satisfied; thus, return true.
    return true;
}

/* Auxiliary of Solve_BackTracking
*/
bool SudokuBoard::AssignNextEmptyCell(int& p_row, int& p_col)
{
    for (int row = 0; row < f_size_grid; ++row)
    {
        for (int col = 0; col < f_size_grid; ++col)
        {
            if (f_grid.ValueRowCol(row, col) == S_VALUE_EMPTY_CELL)
            {
                p_row = row;
                p_col = col;

                return true;
            }

        }

    }

    return false;
}