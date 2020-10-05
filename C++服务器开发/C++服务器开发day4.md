## C++服务器开发day4

### 快速排序七个版本

基本方法：partition法（分区法）

- 选择基准值(第一个元素)
- partition过程
- 递归排序

头部一个指针l指向基准值，尾部一个指针r。

然后两个指针交替移到。

因为头部有一个空位(基准值)，所以先移动尾指针

然后尾指针和基准值比较，小，就放基准值前面。然后前移尾指针。

然后头指针后移，和基准值进行比较，大，就放基准值后面。

基准值会去到正确位置上面。

最后基准值把数组分成两部分。

前面是比基准值小，后面是比基准值大。

```c
//quick_sort.h
#ifndef _QUICK_SORT_H
#define _QUICK_SORT_H

void quick_sort_v1(int *arr, int l, int r);

#endif

```

```cpp
//quick_sort.cpp
void quick_sort_v1(int *arr, int l, int r) {
    if (l >= r) return ;
    //选择基准值z
    int x = l, y = r, z = arr[l];
    //partition过程
    while (x < y) {
        //移动尾指针，找到一个小于基准值的元素arr[y]
        while (x < y && arr[y] >= z) --y;
        if (x < y) arr[x++] = arr[y];
        //移动头指针，找到一个大于基准值的元素arr[x]
        while (x < y && arr[x] <= z) ++x;
        if (x < y) arr[y--] = arr[x];
    }
    //头尾指针重合，这个位置就是基准值应该放的位置
    arr[x] = z;
    //递归排序
    quick_sort_v1(arr, l, x - 1);
    quick_sort_v1(arr, x + 1, r);
    return ;
}
```

```c
//test.h
#ifndef _TEST_H
#define _TEST_H

#define TEST(func, arr, n) { \
    int *temp = (int *)malloc(sizeof(int) * n); \//开辟数组空间
    for (int i = 0; i < n; i++) temp[i] = arr[i]; \//拷贝数组
    long long b = clock(); \//cpu滴答数开始时间
    func(temp, 0, n - 1); \//传递给快速排序函数
    long long e = clock(); \//cpu滴答数结束时间
    if (check(temp, 0, n - 1)) { \//检查是否有序
        printf("\033[1;32m[    OK    ]\033[0m %s ", #func); \
    } else { \
        printf("\033[1;31m[  FAILED  ]\033[0m %s ", #func); \
    } \
    printf("\033[1;33m(%lld ms)\033[0m\n", 1000 * (e - b) / CLOCKS_PER_SEC); \//CLOCKS_PER_SEC：每秒滴答数
}

int check(int *, int, int);
int *getRandData(int);

#endif

```

```c
//quick_sort_test.cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "test.h"
#include "quick_sort.h"
using namespace std;
//检查函数
int check(int *arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < arr[i - 1]) return 0;
    }
    return 1;
}
//获得随机数据数组，返回值是数组的地址，int *类型
int *getRandData(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
    return arr;
}
int main() {
    #define MAX_N 10000000
    int *arr = getRandData(MAX_N);//arr是一个数组
    TEST(quick_sort_v1, arr, MAX_N);
    #undef MAX_N//取消以前定义的宏定义
    return 0;
}

```

### 单边递归法

二分算法

二叉树

当进行完partition，需要等两边子树执行完递归。

怎么优化呢？

可以让左边继续递归，右边由自己主程序继续执行

```cpp
//quick_sort.cpp
void quick_sort_v2(int *arr, int l, int r){
    //多加个循环，代替右边递归
    while (l < r) {
        //选则基准值
        int x = l, y = r, z = arr[l];
        //partition过程
        while (x < y){
            while (x < y && arr[y] >= z) --y;
            if (x < y) arr[x++] = arr[y];
            while (x < y && arr[x] <= z) ++x;
            if (x < y) arr[y--] = arr[x];
        }
        arr[x] = z;
        
        quick_sort_v2(arr, l, x - 1);//左边递归排序
        l = x + 1;//右边更新
    }
    return ;
}
```

算法工程师之间的竞争，并不是时间复杂度，因为你能想到他也能想到。

是什么？是细节的把握。是实现方案。是程序。

时间复杂度只是基础功。

学算法不只是学算法思想，还要学算法实现。

因为一种算法不止一种实现方法。

程序优化，很多时候只是一种优化思想，优化是概率性的，还要看系统。

### 无监督优化

判断坐标范围越界

限制条件就是监督项

无监督优化就是去掉监督项

插入排序

分成未排序区和已排序区。

每次从未排序区中选择一个第一个值插入到已排序区。

```cpp
//insert_sort.cpp
#define SWAP(X,Y) X=X+Y;Y=X-Y;X=X-Y
#define swap(a, b) {\
	__typeof(a) __a = a;\
	a = b, b = __a;\
}
void insert_sort(int *arr, int l, int r){
    for (int i = l + 1; i <= r;i++) {
        //从未排序中第一个元素开始判断。
        int j = i;
        //如果比已排序最后一个元素小，交换。
        //如果还小，继续交换，所以while循环
        //保证已排序区都是有序的。
        while (j > 0 && arr[j] < arr[j-1]) {
            //SWAP(arr[j], arr[j-1]);
            swap(arr[j], arr[j-1]);
        	--j;
        }  
    }
    return ;
}
```

