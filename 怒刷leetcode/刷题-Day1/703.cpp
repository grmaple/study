/*************************************************************************
	> File Name: 703.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 六  8/29 19:49:54 2020
 ************************************************************************/

class KthLargest {
public:
    typedef pair<int, int> PII;
    set<PII> s;
    int k, t;
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        this->t = 0;
        for (int i = 0; i < nums.size(); i++) {
            this->add(nums[i]);
        }
    }
    
    int add(int val) {
        s.insert(PII(val, t++));
        if (s.size() > k) {
            s.erase(s.begin());
        }
        return s.begin()->first;
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */