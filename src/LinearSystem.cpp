#include <cmath>
#include <cassert>

#include "LinearSystem.h"
#include "Vector.h"
#include "Matrix.h"


LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
{
    // check matrix and vector are of compatible sizes
    int local_size = A.GetNumberOfRows();
    assert(A.GetNumberOfColumns() == local_size);
    assert(b.GetSize() == local_size);

    // set variables for linear system
    mSize = local_size;
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem()
{
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve()
{
    // Gaussian elimination

    Vector m(mSize);
    Vector solution(mSize);

    Matrix rA = *mpA;
    Vector rb = *mpb;

    // forward sweep of Gaussian elimination
    for (int k=0; k<mSize-1; k++)
    {
        // see if pivoting is necessary
        double max = 0.0;
        int row = -1;
        for (int i=k; i<mSize; i++)
        {
            if (fabs(rA(i+1, k+1)) > max)
            {
                row = i;
            }
        }
        assert(row>0);

        // pivot if necessary
        if (row != k )
        {
            // swap matrix rows k+1 with row+1
            for (int i=0; i<mSize; i++)
            {
                double temp = rA(k+1, i+1);
                rA(k+1, i+1) = rA(row+1, i+1);
                rA(row+1, i+1) = temp;
            }

            //swap vector entries k+1 with row+1
            double temp = rb(k+1);
            rb(k+1) = rb(row+1);
            rb(row+1) = temp;
        }

        // create zeros in lower part of column k
        for (int i=k+1; i<mSize; i++)
        {
            m(i+1) = rA(i+1, k+1)/rA(k+1, k+1);
            for (int j=k; j<mSize; j++)
            {
                rA(i+1, j+1) -= rA(k+1, j+1) * m(i+1);
            }
            rb(i+1) -= rb(k+1) * m(i+1);
        }
    }
  

    // back substitution
    for (int i=mSize-1; i>-1; i--)
    {
        solution(i+1) = rb(i+1);
        for (int j=i+1; j<mSize; j++)
        {
            solution(i+1) -= rA(i+1, j+1) * solution(j+1);
        }
        solution(i+1) /= rA(i+1, i+1);
    }

    return solution;
}

Vector LinearSystem::SolveTDMA()
{
    /***********************************************************************
     *  TDMA can only be used when Matrix A is a Tri-diagonal square matrix
     * eg.   [ b1 c1  0  0  0 ] [x1]   [d1]
     *       [ a2 b2 c2  0  0 ] [x2]   [d2]
     *       [ 0  c3 b3 c3  0 ] [x3] = [d3]
     *       [ 0  0  c4 b4 b4 ] [x4]   [d4]
     *       [ 0  0  0  c5 b5 ] [x5]   [d5]
     *
     * The code for this part is rewrite based on my 1d FVM solver which
     * could be found on my github:
     *
     *    https://github.com/cmzhang19/1D-convection-diffusion
     *
     * ref. 1. https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
     *      2. https://www.iist.ac.in/sites/default/files/people/tdma.pdf
     * ********************************************************************/

    Vector solution(mSize);

    Matrix rA = *mpA;
    Vector rb = *mpb;

    // set P1 = b1/a1, Q1 = d1/a1
    Vector P(mSize);
    Vector Q(mSize);


    // forward sweep
    P(1) = 0;
    Q(1) = solution(1);

    for (int i=2; i<mSize-1; i++)
    {
        P(i) = -rA(i, i+1) / ( rA(i, i) + rA(i, i-1) * P(i-1) );
        Q(i) = ( rb(i) - rA(i, i-1) * Q(i-1) ) / ( rA(i ,i) + rA(i, i-1) * P(i-1) );
    }

    P(mSize) = 0.0;
    Q(mSize) = solution(mSize);

    // back substitution
    for (int i=mSize-1; i>-1; i--)
    {
        solution(i) = P(i) * solution(i+1) + Q(i);

        solution(i+1) = rb(i+1);
        for (int j=i+1; j<mSize; j++)
        {
            solution(i+1) -= rA(i+1, j+1) * solution(j+1);
        }
        solution(i+1) /= rA(i+1, i+1);
    }

    return solution;
}
