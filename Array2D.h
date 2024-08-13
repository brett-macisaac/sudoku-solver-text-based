#pragma once

#include<stdexcept>


template <typename T>
class Array2D 
{

private:

    T* f_grid;

    // The horizontal (x-axis) size. The number of columns; the number of elements per row.
    unsigned int f_width;

    // The vertical (y-axis) size. The number of rows; the number of elements per column.
    unsigned int f_height;


public:

    Array2D()
        : f_width(0), f_height(0)
    {
        f_grid = nullptr;
    }

    /*
    * Notes:
        (a). When a standard 2D is declared or instantiated in C/C++, it's created in row-major order 
            (see https://en.wikipedia.org/wiki/Row-_and_column-major_order), meaning that the height is given before
            the width: e.g. 'int matrix[height][width]', which is emulated here in the constructor's parameter list.
    */
    Array2D(unsigned int p_height, unsigned int p_width)
        : f_width(p_width), f_height(p_height)
    {
        // (a). Instantiate the array to the size specified by the given dimensions.
        f_grid = new T[f_width * f_height]();
    }

    ~Array2D()
    {
        delete[] f_grid;
    }


    void ChangeDimensions(unsigned int p_height, unsigned int p_width)
    {
        if (p_width == f_width && p_height == f_height)
        { return; }

        if (f_grid != nullptr)
        {
            delete[] f_grid;
        }

        f_grid = new T[p_width * p_height]();

        f_height = p_height;
        f_width = p_width;
    }

    unsigned int GetWidth() const
    {
        return f_width;
    }

    unsigned int GetHeight() const
    {
        return f_height;
    }

    /*
    * Returns the value at coordinate (p_x, p_y).
    * The x-coordinate (p_x) refers to the column, while the y-coordinate (p_y) refers to the row.
    */
    T& ValueXY(unsigned int p_x, unsigned int p_y)
    {
        // Make use of GetValueRowCol to return the value at the desired coordinates.
        return ValueRowCol(p_y, p_x);
    }

    /*
    * Returns the value at row p_row and column p_col.

    * Notes:
        (a). f_height is the number of rows, meaning that p_row, the row 'index', ranges from 0 to f_height - 1.
             f_width is the number of columns; meaning that p_col, the column 'index', ranges from 0 to f_width - 1.
        (b). Though f_grid is a 1D array, it can be indexed like a 2D array by using an indexing technique. 
             p_row * f_width (the row index times the number of elements per row) is the index of the first element 
             in row p_row; adding the column index p_col to this index gives the index at row p_row and column p_col.
    */
    T& ValueRowCol(unsigned int p_row, unsigned int p_col) const
    {
        // (a). The the row or column is out of range.
        if (p_row >= f_height || p_col >= f_width)
        { throw std::range_error("The given row and/or column are invalid."); }

        // (b). Index the array such that the correct value is returned.
        return f_grid[p_row * f_width + p_col];
    }

    /*
    * Sets all cells to the given value.
    */
    void SetAllTo(T p_value)
    {
        unsigned int l_size = f_width * f_height;

        for (int i = 0; i < l_size; ++i)
        {
            f_grid[i] = p_value;
        }

    }


    T& operator[](unsigned int p_index)
    {
        if (p_index >= f_width * f_height)
        {
            throw std::range_error("The given index is invalid.");
        }

        return f_grid[p_index];
    }

    friend std::istream& operator>>(std::istream& p_istream, Array2D<T>& p_array)
    {
        int l_size = p_array.GetWidth() * p_array.GetHeight();

        for (int i = 0; i < l_size; ++i)
        {
            p_istream >> p_array[i];
        }

        return p_istream;
    }

};
