#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

/**
 * @brief The Vector class
 */

class Vector
{
private:

    double* mData; // data stored in vector
    int mSize; // size of vector

public:

    Vector(const Vector& otherVector);
    Vector(int size);
    ~Vector();

    int GetSize() const;

    double& operator[](int i); // zero-based indexing

    // read-only zero-based indexing
    double Read(int i) const;
    double& operator()(int i); // one-based MATLAB-like indexing

    // operation definition
    Vector& operator=(const Vector& otherVector);
    Vector operator+() const; // unary +
    Vector operator-() const; // unary -
    Vector operator+(const Vector& v1) const; // binary +
    Vector operator-(const Vector& v1) const; // binary -

    // scalar multiplication (element-wise product)
    Vector operator*(double a) const;

    // output operator
    friend std::ostream& operator<<(std::ostream& output,
                                    const Vector& v1);

    // p-norm method
    double CalculateNorm(int p=2) const;

    // declare length function as a friend
    friend int length(const Vector& v);

};

// Prototype signature of length() firend function
int length(const Vector& v);

#endif // VECTOR_H
