#include <gtest/gtest.h>  // googletest header file
//#include <gmock/gmock.h>  // googletest header file

#include "LinearSystem.h"
#include "Matrix.h"
#include "Vector.h"
#include <fstream>
#include <cmath>

class MatrixTest : public ::testing::Test {
 protected:
  void SetUp() override {

     vectorA(1) = 1;
     vectorA(2) = 2;
     vectorA(3) = 3;

     matrixA(1,1) = 1;
     matrixA(1,2) = 2;
     matrixA(1,3) = 3;
     matrixA(2,1) = 1;
     matrixA(2,2) = 2;
     matrixA(2,3) = 3;
     matrixA(3,1) = 1;
     matrixA(3,2) = 2;
     matrixA(3,3) = 3;

     matrixB(1,1) = 3;
     matrixB(1,2) = 3;
     matrixB(1,3) = 3;
     matrixB(2,1) = 3;
     matrixB(2,2) = 3;
     matrixB(2,3) = 3;
     matrixB(3,1) = 3;
     matrixB(3,2) = 3;
     matrixB(3,3) = 3;
  }
  Vector vectorA = Vector(3);
  Matrix matrixA = Matrix(3,3);
  Matrix matrixB = Matrix(3,3);
  Matrix matrixC = Matrix(3,3);
  //void TearDown() override {}
};

TEST_F(MatrixTest, CopyConstructor)
{
    matrixC = matrixA;
    ASSERT_TRUE(matrixC(1,1) == matrixA(1,1));
    ASSERT_TRUE(matrixC(1,2) == matrixA(1,2));
    ASSERT_TRUE(matrixC(1,3) == matrixA(1,3));
    ASSERT_TRUE(matrixC(2,1) == matrixA(2,1));
    ASSERT_TRUE(matrixC(2,2) == matrixA(2,2));
    ASSERT_TRUE(matrixC(2,3) == matrixA(2,3));
    ASSERT_TRUE(matrixC(3,1) == matrixA(3,1));
    ASSERT_TRUE(matrixC(3,2) == matrixA(3,2));
    ASSERT_TRUE(matrixC(3,3) == matrixA(3,3));
}

TEST_F(MatrixTest, GetNumberOfRows)
{
    ASSERT_TRUE(matrixA.GetNumberOfRows() == 3);
}

TEST_F(MatrixTest, GetNumberOfColumns)
{
    ASSERT_TRUE(matrixA.GetNumberOfColumns() == 3);
}

TEST_F(MatrixTest, zero_based_MATLAB_like_indexing)
{
    ASSERT_TRUE(matrixA(1,1) == 1);
    ASSERT_TRUE(matrixA(1,2) == 2);
    ASSERT_TRUE(matrixA(1,3) == 3);
    ASSERT_TRUE(matrixA(2,1) == 1);
    ASSERT_TRUE(matrixA(2,2) == 2);
    ASSERT_TRUE(matrixA(2,3) == 3);
    ASSERT_TRUE(matrixA(3,1) == 1);
    ASSERT_TRUE(matrixA(3,2) == 2);
    ASSERT_TRUE(matrixA(3,3) == 3);
}

TEST_F(MatrixTest, unary_plus)
{
    matrixA = +matrixA;
    ASSERT_TRUE(matrixA(1,1) == 1);
    ASSERT_TRUE(matrixA(1,2) == 2);
    ASSERT_TRUE(matrixA(1,3) == 3);
    ASSERT_TRUE(matrixA(2,1) == 1);
    ASSERT_TRUE(matrixA(2,2) == 2);
    ASSERT_TRUE(matrixA(2,3) == 3);
    ASSERT_TRUE(matrixA(3,1) == 1);
    ASSERT_TRUE(matrixA(3,2) == 2);
    ASSERT_TRUE(matrixA(3,3) == 3);
}

