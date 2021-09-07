#include "gtest/gtest.h"
#include "QueueTest.hpp"
#include "QueueTestString.hpp"

extern std::vector<std::string> names;

template <typename T>
struct TypeName {
    std::string name = typeid(T).name();
};

class TypeNames {
public:
    template <typename T>
    static std::string GetName(int type) {
        TypeName<T> tn;
        std::string s{ "Type" };
        for (auto& n : names) {
            if (tn.name == n) {
                s = n;
            }
        }
        return s;
    }
};

REGISTER_TYPED_TEST_SUITE_P(QueueTest,
    DefaultConstructor,
    MoveConstructor,
    Size,
    EnqueueNode,
    EnqueueItem,
    Dequeue
);

using TestTypes = testing::Types<char, int, long, float, double>;

std::vector<std::string> names {
    "char",
    "int",
    "long",
    "float",
    "double"
};

INSTANTIATE_TYPED_TEST_SUITE_P(Param, QueueTest, TestTypes, TypeNames);

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}