#include "gtest/gtest.h"
#include "QueueTest.hpp"
//#include "QueueTestString.hpp"

using TestTypes = testing::Types<int, long, float, double>;
INSTANTIATE_TYPED_TEST_SUITE_P(Initial, QueueTest, TestTypes);

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}