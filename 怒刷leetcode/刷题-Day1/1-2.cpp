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
    static int my_binary_search(vector<PII> &vec, int h, int x) {
        int head = h, tail = vec.size() - 1, mid;
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
            int val = target - vec[i].first, ind1 = vec[i].second;
            int ind2 = my_binary_search(vec, i + 1, val);
            if (ind2 == -1)  continue;
            if (ind1 > ind2) swap(ind1, ind2);
            ret.push_back(ind1);
            ret.push_back(ind2);
            break;
        }
        return ret;
    }
};
