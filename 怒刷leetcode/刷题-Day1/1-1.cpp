/*************************************************************************
	> File Name: 1.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 六  8/29 19:49:54 2020
 ************************************************************************/
#include <vector>
using namespace std;

class Solution {
public:
    typedef pair<int, int> PII;
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<PII> vec;
        for (int i = 0; i < nums.size(); i++) {
            vec.push_back(PII(nums[i], i));
        }
        sort(vec.begin(), vec.end());
        int p = 0, q = vec.size() - 1;
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
