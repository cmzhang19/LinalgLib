#include "Vector.h"
#include "Matrix.h"
#include <iostream>

using namespace std;

int main()
{

    Vector vec1(5);
    std::cout << vec1.GetSize() << std::endl;

    std::cout << vec1 << std::endl;

    Matrix mat1(2,2);
    cout << mat1(2,2) << endl;
    mat1(1,1) = 2;
    mat1(1,2) = 2;
    mat1(2,1) = 2;
    mat1(2,2) = 2;

    cout << "determinant: " << mat1.CalculateDeterminant() << endl;
    cout << mat1 << endl;

    return 0;
}
