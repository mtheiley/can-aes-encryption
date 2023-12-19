#include <gtest/gtest.h>

TEST(ExampleTest, test1) {
    int i = 0;
    EXPECT_EQ(0, i);
}

TEST(ExampleTest, test2) {
    int i = 0;
    EXPECT_EQ(1, i);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}