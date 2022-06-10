#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "Vector.h"
#include "Matrix.h"

class LinearSystem
{
private:
    int mSize; // size of linear system

    // Ax = b
    Matrix* mpA; // matrix for linear system
    Vector* mpb; // vector for linear system

    //LinearSystem (const LinearSystem& otherLinearSystem);

public:
    //LinearSystem(const Matrix& A, const Vector& b);

    ~LinearSystem();

    virtual Vector Solve();
};

#endif // LINEARSYSTEM_H
