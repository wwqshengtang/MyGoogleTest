#include <shengtang/ctest.h>

int add(int a, int b) {
    return a + b;
}

NTEST(AddTest1) {
    
    EXPECT_EQ(add(3, 4), 7);  // ==
    EXPECT_NE(add(3, 4), 6);  // !=
    EXPECT_LT(add(3, 4), 8);  // <
    EXPECT_LE(add(3, 4), 7);  // <=
    EXPECT_GT(add(3, 4), 6);  // >
    EXPECT_GE(add(3, 4), 7);  // >=
}

NTEST(Addtest2) {
    
    EXPECT_EQ(add(3, 4), 7);  // ==
    EXPECT_NE(add(3, 4), 6);  // !=
    EXPECT_LT(add(3, 4), 6);  // <
    EXPECT_LE(add(3, 4), 7);  // <=
    EXPECT_GT(add(3, 4), 6);  // >
    EXPECT_GE(add(3, 4), 7);  // >=
}

int main() {
    return RUN_ALL_TESTS();
}
