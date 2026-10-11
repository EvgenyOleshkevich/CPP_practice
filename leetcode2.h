#pragma once
#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstring>
#include <string>
#include <sstream>
#include <cassert>
#include <tuple>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <algorithm>
#include <random>
#include <numeric>
#include <array>
#include <bitset>
#include "utils.h"
// ||

using namespace std;

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
