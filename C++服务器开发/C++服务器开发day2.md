## C++服务器开发day2

### printf的有趣用法，输出彩色文字

配置信息

\033[ A1;A2;A3;...An m

A1;A2;A3;...An 属性代码

<img src="C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819193905646.png" alt="image-20200819193905646" style="zoom: 50%;" />

<img src="C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819193913696.png" alt="image-20200819193913696" style="zoom:50%;" />

<img src="C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819194114841.png" alt="image-20200819194114841" style="zoom:50%;" />

通用格式控制，前景色(字体)，背景色

比如高亮加粗的黄色字体，红色背景

```c
//test.cpp
#include <gtest/gtest.h>
int add(int a, int b){
    return a + b;
}
TEST(test, add1){//测试用例命名。test.add1
    EXPECT_EQ(add(3,4),7);//相等
    EXPECT_NE(add(3,4),6);//不等
    EXPECT_LT(add(3,4),8);//小于
    EXPECT_LE(add(3,4),7);//小于等于
    EXPECT_GT(add(3,4),6);//大于
    EXPECT_GE(add(3,4),7);//大于等于
}
TEST(test, add2){//test.add2
    EXPECT_EQ(add(3,4),7);//相等
    EXPECT_NE(add(3,4),7);//不等,出错
    EXPECT_LT(add(3,4),8);//小于
    EXPECT_LE(add(3,4),7);//小于等于
    EXPECT_GT(add(3,4),6);//大于
    EXPECT_GE(add(3,4),7);//大于等于
}
int main(){
    printf("\033[1;33;41madd(3,4)=%d\n"，add(3,4));
    printf("hello world\n");
    return RUN_ALL_TESTS();
}
```

![image-20200819194515134](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819194515134.png)

不仅第一行变色，第二行也变色了。

底层信息和显示信息的关系

终端也是一个程序，用来显示底层信息

自己写的配置信息，一直到helloworld才停止。

编程语言只是一个载体，它是承载我们思想的工具。

我们选择的是某一技术方向，而不是某一门语言。

所有方向的基础都是共通的。

```c
//修改成只有等一行变色,添加\033[0m
int main(){
    printf("\033[1;33;41madd(3,4)=%d\n\033[0m"，add(3,4));
    printf("hello world\n");
    return RUN_ALL_TESTS();
}
```

![image-20200819195327778](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819195327778.png)

### 调试信息log日志

调试信息在哪里输出?不知道的话，怎么调试bug。

预处理命令(以#开头)

##### 宏定义

定义符号常量：

#define PI 3.1415926

定义傻瓜表达式:

#define MAX(a, b) (a) > (b) ? (a) : (b)

定义代码段：

#define P(a){\

​	printf("%d\n", a);\

}

**宏做的事情就是做基础的替换**

```c
//main.cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define PI 3.1415926
int main(){
    printf("%lf\n", 2 * PI);
    return 0;
}
```

不做盲人工程师。深入底层理解什么宏就是做替换。

c源码-(预处理)-待编译源码-(编译)-对象文件-(链接)-可执行程序

预处理阶段：把预处理命令给处理掉，比如宏定义的替换这时候就替换掉了。

可执行程序最终功能是什么样子的取决于待编译源码

我们应该站在待编译源码的角度来看可执行程序的功能。

仅执行预处理 g++ -E main.cpp \> output.cpp

![image-20200819201128563](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819201128563.png)

#include<iostream>作用就是把iostream库的内容加进main.cpp文件

#define PI 3.1415926作用就是把PI替换成3.1415926

```c
//宏就是做替换，站在待编译源码的角度来看可执行程序的功能
#define S(a, b) a * b
int main(){
    int n;
    S(int, p) = &n;//int * p = &n;
    return 0;
}
```

c语言连操作系统都能开发出来，怎么可能弱！

编译器要求 宏定义是一行代码。

定义代码段的时候是多行代码，但是编译器看到的是一行代码。

```c
#define P(a){\
	printf("%d\n", a);\
}
```

每一行后面都加个\，告诉编译器，上下两行是同一行。

##### 编译器内置宏（预定义的宏）

![image-20200819203113117](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819203113117.png)

替换的时候是在预处理阶段，所以日期是预处理阶段的日期，而不是执行时的日期

```c
int main(){
    printf("__DATE__ = %s\n", __DATE__);
    return 0;
}
```

log日志

```c
#define log(msg){\
	printf("[%s : %s : %d]\n", __FILE__,__FUNC__, __LINE__);\
}
boid test(){
    log("hello world\n");
    return ;
}
int main(){
    printf("__DATE__ = %s\n", __DATE__);
    log("hello world\n");
    test();
    return 0;
}
```

![image-20200819204701798](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819204701798.png)

使用变参列表，可以把多个参数传入log。

log相当于一个新的printf函数，但是有更多调试信息。

##### 条件式编译

![image-20200819204942039](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819204942039.png)

条件式编译本质作用是做代码剪裁，选择留下哪段代码。

#ifdef 

第三项，一般判断软件版本。

条件式编译一定以#endif结束

![image-20200819205336214](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200819205336214.png)

如果定义了DEBUG宏，就定义log宏定义，否则log宏定义为空。

定义DEBUG宏。

log.cpp里面添加 #define DEBUG

或者g++ -DDEBUG log.cpp

### 自己实现个测试框架mytest.h

```cpp
//test.cpp
#include <mytest.h>//<gtest/gtest.h>
int add(int a, int b){
    return a + b;
}
TEST(test, add1){//测试用例命名。test.add1
    EXPECT_EQ(add(3,4),7);//相等
    EXPECT_NE(add(3,4),6);//不等
    EXPECT_LT(add(3,4),8);//小于
    EXPECT_LE(add(3,4),7);//小于等于
    EXPECT_GT(add(3,4),6);//大于
    EXPECT_GE(add(3,4),7);//大于等于
}
TEST(test, add2){//test.add2
    EXPECT_EQ(add(3,4),7);//相等
    EXPECT_NE(add(3,4),7);//不等,出错
    EXPECT_LT(add(3,4),8);//小于
    EXPECT_LE(add(3,4),7);//小于等于
    EXPECT_GT(add(3,4),6);//大于
    EXPECT_GE(add(3,4),7);//大于等于
}
int main(){
    printf("add（3，4） = %d\n"，add(3,4));
    printf("hello\n");
    return RUN_ALL_TESTS();
}
```

```Cpp
//mytest.h
#ifndef _MYTEST_H
#define _MYTEST_H
//红色字体
#define COLOR(msg, code) "\033[" #code "m" msg "\033[0m"
#define RED(msg) COLOR(msg, "1;31;40")

//先实现EXPECT_EQ功能，应该是宏封装的
/*
#define EXPECT_EQ(a,b) {\
	if (!((a) == (b)) {\
        printf("error\n");\
    }\
}
#define EXPECT_NE(a,b){\
	if (!((a) != (b)) {\
        printf("error\n");\
    }\
}
*/
//程序结构相似，大量结构重复，所以应该进行封装，要么用宏，要么用函数封装
#define EXPECT(a, comp,b) {\
	if (!((a) comp (b)) {\
        printf("error\n");\
    }\
}
#define EXPECT_EQ(a,b) EXPECT(a, ==, b)
#define EXPECT_NE(a,b) EXPECT(a, !=, b)
#define EXPECT_LT(a,b) EXPECT(a, <, b)
#define EXPECT_LE(a,b) EXPECT(a, <=, b)
#define EXPECT_GT(a,b) EXPECT(a, >, b)
#define EXPECT_GE(a,b) EXPECT(a, >=, b)

//TEST(test, add1)大概率是一个宏，应该变成一个函数头部信息。
//用技术想象力来思考，从待编译源码角度来看

#define TEST(a, b)\ 
void a##_##b()；\
__attribute__((constructor))\//在main函数之前运行
void reg_##a##_##b(){\
    add_test_func(a##_##b, #a "." #b);\
    return ;\
}\
void a##_##b()

//RUN_ALL_TESTS函数的实现
//遍历每一个测试用例函数
//依次每一个测试用例函数
struct {
    void (*func)();//函数指针，就是存储函数地址的指针
    const char *func_name;
}func_arr[100];//存储区，使用链表，可以有更大空间
int func_cnt = 0;//有多少测试用例
//注册函数
void add_test_func(void (*func)(), const char *name){
    func_arr[func_cnt].func = func;
    func_arr[func_cnt].func_name = name;
    func_cnt +=1;
    return ;
}

int RUN_ALL_TESTS(){
    for (int i = 0; i < func_cnt; i++){
        func_arr[i].func();
    }
    return 0;
}
//存储区中没有内容，需要把内容写进去--注册函数

#endif
```

优秀的工程师不应该用代码行的多少来决定。

更少的代码，意味着可维护性的提升，bug的减少

事情是做了才能实现，才有希望。而不是有希望，能实现的事情才去做。

海贼精神是不畏牺牲的精神。





\#是“字符串化”的意思。出现在宏定义中的#是把跟在后面的参数转换成一个字符串

\## 简单的说，“##”是一种分隔连接方式，它的作用是先分隔，然后进行强制连接。

1. \#define Conn(x,y) x##y
2. \#define ToChar(x) #@x
3. \#define ToString(x) #x

int n = Conn(123,456); // 结果就是n=123456;

char a = ToChar(1);// 结果就是a='1';结果返回是一个const char

char* str = ToString(123132);//就成了str="123132";