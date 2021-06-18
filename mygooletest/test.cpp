#include <stdio.h>
#include <time.h>
#include <shengtang/ktest.h>
using namespace std;
int add(int a, int b) {
    return a + b;
}

TEST(test, add1) {
    LOG("test1.add")
    EXPECT_EQ(add(3, 4), 7);  // ==
    EXPECT_NE(add(3, 4), 6);  // !=
    EXPECT_LT(add(3, 4), 8);  // <
    EXPECT_LE(add(3, 4), 7);  // <=
    EXPECT_GT(add(3, 4), 6);  // >
    EXPECT_GE(add(3, 4), 7);  // >=
}

TEST(test, add2) {
    LOG("test2.add")
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
