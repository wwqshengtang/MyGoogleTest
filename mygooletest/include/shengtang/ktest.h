#ifndef _KTEST_H
#define _KTEST_H

#define LOG(frm, args...) { \
  printf("[%s : %s : %d]", __FILE__, __func__ ,__LINE__); \
  printf(frm, ##args); \   
  printf("\n"); \
}

// 颜色封装
#define COLOR(msg, code) "\033[0;" #code "m" msg "\033[0m"

#define RED(msg) COLOR(msg, 31)
#define GREEN(msg) COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)


#define EXPECT(a, comp, b) { \
    __typeof(a) __a = (a), __b = (b); \
    if (!((__a) comp (__b))) { \
        func_flag = 0; \
        printf(YELLOW("  %s : %d : Failure\n"), __FILE__, __LINE__); \
        printf(YELLOW("    Expected: (%s) %s (%s), actual: %d vs %d\n"),  \
               #a, #comp, #b, __a, __b); \
    } \
}

#define EXPECT_EQ(a, b) EXPECT(a, ==, b);
#define EXPECT_NE(a, b) EXPECT(a, !=, b);
#define EXPECT_LT(a, b) EXPECT(a, <, b);
#define EXPECT_LE(a, b) EXPECT(a, <=, b);
#define EXPECT_GT(a, b) EXPECT(a, >, b);
#define EXPECT_GE(a, b) EXPECT(a, >=, b);

//扩展出来的函数头部信息
// //扩展出来相关的注册函数
#define FUNC_NAME(a, b) shengtang_##a##_##b
#define TEST(a, b) \
void FUNC_NAME(a, b)(); \ 
__attribute__((constructor)) \
void reg_##shengtang_##a##_##b() { \        
    add_test_function(FUNC_NAME(a, b), #a "." #b); \
} \
void FUNC_NAME(a, b)()

// 存储区, 每个位置存储一个测试用例的函数地址
struct FuncData {
    void (*func)();  //测试用例的函数地址
    const char *func_name;   // 测试用例的函数名称
} func_arr[100];
int fun_arr_cnt = 0;  //计数量，计数当前存储区中存储了多少个测试用例
int func_flag;

void add_test_function(void (*func)(), const char *str) {
    func_arr[fun_arr_cnt].func = func;
    func_arr[fun_arr_cnt].func_name = str;
    fun_arr_cnt += 1;
    return ;
}

const char *RUN    = GREEN("[  RUN       ]  ");
const char *OK     = GREEN("[   OK       ]  ");
const char *FAILED = RED("[  FAILED    ]  ");


int RUN_ALL_TESTS() {
    // 遍历运行每个测试用例
    for (int i = 0; i < fun_arr_cnt; ++i) {
        printf("%s  %s\n", RUN, func_arr[i].func_name);
        func_flag = 1;
        long long b = clock();
        func_arr[i].func();
        long long e = clock();
        if (func_flag)
            printf("%s", OK);
        else
            printf("%s ", FAILED);
        printf("%s   "YELLOW("(%lld ms)") "\n", func_arr[i].func_name, 
              (e - b) * 1000 / CLOCKS_PER_SEC);

    }

    return 0;
}


#endif