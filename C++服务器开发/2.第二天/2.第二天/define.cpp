/*************************************************************************
	> File Name: define.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  8/19 20:03:01 2020
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

#define PI 3.1415926
#define S(a, b) a * b

int main() {
    printf("%lf\n", 2 * PI);
    printf("S(3, 4) = %d\n", S(3, 4));
    printf("S(3 + 6, 4) = %d\n", S(3 + 6, 4));
    int n;
    S(int, p) = &n;
    printf("__DATE__ = %s\n", __DATE__);
    printf("__TIME__ = %s\n", __TIME__);
    printf("__LINE__ = %d\n", 
           __LINE__);
    printf("__FILE__ = %s\n", __FILE__);
    return 0;
}
