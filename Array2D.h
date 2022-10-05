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
    {
        f_grid = nullptr;
    }

    /*
        * Notes:
            (a). When a standard 2D is declared or instantiated in C/C++, it's created in row-major order 
                (see https://en.wikipedia.org/wiki/Row-_and_column-major_order), meaning that the height is given before
                the width: e.g. 'int matrix[height][width]', which is emulated here in the constructor's parameter list.
    */
    Array2D(unsigned int a_height, unsigned int a_width)
        : f_width(a_width), f_height(a_height)
    {
        // (a). Instantiate the array to the size specified by the given dimensions.
        f_grid = new T[f_width * f_height]();
    }

    ~Array2D()
    {
        delete[] f_grid;
    }
    


    void ChangeDimensions(unsigned int a_height, unsigned int a_width)
    {
        if (a_width == f_width && a_height == f_height)
        { return; }

        if (f_grid != nullptr)
        {
            delete[] f_grid;
        }

        f_grid = new T[a_width * a_height]();

        f_height = a_height;
        f_width = a_width;
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
        * Notes:
            (a). The x-coordinate refers to the column, while the y-coordinate refers to the row.
    */
    T& ValueXY(unsigned int a_x, unsigned int a_y)
    {
        // Make use of GetValueRowCol to return the value at the desired coordinates.
        return ValueRowCol(a_y, a_x);
    }

    /*
        * Notes:
            (a). f_height is the number of rows, meaning that a_row, the row 'index', ranges from 0 to f_height - 1.
                 f_width is the number of columns; meaning that a_col, the column 'index', ranges from 0 to f_width - 1.
            (b). Though f_grid is a 1D array, it can be indexed like a 2D array by using an indexing technique. 
                 a_row * f_width (the row index times the number of elements per row) is the index of the first element 
                 in row a_row; adding the column index a_col to this index gives the index at row a_row and column a_col.
    */
    T& ValueRowCol(unsigned int a_row, unsigned int a_col) const
    {
        // (a). The the row or column is out of range.
        if (a_row >= f_height || a_col >= f_width)
        { throw std::range_error("The given row and/or column are invalid."); }

        // (b). Index the array such that the correct value is returned.
        return f_grid[a_row * f_width + a_col];
    }

    void SetAllTo(T a_value)
    {
        unsigned int l_size = f_width * f_height;

        for (int i = 0; i < l_size; ++i)
        {
            f_grid[i] = a_value;
        }

    }



    T& operator[](unsigned int a_index)
    {
        if (a_index >= f_width * f_height)
        {
            throw std::range_error("The given index is invalid.");
        }

        return f_grid[a_index];
    }

    friend std::istream& operator>>(std::istream& a_istream, Array2D<T>& a_array)
    {
        int l_size = a_array.GetWidth() * a_array.GetHeight();

        for (int i = 0; i < l_size; ++i)
        {
            a_istream >> a_array[i];
        }

        return a_istream;
    }

};
