## C++服务器开发day3

### 算法思维

二分算法

二分查找->二分函数->二分答案

这样分开学就很复杂

满足下列两个条件一般用二分算法

1.二分算法解决的是求解单调函数f(x)

把f(x)课程一个f[x]数组，这就是一个有序数组

2.给x容易求f(x)，给f(x)不容易求x时用二分查找

给数组下标，找值容易。

给一个值，找数组下标不容易。所以用二分查找

考研还是就业？

有多少人是因为没找到工作才去考研的？

这不是两个选择，这是一种能力。

有能力了，才可以考虑去工作还是读研究生。

### 认清大环境的共识

学历没有那么重要，它不是减分项。

哈工大，哈理工，哈工程。其他省份的面试官可能根本不知道大学的区别。除非你是清华北大的。

### 快速排序

基本方法：partition法（分区法）

- 选择基准值(第一个元素)
- partition过程
- 递归排序

头部一个指针h指向基准值，尾部一个指针t。

然后尾指针和基准值比较，小，就放前面。然后前移尾指针。

然后头指针后移，和基准值进行比较，大，就放后面。

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
void quick_sort_v1(int *arr, int l, int r){
    if (l >= r) return ;
    //选则基准值
    int x = l, y = r, z = arr[l];
    //partition过程
    while (x < y){
        while (x < y && arr[y] >= z) --y;
        if (x < y) arr[x++] = arr[y];
        while (x < y && arr[y] <= z) ++x;
        if (x < y) arr[y--] = arr[x];
    }
    //递归排序
    arr[x] = z;
    quick_sort_v1(arr, l, x - 1);
    quick_sort_v1(arr, x + 1, r);
    return ;
}
```

```c
//test.h
#ifndef _TEST_H
#define _TEST_H
#define TEST(func, arr, n) {\
	int *temp = (int *)malloc(sizeof(int) * n);\
	for (int i = 0; i < n; i++) temp[i] = arr[i];\
	func(temp, 0, n - 1);\
	if (check(temp, 0, n - 1)){\
        printf("[  OK  ]%s\n", #func);\
    }else {\
        printf("[  FAILED  ]%s\n", #func);\
    }\
}
int check(int *arr, int l, int r){
    for(int i = l + 1; i <= r; i++){
        if (arr[i] < arr[i - 1]) return 0;
    }
    return 1;
}

int * getRandData(int n){
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
    return arr;
}

#endif
```

```c
//quick_sort_test.cpp
#include "test.h"
#include "quick_sort.h"
int main() {
    #define MAX_N 10000000
    int *arr = getRandData(MAX_N);
    TEST(quick_sort_v1, arr, MAX_N);
    #undef MAX_N
    return 0;
}

```

添加彩色文字

添加排序运行时间

```cpp
//test.h
#ifndef _TEST_H
#define _TEST_H

#define TEST(func, arr, n) { \
    int *temp = (int *)malloc(sizeof(int) * n); \
    for (int i = 0; i < n; i++) temp[i] = arr[i]; \
    long long b = clock(); \
    func(temp, 0, n - 1); \
    long long e = clock(); \
    if (check(temp, 0, n - 1)) { \
        printf("\033[1;32m[    OK    ]\033[0m %s ", #func); \
    } else { \
        printf("\033[1;31m[  FAILED  ]\033[0m %s ", #func); \
    } \
    printf("\033[1;33m(%lld ms)\033[0m\n", 1000 * (e - b) / CLOCKS_PER_SEC); \
}

int check(int *arr, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        if (arr[i] < arr[i - 1]) return 0;
    }
    return 1;
}

int *getRandData(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) arr[i] = rand() % n;
    return arr;
}

