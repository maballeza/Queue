#include "gtest/gtest.h"
#include "QueueTest.hpp"
#include "QueueTestString.hpp"
#include <string>

class TypeStrings {
public:
    template<typename T>
    static std::string GetName(int ind) {
        switch (ind) {
        case 0:
            return "Int";
        case 1:
            return "Long";
        case 2:
            return "Float";
        case 3:
            return "Double";
        default:
            return "User-Defined";
        }
    }
};

using TestTypes = testing::Types<int, long, float, double>;
INSTANTIATE_TYPED_TEST_SUITE_P(Initial, QueueTest, TestTypes, TypeStrings);

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}