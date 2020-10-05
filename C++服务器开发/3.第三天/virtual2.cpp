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
#include<typeinfo>

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
        cout << "this is Class B : " << x << endl;
    }
};

typedef void (*T)(void *, int);

int main() {
    B b;
	cout << &b <<endl;
	//cout << sizeid(&b).name() <<endl;
	cout << (T **)(&b) <<endl;
	//cout << sizeid((T **)(&b)).name() <<endl;
	cout << ((T **)(&b))[0] <<endl;
	//cout << sizeid(((T **)(&b))[0]).name() <<endl;
	cout << ((T **)(&b))[0] <<endl;
	cout << ((T **)(&b))[0][0] <<endl;

    ((T **)(&b))[0][0](&b, 123);

    return 0;
}
