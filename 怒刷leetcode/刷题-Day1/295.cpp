/*************************************************************************
	> File Name: 295.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 六  8/29 19:49:54 2020
 ************************************************************************/

class MedianFinder {
public:
    /** initialize your data structure here. */
    typedef pair<int, int> PII;
    set<PII> s1, s2;
    int t;
    MedianFinder() {
        t = 0;
    }
    
    void addNum(int num) {
        if (s1.size() == 0 || num <= -(s1.begin()->first)) {
            s1.insert(PII(-num, t++));
        } else {
            s2.insert(PII(num, t++));
        }
        if (s1.size() == s2.size() + 2) {
            int val = -(s1.begin()->first);
            s2.insert(PII(val, t++));
            s1.erase(s1.begin());
        }
        if (s2.size() == s1.size() + 2) {
            int val = s2.begin()->first;
            s1.insert(PII(-val, t++));
            s2.erase(s2.begin());
        }
        return ;
    }
    
    double findMedian() {
        double val1 = -(s1.begin()->first);
        double val2 = s2.begin()->first;
        if (s1.size() == s2.size()) return (val1 + val2) / 2.0;
        if (s1.size() > s2.size()) return val1;
        return val2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
