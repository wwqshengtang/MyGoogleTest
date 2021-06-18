#include <iostream>
#include <cstdio>
using namespace std;

void (*FuncArr[3])() = {0};    // 存储区

void test1() {
    printf("function test1\n");
    return ;
}

void test2() {
    printf("function test2\n");
    return ;
}

void test3() {
    printf("function test3\n");
    return ;
}

/* 在主函数之前会有一些注册函数执行， 注册函数将相应的函数信息写到这片存储区中
然后在主函数中，在这片存储区中随机选择一个函数执行
注册函数： 一类保存函数信息的函数
*/
__attribute__((constructor))   //设置函数属性为构造函数，实现系统中的注册函数
void reg1() {
    FuncArr[0] = test1;
    return ;
}

__attribute__((constructor))   //设置函数属性为构造函数，实现系统中的注册函数
void reg2() {
    FuncArr[1] = test2;
    return ;
}

__attribute__((constructor))   //设置函数属性为构造函数，实现系统中的注册函数
void reg3() {
    FuncArr[2] = test3;
    return ;
}

int main() {
    srand(time(0));
    FuncArr[rand() % 3]();  //随机选择一个函数执行
    
    return 0;
}