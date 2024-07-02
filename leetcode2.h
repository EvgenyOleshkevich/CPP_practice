#pragma once
#include <math.h>
#include <ctime>
#include <queue>
#include <unordered_set>
#include <cstring>

namespace leetcode {

    namespace task_2248__ {
        /*
        * https://leetcode.com/problems/intersection-of-multiple-arrays/description/
        */
        class Solution {
        public:
            vector<int> intersect(vector<vector<int>>& nums) {
                for (vector<int>& num : nums)
                    sort(num.begin(), num.end());
                vector<int> intersection;
                return intersection;
            }
        };
    }

}