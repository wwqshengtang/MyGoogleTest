#include <iostream>
#include <vector>
#include <time.h>
#include <shengtang/ktest.h>
using namespace std;

// 版本1， 简单的快速排序
void quick_sort_v1(int *arr, int l, int r) {
    if (l >= r)
        return;
    int x = l, y = r, z = arr[l];
    while (x < y) {
        while (x < y && arr[y] >= z)
            --y;
        if (x < y)
            arr[x++] = arr[y];
        while (x < y && arr[x] <= z)
            ++x;
        if (x < y)
            arr[y--] = arr[x];
    }
    arr[x] = z;

    quick_sort_v1(arr, l, x - 1);
    quick_sort_v1(arr, x + 1, r);
    return ;
}

#define swap(a, b) { \
    __typeof(a) __a = a; \
    a = b, b = __a; \
}

// 三点取中法
int median(int a, int b, int c) {
    if (a > b)
        swap(a, b)
    if (a > c)
        swap(a, c);
    if (b > c)
        swap(b, c);
    return b;
}

// 版本2，单边递归法，三点取中法, 无监督partition
void quick_sort_v2(int *arr, int l, int r) {
    while (l < r) {
        int x = l, y = r;
        int z = median(arr[l], arr[(l + r) >> 1], arr[r]);  //三点取中
        do {
            while (arr[x] < z)
                x++;
            while (arr[y] > z)
                y--;
            if (x <= y) {
                swap(arr[x], arr[y]);
                x++;
                y--;
            }
                
        }while (x <= y);
        quick_sort_v2(arr, x, r); //对右区间进行递归排序，
        r = y;    // 左区间在本层进行排序
    }  
    return ;
}

const int threshold = 16;

void __quick_sort_v3(int *arr, int l, int r) {
    while (r - l > threshold) {
        int x = l, y = r;
        int z = median(arr[l], arr[(l + r) >> 1], arr[r]);  //三点取中
        do {
            while (arr[x] < z)
                x++;
            while (arr[y] > z)
                y--;
            if (x <= y) {
                swap(arr[x], arr[y]);
                x++;
                y--;
            }
                
        }while (x <= y);
        __quick_sort_v3(arr, x, r); //对右区间进行递归排序，
        r = y;    // 左区间在本层进行排序
    }  
    return ;
}

// 插入排序，优化版
void insert_sort(int *arr, int l, int r) {
    int ind = l;
    for (int i = l + 1; i <= r; ++i) {
        if (arr[ind] > arr[i])
            ind = i;
    }
    swap(arr[ind], arr[l]);
    for (int i = l + 2; i <= r; ++i) {
        int j = i;
        while (arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            --j;
        }
    }
    return ;
}

//版本3， 设定阈值 + 插入排序
void quick_sort_v3(int *arr, int l, int r) {
    __quick_sort_v3(arr, l, r);
    insert_sort(arr, l, r);
    return ;
}


#define MAX_N 10000000
int *arr;
int *getRandData(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    return arr;
}

int check(int *arr, int n) {
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1])
            return 0;
    }
    return 1;
}

int *copyArray(int *arr, int n) {
    int *tmp = (int *)malloc(sizeof(int) * n);
    memcpy(tmp,arr, sizeof(int) * n);
    return tmp;
}

TEST(test, quick_sort_v1) {
    int *tmp =  copyArray(arr, MAX_N);
    quick_sort_v1(tmp, 0, MAX_N - 1);
    EXPECT_EQ(check(tmp, MAX_N), 1);
}

TEST(test, quick_sort_v2) {
    int *tmp =  copyArray(arr, MAX_N);
    quick_sort_v2(tmp, 0, MAX_N - 1);
    EXPECT_EQ(check(tmp, MAX_N), 1);
}

TEST(test, quick_sort_v3) {
    int *tmp =  copyArray(arr, MAX_N);
    quick_sort_v3(tmp, 0, MAX_N - 1);
    EXPECT_EQ(check(tmp, MAX_N), 1);
}

int main() {
    srand(time(0));
    arr = getRandData(MAX_N);

    return RUN_ALL_TESTS();
}