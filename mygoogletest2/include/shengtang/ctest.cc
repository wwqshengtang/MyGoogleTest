#include <iostream>
#include <vector>


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
    nTestResult = 1;
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
    printf(GREEN("Passed :  %d\n"), nPassed);
    printf(RED("Failed :  %d\n"), nFailed);
    return nTestResult;
}

