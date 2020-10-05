/*************************************************************************
	> File Name: 1.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 六  8/29 19:49:54 2020
 ************************************************************************/
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    typedef pair<int, int> PII;
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        unordered_map<int, int> h;
        for (int i = 0; i < nums.size(); i++) {
            int val = target - nums[i];
            if (h.find(val) == h.end()) {
                h[val] = i;
            } else {
                ret.push_back(h[val]);
                ret.push_back(i);
                break;
            }
        }
        return ret;
    }
};
