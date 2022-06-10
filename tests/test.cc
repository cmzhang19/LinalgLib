#include <gtest/gtest.h>  // googletest header file
//#include <gmock/gmock.h>  // googletest header file

#include "LinearSystem.h"
#include "Matrix.h"
#include "Vector.h"

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

// 结果字符串输出长度含尾字符长度为11，匹配有效等价类
TEST_F(VectorTest, test1)
{
    vectorC = vectorA + vectorB;
    ASSERT_TRUE(vectorC[0] == 4);
}

TEST_F(VectorTest, test2)
{
    vectorC = vectorA - vectorB;
    ASSERT_TRUE(vectorC[0] == -2);
}