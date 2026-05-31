#pragma once
#include <math.h>
#include <ctime>
#include <queue>
#include <unordered_set>
#include <cstring>
#include <numeric>
#include <array>
#include <bitset>
// ||

namespace leetcode {
	// NOT SOLVED
	namespace task_324 {
		/*
		* https://leetcode.com/problems/wiggle-sort-ii/description/
		*/
		class Solution {
		public:
			void wiggleSort__count__sort(vector<int>& nums) {
				size_t size = nums.size();
				if (size < 5000) {
					wiggleSort__sort(nums, size);
					return;
				}
			}

			void wiggleSort__sort(vector<int>& nums, const size_t size) {
				vector<int> sorted(size);
				sort(nums.begin(), nums.end());
				size_t half = (size + 1) / 2;
				for (int i = half - 1, j = 0; i != -1; --i, j += 2)
					sorted[i * 2] = nums[i];

				for (size_t i = half, j = 1; i < size; ++i, j += 2)
					sorted[j] = nums[i];
				swap(sorted, nums);
			}
		};
	}
}
