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

	namespace task_396 {
		/*
		* https://leetcode.com/problems/rotate-function/description/
		*/
		class Solution {
		public:
			int maxRotateFunction(vector<int>& nums) {
				const int size = nums.size();
				int sum = 0, f = 0;
				for (int i = 0; i < size; ++i) {
					sum += nums[i];
					f += nums[i] * i;
				}

				int max_f = f;
				for (int i = 1; i < size; ++i) {
					f += sum - size * nums[size - i];
					max_f = max(max_f, f);
				}
				return max_f;
			}
		};
	}

	namespace task_788 {
		/*
		* https://leetcode.com/problems/rotated-digits/description/description/
		*/
		class Solution {
		public:
			int allowed [10] { 1,1,1,0,0,1,1,0,1,1 };
			int symmetric [10] { 1,1,0,0,0,0,0,0,1,0 };

			int rotatedDigits(int n) {
				int count = 0;
				for (int i = 2; i <= n; i++) {
					if (isValid(i))
						++count;
				}
				return count;
			}

			bool isValid(int n) {
				bool has_no_symmetric = false;
				while (n > 0) {
					int d = n % 10;
					if (allowed[d] == 0)
						return false;
					has_no_symmetric |= symmetric[d] == 0;
					n /= 10;
				}
				return has_no_symmetric;
			}

			int getCount(int len) {
				int count = 1;
				while (len != 0) {
					count *= 7;
					--len;
				}
				count;
			}

			int getCountSymmetric(int len) {
				int count = 1;
				while (len != 0) {
					count *= 3;
					--len;
				}
				return count;
			}
		};
	}

	namespace task_1665 {
		/*
		* https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/description/
		*/
		class Solution {
		public:
			int minimumEffort(vector<vector<int>>& tasks) {
				for (vector<int>& task : tasks) {
					task.push_back(task.back());
					task[1] = task[0];
					task[0] = task[2] - task[1];
				}
				sort(tasks.begin(), tasks.end(), greater<vector<int>>());
				int spent = 0, max_energy = 0;
				for (const vector<int>& task : tasks) {
					max_energy = max(max_energy, spent + task[2]);
					spent += task[1];
				}
				return max_energy;
			}
		};
	}

	namespace task_1674 {
		/*
		* https://leetcode.com/problems/minimum-moves-to-make-array-complementary/description/
		*/
		class Solution {
		public:
			int minMoves__leetcode(vector<int>& nums, int limit) {
				int n = nums.size();
				unordered_map<int, int> sum_count;
				vector<int> min_arr, max_arr;
				min_arr.reserve(n / 2);
				max_arr.reserve(n / 2);

				for (int i = 0; i < n / 2; ++i) {
					int a = std::min(nums[i], nums[n - 1 - i]);
					int b = std::max(nums[i], nums[n - 1 - i]);

					sum_count[a + b]++;
					min_arr.push_back(a);
					max_arr.push_back(b);
				}

				std::sort(min_arr.begin(), min_arr.end());
				std::sort(max_arr.begin(), max_arr.end());

				int min_ops = n;

				for (int c = 2; c <= 2 * limit; ++c) {
					int add_left =
						n / 2 - (lower_bound(min_arr.begin(), min_arr.end(), c) -
							min_arr.begin());
					int add_right =
						lower_bound(max_arr.begin(), max_arr.end(), c - limit) -
						max_arr.begin();

					int current_ops = n / 2 + add_left + add_right - sum_count[c];
					min_ops = min(min_ops, current_ops);
				}

				return min_ops;
			}
		};
	}

	namespace task_1914 {
		/*
		* https://leetcode.com/problems/cyclically-rotating-a-grid/description/
		*/
		class Solution {
		public:
			vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
				int x1 = 0, y1 = 0;
				int x2 = grid.size() - 1, y2 = grid[0].size() -1;
				while (x2 > x1 && y2 > y1) {
					auto arr = crateCyclicallyArray(grid, x1, y1, x2, y2);
					fillByCyclicallyArray(grid, arr, k, x1, y1, x2, y2);
					++x1, ++y1, --x2, --y2;
				}

				return grid;
			}

			vector<int> crateCyclicallyArray(const vector<vector<int>>& grid,
				const int x1, const int y1, const int x2, const int y2) {
				int size = (x2 - x1 + y2 - y1) * 2;
				vector<int> arr(size);
				int i = 0;
				for (int j = x1; j < x2; ++j)
					arr[i++] = grid[j][y1];
				for (int j = y1; j < y2; ++j)
					arr[i++] = grid[x2][j];
				for (int j = x2; j > x1; --j)
					arr[i++] = grid[j][y2];
				for (int j = y2; j > y1; --j)
					arr[i++] = grid[x1][j];

				return arr;
			}

			void fillByCyclicallyArray(vector<vector<int>>& grid,
				const vector<int>& arr, int k,
				const int x1, const int y1, const int x2, const int y2) {
				const int size = arr.size();
				k %= size;
				if (k == 0)
					return;
				int i = 0;
				for (int j = x1; j < x2; ++j)
					grid[j][y1] = arr[(i++ + size - k) % size];
				for (int j = y1; j < y2; ++j)
					grid[x2][j] = arr[(i++ + size - k) % size];
				for (int j = x2; j > x1; --j)
					grid[j][y2] = arr[(i++ + size - k) % size];
				for (int j = y2; j > y1; --j)
					grid[x1][j] = arr[(i++ + size - k) % size];
			}
		};
	}

	namespace task_2553 {
		/*
		* https://leetcode.com/problems/separate-the-digits-in-an-array/description/
		*/
		class Solution {
		public:
			vector<int> separateDigits(vector<int>& nums) {
				vector<int> answer;
				stack<int> stack;

				for (int n : nums) {
					while (n != 0) {
						stack.push(n % 10);
						n /= 10;
					}
					while (!stack.empty()) {
						answer.push_back(stack.top());
						stack.pop();
					}
				}

				return answer;
			}
		};
	}

	namespace task_2770 {
		/*
		* https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/description/
		*/
		class Solution {
		public:
			int maximumJumps(vector<int>& nums, int target) {
				const int size = nums.size();
				vector<int> dp(size, -1);
				dp[0] = 0;

				for (int i = 1; i < size; ++i) {
					int min_dp = -1;
					for (int j = 0; j < i; ++j) {
						if (abs(nums[i] - nums[j]) <= target)
							min_dp = max(min_dp, dp[j]);
					}
					if (min_dp != -1)
						dp[i] = min_dp + 1;
				}

				return dp[size - 1];
			}
		};
	}

	namespace task_2784 {
		/*
		* https://leetcode.com/problems/check-if-array-is-good/description/
		*/
		class Solution {
		public:
			bool isGood(vector<int>& nums) {
				sort(nums.begin(), nums.end());
				int n = nums.size() - 1;
				for (int i = 0; i < n; ++i) {
					if (nums[i] != i + 1)
						return false;
				}
				return nums[n] == n;
			}
		};
	}

	namespace task_3629 {
		/*
		* https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/description/
		*/
		class Solution {
		public:
			vector<int> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293 };
			int count_primes;
			unordered_map<int, vector<int>> prime_teleport;

			int minJumps(vector<int>& nums) {
				const int size = nums.size();
				if (size == 1)
					return 0;
				int max_num = 0;
				for (const int n : nums)
					max_num = max(max_num, n);
				getPrimes(max_num);
				getMapping(nums);

				queue<int> queue;
				queue.push(0);
				vector<int> visited(size);
				visited[0] = 1;
				int count = 0;
				while (!queue.empty()) {
					int size_q = queue.size();
					++count;
					for (int j = 0; j < size_q; ++j) {
						auto n = queue.front();
						queue.pop();
						if (n + 2 == size)
							return count;
						
						if (n > 0 && visited[n - 1] == 0) {
							visited[n - 1] = 1;
							queue.push(n - 1);
						}

						if (visited[n + 1] == 0) {
							visited[n + 1] = 1;
							queue.push(n + 1);
						}
						
						if (auto it = prime_teleport.find(nums[n]); it != prime_teleport.end()) {
							const auto teleports = it->second;
							for (const int dest : teleports) {
								if (dest + 1 == size)
									return count;
								if (visited[dest] == 0) {
									visited[dest] = 1;
									queue.push(dest);
								}
							}
						}
					}
				}

				return size - 1;
			}

			void getPrimes(int to) {
				++to;
				for (int n = 294; n < to; ++n) {
					bool isPrime = true;
					for (const int p : primes) {
						if (n % p == 0) {
							isPrime = false;
							break;
						}
						if (p * p > n) {
							break;
						}
					}
					if (isPrime)
						primes.push_back(n);
					count_primes = primes.size();
				}
			}

			void getMapping(const vector<int>& nums) {
				const int size = nums.size();
				for (int i = 0; i < size; i++) {
					vector<int> factors;
					int n = nums[i];
					for (const int p : primes) {
						if (n % p == 0) {
							factors.push_back(p);
							while (n % p == 0)
								n /= p;
						}
						if (n == 1) {
							break;
						}
					}

					if (!factors.empty()) {
						for (const int p : factors)
							prime_teleport[p].push_back(i);
					}
				}
			}
		};

		const int MX = 1000001;
		vector<int> factors[MX];
		bool initialized = []() {
			for (int i = 2; i < MX; ++i) {
				if (factors[i].empty()) {
					for (int j = i; j < MX; j += i) {
						factors[j].push_back(i);
					}
				}
			}
			return true;
		}();

		class Solution__leetcode {
		public:
			int minJumps(vector<int>& nums) {
				int n = nums.size();
				unordered_map<int, vector<int>> edges;
				for (int i = 0; i < n; ++i) {
					for (int p : factors[nums[i]]) {
						edges[p].push_back(i);
					}
				}
				int res = 0;
				vector<bool> seen(n, false);
				seen[0] = true;
				vector<int> q = { 0 };
				while (true) {
					vector<int> q2;
					for (int i : q) {
						if (i == n - 1) return res;
						if (i > 0 && !seen[i - 1]) {
							seen[i - 1] = true;
							q2.push_back(i - 1);
						}
						if (i < n - 1 && !seen[i + 1]) {
							seen[i + 1] = true;
							q2.push_back(i + 1);
						}
						if (factors[nums[i]].size() == 1) {
							int p = nums[i];
							if (edges.count(p)) {
								for (int j : edges[p]) {
									if (!seen[j]) {
										seen[j] = true;
										q2.push_back(j);
									}
								}
								edges[p].clear();
							}
						}
					}
					q = move(q2);
					res++;
				}
			}
		};
	}

	namespace task_3660 {
		/*
		* https://leetcode.com/problems/jump-game-ix/description/
		*/
		class Solution {
		public:
			struct Item {
				int value;
				int left;
				int right;
			};

			vector<int> maxValue__leetcode(const vector<int>& nums) {
				int n = nums.size();
				vector<int> ans(n, 0);

				vector<Item> stack;

				for (int i = 0; i < n; ++i) {
					Item curr = { nums[i], i, i };

					while (!stack.empty() && stack.back().value > nums[i]) {
						Item top = stack.back();
						stack.pop_back();
						curr.value = max(curr.value, top.value);
						curr.left = top.left;
					}

					stack.push_back(curr);
				}

				for (size_t i = 0; i < stack.size(); ++i) {
					for (int j = stack[i].left; j <= stack[i].right; ++j) {
						ans[j] = stack[i].value;
					}
				}

				return ans;
			}

			vector<int> maxValue(vector<int>& nums) {
				const int size = nums.size();
				vector<int> answer(size);
				int max_left = 0;
				for (int i = 0; i < size; ++i) {
					max_left = max(max_left, nums[i]);
					answer[i] = max_left;
				}


				map<int, int, greater<int>> less_from_right_ans;
				for (int i = size - 1; i >= 0; --i) {
					if (auto it = less_from_right_ans.upper_bound(nums[i]);
						it != less_from_right_ans.end()) {
						answer[i] = it->second;
					}
					if (!less_from_right_ans.contains(nums[i])) {
						less_from_right_ans[nums[i]] = answer[i];
					}
				}
				return answer;
			}
		};
	}
}