#endif
```

为什么那么多二三本学生逆序重点学校学生？

大学背景只意味着高考成绩。

就是因为二三本大学学生已经用了三四年时间去还债了！而你重点学校学生却在浪费时间，却在欠债！

### 百度内部评估表告诉你，为什么面试被挂掉

![image-20200820210204729](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200820210204729.png)

![image-20200820210253724](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200820210253724.png)

##### 五种能力

**代码能力**

对语言基础的理解

**数据结构和算法**

对算法和数据结构的理解

**专业知识**

研究生相关方向

**系统知识**

linux系统，网络，操作系统，计算机组成原理

**项目经验**

本科生考核

代码能力，数据结构和算法，系统知识

想象自己是面试官，一个本科生和一个研究生能力相同，你选谁？

本科生能力强，要钱还少，当然要本科生啊。

##### 简历

普通简历：一般的简历

学霸简历：科科高分

竞赛简历：除非是金牌，不然竞赛做经历就好，

项目简历：不一定是真项目，只是用来说明对这个公司感兴趣

一般都是普通型简历和项目型简历。

可以设计几个实验级别的个人项目，针对感兴趣的公司方向。

有个人项目经验不意味能找到工作，只是意味着能找到更对口的工作。

大部分学生能找到工作，只是工作好坏的问题。

### 面试官会问什么？

你跟面试官接触的媒介是什么？就是简历啊。所以要聊简历。

面试官为什么约你面试？因为你简历上面的内容和他们的岗位要求是一致的，所以要面试你，看看你是不是真的满足岗位要求。

你简历写了什么，面试官就会问你什么。

所以我们简历要写真内容，写自己擅长的东西。

你能捉得住的岗位，面试一千次也能进；

你捉不住的岗位，面试一千次也不能进。

简历写假内容，你会吸引一大批捉不住的岗位，浪费大量时间！

简历写真内容，你吸引到的大多数是你可以捉住的岗位。

##### 成为面试中的精算师

很多同学学知识学的不深。

学个快速排序，只学一两个版本，没有深入里面的知识。

一般两场技术面试。

一场面试最长两个小时。

通常半个小时到一个小时。

240分钟，四个小时，你应该怎么说？

如果你一个问题聊1分钟，面试官要问你240个问题。

而如果你一个问题聊天15分钟，你就只需要准备16个问题。

所以我们对问题要深入，这样才能聊的久。

面试的核心逻辑：掌握更多深入理解的问题

### 虚函数

```cpp
//virtual.cpp
class A {
public :
    void say(){
        cout << "this is Class A" << endl;
    }
}
class B : public A {
public :
    void say(){
        cout << "this is Class B" << endl;
    }
}
int main() {
	B b;
    A &a = b;
    A *c = &b;
    b.say();//B
    a.say();//A
    c->say();//A
	return 0;
}
```

普通成员方法是跟着类走的。

b.say();//b是B类型的对象
a.say();//a是A类型的引用
c->say();//c是A类型的指针

```cpp
//virtual.cpp
class A {
public :
    virtual void say(){
        cout << "this is Class A" << endl;
    }
}
class B : public A {
public :
    void say(){
        cout << "this is Class B" << endl;
    }
}
int main() {
	B b;
    A &a = b;
    A *c = &b;
    b.say();//B
    a.say();//B
    c->say();//B
	return 0;
}
```

虚函数是跟着对象走的。

b.say();//b是B类型的对象
a.say();//a是A类型的引用，但它绑定的是B类型的对象
c->say();//c是A类型的指针，但它指向的是B类型的对象

为什么虚函数是跟着对象走的？

对象在内存中的区域

第一个位置是一个指针，会记录一个地址，这个地址会指向虚函数表。

在没有虚函数时，查看A类的大小

sizeof(A)==1，因为没有成员属性，最少占用一个字节。

sizeof(B)==1，一样。

当A有虚函数时，查看类大小。

sizeof(A)==8，64位占用8个字节，说明多了一个指针，记录虚函数表的首地址。

sizeof(B)==8，一样。

```cpp
//virtual.cpp
class A {
public :
    virtual void say(){
        cout << "this is Class A" << endl;
    }
}
class B : public A {
public :
    void say(){
        cout << "this is Class B" << endl;
    }
}
//typedef 为一种数据类型定义一个新名字
typedef void (*T)();//定义了一个指向函数的指针T

int main() {
	B b;
    ((T **)(&b))[0][0]()//相当于b.say()
    cout << "----"<<endl;
    A &a = b;
    A *c = &b;
    b.say();//B
    a.say();//B
    c->say();//B
	return 0;
}
```

用指针从地址里面提取出虚函数。

如果say有参数呢？

```cpp
//virtual.cpp
class A {
public :
    virtual void say(int x){
        cout << "this is Class A" << endl;
    }
}
class B : public A {
public :
    void say(int x){
        cout << this << endl;
        cout << "this is Class B" << x << endl;
    }
}
//typedef 为一种数据类型定义一个新名字
typedef void (*T)(int);//定义了一个指向函数的指针T

int main() {
	B b;
    ((T **)(&b))[0][0](123)//输出一个脏数据。因为this指针变成123了。
    cout << "----"<<endl;
    A &a = b;
    A *c = &b;
    b.say(123);//123
    a.say(123);//123
    c->say(123);//123
	return 0;
}
```

this指针是一个变量，是可以变的。

成员方法其实有一个隐藏的参数就是this指针。

```cpp
//virtual.cpp
class A {
public :
    virtual void say(int x){
        cout << "this is Class A" << endl;
    }
}
class B : public A {
public :
    void say(int x){
        cout << this << endl;
        cout << "this is Class B" << x << endl;
    }
}
//typedef 为一种数据类型定义一个新名字
typedef void (*T)(void *, int);//定义了一个指向函数的指针T

int main() {
	B b;
    ((T **)(&b))[0][0](&b, 123)//123,通过修改this指针
    cout << "----"<<endl;
    A &a = b;
    A *c = &b;
    b.say(123);//123
    a.say(123);//123
    c->say(123);//123
	return 0;
}
```

