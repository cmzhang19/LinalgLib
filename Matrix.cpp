#include <cmath>
#include <cassert>
#include "Matrix.h"

Matrix::Matrix(const Matrix& otherMatrix)
{
    mNumRows = otherMatrix.mNumRows;
    mNumCols = otherMatrix.mNumCols;

    // initialize matrix
    mData = new double* [mNumRows];
    for (int i=0; i<mNumRows; i++)
    {
        mData[i] = new double [mNumCols];
    }

    // assign value to each entries
    for (int i=0; i<mNumRows; i++)
    {
        for(int j=0; j<mNumCols; i++)
        {
            mData[i][j] = otherMatrix.mData[i][j];
        }
    }
}

Matrix::Matrix(int numRows, int numCols)
{
    assert(numRows > 0);
    assert(numCols > 0);
    mNumRows = numRows;
    mNumCols = numCols;

    mData = new double* [mNumRows];
    for (int i=0; i<mNumRows; i++)
    {
        mData[i] = new double [numCols];
    }
    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; i<mNumCols; i++)
        {
            mData[i][j] = 0.0;
        }
    }
}

Matrix::~Matrix()
{
    for (int i=0; i<mNumRows; i++)
    {
        delete mData[i];
    }
    delete[] mData;
}

int Matrix::GetNumberOfRows() const
{
    return mNumRows;
}

int Matrix::GetNumberOfColumns() const
{
    return mNumCols;
}

double& Matrix::operator()(int i, int j)
{
    assert(i > 0);
    assert(i < mNumRows+1);
    assert(j > 0);
    assert(j < mNumCols+1);

    return mData[i-1][j-1];
}

Matrix& Matrix::operator=(const Matrix& otherMatrix)
{
    assert(mNumRows == otherMatrix.mNumRows);
    assert(mNumCols == otherMatrix.mNumCols);

    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; j<mNumCols; j++)
        {
            mData[i][j] = otherMatrix.mData[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+() const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; i<mNumCols; j++)
        {
            mat(i+1, j+1) = mData[i][j];
        }
    }
    return mat;
}

Matrix Matrix::operator-() const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; j<mNumCols; j++)
        {
            mat(i+1, j+1) = -mData[i][j];
        }
    }
    return mat;
}

Matrix Matrix::operator+(const Matrix& m1) const
{
    assert(mNumRows == m1.mNumRows);
    assert(mNumCols == m1.mNumCols);

    Matrix mat(mNumRows, mNumCols);

    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; j<mNumCols; j++)
        {
           mat(i+1, j+1) = mData[i][j] + m1.mData[i][j];
        }
    }
    return mat;
}

Matrix Matrix::operator-(const Matrix& m1) const
{
    assert(mNumRows == m1.mNumRows);
    assert(mNumCols == m1.mNumCols);

    Matrix mat(mNumRows, mNumCols);

    for (int i=0; i<mNumRows; i++)
    {
        for (int j=0; j<mNumCols; j++)
        {
           mat(i+1, j+1) = mData[i][j] - m1.mData[i][j];
        }
    }
    return mat;
}

Matrix Matrix::operator*(double a) const
{
    Matrix mat(mNumRows, mNumCols);
    for (int i=0; i<mNumRows; i++)
    {
        for(int j=0; j<mNumCols; j++)
        {
            mat(i+1,j+1) = a*mData[i][j];
        }
    }
    return mat;
}

Matrix Matrix::Transpose() const
{
    Matrix mat(mNumRows, mNumCols);

    if(mNumRows==mNumCols) // square matrix
    {
        for (int i=0; i<mNumRows; i++)
        {
            for (int j=0; j<mNumCols; j++)
            {
                mat(i+1, j+1) = mData[j][i];
            }
        }
    }
    else // an arbitrary matrix eg.rectangular
    {
        int temp = mat.mNumRows;
        mat.mNumRows = mat.mNumCols;
        mat.mNumCols = temp;

        for (int i=0; i<mNumCols; i++)
        { // M x N -> N x M, start from N which is #cols previous
            for (int j=0; j<mNumRows; j++)
            {
                mat(i+1, j+1) = mData[j][i];
            }
        }
    }
    return mat;
}

double Matrix::CalculateDeterminant() const
{
    assert(mNumRows == mNumCols);
    double determinant = 0.0;

    if (mNumRows == 1)
    {
        determinant = mData[0][0];
    }
    else
    {
        // More than one entry of matrix
        for (int i_outer=0; i_outer<mNumRows; i_outer++)
        {
            Matrix sub_matrix(mNumRows-1, mNumCols-1);

            for (int i=0; i<mNumRows-1; i++)
            {
                for (int j=0; j<i_outer; j++)
                {
                    sub_matrix(i+1, j+1) = mData[i+1][j];
                }
                for (int j=i_outer; j<mNumRows-1; j++)
                {
                    sub_matrix(i+1, j+1) = mData[i+1][j+1];
                }
            }
            // recursion
            double sub_matrix_determinant = sub_matrix.CalculateDeterminant();
            determinant += pow(-1.0, i_outer) * mData[0][i_outer] * sub_matrix_determinant;
        }
    }
    return determinant;
}

Vector operator*(const Matrix& m, const Vector& v)
{
    int original_vector_size = v.GetSize();
    assert(m.GetNumberOfColumns() == original_vector_size);
    int new_vector_length = m.GetNumberOfRows();
    Vector new_vector(new_vector_length);

    for (int i=0; i<new_vector_length; i++)
    {
        for (int j=0; j<original_vector_size; j++)
        {
            new_vector[i] += m.mData[i][j] * v.Read(j);
        }
    }
    return new_vector;
}

Vector operator*(const Vector& v, const Matrix& m)
{
    int original_vector_size = v.GetSize();
    assert(m.GetNumberOfRows() == original_vector_size);
    int new_vector_lenth = m.GetNumberOfColumns();

    Vector new_vector(new_vector_lenth);

    for (int i=0; i<new_vector_lenth; i++)
    {
        for (int j=0; j<original_vector_size; j++)
        {
            new_vector[i] += v.Read(j) * m.mData[j][i];
        }
    }

    return new_vector;
}

std::ostream& operator<<(std::ostream& output, const Matrix& m1)
{
    // Format as "[ a, b, c ]
    //            [ d, e, f ]"
    // 需要更新打印形式,当前形式容易与两个vector混淆

    output << "Matrix:\n";
    for (int i=0; i < m1.mNumRows; i++ )
    {
        output << "[ ";
        for (int j=0; j < m1.mNumCols; j++)
        {
            if (j == m1.mNumCols - 1)
            {
                output << m1.mData[i][j] << " ";
            }
            else
            {
                output << m1.mData[i][j] << ", ";
            }
        }
        output << "] \n";
    }
    return output;
}
