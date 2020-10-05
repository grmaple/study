/*************************************************************************
	> File Name: array.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 二  8/18 19:43:57 2020
 ************************************************************************/

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
using namespace std;

// 面向过程的编程范式
int add1(int a, int b) {
    return a + b;
}

// 面向对象的编程范式
struct ADD {
    int operator()(int a, int b) {
        return a + b;
    }
};

// 泛型编程
template<typename T, typename U>
auto add3(T a, U b) -> decltype(a + b) {
    return a + b;
}

// 函数式编程
auto add4 = [](int a, int b) -> int { return a + b; };

int main() {
    ADD add2;
    cout << add1(3, 4) << endl;
    cout << add2(3, 4) << endl;
    cout << add3(3, 4) << endl;
    cout << add4(3, 4) << endl;
    return 0;
}
