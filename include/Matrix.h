#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix
{
private:
    int mNumRows;
    int mNumCols;
    double **mData; // entries of matrix

public:
    Matrix(const Matrix& otherMatrix);
    Matrix(int numRows, int numCols);
    ~Matrix();

    int GetNumberOfRows() const;
    int GetNumberOfColumns() const;

    double& operator()(int i, int j);

    Matrix& operator=(const Matrix& otherMatrix);
    Matrix operator+() const;
    Matrix operator-() const;
    Matrix operator+(const Matrix& m1) const;
    Matrix operator-(const Matrix& m1) const;

    // scalar multiplication
    Matrix operator*(double a) const;

    Matrix Transpose() const;

    double CalculateDeterminant() const;

    friend Vector operator*(const Matrix& m,
                            const Vector& v);

    friend Vector operator*(const Vector& v,
                            const Matrix& m);

    // output operator
    friend std::ostream& operator<<(std::ostream& output,
                                    const Matrix& m1);

};

// prototype signature for friend operators
Vector operator*(const Matrix& m, const Vector& v);
Vector operator*(const Vector& v, const Matrix& m);

#endif // MATRIX_H
