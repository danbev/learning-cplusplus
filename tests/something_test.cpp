#include <gtest/gtest.h>
#include "../src/something.h"
#include <iostream>

class SomethingTest : public ::testing::Test {
protected:
    Something something;
};

TEST_F(SomethingTest, TestSomething) {
    EXPECT_EQ(something.call(1), "bajja");
    // enable with --gtest_print_time=0
    std::cout << "TestSomething: " << something.call(1) << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