j > 0就是监督项。

为什么需要这个条件，就是怕--j的时候，j去到0这个位置，然后arr[j-1]就访问越界了。

那么什么时候j会跑到0这个位置？

arr[j]比前面已经排序的元素都要小的时候，j就需要等于0。

那么如果我们一开始就把最小值放在第一个位置。

这样j怎么样都是大于0的。

所以先需要找到最小值。然后将这个最小值放第一个位置。

```c
//insert_sort.cpp
#define swap(a, b) {\
	__typeof(a) __a = a;\
	a = b, b = __a;\
}
void insert_sort_v2(int *arr, int l, int r){
    int ind = l;
    //找最小值
    for(int i = l + 1; i <= r; i++) {
        if (arr[ind] > arr [i]) ind = i;
    }
    //swap(arr[ind], arr[l]);
    //这样影响稳定性，不能直接swap
    //和前面的值，依次交换，不影响稳定性。
   	while (ind > l) {
        swap(arr[ind], arr[ind - 1]);
        --ind;
    }
    for (int i = l + 2; i <= r; i++) {
        int j = i;
        //找到小值，放前面。
        while (arr[j] < arr[j-1]) {
            swap(arr[j], arr[j-1]);
        	--j;
        }  
    }
    return ;
}
```

无监督快速排序

这里的监督项是x<y

确定了基准值

前后元素的数量就一定了。

把一个大的放后面，就会有一个小的放前面。

意味着左右两边违反规则的元素是相等的。

因此可以头尾指针一起走，可以成对交换

```cpp
//quick_sort.cpp
#define swap(a, b) {\
	__typeof(a) __a = a;\
	a = b, b = __a;\
}
void quick_sort_v3(int *arr, int l, int r){
    while (l < r) {
        //选则基准值
        int x = l, y = r, z = arr[l];
        //partition过程
        do {
            //找到比基准值大的数arr[x]
            while (arr[x] < z) ++x;
            //找到比基准值小的数arr[y]
            while (arr[y] > z) --y;
            if (x <= y){
                swap(arr[x], arr[y]);
                ++x, --y;
            }   
        }while (x <= y);
        quick_sort_v3(arr, l, y);//递归排序
        l = x;//右边更新
    }
    return ;
}
```

### 基准值选择

快速排序的时间复杂度

本层做partition过程的时间复杂度

头尾指针移动次数，和长度有关，O(n)

第二层做partition过程的总时间复杂度O(n-1)=O(n)

每一层都是O(n)

所以快速排序的时间复杂度为O(n*h),h为树高

<img src="C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200821211724518.png" alt="image-20200821211724518" style="zoom:50%;" />

h = log n 快速排序的时间复杂度为O(n*h)

h = n 快速排序的时间复杂度为O(n^2)

所以怎么让快速排序的时间复杂度稳定为O(n*h)

就是通过控制树的高度。

所以应该让它成为平衡二叉树。

选基准值的时候，尽可能让左右两边元素相等。

1.选基准值的时候，随机选择，期望是中位数

```c
//quick_sort.cpp
#define swap(a, b) {\
	__typeof(a) __a = a;\
	a = b, b = __a;\
}
void quick_sort_v4(int *arr, int l, int r){
    while (l < r) {
        //选则基准值
        int x = l, y = r, z = arr[l + rand()%(r - l + 1)];
        //partition过程
        do {
            while (arr[y] > z) --y;
            while (arr[x] < z) ++x;
            if (x <= y){
                swap(arr[x], arr[y]);
                ++x, --y;
            }   
        }while (x <= y);
        quick_sort_v4(arr, l, y);//递归排序
        l = x;//右边更新
    }
    return ;
}
```

在有序的数据中，更有效。

2.三点取中法

取左端、中间、右端三个数，然后进行排序，将中间数作为基准值。

```cpp
//quick_sort.cpp
#define swap(a, b) {\
	__typeof(a) __a = a;\
	a = b, b = __a;\
}
//寻找三者中最小值
int median(int *arr, int l, int r) {
    int a = arr[l], b = arr[r], c = arr[(l+r) >> 1];
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    return b;
}
void quick_sort_v5(int *arr, int l, int r){
    while (l < r) {
        //选则基准值
        int x = l, y = r, z = median(arr, l, r);
        //partition过程 
        do {
            while (arr[y] > z) --y;
            while (arr[x] < z) ++x;
            if (x <= y){
                swap(arr[x], arr[y]);
                ++x, --y;
            }   
        }while (x <= y);
        quick_sort_v5(arr, l, y);//递归排序
        l = x;//右边更新
    }
    return ;
}
```

