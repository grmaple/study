/*************************************************************************
	> File Name: 202.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 六  8/29 19:49:54 2020
 ************************************************************************/

class Solution {
public:
    int getNext(int x) {
        int y = 0, z;
        while (x) {
            z = x % 10;
            y += z * z;
            x /= 10;
        }
        return y;
    }
    bool isHappy(int n) {
        if (n == 1) return true;
        int p = n;
        int q = getNext(n);
        while (p - q) {
            if (q == 1) return true;
            p = getNext(p);
            q = getNext(getNext(q));
        }
        return false;
    }
};
