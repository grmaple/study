## day1

![image-20200829193809584](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200829193809584.png)

### 两数之和

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

**刷算法是在刷思维**

杨氏矩阵

![image-20200829194131756](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200829194131756.png)

每一行，每一列都是递增的。

如果要查找x，先从右上角开始查找。当前行最大值，当前列最小值。

时间复杂度O(n+m)

与之对应的，左下角也可以。

回到两数之和

做法一

双指针扫描法

先让数组有序。

 1.start指向开头，end指向结尾
 2.如果和小于sum，说明太小了，start右移寻找更大的数
 3.如果和大于sum，说明太大了，end左移寻找更小的数
 4.和相等，把start和end的数返回

```cpp
class Solution {
public:
    typedef pair<int, int> PII;
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<PII> vec;
        for (int i = 0; i < nums.size(); i++) {
            vec.push_back(PII(nums[i], i));
        }
        sort(vec.begin(), vec.end());
        int p = 0, q = vec.size()-1;
        while (1) {
            int a = vec[p].first;
        	int b = vec[q].second;
            if (a + b == target) break;
            if (a + b < target) ++p;
            else --q;
        }
        int a = vec[p].second;
        int b = vec[q].second;
        if (a > b) swap(a, b);
        vector<int> ret;
        ret.push_back(a);
        ret.push_back(b);
        return ret;
	}
};
```

很多人知道怎么做这道题，却不知道算法思维。

面对一个数组2，5，7，9。生成一个二维数组。

![image-20200829195914728](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200829195914728.png)

这不就变成了杨氏矩阵！

原问题是在一维数组中找两个数相加之和target，

变成在杨氏矩阵中查找target是否存在。

如果和小于target，向下走，对应于一维数组，就是头指针加一；

如果和小于target，向下走，对应于一维数组，就是尾指针减一。

做题的角度：猛抄快。选一个懂的学会就可以了。

比赛的难，还是线下训练的题目难?

线下训练的题目难,因为大部分人都是欠水平发挥。

大部分人都是线下练习一百分的题目，比赛时遇到的却是80分的题目。

线下练习刷题怎么刷?我们要锻炼思维方式，一种题目多种做法。

方法二

```cpp
class Solution {
public:
    typedef pair<int, int> PII;
    static int my_binary_search(vector<PII> &vec, int h, int x) {
        int head = h , tail = vec.size() - 1, mid;
        while (head <= tail) {
            mid = (head + tail) >> 1;
            if (vec[mid].first == x) return vec[mid].second;
            if (vec[mid].first < x) head = mid + 1;
            else tail = mid - 1;
        }
        return -1;
    }
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        vector<PII> vec;
        for (int i = 0; i < nums.size(); i++) {
            vec.push_back(PII(nums[i], i));
        }
        sort(vec.begin(), vec.end());
        for (int i = 0; i < vec.size(); i++) {
			int val = target - vec[i].first;
            int ind1 = vec[i].second;
            int ind2 = my_binary_search(vec, i+1, val);
            if (ind2 == -1) continue;
            if (ind1 > ind2) swap(ind1, ind2);
            ret.push_back(ind1);
            ret.push_back(ind2);
            break;
        }
        return ret;
	}
};
```

在一个有序数组中，查找一个值。这不就是二分查找嘛。

O(nlgn)

方法二

哈希表

问题性质，固定一个值，然后查找另一个值存不存在。如果数列有序，使用二分查找。如果无序/有序，都可以使用哈希表。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        unordered_map<int, int> h;
        for (int i = 0; i < nums.size(); i++) {
            int val = target - nums[i];
            if (h.find(val) == h.end()) {
                h[val[i]] = i;
            } else {
                ret.push_back(h[val]);
                ret.push_back(i);
                break;
            }
        }
        return ret;
	}
};
```

O(n)

### 数据流中的第K大元素

设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。

你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。每次调用 KthLargest.add，返回当前数据流中第K大的元素。



字节跳动面临的真实问题。

解决方案不是今天学的代码，是算法思维。

如何维护集合第k大的问题。

堆？

堆是一种思维逻辑结构。

堆用一个一维数组实现。

看待方式却不一样。我们认为它是树结构。

堆对我们思维的影响：思维升级。

数据结构的什么是重点？

内部实现是最基础的。大家都会。

学习数据结构更加抽象的思维方式。

如果我们把堆看作集合。它支持动态添加，查询最值，删除最值。

```cpp
class KthLargest {
public:
    typedef pair<int, int> PII;
    set<PII> s;
    int k,t;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        this->t = 0;//时间戳，防止set去重,set底层是红黑树
		//维护第k大，小顶堆
        for (int i = 0; i < nums.size(); i++) {
            this->add(nums[i]);
        }
    }
    
    int add(int val) {
        s.insert(PII(val,t++));
		if (s.size() > k) {
            s.erase(s.begin());
        }
        return s.begin()->first;
    }
};
```

### 快乐数

编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。如果 可以变为  1，那么这个数就是快乐数。

如果 n 是快乐数就返回 True ；不是，则返回 False 。

![image-20200829211809578](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200829211809578.png)

NLP

python搭载框架，做快速代码实现，胶水特性

c++做密集型计算，真正实现的语言。

不是说哪门语言好，是需要哪种语言就用哪种语言。



有限次变换？

上限评估法

当前状态确定了，可以唯一映射到下一个状态。

这不就是链表吗?

快乐数有个特殊状态1。

这不就是链表的那个NULL？

什么情况下，链表才不能走到NULL？

有环的情况下。

如果链表有环，说明不是快乐数。

所以题目转变成链表是否有环？

```cpp
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
    bool isHappy(int n){
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
```

数据结构重要的是在思维逻辑上的展示。

```cpp
bool isHappy(int n){      
	int q=getnext(n);
      int p=n;
      while(q!=1&&p!=q){
          p=getnext(slownum);
          q=getnext(getnext(q));
      }
      return fastnum==1;
}

```

### 数据流的中位数

中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：

void addNum(int num) - 从数据流中添加一个整数到数据结构中。
double findMedian() - 返回目前所有元素的中位数。

算法思维

中位数。

先找到中间位置

![image-20200829220024175](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200829220024175.png)

在左边插入两个比中间元素小的元素。

那么中间位置应该向左移动一格。蓝色元素插入到右边集合。

问题性质：支持插入元素，查询最值，删除最值。

——>堆，可以用集合实现。

对顶堆。

```cpp
class MedianFinder {
public:
    /** initialize your data structure here. */
    typedef pair<int, int> PII;
    set<PII> s1, s2;//小顶堆
    int t;
    MedianFinder() {
		t = 0;
    }
    
    void addNum(int num) {
		if (s1.size() == 0 || num <= -(s1.begin()->first)) {
            s1.insert(PII(-num, t++));//取反，变成大顶堆
        } else {
            s2.insert(PII(num, t++));
        }
        //if (s1.size() - 2 == s2.size()) size()是unsigned值，减法变成最大值了。
        if (s1.size() == s2.size() + 2) {
            int val = -(s1.begin()->first);
            s2.insert(PII(val,t++));
            s1.erase(s1.begin());
        }
        if (s2.size() == s1.size() + 2) {
            int val = s2.begin()->first;
            s1.insert(PII(-val,t++));
            s2.erase(s2.begin());
        }
        return ;
    }
    
    double findMedian() {
		double val1 = -(s1.begin()->first);
        double val2 = s2.begin()->first;
        if (s1.size() == s2.size()) return (val1+val2) / 2.0;
        if (s1.size() > s2.size()) return val1;
        else return val2;
    }
};
```

