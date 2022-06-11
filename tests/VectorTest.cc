#include <gtest/gtest.h>  // googletest header file
//#include <gmock/gmock.h>  // googletest header file

#include "LinearSystem.h"
#include "Vector.h"
#include <fstream>
#include <cmath>

class VectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
     vectorA[0] = 1;
     vectorA[1] = 2;
     vectorA[2] = 3;
     vectorB[0] = 3;
     vectorB[1] = 3;
     vectorB[2] = 3;
  }

  Vector vectorA = Vector(3);
  Vector vectorB = Vector(3);
  Vector vectorC = Vector(3);
  //void TearDown() override {}
};

TEST_F(VectorTest, CopyConstructor)
{
    vectorC = vectorA;
    ASSERT_TRUE(vectorC[0] = vectorA[0]);
    ASSERT_TRUE(vectorC[1] = vectorA[1]);
    ASSERT_TRUE(vectorC[2] = vectorA[2]);
}

TEST_F(VectorTest, GetSize)
{
    ASSERT_TRUE(vectorA.GetSize() == 3);
}

TEST_F(VectorTest, zero_based_indexing)
{
    ASSERT_TRUE(vectorA[0] == 1);
    ASSERT_TRUE(vectorA[1] == 2);
    ASSERT_TRUE(vectorA[2] == 3);
}

TEST_F(VectorTest, one_based_MATLAB_like_indexing)
{
    ASSERT_TRUE(vectorA(1) == 1);
    ASSERT_TRUE(vectorA(2) == 2);
    ASSERT_TRUE(vectorA(3) == 3);
}

TEST_F(VectorTest, read_only_zero_based_indexing)
{
    ASSERT_TRUE(vectorA.Read(0) == 1);
    ASSERT_TRUE(vectorA.Read(1) == 2);
    ASSERT_TRUE(vectorA.Read(2) == 3);
}

TEST_F(VectorTest, unary_plus)
{
    vectorA = +vectorA;
    ASSERT_TRUE(vectorA.Read(0) == 1);
    ASSERT_TRUE(vectorA.Read(1) == 2);
    ASSERT_TRUE(vectorA.Read(2) == 3);
}

TEST_F(VectorTest, unary_minus)
{
    vectorA = -vectorA;
    ASSERT_TRUE(vectorA.Read(0) == -1);
    ASSERT_TRUE(vectorA.Read(1) == -2);
    ASSERT_TRUE(vectorA.Read(2) == -3);
}

TEST_F(VectorTest, binary_plus)
{
    vectorC = vectorA + vectorB;
    ASSERT_TRUE(vectorC.Read(0) == 4);
    ASSERT_TRUE(vectorC.Read(1) == 5);
    ASSERT_TRUE(vectorC.Read(2) == 6);
}

TEST_F(VectorTest, binary_minus)
{
    vectorC = vectorA - vectorB;
    ASSERT_TRUE(vectorC.Read(0) == -2);
    ASSERT_TRUE(vectorC.Read(1) == -1);
    ASSERT_TRUE(vectorC.Read(2) == 0);
}

TEST_F(VectorTest, element_wise_product)
{
    vectorC = vectorA * 3;
    ASSERT_TRUE(vectorC.Read(0) == 3);
    ASSERT_TRUE(vectorC.Read(1) == 6);
    ASSERT_TRUE(vectorC.Read(2) == 9);
}

TEST_F(VectorTest, output)
{
    //EXPECT_EQ(0,0) << ::testing::PrintToString(vectorA);
    EXPECT_EQ(0,0) << vectorA;
}

TEST_F(VectorTest, p_norm_method)
{
    ASSERT_TRUE(vectorA.CalculateNorm()-sqrt(14)<1e-8);
    ASSERT_TRUE(vectorA.CalculateNorm(3)-pow(36,1.0/3)<1e-6);
}

TEST_F(VectorTest, length_friend)
{
    ASSERT_TRUE(length(vectorA)==3);
}