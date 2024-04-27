#include <gtest/gtest.h>

extern "C" {
    int a_lib_function();
}

TEST(MyTest, ExampleTest) {
    ASSERT_EQ(a_lib_function(), 18);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

