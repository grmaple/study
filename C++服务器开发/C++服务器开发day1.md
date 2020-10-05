## C++服务器开发day1

### 得C++者，得高薪

数组和函数的关系。

a[3]和f(3)

当你看到[]时，你会下想到数组的知识。

当你看到()时，你会下想到函数的知识。

只是一个符号的区别，就会有两套思维方式，其实是错误的。

数组和函数应该统一思考。

数组是展开的函数

函数是压缩的数组

数组是空间。

函数是时间。

```cpp
//加法的实现方法
//面向过程的编程范式
int add1(int a, int b){
    return a + b;
}
//面向对象的编程范式
struct ADD{
    int operator()(int a, int b){
        return a + b;
    }
};
//泛型编程
template<typename T, typename U>
auto add3(T a, U b) -> decltype(a + b){
    return a + b;
}
//函数式编程
auto add4 = [](int a, int b) -> int { return a + b;};

int main(){
    ADD add2;
    printf("%d/n",add1(3,4));
    printf("%d/n",add2(3,4));
    printf("%d/n",add3(3,4));
    printf("%d/n",add4(3,4));
    return 0;
}
```

c++需要技术性想象

c++很看重基础知识

操作系统，计算机组成原理，计算机网络，数据结构和算法

### 你是这样的盲人工程师么？

c源码-(编译)-目标文件-(链接)-可执行文件

编译：进行语法检查

目标文件：存储定义

链接：把多个目标文件合成一个可执行文件（简单理解）

可执行文件：声明

```c++
int add(int a, int b);//声明
int add(int a, int b){//定义
    return a + b;
}
int main(){
    printf("%d/n",add(3,4));
    return 0;
}
```

函数声明是在调用函数时做语法检查的。只检查传入参数和返回值的类型，作用于编译阶段。

函数定义作用于链接阶段。

只有声明的源程序，可以通过编译，因为没有语法错误。

```cpp
//mian.cpp
int add(int a, int b);//声明
int main(){
    printf("%d/n",add(3,4));
    return 0;
}
```

编译g++  -c main.cpp

源代码和目标文件一一对应。

不去深究的工程师不可能成为一个优秀的工程师

**查看目标文件里面的定义**

nm -C main.o

```cpp
//add.cpp
int add(int a, int b){
    return a + b;
}
```

![image-20200818203212953](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200818203212953.png)

main.o存储着add()的定义。

printf存储在系统库中，自动链接。

链接g++ main.o add.o

nm -C ./a 也可以查看可执行文件里面的定义

![image-20200818203643723](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200818203643723.png)

linux系统下进行编程可以看到编程最本质的现象。

技术学习的第一个门槛：是对错误信息的理解

![image-20200818204442170](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200818204442170.png)

符号未定义。多数发生在链接阶段，应该思考是不是少给了源文件导致缺少了定义。

![image-20200818204604180](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200818204604180.png)

符号冲突。发生在链接阶段，链接的源文件有重复声明。

什么是定义？什么是声明？

定义和声明为什么要分开？

因为头文件存在定义，可能会在链接时出现符号冲突错误。

**所以头文件放声明，源文件放定义。**

### 初始：google测试框架

怎么把第三方的框架引入自己的程序中？

想引入第三方的功能，通过编译。

需要知道第三方的头文件。

链接时目标文件需要查找第三方的源文件(定义部分)，需要静态链接库。

第三方的目标文件，压缩在了一起，生成了一个库文件，就是静态链接库。

链接过程中除了生成可执行文件，还可以生成库文件。

IDE集成开发环境(VScode)

文本编辑器(vim)

编译器(g++)

调试器(gdb/lldb)

IDE相当于一个工具箱，重要的是里面的工具。

googletest 可以在github里面搜索gtest下载

放到1.第一天 文件夹下面

在googletest 文件夹下面新建个build文件夹

进入build文件夹

cmake ../    进行初始化

make

![image-20200818212412453](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200818212412453.png)

生成四个静态链接库，里面存放着google测试框架的定义。存于lib文件夹。

进入googletest/build

cp -R lib ../../   复制到1.第一天 文件夹

找到了定义，还差声明。

进入googletest/googletest 

cp -R include ../../ 复制到1.第一天 文件夹

```cpp
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
    printf("add（3，4） = %d\n"，add(3,4));
    printf("hello\n");
    return RUN_ALL_TESTS();
}
```

![image-20200818213306512](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200818213306512.png)

出错在预处理阶段，找不到头文件

g++ -I./include test.cpp

编译程序按照-I指定的路进去搜索头文件。

告诉我们这个头文件在include文件夹里面。

但是找不到第三方的定义

g++ -I./include -L./lib  test.cpp -lgtest

ubuntu中可能通过不了，需要加 -lpthread

编译程序按照－L指定的路进去寻找库文件

-L./lib告诉我们定义在lib文件夹里面

-lgtest告诉我们链接的时候找到libtest.a文件

很多技术是华而不实的技术，只是因为我们没接触过，只要接触了就很容易学会了。

真正厉害的技术是接触了还是很难学会的。

![image-20200818214509070](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200818214509070.png)

思考是先有RUN_ALL_TESTS()还是先有测试用例？

先有RUN_ALL_TESTS()，这是谷歌开发出来的。

问题是它是怎么知道我们有多少测试用例的？未卜先知?

