#include <iostream>
#include <vector>

int fail = 0;

// 颜色封装
#define COLOR(msg, code) "\033[0;" #code "m" msg "\033[0m"

#define RED(msg) COLOR(msg, 31)
#define GREEN(msg) COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)

#define EXPECT(a, comp, b) { \
    __typeof(a) __a = (a), __b = (b); \
    if (!((__a) comp (__b))) { \
        UnitTest::GetInstance()->CurrentTestCase->nTestResult = 0; \
        fail++; \
        printf(RED("    Failed\n")); \
        printf(RED("    Expected: (%s) %s (%s)\n"), #a, #comp, #b); \
        printf(RED("    Actual : %d vs %d\n"), __a, __b); \
    } \
}

#define EXPECT_EQ(a, b) EXPECT(a, ==, b);
#define EXPECT_NE(a, b) EXPECT(a, !=, b);
#define EXPECT_LT(a, b) EXPECT(a, <, b);
#define EXPECT_LE(a, b) EXPECT(a, <=, b);
#define EXPECT_GT(a, b) EXPECT(a, >, b);
#define EXPECT_GE(a, b) EXPECT(a, >=, b);


#define TESTCASE_NAME(testcase_name) \
    testcase_name##_TEST

#define NANCY_TEST_(testcase_name) \
class TESTCASE_NAME(testcase_name) : public TestCase { \
public: \
    TESTCASE_NAME(testcase_name)(const char* case_name) : TestCase(case_name) {}; \
    virtual void Run(); \  
private: \
    static TestCase* const testcase_; \
}; \
\
TestCase* const TESTCASE_NAME(testcase_name)::testcase_ =  \
    UnitTest::GetInstance()->RegisterTestCase(new TESTCASE_NAME(testcase_name)(#testcase_name)); \
void TESTCASE_NAME(testcase_name)::Run()


// TEST宏
#define NTEST(testcase_name) \
    NANCY_TEST_(testcase_name)

#define RUN_ALL_TESTS() \
    UnitTest::GetInstance()->Run();


class TestCase {
public:
    TestCase(const char *case_name) : testcase_name(case_name) {}

    virtual void Run() = 0;  // 执行测试案例的方法

    int nTestResult;  // 测试案例的执行结果 
    const char *testcase_name;  // 测试案例名称
};

class UnitTest {
public:
    // 获取单例
    static UnitTest* GetInstance(); 

    // 注册测试案例
    TestCase* RegisterTestCase(TestCase* testcase);

    // 执行单元测试
    int Run();

    TestCase* CurrentTestCase; // 记录当前执行的测试案例
    int nTestResult; // 总的执行结果
    int nPassed; // 通过案例数
    int nFailed; // 失败案例数
private:
    std::vector<TestCase*> testcases_; // 案例集合
};

UnitTest* UnitTest::GetInstance() {
    static UnitTest instance;
    return &instance; 
}

TestCase* UnitTest::RegisterTestCase(TestCase* testcase) {
    testcases_.push_back(testcase);
    return testcase;
}

int UnitTest::Run() {
    UnitTest::nTestResult = 1;
    for (std::vector<TestCase*>::iterator it = testcases_.begin();
            it != testcases_.end(); ++it) 
    {
        TestCase *tmp = *it;
        CurrentTestCase = tmp;
        printf(GREEN("======================================\n"));
        printf(GREEN("Run TestCase :  %s\n"), tmp->testcase_name);
        tmp->Run();
        printf(GREEN("End TestCase :  %s\n"), tmp->testcase_name);

        if (tmp->nTestResult)
            nPassed++;

        else {
            nFailed++;
            nTestResult = 0; 
        }
    }
    printf(GREEN("======================================\n"));
    printf(GREEN("Total TestCase :  %d\n"), nPassed + nFailed);
    printf(GREEN("Passed :  %d\n"), nPassed + nFailed - fail);
    printf(RED("Failed :  %d\n"), fail);
    return nTestResult;
}