TEST_F(MatrixTest, unary_minus)
{
    matrixA = -matrixA;
    ASSERT_TRUE(matrixA(1,1) == -1);
    ASSERT_TRUE(matrixA(1,2) == -2);
    ASSERT_TRUE(matrixA(1,3) == -3);
    ASSERT_TRUE(matrixA(2,1) == -1);
    ASSERT_TRUE(matrixA(2,2) == -2);
    ASSERT_TRUE(matrixA(2,3) == -3);
    ASSERT_TRUE(matrixA(3,1) == -1);
    ASSERT_TRUE(matrixA(3,2) == -2);
    ASSERT_TRUE(matrixA(3,3) == -3);
}

TEST_F(MatrixTest, binary_plus)
{
    matrixC = matrixA + matrixB;
    ASSERT_TRUE(matrixC(1,1) == 4);
    ASSERT_TRUE(matrixC(1,2) == 5);
    ASSERT_TRUE(matrixC(1,3) == 6);
    ASSERT_TRUE(matrixC(2,1) == 4);
    ASSERT_TRUE(matrixC(2,2) == 5);
    ASSERT_TRUE(matrixC(2,3) == 6);
    ASSERT_TRUE(matrixC(3,1) == 4);
    ASSERT_TRUE(matrixC(3,2) == 5);
    ASSERT_TRUE(matrixC(3,3) == 6);
}

TEST_F(MatrixTest, binary_minus)
{
    matrixC = matrixA - matrixB;
    ASSERT_TRUE(matrixC(1,1) == -2);
    ASSERT_TRUE(matrixC(1,2) == -1);
    ASSERT_TRUE(matrixC(1,3) == 0);
    ASSERT_TRUE(matrixC(2,1) == -2);
    ASSERT_TRUE(matrixC(2,2) == -1);
    ASSERT_TRUE(matrixC(2,3) == 0);
    ASSERT_TRUE(matrixC(3,1) == -2);
    ASSERT_TRUE(matrixC(3,2) == -1);
    ASSERT_TRUE(matrixC(3,3) == 0);
}

TEST_F(MatrixTest, scalar_multiplication)
{
    matrixC = matrixA * 3;
    ASSERT_TRUE(matrixC(1,1) == 3);
    ASSERT_TRUE(matrixC(1,2) == 6);
    ASSERT_TRUE(matrixC(1,3) == 9);
    ASSERT_TRUE(matrixC(2,1) == 3);
    ASSERT_TRUE(matrixC(2,2) == 6);
    ASSERT_TRUE(matrixC(2,3) == 9);
    ASSERT_TRUE(matrixC(3,1) == 3);
    ASSERT_TRUE(matrixC(3,2) == 6);
    ASSERT_TRUE(matrixC(3,3) == 9);
}

TEST_F(MatrixTest, Transpose)
{
    matrixC = matrixA.Transpose();
    ASSERT_TRUE(matrixC(1,1) == 1);
    ASSERT_TRUE(matrixC(1,2) == 1);
    ASSERT_TRUE(matrixC(1,3) == 1);
    ASSERT_TRUE(matrixC(2,1) == 2);
    ASSERT_TRUE(matrixC(2,2) == 2);
    ASSERT_TRUE(matrixC(2,3) == 2);
    ASSERT_TRUE(matrixC(3,1) == 3);
    ASSERT_TRUE(matrixC(3,2) == 3);
    ASSERT_TRUE(matrixC(3,3) == 3);
}

TEST_F(MatrixTest, CalculateDeterminant)
{
    ASSERT_TRUE(matrixA.CalculateDeterminant()==0);
}

TEST_F(MatrixTest, Matrix_Multiple_Vector)
{
    vectorA = matrixA * vectorA;
    ASSERT_TRUE(vectorA(1) == 14);
    ASSERT_TRUE(vectorA(2) == 14);
    ASSERT_TRUE(vectorA(3) == 14);
    ASSERT_TRUE(vectorA.GetSize() == 3);
}

TEST_F(MatrixTest, Vector_Multiple_Matrix)
{
    vectorA = vectorA * matrixA;
    ASSERT_TRUE(vectorA(1) == 6);
    ASSERT_TRUE(vectorA(2) == 12);
    ASSERT_TRUE(vectorA(3) == 18);
    ASSERT_TRUE(vectorA.GetSize() == 3);
}

TEST_F(MatrixTest, output)
{
    EXPECT_EQ(1,1) << matrixA;
}