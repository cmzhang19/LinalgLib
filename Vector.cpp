#include <cmath>
#include <iostream>
#include <cassert>

#include "Vector.h"


/**
 * @brief Vector::Vector
 *  Overridden copy constructor.
 *  Allocates memory for new vector, and copies entries of other
 *  vector into it.
 * @param otherVector
 */
Vector::Vector(const Vector &otherVector)
{
    mSize = otherVector.GetSize();
    mData = new double [mSize];
    for (int i=0; i<mSize; i++)
    {
        mData[i] = otherVector.mData[i];
    }
}

/**
 * @brief Vector::Vector
 * @param size
 */
Vector::Vector(int size)
{
    assert(size > 0);
    mSize = size;
    mData = new double [mSize];
    for (int i=0; i<mSize; i++)
    {
        mData[i] = 0.0;
    }
}

Vector::~Vector()
{
    delete[] mData;
}

/**
 * @brief Vector::GetSize
 * Method to get the size of a vector
 * @return size
 */
int Vector::GetSize() const
{
    return mSize;
}

/**
 * @brief Vector::operator []
 * @param i
 * @return
 */
double& Vector::operator[](int i)
{
    assert(i > -1);
    assert(i < mSize);
    return mData[i];
}

/**
 * @brief Vector::Read
 * @param i
 * @return
 */
double Vector::Read(int i) const
{
    assert(i > -1);
    assert(i < mSize);
    return mData[i];
}

/**
 * @brief Vector::operator ()
 * @param i
 * @return
 */
double& Vector::operator()(int i)
{
    assert(i > 0);
    assert(i < mSize+1);
    return mData[i-1];
}

/**
 * @brief Vector::operator =
 *  Overloading the assignment operator
 * @param otherVector
 * @return
 */
Vector& Vector::operator=(const Vector& otherVector)
{
    assert(mSize == otherVector.mSize);
    for (int i=0; i<mSize; i++)
    {
        mData[i] = otherVector.mData[i];
    }
    return *this;
}

/**
 * @brief Vector::operator +
 * @return
 */
Vector Vector::operator+() const
{
    Vector v(mSize);
    for (int i=0; i<mSize; i++)
    {
        v[i] = mData[i];
    }
    return v;
}

/**
 * @brief Vector::operator -
 * @return
 */
Vector Vector::operator-() const
{
    Vector v(mSize);
    for (int i=0; i<mSize; i++)
    {
        v[i] = -mData[i];
    }
    return v;
}

/**
 * @brief Vector::operator +
 * @param v1
 * @return
 */
Vector Vector::operator+(const Vector& v1) const
{
    assert(mSize == v1.mSize);
    Vector v(mSize);
    for (int i=0; i<mSize; i++)
    {
        v[i] = mData[i] + v1.mData[i];
    }
    return v;
}

/**
 * @brief Vector::operator -
 * @param v1
 * @return
 */
Vector Vector::operator-(const Vector& v1) const
{
    assert(mSize == v1.mSize);
    Vector v(mSize);
    for (int i=0; i<mSize; i++)
    {
        v[i] = mData[i] - v1.mData[i];
    }
    return v;
}

/**
 * @brief Vector::operator *
 * @param a
 * @return
 */
Vector Vector::operator*(double a) const
{
    Vector v(mSize);
    for (int i=0; i<mSize; i++)
    {
        v[i] = a*mData[i];
    }
    return v;
}

std::ostream& operator<<(std::ostream& output, const Vector& v1)
{
    // Format as "[a; b; c]", a column vector
    output << "[" << " ";
    for (int i=0; i < v1.GetSize(); i++)
    {
        output << v1.mData[i] << "; ";
        if(i == v1.GetSize() - 1)
        {
            output << v1.mData[i] << " ";
        }
    }
    output << "]";

    return output;
}

/**
 * @brief Vector::CalculateNorm
 * @param p
 * @return
 */
double Vector::CalculateNorm(int p) const
{
    double norm_val;
    double sum = 0.0;

    for (int i=0; i<mSize; i++)
    {
        sum += pow(fabs(mData[i]), p);
    }

    norm_val = pow(sum, 1.0/((double)(p)));
    return norm_val;
}

/**
 * @brief length
 * @param v
 * @return
 */
int length(const Vector& v)
{
    return v.mSize;
}








