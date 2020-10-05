/*************************************************************************
	> File Name: virtual.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 四  8/20 22:15:22 2020
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

class A {
public :
    virtual void say(int x) {
        cout << "this is Class A" << endl;
    }
};

class B : public A {
public :
    void say(int x) {
        cout << this << endl;
        cout << "this is Class B : " << x << endl;
    }
};

typedef void (*T)(void *, int);

int main() {
    cout << sizeof(A) << endl;   
    cout << sizeof(B) << endl;   
    B b;
    ((T **)(&b))[0][0](&b, 123);
    cout << "============" << endl;
    A &a = b;
    A *c = &b;
    b.say(123);
    a.say(123);
    c->say(123);
    return 0;
}
