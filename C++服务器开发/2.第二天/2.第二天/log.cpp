/*************************************************************************
	> File Name: log.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  8/19 19:57:33 2020
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

#ifdef DEBUG

#define log(frm, args...) { \
    printf("[%s : %s : %d] ", __FILE__, __func__, __LINE__); \
    printf(frm,##args); \
    printf("\n");\
}

#else 

#define log(frm, args...) 

#endif

void test() {
    log("hello world");
    int n = 123;
    log("%d", n);
    return ;
}

int main() {
    log("hello world");
    test();
    return 0;
}
