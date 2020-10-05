## day2

### 国王游戏



```cpp
int main() {
	int n;
    cin>>n;
    for (int i = 0; i <= n; i++) {
        cin>>a[i]>>b[i];
        ind[i] = i;
    }
    sort(ind+1, ind+n+1, cmp);
    int ans = 0, p = a[ind[0]];
    for (int i = 1; i <= n; i++) {
        int temp = p / b[ind[i]];
        if (temp > ans) ans = temp;
        p *= a[ind[i]];
    }
    cout<<ans<<endl;
    return 0;
}
```

存放累乘的p，数值很大会超过int类型的最大值。

所以使用大整数BigInt

解决报错，能加深对C++基础的理解。

算法流程不变。然后修改数据结构。

自己创造一个数据类型

需要解决<<，+=，/, >运算符重载。

```cpp
#include<iostream>
using namespace std;

class BigInt:public vector<int> {
public:
    BigInt(vector<int> &)
    BigInt(int x) {
        push_back(x);
        process_digit();
    }
    void operator*=(int x) {
        for (int i = 0; i < size.(); i++) {
        	at(i) *= x;
        }
        process_digit();
        return ;
    }
    BigInt operator/(int x) {
        vector<int> ret(size());
        int y = 0;
        for (int i = size()-1; i >= 0; i--) {
            y = y * 10 + at(i);
            ret[i] = y / x;
            y %= x;
        }
        while (ret.size()>1 && ret[ret.size()-1] == 0) {
            ret.pop_back();
        }
        return ret;
    }
    bool operator>(const BigInt &a) {
        if(size() - a.size()) return size() > a.size();
    }
    
private:
    void proccess_digit() {
        for(int i = 0; i < size(); i++) {
            if (at(i) < 10) continue;
            if (i + 1 == size()) push_back(0);
            at(i+1) += at(i) / 10;
            
        }
    }
};

ostream& 
operator<< (ostream &out, const BigInt &a) {
    for (int i = a.size()-1; i >= 0; i--) {
        out<<a[i];
    }
    return out;
}
int main() {
	int n;
    cin>>n;
    for (int i = 0; i <= n; i++) {
        cin>>a[i]>>b[i];
        ind[i] = i;
    }
    sort(ind+1, ind+n+1, cmp);
    BigInt ans = 0, p = a[ind[0]];
    for (int i = 1; i <= n; i++) {
        BigInt temp = p / b[ind[i]];
        if (temp > ans) ans = temp;
        p *= a[ind[i]];
    }
    cout<<ans<<endl;
    return 0;
}
```

如果是c语言，面向过程的，那么不止要修改数据结构，还要修改算法流程。

STL在C++11之前，有效率问题，所以STL在C++11后大火。

### 无重复字符的最长子串

给定一个字符串，请你找出其中不含有重复字符的 **最长子串** 的长度。

二分算法

二分的到底是什么？

查找范围，问题规模

二分算法在非常规问题时，先解决查找范围(问题规模)

满足下列两个条件一般用二分算法

1.二分算法解决的是求解单调函数f(x)

2.给x容易求f(x)，给f(x)不容易求x时用二分查找

一个有序数组，给数组下标，找值容易；给一个值，找数组下标不容易。所以用二分查找

数组和函数没什么区别。

回到无重复字符的最长子串

s确定，然后f(x)表示在s上是否存在长度为x的无重复子串

对于s=“abcabcbb”

x = 1,f(x) = 1;在s上存在长度为1的无重复子串

x = 2,f(x) = 1;在s上存在长度为2的无重复子串

x = 3,f(x) = 1;在s上存在长度为3的无重复子串

x = 4,f(x) = 0;在s上不存在长度为4的无重复子串

这样看，f(x)是一个单调函数。

并且满足给x容易求f(x)，给f(x)不容易求x

怎么求f(x),就是用一个长度为x的滑动窗口在s上查找是否有无重复子串

所以可以使用二分查找法。

```cpp
int f(string& s, int x) {
    int lcnt[256] = {0}, cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        lcnt[s[i]] += 1;
        if (lcnt[s[i]] == 1) cnt +=1;
        if (i >= x) {
            lcnt[s[i-x]] -= 1;
            if (lcnt[s[i-x]] == 0) cnt -=1;
        }
        if (cnt == x) return 1;
    }
    return 0;
}
int binary_search(string& s, int l, int r) {
    if (l == r) return l;
    int mid = (l+r+1)>>1;
    //1110 0000 f(4) == 0，取前面的1110
    if(f(s, mid) == 0) return binary_search(s, l, mid-1);
    //11 100000 f(2) == 1，取后面的100000
    return binary_search(s, mid, r);
}
int lengthOfLongestSubstring(string s) {
    if (s == "") return 0;
    return binary_search(s, 0, s.size()-1);
}
```

二分算法难的是把什么抽象成f(x)函数。

### 最大平均值

给定一个有N个元素的非负序列，求长度大于等于M的连续子序列的最大平均值。

二分查找，找f(x)

x是平均值，长度大于等于M的连续子序列，能不能大于等于x

x = 1,f(x) = 1;长度大于等于M的连续子序列能大于等于1

x = 2,f(x) = 1;长度大于等于M的连续子序列能大于等于2

x = 3,f(x) = 1;长度大于等于M的连续子序列能大于等于3

x = 4,f(x) = 0;长度大于等于M的连续子序列不能大于等于4

长度大于等于M的连续子序列，能不能大于等于平均值

![image-20200830215314541](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200830215314541.png)

![image-20200830215419080](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200830215419080.png)

![image-20200830215510194](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200830215510194.png)

```cpp

```

