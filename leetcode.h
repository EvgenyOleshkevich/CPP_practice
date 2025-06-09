#pragma once

#include <iostream>
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
using namespace std;

namespace leetcode {
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};

	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};

	struct Node {
		int val;
		Node* left;
		Node* right;
		Node* next;

		Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
		Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
		Node(int x, Node* left, Node* right, Node* next) : val(x), left(left), right(right), next(next) {}
	};

	class NodeNTree {
	public:
		int val;
		vector<NodeNTree*> children;

		NodeNTree() {}

		NodeNTree(int _val) {
			val = _val;
		}

		NodeNTree(int _val, vector<NodeNTree*> _children) {
			val = _val;
			children = _children;
		}
	};

	struct NodeRandom {
		int val;
		NodeRandom* next;
		NodeRandom* random;

		NodeRandom() : val(0), next(nullptr), random(nullptr) {}
		NodeRandom(int x) : val(x), next(nullptr), random(nullptr) {}
	};

	namespace utils {
		ListNode* vector2list(const vector<int>& v) {
			auto head = new ListNode();
			auto ptr = head;
			for (const int val : v) {
				ptr->next = new ListNode(val);
				ptr = ptr->next;
			}
			ptr = head->next;
			delete head;
			return ptr;
		}

		vector<int> list2vector(ListNode* head) {
			vector<int> vec;
			while (head) {
				vec.push_back(head->val);
				head = head->next;
			}
			return vec;
		}

		template <class T>
		ostream& operator<<(ostream& os, const vector<T>& v) {
			for (const T& val : v)
				os << val << " ";
			os << endl;
			return os;
		}

		ostream& operator<<(ostream& os, const vector<string>& v) {
			for (const string& val : v)
				os << val << endl;
			return os;
		}

		ostream& operator<<(ostream& os, ListNode* head) {
			while (head) {
				os << head->val << " ";
				head = head->next;
			}
			os << endl;
			return os;
		}
	}

	namespace task_1 {
		/*
		* https://leetcode.com/problems/two-sum/
		*/
		class Solution {
		public:
			vector<int> twoSum(vector<int>& nums, int target) {
				for (size_t i = 0; i < nums.size(); i++)
					for (size_t j = i + 1; j < nums.size(); j++)
						if (nums[i] + nums[j] == target)
							return { (int)i, (int)j };
				return { 0, 0 };
			}
		};
	}

	namespace task_2 {
		/*
		* https://leetcode.com/problems/add-two-numbers/
		*/
		class Solution {
		public:
			ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
				auto head = new ListNode(l1->val);
				l1 = l1->next;
				auto current = head;
				while (l1) {
					current->next = new ListNode(l1->val);
					current = current->next;
					l1 = l1->next;
				}
				current = head;
				current->val += +l2->val;
				l2 = l2->next;
				int add_one = current->val / 10;
				current->val %= 10;
				while (l2 || add_one) {
					if (l2) {
						add_one += l2->val;
						l2 = l2->next;
					}
					if (!current->next)
						current->next = new ListNode(0);
					current = current->next;
					current->val += add_one;
					add_one = current->val / 10;
					current->val %= 10;
				}
				return head;
			}
		};
	}

	namespace task_3 {
		/*
		* https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/
		*/
		class Solution {
		public:
			int lengthOfLongestSubstring(string s) {
				vector<int> set(256, -1);
				int max_size = 0;
				size_t start = 0;
				for (size_t i = 0; i < s.size(); i++) {
					if (set[s[i]] >= 0) {
						int size = i - start;
						if (max_size < size)
							max_size = size;
						auto index = set[s[i]];
						for (size_t j = start; j < index; j++)
							set[s[j]] = -1;
						start = index + 1;
					}
					set[s[i]] = i;
				}
				int size = s.size() - start;
				if (max_size < size)
					max_size = size;
				return max_size;
			}
		};
	}

	namespace task_4 {
		/*
		* https://leetcode.com/problems/median-of-two-sorted-arrays/
		*/
		class Solution {
		public:
			double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
				const size_t size1 = nums1.size();
				const size_t size2 = nums2.size();
				bool odd = (size1 + size2) & 1;
				size_t i1 = size1 >> 1;
				size_t i2 = size2 >> 1;
				if (size1 == 0)
					return odd ? nums2[i2] : (nums2[i2] + nums2[i2 - 1]) / 2.0;
				if (size2 == 0)
					return odd ? nums1[i1] : (nums1[i1] + nums1[i1 - 1]) / 2.0;

				size_t l1 = 0;
				size_t r1 = size1;
				size_t l2 = 0;
				size_t r2 = size2;
				size_t target = (size2 + size1) >> 1;

				while (true) {
					i1 = (r1 + l1) >> 1;
					i2 = (r2 + l2) >> 1;
					size_t sum_i = i1 + i2 + 1;
					bool first_less = nums1[i1] <= nums2[i2];
					if (sum_i > target) {
						if (first_less && l2 != i2 || l1 == i1)
							r2 = i2;
						else
							r1 = i1;
						continue;
					}
					else if (sum_i < target) {
						if (first_less && l1 != i1 || l2 == i2)
							l1 = i1;
						else
							l2 = i2;
						continue;
					}
					else {
						if (first_less) {
							if (i1 + 1 < r1 && nums1[i1 + 1] < nums2[i2]) {
								l1 = i1;
								continue;
							}
						}
						else {
							if (i2 + 1 < r2 && nums1[i1] > nums2[i2 + 1]) {
								l2 = i2;
								continue;
							}
						}
					}
					break;
				}

				if (odd) {
					if (nums1[i1] < nums2[i2]) {
						int next1 = INT_MAX;
						if (i1 + 1 < size1)
							next1 = nums1[i1 + 1];
						return min(next1, nums2[i2]);
					}
					else {
						int next2 = INT_MAX;
						if (i2 + 1 < size2)
							next2 = nums2[i2 + 1];
						return min(nums1[i1], next2);
					}
				}
				else {
					if (nums1[i1] < nums2[i2]) {
						int val1 = INT_MIN;
						if (i2 > l2)
							val1 = nums2[i2 - 1];
						val1 = max(nums1[i1], val1);

						int val2 = INT_MAX;
						if (i1 + 1 < size1)
							val2 = nums1[i1 + 1];
						val2 = min(nums2[i2], val2);
						return (val1 + val2) / 2.0;
					}
					else {
						int val1 = INT_MIN;
						if (i1 > l1)
							val1 = nums1[i1 - 1];
						val1 = max(nums2[i2], val1);

						int val2 = INT_MAX;
						if (i2 + 1 < size2)
							val2 = nums2[i2 + 1];
						val2 = min(nums1[i1], val2);
						return (val1 + val2) / 2.0;
					}
				}
			}
		};
	}

	namespace task_5 {
		/*
		* https://leetcode.com/problems/longest-palindromic-substring/description/
		*/
		class Solution {
		public:
			string longestPalindrome(string s) {
				size_t max_size = 1;
				size_t max_left = 0;
				size_t max_right = 0;
				size_t length = s.size() * 2 - 1;

				for (size_t i = 0; i < length; i++) {
					int index = i / 2;
					int left = index + i % 2;
					int right = index;
					while (true) {
						--left;
						++right;
						if (0 > left ||
							right == s.size() ||
							s[left] != s[right]) {
							--right;
							++left;
							break;
						}
					}
					int size = right - left + 1;
					if (max_size < size) {
						max_size = size;
						max_left = left;
						max_right = right;
					}
				}
				return s.substr(max_left, max_right - max_left + 1);
			}
		};
	}

	namespace task_6 {
		/*
		* https://leetcode.com/problems/zigzag-conversion/description/
		*/
		class Solution {
		public:
			string convert(string s, int numRows) {
				if (numRows == 1)
					return s;
				auto length = s.size();
				string res;
				
				for (size_t i = 0; i < length; i += (numRows - 1) * 2)
					res.push_back(s[i]);

				for (size_t j = 1; j < numRows - 1; j++)
					for (size_t i = j; i < length; i += (numRows - 1) * 2)
					{
						res.push_back(s[i]);
						size_t index = i + (numRows - j - 1) * 2;
						if (index < length)
							res.push_back(s[index]);
						else
							break;
					}

				for (size_t i = numRows - 1; i < length; i += (numRows - 1) * 2)
					res.push_back(s[i]);

				return res;
			}
		};
	}

	namespace task_7 {
		/*
		* https://leetcode.com/problems/reverse-integer/description/
		*/
		class Solution {
		public:
			int reverse(int x) {
				int res = 0;
				while (x != 0) {
					if (abs(x) < 10) {
						int add = x % 10;
						if (res > 214748364 || res == 214748364 && add > 7)
							return 0;
						if (res < -214748364 || res == -214748364 && add < -8)
							return 0;
					}
					res *= 10;
					res += x % 10;
					x /= 10;
				}
				return res;
			}
		};
	}

	namespace task_8 {
		/*
		* https://leetcode.com/problems/string-to-integer-atoi/
		*/
		class Solution {
		public:
			int myAtoi(string s) {
				int sign = 1;
				int res = 0;
				for (size_t i = 0; i < s.length(); i++)
				{
					if (s[i] == ' ')
						continue;
					if (s[i] == '-' || s[i] == '+' || (s[i] >= '0' && s[i] <= '9')) {
						if (s[i] == '-')
							sign = -1;
						if (s[i] == '-' || s[i] == '+')
							++i;
						
						for (size_t j = i; j < s.length() && s[j] >= '0' && s[j] <= '9'; j++) {
							int add = (s[j] - '0') * sign;
							if (res > 214748364 || res == 214748364 && add > 7)
								return 2147483647;
							if (res < -214748364 || res == -214748364 && add < -8)
								return -214748364;
							res = res * 10 + add;
						}
						break;
					}
					return 0;
				}
				return res;
			}
		};
	}

	namespace task_9 {
		/*
		* https://leetcode.com/problems/palindrome-number/
		*/
		class Solution {
		public:
			bool isPalindrome(int x) {
				if (x < 0)
					return false;
				int digit = 1;
				while (x / digit > 9)
					digit *= 10;
				int left = 0;
				int right = 0;
				while (x)
				{
					left = left * 10 + x / digit;
					right = right * 10 + x % 10;;
					if (left != right)
						return false;
					x %= digit;
					x /= 10;
					digit /= 100;
				}
				return left == right;
			}
		};
	}

	namespace task_10 {
		/*
		* https://leetcode.com/problems/regular-expression-matching/description/
		*/
		class Solution {
		public:
			vector<int> states;
			vector<int> new_states;
			string new_p;
			size_t size_pat;

			bool isMatch(string s, string p) {
				size_t size_str = s.size(), s_ptr = 0;
				new_p = string();
				for (const char c : p)
					if (c != '*')
						new_p.push_back(c);
					else if (new_p.back() == '.')
						new_p.back() = '?';  // '?' for repeating '.*'
					else if (new_p.back() >= 'a')
						new_p.back() -= 'a' - 'A'; // A-Z for repeating caracters (a-z*)

				size_pat = new_p.size();
				states = vector<int>(size_pat);
				new_states = vector<int>(size_pat);
				new_states[0] = 1;
				for (; s_ptr < size_str && !states.empty(); ++s_ptr) {
					activate();
					for (size_t i = 0; i < size_pat; ++i) {
						if (states[i] == 0)
							continue;
						size_t next = i + 1;
						if (new_p[i] == '.') {
							if (next == size_pat) {
								if (s_ptr + 1 == size_str)
									return true;
							}
							else
								new_states[next] = 1;
							states[i] = 0;
						}
						else if (new_p[i] >= 'a') {
							if (new_p[i] == s[s_ptr])
								if (next == size_pat) {
									if (s_ptr + 1 == size_str)
										return true;
								}
								else
									new_states[next] = 1;
							states[i] = 0;
						}
						else if (new_p[i] == '?') {
							if (next == size_pat)
								return true;
							new_states[next] = 1;
						}
						else {
							if (new_p[i] - 'A' + 'a' == s[s_ptr]) {
								if (next == size_pat) {
									if (s_ptr + 1 == size_str)
										return true;
								}
								else
									new_states[next] = 1;
							}
							else
								states[i] = 0;
						}
					}
				}
				for (int i = size_pat - 1; i >= 0 && (new_p[i] == '?' || (new_p[i] >= 'A' && new_p[i] <= 'Z')); --i)
					if (new_states[i])
						return true;
				return false;
			}

			void activate() {
				for (size_t i = 0; i < size_pat; ++i)
					if (new_states[i]) {
						if ((new_p[i] == '?' || (new_p[i] >= 'A' && new_p[i] <= 'Z')) && i + 1 < size_pat)
							new_states[i + 1] = 1;
						new_states[i] = 0;
						states[i] = 1;
					}
			}
		};
	}

	namespace task_11 {
		/*
		* https://leetcode.com/problems/container-with-most-water/description/
		*/
		class Solution_slow {
		public:
			int maxArea(vector<int>& height) {
				int max_area = 0;
				int max_j = height.size() - 1;
				for (size_t i = 0; i < max_j; i++)
					if (height[i] * (max_j - i) > max_area)
						for (size_t j = i + 1; j < height.size(); j++)
						{
							int area = min(height[i], height[j]) * (j - i);
							if (max_area < area)
								max_area = area;
						}
				return max_area;
			}
		};

		class Solution {
		public:
			int maxArea(vector<int>& height) {
				int max_area = 0;
				int left = 0;
				int right = height.size() - 1;
				while (left != right) {
					int area = min(height[left], height[right]) * (right - left);
					if (max_area < area)
						max_area = area;
					if (height[left] < height[right])
						++left;
					else
						--right;
				}
				return max_area;
			}
		};
	}

	namespace task_12 {
		/*
		* https://leetcode.com/problems/integer-to-roman/
		*/
		class Solution {
		public:
			string intToRoman(int num) {
				string res;
				int n = num / 1000;
				num %= 1000;
				for (size_t i = 0; i < n; i++)
					res += "M";

				n = num / 100;
				num %= 100;
				if (n == 9)
					res += "CM";
				else if (n == 4)
					res += "CD";
				else {
					if (n > 4) {
						res += "D";
						n -= 5;
					}
					for (size_t i = 0; i < n; i++)
						res += "C";
				}

				n = num / 10;
				num %= 10;
				if (n == 9)
					res += "XC";
				else if (n == 4)
					res += "XL";
				else {
					if (n > 4) {
						res += "L";
						n -= 5;
					}
					for (size_t i = 0; i < n; i++)
						res += "X";
				}

				n = num;
				if (n == 9)
					res += "IX";
				else if (n == 4)
					res += "IV";
				else {
					if (n > 4) {
						res += "V";
						n -= 5;
					}
					for (size_t i = 0; i < n; i++)
						res += "I";
				}

				return res;
			}
		};
	}

	namespace task_13 {
		/*
		* https://leetcode.com/problems/roman-to-integer/description/
		*/
		class Solution {
		public:
			int romanToInt(string s) {
				int n = 0;
				for (int i = s.size() - 1; i >= 0; --i) {
					if (s[i] == 'I')
						n += 1;
					if (s[i] == 'V')
						if (i > 0 && s[i - 1] == 'I') {
							--i;
							n += 4;
						}
						else
							n += 5;
					if (s[i] == 'X')
						if (i > 0 && s[i - 1] == 'I') {
							--i;
							n += 9;
						}
						else
							n += 10;
					if (s[i] == 'L')
						if (i > 0 && s[i - 1] == 'X') {
							--i;
							n += 40;
						}
						else
						n += 50;
					if (s[i] == 'C')
						if (i > 0 && s[i - 1] == 'X') {
							--i;
							n += 90;
						}
						else
						n += 100;
					if (s[i] == 'D')
						if (i > 0 && s[i - 1] == 'C') {
							--i;
							n += 400;
						}
						else
						n += 500;
					if (s[i] == 'M')
						if (i > 0 && s[i - 1] == 'C') {
							--i;
							n += 900;
						}
						else
						n += 1000;
				}

				return n;
			}
		};
	}

	namespace task_14 {
		/*
		* https://leetcode.com/problems/longest-common-prefix/
		*/
		class Solution {
		public:
			string longestCommonPrefix(vector<string>& strs) {
				string res;
				for (size_t i = 0; i < strs[0].size(); i++)
				{
					char c = strs[0][i];
					bool common = true;
					for (size_t j = 1; j < strs.size(); j++)
						if (i == strs[j].size() || strs[j][i] != c) {
							common = false;
							break;
						}
					if (common)
						res += c;
					else
						break;
				}

				return res;
			}
		};
	}

	namespace task_15 {
		/*
		* https://leetcode.com/problems/3sum/description/
		*/
		class Solution {
		public:
			vector<vector<int>> threeSum_fast(vector<int>& nums) {
				// Step 1: Sort the input vector in ascending order.
				sort(nums.begin(), nums.end());

				// Step 2: Create a vector to store the resulting triplets.
				vector<vector<int>> ans;

				// Step 3: Loop through the input vector.
				for (int i = 0; i < nums.size(); i++) {
					// Step 4: Find the target value to make the sum zero.
					int target = -(nums[i]);

					// Step 5: Initialize two pointers, j and k, to search for the other two elements.
					int j = i + 1;
					int k = nums.size() - 1;

					// Step 6: Perform a two-pointer search to find the other two elements.
					while (j < k) {
						// Step 7: If a triplet is found, add it to the result vector.
						if (nums[j] + nums[k] == target) {
							ans.push_back({ nums[i], nums[j], nums[k] });

							// Skip duplicate elements for pointers j and k.
							while (j < k && nums[j] == nums[j + 1]) j++;
							while (j < k && nums[k] == nums[k - 1]) k--;

							// Move the pointers to new positions.
							j++;
							k--;
						}
						// Step 8: If the sum is greater than the target, decrement k to reduce the sum.
						else if (nums[j] + nums[k] > target) {
							k--;
						}
						// Step 9: If the sum is smaller than the target, increment j to increase the sum.
						else {
							j++;
						}
					}

					// Step 10: Skip duplicate elements for pointer i.
					while (i + 1 < nums.size() && nums[i + 1] == nums[i]) {
						i++;
					}
				}

				// Step 11: Return the resulting vector of triplets.
				return ans;
			}

			vector<vector<int>> threeSum(vector<int>& nums) {
				vector<vector<int>> res;
				size_t size = nums.size();
				heap_sort(nums);

				for (size_t i = 0; i < size - 2; i++) {
					if (i > 0 && nums[i] == nums[i - 1])
						continue;
					if (nums[i] + nums[size - 2] + nums[size - 1] < 0)
						continue;
					if (nums[i] + nums[i + 1] + nums[i + 2] > 0)
						break;
					for (size_t j = i + 1; j < size - 1; j++) {
						if (j > i + 1 && nums[j] == nums[j - 1])
							continue;
						if (nums[i] + nums[j] + nums[size - 1] < 0)
							continue;
						if (nums[i] + nums[j] + nums[j + 1] > 0)
							break;

						size_t k = bin_search(nums, -nums[i] - nums[j], j, size);
						if (k != 0)
							res.push_back({ nums[i], nums[j], nums[k] });
					}
				}
				return res;
			}

			void heap_sort(std::vector<int>& arr)
			{
				build_max_heap(arr);
				int sz = arr.size();
				for (int i = arr.size() - 1; i > 0; i--)
				{
					std::swap(arr[0], arr[i]);
					sz--;
					max_heapify(arr, 0, sz);
				}
			}

			void build_max_heap(std::vector<int>& arr)
			{
				for (int i = (arr.size() / 2); i >= 0; i--)
					max_heapify(arr, i, arr.size());
			}

			void max_heapify(std::vector<int>& arr, int i, int size_)
			{
				int largest, l = (2 * i) + 1, r = l + 1;

				if (l < size_ && arr[l] > arr[i])
					largest = l;
				else
					largest = i;

				if (r < size_ && arr[r] > arr[largest])
					largest = r;

				if (largest != i)
				{
					std::swap(arr[i], arr[largest]);
					max_heapify(arr, largest, size_);
				}
			}

			size_t bin_search(vector<int>& nums, int value, size_t l, size_t r) {
				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == value)
						return i;
					if (nums[i] > value)
						r = i;
					else
						l = i;
				}
				return 0;
			}
		};
	}

	namespace task_16 {
		/*
		* https://leetcode.com/problems/3sum-closest/description/
		*/
		class Solution {
		public:
			int threeSumClosest(vector<int>& nums, int target) {
				heap_sort(nums);
				int sum = nums[0] + nums[1] + nums[2];
				int dif = abs(target - sum);
				const size_t size = nums.size();
				
				for (size_t i = 0; i < size - 2; i++) {
					if (i > 0 && nums[i] == nums[i - 1])
						continue;
					int step_target = target - nums[i];

					int j = i + 1;
					int k = size - 1;

					while (j < k) {
						int step_dif = step_target - (nums[j] + nums[k]);
						if (step_dif == 0)
							return target;
						if (dif > abs(step_dif)) {
							dif = abs(step_dif);
							sum = nums[i] + nums[j] + nums[k];
						}

						if (step_dif < 0)
							k--;
						else
							j++;
					}
				}
				return sum;
			}

			void heap_sort(std::vector<int>& arr)
			{
				build_max_heap(arr);
				int sz = arr.size();
				for (int i = arr.size() - 1; i > 0; i--)
				{
					std::swap(arr[0], arr[i]);
					sz--;
					max_heapify(arr, 0, sz);
				}
			}

			void build_max_heap(std::vector<int>& arr)
			{
				for (int i = (arr.size() / 2); i >= 0; i--)
					max_heapify(arr, i, arr.size());
			}

			void max_heapify(std::vector<int>& arr, int i, int size_)
			{
				int largest, l = (2 * i) + 1, r = l + 1;

				if (l < size_ && arr[l] > arr[i])
					largest = l;
				else
					largest = i;

				if (r < size_ && arr[r] > arr[largest])
					largest = r;

				if (largest != i)
				{
					std::swap(arr[i], arr[largest]);
					max_heapify(arr, largest, size_);
				}
			}
		};
	}

	namespace task_17 {
		/*
		* https://leetcode.com/problems/letter-combinations-of-a-phone-number/
		*/
		class Solution {
		public:
			vector<string> letterCombinations(string digits) {
				if (digits.size() == 0)
					return vector<string>();
				vector<string> res = init(digits);
				string letters(4, 'a');
				size_t letters_size = 3;
				size_t repeat = 1;
				size_t size = res.size();

				for (size_t i = 0; i < digits.size(); i++) {
					switch (digits[i])
					{
					case '2': {
						letters[0] = 'a';
						letters[1] = 'b';
						letters[2] = 'c';
						letters_size = 3;
						break;
					}
					case '3': {
						letters[0] = 'd';
						letters[1] = 'e';
						letters[2] = 'f';
						letters_size = 3;
						break;
					}
					case '4': {
						letters[0] = 'g';
						letters[1] = 'h';
						letters[2] = 'i';
						letters_size = 3;
						break;
					}
					case '5': {
						letters[0] = 'j';
						letters[1] = 'k';
						letters[2] = 'l';
						letters_size = 3;
						break;
					}
					case '6': {
						letters[0] = 'm';
						letters[1] = 'n';
						letters[2] = 'o';
						letters_size = 3;
						break;
					}
					case '7': {
						letters[0] = 'p';
						letters[1] = 'q';
						letters[2] = 'r';
						letters[3] = 's';
						letters_size = 4;
						break;
					}
					case '8': {
						letters[0] = 't';
						letters[1] = 'u';
						letters[2] = 'v';
						letters_size = 3;
						break;
					}
					case '9': {
						letters[0] = 'w';
						letters[1] = 'x';
						letters[2] = 'y';
						letters[3] = 'z';
						letters_size = 4;
						break;
					}
					default:
						break;
					}

					size_t res_i = 0;
					while (res_i < size)
						for (size_t j = 0; j < letters_size; j++)
							for (size_t k = 0; k < repeat; k++)
							{
								res[res_i][i] = letters[j];
								++res_i;
							}

					repeat *= letters_size;
				}
				   

				return res;
			}

			vector<string> init(string& digits) {
				
				size_t size_str = digits.size();
				size_t size = 1;
				for (const char c : digits)
					if (c == '7' || c == '9')
						size *= 4;
					else
						size *= 3;
				return vector<string>(size, string(size_str, 'a'));
			}
		};
	}

	namespace task_18 {
		/*
		* https://leetcode.com/problems/4sum/description/
		*/
		class Solution {
		public:
			vector<vector<int>> fourSum(vector<int>& nums, int target) {
				if (nums.size() < 4)
					return vector<vector<int>>();
				heap_sort(nums);
				vector<vector<int>> res;
				for (size_t q = 0; q < nums.size() - 3; q++) {
					if (q > 0 && nums[q] == nums[q - 1])
						continue;
					for (size_t i = q + 1; i < nums.size() - 2; i++) {
						if (i > q + 1 && nums[i] == nums[i - 1])
							continue;
						long long step_target = (long long)target - nums[q] - nums[i];
						int j = i + 1;
						int k = nums.size() - 1;

						while (j < k) {
							if (nums[j] + nums[k] == step_target) {
								res.push_back({ nums[q], nums[i], nums[j], nums[k] });

								while (j < k && nums[j] == nums[j + 1]) j++;
								while (j < k && nums[k] == nums[k - 1]) k--;

								j++;
								k--;
							}
							else if (nums[j] + nums[k] > step_target) {
								k--;
							}
							else {
								j++;
							}
						}
					}
				}
				return res;
			}

			void heap_sort(std::vector<int>& arr)
			{
				build_max_heap(arr);
				int sz = arr.size();
				for (int i = arr.size() - 1; i > 0; i--)
				{
					std::swap(arr[0], arr[i]);
					sz--;
					max_heapify(arr, 0, sz);
				}
			}

			void build_max_heap(std::vector<int>& arr)
			{
				for (int i = (arr.size() / 2); i >= 0; i--)
					max_heapify(arr, i, arr.size());
			}

			void max_heapify(std::vector<int>& arr, int i, int size_)
			{
				int largest, l = (2 * i) + 1, r = l + 1;

				if (l < size_ && arr[l] > arr[i])
					largest = l;
				else
					largest = i;

				if (r < size_ && arr[r] > arr[largest])
					largest = r;

				if (largest != i)
				{
					std::swap(arr[i], arr[largest]);
					max_heapify(arr, largest, size_);
				}
			}
		};
	}

	namespace task_19 {
		/*
		* https://leetcode.com/problems/remove-nth-node-from-end-of-list/
		*/
		class Solution {
		public:
			ListNode* removeNthFromEnd(ListNode* head, int n) {
				size_t size = 0;
				auto ptr = head;
				while (ptr)
				{
					++size;
					ptr = ptr->next;
				}
				if (n == size)
					return head->next;
				n = size + 1 - n;
				ptr = head;
				for (size_t i = 2; i < n; ++i)
					ptr = ptr->next;
				auto tmp = ptr->next->next;
				delete ptr->next;
				ptr->next = tmp;

				return head;
			}
		};
	}

	namespace task_20 {
		/*
		* https://leetcode.com/problems/valid-parentheses/description/
		*/
		class Solution {
		public:
			bool isValid(string s) {
				stack<char> st;
				for (const char c : s) {
					if (c == '(' || c == '{' || c == '[') {
						st.push(c);
						continue;
					}
					char top = 'c';
					if (st.empty())
						return false;
					else
						top = st.top();
					st.pop();

					if (top == '(' && c == ')' || top == '{' && c == '}' || top == '[' && c == ']')
						continue;
					return false;
				}
				return st.empty();
			}
		};
	}

	namespace task_21 {
		/*
		* https://leetcode.com/problems/merge-two-sorted-lists/
		*/
		class Solution {
		public:
			ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
				auto head = new ListNode();
				auto res = head;

				while (list1 && list2)
				{
					if (list1->val < list2->val) {
						res->next = list1;
						list1 = list1->next;
					}
					else {
						res->next = list2;
						list2 = list2->next;
					}
					res = res->next;
				}

				if (list1)
					res->next = list1;
				else
					res->next = list2;

				res = head->next;
				delete head;
				return res;
			}
		};
	}

	namespace task_22 {
		/*
		* https://leetcode.com/problems/generate-parentheses/description/
		*/
		class Solution {
		public:
			vector<string> generateParenthesis(int n) {
				vector<string> res({ "(" });
				generateParenthesis(res, 0, n - 1, n);
				return res;
			}

			void generateParenthesis(vector<string>& res, size_t i, size_t open, size_t close) {
				if (close == 0)
					return;
				if (open != 0) {
					if (open == close) {
						res[i].push_back('(');
						generateParenthesis(res, i, open - 1, close);;
					}
					else {
						res.push_back(res[i] + '(');
						generateParenthesis(res, res.size() - 1, open - 1, close);
					}
				}
				if (close > open) {
					res[i].push_back(')');
					generateParenthesis(res, i, open, close - 1);;
				}
			}
		};
	}

	namespace task_23 {
		/*
		* https://leetcode.com/problems/merge-k-sorted-lists/description/
		*/
		class Solution {
		public:
			ListNode* mergeKLists(vector<ListNode*>& lists) {
				for (int i = 0; i < lists.size(); i++)
					if (lists[i] == nullptr) {
						lists.erase(lists.begin() + i);
						--i;
					}
				if (lists.size() == 0)
					return nullptr;

				auto head = new ListNode();
				auto res = head;

				while (lists.size())
				{
					size_t min_index = 0;
					int min = lists[0]->val;
					for (size_t i = 1; i < lists.size(); i++)
						if (min > lists[i]->val) {
							min = lists[i]->val;
							min_index = i;
						}

					res->next = lists[min_index];
					lists[min_index] = lists[min_index]->next;
					if (!lists[min_index]) 
						lists.erase(lists.begin() + min_index);
					   
					res = res->next;
				}

				res = head->next;
				delete head;
				return res;
			}
		};
	}

	namespace task_24 {
		/*
		* https://leetcode.com/problems/swap-nodes-in-pairs/description/
		*/
		class Solution {
		public:
			ListNode* swapPairs(ListNode* head) {
				if (!head || !head->next)
					return head;
				auto newHead = head->next;
				head->next = newHead->next;
				newHead->next = head;

				auto cur = head;
				while (cur->next && cur->next->next) {
					auto next = cur->next;
					cur->next = next->next;
					next->next = cur->next->next;
					cur->next->next = next;
					cur = next;
				}
				return newHead;
			}
		};
	}

	namespace task_25 {
		/*
		* https://leetcode.com/problems/reverse-nodes-in-k-group/description/
		*/
		class Solution {
		public:
			ListNode* reverseKGroup(ListNode* head, int k) {
				if (k == 1)
					return head;
				size_t size = 0;
				auto ptr = head;
				while (ptr)
				{
					++size;
					ptr = ptr->next;
				}
				if (size < k)
					return head;

				auto guard = new ListNode(0, head);
				ptr = guard;
				auto j = ptr->next;
				vector<ListNode*> stack(k);
				while (k <= size) {
					for (size_t i = 0; i < k; i++) {
						stack[i] = j;
						j = j->next;
					}
					ptr->next = stack[k - 1];

					for (int i = k - 2; i >= 0; --i)
						stack[i + 1]->next = stack[i];
					stack[0]->next = j;
					ptr = stack[0];
					size -= k;
				}
				head = guard->next;
				delete guard;
				return head;
			}
		};
	}

	namespace task_26 {
		/*
		* https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
		*/
		class Solution {
		public:
			int removeDuplicates(vector<int>& nums) {
				for (size_t i = 1; i < nums.size(); i++)
					if (nums[i] == nums[i -1]) {
						nums.erase(nums.begin() + i);
						--i;
					}
				return nums.size();
			}
		};
	}

	namespace task_27 {
		/*
		* https://leetcode.com/problems/remove-element/description/
		*/
		class Solution {
		public:
			int removeElement(vector<int>& nums, int val) {
				for (int i = 0; i < nums.size(); i++)
					if (nums[i] == val) {
						nums.erase(nums.begin() + i);
						--i;
					}
				return nums.size();
			}
		};
	}

	namespace task_28 {
		/*
		* https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/
		*/
		class Solution {
		public:
			int strStr(string haystack, string needle) {
				if (haystack.size() < needle.size())
					return -1;
				for (size_t i = 0; i < haystack.size() - needle.size() + 1; ++i)
				{
					size_t j = 0;
					for (; j < needle.size(); ++j)
						if (haystack[i + j] != needle[j])
							break;
					if (j == needle.size())
						return i;
				}
				return -1;
			}
		};
	}

	namespace task_29 {
		/*
		* https://leetcode.com/problems/divide-two-integers/description/
		*/
		class Solution {
		public:
			int divide(int dividend, int divisor) {
				if (dividend == -2147483648 && divisor == -1)
					return 2147483647;
				return dividend / divisor;
			}
		};
	}

	namespace task_30 {
		/*
		* https://leetcode.com/substring-with-concatenation-of-all-words/
		*/
		class Solution {
		public:
			vector<int> findSubstring(string s, vector<string>& words) {
				const size_t size = s.size();
				const size_t count = words.size();
				const size_t length = words[0].size();
				const size_t end = size - count * length + 1;
				vector<int> res;
				if (size < count * length)
					return res;

				unordered_map<string, pair<size_t, size_t>> words_map; // <index in words, count of copy>
				vector<int> used(count, 0);
				vector<int> max_used(count, 0);
				vector<int> substr_indexes(size, -1);

				for (size_t i = 0; i < count; ++i) {
					auto it = words_map.find(words[i]);
					if (it != words_map.end())
						++it->second.second;
					else
						words_map[words[i]] = {i, 1};
				}

				for (const auto& it : words_map)
					max_used[it.second.first] = it.second.second;

				for (size_t i = 0; i < size - length + 1; ++i) {
					auto substr = s.substr(i, length);
					auto it = words_map.find(substr);
					if (it != words_map.end())
						substr_indexes[i] = it->second.first;
				}
			 
				for (size_t i = 0; i < end; ++i) {
					if (substr_indexes[i] == -1)
						continue;

					size_t count_used = 0;
					for (size_t j = 0; j < count; j++)
						used[j] = 0;

					size_t ii = i;
					while (ii < size - length + 1 && count_used < count) {
						if (substr_indexes[ii] == -1)
							break;
						++used[substr_indexes[ii]];
						if (used[substr_indexes[ii]] > max_used[substr_indexes[ii]])
							break;
						++count_used;
						ii += length;
					}
					if (count_used == count)
						res.push_back(i);

				}

				return res;
			}
		};
	}

	namespace task_31 {
		/*
		* https://leetcode.com/next-permutation/
		*/
		class Solution {
		public:
			void nextPermutation(vector<int>& nums) {
				const size_t size = nums.size();
				if (size < 2)
					return;
				int i = size - 2;
				for (; i >= 0; --i)
					if (nums[i] < nums[i + 1])
						break;

				const size_t count_swap = 1 + (size - i - 1) / 2;
				if (i != -1) {
					size_t j = size - 1;
					while (nums[j] <= nums[i])
						--j;
					swap(nums[j], nums[i]);
				}
				for (size_t k = 1; k < count_swap; ++k)
					swap(nums[i + k], nums[size - k]);
			}
		};
	}

	namespace task_32 {
		/*
		* https://leetcode.com/problems/longest-valid-parentheses/description/
		*/
		class Solution {
		public:
			int longestValidParentheses(string s) {
				size_t max = 0;
				stack<size_t> st;
				stack<pair<size_t, size_t>> seq_index;
				for (size_t i = 0; i < s.size(); i++) {
					if (s[i] == '(') {
						st.push(i);
						continue;
					}
					if (st.size() > 0) {
						size_t left = st.top();
						st.pop();
						while (seq_index.size() > 0) {
							auto& top_seq = seq_index.top();
							if (top_seq.second + 1 >= left) {
								if (left > top_seq.first  )
									left = top_seq.first;
								seq_index.pop();
								continue;
							}
							break;
						}
						seq_index.push({left, i});
					}
				}
				while (seq_index.size() > 0) {
					const auto& top_seq = seq_index.top();
					size_t len = top_seq.second - top_seq.first + 1;
					if (max < len)
						max = len;
					seq_index.pop();
				}
				return max;
			}

			int longestValidParentheses_quick(string s) {
				int n = s.length();
				stack<int> st;
				for (int i = 0; i < n; i++)
				{
					if (s[i] == ')')
					{
						if (st.empty() == 0)
						{
							int j = st.top();
							st.pop();
							s[i] = '_';
							s[j] = '_';
						}
					}
					if (s[i] == '(')
						st.push(i);
				}
				int ans = 0;
				for (int i = 0; i < n; i++)
				{
					if (s[i] == '_')
					{
						int ct = 1;
						i++;
						while (s[i] == '_')
						{
							ct++;
							i++;
						}
						i--;
						ans = max(ans, ct);
					}
				}
				return ans;
			}
		};
	}

	namespace task_33 {
		/*
		* https://leetcode.com/problems/search-in-rotated-sorted-array/description/
		*/
		class Solution {
		public:
			int search(vector<int>& nums, int target) {
				const size_t size = nums.size();
				if (size < 32) {
					for (size_t i = 0; i < size; i++)
						if (nums[i] == target)
							return i;
					return -1;
				}
				return bin_search(nums, target, size, find_rotate(nums, size));
			}

			size_t find_rotate(vector<int>& nums, const size_t size) {
				size_t l = 0;
				size_t r = size - 1;
				if (nums[l] < nums[r])
					return l;

				if (nums[r - 1] > nums[r])
					return r;
				size_t i = 0;
				while (r - l > 2) {
					i = (r + l) / 2;
					if (nums[i] < nums[l])
						r = i + 1;
					else
						l = i;
				}
				return i;
			}

			int bin_search(vector<int>& nums, int value, const size_t size, const size_t rotate_point) {
				size_t l = 0;
				size_t r = size;

				if (nums[rotate_point] == value)
					return rotate_point;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[(rotate_point + i) % size] == value)
						return (rotate_point + i) % size;
					if (nums[(rotate_point + i) % size] > value)
						r = i;
					else
						l = i;
				}
				return -1;
			}
		};
	}

	namespace task_34 {
		/*
		* https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
		*/
		class Solution {
		public:
			vector<int> searchRange(vector<int>& nums, int target) {
				const size_t size = nums.size();
				if (size < 32) {
					vector<int> res({ -1, -1 });
					for (size_t i = 0; i < size; i++)
						if (nums[i] == target) {
							res[0] = i;
							do
								++i;
							while (i < size && nums[i] == target);
							--i;
							res[1] = i;
							break;
						}
					return res;
				}

				return bin_search(nums, target, size);
			}

			vector<int> bin_search(vector<int>& nums, int target, const size_t size) {
				int l = 0;
				int r = size;
				if (nums[l] == target)
					return vector<int>({ l, right_search(nums, target, l, r)});

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == target)
						return vector<int>({ left_search(nums, target, l, i), right_search(nums, target, i, r) });
					if (nums[i] > target)
						r = i;
					else
						l = i;
				}
				return vector<int>({ -1, -1 });
			}

			int left_search(vector<int>& nums, int target, size_t l, size_t r) {
				if (nums[r - 1] != target)
					return r;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == target)
						r = i;
					else
						l = i;
				}
				return r;
			}

			int right_search(vector<int>& nums, int target, size_t l, size_t r) {
				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == target)
						l = i;
					else
						r = i;
				}
				return l;
			}
		};
	}

	namespace task_35 {
		/*
		* https://leetcode.com/problems/search-insert-position/description/
		*/
		class Solution {
		public:
			int searchInsert(vector<int>& nums, int target) {
				size_t l = 0;
				size_t r = nums.size();

				if (nums[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_36 {
		/*
		* https://leetcode.com/problems/valid-sudoku/description/
		*/
		class Solution {
		public:
			bool isValidSudoku(vector<vector<char>>& board) {
				const size_t size = 9;
				vector<int> unique(size, -1);
				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j)
					{
						if (board[i][j] == '.')
							continue;
						if (unique[board[i][j] - '1'] == i)
							return false;
						unique[board[i][j] - '1'] = i;
					}

				for (size_t i = 0; i < size; ++i)
					unique[i] = -1;

				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j)
					{
						if (board[j][i] == '.')
							continue;
						if (unique[board[j][i] - '1'] == i)
							return false;
						unique[board[j][i] - '1'] = i;
					}

				for (size_t i = 0; i < size; ++i)
					unique[i] = -1;

				for (size_t k = 0; k < 3; ++k)
					for (size_t l = 0; l < 3; ++l)
						for (size_t i = k * 3; i < (k + 1) * 3; ++i)
							for (size_t j = l * 3; j < (l + 1) * 3; ++j)
							{
								if (board[i][j] == '.')
									continue;
								if (unique[board[i][j] - '1'] == k * 3 + l)
									return false;
								unique[board[i][j] - '1'] = k * 3 + l;
							}

				return true;
			}
		};
	}

	namespace task_37 {
		/*
		* https://leetcode.com/problems/valid-sudoku/description/
		*/
		class Solution {
		public:
			const size_t size = 9;
			vector<size_t> empties;

			void solveSudoku(vector<vector<char>>& board) {
				empties.clear();
				prepareBefore(board);
				solve(board);
				prepareAfter(board);
			}

			void prepareBefore(vector<vector<char>>& board) {
				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j)
						if (board[i][j] == '.') {
							board[i][j] = 0;
							empties.push_back(i * size + j);
						}
						else
							board[i][j] -= '0';
			}

			void prepareAfter(vector<vector<char>>& board) {
				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j)
						board[i][j] += '0';
			}

			void solve(vector<vector<char>>& board) {
				size_t empty_i = 0, i, j;
				char c = 1;
				i = empties[empty_i] / size;
				j = empties[empty_i] % size;
				while (empty_i < empties.size()) {
					for (; c < 10; ++c)
						if (canWirtie(board, i, j, c))
							break;
					if (c == 10) {
						--empty_i;
						i = empties[empty_i] / size;
						j = empties[empty_i] % size;
						c = board[i][j] + 1;
						board[i][j] = 0;
						continue;
					}
					board[i][j] = c;
					c = 1;
					++empty_i;
					i = empties[empty_i] / size;
					j = empties[empty_i] % size;
				}
			}

			bool canWirtie(vector<vector<char>>& board, const size_t i, const size_t j, const char value) {
				vector<int> unique(size, -1);
				for (size_t k = 0; k < size; ++k) {
					if (board[k][j] == value)
						return false;
					if (board[i][k] == value)
						return false;
				}

				size_t to_i = (1 + i / 3) * 3, to_j = (1 + j / 3) * 3;
				for (size_t k = (i / 3) * 3; k < to_i; ++k)
					for (size_t l = (j / 3) * 3; l < to_j; ++l)
						if (board[k][l] == value)
							return false;

				return true;
			}
		};
	}

	namespace task_37__ {
		/*
		* https://leetcode.com/problems/sudoku-solver/description/
		*/
		class Solution {
		public:
			const size_t size = 9;
			size_t countEmpty;
			vector<vector<int>> rowPossible;
			vector<vector<int>> columnPossible;
			vector<vector<int>> cellPossible;
			set<vector<size_t>> rowCheck;
			set<vector<size_t>> columnCheck;
			set<vector<size_t>> cellCheck;
			stack<pair<size_t, size_t>> markIndexes;
			vector<vector<set<int>>> solveSet;
			vector<vector<int>> board;

			Solution(const Solution& solution) : countEmpty(solution.countEmpty),
				rowPossible(solution.rowPossible), columnPossible(solution.columnPossible),
				cellPossible(solution.cellPossible), rowCheck(solution.rowCheck),
				columnCheck(solution.columnCheck), cellCheck(solution.cellCheck),
				solveSet(solution.solveSet), board(solution.board) { }

			void solveSudoku(vector<vector<char>>& board) {
				buildSet(board);
			}

			void buildSet(vector<vector<char>>& _board) {
				rowPossible = vector<vector<int>>(size, vector<int>(size + 1, 0));
				columnPossible = vector<vector<int>>(size, vector<int>(size + 1, 0));
				cellPossible = vector<vector<int>>(size, vector<int>(size + 1, 0));

				rowCheck.clear();
				columnCheck.clear();
				cellCheck.clear();

				solveSet = vector<vector<set<int>>>(size, vector<set<int>>(size));
				board = vector<vector<int>>(size, vector<int>(size));
				const set<int> allowed({ 1, 2, 3,4, 5, 6, 7, 8, 9 });

				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j) {
						if (_board[i][j] == '.')
							board[i][j] = 0;
						else
							board[i][j] = _board[i][j] - '0';
						if (board[i][j] == 0) {
							solveSet[i][j] = allowed;


							for (size_t k = 0; k < size; ++k)
								if (board[i][k] != 0)
									solveSet[i][j].erase(board[i][k]);

							for (size_t k = 0; k < size; ++k)
								if (board[k][j] != 0)
									solveSet[i][j].erase(board[k][j]);

							for (size_t k = (i / 3) * 3; k < (1 + i / 3) * 3; ++k)
								for (size_t l = (j / 3) * 3; l < (1 + j / 3) * 3; ++l)
									if (board[k][l] != 0)
										solveSet[i][j].erase(board[k][l]);
						}
						else
							solveSet[i][j].insert(board[i][j]);
					}
				fillPossibles();
				adjustOneSizeSet();
			}

			void adjustOneSizeSet() {
				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j)
						if (board[i][j] == 0 && solveSet[i][j].size() == 1)
							writeNumber(i, j, *solveSet[i][j].begin());
				CheckNumber();
			}

			void fillPossibles() {
				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j) {
						if (board[i][j] == 0) {
							++countEmpty;
							for (const int option : solveSet[i][j]) {
								++rowPossible[i][option];
								++columnPossible[j][option];
								++cellPossible[(i / 3) * 3 + j / 3][option];;
							}
						}
					}
			}

			void CheckNumber() {
				while (!markIndexes.empty()) {
					const auto& index = markIndexes.top();
					size_t i = index.first;
					size_t j = index.second;
					markIndexes.pop();

					for (size_t k = 0; k < size; ++k)
						if (board[i][k] == 0 && solveSet[i][k].erase(board[i][j]))
							markPossoble(i, k, board[i][j]);

					for (size_t k = 0; k < size; ++k)
						if (board[k][j] == 0 && solveSet[k][j].erase(board[i][j]))
							markPossoble(k, j, board[i][j]);

					for (size_t k = (i / 3) * 3; k < (1 + i / 3) * 3; ++k)
						for (size_t l = (j / 3) * 3; l < (1 + j / 3) * 3; ++l)
							if (board[k][l] == 0 && solveSet[k][l].erase(board[i][j]))
								markPossoble(k, l, board[i][j]);
				}
			}

			void markPossoble(const size_t i, const size_t j, const int value) {
				--rowPossible[i][value];
				--columnPossible[j][value];
				const size_t cell_i = (i / 3) * 3 + j / 3;
				--cellPossible[cell_i][value];

				if (solveSet[i][j].size() == 1 ||
					rowPossible[i][value] == 1 ||
					columnPossible[j][value] == 1 ||
					cellPossible[cell_i][value] == 1)
					writeNumber(i, j, cell_i, value);
			}

			void writeNumber(const size_t i, const size_t j, const int value) {
				writeNumber(i, j, (i / 3) * 3 + j / 3, value);
			}

			void writeNumber(const size_t i, const size_t j, const size_t cell_i, const int value) {
				--countEmpty;
				board[i][j] = value;
				solveSet[i][j].clear();
				rowPossible[i][value] = 0;
				columnPossible[j][value] = 0;
				cellPossible[cell_i][value] = 0;
				markIndexes.push({ i, j });
			}

			void findOnePossible() {
				for (int value = 1; value < size + 1; value++)
				{
					for (size_t i = 0; i < size; i++)
						if (rowPossible[i][value] == 1)
							for (size_t j = 0; j < size; j++)
								if (solveSet[i][j].count(value))
									writeNumber(i, j, value);

					for (size_t j = 0; j < size; j++)
						if (columnPossible[j][value] == 1)
							for (size_t i = 0; i < size; i++)
								if (solveSet[i][j].count(value))
									writeNumber(i, j, value);

					for (size_t cell_i = 0; cell_i < size; cell_i++)
						if (cellPossible[cell_i][value] == 1)
							for (size_t i = (cell_i / 3) * 3; i < (1 + cell_i / 3) * 3; i++)
								for (size_t j = (cell_i % 3) * 3; j < (1 + cell_i % 3) * 3; j++)
									if (solveSet[i][j].count(value))
										writeNumber(i, j, cell_i, value);
				}

			}

			void obviousPair() {
				for (size_t i = 0; i < size; i++)
					for (size_t j = 1; j < size; j++)
						if (solveSet[i][j].size() == 2) {
							for (size_t row_i = i + 1; row_i < size; row_i++)
								if (solveSet[i][j] == solveSet[row_i][j])
									for (size_t a = 0; a < size; a++)
										if (a != i && a != row_i && board[a][j] == 0)
											for (const int value : solveSet[i][j])
												if (solveSet[a][j].erase(value))
													markPossoble(a, j, value);

							for (size_t column_i = i + 1; column_i < size; column_i++)
								if (solveSet[i][j] == solveSet[i][column_i])
									for (size_t b = 0; b < size; b++)
										if (b != j && b != column_i && board[i][b] == 0)
											for (const int value : solveSet[i][j])
												if (solveSet[i][b].erase(value))
													markPossoble(i, b, value);

							size_t cell_i_begin = (i / 3) * 3;
							size_t cell_i_end = (1 + i / 3) * 3;
							size_t cell_j_begin = (j / 3) * 3;
							size_t cell_j_end = (1 + j / 3) * 3;
							for (size_t cell_i = i; cell_i < cell_i_end; cell_i++)
								for (size_t cell_j = j + 1; cell_j < cell_j_end; cell_j++)
									if (solveSet[i][j] == solveSet[cell_i][cell_j])
										for (size_t a = cell_i_begin; a < cell_i_end; a++)
											for (size_t b = cell_j_begin; b < cell_j_end; b++)
												if (board[a][b] == 0 && solveSet[i][j] != solveSet[a][b])
													for (const int value : solveSet[i][j])
														if (solveSet[a][b].erase(value))
															markPossoble(a, b, value);
						}
			}

			void solve() {

				//fillPossibleQueue();
				findOnePossible();
				//if (countEmpty != 0)
			}

			bool chooseNumber(const size_t i, const size_t j, const int value) {
				//writeNumberCheck(i, j, value);
				findOnePossible();


			}

			bool checkSudoku(vector<vector<char>>& board) {
				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j)
						if (board[i][j] == 0 && solveSet[i][j].size() == 0)
							return false;
				return true;
			}
		};
	}

	namespace task_38 {
		/*
		* https://leetcode.com/problems/count-and-say/
		*/
		class Solution {
		public:
			string countAndSay(int n) {
				string s = "1";
				for (size_t i = 1; i < n; i++)
					s = getNext(s);
				return s;
			}

			string getNext(string s) {
				int i = 0;
				string next = "";
				while (i < s.size()) {
					int count = 1;
					int j = i + 1;
					while (j < s.size() && s[i] == s[j])
						++j;
					next.push_back('0' + j - i);
					next.push_back(s[i]);
					i = j;
				}
				return next;
			}
		};
	}

	namespace task_39 {
		/*
		* https://leetcode.com/problems/combination-sum/description/
		*/
		class Solution {
		public:
			vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
				sort(candidates.begin(), candidates.end());
				return combinationSumReq(candidates, 0, target);
			}

			vector<vector<int>> combinationSumReq(const vector<int>& candidates, const size_t from, int target) {
				if (from == candidates.size() || candidates[from] > target)
					return vector<vector<int>>();
				vector<vector<int>> res;

				int i = 0;
				for (; candidates[from] * i < target; i++) {
					auto vectors = combinationSumReq(candidates, from + 1, target - candidates[from] * i);
					for (auto& vec : vectors) {
						for (int j = i; j > 0; j--)
							vec.push_back(candidates[from]);
						res.push_back(vec);
					}
				}

				if (candidates[from] * i == target) 
					res.push_back(vector<int>(i, candidates[from]));

				return res;
			}
		};
	}

	namespace task_40 {
		/*
		* https://leetcode.com/problems/combination-sum-ii/description/
		*/
		class Solution {
		public:
			vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
				sort(candidates.begin(), candidates.end());
				return combinationSumReq(candidates, 0, target);
			}

			vector<vector<int>> combinationSumReq(const vector<int>& candidates, const size_t from, const int target) {
				if (from == candidates.size() || candidates[from] > target)
					return vector<vector<int>>();
				if (candidates[from] == target)
					return vector<vector<int>>(1, vector<int>(1, target));

				auto vectorsWith = combinationSumReq(candidates, from + 1, target - candidates[from]);
				auto vectorsWithout = combinationSumReq(candidates, getNextUnique(candidates, from), target);
				for (auto& vec : vectorsWith)
					vec.push_back(candidates[from]);
				for (auto& vec : vectorsWithout)
					vectorsWith.push_back(vec);

				return vectorsWith;
			}

			size_t getNextUnique(const vector<int>& candidates, const size_t from) {
				size_t next = from + 1;
				while (candidates.size() > next && candidates[next] == candidates[from])
					++next;
				return next;
			}
		};
	}

	namespace task_41 {
		/*
		* https://leetcode.com/problems/first-missing-positive/description/
		*/
		class Solution {
		public:
			int firstMissingPositive(vector<int>& nums) {
				const size_t size = nums.size();
				for (size_t i = 0; i < size; ++i)
					while (nums[i] > 0 && nums[i] <= size && nums[nums[i] - 1] != nums[i])
						swap(nums[nums[i] - 1], nums[i]);
				for (size_t i = 0; i < size; ++i)
					if (nums[i] != i + 1)
						return i + 1;
				return size + 1;
			}
		};
	}

	namespace task_42 {
		/*
		* https://leetcode.com/problems/trapping-rain-water/description/
		*/
		class Solution {
		public:
			int trapFast(std::vector<int>& height) {
				int i = 0, left_max = height[0], sum = 0;
				int j = height.size() - 1, right_max = height[j];
				while (i < j) {
					if (left_max <= right_max) {
						sum += (left_max - height[i]);
						i++;
						left_max = std::max(left_max, height[i]);
					}
					else {
						sum += (right_max - height[j]);
						j--;
						right_max = std::max(right_max, height[j]);
					}
				}
				return sum;
			}

			vector<pair<int, size_t>> monotonic_stack;
			int size_stack;

			int trap(vector<int>& height) {
				size_t size = height.size();
				if (size < 3)
					return 0;
				monotonic_stack = vector<pair<int, size_t>>(size);
				size_stack = 1;
				monotonic_stack[0] = { 0, 0 };
				int water = 0;
				for (size_t i = 0; i < size; i++)
					if (height[i] > 0)
						water += nextStep(height[i], i);
				return water;
			}

			int nextStep(int value, size_t index) {
				int i = size_stack - 1;
				int water = 0;
				monotonic_stack[size_stack] = { 0, index };
				for (; i >= 0 && monotonic_stack[i].first <= value; --i)
					water += (monotonic_stack[i].first - monotonic_stack[i + 1].first) *
					(index - monotonic_stack[i].second - 1);
				if (i >= 0)
					water += (value - monotonic_stack[i + 1].first) *
					(index - monotonic_stack[i].second - 1);
				++i;
				size_stack = i + 1;
				monotonic_stack[i] = { value, index };
				return water;
			}
		};
	}

	namespace task_43 {
		/*
		* https://leetcode.com/problems/multiply-strings/
		*/
		class Solution {
		public:
			string multiply(string num1, string num2) {
				if (num1 == "0" || num2 == "0")
					return "0";

				size_t size1 = num1.size();
				size_t size2 = num2.size();

				for (size_t i = 0; i < size1; i++)
					num1[i] -= '0';
				for (size_t i = 0; i < size2; i++)
					num2[i] -= '0';

				vector<int> res(num1.size() + num2.size(), 0);
				char x = 0;
				char plus10 = 0;

				for (int i = size1 - 1; i >= 0; --i) 
					for (int j = size2 - 1; j >= 0; --j) {
						res[i + j + 1] += num1[i] * num2[j];
						res[i + j] += res[i + j + 1] / 10;
						res[i + j + 1] %= 10;
					}
			
				
				size_t i = 0;
				string answer = "";
				while (res[i] == 0) i++;
				while (i < res.size()) answer.push_back(res[i++] + '0');

				return answer;
			}
		};
	}

	namespace task_44 {
		/*
		* https://leetcode.com/problems/regular-expression-matching/description/
		*/
		class Solution {
		public:
			vector<int> states;
			vector<int> new_states;
			size_t size_pat;

			bool isMatch(string s, string p) {
				size_t size_str = s.size(), s_ptr = 0;
				size_pat = p.size();
				if (size_pat == 0)
					return size_str == 0;
				states = vector<int>(size_pat);
				new_states = vector<int>(size_pat);
				new_states[0] = 1;
				for (; s_ptr < size_str && !states.empty(); ++s_ptr) {
					activate(p);
					for (size_t i = 0; i < size_pat; ++i) {
						if (states[i] == 0)
							continue;
						size_t next = i + 1;
						if (p[i] == '?') {
							if (next == size_pat) {
								if (s_ptr + 1 == size_str)
									return true;
							}
							else
								new_states[next] = 1;
							states[i] = 0;
						}
						else if (p[i] == '*') {
							if (next == size_pat) {
								if (s_ptr + 1 == size_str)
									return true;
							}
							else
								new_states[next] = 1;
						}
						else {
							if (p[i] == s[s_ptr])
								if (next == size_pat) {
									if (s_ptr + 1 == size_str)
										return true;
								}
								else
									new_states[next] = 1;
							states[i] = 0;
						}
					}
				}
				for (int i = size_pat - 1; i >= 0 && p[i] == '*'; --i)
					if (new_states[i])
						return true;
				return false;
			}

			void activate(const string& p) {
				for (size_t i = 0; i < size_pat; ++i)
					if (new_states[i]) {
						if (p[i] == '*' && i + 1 < size_pat)
							new_states[i + 1] = 1;
						new_states[i] = 0;
						states[i] = 1;
					}
			}
		};
	}

	namespace task_45 {
		/*
		* https://leetcode.com/problems/jump-game-ii/description/
		*/
		class Solution {
		public:
			int jump(vector<int>& nums) {
				for (int i = 1; i < nums.size(); i++)
					nums[i] = max(nums[i] + i, nums[i - 1]);

				int i = 0;
				int ans = 0;

				while (i < nums.size() - 1) {
					ans++;
					i = nums[i];
				}

				return ans;
			}

			int jump_first(vector<int>& nums) {
				const size_t size = nums.size();
				vector<int> steps(size, INT32_MAX);
				steps[0] = 0;
				for (size_t i = 1; i < size; i++)
					for (int j = i - 1; j >= 0; j--)
						if (nums[j] + j >= i && steps[j] < steps[i] - 1)
							steps[i] = steps[j] + 1;
				return steps.back();
			}
		};
	}

	namespace task_46 {
		/*
		* https://leetcode.com/permutations/description/
		*/
		class Solution {
		public:
			vector<vector<int>> permute(vector<int>& nums) {
				const int count = factorial(nums.size());
				vector<vector<int>> res(count);
				for (size_t i = 0; i < count; i++) {
					res[i] = nums;
					nextPermutation(nums);
				}
				return res;
			}

			void nextPermutation(vector<int>& nums) {
				const size_t size = nums.size();
				if (size < 2)
					return;
				int i = size - 2;
				for (; i >= 0; --i)
					if (nums[i] < nums[i + 1])
						break;

				const size_t count_swap = 1 + (size - i - 1) / 2;
				if (i != -1) {
					size_t j = size - 1;
					while (nums[j] <= nums[i])
						--j;
					swap(nums[j], nums[i]);
				}
				for (size_t k = 1; k < count_swap; ++k)
					swap(nums[i + k], nums[size - k]);
			}

			int factorial(int n) {
				int res = 1;
				for (size_t i = 2; i <= n; i++)
					res *= i;
				return res;
			}
		};
	}

	namespace task_47 {
		/*
		* https://leetcode.com/permutations-ii/description/
		*/
		class Solution {
		public:
			vector<vector<int>> permute(vector<int>& nums) {
				sort(nums.begin(), nums.end());
				const int count = factorial(nums.size());
				vector<vector<int>> res;
				res.push_back(nums);
				for (size_t i = 1; i < count; i++) {
					nextPermutation(nums);
					res.push_back(nums);
					if (res[i] == res[0]) {
						res.pop_back();
						break;
					}
				}
				return res;
			}

			void nextPermutation(vector<int>& nums) {
				const size_t size = nums.size();
				if (size < 2)
					return;
				int i = size - 2;
				for (; i >= 0; --i)
					if (nums[i] < nums[i + 1])
						break;

				const size_t count_swap = 1 + (size - i - 1) / 2;
				if (i != -1) {
					size_t j = size - 1;
					while (nums[j] <= nums[i])
						--j;
					swap(nums[j], nums[i]);
				}
				for (size_t k = 1; k < count_swap; ++k)
					swap(nums[i + k], nums[size - k]);
			}

			int factorial(int n) {
				int res = 1;
				for (size_t i = 2; i <= n; i++)
					res *= i;
				return res;
			}
		};
	}

	namespace task_48 {
		/*
		* https://leetcode.com/problems/rotate-image/description/
		*/
		class Solution {
		public:
			void rotate(vector<vector<int>>& matrix) {
				const size_t size = matrix.size();
				for (size_t i = 0; i < size >> 1; i++)
					for (size_t j = 0; j < (size + 1) >> 1; j++)
					{
						auto tmp = matrix[i][j];
						matrix[i][j] = matrix[size - j - 1][i];
						matrix[size - j - 1][i] = matrix[size - i - 1][size - j - 1];
						matrix[size - i - 1][size - j - 1] = matrix[j][size - i - 1];
						matrix[j][size - i - 1] = tmp;
					}
			}
		};
	}

	namespace task_49 {
		/*
		* https://leetcode.com/problems/group-anagrams/
		*/
		class Solution {
		public:
			vector<vector<string>> groupAnagrams(vector<string>& strs) {
				vector<pair<string, size_t>> copy;
				for (size_t i = 0; i < strs.size(); i++) {
					copy.push_back({ strs[i], i });
					sort(copy.back().first.begin(), copy.back().first.end());
				}

				sort(copy.begin(), copy.end());
				vector<vector<string>> answer(1);
				string curr = copy[0].first;
				for (const auto& c : copy) {
					if (curr != c.first) {
						curr = c.first;
						answer.push_back(vector<string>());
					}
					answer.back().push_back(strs[c.second]);
				}
				return answer;
			}
		};
	}

	namespace task_50 {
		/*
		* https://leetcode.com/problems/powx-n/description/
		*/
		class Solution {
		public:
			double myPow(double x, int n) {
				if (n < 0) {
					x = 1 / x;
					if (n == INT32_MIN) {
						n = n / 2;
						x = x * x;
					}
					n = -n;
				}
				double acc_odd = 1;
				double acc_even = x;
				while (n > 0) {
					if (n % 2 == 0) {
						acc_even *= acc_even;
						n >>= 1;
					}
					else {
						--n;
						acc_odd *= acc_even;
					}
				}
				return acc_odd;
			}
		};
	}

	namespace task_51 {
		/*
		* https://leetcode.com/problems/n-queens/
		*/
		class Solution {
		public:
			vector<string> chess;
			vector<vector<char>> prohibitions;
			vector<vector<string>> answers;
			size_t size;
			vector<vector<string>> solveNQueens(int n) {
				if (n < 4) {
					if (n == 1)
						return { {"Q"} };
					else
						return {};
				}
				size = n;
				answers.clear();
				chess = vector<string>(n, string(n, '.'));
				prohibitions = vector<vector<char>>{ vector<char>(n, 1), vector<char>(n * 2 - 1, 1), vector<char>(n * 2 - 1, 1) };
				solveNQueensReq(0);
				return answers;
			}

			void solveNQueensReq(size_t line) {
				if (line == size)
					answers.push_back(chess);
				for (size_t i = 0; i < size; ++i) {
					if (prohibitions[0][i] &&
						prohibitions[1][i + line] &&
						prohibitions[2][size - i - 1 + line]) {
						prohibitions[0][i] = 0;
						prohibitions[1][i + line] = 0;
						prohibitions[2][size - i - 1 + line] = 0;
						chess[line][i] = 'Q';
						solveNQueensReq(line + 1);
						prohibitions[0][i] = 1;
						prohibitions[1][i + line] = 1;
						prohibitions[2][size - i - 1 + line] = 1;
						chess[line][i] = '.';
					}
				}
			}
		};
	}

	namespace task_52 {
		/*
		* https://leetcode.com/problems/n-queens-ii/description/
		*/
		class Solution {// 1,0,0,2,10,4,40,92,352
		public:
			vector<vector<char>> prohibitions;
			int count;
			size_t size;
			int totalNQueens(int n) {
				if (n < 4)
					return n == 1 ? 1 : 0;
				size = n;
				count = 0;
				prohibitions = vector<vector<char>>{ vector<char>(n, 1), vector<char>(n * 2 - 1, 1), vector<char>(n * 2 - 1, 1) };
				solveNQueensReq(0);
				return count;
			}

			void solveNQueensReq(size_t line) {
				if (line == size)
					++count;
				for (size_t i = 0; i < size; ++i) {
					if (prohibitions[0][i] &&
						prohibitions[1][i + line] &&
						prohibitions[2][size - i - 1 + line]) {
						prohibitions[0][i] = 0;
						prohibitions[1][i + line] = 0;
						prohibitions[2][size - i - 1 + line] = 0;
						solveNQueensReq(line + 1);
						prohibitions[0][i] = 1;
						prohibitions[1][i + line] = 1;
						prohibitions[2][size - i - 1 + line] = 1;
					}
				}
			}

			int totalNQueensSwitch(int n) {
				switch (n)
				{
				case 1: return 1;
				case 4: return 2;
				case 5: return 10;
				case 6: return 4;
				case 7: return 40;
				case 8: return 92;
				case 9: return 352;
				default:
					return 0;
				}
			}
		};
	}

	namespace task_53 {
		/*
		* https://leetcode.com/problems/maximum-subarray/description/
		*/
		class Solution {
		public:
			int maxSubArray(vector<int>& nums) {
				int prev_sum = 0;
				int max_sum = INT_MIN;
				for (size_t n : nums) {
					if (prev_sum > 0)
						prev_sum += n;
					else
						prev_sum = n;
					max_sum = max(max_sum, prev_sum);
				}
				return max_sum;
			}
		};
	}

	namespace task_54 {
		/*
		* https://leetcode.com/problems/spiral-matrix/description/
		*/
		class Solution {
		public:
			vector<int> spiralOrder(vector<vector<int>>& matrix) {
				int left = 0, right = matrix[0].size(), up = 0, down = matrix.size();
				size_t size = right * down;
				vector<int> res;
				while (res.size() != size) {
					int j = left;
					int i = up;
					for (; j < right; j++)
						res.push_back(matrix[i][j]);
					if (res.size() == size)
						break;
					++i;
					--j;
					for (; i < down; i++)
						res.push_back(matrix[i][j]);
					if (res.size() == size)
						break;
					--i;
					--j;
					for (; j >= left; j--)
						res.push_back(matrix[i][j]);
					if (res.size() == size)
						break;
					--i;
					++j;
					for (; i > up; i--)
						res.push_back(matrix[i][j]);

					++left;
					++up;
					--right;
					--down;
				}
				return res;
			}
		};
	}

	namespace task_55 {
		/*
		* https://leetcode.com/problems/jump-game/description/
		*/
		class Solution {
		public:
			bool canJump(vector<int>& nums) {
				size_t maxPos = 0;
				for (size_t i = 0; i < nums.size() && i <= maxPos; ++i)
					maxPos = max(maxPos, nums[i] + i);

				return maxPos >= nums.size() - 1;
			}
		};
	}

	namespace task_56 {
		/*
		* https://leetcode.com/problems/merge-intervals/description/
		*/
		class Solution {
		public:
			vector<vector<int>> merge(vector<vector<int>>& intervals) {
				sort(intervals.begin(), intervals.end());
				vector<vector<int>> merged_intervals;
				for (size_t i = 0; i < intervals.size(); i++)
				{
					int start = intervals[i][0];
					int end = intervals[i][1];
					++i;
					for (; i < intervals.size() && end >= intervals[i][0]; i++)
						end = max(end, intervals[i][1]);
					--i;
					merged_intervals.push_back({ start , end });
				}
				return merged_intervals;
			}
		};
	}

	namespace task_57 {
		/*
		* https://leetcode.com/problems/insert-interval/description/
		*/
		class Solution {
		public:
			vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
				int start = newInterval[0];
				int end = newInterval[1];
				size_t i = 0;
				for (; i < intervals.size(); i++)
					if (intervals[i][1] >= start)
						break;

				if (i == intervals.size()) {
					intervals.push_back(newInterval);
					return intervals;
				}

				if (intervals[i][0] > end) {
					intervals.emplace(intervals.begin() + i, newInterval);
					return intervals;
				}

				if (intervals[i][1] >= end) {
					intervals[i][0] = min(intervals[i][0], start);
					return intervals;
				}

				size_t j = i + 1;
				for (; j < intervals.size(); j++)
					if (intervals[j][0] > end)
						break;
				start = min(intervals[i][0], start);
				end = max(intervals[j - 1][1], end);
				intervals.erase(intervals.begin() + i, intervals.begin() + j);
				intervals.emplace(intervals.begin() + i, vector<int>({ start , end }));

				return intervals;
			}
		};
	}

	namespace task_58 {
		/*
		* https://leetcode.com/problems/length-of-last-word/
		*/
		class Solution {
		public:
			int lengthOfLastWord(string s) {
				int i = s.size() - 1;
				while (s[i] == ' ')
					--i;
				int j = i - 1;
				for (; j >= 0 && s[j] != ' '; --j) {}
				return i - j;
			}
		};
	}

	namespace task_59 {
		/*
		* https://leetcode.com/problems/spiral-matrix-ii/description/
		*/
		class Solution {
		public:
			vector<vector<int>> generateMatrix(int n) {
				vector<vector<int>> matrix(n, vector<int>(n));
				int left = 0, right = n, up = 0, down = n;
				int c = 0;
				size_t size = n * n;
				while (c != size) {
					int j = left;
					int i = up;
					for (; j < right; j++)
						matrix[i][j] = ++c;
					if (c == size)
						break;
					++i;
					--j;
					for (; i < down; i++)
						matrix[i][j] = ++c;
					--i;
					--j;
					for (; j >= left; j--)
						matrix[i][j] = ++c;
					--i;
					++j;
					for (; i > up; i--)
						matrix[i][j] = ++c;

					++left;
					++up;
					--right;
					--down;
				}
				return matrix;
			}
		};
	}

	namespace task_60 {
		/*
		* https://leetcode.com/permutation-sequence/description/
		*/
		class Solution {
		public:
			string getPermutation(int n, int k) {
				--k;
				string res;
				string set;
				int group_size = factorial(n - 1);
				for (size_t i = 0; i < n; i++) 
					set.push_back('1' + i);

				while (n > 1) {
					size_t i = k / group_size;
					res.push_back(set[i]);
					set.erase(set.begin() + i);
					k %= group_size;
					--n;
					group_size /= n;
				}
				res.push_back(set[0]);
				return res;
			}

			int factorial(int n) {
				int res = 1;
				for (size_t i = 2; i <= n; i++)
					res *= i;
				return res;
			}
		};
	}

	namespace task_61
	{
		/*
		* https://leetcode.com/problems/rotate-list/description/
		*/
		class Solution {
		public:
			ListNode* rotateRight(ListNode* head, int k) {
				if (!head || !head->next)
					return head;

				ListNode* tail = head;
				size_t size = 1;
				while (tail->next) {
					++size;
					tail = tail->next;
				}
				k %= size;
				if (k == 0)
					return head;
				tail->next = head;
				k = size - k;
				for (size_t i = 0; i < k; i++) {
					tail = tail->next;
				}
				head = tail->next;
				tail->next = nullptr;
				return head;
			}
		};
	}

	namespace task_62 {
		/*
		* https://leetcode.com/problems/unique-paths/description/
		*/
		class Solution {
		public:
			int uniquePaths(int m, int n) {
				vector<vector<int>> matrix(m, (vector<int>(n)));
				matrix[0][0] = 1;
				for (size_t i = 0; i < m; i++)
					matrix[i][0] = 1;
				for (size_t j = 0; j < n; j++)
					matrix[0][j] = 1;

				for (size_t i = 1; i < m; i++)
					for (size_t j = 1; j < n; j++)
						matrix[i][j] = matrix[i][j - 1] + matrix[i - 1][j];

				return matrix[m - 1][n - 1];
			}

			int uniquePaths_math(int m, int n) {
				int t = min(m, n) - 1;
				m = m + n - 2;
				n = t;
				unsigned long long res = 1;
				for (int i = 1; i <= n; ++i)
					res = ((m - i + 1) * res) / i;
				return res;
			}
		};
	}

	namespace task_63 {
		/*
		* https://leetcode.com/problems/unique-paths-ii/description/
		*/
		class Solution {
		public:
			int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
				const size_t m = obstacleGrid.size();
				const size_t n = obstacleGrid[0].size();
				if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
					return 0;

				obstacleGrid[0][0] = 1;
				for (size_t i = 1; i < m; i++)
					if (obstacleGrid[i][0] == 0)
						obstacleGrid[i][0] = obstacleGrid[i - 1][0];
					else
						obstacleGrid[i][0] = 0;
				for (size_t j = 1; j < n; j++)
					if (obstacleGrid[0][j] == 0)
						obstacleGrid[0][j] = obstacleGrid[0][j - 1];
					else
						obstacleGrid[0][j] = 0;

				for (size_t i = 1; i < m; i++)
					for (size_t j = 1; j < n; j++)
						if (obstacleGrid[i][j] == 0)
							obstacleGrid[i][j] = obstacleGrid[i][j - 1] + obstacleGrid[i - 1][j];
						else
							obstacleGrid[i][j] = 0;

				return obstacleGrid[m - 1][n - 1];
			}
		};
	}

	namespace task_64 {
		/*
		* https://leetcode.com/problems/minimum-path-sum/description/
		*/
		class Solution {
		public:
			int minPathSum(vector<vector<int>>& grid) {
				const size_t m = grid.size();
				const size_t n = grid[0].size();

				for (size_t i = 1; i < m; i++)
					grid[i][0] += grid[i - 1][0];

				for (size_t j = 1; j < n; j++)
					grid[0][j] += grid[0][j - 1];

				for (size_t i = 1; i < m; i++)
					for (size_t j = 1; j < n; j++)
						grid[i][j] += min(grid[i][j - 1], grid[i - 1][j]);

				return grid[m - 1][n - 1];
			}
		};
	}

	namespace task_65 {
		/*
		* https://leetcode.com/problems/valid-number/description/
		*/
		class Solution {
		public:
			bool isNumber(string s) {
				size_t size = s.size(), from = 0;
				if (s[0] == '+' || s[0] == '-')
					++from;
				if (size == 1 && (s[0] < '0' || s[0] > '9'))
					return false;

				size_t ePos = size, dotPos = size;
				for (size_t i = from; i < size; i++) {
					if (s[i] == 'e' || s[i] == 'E') {
						if (ePos != size)
							return false;
						ePos = i;
					}
					else if (s[i] == '.') {
						if (dotPos != size)
							return false;
						dotPos = i;
					}
				}

				if (dotPos != size && dotPos > ePos) // 1e1.1
					return false;

				bool res = true;
				if (ePos != size) {
					if (ePos == from || ePos + 1 == size || (ePos == from + 1 && dotPos == from)) // +-e1, 1e, .e1
						return false;
					if (s[ePos + 1] == '+' || s[ePos + 1] == '-') {
						if (ePos + 2 == size) // 1e+
							return false;
						res &= isInt(s, ePos + 2, size);
					}
					else
						res &= isInt(s, ePos + 1, size);
				}
				size = ePos;
				if (from == dotPos && from + 1 == size) // +.
					return false;
				return res && isDec(s, from, size, dotPos);
			}

			bool isDec(const string& s, size_t i, const size_t size, const size_t dot) {
				if (dot >= size)
					return isInt(s, i, size);
				else
					return isInt(s, i, dot) && isInt(s, dot + 1, size);
			}

			bool isInt(const string& s, size_t i, const size_t size) {
				for (; i < size && s[i] >= '0' && s[i] <= '9'; ++i) {}
				return i == size;
			}
		};
	}

	namespace task_66
	{
		/*
		* https://leetcode.com/problems/plus-one/description/
		*/
		class Solution {
		public:
			vector<int> plusOne(vector<int>& digits) {
				int i = digits.size() - 1;
				bool add = true;
				for (; add && i >= 0; --i) {
					++digits[i];
					add = digits[i] == 10;
					if (add)
						digits[i] = 0;
				}

				if (add && i == -1)
					digits.emplace(digits.begin(), 1);
				return digits;
			}
		};
	}

	namespace task_67
	{
		/*
		* https://leetcode.com/problems/add-binary/description/
		*/
		class Solution {
		public:
			string addBinary(string a, string b) {
				if (a.size() < b.size())
					swap(a, b);
				int i = a.size() - 1;

				char add = 0;
				int sum = 0;
				for (int j = b.size() - 1; j >= 0; --j, --i) {
					sum = a[i] + b[j] + add - ('0' << 1);
					add = sum >> 1;
					sum &= 1;
					a[i] = sum + '0';
				}

				if (!add)
					return a;

				for (; add && i >= 0; --i) {
					sum = a[i] + add - '0';
					add = sum >> 1;
					sum &= 1;
					a[i] = sum + '0';
				}

				if (add && i == -1)
					a.insert(a.begin(), '1');
				return a;
			}
		};
	}

	namespace task_68 {
		/*
		* https://leetcode.com/problems/text-justification/description/
		*/
		class Solution {
		public:
			vector<string> fullJustify(vector<string>& words, int maxWidth) {
				size_t size = words.size(), first_in_line = 0;
				vector<string> res;
				int width = 0;
				for (size_t i = 0; i < size; ++i) {
					width += words[i].size() + 1;
					if (width - 1 > maxWidth) {
						width -= words[i].size() + 1;
						int count = i - first_in_line;
						int spaces = maxWidth - width + count;
						string str;
						for (; first_in_line < i; ++first_in_line) {
							--count;
							int len_spaces = count == 0 ? 0 : (spaces / count + (spaces % count == 0 ? 0 : 1));
							str += words[first_in_line] + string(len_spaces, ' ');
							spaces -= len_spaces;
						}
						if (str.size() < maxWidth)
							str += string(maxWidth - str.size(), ' ');
						res.push_back(str);
						width = words[i].size() + 1;
					}
				}
				string str;
				for (; first_in_line < size; ++first_in_line)
					str += words[first_in_line] + " ";
				if (str.size() > maxWidth)
					str.pop_back();
				else if (str.size() < maxWidth)
					str += string(maxWidth - str.size(), ' ');
				res.push_back(str);

				return res;
			}
		};
	}

	namespace task_69 {
		/*
		* https://leetcode.com/problems/sqrtx/description/
		*/
		class Solution {
		public:
			int mySqrt(int x) {
				int left = 0, right = 46340;

				while (left <= right) {
					// Prevent (left + right) overflow
					int mid = left + (right - left) / 2;
					if (mid * mid == x) { return mid; }
					else if (mid * mid > x) { right = mid - 1; }
					else { left = mid + 1; }
				}

				return right;
			}
		};
	}

	namespace task_70 {
		/*
		* https://leetcode.com/problems/climbing-stairs/description/
		*/
		class Solution {
		public:
			int climbStairs(int n) {
				if (n < 3)
					return n;
				int cur = 2;
				int prev = 1;
				for (size_t i = 2; i < n; i++) {
					int temp = cur + prev;
					prev = cur;
					cur = temp;
				}
				return cur;
			}
		};
	}

	namespace task_71 {
		/*
		* https://leetcode.com/problems/simplify-path/description/
		*/
		class Solution {
		public:
			string simplifyPath(string path) {
				size_t size = path.size(), pos = 1;
				for (; pos < size && path[pos] == '/'; ++pos) {}

				vector<string> words;
				for (size_t pos2 = path.find('/', pos); pos < size; pos = pos2, pos2 = path.find('/', pos)) {
					string word = path.substr(pos, pos2 - pos);
					for (; pos2 < size && path[pos2] == '/'; ++pos2) {}
					if (word == ".")
						continue;
					if (word == "..") {
						if (words.size() > 0)
							words.pop_back();
						continue;
					}
					words.push_back(word);
				}

				if (words.size() == 0)
					return "/";
				string canonical_path;
				for (const string& word : words)
					canonical_path += "/" + word;
				return canonical_path;
			}
		};
	}

	namespace task_72 {
		/*
		* https://leetcode.com/problems/edit-distance/description/
		*/
		class Solution {
		public:
			int minDistance(string word1, string word2) {
				const size_t size1 = word1.size();
				const size_t size2 = word2.size();
				if (size1 == 0 || size2 == 0)
					return size1 + size2;
				vector<vector<int>> result(size1, vector<int>(size2));
				int is_first_letter_same = 0;
				for (size_t j = 0; j < size2; j++) {
					if (word1[0] == word2[j])
						is_first_letter_same = 1;
					result[0][j] = j + 1 - is_first_letter_same;
				}
				is_first_letter_same = 0;
				for (size_t i = 0; i < size1; i++) {
					if (word1[i] == word2[0])
						is_first_letter_same = 1;
					result[i][0] = i + 1 - is_first_letter_same;
				}

				for (size_t i = 1; i < size1; i++)
					for (size_t j = 1; j < size2; j++)
						result[i][j] = min(min(result[i][j - 1] + 1, result[i - 1][j] + 1),
							result[i - 1][j - 1] + (word1[i] == word2[j] ? 0 : 1));
				return result.back().back();
			}
		};
	}

	namespace task_73 {
		/*
		* https://leetcode.com/problems/set-matrix-zeroes/
		*/
		class Solution {
		public:
			void setZeroes(vector<vector<int>>& matrix) {
				size_t m = matrix.size(), n = matrix[0].size();
				vector<int> rows(m), columns(n);
				for (size_t i = 0; i < m; ++i) {
					for (size_t j = 0; j < n; ++j)
						if (matrix[i][j] == 0) {
							rows[i] = 1;
							columns[j] = 1;
						}
				}
				for (size_t i = 0; i < m; ++i) {
					if (rows[i])
						for (size_t j = 0; j < n; ++j)
							matrix[i][j] = 0;
				}
				for (size_t j = 0; j < n; ++j) {
					if (columns[j])
						for (size_t i = 0; i < m; ++i)
							matrix[i][j] = 0;
				}
			}

			void setZeroes__o1_memory(vector<vector<int>>& matrix) {
				size_t m = matrix.size(), n = matrix[0].size();
				bool first_row = false, first_column = false;
				for (size_t i = 0; i < m; ++i) {
					if (matrix[i][0] == 0) {
						first_column = true;
						break;
					}
				}
				for (size_t j = 0; j < n; ++j) {
					if (matrix[0][j] == 0) {
						first_row = true;
						break;
					}
				}

				for (size_t i = 1; i < m; ++i) {
					for (size_t j = 1; j < n; ++j)
						if (matrix[i][j] == 0) {
							matrix[i][0] = 0;
							matrix[0][j] = 0;
						}
				}
				for (size_t i = 1; i < m; ++i) {
					if (matrix[i][0] == 0)
						for (size_t j = 1; j < n; ++j)
							matrix[i][j] = 0;
				}
				for (size_t j = 1; j < n; ++j) {
					if (matrix[0][j] == 0)
						for (size_t i = 1; i < m; ++i)
							matrix[i][j] = 0;
				}
				if (first_column) {
					for (size_t i = 0; i < m; ++i)
						matrix[i][0] = 0;
				}
				if (first_row) {
					for (size_t j = 0; j < n; ++j)
						matrix[0][j] = 0;
				}
			}
		};
	}

	namespace task_74 {
		/*
		* https://leetcode.com/problems/search-a-2d-matrix/description/
		*/
		class Solution {
		public:
			bool searchMatrix(vector<vector<int>>& matrix, int target) {
				const size_t length = matrix.size();
				const size_t width = matrix[0].size();
				size_t l = 0;
				size_t r = length * width;

				if (matrix[l][l] == target)
					return true;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (matrix[i / width][i % width] == target)
						return true;
					if (matrix[i / width][i % width] > target)
						r = i;
					else
						l = i;
				}
				return false;
			}
		};
	}

	namespace task_75 {
		/*
		* https://leetcode.com/problems/sort-colors/description/
		*/
		class Solution {
		public:
			void sortColors(vector<int>& nums) {
				vector<int> counts(3);
				for (const int n : nums)
					++counts[n];
				size_t size;
				size_t i = 0;
				for (size_t j = 0; j < 3; ++j) {
					size = counts[j];
					for (size_t count = 0; count < size; ++i, ++count)
						nums[i] = j;
				}
			}

			void sortColors2(vector<int>& nums) {
				int size = nums.size(), l = 0, r = size - 1;
				for (int i = 0; i < size; i++) {
					while (i >= l && i <= r && (nums[i] == 0 || nums[i] == 2)) {
						if (nums[i] == 0) swap(nums[i], nums[l++]);
						else if (nums[i] == 2) swap(nums[i], nums[r--]);
					}
				}
			}
		};
	}

	namespace task_76 {
		/*
		* https://leetcode.com/minimum-window-substring/description/
		*/
		class Solution {
		public:
			string minWindow(string s, string t) {
				const size_t s_size = s.size();
				const size_t t_size = t.size();
				if (s_size < t_size)
					return "";

				unordered_map<char, pair<size_t, size_t>> words_map; // <index in t, count of copy>
				vector<int> used(t_size, 0);
				vector<int> max_used(t_size, 0);
				vector<int> substr_indexes(s_size, -1);

				for (size_t i = 0; i < t_size; ++i) {
					auto it = words_map.find(t[i]);
					if (it != words_map.end())
						++it->second.second;
					else
						words_map[t[i]] = { i, 1 };
				}

				for (const auto& it : words_map)
					max_used[it.second.first] = it.second.second;

				for (size_t i = 0; i < s_size; ++i) {
					auto it = words_map.find(s[i]);
					if (it != words_map.end())
						substr_indexes[i] = it->second.first;
				}
				
				size_t r = 0;
				size_t count_used = 0;
				for (; r < s_size && count_used < t_size; ++r) {
					if (substr_indexes[r] == -1)
						continue;

					++used[substr_indexes[r]];
					if (used[substr_indexes[r]] <= max_used[substr_indexes[r]])
						++count_used;
				}

				if (r == s_size && count_used < t_size)
					return "";
				size_t min_l = 0;
				size_t min_r = s_size;
				size_t min_str_size = s_size;
				for (size_t l = 0; l < r; ++l) {
					if (substr_indexes[l] == -1)
						continue;

					if (used[substr_indexes[l]] > max_used[substr_indexes[l]]) {
						--used[substr_indexes[l]];
						continue;
					}

					size_t str_size = r - l;
					if (min_str_size > str_size) {
						min_str_size = str_size;
						min_l = l;
						min_r = r;
					}
					bool not_found = true;
					for (; r < s_size; ++r) {
						if (substr_indexes[l] == substr_indexes[r]) {
							++r;
							not_found = false;
							break;
						}
						else if (substr_indexes[r] != -1)
							++used[substr_indexes[r]];
					}

					if (not_found) 
						break;
				}
				return s.substr(min_l, min_str_size);
			}
		};
	}

	namespace task_77 {
		/*
		* https://leetcode.com/combinations/
		*/
		class Solution {
		public:
			vector<vector<int>> combine(int n, int k) {
				const size_t count = C(n, k);
				vector<vector<int>> res;
				res.push_back(vector<int>(k));
				for (size_t i = 0; i < k; i++)
					res[0][i] = i + 1;

				for (size_t i = 1; i < count; i++) {
					res.push_back(res[i - 1]);
					size_t max_allowed = n;
					int j = k - 1;

					while (j >= 0) {
						if (res[i][j] != max_allowed) {
							++res[i][j];
							++j;
							for (; j < k; ++j)
								res[i][j] = res[i][j - 1] + 1;
							break;
						}
						--j;
						--max_allowed;
					}
				}
				return res;
			}

			int C(int n, int k) {
				if ((n >> 1) < k)
					k = n - k;
				int res = 1;
				for (int i = 1; i <= k; ++i)
					res = ((n - i + 1)* res) / i;
				return res;
			}
		};
	}

	namespace task_78 {
		/*
		* https://leetcode.com/problems/subsets/description/
		*/
		class Solution {
		public:
			vector<vector<int>> subsets(vector<int>& nums) {
				size_t size = nums.size();
				vector<vector<int>> res(1 << size);
				for (size_t i = 0; i < size; i++) {
					size_t count_pieces = 1 << (i + 1);
					size_t size_of_piece = 1 << (size - i - 1);
					size_t t = 0;
					for (size_t j = 0; j < count_pieces; j++)
						if (j & 1)
							for (size_t k = 0; k < size_of_piece; k++, t++)
								res[t].push_back(nums[i]);
						else
							t += size_of_piece;
				}
				return res;
			}

			vector<vector<int>> subsets_recursion(vector<int>& nums) {
				vector<vector<int>> result;
				vector<int> path;
				backtrack(nums, 0, path, result);
				return result;
			}

			void backtrack(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& result) {
				result.push_back(path);
				for (int i = start; i < nums.size(); i++) {
					path.push_back(nums[i]);
					backtrack(nums, i + 1, path, result);
					path.pop_back();
				}
			}

			vector<vector<int>> subsets_bit_manipulation(vector<int>& nums) {
				vector<vector<int>> result;
				int n = nums.size();
				for (int i = 0; i < (1 << n); i++) {
					vector<int> subset;
					for (int j = 0; j < n; j++) {
						if ((i & (1 << j)) > 0) {
							subset.push_back(nums[j]);
						}
					}
					result.push_back(subset);
				}
				return result;
			}

			vector<vector<int>> subsets_iterative_way(vector<int>& nums) {
				vector<vector<int>> result = { {} }; // Add the empty subset
				for (int num : nums) {
					int size = result.size();
					for (int i = 0; i < size; i++) {
						vector<int> subset = result[i];
						subset.push_back(num);
						result.push_back(subset);
					}
				}
				return result;
			}
		};
	}

	namespace task_79 {
		/*
		* https://leetcode.com/problems/word-search/description/
		*/
		class Solution {
		public:
			vector<vector<char>> used = vector<vector<char>>(6, vector<char>(6));
			int m, n, size;
			bool exist(vector<vector<char>>& board, string word) {
				m = board.size();
				n = board[0].size();
				size = word.size();
				for (int i = 0; i < m; ++i) {
					for (int j = 0; j < n; ++j) {
						if (board[i][j] == word[0] && check(board, word, i, j, 1))
							return true;
					}
				}
				return false;
			}

			bool check(vector<vector<char>>& board, const string& word, const int i, const int j, const int k) {
				if (k == size)
					return true;
				used[i][j] = 1;
				bool found = false;
				if (i + 1 < m && board[i + 1][j] == word[k] && used[i + 1][j] == 0)
					found = check(board, word, i + 1, j, k + 1);
				if (j + 1 < n && board[i][j + 1] == word[k] && used[i][j + 1] == 0 && !found)
					found = check(board, word, i, j + 1, k + 1);
				if (i - 1 > -1 && board[i - 1][j] == word[k] && used[i - 1][j] == 0 && !found)
					found = check(board, word, i - 1, j, k + 1);
				if (j - 1 > -1 && board[i][j - 1] == word[k] && used[i][j - 1] == 0 && !found)
					found = check(board, word, i, j - 1, k + 1);
				used[i][j] = 0;
				return found;
			}
		};
	}

	namespace task_80 {
		/*
		* https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description/
		*/
		class Solution {
		public:
			int removeDuplicates(vector<int>& nums) {
				size_t insert_pos = 1, size = nums.size();
				for (size_t i = 1; i < size;) {
					for (; i < size && nums[i] != nums[i - 1]; ++i)
						nums[insert_pos++] = nums[i];
					if (i == size)
						break;
					nums[insert_pos++] = nums[i];
					for (; i < size && nums[i] == nums[i - 1]; ++i) {}
				}
				return insert_pos;
			}
		};
	}

	namespace task_81 {
		/*
		* https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/
		*/
		class Solution {
		public:
			bool search(vector<int>& nums, int target) {
				const size_t size = nums.size();
				for (size_t i = 0; i < size; i++)
					if (nums[i] == target)
						return true;
				return false;
			}
		};
	}

	namespace task_82
	{
		/*
		* https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
		*/
		class Solution {
		public:
			ListNode* deleteDuplicates(ListNode* head) {
				if (!head || !head->next)
					return head;

				ListNode* guard = new ListNode(-1000, head);
				ListNode* ptr = guard;
				while (ptr->next && ptr->next->next) {
					bool isRepeated = false;
					while (ptr->next->next && ptr->next->val == ptr->next->next->val) {
						ptr->next->next = ptr->next->next->next;
						isRepeated = true;
					}
					if (isRepeated)
						ptr->next = ptr->next->next;
					else
						ptr = ptr->next;
				}
				head = guard->next;
				delete guard;
				return head;
			}
		};
	}

	namespace task_83
	{
		/*
		* https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
		*/
		class Solution {
		public:
			ListNode* deleteDuplicates(ListNode* head) {
				if (!head || !head->next)
					return head;

				ListNode* ptr = head;
				while (ptr->next)
					if (ptr->val == ptr->next->val)
						ptr->next = ptr->next->next;
					else
						ptr = ptr->next;
				return head;
			}
		};
	}

	namespace task_84 {
		/*
		* https://leetcode.com/problems/largest-rectangle-in-histogram/description/
		*/
		class Solution {
		public:
			int largestRectangleAreaFast(vector<int>& heights) {
				stack<pair<int, int>> stack;
				int max_square = 0;
				int size = heights.size();
				for (int i = 0; i < size; ++i) {
					int idx = i;
					int x = heights[i];
					while (!stack.empty() && stack.top().first >= x) {
						int cal = abs(i - stack.top().second);
						max_square = max(max_square, cal * stack.top().first);
						idx = stack.top().second;
						stack.pop();
					}
					stack.push({ x,idx });
				}
				while (!stack.empty()) {
					int cal = abs(size - stack.top().second);
					max_square = max(max_square, cal * stack.top().first);
					stack.pop();
				}
				return max_square;
			}

			vector<pair<int, int>> monotonic_stack;
			int size_stack;

			int largestRectangleArea(vector<int>& heights) {
				int size = heights.size();
				monotonic_stack = vector<pair<int, int>>(size);
				int max_square = 0;
				for (int i = 0; i < size; i++)
					max_square = max(max_square, squareAt(heights[i], i));
				return max_square;
			}

			int squareAt(int value, int index) {
				if (value == 0) {
					size_stack = 0;
					return 0;
				}
				if (size_stack == 0) {
					monotonic_stack[0] = { value, index };
					size_stack = 1;
					return value;
				}
				int i = size_stack - 1;
				int max_square = value;
				for (; i >= 0; --i)
					max_square = max(max_square,
						min(monotonic_stack[i].first, value) * (index - monotonic_stack[i].second + 1));

				i = size_stack - 1;
				for (; i >= 0 && monotonic_stack[i].first > value; --i) {}

				if (i == -1) {
					monotonic_stack[0].first = value;
					size_stack = 1;
				}
				else {
					if (monotonic_stack[i].first < value) {
						++i;
						if (i == size_stack)
							monotonic_stack[i] = { value, index };
						else
							monotonic_stack[i].first = value;
					}
					size_stack = i + 1;
				}
				return max_square;
			}
		};
	}

	namespace task_85 {
		/*
		* https://leetcode.com/problems/largest-rectangle-in-histogram/description/
		*/
		class Solution {
		public:
			int maximalRectangle(vector<vector<char>>& matrix) {
				size_t height = matrix.size();
				size_t length = matrix[0].size();
				vector<int> heights(length);
				int max_square = 0;
				for (size_t i = 0; i < height; ++i) {
					for (size_t j = 0; j < length; j++) {
						int count = 0;
						for (size_t k = i; k < height && matrix[k][j] == '1'; ++k, ++count) {}
						heights[j] = count;
					}
					max_square = max(max_square, largestRectangleAreaFast(heights));
				}
				return max_square;
			}

			int largestRectangleAreaFast(vector<int>& heights) {
				stack<pair<int, int>> stack;
				int max_square = 0;
				int size = heights.size();
				for (int i = 0; i < size; ++i) {
					int idx = i;
					int x = heights[i];
					while (!stack.empty() && stack.top().first >= x) {
						int cal = abs(i - stack.top().second);
						max_square = max(max_square, cal * stack.top().first);
						idx = stack.top().second;
						stack.pop();
					}
					stack.push({ x,idx });
				}
				while (!stack.empty()) {
					int cal = abs(size - stack.top().second);
					max_square = max(max_square, cal * stack.top().first);
					stack.pop();
				}
				return max_square;
			}
		};
	}

	namespace task_86
	{
		/*
		* https://leetcode.com/problems/partition-list/description/
		*/
		class Solution {
		public:
			ListNode* partition(ListNode* head, int x) {
				if (!head)
					return head;

				ListNode* less_head = new ListNode();
				ListNode* less = less_head;
				ListNode* greater_head = new ListNode();
				ListNode* greater = greater_head;
				ListNode* ptr = head;
				while (ptr) {
					if (ptr->val < x) {
						less->next = ptr;
						less = less->next;
					}
					else {
						greater->next = ptr;
						greater = greater->next;
					}
					ptr = ptr->next;
				}
				greater->next = nullptr;
				less->next = greater_head->next;
				less = less_head->next;
				delete less_head;
				delete greater_head;
				return less;
			}
		};
	}

	namespace task_87 {
		/*
		* https://leetcode.com/problems/scramble-string/description/
		*/
		class Solution {
		public:
			bool isScramble(string s1, string s2) {
				size_t size = s1.size();
				vector<vector<vector<char>>> dp(size + 1, vector<vector<char>>(size, vector<char>(size)));
				for (size_t i = 0; i < size; ++i) {
					for (size_t j = 0; j < size; ++j)
						dp[1][i][j] = s1[i] == s2[j] ? 1 : 0;
				}

				for (size_t len = 2; len <= size; ++len) {
					for (size_t i = 0; i < size - len + 1; ++i) {
						for (size_t j = 0; j < size - len + 1; ++j) {
							for (size_t k = 1; k < len; ++k) {
								if (dp[k][i][j] == 1 && dp[len - k][i + k][j + k] == 1 ||
									dp[k][i][j + len - k] == 1 && dp[len - k][i + k][j] == 1) {
									dp[len][i][j] = 1;
									break;
								}
							}
						}
					}
				}

				return dp[size][0][0] == 1;
			}

			bool isScramble__TLE(string s1, string s2) {
				return isScramble__TLE(s1, s2, 0, s1.size(), 0, s1.size());
			}

			bool isScramble__TLE(const string& s1, const string& s2, size_t l1, size_t r1, size_t l2, size_t r2) {
				if (r1 - l1 == 1 && s1[l1] == s2[l2])
					return true;

				size_t length = r1 - l1;
				vector<int> count_letter(26);
				for (size_t i = 0; i < length; ++i) {
					++count_letter[s1[l1 + i] - 'a'];
					--count_letter[s2[l2 + i] - 'a'];
				}
				for (int n : count_letter)
					if (n != 0)
						return false;

				for (size_t i = 1; i < length; ++i) {
					if (isScramble__TLE(s1, s2, l1, l1 + i, l2, l2 + i) &&
						isScramble__TLE(s1, s2, l1 + i, r1, l2 + i, r2) ||
						isScramble__TLE(s1, s2, l1, l1 + i, r2 - i, r2) &&
						isScramble__TLE(s1, s2, l1 + i, r1, l2, r2 - i))
						return true;
				}
				return false;
			}
		};
	}

	namespace task_88 {
		/*
		* https://leetcode.com/problems/merge-sorted-array/description/
		*/
		class Solution {
		public:
			void mergeSaveMemory(vector<int>& nums1, int m, vector<int>& nums2, int n) {
				if (n == 0)
					return;
				if (m == 0) {
					swap(nums1, nums2);
					return;
				}
				for (size_t i = 0; i < m; ++i)
					nums1[m + n - 1 - i] = nums1[m - 1 - i];

				int i = n, j = 0, k = 0;
				while (i < m + n && j < n) {
					if (nums1[i] < nums2[j]) {
						nums1[k] = nums1[i];
						++i;
					}
					else {
						nums1[k] = nums2[j];
						++j;
					}
					++k;
				}
				for (; j < n; ++j, ++k)
					nums1[k] = nums2[j];
			}

			void mergeFast(vector<int>& nums1, int m, vector<int>& nums2, int n) {
				if (n == 0)
					return;
				vector<int> copy(m);
				copy.assign(nums1.begin(), nums1.begin() + m);
				int i = 0, j = 0, k = 0;
				while (i < m && j < n) {
					if (copy[i] < nums2[j]) {
						nums1[k] = copy[i];
						++i;
					}
					else {
						nums1[k] = nums2[j];
						++j;
					}
					++k;
				}
				for (; i < m; ++i, ++k)
					nums1[k] = copy[i];
				for (; j < n; ++j, ++k)
					nums1[k] = nums2[j];
			}
		};
	}

	namespace task_89 {
		/*
		* https://leetcode.com/problems/gray-code/description/
		*/
		class Solution {
		public:
			vector<int> grayCodeFast(int n) {
				size_t size = 1 << n;
				res = vector<int>(size);
				for (size_t i = 0; i < size; ++i)
					res[i] = ((i << 1) ^ i) >> 1;
				return res;
			}

			vector<int> res;
			vector<int> grayCode(int n) { // build the sequence which bit sould change (1,2,1,3,1,2,1,4,1,2,1,3,1,2,1...)
				size_t size = 1 << n;
				res = vector<int>(size);
				res[0] = 0;
				fillBitChangeQueue(size >> 1, n - 1);

				for (size_t i = 1; i < size; ++i)
					res[i] = res[i - 1] ^ (1 << res[i]);
				return res;
			}

			void fillBitChangeQueue(size_t from, int bit) {
				res[from] = bit;
				if (bit > 1) {
					--bit;
					fillBitChangeQueue(from - (1 << bit), bit);
					fillBitChangeQueue(from + (1 << bit), bit);
				}
			}
		};
	}

	namespace task_90 {
		/*
		* https://leetcode.com/problems/subsets-ii/description/
		*/
		class Solution {
		public:
			vector<vector<int>> subsetsWithDup(vector<int>& nums) {
				size_t size;
				vector<int> count_elements(21);
				for (const int n : nums)
					++count_elements[n + 10];

				vector<vector<int>> res = { {} }; // Add the empty subset
				for (size_t i = 0; i < 21; ++i) {
					size = res.size();
					for (size_t count = 1; count <= count_elements[i]; ++count)
						for (size_t j = 0; j < size; ++j) {
							vector<int> subset = res[j];
							for (size_t k = 1; k <= count; ++k)
								subset.push_back(i - 10);
							res.push_back(subset);
						}
				}
				return res;
			}
		};
	}

	namespace task_91 {
		/*
		* https://leetcode.com/problems/decode-ways/description/
		*/
		class Solution {
		public:
			int numDecodings(string s) {
				int size = s.size();
				if (size == 1)
					return s[0] == '0' ? 0 : 1;
				vector<int> ways(size);
				if (s[size - 1] != '0')
					ways[size - 1] = 1;

				if (s[size - 2] != '0')
					ways[size - 2] = ways[size - 1];
				if (s[size - 2] == '1')
					++ways[size - 2];
				else if (s[size - 2] == '2' && s[size - 1] < '7')
					++ways[size - 2];

				for (int i = size - 3; i > -1; --i) {
					if (s[i] != '0')
						ways[i] = ways[i + 1];
					if (s[i] == '1')
						ways[i] += ways[i + 2];
					else if (s[i] == '2' && s[i + 1] < '7')
						ways[i] += ways[i + 2];
				}
				return ways[0];
			}

			int numDecodings__o1_memory(string s) {
				int size = s.size();
				if (size == 1)
					return s[0] == '0' ? 0 : 1;
				int cur = 0, prev = 0, prev_prev = 0;
				if (s[size - 1] != '0')
					prev_prev = 1;

				if (s[size - 2] != '0')
					prev = prev_prev;
				if (s[size - 2] == '1')
					++prev;
				else if (s[size - 2] == '2' && s[size - 1] < '7')
					++prev;

				for (int i = size - 3; i > -1; --i) {
					if (s[i] != '0')
						cur = prev;
					if (s[i] == '1')
						cur += prev_prev;
					else if (s[i] == '2' && s[i + 1] < '7')
						cur += prev_prev;
					prev_prev = prev;
					prev = cur;
					cur = 0;
				}
				return prev;
			}
		};
	}

	namespace task_92 {
		/*
		* https://leetcode.com/problems/reverse-linked-list-ii/description/
		*/
		class Solution {
		public:
			ListNode* reverseBetween(ListNode* head, int left, int right) {
				if (!head || !head->next || left == right)
					return head;

				ListNode* guard = nullptr;
				if (left == 1) {
					guard = new ListNode(0, head);
					head = guard;
					++left;
					++right;
				}

				auto begin = head;

				for (size_t i = 2; i < left; ++i)
					begin = begin->next;

				auto prev = begin->next;
				auto ptr = prev->next;
				auto next = ptr->next;
				for (size_t i = left; i < right; ++i) {
					ptr->next = prev;
					prev = ptr;
					ptr = next;
					if (next) 
						next = next->next;
					else
						break;
				}
				begin->next->next = ptr;
				begin->next = prev;

				if (guard) {
					head = guard->next;
					delete guard;
				}
				return head;
			}
		};
	}

	namespace task_93 {
		/*
		* https://leetcode.com/problems/restore-ip-addresses/description/
		*/
		class Solution {
		public:
			vector<string> restoreIpAddresses(string s) {
				int size = s.size();
				if (size < 4)
					return {};
				vector<string> res;
				for (size_t i = 0; i < 3; ++i) {
					auto ip1 = s.substr(0, i + 1);
					if (isNotValid(ip1))
						continue;
					for (size_t j = i + 1; j < i + 4 && j < size; ++j) {
						auto ip2 = s.substr(i + 1, j - i);
						if (isNotValid(ip2))
							continue;
						for (size_t k = j + 1; k < j + 4 && k < size; ++k) {
							auto ip3 = s.substr(j + 1, k - j);
							if (isNotValid(ip3))
								continue;
							auto ip4 = s.substr(k + 1);
							if (isNotValid(ip4))
								continue;
							res.push_back(ip1 + "." + ip2 + "." + ip3 + "." + ip4);
						}
					}
				}
				return res;
			}

			bool isNotValid(const string& s) {
				if (s.size() > 3 || s.size() == 0)
					return true;
				if (s.size() == 1)
					return false;
				if (s.size() == 2)
					return s[0] == '0';
				return s[0] == '0' || s > "255";
			}
		};
	}

	namespace task_94 {
		/*
		* https://leetcode.com/problems/binary-tree-inorder-traversal/
		*/
		class Solution {
		public:
			vector<int> inorderTraversal(TreeNode* root) {
				if (!root)
					return {};
				vector<int> res;
				stack<TreeNode*> nodes;
				nodes.push(root);
				while (!nodes.empty()) {
					TreeNode* node = nodes.top();
					if (node->left && node->left->val != -1000) {
						nodes.push(node->left);
						continue;
					}
					res.push_back(node->val);
					node->val = -1000;
					nodes.pop();
					if (node->right)
						nodes.push(node->right);
				}
				return res;
			}
		};
	}

	namespace task_95 {
		/*
		* https://leetcode.com/problems/unique-binary-search-trees/
		*/
		class Solution {
		public:
			vector<TreeNode*> generateTrees(int n) {
				return generateTrees(1, n + 1);
			}

			vector<TreeNode*> generateTrees(int from, int to) {
				if (to == from)
					return { nullptr };
				if (to - from == 1)
					return { new TreeNode(from) };
				vector<TreeNode*> trees;
				for (int root = from; root < to; ++root) {
					auto lefts = generateTrees(from, root);
					auto rights = generateTrees(root + 1, to);
					for (size_t i = 0; i < lefts.size(); ++i) {
						for (size_t j = 0; j < rights.size(); ++j)
							trees.push_back(new TreeNode(root, lefts[i], rights[j]));
					}
				}
				return trees;
			}
		};
	}

	namespace task_96 {
		/*
		* https://leetcode.com/problems/unique-binary-search-trees/
		*/
		class Solution {
		public:
			int numTrees(int n) {
				if (n < 3) {
					switch (n)
					{
					case 1: return 1;
					case 2: return 2;
					case 3: return 5;
					}
				}
				++n;
				vector<int> counts(n);
				counts[0] = 1;
				counts[1] = 1;
				counts[2] = 2;
				counts[3] = 5;
				for (int i = 4; i < n; ++i) {
					for (int j = 0; j < i; ++j)
						counts[i] += counts[j] * counts[i - j - 1];
				}
				return counts[n - 1];
			}
		};
	}

	namespace task_97 {
		/*
		* https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/description/
		*/
		class Solution {
		public:
			bool isInterleave(string s1, string s2, string s3) {
				size_t size1 = s1.size(), size2 = s2.size(), size3 = s3.size();
				if (size1 + size2 != size3)
					return false;
				if (size1 == 0)
					return s2 == s3;
				if (size2 == 0)
					return s1 == s3;

				++size1, ++size2;
				vector<vector<char>> dp(size1, vector<char>(size2));
				dp[1][0] = s1[0] == s3[0] ? 1 : 0;
				dp[0][1] = s2[0] == s3[0] ? 1 : 0;
				for (int i = 2; i < size1 && dp[i - 1][0] == 1; ++i)
					dp[i][0] = s1[i - 1] == s3[i - 1] ? 1 : 0;
				for (int j = 2; j < size2 && dp[0][j - 1] == 1; ++j)
					dp[0][j] = s2[j - 1] == s3[j - 1] ? 1 : 0;

				for (int i = 1; i < size1; ++i) {
					for (int j = 1; j < size2; ++j) {
						if (dp[i][j - 1] == 1)
							dp[i][j] = s2[j - 1] == s3[i + j - 1] ? 1 : 0;
						if (dp[i - 1][j] == 1 && dp[i][j] == 0)
							dp[i][j] = s1[i - 1] == s3[i + j - 1] ? 1 : 0;
					}
				}

				return dp[size1 - 1][size2 - 1] == 1;
			}
		};
	}

	namespace task_98 {
		/*
		* https://leetcode.com/problems/validate-binary-search-tree/description/
		*/
		class Solution {
		public:
			bool isValidBST(TreeNode* root) {
				return isValidBST(root->left, 0, false, root->val, true) &&
					isValidBST(root->right, root->val, true, 0, false);
			}

			bool isValidBST(TreeNode* root, int bottom, bool hasBottom, int up, bool hasUp) {
				if (root == nullptr)
					return true;
				if (hasBottom && root->val <= bottom)
					return false;
				if (hasUp && root->val >= up)
					return false;
				return isValidBST(root->left, bottom, hasBottom, root->val, true) &&
					isValidBST(root->right, root->val, true, up, hasUp);
			}
		};
	}

	namespace task_99 {
		/*
		* https://leetcode.com/problems/recover-binary-search-tree/description/
		*/
		class Solution {
		public:
			TreeNode* firstElement = nullptr;
			TreeNode* secondElement = nullptr;
			TreeNode* prevElement = nullptr;

			void recoverTree(TreeNode* root) {
				traverse(root);
				swap(firstElement->val, secondElement->val);
			}

			void traverse(TreeNode* root) {
				if (root == nullptr)
					return;

				traverse(root->left);

				if (prevElement != nullptr && prevElement->val >= root->val) {
					if (firstElement == nullptr) {
						firstElement = prevElement;
					}
					if (firstElement != nullptr) {
						secondElement = root;
					}
				}
				prevElement = root;
				traverse(root->right);
			}
		};
	}

	namespace task_100 {
		/*
		* https://leetcode.com/same-tree/description/
		*/
		class Solution {
		public:
			bool isSameTree(TreeNode* p, TreeNode* q) {
				if (!p) {
					if (q)
						return false;
					return true;
				}
				else if (!q)
					return false;
				stack<TreeNode*> pStack, qStack;
				pStack.push(p);
				qStack.push(q);
				while (!pStack.empty()) {
					p = pStack.top();
					pStack.pop();
					q = qStack.top();
					qStack.pop();
					if (p->val != q->val)
						return false;
					if (p->left) {
						if (!q->left)
							return false;
						pStack.push(p->left);
						qStack.push(q->left);
					}
					else if (q->left)
						return false;
					if (p->right) {
						if (!q->right)
							return false;
						pStack.push(p->right);
						qStack.push(q->right);
					}
					else if (q->right)
						return false;
				}
				return true;
			}
		};
	}

	namespace task_101 {
		/*
		* https://leetcode.com/same-tree/description/
		*/
		class Solution {
		public:
			bool isSymmetric(TreeNode* root) {
				return isSameTree(root->left, root->right);
			}

			bool isSameTree(TreeNode* p, TreeNode* q) { // from task 100
				if (!p) {
					if (q)
						return false;
					return true;
				}
				else if (!q)
					return false;
				stack<TreeNode*> pStack, qStack;
				pStack.push(p);
				qStack.push(q);
				while (!pStack.empty()) {
					p = pStack.top();
					pStack.pop();
					q = qStack.top();
					qStack.pop();
					if (p->val != q->val)
						return false;
					if (p->left) {
						if (!q->right)
							return false;
						pStack.push(p->left);
						qStack.push(q->right);
					}
					else if (q->right)
						return false;
					if (p->right) {
						if (!q->left)
							return false;
						pStack.push(p->right);
						qStack.push(q->left);
					}
					else if (q->left)
						return false;
				}
				return true;
			}
		};
	}

	namespace task_104 {
		/*
		* https://leetcode.com/maximum-depth-of-binary-tree/description/
		*/
		class Solution {
		public:
			int maxDepth(TreeNode* root) {
				if (!root)
					return 0;
				queue<TreeNode*> queue({ root });
				int depth = 0;
				while (!queue.empty()) {
					++depth;
					int size = queue.size();
					for (int i = 0; i < size; ++i) {
						root = queue.front();
						queue.pop();
						if (root->right)
							queue.push(root->right);
						if (root->left)
							queue.push(root->left);
					}
				}
				return depth;
			}
		};
	}

	namespace task_108
	{
		/*
		* https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/
		*/
		class Solution {
		public:
			TreeNode* sortedArrayToBST(vector<int>& nums) {
				int l = 0;
				int r = nums.size();
				int m = (l + r) >> 1;

				auto root = new TreeNode(nums[m]);
				TreeNode* node = nullptr;
				stack<pair<vector<int>, TreeNode*>> stack;
				if (m - l > 0)
					stack.push({ {l, m, 0}, root });
				if (r - m - 1 > 0)
					stack.push({ {m + 1, r, 1}, root });

				while (!stack.empty()) {
					auto el = stack.top();
					stack.pop();
					l = el.first[0];
					r = el.first[1];
					m = (l + r) >> 1;
					node = new TreeNode(nums[m]);
					if (el.first[2])
						el.second->right = node;
					else
						el.second->left = node;

					if (m - l > 0)
						stack.push({ {l, m, 0}, node });
					if (r - m - 1 > 0)
						stack.push({ {m + 1, r, 1}, node });
				}
				return root;
			}
		};
	}

	namespace task_109
	{
		/*
		* https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
		*/
		class Solution {
		public:
			TreeNode* sortedListToBST(ListNode* head) {
				if (!head)
					return nullptr;

				vector<int> vec;
				while (head) {
					vec.push_back(head->val);
					head = head->next;
				}
				sort(vec.begin(), vec.end());
				int l = 0;
				int r = vec.size();
				int m = (l + r) >> 1;

				auto root = new TreeNode(vec[m]);
				TreeNode* node = nullptr;
				stack<pair<vector<int>, TreeNode*>> stack;
				if (m - l > 0)
					stack.push({ {l, m, 0}, root });
				if (r - m - 1 > 0)
					stack.push({ {m + 1, r, 1}, root });

				while (!stack.empty()) {
					auto el = stack.top();
					stack.pop();
					l = el.first[0];
					r = el.first[1];
					m = (l + r) >> 1;
					node = new TreeNode(vec[m]);
					if (el.first[2])
						el.second->right = node;
					else
						el.second->left = node;

					if (m - l > 0)
						stack.push({ {l, m, 0}, node });
					if (r - m - 1 > 0)
						stack.push({ {m + 1, r, 1}, node });
				}
				return root;
			}
		};
	}

	namespace task_110 {
		/*
		* https://leetcode.com/balanced-binary-tree/description/
		*/
		class Solution {
		public:
			bool isNotBalanced;
			bool isBalanced(TreeNode* root) {
				isNotBalanced = false;
				maxDepth(root);
				return !isNotBalanced;
			}

			int maxDepth(TreeNode* root) {
				if (!root || isNotBalanced)
					return 0;
				int left = maxDepth(root->left), right = maxDepth(root->right);
				isNotBalanced |= abs(left - right) > 1;
				return max(left, right) + 1;
			}

			int maxDepth2(TreeNode* root) {
				if (!root)
					return 0;
				queue<TreeNode*> queue({ root });
				int depth = 0;
				while (!queue.empty()) {
					++depth;
					int size = queue.size();
					for (int i = 0; i < size; ++i) {
						root = queue.front();
						queue.pop();
						if (root->right)
							queue.push(root->right);
						if (root->left)
							queue.push(root->left);
					}
				}
				return depth;
			}
		};
	}

	namespace task_111 {
		/*
		* https://leetcode.com/minimum-depth-of-binary-tree/description/
		*/
		class Solution {
		public:
			int minDepth(TreeNode* root) {
				if (!root)
					return 0;
				queue<TreeNode*> queue({ root });
				int depth = 0;
				while (!queue.empty()) {
					++depth;
					int size = queue.size();
					for (int i = 0; i < size; ++i) {
						root = queue.front();
						queue.pop();
						if (root->right)
							queue.push(root->right);
						if (root->left)
							queue.push(root->left);
						if (!root->left && !root->right)
							return depth;
					}
				}
				return depth;
			}
		};
	}

	namespace task_112 {
		/*
		* https://leetcode.com/path-sum/description/
		*/
		class Solution {
		public:
			bool hasPathSum(TreeNode* root, int targetSum) {
				if (!root)
					return false;
				queue<TreeNode*> queue({ root });
				while (!queue.empty()) {
					root = queue.front();
					queue.pop();
					if (root->right) {
						root->right->val += root->val;
						queue.push(root->right);
					}
					if (root->left) {
						root->left->val += root->val;
						queue.push(root->left);
					}
					if (!root->left && !root->right && root->val == targetSum)
						return true;
				}
				return false;
			}
		};
	}

	namespace task_114 {
		/*
		* https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
		*/
		class Solution {
		public:
			void flatten(TreeNode* root) {
				if (!root)
					return;

				TreeNode* node = nullptr;
				stack<TreeNode*> stack;
				if (root->right)
					stack.push(root->right);
				if (root->left)
					stack.push(root->left);
				root->left = nullptr;

				while (!stack.empty()) {
					auto node = stack.top();
					stack.pop();
					root->right = node;
					root = node;
					if (root->right)
						stack.push(root->right);
					if (root->left)
						stack.push(root->left);
					root->left = nullptr;
				}
			}
		};
	}

	namespace task_115 {
		/*
		* https://leetcode.com/problems/distinct-subsequences/description/
		*/
		class Solution {
		public:
			int numDistinct(string s, string t) {
				const size_t size1 = s.size();
				const size_t size2 = t.size();
				if (size1 < size2)
					return 0;
				vector<vector<long long>> result(size1, vector<long long>(size2));
				result[0][0] = s[0] == t[0] ? 1 : 0;
				for (size_t i = 1; i < size1 + 1 - size2; i++)
					result[i][0] = result[i - 1][0] + (s[i] == t[0] ? 1 : 0);

				for (size_t j = 1; j < size2; j++)
					for (size_t i = j; i < size1 + 1 + j - size2; i++)
						result[i][j] += result[i - 1][j] + (s[i] == t[j] ? result[i - 1][j - 1] : 0);
				return result.back().back();
			}
		};
	}

	namespace task_116 {
		/*
		* https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
		*/
		class Solution {
		public:
			Node* connect(Node* root) {
				if (!root)
					return root;
				queue<Node*> queue;
				Node* prev = nullptr;
				int count = 0;
				int max_count = 1;
				queue.push(root);

				while (!queue.empty()) {
					Node* node = queue.front();
					queue.pop();
					node->next = prev;
					prev = node;
					if (node->right)
						queue.push(node->right);
					if (node->left)
						queue.push(node->left);
					++count;
					if (count == max_count) {
						max_count <<= 1;
						count = 0;
						prev = nullptr;
					}
				}
				return root;
			}
		};
	}

	namespace task_117 {
		/*
		* https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/description/
		*/
		class Solution {
		public:
			Node* connect(Node* root) {
				if (!root)
					return root;
				queue<Node*> consume_queue;
				queue<Node*> store_queue;
				Node* prev = nullptr;
				consume_queue.push(root);

				while (!consume_queue.empty()) {
					prev = nullptr;
					while (!consume_queue.empty()) {
						Node* node = consume_queue.front();
						consume_queue.pop();

						node->next = prev;
						prev = node;

						if (node->right)
							store_queue.push(node->right);
						if (node->left)
							store_queue.push(node->left);
					}
					swap(consume_queue, store_queue);
				}
				return root;
			}
		};
	}

	namespace task_118 {
		/*
		* https://leetcode.com/problems/pascals-triangle/
		*/
		class Solution {
		public:
			vector<vector<int>> generate(int numRows) {
				vector<vector<int>> res;
				for (size_t k = 0; k < numRows; k++)
					res.push_back(getRow(k));
				return res;
			}

			vector<int> getRow(int rowIndex) {
				vector<int> res(rowIndex + 1, 1);
				for (size_t k = 1; k <= rowIndex; k++)
					res[k] = res[k - 1] * (rowIndex - k + 1) / k;
				return res;
			}
		};
	}

	namespace task_119 {
		/*
		* https://leetcode.com/problems/pascals-triangle-ii/description/
		*/
		class Solution {
		public:
			vector<int> getRow(int rowIndex) {
				vector<int> res(rowIndex + 1, 1);
				for (size_t k = 1; k <= rowIndex; k++)
					res[k] = res[k - 1] * (rowIndex - k + 1) / k;
				return res;
			}
		};
	}

	namespace task_120 {
		/*
		* https://leetcode.com/problems/triangle/description/
		*/
		class Solution {
		public:
			int minimumTotal(vector<vector<int>>& triangle) {
				const size_t size = triangle.size();

				for (size_t i = 1; i < size; i++)
					for (size_t j = 0; j <= i; j++)
						triangle[i][j] += min(j < i ? triangle[i - 1][j] : INT_MAX,
							j > 0 ? triangle[i - 1][j - 1] : INT_MAX);

				int min_path = INT_MAX;
				for (size_t j = 0; j < size; j++)
					if (min_path > triangle.back()[j])
						min_path = triangle.back()[j];

				return min_path;
			}
		};
	}

	namespace task_121 {
		/*
		* https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
		*/
		class Solution {
		public:
			int maxProfit(vector<int>& prices) {
				size_t size = prices.size();
				int min_price = prices[0];
				int profit = 0;
				for (int i = 1; i < size; ++i) {
					profit = max(profit, prices[i] - min_price);
					min_price = min(min_price, prices[i]);
				}
				return profit;
			}
		};
	}

	namespace task_122 {
		/*
		* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/
		*/
		class Solution {
		public:
			int maxProfit(vector<int>& prices) {
				size_t size = prices.size();
				int min_price = prices[0];
				int profit = 0;
				for (int i = 1; i < size; ++i) {
					if (prices[i] > min_price) {
						profit += prices[i] - min_price;
						min_price = prices[i];
					}
					else
						min_price = min(min_price, prices[i]);
				}
				return profit;
			}
		};
	}

	namespace task_123 {
		/*
		* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
		*/
		class Solution {
		public:
			int maxProfit(vector<int>& prices) {
				size_t size = prices.size();
				int min_price = prices[0];
				int profit = 0;
				for (int i = 1; i < size; ++i) {
					if (prices[i] > min_price) {
						profit += prices[i] - min_price;
						min_price = prices[i];
					}
					else
						min_price = min(min_price, prices[i]);
				}
				return profit;
			}
		};
	}

	namespace task_125 {
		/*
		* https://leetcode.com/problems/valid-palindrome/description/
		*/
		class Solution {
		public:
			bool isPalindrome(string s) {
				string converted;
				for (const char c : s) {
					if (c >= 'a' && c <= 'z' || c >= '0' && c <= '9')
						converted.push_back(c);
					else if (c >= 'A' && c <= 'Z')
						converted.push_back(c + 32);
				}
				return isPalindromeConverted(converted);
			}

			bool isPalindromeConverted(const string& s) {
				size_t size = s.size(), mid = size >> 1;
				for (size_t i = 0; i < mid; i++)
					if (s[i] != s[size - i - 1])
						return false;
				return true;
			}
		};
	}

	namespace task_131 {
		/*
		* https://leetcode.com/problems/palindrome-partitioning/description/
		*/
		class Solution {
		public:
			string str;
			size_t size;
			vector<vector<int>> palindrome_ends;

			vector<vector<string>> partition(string s) {
				str = s;
				size = s.size();
				palindrome_ends = vector<vector<int>>(size);
				allPalindromes();
				auto res = partitionRecursive(0);
				for (vector<string>& vec : res)
					reverse(vec.begin(), vec.end());
				return res;
			}

			vector<vector<string>> partitionRecursive(const size_t from) {
				vector<vector<string>> res;
				if (from == size) {
					res.push_back({});
					return res;
				}
				for (int length : palindrome_ends[from]) {
					auto partitionRes = partitionRecursive(from + length);
					string substr = str.substr(from, length);
					for (vector<string>& vec : partitionRes)
						vec.push_back(substr);
					res.insert(res.end(), partitionRes.begin(), partitionRes.end());
				}
				return res;
			}

			void allPalindromes() {
				size_t length = size * 2 - 1;

				for (size_t i = 0; i < size; i++)
					palindrome_ends[i].push_back(1);

				for (size_t i = 0; i < length; i++) {
					int index = i / 2;
					int left = index + i % 2;
					int right = index;
					while (true) {
						--left;
						++right;
						if (0 > left ||
							right == size ||
							str[left] != str[right]) {
							--right;
							++left;
							break;
						}
						palindrome_ends[left].push_back(right - left + 1);
					}
				}
			}

			vector<vector<string>> partition2(string s) {
				str = s;
				size = s.size();
				auto res = partitionRecursive2(0);
				for (vector<string>& vec : res)
					reverse(vec.begin(), vec.end());
				return res;
			}

			vector<vector<string>> partitionRecursive2(const size_t from) {
				vector<vector<string>> res;
				if (from == size) {
					res.push_back({});
					return res;
				}
				for (size_t i = from; i < size; i++)
					if (i - from + 1 == 1 || isPpalindrome(from, i)) {
						auto partitionRes = partitionRecursive(i + 1);
						string substr = str.substr(from, i - from + 1);
						for (vector<string>& vec : partitionRes)
							vec.push_back(substr);
						res.insert(res.end(), partitionRes.begin(), partitionRes.end());
					}
				return res;
			}

			bool isPpalindrome(const size_t from, const size_t to) {
				for (size_t i = from, j = to; i < j; ++i, --j)
					if (str[i] != str[j])
						return false;
				return true;
			}
		};
	}

	namespace task_135 {
		/*
		* https://leetcode.com/problems/candy/description/
		*/
		class Solution {
		public:
			int candy(vector<int>& ratings) {
				const size_t n = ratings.size();
				int sum = 1, prev_value = 1; // count candy for last child in previous sequence
				for (size_t i = 1; i < n; ++i) {
					if (ratings[i] == ratings[i - 1]) {
						++sum;
						prev_value = 1;
						continue;
					}
					size_t from = i - 1;
					if (ratings[i] > ratings[i - 1]) {
						for (; i < n && ratings[i] > ratings[i - 1]; ++i) {}
						int len = i - from;
						sum += len * (len + 1) / 2 - prev_value;
						prev_value = len;
					}
					else {
						for (; i < n && ratings[i] < ratings[i - 1]; ++i) {}
						int len = i - from;
						sum += len * (len - 1) / 2 - prev_value + max(prev_value, len);
						prev_value = 1;
					}
					--i;
				}
				return sum;
			}
		};
	}

	namespace task_136 {
		/*
		* https://leetcode.com/problems/single-number/description/
		*/
		class Solution {
		public:
			int singleNumber(vector<int>& nums) {
				int number = 0;
				for (int n : nums)
					number ^= n;
				return number;
			}
		};
	}

	namespace task_137 {
		/*
		* https://leetcode.com/problems/single-number-ii/description/
		*/
		class Solution {
		public:
			int singleNumberFastest(vector<int>& nums) {
				int ones = 0;
				int twos = 0;
				for (const int n : nums) {
					ones ^= (n & ~twos);
					twos ^= (n & ~ones);
				}

				return ones;
			}

			int singleNumberFast(vector<int>& nums) {
				int answer = 0;
				for (int i = 0; i < 32; ++i) {
					int sum = 0;
					for (const int num : nums)
						sum += num >> i & 1;
					sum %= 3;
					answer |= sum << i;
				}

				return answer;
			}

			int singleNumber(vector<int>& nums) {
				vector<int> bits(32);
				for (int n : nums) {
					for (size_t i = 0; i < 32 && n; i++) {
						if (n & 1)
							++bits[i];
						n >>= 1;
					}
				}
				int answer = 0;
				for (size_t i = 0; i < 32; i++)
					if (bits[i] % 3 == 1)
						answer |= 1 << i;
				return answer;
			}
		};
	}

	namespace task_138 {
		/*
		* https://leetcode.com/problems/copy-list-with-random-pointer/
		*/
		class Solution {
		public:
			NodeRandom* copyRandomList(NodeRandom* head) {
				if (!head)
					return head;
				size_t size = 0;
				map<NodeRandom*, size_t> node_number;
				vector<NodeRandom*> nodes;
				auto ptr = head;
				while (ptr) {
					auto node = new NodeRandom(ptr->val);
					nodes.push_back(node);
					node_number[ptr] = size;
					ptr = ptr->next;
					++size;
				}

				ptr = head->next;
				nodes[0]->random = head->random ? nodes[node_number[head->random]] : nullptr;
				for (size_t i = 1; i < size; i++, ptr = ptr->next) {
					nodes[i - 1]->next = nodes[i];
					nodes[i]->random = ptr->random ? nodes[node_number[ptr->random]] : nullptr;
				}
				return nodes[0];
			}
		};
	}

	namespace task_139 {
		/*
		* https://leetcode.com/problems/word-break/description/
		*/
		class Solution {
		public:
			bool wordBreak(string s, vector<string>& wordDict) {
				const size_t size = s.size();
				vector<char> result(size, 0);

				for (size_t i = 0; i < size; i++)
					for (size_t j = 0; j < wordDict.size(); j++) {
						const size_t word_size = wordDict[j].size();
						if (word_size > i + 1)
							continue;

						if ((word_size == i + 1 || result[i - word_size]) && s.substr(i + 1 - word_size, word_size) == wordDict[j]) {
							result[i] = 1;
							break;
						}
					}
				return result.back();
			}
		};
	}

	namespace task_140 {
		/*
		* https://leetcode.com/problems/word-break-ii/description/
		*/
		class Solution {
		public:
			vector<string> wordBreak(string s, vector<string>& wordDict) {
				const size_t size = s.size();
				vector<vector<size_t>> word_indexer(size);

				for (size_t i = 0; i < size; i++)
					for (size_t j = 0; j < wordDict.size(); j++) {
						const size_t word_size = wordDict[j].size();
						if (word_size > i + 1)
							continue;

						if ((word_size == i + 1 || !word_indexer[i - word_size].empty()) && s.substr(i + 1 - word_size, word_size) == wordDict[j]) {
							word_indexer[i].push_back(j);
						}
					}

				return buildResult(word_indexer, size - 1, wordDict);
			}

			vector<string> buildResult(const vector<vector<size_t>>& word_indexer, const size_t s_pos, const vector<string>& wordDict) {
				vector<string> result;
				for (size_t i = 0; i < word_indexer[s_pos].size(); i++) {
					const size_t word_size = wordDict[word_indexer[s_pos][i]].size();
					if (word_size > s_pos) {
						result.push_back(wordDict[word_indexer[s_pos][i]]);
						continue;
					}
					auto words = buildResult(word_indexer, s_pos - word_size, wordDict);
					for (size_t j = 0; j < words.size(); j++) {
						words[j] += " " + wordDict[word_indexer[s_pos][i]];
						result.push_back(words[j]);
					}
				}
				return result;
			}
		};
	}

	namespace task_141 {
		/*
		* https://leetcode.com/problems/linked-list-cycle/description/
		*/
		class Solution {
		public:
			bool hasCycle(ListNode* head) {
				ListNode* node = head;
				while (node && node->next) {
					node = node->next->next;
					head = head->next;
					if (head == node)
						return true;
				}
				return false;
			}

			bool hasCycleSet(ListNode* head) {
				set<ListNode*> nodes;
				while (head) {
					if (nodes.contains(head))
						return true;
					nodes.insert(head);
					head = head->next;
				}
				return false;
			}
		};
	}

	namespace task_142 {
		/*
		* https://leetcode.com/problems/linked-list-cycle-ii/description/
		*/
		class Solution {
		public:
			ListNode* detectCycle(ListNode* head) {
				ListNode* fast = head;
				ListNode* slow = head;
				while (fast && fast->next) {
					fast = fast->next->next;
					slow = slow->next;
					if (slow == fast)
						break;
				}
				if (!fast || !fast->next)
					return nullptr;
				while (head != slow) {
					slow = slow->next;
					head = head->next;
				}
				return head;
			}

			ListNode* detectCycleSet(ListNode* head) {
				set<ListNode*> nodes;
				while (head) {
					if (nodes.contains(head))
						return head;
					nodes.insert(head);
					head = head->next;
				}
				return nullptr;
			}
		};
	}

	namespace task_143 {
		/*
		* https://leetcode.com/problems/reorder-list/
		*/
		class Solution {
		public:
			void reorderList(ListNode* head) {
				if (!head || !head->next || !head->next->next)
					return;
				ListNode* ptr = head;
				size_t size = 0;
				while (ptr) {
					++size;
					ptr = ptr->next;
				}
				size >>= 1;
				ptr = head;
				for (size_t i = 0; i < size; ++i, ptr = ptr->next) {}

				ListNode* next_ptr = ptr->next;
				ListNode* temp;
				ptr->next = nullptr;
				ptr = next_ptr;
				next_ptr = ptr->next;
				ptr->next = nullptr;
				while (next_ptr) {
					temp = next_ptr->next;
					next_ptr->next = ptr;
					ptr = next_ptr;
					next_ptr = temp;
				}

				while (ptr) {
					temp = head->next;
					head->next = ptr;
					ptr = ptr->next;
					head->next->next = temp;
					head = temp;
				}
			}
		};
	}

	namespace task_144 {
		/*
		* https://leetcode.com/problems/binary-tree-postorder-traversal/
		*/
		class Solution {
		public:
			vector<int> preorderTraversal(TreeNode* root) {
				vector<int> res;
				if (!root)
					return res;

				stack<TreeNode*> stack;
				stack.push(root);

				while (!stack.empty()) {
					root = stack.top();
					stack.pop();
					res.push_back(root->val);
					if (root->right)
						stack.push(root->right);
					if (root->left)
						stack.push(root->left);
				}
				return res;
			}
		};
	}

	namespace task_145 {
		/*
		* https://leetcode.com/problems/binary-tree-postorder-traversal/
		*/
		class Solution {
		public:
			vector<int> postorderTraversal(TreeNode* root) {
				vector<int> res;
				if (!root)
					return res;

				stack<TreeNode*> stack;
				stack.push(root);

				while (!stack.empty()) {
					root = stack.top();
					stack.pop();
					res.push_back(root->val);
					if (root->left)
						stack.push(root->left);
					if (root->right)
						stack.push(root->right);
				}
				reverse(res.begin(), res.end());
				return res;
			}
		};
	}

	namespace task_146 {
		/*
		* https://leetcode.com/problems/reorder-list/
		*/
		class LRUCache {
		public:
			int capacity;
			int operations;
			unordered_map<int, pair<int, int>> map;

			LRUCache(int capacity) : capacity(capacity), operations(0) { }

			int get(int key) {
				if (auto it = map.find(key); it != map.end()) {
					it->second.second = operations;
					++operations;
					return it->second.first;
				}
				else {
					return -1;
				}
			}

			void put(int key, int value) {
				map[key] = { value , operations };
				++operations;
				if (map.size() > capacity) {
					value = operations;
					for (const auto& [_key, _value] : map)
						if (value > _value.second) {
							value = _value.second;
							key = _key;
						}
					map.erase(key);
				}
			}
		};
	}

	namespace task_147 {
		/*
		* https://leetcode.com/problems/insertion-sort-list/description/
		*/
		class Solution {
		public:
			ListNode* insertionSortList(ListNode* head) {
				ListNode* guard = new ListNode(0, head);
				ListNode* node = head->next;
				ListNode* temp;
				head->next = nullptr;
				while (node)
				{
					temp = node;
					node = node->next;
					head = guard;
					while (head->next && head->next->val < temp->val)
						head = head->next;
					temp->next = head->next;
					head->next = temp;
				}

				head = guard->next;
				delete guard;
				return head;
			}
		};
	}

	namespace task_148 {
		/*
		* https://leetcode.com/problems/sort-list/description/
		*/
		class Solution {
		public:
			ListNode* sortList(ListNode* head) {
				if (!head || !head->next)
					return head;
				ListNode* slow = head;
				ListNode* fast = head->next;
				while (fast && fast->next) {
					fast = fast->next->next;
					slow = slow->next;
				}

				fast = slow->next;
				slow->next = nullptr;
				slow = sortList(head);
				fast = sortList(fast);
				head = mergeTwoLists(slow, fast);
				return head;
			}

			ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
				auto head = new ListNode();
				auto res = head;

				while (list1 && list2)
				{
					if (list1->val < list2->val) {
						res->next = list1;
						list1 = list1->next;
					}
					else {
						res->next = list2;
						list2 = list2->next;
					}
					res = res->next;
				}

				if (list1)
					res->next = list1;
				else
					res->next = list2;

				res = head->next;
				delete head;
				return res;
			}
		};
	}

	namespace task_152 {
		/*
		* https://leetcode.com/problems/maximum-product-subarray/description/
		*/
		class Solution {
		public:
			int maxProduct(vector<int>& nums) {
				int max_prod = INT_MIN;
				int prod = 1;

				for (int i = 0; i < nums.size(); i++)
				{
					prod *= nums[i];
					max_prod = max(prod, max_prod);
					if (prod == 0)
						prod = 1;
				}
				prod = 1;
				for (int i = nums.size() - 1; i >= 0; i--)
				{
					prod *= nums[i];

					max_prod = max(prod, max_prod);
					if (prod == 0)
						prod = 1;
				}
				return max_prod;
			}
		};
	}

	namespace task_153 {
		/*
		* https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
		*/
		class Solution {
		public:
			int findMin(vector<int>& nums) {
				const size_t size = nums.size();
				if (size == 1)
					return nums[0];
				size_t l = 0;
				size_t r = size - 1;
				if (nums[l] < nums[r])
					return nums[l];
				if (nums[r - 1] > nums[r])
					return nums[r];

				while (r - l > 2) {
					size_t i = (r + l) / 2;
					if (nums[i] < nums[l])
						r = i + 1;
					else
						l = i;
				}
				return nums[l + 1];
			}
		};
	}

	namespace task_154 {
		/*
		* https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/description/
		*/
		class Solution {
		public:
			int findMin(vector<int>& nums) {
				const size_t size = nums.size();
				size_t min = 0;
				for (size_t i = 0; i < size; i++)
					if (nums[min] > nums[i])
						min = i;
				return nums[min];
			}
		};
	}

	namespace task_160 {
		/*
		* https://leetcode.com/problems/intersection-of-two-linked-lists/description/
		*/
		class Solution {
		public:
			ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
				size_t size_a = 0, size_b = 0;
				for (ListNode* ptr = headA; ptr; ptr = ptr->next, ++size_a) {}
				for (ListNode* ptr = headB; ptr; ptr = ptr->next, ++size_b) {}
				for (; size_a > size_b; headA = headA->next, --size_a) {}
				for (; size_b > size_a; headB = headB->next, --size_b) {}
				for (; headA && headA != headB; headA = headA->next, headB = headB->next) {}
				return headA;
			}
		};
	}

	namespace task_162 {
		/*
		* https://leetcode.com/problems/find-peak-element/description/
		*/
		class Solution {
		public:
			int findPeakElement(vector<int>& nums) {
				const size_t size = nums.size();
				if (size == 1 || nums[1] < nums[0])
					return 0;

				size_t l = 0;
				size_t r = size;

				while (r - l > 2) {
					size_t i = (r + l) / 2;
					if (nums[i] > nums[i + 1])
						r = i + 1;
					else
						l = i;
				}
				return l + 1;
			}
		};
	}

	namespace task_167 {
		/*
		* https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
		*/
		class Solution {
		public:
			vector<int> twoSum(vector<int>& numbers, int target) { // 36.76%-59.76%
				int i = 0, j = numbers.size() - 1;
				int dif = 0;
				do {
					dif = numbers[i] + numbers[j] - target;
					if (dif < 0)
						++i;
					else if (dif > 0)
						--j;
				} while (dif != 0);
				return { i + 1, j + 1 };
			}
		};
	}

	namespace task_168 {
		/*
		* https://leetcode.com/problems/excel-sheet-column-title/description/
		*/
		class Solution {
		public:
			string convertToTitle(int columnNumber) {
				string res;
				while (columnNumber > 0) {
					res.push_back('A' + (columnNumber - 1) % 26);
					columnNumber = (columnNumber - 1) / 26;
				}
				reverse(res.begin(), res.end());
				return res;
			}
		};
	}

	namespace task_169 {
		/*
		* https://leetcode.com/problems/majority-element/description/
		*/
		class Solution {
		public:
			int majorityElement(vector<int>& nums) {
				int size = nums.size(), from = 0, to = size - 1, less = from, more = to;
				while (true) {
					int middle = nums[from];
					for (int i = from + 1; i <= more; ) {
						if (middle < nums[i]) {
							swap(nums[i], nums[more]);
							--more;
						}
						else {
							if (middle > nums[i]) {
								swap(nums[i], nums[less]);
								++less;
							}
							++i;
						}
					}
					if ((more - less + 1) * 2 >= size)
						return middle;
					if (less - from > to - more)
						to = less - 1;
					else
						from = more + 1;
					more = to;
					less = from;
				}
				return nums[from];
			}

			int majorityElement__faster(vector<int>& nums) {
				int res = 0, majority = 0;

				for (int n : nums) {
					if (majority == 0)
						res = n;
					majority += n == res ? 1 : -1;
				}

				return res;
			}
		};
	}

	namespace task_171 {
		/*
		* https://leetcode.com/problems/excel-sheet-column-number/description/
		*/
		class Solution {
		public:
			int titleToNumber(string columnTitle) {
				size_t size = columnTitle.size();
				int res = 0;
				for (size_t i = 0; i < size; ++i)
					res = res * 26 + (columnTitle[i] - 'A' + 1);
				return res;
			}
		};
	}

	namespace task_175 {
		/*
		* https://leetcode.com/problems/combine-two-tables/description/
		*/
		/*
		SELECT Person.firstName , Person.lastName, Address.city, Address.state
		FROM Person
		LEFT JOIN Address ON Person.personId=Address.personId;
		*/
	}

	namespace task_179 {
		/*
		* https://leetcode.com/problems/largest-number/description/
		*/
		class Solution {
		public:
			string largestNumber(vector<int>& nums) {
				vector<string> numbers;
				for (const int n : nums)
					numbers.push_back(to_string(n));
				sort(numbers.begin(), numbers.end(), [this](const string& a, const string& b) {
					if (a.size() > b.size())
						return !greater(b, a);
					else
						return greater(a, b);
					});
				string number;
				for (const string& n : numbers)
					number.append(n);
				return number[0] == '0' ? "0" : number;
			}

			bool greater(const string& a, const string& b) {
				size_t i = 0;
				size_t a_size = a.size();
				size_t b_size = b.size();
				size_t size = a_size + b_size;
				for (; i < a_size; ++i) {
					if (a[i] < b[i])
						return false;
					if (a[i] > b[i])
						return true;
				}
				for (; i < b_size; ++i) {
					if (b[i - a_size] < b[i])
						return false;
					if (b[i - a_size] > b[i])
						return true;
				}
				for (; i < size; ++i) {
					if (b[i - a_size] < a[i - b_size])
						return false;
					if (b[i - a_size] > a[i - b_size])
						return true;
				}
				return false;
			}
		};
	}

	namespace task_181 {
		/*
		* https://leetcode.com/problems/employees-earning-more-than-their-managers/description/
		*/
		/*
		SELECT A.name  AS Employee
		FROM Employee A
		LEFT JOIN Employee B ON A.managerId=B.id
		WHERE A.salary  > B.salary;
		*/
	}

	namespace task_182 {
		/*
		* https://leetcode.com/problems/duplicate-emails/description/
		*/
		/*
		SELECT DISTINCT Person.Email, COUNT(*) FROM Person
		GROUP BY Person.Email
		HAVING
		COUNT(*) > 1;
		*/
	}

	namespace task_183 {
		/*
		* https://leetcode.com/problems/customers-who-never-order/description/
		*/
		/*
		SELECT Customers.name
		FROM Customers
		left join Orders
		on Customers.id = Orders.customerId
		where Orders.customerId Is Null;
		*/
	}

	namespace task_188 {
		/*
		* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
		*/
		class Solution {
		public:
			int maxProfit(int k, vector<int>& prices) {
				if (k == 1)
					return maxProfitOnce(prices);
				prices.push_back(-1);
				const size_t size = prices.size();
				vector<int> trades;
				size_t i = 1;
				size_t min_price_i = 0;

				while (i < size) {
					for (; i < size && (prices[min_price_i] >= prices[i - 1] || prices[i] >= prices[i - 1]); ++i)
						if (prices[min_price_i] > prices[i])
							min_price_i = i;
					if (i == size)
						break;

					trades.push_back(prices[min_price_i]);
					trades.push_back(prices[i - 1]);
					bool is_not_last_deleted = true;
					if (trades.size() >> 1 > k)
						is_not_last_deleted = findToErase(trades);
					if (is_not_last_deleted)
						min_price_i = i;
					++i;
				}

				int sum = 0;
				for (size_t i = 1; i < trades.size(); i += 2)
					sum += trades[i] - trades[i - 1];
				return sum;
			}

			bool findToErase(vector<int>& trades) {
				size_t to_erase_i = 1;
				const size_t size = trades.size();
				int min_loss = INT_MAX;
				for (size_t i = 1; i < size; i++) {
					int loss = abs(trades[i] - trades[i - 1]);
					if (min_loss > loss) {
						min_loss = loss;
						to_erase_i = i;
					}
				}

				trades.erase(trades.begin() + to_erase_i - 1);
				trades.erase(trades.begin() + to_erase_i - 1);
				return to_erase_i != size - 1;
			}

			int maxProfitOnce(const vector<int>& prices) {
				size_t size = prices.size();
				int min_price = prices[0];
				int profit = 0;
				for (int i = 1; i < size; ++i) {
					profit = max(profit, prices[i] - min_price);
					min_price = min(min_price, prices[i]);
				}
				return profit;
			}
		};
	}

	namespace task_190 {
		/*
		* https://leetcode.com/problems/reverse-bits/description/
		*/
		class Solution {
		public:
			uint32_t reverseBits(uint32_t n) {
				uint32_t reversed = 0;
				for (int i = 0; i < 32; ++i)
					reversed += (((1 << i) & n) >> i) << (31 - i);
				return reversed;
			}

			uint32_t reverseBits_fats(uint32_t n) {
				n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
				n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
				n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
				n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
				n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
				return n;

			}
		};
	}

	namespace task_191 {
		/*
		* https://leetcode.com/problems/number-of-1-bits/description/
		*/
		class Solution {
		public:
			int hammingWeight(int n) {
				int count = 0;
				for (; n != 0; n >>= 1)
					if (n & 1)
						++count;
				return count;
			}
		};
	}

	namespace task_196 {
		/*
		* https://leetcode.com/problems/customers-who-never-order/description/
		*/
		/*
		delete p1
		from person p1
		join person p2
		on p1.email = p2.email and p1.id>p2.id;
		*/
	}

	namespace task_198 {
		/*
		* https://leetcode.com/problems/house-robber/description/
		*/
		class Solution {
		public:
			int rob(vector<int>& nums) {
				const size_t size = nums.size();
				if (size == 1)
					return nums[0];
				if (size == 2)
					return max(nums[0], nums[1]);
				nums[2] += nums[0];
				if (size == 3)
					return max(nums[1], nums[2]);

				for (size_t i = 3; i < size; i++)
					nums[i] += max(nums[i - 2], nums[i - 3]);
				return max(nums[size - 1], nums[size - 2]);
			}
		};
	}

	namespace task_201 {
		/*
		* https://leetcode.com/problems/bitwise-and-of-numbers-range/description/
		*/
		class Solution {
		public:
			int rangeBitwiseAndFast(int left, int right) {
				int shift = 0;
				while (left && left != right) {
					left >>= 1, right >>= 1;
					shift++;
				}
				return (left << shift);
			}

			int rangeBitwiseAnd(int left, int right) {
				if (right - left >= left)
					return 0;
				int x = left;

				for (int i = 0; i < 31 && x; ++i) {
					int bit = (1 << i) & x;
					if (bit && ((bit & right) == 0 || right - left >= bit))
						x &= ~bit;
				}
				return x;
			}
		};
	}

	namespace task_202 {
		/*
		* https://leetcode.com/problems/happy-number/description/
		*/
		class Solution {
		public:
			bool isHappy(int n) {
				int sum = 0;
				unordered_set<int> set;
				while (!set.contains(n) && n != 1) {
					set.insert(n);
					sum = 0;
					for (; n > 0; n /= 10)
						sum += (n % 10) * (n % 10);
					n = sum;
				}
				return n == 1;
			}
		};
	}

	namespace task_203 {
		/*
		* https://leetcode.com/problems/remove-linked-list-elements/
		*/
		class Solution {
		public:
			ListNode* removeElements(ListNode* head, int val) {
				if (!head)
					return head;
				auto guard = new ListNode(0, head);
				head = guard;
				while (head && head->next) {
					if (head->next->val == val) {
						auto temp = head->next->next;
						delete head->next;
						head->next = temp;
					}
					else
						head = head->next;
				}

				head = guard->next;
				delete guard;
				return head;
			}
		};
	}

	namespace task_205 {
		/*
		* https://leetcode.com/problems/isomorphic-strings/description/
		*/
		class Solution {
		public:
			bool isIsomorphic__copied(string s, string t) {
				int s_array[256] = { 0 };
				int t_array[256] = { 0 };
				int n = s.size();

				for (int i = 0; i < n; ++i) {
					if (s_array[s[i]] != t_array[t[i]])
						return false;
					s_array[s[i]] = i + 1;
					t_array[t[i]] = i + 1;
				}
				return true;
			}
		};
	}

	namespace task_206 {
		/*
		* https://leetcode.com/problems/reverse-linked-list/description/
		*/
		class Solution {
		public:
			ListNode* reverseList(ListNode* head) {
				if (!head || !head->next)
					return head;
				
				auto prev = head;
				auto ptr = head->next;
				auto next = ptr->next;
				while (true) {
					ptr->next = prev;
					prev = ptr;
					if (next) {
						ptr = next;
						next = next->next;
					}
					else
						break;
				}
				head->next = nullptr;

				return ptr;
			}
		};
	}

	namespace task_207 {
		/*
		* https://leetcode.com/problems/course-schedule/description/
		*/
		class Solution {
		public:
			bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
				vector<vector<int>> adjacency_list(numCourses);
				for (const auto& edge : prerequisites)
					adjacency_list[edge[0]].push_back(edge[1]);
				return topologySort(adjacency_list, numCourses);
			}

			bool topologySort(const vector<vector<int>>& adjacency_list, const size_t size) {
				vector<int> visited(size);
				stack<size_t> vertexes;
				for (size_t i = 0; i < size; ++i)
					if (visited[i] == 0) {
						vertexes.push(i);
						while (!vertexes.empty()) {
							size_t vertex = vertexes.top();
							if (visited[vertex] == 2) {
								vertexes.pop();
								continue;
							}
							if (visited[vertex] == 1) {
								visited[vertex] = 2;
								vertexes.pop();
								continue;
							}
							visited[vertex] = 1;
							for (const int neighbour : adjacency_list[vertex]) {
								if (visited[neighbour] == 1)
									return false;
								if (visited[neighbour] == 0)
									vertexes.push(neighbour);
							}
						}
					}
				return true;
			}
		};
	}

	namespace task_208 {
		/*
		* https://leetcode.com/problems/implement-trie-prefix-tree/description/
		*/
		class Trie {
		public:
			class Node {
			public:
				Node* children[26];
				bool isEnd = false;
			};
			Node* root;

			Trie() : root(new Node()) { }

			void insert(string word) {
				Node* node = root;
				for (const char c : word) {
					size_t i = c - 'a';
					if (!node->children[i])
						node->children[i] = new Node();
					node = node->children[i];
				}
				node->isEnd = true;
			}

			bool search(string word) {
				Node* node = root;
				for (const char c : word) {
					size_t i = c - 'a';
					if (!node->children[i])
						return false;
					node = node->children[i];
				}
				return node->isEnd;
			}

			bool startsWith(string prefix) {
				Node* node = root;
				for (const char c : prefix) {
					size_t i = c - 'a';
					if (!node->children[i])
						return false;
					node = node->children[i];
				}
				return true;
			}
		};
	}

	namespace task_210 {
		/*
		* https://leetcode.com/problems/course-schedule-ii/description/
		*/
		class Solution {
		public:
			vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
				vector<vector<int>> adjacency_list(numCourses);
				for (const auto& edge : prerequisites)
					adjacency_list[edge[0]].push_back(edge[1]);
				return topologySort(adjacency_list, numCourses);
			}

			vector<int> topologySort(const vector<vector<int>>& adjacency_list, const size_t size) {
				vector<int> visited(size);
				stack<size_t> vertexes;
				vector<int> sorted;
				for (size_t i = 0; i < size; ++i)
					if (visited[i] == 0) {
						vertexes.push(i);
						while (!vertexes.empty()) {
							size_t vertex = vertexes.top();
							if (visited[vertex] == 2) {
								vertexes.pop();
								continue;
							}
							if (visited[vertex] == 1) {
								visited[vertex] = 2;
								sorted.push_back(vertex);
								vertexes.pop();
								continue;
							}
							visited[vertex] = 1;
							for (const int neighbour : adjacency_list[vertex]) {
								if (visited[neighbour] == 1)
									return {};
								if (visited[neighbour] == 0)
									vertexes.push(neighbour);
							}
						}
					}
				reverse(sorted.begin(), sorted.end());
				return sorted;
			}
		};

	}

	namespace task_213 {
		/*
		* https://leetcode.com/problems/house-robber-ii/description/
		*/
		class Solution {
		public:
			int rob(vector<int>& nums) {
				size_t size = nums.size() - 1; // -1 to not write -1 everywhere
				if (size == 0)
					return nums[0];
				if (size == 1)
					return max(nums[0], nums[1]);
				if (size == 2)
					return max(nums[0], max(nums[1], nums[2]));
				if (size == 3)
					return max(nums[0] + nums[2], nums[1] + nums[3]);

				int sum = 0, sum_1 = nums[0] + nums[3], sum_2 = nums[0] + nums[2], sum_3 = 0; // for tracking with nums[0]
				nums[3] += nums[1]; // for tracking without nums[0]
				for (size_t i = 4; i < size; i++) {
					sum = nums[i] + max(sum_2, sum_3);
					sum_3 = sum_2;
					sum_2 = sum_1;
					sum_1 = sum;
					nums[i] += max(nums[i - 2], nums[i - 3]);
				}
				nums[size] += max(nums[size - 2], nums[size - 3]);

				return max(max(nums[size - 1], nums[size]), max(sum_1, sum_2));
			}
		};
	}

	namespace task_214 {
		/*
		* https://leetcode.com/problems/shortest-palindrome/description/
		*/
		class Solution {
		public:
			string shortestPalindrome(string s) {
				size_t size = s.size(), end = size - 1;
				if (size < 2)
					return s;

				for (; end > 0; --end) {
					if (s[0] == s[end]) {
						size_t to = 1 + end >> 1, i = 1;
						for (; i < to && s[i] == s[end - i]; ++i) {}
						if (i == to)
							break;
					}
				}

				auto left = s.substr(end + 1);
				reverse(left.begin(), left.end());
				return left + s;
			}
		};
	}

	namespace task_216 {
		/*
		* https://leetcode.com/problems/combination-sum-iii/description/
		*/
		class Solution {
		public:
			vector<vector<int>> combinationSum3(int k, int n) {
				return combinationSumReq(1, k, n);
			}

			vector<vector<int>> combinationSumReq(const int from, const int count, const int target) {
				if (from > target || from == 10 || count == 0)
					return vector<vector<int>>();
				if (from == target && count == 1)
					return vector<vector<int>>(1, vector<int>(1, target));

				auto vectorsWith = combinationSumReq(from + 1, count - 1, target - from);
				auto vectorsWithout = combinationSumReq(from + 1, count, target);
				for (auto& vec : vectorsWith)
					vec.push_back(from);
				for (auto& vec : vectorsWithout)
					vectorsWith.push_back(vec);

				return vectorsWith;
			}
		};
	}

	namespace task_217 {
		/*
		* https://leetcode.com/problems/contains-duplicate/
		*/
		class Solution {
		public:
			bool containsDuplicate(vector<int>& nums) {
				unordered_set<int> set;
				for (int n : nums) {
					if (set.contains(n))
						return true;
					set.insert(n);
				}
				return false;
			}
		};
	}

	namespace task_219 {
		/*
		* https://leetcode.com/problems/contains-duplicate-ii/
		*/
		class Solution {
		public:
			bool containsNearbyDuplicate(vector<int>& nums, int k) {
				if (k == 0)
					return false;
				int size = nums.size(), i = 0;
				if (k >= size)
					return containsDuplicate(nums);
				unordered_set<int> set;
				vector<int> queue(k);
				int front = 0;
				for (; i < k; ++i) {
					if (set.contains(nums[i]))
						return true;
					queue[i] = nums[i];
					set.insert(nums[i]);
				}
				for (; i < size; ++i) {
					if (set.contains(nums[i]))
						return true;
					set.erase(queue[front]);
					queue[front] = nums[i];
					front = (front + 1) % k;
					set.insert(nums[i]);
				}
				return false;
			}

			bool containsDuplicate(vector<int>& nums) {
				unordered_set<int> set;
				for (int n : nums) {
					if (set.contains(n))
						return true;
					set.insert(n);
				}
				return false;
			}
		};
	}

	namespace task_221 {
		/*
		* https://leetcode.com/problems/maximal-square/description/
		*/
		class Solution {
		public:
			int maximalSquare(vector<vector<char>>& matrix) {
				const size_t m = matrix.size();
				const size_t n = matrix[0].size();
				vector<vector<int>> square_matrix(m, vector<int>(n));
				for (size_t i = 0; i < m; i++)
					square_matrix[i][0] = matrix[i][0] - '0';
				for (size_t j = 1; j < n; j++)
					square_matrix[0][j] = matrix[0][j] - '0';

				for (size_t i = 1; i < m; i++)
					for (size_t j = 1; j < n; j++)
						if (matrix[i][j] == '1')
							square_matrix[i][j] = 1 + min(min(square_matrix[i - 1][j], square_matrix[i][j - 1]), square_matrix[i - 1][j - 1]);

				int max_size = 0;
				for (size_t i = 0; i < m; i++)
					for (size_t j = 0; j < n; j++)
						if (max_size < square_matrix[i][j])
							max_size = square_matrix[i][j];
				return max_size * max_size;
			}
		};
	}

	namespace task_222 {
		/*
		* https://leetcode.com/problems/special-array-i/description/
		*/
		class Solution {
		public:
			int countNodes(TreeNode* root) {
				if (!root)
					return 0;
				queue<TreeNode*> queue;
				queue.push(root);
				int count = 1;
				while (!queue.empty()) {
					root = queue.front();
					queue.pop();
					if (root->left)
						queue.push(root->left);
					else
						return count;
					if (root->right)
						queue.push(root->right);
					else
						return count + 1;
					count += 2;
				}
				return count;
			}
		};
	}

	namespace task_225 {
		/*
		* https://leetcode.com/problems/implement-stack-using-queues/description/
		*/
		class MyStack {
		public:
			queue<int> q;
			void push(int x) {
				q.push(x);
				for (int i = 0; i < q.size() - 1; i++) {
					q.push(q.front());
					q.pop();
				}
			}

			int pop() {
				int result = q.front();
				q.pop();
				return result;
			}

			int top() {
				return q.front();
			}

			bool empty() {
				return q.empty();
			}
		};
	}

	namespace task_226 {
		/*
		* https://leetcode.com/problems/invert-binary-tree/description/
		*/
		class Solution {
		public:
			TreeNode* invertTree(TreeNode* root) {
				if (root) {
					swap(root->left, root->right);
					invertTree(root->left);
					invertTree(root->right);
				}
				return root;
			}
		};
	}

	namespace task_229 {
		/*
		* https://leetcode.com/problems/majority-element-ii/description/
		*/
		class Solution {
		public:
			vector<int> res;
			int size;

			vector<int> majorityElement(vector<int>& nums) {
				size = nums.size();
				int from = 0, to = size - 1, less = from, more = to;
				res = vector<int>();
				majorityElementReq(nums, 0, size - 1);
				return res;
			}

			void majorityElementReq(vector<int>& nums, const int from, const int to) {
				int middle = nums[from], less = from, more = to;
				for (int i = from + 1; i <= more; ) {
					if (middle < nums[i]) {
						swap(nums[i], nums[more]);
						--more;
					}
					else {
						if (middle > nums[i]) {
							swap(nums[i], nums[less]);
							++less;
						}
						++i;
					}
				}
				if ((more - less + 1) * 3 > size)
					res.push_back(middle);
				if ((less - from) * 3 > size)
					majorityElementReq(nums, from, less - 1);
				if ((to - more) * 3 > size)
					majorityElementReq(nums, more + 1, to);
			}

			vector<int> majorityElement__faster(vector<int>& nums) {
				int count1 = 0, count2 = 0; // Counters for the potential majority elements
				int candidate1 = 0, candidate2 = 0; // Potential majority element candidates

				// First pass to find potential majority elements.
				for (int i = 0; i < nums.size(); i++) {
					// If count1 is 0 and the current number is not equal to candidate2, update candidate1.
					if (count1 == 0 && nums[i] != candidate2) {
						count1 = 1;
						candidate1 = nums[i];
					}
					// If count2 is 0 and the current number is not equal to candidate1, update candidate2.
					else if (count2 == 0 && nums[i] != candidate1) {
						count2 = 1;
						candidate2 = nums[i];
					}
					// Update counts for candidate1 and candidate2.
					else if (candidate1 == nums[i]) {
						count1++;
					}
					else if (candidate2 == nums[i]) {
						count2++;
					}
					// If the current number is different from both candidates, decrement their counts.
					else {
						count1--;
						count2--;
					}
				}

				vector<int> result;
				int threshold = nums.size() / 3; // Threshold for majority element

				// Second pass to count occurrences of the potential majority elements.
				count1 = 0, count2 = 0;
				for (int i = 0; i < nums.size(); i++) {
					if (candidate1 == nums[i])
						count1++;
					else if (candidate2 == nums[i])
						count2++;
				}

				// Check if the counts of potential majority elements are greater than n/3 and add them to the result.
				if (count1 > threshold)
					result.push_back(candidate1);
				if (count2 > threshold)
					result.push_back(candidate2);

				return result;
			}
		};
	}

	namespace task_231 {
		/*
		* https://leetcode.com/problems/power-of-two/description/
		*/
		class Solution {
		public:
			bool isPowerOfTwo(int n) {
				if (n < 1)
					return false;
				while (n % 2 == 0)
					n >>= 1;
				return n == 1;
			}
		};
	}

	namespace task_232 {
		/*
		* https://leetcode.com/problems/implement-queue-using-stacks/description/
		*/
		class MyQueue {
		public:
			queue<int> in_stack;
			queue<int> out_stack;

			void push(int x) {
				in_stack.push(x);
			}

			int pop() {
				int res = peek();
				out_stack.pop();
				return res;
			}

			int peek() {
				if (out_stack.empty()) {
					while (!in_stack.empty())
					{
						out_stack.push(in_stack.front());
						in_stack.pop();
					}
				}
				return out_stack.front();
			}

			bool empty() {
				return in_stack.empty() && out_stack.empty();
			}
		};

		class MyStack {
		public:
			queue<int> q;
			void push(int x) {
				q.push(x);
				for (int i = 0; i < q.size() - 1; i++) {
					q.push(q.front());
					q.pop();
				}
			}

			int pop() {
				int result = q.front();
				q.pop();
				return result;
			}

			int top() {
				return q.front();
			}

			bool empty() {
				return q.empty();
			}
		};
	}

	namespace task_234 {
		/*
		* https://leetcode.com/problems/palindrome-linked-list/
		*/
		class Solution {
		public:
			bool isPalindrome(ListNode* head) {
				if (!head->next)
					return true;
				ListNode* ptr = head->next;
				size_t size = 1;
				for (; ptr; ptr = ptr->next, ++size) {}
				ptr = head;
				ListNode* temp, * next = head->next;
				ptr->next = nullptr;
				size_t half = size >> 1;
				for (size_t i = 1; i < half; ++i) {
					temp = next->next;
					next->next = ptr;
					ptr = next;
					next = temp;
				}
				if (size & 1)
					next = next->next;
				for (; ptr; ptr = ptr->next, next = next->next)
					if (ptr->val != next->val)
						return false;
				return true;
			}
		};
	}

	namespace task_237 {
		/*
		* https://leetcode.com/problems/remove-linked-list-elements/
		*/
		class Solution {
		public:
			void deleteNode(ListNode* node) {
				node->val = node->next->val;
				node->next = node->next->next;
			}
		};
	}

	namespace task_239 {
		/*
		* https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/
		*/
		class Solution {
		public:
			vector<int> longestSubarrayLinear(vector<int>& nums, int k) {
				deque<int> maxDeque;
				size_t size = nums.size(), left = 0, right = 0;
				vector<int> differences(size - k + 1);

				for (; right < k; ++right) {
					int value = nums[right];
					while (!maxDeque.empty() && value > maxDeque.back())
						maxDeque.pop_back();
					maxDeque.push_back(value);
				}
				differences[0] = maxDeque.front();

				for (; right < size; ++right) {
					int value = nums[right];
					while (!maxDeque.empty() && value > maxDeque.back())
						maxDeque.pop_back();
					maxDeque.push_back(value);

					if (nums[left] == maxDeque.front())
						maxDeque.pop_front();
					++left;

					differences[left] = maxDeque.front();
				}

				return differences;
			}
		};
	}

	namespace task_240 {
		/*
		* https://leetcode.com/search-a-2d-matrix-ii/
		*/
		class Solution {
		public:
			bool searchMatrix(vector<vector<int>>& matrix, int target) {
				for (size_t i = 0; i < matrix.size(); i++) {
					int j = bin_search(matrix[i], target);
					if (j != -1)
						return true;
				}
				return false;
			}

			int bin_search(vector<int>& nums, int target) {
				size_t l = 0;
				size_t r = nums.size();

				if (nums[l] == target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == target)
						return i;
					if (nums[i] > target)
						r = i;
					else
						l = i;
				}
				return -1;
			}
		};
	}

	namespace task_241 {
		/*
		* https://leetcode.com/problems/different-ways-to-add-parentheses/description/
		*/
		class Solution {
		public:
			vector<int> diffWaysToCompute(string expression) {
				int n = expression.length();
				// Create a 2D array of lists to store results of subproblems
				vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));

				initializeBaseCases(expression, dp);

				// Fill the dp table for all possible subexpressions
				for (int length = 3; length <= n; length++) {
					for (int start = 0; start + length - 1 < n; start++) {
						int end = start + length - 1;
						processSubexpression(expression, dp, start, end);
					}
				}

				// Return the results for the entire expression
				return dp[0][n - 1];
			}

			void initializeBaseCases(string& expression,
				vector<vector<vector<int>>>& dp) {
				int n = expression.length();
				// Handle base cases: single digits and two-digit numbers
				for (int i = 0; i < n; i++) {
					if (isdigit(expression[i])) {
						// Check if it's a two-digit number
						int dig1 = expression[i] - '0';
						if (i + 1 < n && isdigit(expression[i + 1])) {
							int dig2 = expression[i + 1] - '0';
							int number = dig1 * 10 + dig2;
							dp[i][i + 1].push_back(number);
						}
						// Single digit case
						dp[i][i].push_back(dig1);
					}
				}
			}

			void processSubexpression(string& expression,
				vector<vector<vector<int>>>& dp, int start,
				int end) {
				// Try all possible positions to split the expression
				for (int split = start; split <= end; split++) {
					if (isdigit(expression[split])) continue;

					vector<int> leftResults = dp[start][split - 1];
					vector<int> rightResults = dp[split + 1][end];

					computeResults(expression[split], leftResults, rightResults,
						dp[start][end]);
				}
			}

			void computeResults(char op, vector<int>& leftResults,
				vector<int>& rightResults, vector<int>& results) {
				// Compute results based on the operator at position 'split'
				for (int leftValue : leftResults) {
					for (int rightValue : rightResults) {
						switch (op) {
						case '+':
							results.push_back(leftValue + rightValue);
							break;
						case '-':
							results.push_back(leftValue - rightValue);
							break;
						case '*':
							results.push_back(leftValue * rightValue);
							break;
						}
					}
				}
			}
		};
	}

	namespace task_260 {
		/*
		* https://leetcode.com/problems/single-number-iii/
		*/
		class Solution {
		public:
			vector<int> singleNumber(vector<int>& nums) {
				int xor_a_b = 0, a = 0, b = 0;
				for (const int n : nums)
					xor_a_b ^= n;

				int i = 1;
				for (; (xor_a_b & i) == 0; i <<= 1) {}

				for (const int n : nums)
					if (n & i)
						a ^= n;
					else
						b ^= n;
				return { a , b };
			}
		};
	}

	namespace task_263 {
		/*
		* https://leetcode.com/problems/ugly-number/description/
		*/
		class Solution {
		public:
			bool isUgly(int n) {
				if (n < 1)
					return false;
				if (n < 7)
					return true;
				while (n % 2 == 0)
					n >>= 1;
				while (n % 3 == 0)
					n /= 3;
				while (n % 5 == 0)
					n /= 5;
				return n == 1;
			}
		};
	}

	namespace task_264 {
		/*
		* https://leetcode.com/problems/ugly-number-ii/description/
		*/
		class Solution {
		public:

			int nthUglyNumber(int n) {
				if (n < 7)
					return n;
				long long number = 1;
				set<long long> numbers{ 1 };
				for (int i = 0; i < n; i++) {
					number = *numbers.begin();
					numbers.erase(numbers.begin());

					numbers.insert(number * 2);
					numbers.insert(number * 3);
					numbers.insert(number * 5);
				}
				return number;
			}
		};
	}

	namespace task_268 {
		/*
		* https://leetcode.com/problems/missing-number/
		*/
		class Solution {
		public:
			int missingNumberXOR(vector<int>& nums) { // 51.71%-56.98%
				size_t size = nums.size() + 1;
				int res = 0;
				for (int i = 1; i < size; ++i)
					res ^= i;
				for (const int n : nums)
					res ^= n;
				return res;
			}

			int missingNumberSum(vector<int>& nums) { // 81.24%-56.98%
				int n = nums.size(), sum = 0;
				for (const int n : nums)
					sum += n;
				return (n * (n + 1) >> 1) - sum;
			}

			int missingNumber(vector<int>& nums) { // 68.07%-31.13%
				nums.push_back(-1);
				int size = nums.size();
				for (int i = 0; i < size; ++i)
					while (nums[i] != -1 && nums[i] != i)
						swap(nums[i], nums[nums[i]]);
				for (int i = 0; i < size; ++i)
					if (nums[i] == -1)
						return i;
				return 0;
			}
		};
	}

	namespace task_273 {
		/*
		* https://leetcode.com/integer-to-english-words/description/
		*/
		class Solution {
		public:
			string numberToWords(int num) {
				if (num == 0)
					return "Zero";
				string res = parse3Numbers(num % 1000);
				num /= 1000;
				if (num == 0)
					return res;
				string leftPart = parse3Numbers(num % 1000);
				if (leftPart.size() > 0)
					res = res.size() == 0 ?
					leftPart + " Thousand" :
					leftPart + " Thousand " + res;
				num /= 1000;
				if (num == 0)
					return res;
				leftPart = parse3Numbers(num % 1000);
				if (leftPart.size() > 0)
					res = res.size() == 0 ?
					leftPart + " Million" :
					leftPart + " Million " + res;
				num /= 1000;
				if (num == 0)
					return res;
				return res.size() == 0 ?
					parse3Numbers(num % 1000) + " Billion" :
					parse3Numbers(num % 1000) + " Billion " + res;
			}

			string parse3Numbers(int num) {
				int hundreds = num / 100;
				num %= 100;
				string units = num < 20 ?
					getNumber1_19(num) :
					num % 10 == 0 ?
					getNumber20_90(num / 10) :
					getNumber20_90(num / 10) + " " + getNumber1_19(num % 10);
				return hundreds ?
					units.size() == 0 ?
					getNumber1_19(hundreds) + " Hundred" :
					getNumber1_19(hundreds) + " Hundred " + units :
					units;
			}

			string getNumber1_19(const int num) {
				switch (num)
				{
				case 1:
					return "One";
				case 2:
					return "Two";
				case 3:
					return "Three";
				case 4:
					return "Four";
				case 5:
					return "Five";
				case 6:
					return "Six";
				case 7:
					return "Seven";
				case 8:
					return "Eight";
				case 9:
					return "Nine";
				case 10:
					return "Ten";
				case 11:
					return "Eleven";
				case 12:
					return "Twelve";
				case 13:
					return "Thirteen";
				case 14:
					return "Fourteen";
				case 15:
					return "Fifteen";
				case 16:
					return "Sixteen";
				case 17:
					return "Seventeen";
				case 18:
					return "Eighteen";
				case 19:
					return "Nineteen";
				default:
					return "";
				}
			}

			string getNumber20_90(const int num) {
				switch (num)
				{
				case 2:
					return "Twenty";
				case 3:
					return "Thirty";
				case 4:
					return "Forty";
				case 5:
					return "Fifty";
				case 6:
					return "Sixty";
				case 7:
					return "Seventy";
				case 8:
					return "Eighty";
				case 9:
					return "Ninety";
				default:
					return "";
				}
			}
		};
	}

	namespace task_274 {
		/*
		* https://leetcode.com/problems/h-index/description/
		*/
		class Solution {
		public:
			int hIndex(vector<int>& citations) {
				sort(citations.begin(), citations.end());
				size_t size = citations.size();
				int l = -1;
				size_t r = size - 1;
				if (citations[r] < 1)
					return 0;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (citations[i] >= size - i)
						r = i;
					else
						l = i;
				}
				return size - r;
			}
		};
	}

	namespace task_275 {
		/*
		* https://leetcode.com/problems/h-index/description/
		*/
		class Solution {
		public:
			int hIndex(vector<int>& citations) {
				size_t size = citations.size();
				int l = -1;
				size_t r = size - 1;
				if (citations[r] < 1)
					return 0;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (citations[i] >= size - i)
						r = i;
					else
						l = i;
				}
				return size - r;
			}
		};
	}

	namespace task_278 {
		/*
		* https://leetcode.com/sqrtx/description/
		*/
		bool isBadVersion(int version);

		class Solution {
		public:
			int firstBadVersion(int n) {
				int left = 1, right = n;
				while (left < right) {
					int mid = left + (right - left) / 2;
					if (isBadVersion(mid)) { right = mid; }
					else { left = mid + 1; }
				}

				return right;
			}
		};
	}

	namespace task_283 {
		/*
		* https://leetcode.com/problems/move-zeroes/
		*/
		class Solution {
		public:
			void moveZeroes(vector<int>& nums) {
				const size_t size = nums.size();
				if (size < 2)
					return;
				for (size_t i = 0; i < size - 1; i++) {
					if (nums[i] == 0) {
						size_t j = i + 1;
						while (j < size && nums[j] == 0)
							++j;
						if (j == size)
							return;
						swap(nums[i], nums[j]);
					}
				}
			}
		};
	}

	namespace task_287 {
		/*
		* https://leetcode.com/problems/find-the-duplicate-number/description/
		*/
		class Solution {
		public:
			int findDuplicateSameAsMy(vector<int>& nums) {
				int slow = nums[0], fast = slow;
				do {
					slow = nums[slow];
					fast = nums[nums[fast]];
				} while (slow != fast);
				slow = nums[0];
				while (slow != fast) {
					slow = nums[slow];
					fast = nums[fast];
				}

				return slow;
			}

			int findDuplicateMy(vector<int>& nums) {
				int fast = nums.size() - 1;
				int slow = fast;
				do {
					fast = nums[fast] - 1;
					fast = nums[fast] - 1;
					slow = nums[slow] - 1;
				} while (slow != fast);
				int ptr = nums.size() - 1;
				while (ptr != slow) {
					ptr = nums[ptr] - 1;
					slow = nums[slow] - 1;
				}
				return ptr + 1;
			}
		};
	}

	namespace task_300 {
		/*
		* https://leetcode.com/problems/longest-increasing-subsequence/description/
		*/
		class Solution {
		public:
			int lengthOfLIS(vector<int>& nums) {
				const size_t size = nums.size();
				size_t length = 0;
				vector<int> ends_of_LIS(size, INT_MAX);

				for (size_t i = 0; i < size; i++) {
					size_t j = search(ends_of_LIS, length, nums[i]);
					ends_of_LIS[j] = min(ends_of_LIS[j], nums[i]);
					length = max(j + 1, length);
				}

				return length;
			}

			size_t search(vector<int>& nums, size_t r, const int target) {
				size_t l = 0;
				if (nums[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_309 {
		/*
		* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
		*/
		class Solution {
		public:
			int maxProfit_copy(vector<int>& prices) {
				int prev_prev_buy = 0, prev_buy = 0, curr_buy = 0;
				int prev_sell = 0, curr_sell = 0;
				for (int i = prices.size() - 1; i >= 0; --i)
				{
					curr_buy = max(-prices[i] + prev_sell, prev_buy);
					curr_sell = max(prices[i] + prev_prev_buy, prev_sell);
					prev_prev_buy = prev_buy;
					prev_buy = curr_buy;
					prev_sell = curr_sell;
				}
				return curr_buy;
			}

			int maxProfit(vector<int>& prices) {
				const size_t size = prices.size();
				if (size < 2)
					return 0;
				vector<int> profits(size);
				profits[0] = 0;
				profits[1] = max(0, prices[1] - prices[0]);
				int result = max(0, profits[1]);

				for (int i = 2; i < size; i++) {
					int buy_i = i - 1;
					int min_buy = prices[buy_i];
					int max_profit = max(-prices[1], -prices[0]);
					for (int last_sell = buy_i - 2; last_sell >= 0; --last_sell, --buy_i) {
						min_buy = min(prices[buy_i], min_buy);
						max_profit = max(max_profit, profits[last_sell] - min_buy);
					}
					profits[i] = max(0, max_profit + prices[i]);
					result = max(result, profits[i]);
				}
				return result;
			}
		};
	}

	namespace task_316 {
		/*
		* https://leetcode.com/problems/remove-duplicate-letters/description/
		*/
		class Solution {
		public:
			vector<int> count_letters;
			vector<int> added;
			const size_t size_letters = 'z' - 'a' + 1;

			string removeDuplicateLetters(string s) {
				count_letters = vector<int>(size_letters);
				added = vector<int>(size_letters);
				for (const char c : s)
					++count_letters[c - 'a'];

				string res;
				for (const char c : s) {
					--count_letters[c - 'a'];
					if (added[c - 'a'] == 1)
						continue;

					int i = res.size() - 1;
					for (; i >= 0 &&
						res[i] > c &&
						count_letters[res[i] - 'a'] > 0; --i) {
						added[res[i] - 'a'] = 0;
					}

					++i;
					if (i == res.size())
						res.push_back(c);
					else {
						res[i] = c;
						res.erase(i + 1);
					}
					added[c - 'a'] = 1;
				}

				return res;
			}

			string removeDuplicateLetters1(string s) {
				count_letters = vector<int>(size_letters);
				added = vector<int>(size_letters);
				vector<int> res(size_letters);
				size_t size = s.size();
				int res_size = 0;
				for (size_t i = 0; i < s.length(); ++i)
					count_letters[s[i] - 'a'] = i;

				for (size_t i = 0; i < s.length(); ++i) {
					int c = s[i] - 'a';
					if (added[c] == 1)
						continue;

					int j = res_size - 1;
					for (; j >= 0 &&
						res[j] > c &&
						count_letters[res[j]] > i; --j) {
						added[res[j]] = 0;
					}

					++j;
					res[j] = c;
					res_size = j + 1;
					added[c] = 1;
				}

				string str;
				for (int i = 0; i < res_size; ++i)
					str.push_back(res[i] + 'a');

				return str;
			}
		};
	}

	namespace task_319 {
		/*
		* https://leetcode.com/problems/bulb-switcher/description/
		*/
		class Solution {
		public:
			int bulbSwitchFastest(int n) {
				return sqrt(n);
			}

			int bulbSwitchFaster(int n) {
				int sum = 0, count = 0;
				for (int i = 1; i <= n; i += 2) {
					sum += i;
					if (n < sum)
						break;
					++count;
				}
				return count;
			}

			vector<int> primes;
			long long _n;

			int bulbSwitch(int n) {
				if (n == 0)
					return 0;
				if (n < 4)
					return 1;
				_n = n;
				getPrimes();
				for (int& prime : primes)
					prime *= prime;
				int count = 1;

				return getCount(1, 0);
			}

			int getCount(long long base, size_t from) {
				if (from == primes.size())
					return 1;
				int count = 0;
				while (base <= _n) {
					count += getCount(base, from + 1);
					base *= primes[from];
				}
				return count;
			}

			vector<int> getPrimes() {
				primes = vector<int>{ 2 };
				int i = 3, to = sqrt(_n) + 1;
				for (; i < to; ++i) {
					bool isPrime = true;
					for (const int p : primes)
						if (i % p == 0) {
							isPrime = false;
							break;
						}
					if (isPrime)
						primes.push_back(i);
				}
				return primes;
			}
		};
	}

	namespace task_328 {
		/*
		* https://leetcode.com/problems/odd-even-linked-list/
		*/
		class Solution {
		public:
			ListNode* oddEvenList(ListNode* head) {
				if (!head || !head->next || !head->next->next)
					return head;
				ListNode* oddTail = head->next->next, * evenHead = head->next, * evenTail = head->next;
				head->next = oddTail;
				while (oddTail->next && oddTail->next->next) {
					evenTail->next = oddTail->next;
					evenTail = oddTail->next;
					oddTail->next = evenTail->next;
					oddTail = evenTail->next;
				}
				if (oddTail->next)
					evenTail->next = oddTail->next;
				else
					evenTail->next = nullptr;
				oddTail->next = evenHead;
				return head;
			}
		};
	}

	namespace task_330 {
		/*
		* https://leetcode.com/problems/problems/patching-array/description/
		*/
		class Solution {
		public:
			int minPatches(vector<int>& nums, int n) {
				size_t size = nums.size(), i = 0;
				long long next_sum = 1;
				int count = 0;
				while (next_sum <= n)
					if (i < size && nums[i] <= next_sum) {
						next_sum += nums[i];
						++i;
					}
					else {
						next_sum <<= 1;
						++count;
					}
				return count;
			}
		};
	}

	namespace task_337 {
		/*
		* https://leetcode.com/problems/house-robber-iii/description/
		*/
		class Solution {
		public:
			int rob(TreeNode* root) {
				auto p = robChild(root);
				return max(p.first, p.second);
			}

			pair<int, int> robChild(TreeNode* root) {
				if (!root)
					return { 0, 0 };

				auto left = robChild(root->left);
				auto right = robChild(root->right);
				return { root->val + left.second + right.second, max(left.first, left.second) + max(right.first, right.second) };
			}
		};
	}

	namespace task_338 {
		/*
		* https://leetcode.com/problems/counting-bits/
		*/
		class Solution {
		public:
			vector<int> countBits(int n) {
				vector<int> ans(n + 1);
				for (int i = 1; i < n + 1; ++i) {
					int count = 0;
					for (int num = i; num != 0; num >>= 1)
						count += num & 1;
					ans[i] = count;
				}

				return ans;
			}
		};
	}

	namespace task_341 {
		/*
		* https://leetcode.com/problems/flatten-nested-list-iterator/description/
		*/
		class NestedInteger {
		public:
			vector<NestedInteger> nodes;
			int value;

			bool isInteger() const {
				return nodes.empty();
			}

			int getInteger() const {
				return value;
			}

			const vector<NestedInteger>& getList() const {
				return nodes;
			}
		};

		class NestedIterator {
		public:
			vector<int> values;
			size_t index = 0;

			NestedIterator(vector<NestedInteger>& nestedList) {
				stack<NestedInteger> stack;
				for (int i = nestedList.size() - 1; i >= 0; --i)
					stack.push(nestedList[i]);
				while (!stack.empty()) {
					NestedInteger node = stack.top();
					stack.pop();
					if (node.isInteger())
						values.push_back(node.getInteger());
					else {
						const vector<NestedInteger>& nodes = node.getList();
						for (int i = nodes.size() - 1; i >= 0; --i)
							stack.push(nodes[i]);
					}
				}
			}

			int next() {
				return values[index++];
			}

			bool hasNext() {
				return index < values.size();
			}
		};
	}

	namespace task_342 {
		/*
		* https://leetcode.com/problems/power-of-four/description/
		*/
		class Solution {
		public:
			bool isPowerOfFour(int n) {
				if (n < 1)
					return false;
				while ((~n & 3) == 3)
					n >>= 2;
				return n == 1;
			}

			bool isPowerOfFour__bit_magic(int n) {
				int mask = 0b01010101010101010101010101010101;
				return n > 0 && (n & (n - 1)) == 0 && (n | mask) == mask;
			}
		};
	}

	namespace task_344 {
		/*
		* https://leetcode.com/problems/reverse-string/description/
		*/
		class Solution {
		public:
			void reverseString(vector<char>& s) {
				size_t size = s.size();
				char t;
				for (size_t i = size >> 1; i < size; ++i) {
					t = s[i];
					s[i] = s[size - i - 1];
					s[size - i - 1] = t;
				}
			}

			void reverseString2(vector<char>& s) {
				reverse(s.begin(), s.end());
			}
		};
	}

	namespace task_345 {
		/*
		* https://leetcode.com/problems/reverse-vowels-of-a-string/
		*/
		class Solution {
		public:
			string reverseVowelsFaster(string s) {
				size_t i = 0, j = s.size() - 1;
				char t;
				while (i < j) {
					t = s[i];
					if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u' ||
						t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U') {
						while (i < j) {
							t = s[j];
							if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u' ||
								t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U') {
								s[j] = s[i];
								s[i] = t;
								--j;
								break;
							}
							--j;
						}
					}
					++i;
				}
				return s;
			}

			string reverseVowels(string s) {
				vector<int> indexes;
				size_t size = s.size();
				char t;
				for (size_t i = 0; i < size; ++i) {
					t = s[i];
					if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u' ||
						t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U')
						indexes.push_back(i);
				}

				size = indexes.size();
				for (size_t i = size >> 1; i < size; ++i) {
					t = s[indexes[i]];
					s[indexes[i]] = s[indexes[size - i - 1]];
					s[indexes[size - i - 1]] = t;
				}
				return s;
			}
		};
	}

	namespace task_349 {
		/*
		* https://leetcode.com/problems/intersection-of-two-arrays/description/
		*/
		class Solution {
		public:
			vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
				sort(nums1.begin(), nums1.end());
				sort(nums2.begin(), nums2.end());
				vector<int> intersection;
				for (size_t i = 0, j = 0; i < nums1.size() && j < nums2.size();) {
					if (nums1[i] == nums2[j]) {
						if (intersection.empty() || intersection.back() != nums1[i])
							intersection.push_back(nums1[i]);
						++i, ++j;
					}
					else if (nums1[i] < nums2[j])
						++i;
					else
						++j;
				}
				return intersection;
			}
		};
	}

	namespace task_350 {
		/*
		* https://leetcode.com/problems/intersection-of-two-arrays-ii/description/
		*/
		class Solution {
		public:
			vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
				sort(nums1.begin(), nums1.end());
				sort(nums2.begin(), nums2.end());
				vector<int> intersection;
				for (size_t i = 0, j = 0; i < nums1.size() && j < nums2.size();) {
					if (nums1[i] == nums2[j]) {
						intersection.push_back(nums1[i]);
						++i, ++j;
					}
					else if (nums1[i] < nums2[j])
						++i;
					else
						++j;
				}
				return intersection;
			}
		};
	}

	namespace task_354 {
		/*
		* https://leetcode.com/problems/russian-doll-envelopes/description/
		*/
		class Solution {
		public:
			class Node {
			public:
				Node(const vector<int>& envelope) : widht(envelope[0]), height(envelope[1]) {}
				int widht;
				int height;
				Node* left = nullptr;
				Node* right = nullptr;
			};
			Node* tree;
			vector<Node*> to_delete;

			// sort by widht and then solve LIS for the height
			int maxEnvelopes(vector<vector<int>>& envelopes) {
				set<vector<int>> envelopes_set;
				const size_t size = envelopes.size();
				for (size_t i = 0; i < size; i++)
					envelopes_set.insert(envelopes[i]);

				map<int, int> heights_inserted;
				int max_inserted = 0;
				int current_widht = 0;
				stack<pair<size_t, int>> heights;
				vector<int> height_of_inserted(envelopes_set.size(), INT_MAX);

				for (const vector<int>& envelope : envelopes_set) {
					if (current_widht != envelope[0]) {
						while (!heights.empty()) {
							const pair<int, int>& height = heights.top();
							max_inserted = max(height.first + 1, max_inserted);
							height_of_inserted[height.first] = min(height_of_inserted[height.first], height.second);
							heights.pop();
						}
						current_widht = envelope[0];
					}

					size_t count_inserted = search(height_of_inserted, max_inserted, envelope[1]);
					heights.push({ count_inserted, envelope[1] });
				}

				while (!heights.empty()) {
					const pair<int, int>& height = heights.top();
					max_inserted = max(height.first + 1, max_inserted);
					height_of_inserted[height.first] = min(height_of_inserted[height.first], height.second);
					heights.pop();
				}

				return max_inserted;
			}

			size_t search(vector<int>& nums, size_t r, const int target) {
				size_t l = 0;
				if (nums[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}

			Node* merge(Node* a, Node* b) {
				if (!a || !b)
					return a ? a : b;
				if (a->height >= b->height) {
					a->right = merge(a->right, b);
					return a;
				} else {
					b->left = merge(a, b->left);
					return b;
				}
			}

			void split(Node* n, int widht, Node*& a, Node*& b) {
				if (!n) {
					a = nullptr;
					b = nullptr;
					return;
				}
				if (n->widht < widht) {
					split(n->right, widht, n->right, b);
					a = n;
				}
				else {
					split(n->left, widht, a, n->left);
					b = n;
				}
			}

			void insert(const vector<int>& envelope) {
				Node* left, * right;
				split(tree, envelope[0], left, right);
				tree = merge(left, merge(new Node(envelope), right));
			}

			int dfs(Node* n) {
				if (!n)
					return 0;
				to_delete.push_back(n);
				return max(dfs(n->left) + 1, dfs(n->right));
			}

			int maxEnvelopesTree(vector<vector<int>>& envelopes) {
				set<vector<int>> envelopes_set;
				const size_t size = envelopes.size();
				tree = nullptr;
				to_delete.clear();
				for (size_t i = 0; i < size; i++)
					envelopes_set.insert(envelopes[i]);

				for (const vector<int>& envelope : envelopes_set)
					insert(envelope);

				int res = dfs(tree);
				for (size_t i = 0; i < to_delete.size(); i++)
					delete to_delete[i];
				return res;
			}

			int maxEnvelopesSlow(vector<vector<int>>& envelopes) {
				vector<pair<map<int, int>, set<int>>> insertedEnvelopes;
				const size_t size = envelopes.size();
				sort(envelopes.begin(), envelopes.end());

				for (size_t i = 0; i < size; i++) {
					envelopes[i][0] = -envelopes[i][0];
					envelopes[i][1] = -envelopes[i][1];
					int j = insertedEnvelopes.size() - 1;
					for (; j >= 0; --j) {
						auto it = insertedEnvelopes[j].first.upper_bound(envelopes[i][0]);
						for (; it != insertedEnvelopes[j].first.end(); it++)
							if (it->second > envelopes[i][1])
								break;

						if (it != insertedEnvelopes[j].first.end())
							break;
					}
					++j;
					if (j == insertedEnvelopes.size())
						insertedEnvelopes.push_back({ map<int, int>(), set<int>() });
					auto it_set = insertedEnvelopes[j].second.upper_bound(envelopes[i][1]);
					if (it_set == insertedEnvelopes[j].second.end())
						insertedEnvelopes[j].first.insert({ envelopes[i][0], envelopes[i][1] });
				}

				return insertedEnvelopes.size();
			}
		};
	}

	namespace task_355 {
		/*
		* https://leetcode.com/problems/design-twitter/
		*/
		class Twitter {
		public:
			struct Node {
				int time;
				int val;
				Node* next;
				Node* prev;
				Node(int time, int x) : time(time), val(x), next(nullptr), prev(nullptr) {}
				Node(int time, int x, Node* next, Node* prev) : time(time), val(x), next(next), prev(prev) {}
			};

			unordered_map<int, pair<Node*, int>> users;
			unordered_map<int, set<int>> following;
			int time;
			const int max_feed_length = 10;


			Twitter() : time(0) { }
			~Twitter() {
				Node* ptr, * temp;
				for (auto& [key, val] : users) {
					ptr = val.first;
					for (size_t i = 0; i < val.second; i++) {
						temp = ptr;
						ptr = ptr->next;
						delete temp;
					}
				}
			}

			void postTweet(int userId, int tweetId) {
				if (auto it = users.find(userId); it != users.end()) {
					if (it->second.second == max_feed_length) {
						it->second.first = it->second.first->prev;
						it->second.first->time = ++time;
						it->second.first->val = tweetId;
					}
					else {
						auto node = new Node(++time, tweetId, it->second.first, it->second.first->prev);
						it->second.first->prev->next = node;
						it->second.first->prev = node;
						it->second.first = node;
					}
				}
				else {
					auto node = new Node(++time, tweetId);
					node->prev = node;
					node->next = node;
					users[userId] = { node, 1 };
					follow(userId, userId);
				}
			}

			vector<int> getNewsFeed(int userId) {
				vector<Node*> tweets;
				auto it_following = following.find(userId);
				if (it_following == following.end() || it_following->second.size() == 0)
					return vector<int>();
				for (const int followedId : it_following->second)
					if (auto it = users.find(followedId); it != users.end())
						tweets.push_back(it->second.first);
				vector<int> feed;
				int count_followed = tweets.size();
				while (feed.size() < max_feed_length && count_followed > 0) {
					int max_time = 0;
					int max_index = 0;
					for (size_t i = 0; i < count_followed; i++) {
						if (max_time < tweets[i]->time) {
							max_time = tweets[i]->time;
							max_index = i;
						}
					}
					feed.push_back(tweets[max_index]->val);
					tweets[max_index] = tweets[max_index]->next;
					if (tweets[max_index]->prev->time <= tweets[max_index]->time) {
						swap(tweets[max_index], tweets[count_followed - 1]);
						--count_followed;
					}
				}
				return feed;
			}

			void follow(int followerId, int followeeId) {
				if (auto it = following.find(followerId); it != following.end())
					it->second.insert(followeeId);
				else
					following[followerId] = set<int>({ followeeId });
			}

			void unfollow(int followerId, int followeeId) {
				if (auto it = following.find(followerId); it != following.end())
					it->second.erase(followeeId);
			}
		};
	}

	namespace task_367 {
		/*
		* https://leetcode.com/problems/valid-perfect-square/description/
		*/
		class Solution {
		public:
			bool isPerfectSquare(int num) {
				int left = 0, right = 46340;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					if (mid * mid == num) { return true; }
					else if (mid * mid > num) { right = mid - 1; }
					else { left = mid + 1; }
				}
				return right * right == num;;
			}
		};
	}

	namespace task_368 {
		/*
		* https://leetcode.com/problems/largest-divisible-subset/description/
		*/
		class Solution {
		public:
			vector<int> largestDivisibleSubset(vector<int>& nums) {
				int max_len = 0, max_num = 0, size = nums.size();
				unordered_map<int, pair<int, int>> set_by_number;
				sort(nums.begin(), nums.end());

				for (int i = 0; i < size; ++i) {
					int len = 0, divider = 0, num = nums[i];
					for (int j = i - 1; j >= 0; --j) {
						if (num % nums[j] == 0 && len < set_by_number[nums[j]].first) {
							len = set_by_number[nums[j]].first;
							divider = nums[j];
						}
					}
					++len;
					set_by_number[num] = { len, divider };
					if (max_len < len) {
						max_len = len;
						max_num = num;
					}
				}

				vector<int> res(max_len);
				for (int i = 0; i < max_len; ++i) {
					res[i] = max_num;
					max_num = set_by_number[max_num].second;
				}
				return res;
			}
		};
	}

	namespace task_374 {
		/*
		* https://leetcode.com/problems/guess-number-higher-or-lower/description/
		*/
		int guess(int num);

		class Solution {
		public:
			int guessNumber(int n) {
				int left = 0, right = n;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					int pick = guess(mid);
					if (pick == 0) { return mid; }
					else if (pick == 1) { left = mid + 1; }
					else { right = mid - 1; }
				}

				return -1;
			}
		};
	}

	namespace task_382 {
		/*
		* https://leetcode.com/problems/linked-list-random-node/
		*/
		class Solution {
		public:
			vector<int> nums;

			Solution(ListNode* head) {
				while (head) {
					nums.push_back(head->val);
					head = head->next;
				}
			}

			int getRandom() {
				return nums[rand() % nums.size()];
			}
		};
	}

	namespace task_386 {
		/*
		* https://leetcode.com/problems/lexicographical-numbers/description/
		*/
		class Solution {
		public:
			vector<int> lexicalOrder(int n) {
				vector<int> numbers;
				vector<int> bases(5);
				int last_base;
				++n;
				if (n < 10) {
					for (int i = 1; i < n; i++)
						numbers.push_back(i);
					return numbers;
				}

				for (int base = 1; base < 10; ++base) {
					last_base = 0;
					bases[last_base] = base * 10;
					numbers.push_back(base);
					while (last_base > -1) {
						if (bases[last_base] < n) {
							numbers.push_back(bases[last_base]);
							bases[last_base + 1] = bases[last_base] * 10;
							++last_base;
							continue;
						}
						--last_base;
						while (last_base > -1) {
							if (bases[last_base] % 10 == 9)
								--last_base;
							else {
								++bases[last_base];
								break;
							}
						}
					}
				}
				return numbers;
			}

			vector<int> lexicalOrder2(int n) {
				vector<int> lexicographicalNumbers;
				int currentNumber = 1;

				for (int i = 0; i < n; ++i) {
					lexicographicalNumbers.push_back(currentNumber);

					if (currentNumber * 10 <= n) {
						currentNumber *= 10;
					}
					else {
						while (currentNumber % 10 == 9 || currentNumber >= n)
							currentNumber /= 10;
						currentNumber += 1;
					}
				}

				return lexicographicalNumbers;
			}
		};
	}

	namespace task_392 {
		/*
		* https://leetcode.com/problems/is-subsequence/description/
		*/
		class Solution {
		public:
			bool isSubsequence(string s, string t) {
				size_t size_s = s.size(), size_t_ = t.size(), j = 0;
				if (size_s == 0)
					return true;
				for (size_t i = 0; i < size_t_; ++i) {
					if (t[i] == s[j]) {
						++j;
						if (j == size_s)
							return true;
					}
				}
				return false;
			}
		};
	}

	namespace task_398 {
		/*
		* https://leetcode.com/problems/random-pick-index/description/
		*/
		class Solution {
		public:
			unordered_map<int, vector<int>> nums_indexes;

			Solution(vector<int>& nums) {
				for (int i = 0; i < nums.size(); i++)
					if (auto it = nums_indexes.find(nums[i]); it != nums_indexes.end())
						it->second.push_back(i);
					else
						nums_indexes[nums[i]] = vector<int>({ i });
			}

			int pick(int target) {
				auto it = nums_indexes.find(target);
				return it->second[rand() % it->second.size()];
			}
		};
	}

	namespace task_407 {
		/*
		* https://leetcode.com/problems/trapping-rain-water-ii/description/
		*/
		class Solution {
		public:
			int trapRainWater__leeicode(vector<vector<int>>& heightMap) {
				// Direction arrays
				int dRow[4] = { 0, 0, -1, 1 };
				int dCol[4] = { -1, 1, 0, 0 };

				int numOfRows = heightMap.size();
				int numOfCols = heightMap[0].size();

				vector<vector<bool>> visited(numOfRows, vector<bool>(numOfCols, false));

				// Priority queue (min-heap) to process boundary cells in increasing
				// height order
				priority_queue<Cell> boundary;

				// Add the first and last column cells to the boundary and mark them as
				// visited
				for (int i = 0; i < numOfRows; i++) {
					boundary.push(Cell(heightMap[i][0], i, 0));
					boundary.push(Cell(heightMap[i][numOfCols - 1], i, numOfCols - 1));
					// Mark left and right boundary cells as visited
					visited[i][0] = visited[i][numOfCols - 1] = true;
				}

				// Add the first and last row cells to the boundary and mark them as
				// visited
				for (int i = 0; i < numOfCols; i++) {
					boundary.push(Cell(heightMap[0][i], 0, i));
					boundary.push(Cell(heightMap[numOfRows - 1][i], numOfRows - 1, i));
					// Mark top and bottom boundary cells as visited
					visited[0][i] = visited[numOfRows - 1][i] = true;
				}

				int totalWaterVolume = 0;

				while (!boundary.empty()) {
					// Pop the cell with the smallest height from the boundary
					Cell currentCell = boundary.top();
					boundary.pop();

					int currentRow = currentCell.row;
					int currentCol = currentCell.col;
					int minBoundaryHeight = currentCell.height;

					// Explore all 4 neighboring cells
					for (int direction = 0; direction < 4; direction++) {
						int neighborRow = currentRow + dRow[direction];
						int neighborCol = currentCol + dCol[direction];

						// Check if the neighbor is within the grid bounds and not yet
						// visited
						if (isValidCell(neighborRow, neighborCol, numOfRows,
							numOfCols) &&
							!visited[neighborRow][neighborCol]) {
							int neighborHeight = heightMap[neighborRow][neighborCol];

							// If the neighbor's height is less than the current
							// boundary height, water can be trapped
							if (neighborHeight < minBoundaryHeight) {
								totalWaterVolume += minBoundaryHeight - neighborHeight;
							}

							// Push the neighbor into the boundary with updated height
							// (to prevent water leakage)
							boundary.push(Cell(max(neighborHeight, minBoundaryHeight),
								neighborRow, neighborCol));
							visited[neighborRow][neighborCol] = true;
						}
					}
				}

				return totalWaterVolume;
			}

			// Struct to store the height and coordinates of a cell in the grid
			class Cell {
			public:
				int height;
				int row;
				int col;

				// Constructor to initialize a cell
				Cell(int height, int row, int col)
					: height(height), row(row), col(col) {}

				// Overload the comparison operator to make the priority queue a
				// min-heap based on height
				bool operator<(const Cell& other) const {
					// Reverse comparison to simulate a min-heap
					return height >= other.height;
				}
			};

			// Helper function to check if a cell is valid (within grid bounds)
			bool isValidCell(int row, int col, int numOfRows, int numOfCols) {
				return row >= 0 && col >= 0 && row < numOfRows&& col < numOfCols;
			}
		};
	}

	namespace task_409 {
		/*
		* https://leetcode.com/problems/longest-palindrome/description/
		*/
		class Solution {
		public:
			int longestPalindrome(string s) {
				vector<int> counts('z' - 'A' + 1);
				for (const char c : s)
					++counts[c - 'A'];
				int length = 0;
				bool has_odd = false;
				for (const int count : counts)
					if (count & 1) {
						has_odd = true;
						length += count - (count & 1);
					}
					else
						length += count;
				return has_odd ? length + 1 : length;
			}
		};
	}

	namespace task_415 {
		/*
		* https://leetcode.com/problems/add-strings/description/
		*/
		class Solution {
		public:
			string addStrings(string num1, string num2) {
				int l1 = num1.length() - 1;
				int l2 = num2.length() - 1;
				int x = 0;
				int plus10 = 0;
				std::string answer;

				while (l1 >= 0 || l2 >= 0 || plus10 > 0) {
					int digit1 = (l1 >= 0) ? num1[l1] - '0' : 0;
					int digit2 = (l2 >= 0) ? num2[l2] - '0' : 0;

					x = digit1 + digit2 + plus10;
					plus10 = x / 10;
					x %= 10;
					answer.push_back(x + '0');

					if (l1 >= 0) l1--;
					if (l2 >= 0) l2--;
				}

				reverse(answer.begin(), answer.end());
				return answer;
			}
		};
	}

	namespace task_416 {
		/*
		* https://leetcode.com/problems/partition-equal-subset-sum/description/
		*/
		class Solution {
		public:
			bool canPartition(vector<int>& nums) {
				int sum = 0;
				for (int num : nums)
					sum += num;

				if (sum & 1)
					return false;

				int target = sum / 2;
				vector<bool> dp(target + 1, false);
				dp[0] = true;
				for (int num : nums) {
					for (int currSum = target; currSum >= num; --currSum)
						dp[currSum] = dp[currSum] || dp[currSum - num];
				}
				return dp[target];
			}
		};
	}

	namespace task_430 {
		/*
		* https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
		*/
		class Solution {
		public:
			class Node {
			public:
				int val;
				Node* prev;
				Node* next;
				Node* child;
				Node(int x) : val(x), prev(nullptr), next(nullptr), child(nullptr) {}
			};

			Node* flatten(Node* head) {
				Node* ptr = head;
				stack<Node*> stack;
				while (ptr) {
					if (ptr->child) {
						if (ptr->next)
							stack.push(ptr->next);
						ptr->next = ptr->child;
						ptr->child = nullptr;
						ptr->next->prev = ptr;
						ptr = ptr->next;
						continue;
					}
					if (!ptr->next && !stack.empty()) {
						ptr->next = stack.top();
						ptr->next->prev = ptr;
						stack.pop();
					}
					ptr = ptr->next;
				}
				return head;
			}
		};
	}

	namespace task_432 {
		/*
		* https://leetcode.com/problems/all-oone-data-structure/description/
		*/
		class AllOne {
		public:
			unordered_map<string, int> words;
			map<int, unordered_set<string>> counts;
			AllOne() { }

			void inc(string key) {
				auto it = words.find(key);
				if (it == words.end()) {
					words[key] = 1;
					auto count_it = counts.begin();
					if (count_it != counts.end() && count_it->first == 1)
						count_it->second.insert(key);
					else
						counts[1] = { key };
				}
				else {
					auto count_it = counts.find(it->second);
					count_it->second.erase(key);
					if (count_it->second.size() == 0)
						counts.erase(count_it);
					++it->second;
					counts[it->second].insert(key);
				}
			}

			void dec(string key) {
				auto it = words.find(key);
				auto count_it = counts.find(it->second);
				count_it->second.erase(key);
				if (count_it->second.size() == 0)
					counts.erase(count_it);
				--it->second;
				if (it->second == 0)
					words.erase(it);
				else
					counts[it->second].insert(key);
			}

			string getMaxKey() {
				if (counts.size() == 0)
					return "";
				return *(--counts.end())->second.begin();
			}

			string getMinKey() {
				if (counts.size() == 0)
					return "";
				return *counts.begin()->second.begin();
			}
		};

		class AllOne_leetcode {
		private:
			class Node {
			public:
				int freq;
				Node* prev;
				Node* next;
				unordered_set<string> keys;

				Node(int freq) : freq(freq), prev(nullptr), next(nullptr) {}
			};

			Node* head;						// Dummy head
			Node* tail;						// Dummy tail
			unordered_map<string, Node*> map;  // Mapping from key to its node

			void removeNode(Node* node) {
				Node* prevNode = node->prev;
				Node* nextNode = node->next;

				prevNode->next = nextNode;  // Link previous node to next node
				nextNode->prev = prevNode;  // Link next node to previous node

				delete node;  // Free the memory of the removed node
			}

		public:
			// Initialize your data structure here.
			AllOne_leetcode() {
				head = new Node(0);  // Create dummy head
				tail = new Node(0);  // Create dummy tail
				head->next = tail;   // Link dummy head to dummy tail
				tail->prev = head;   // Link dummy tail to dummy head
			}

			// Inserts a new key <Key> with value 1. Or increments an existing key by 1.
			void inc(string key) {
				if (map.find(key) != map.end()) {
					Node* node = map[key];
					int freq = node->freq;
					node->keys.erase(key);  // Remove key from current node

					Node* nextNode = node->next;
					if (nextNode == tail || nextNode->freq != freq + 1) {
						// Create a new node if next node does not exist or freq is not
						// freq + 1
						Node* newNode = new Node(freq + 1);
						newNode->keys.insert(key);
						newNode->prev = node;
						newNode->next = nextNode;
						node->next = newNode;
						nextNode->prev = newNode;
						map[key] = newNode;
					}
					else {
						// Increment the existing next node
						nextNode->keys.insert(key);
						map[key] = nextNode;
					}

					// Remove the current node if it has no keys left
					if (node->keys.empty()) {
						removeNode(node);
					}
				}
				else {  // Key does not exist
					Node* firstNode = head->next;
					if (firstNode == tail || firstNode->freq > 1) {
						// Create a new node
						Node* newNode = new Node(1);
						newNode->keys.insert(key);
						newNode->prev = head;
						newNode->next = firstNode;
						head->next = newNode;
						firstNode->prev = newNode;
						map[key] = newNode;
					}
					else {
						firstNode->keys.insert(key);
						map[key] = firstNode;
					}
				}
			}

			// Decrements an existing key by 1. If Key's value is 1, remove it from the
			// data structure.
			void dec(string key) {
				if (map.find(key) == map.end()) {
					return;  // Key does not exist
				}

				Node* node = map[key];
				node->keys.erase(key);
				int freq = node->freq;

				if (freq == 1) {
					// Remove the key from the map if freq is 1
					map.erase(key);
				}
				else {
					Node* prevNode = node->prev;
					if (prevNode == head || prevNode->freq != freq - 1) {
						// Create a new node if the previous node does not exist or freq
						// is not freq - 1
						Node* newNode = new Node(freq - 1);
						newNode->keys.insert(key);
						newNode->prev = prevNode;
						newNode->next = node;
						prevNode->next = newNode;
						node->prev = newNode;
						map[key] = newNode;
					}
					else {
						// Decrement the existing previous node
						prevNode->keys.insert(key);
						map[key] = prevNode;
					}
				}

				// Remove the node if it has no keys left
				if (node->keys.empty()) {
					removeNode(node);
				}
			}

			// Returns one of the keys with maximal value.
			string getMaxKey() {
				if (tail->prev == head) {
					return "";  // No keys exist
				}
				return *(tail->prev->keys.begin());  // Return one of the keys from the
													 // tail's previous node
			}

			// Returns one of the keys with minimal value.
			string getMinKey() {
				if (head->next == tail) {
					return "";  // No keys exist
				}
				return *(
					head->next->keys
					.begin());  // Return one of the keys from the head's next node
			}
		};
	}

	namespace task_436 {
		/*
		* https://leetcode.com/find-right-interval/description/
		*/
		class Solution {
		public:
			vector<int> findRightInterval(vector<vector<int>>& intervals) {
				size_t size = intervals.size();
				vector<int> res(size, -1);
				for (size_t i = 0; i < size; i++)
					intervals[i].push_back(i);
				sort(intervals.begin(), intervals.end()); 
				
				for (size_t i = 0; i < size; i++) {
					int pos = bin_search(intervals, size - 1, intervals[i][1]);
					if (pos != -1)
						res[intervals[i][2]] = intervals[pos][2];
					else
						res[intervals[i][2]] = pos;
				}
				return res;
			}

			int bin_search(vector<vector<int>>& interval, size_t r, int target) {
				size_t l = 0;
				if (interval[l][0] >= target)
					return l;
				if (interval[r][0] < target)
					return -1;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (interval[i][0] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_440 {
		/*
		* https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/description/
		*/
		class Solution {
		public:
			int number;
			int n;
			vector<int> counts{ 0,0,0,0,0,0,0,0,0,0 };

			int findKthNumberWithoutReq(int n, int k) {
				if (n < 10)
					return k;
				vector<int> counts(10);
				int number = 0, i = 1;
				for (; i < 10; ++i) {
					counts[i] = 1;
					long long degree = 10;
					while ((i + 1) * degree <= n) {
						counts[i] = counts[i] * 10 + 1;
						degree *= 10;
					}
					if (i * degree <= n)
						counts[i] += n + 1 - i * degree;
					counts[i] += counts[i - 1];
					if (k <= counts[i])
						break;
				}
				number = i;
				k -= counts[i - 1] + 1;

				while (k > 0) {
					i = 0;
					for (; i < 10; ++i) {
						counts[i] = 1;
						long long degree = 10;
						while ((number * 10 + i + 1) * degree <= n) {
							counts[i] = counts[i] * 10 + 1;
							degree *= 10;
						}
						if ((number * 10 + i) * degree <= n)
							counts[i] += n + 1 - (number * 10 + i) * degree;
						if (i > 0)
							counts[i] += counts[i - 1];
						if (k <= counts[i])
							break;
					}
					number = number * 10 + i;
					if (i > 0)
						k -= counts[i - 1];
					--k;
				}
				return number;
			}

			int findKthNumber(int n, int k) {
				if (n < 10)
					return k;
				this->n = n;
				int i = 1;
				for (; i < 10; ++i) {
					counts[i] = 1;
					long long degree = 10;
					while ((i + 1) * degree <= n) {
						counts[i] = counts[i] * 10 + 1;
						degree *= 10;
					}
					if (i * degree <= n)
						counts[i] += n + 1 - i * degree;
					counts[i] += counts[i - 1];
					if (k <= counts[i])
						break;
				}
				number = i;
				k -= counts[i - 1];
				findKthNumberReq(k - 1);
				return number;
			}

			void findKthNumberReq(int k) {
				if (k == 0)
					return;
				int i = 0;
				for (; i < 10; ++i) {
					counts[i] = 1;
					long long degree = 10;
					while ((number * 10 + i + 1) * degree <= n) {
						counts[i] = counts[i] * 10 + 1;
						degree *= 10;
					}
					if ((number * 10 + i) * degree <= n)
						counts[i] += n + 1 - (number * 10 + i) * degree;
					if (i > 0)
						counts[i] += counts[i - 1];
					if (k <= counts[i])
						break;
				}
				number = number * 10 + i;
				if (i > 0)
					k -= counts[i - 1];
				findKthNumberReq(k - 1);
			}
		};
	}

	namespace task_441 {
		/*
		* https://leetcode.com/problems/arranging-coins/description/
		*/
		class Solution {
		public:
			int arrangeCoins(int n) {
				size_t left = 1, right = 65535;

				while (left <= right) {
					size_t mid = left + (right - left) / 2;
					size_t val = mid * (mid + 1) / 2;
					if (val == n) { return mid; }
					else if (val > n) { right = mid - 1; }
					else { left = mid + 1; }
				}

				return right;
			}
		};
	}

	namespace task_443 {
		/*
		* https://leetcode.com/problems/string-compression/description/
		*/
		class Solution {
		public:
			int compress(vector<char>& chars) {
				size_t size = chars.size(), writeIndex = 0, countDigit = 0;
				int len = 0;
				for (size_t i = 0; i < size; ++i) {
					size_t j = 1;
					for (; i + j < size && chars[i] == chars[i + j]; ++j) {}
					chars[writeIndex] = chars[i];
					++writeIndex;
					if (j == 1)
						continue;
					i += j - 1;
					countDigit = 0;
					for (; j > 0; j /= 10, countDigit += 1)
						chars[writeIndex + countDigit] = '0' + j % 10;

					for (size_t j = 0; j < (countDigit >> 1); ++j)
						swap(chars[writeIndex + j], chars[writeIndex + countDigit - j - 1]);
					writeIndex += countDigit;
				}
				return writeIndex;
			}
		};
	}

	namespace task_445 {
		/*
		* https://leetcode.com/problems/add-two-numbers-ii/description/
		*/
		class Solution {
		public:
			ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
				return reverseList(addTwoNumbersR(reverseList(l1), reverseList(l2)));
			}

			ListNode* reverseList(ListNode* head) {
				if (!head || !head->next)
					return head;

				auto prev = head;
				auto ptr = head->next;
				auto next = ptr->next;
				while (true) {
					ptr->next = prev;
					prev = ptr;
					if (next) {
						ptr = next;
						next = next->next;
					}
					else
						break;
				}
				head->next = nullptr;

				return ptr;
			}

			ListNode* addTwoNumbersR(ListNode* l1, ListNode* l2) {
				auto head = new ListNode(l1->val);
				l1 = l1->next;
				auto current = head;
				while (l1) {
					current->next = new ListNode(l1->val);
					current = current->next;
					l1 = l1->next;
				}
				current = head;
				current->val += +l2->val;
				l2 = l2->next;
				int add_one = current->val / 10;
				current->val %= 10;
				while (l2 || add_one) {
					if (l2) {
						add_one += l2->val;
						l2 = l2->next;
					}
					if (!current->next)
						current->next = new ListNode(0);
					current = current->next;
					current->val += add_one;
					add_one = current->val / 10;
					current->val %= 10;
				}
				return head;
			}
		};
	}

	namespace task_448 {
		/*
		* https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/description/
		*/
		class Solution {
		public:
			vector<int> findDisappearedNumbers(vector<int>& nums) {
				const int size = nums.size();
				for (int i = 0; i < size; ++i)
					while (nums[i] != i + 1 && nums[i] != nums[nums[i] - 1])
						swap(nums[i], nums[nums[i] - 1]);

				vector<int> not_appear;
				for (int i = 0; i < size; ++i)
					if (i + 1 != nums[i])
						not_appear.push_back(i + 1);
				return not_appear;
			}

			vector<int> findDisappearedNumbersNegation(vector<int>& nums) {
				vector<int> not_appear;
				for (auto c : nums)
					nums[abs(c) - 1] = -abs(nums[abs(c) - 1]);   // mark c is present by negating nums[c-1]
				for (int i = 0; i < size(nums); ++i)
					if (nums[i] > 0) not_appear.push_back(i + 1);	  // nums[i] > 0 means i+1 isnt present in nums
				return not_appear;
			}
		};
	}

	namespace task_476 {
		/*
		* https://leetcode.com/problems/number-complement/description/
		*/
		class Solution {
		public:
			int findComplement(int num) {
				int rev_num = ~num, mask = num;
				do {
					mask |= num;
					num >>= 1;
				} while (num > 0);
				return rev_num & mask;
			}
		};
	}

	namespace task_494 {
		/*
		* https://leetcode.com/problems/target-sum/description/
		*/
		class Solution {
		public:
			int findTargetSumWays__TLE(vector<int>& nums, int target) {
				int count = 0;
				int end = 1 << nums.size();
				for (int i = 0; i < end; ++i) {
					int sum = 0, choose = i;
					for (size_t j = 0; j < nums.size(); ++j) {
						if (choose & 1)
							sum += nums[j];
						else
							sum -= nums[j];
						choose >>= 1;
					}
					if (sum == target)
						++count;
				}
				return count;
			}

			int sum, remain, count, tar;
			size_t size;

			int findTargetSumWays(vector<int>& nums, int target) {
				sort(nums.begin(), nums.end(), greater<>());
				sum = 0, remain = 0, count = 0, tar = target;
				size = nums.size();
				for (int n : nums)
					remain += n;
				findTargetSumWaysReq(nums, 0);
				return count;
			}

			void findTargetSumWaysReq(const vector<int>& nums, size_t i) {
				if (i == size) {
					if (sum == tar)
						++count;
					return;
				}
				sum += nums[i];
				remain -= nums[i];
				if (sum - remain <= tar)
					findTargetSumWaysReq(nums, i + 1);
				sum -= nums[i] << 1;
				if (sum + remain >= tar)
					findTargetSumWaysReq(nums, i + 1);
				sum += nums[i];
				remain += nums[i];
			}
		};
	}

	namespace task_502 {
		/*
		* https://leetcode.com/problems/ipo/description/
		*/
		class Solution {
		public:
			int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
				size_t size = capital.size();
				vector<pair<int, int>> not_allowed_projects(size);
				priority_queue<int> projects;

				for (size_t i = 0; i < size; ++i)
					not_allowed_projects[i] = { capital[i],profits[i] };
				sort(not_allowed_projects.begin(), not_allowed_projects.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
					return a.first > b.first;
					});
				for (size_t i = 0; i < k; ++i) {
					while (!not_allowed_projects.empty() && not_allowed_projects.back().first <= w) {
						projects.push(not_allowed_projects.back().second);
						not_allowed_projects.pop_back();
					}
					if (projects.empty())
						return w;
					w += projects.top();
					projects.pop();
				}
				return w;
			}
		};
	}

	namespace task_509 {
		/*
		* https://leetcode.com/problems/fibonacci-number/description/
		*/
		class Solution {
		public:
			int fib(int n) {
				if (n < 2)
					return n;
				int cur = 1;
				int prev = 1;
				for (size_t i = 2; i < n; i++) {
					int temp = cur + prev;
					prev = cur;
					cur = temp;
				}
				return cur;
			}
		};
	}

	namespace task_513 {
		/*
		* https://leetcode.com/problems/find-bottom-left-tree-value/description/
		*/
		class Solution {
		public:
			int findBottomLeftValue(TreeNode* root) {
				int last_level = 0;
				int value = root->val;
				queue<pair<TreeNode*, int>> q;
				q.push({ root, 0 });
				while (!q.empty()) {
					auto node = q.front();
					q.pop();
					if (last_level < node.second) {
						last_level = node.second;
						value = node.first->val;
					}
					if (node.first->left)
						q.push({ node.first->left, node.second + 1 });
					if (node.first->right)
						q.push({ node.first->right, node.second + 1 });
				}
				return value;
			}
		};
	}

	namespace task_515 {
		/*
		* https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/description/
		*/
		class Solution {
		public:
			vector<int> largestValues(TreeNode* root) {
				if (!root)
					return {};
				queue<TreeNode*> queue;
				vector<int> res;
				size_t size;
				int max_value;
				queue.push(root);
				res.push_back(root->val);
				while (true) {
					size = queue.size();
					max_value = INT_MIN;
					for (size_t i = 0; i < size; ++i) {
						auto node = queue.front();
						queue.pop();
						if (node->left) {
							queue.push(node->left);
							max_value = max(max_value, node->left->val);
						}
						if (node->right) {
							queue.push(node->right);
							max_value = max(max_value, node->right->val);
						}
					}
					if (queue.empty())
						break;
					else
						res.push_back(max_value);
				}
				return res;
			}
		};
	}

	namespace task_516 {
		/*
		* https://leetcode.com/problems/longest-palindromic-subsequence/description/
		*/
		class Solution {
		public:
			int longestPalindromeSubseq(string s) {
				const size_t size = s.size();
				vector<int> length_palindrome(size);

				for (size_t i = 0; i < size; i++) {
					length_palindrome[i] = 1;
					int max_palindrome_between = 0;
					int j = i - 1;
					for (; j >= 0; --j) {
						int temp = max_palindrome_between;
						if (max_palindrome_between < length_palindrome[j])
							temp = length_palindrome[j];
						if (s[j] == s[i])
							length_palindrome[j] = max_palindrome_between + 2;
						max_palindrome_between = temp;
					}
				}

				int max_palindrome = 0;
				for (size_t i = 0; i < size; i++)
					if (max_palindrome < length_palindrome[i])
						max_palindrome = length_palindrome[i];
				return max_palindrome;
			}
		};
	}

	namespace task_523 {
		/*
		* https://leetcode.com/problems/continuous-subarray-sum/description/
		*/
		class Solution {
		public:
			bool checkSubarraySum(vector<int>& nums, int k) {
				size_t size = nums.size();
				int sum = nums[0] % k;
				unordered_set<int> set({ sum });
				for (size_t i = 1; i < size; ++i) {
					sum = (sum + nums[i]) % k;
					if ((nums[i] + nums[i - 1]) % k == 0)
						return true;
					else if (set.contains(sum) && nums[i] % k != 0 || sum == 0)
						return true;
					set.insert(sum);
				}
				return false;
			}

			bool checkSubarraySumFaster(std::vector<int>& nums, int k) {
				int sum = 0, prev_sum = 0;
				unordered_set<int> set;
				for (const int n : nums) {
					sum = (sum + n) % k;
					if (set.count(sum)) return true;
					set.insert(prev_sum);
					prev_sum = sum;
				}
				return false;
			}
		};
	}

	namespace task_528 {
		/*
		* https://leetcode.com/problems/random-pick-with-weight/description/
		*/
		class Solution {
		public:
			vector<unsigned int> prob_sum;
			size_t size;
			std::uniform_int_distribution<> distr; // define the range
			std::mt19937 gen;

			Solution(vector<int>& w) {
				std::random_device rd; // obtain a random number from hardware
				gen = std::mt19937(rd()); // seed the generator
				size = w.size();
				unsigned int sum = 0;
				for (size_t i = 0; i < size; i++) {
					sum += w[i];
					prob_sum.push_back(sum);
				}
				distr = std::uniform_int_distribution<>(1, sum); // define the range
			}

			int pickIndex() {
				unsigned int target = distr(gen);
				size_t l = 0;
				size_t r = size - 1;
				if (prob_sum[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) >> 1;
					if (prob_sum[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_538 {
		/*
		* https://leetcode.com/problems/convert-bst-to-greater-tree/
		*/
		class Solution {
		public:
			int sum;

			TreeNode* convertBST(TreeNode* root) {
				sum = 0;
				if (root)
					bstToGstReq(root);
				return root;
			}

			void bstToGstReq(TreeNode* root) {
				if (root->right)
					bstToGstReq(root->right);
				sum += root->val;
				root->val = sum;
				if (root->left)
					bstToGstReq(root->left);
			}
		};
	}

	namespace task_539 {
		/*
		* https://leetcode.com/problems/path-sum/description/
		*/
		class Solution {
		public:
			int findMinDifference(vector<string>& timePoints) { // 41,48%; 88,24%
				size_t size = timePoints.size();
				vector<int> times(size);
				for (size_t i = 0; i < size; ++i)
					times[i] = stoi(timePoints[i].substr(0, 2)) * 60 + stoi(timePoints[i].substr(3));
				sort(times.begin(), times.end());
				int min_time = times[0] + 24 * 60 - times.back();
				for (size_t i = 1; i < size; ++i)
					min_time = min(min_time, times[i] - times[i - 1]);
				return min_time;
			}

			int findMinDifferenceBucketSort(vector<string>& timePoints) { // 99,52%; 77,18%
				// create buckets array for the times converted to minutes
				int allTime = 24 * 60;
				vector<char> minutes(allTime);
				for (const string& time : timePoints) {
					int min = stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3));
					if (minutes[min]) return 0;
					minutes[min] = 1;
				}
				int prevIndex = 0, ans = INT_MAX;

				for (int i = allTime - 1; i >= 0; --i)
					if (minutes[i]) {
						prevIndex = i - allTime;
						break;
					}

				// find differences between adjacent elements in sorted array
				for (int i = 0; i < allTime; i++)
					if (minutes[i]) {
						ans = min(ans, i - prevIndex);
						prevIndex = i;
					}

				return ans;
			}
		};
	}

	namespace task_540 {
		/*
		* https://leetcode.com/problems/single-element-in-a-sorted-array/description/
		*/
		class Solution {
		public:
			int singleNonDuplicate(vector<int>& nums) {
				size_t l = 1;
				size_t r = nums.size();

				if (nums.size() == 1 || nums[l] != nums[l - 1])
					return nums[0];

				while (r - l > 2) {
					size_t i = ((r + l) >> 2) << 1;
					i -= i & 1;
					if (nums[i] == nums[i - 1])
						r = i - 1;
					else {
						if (nums[i] != nums[i + 1])
							return nums[i];
						l = i + 1;
					}
				}
				return nums[l + 1];
			}
		};
	}

	namespace task_541 {
		/*
		* https://leetcode.com/problems/reverse-string-ii/description/
		*/
		class Solution {
		public:
			string reverseStr(string s, int k) {
				size_t size = s.size();
				char t;
				for (size_t i = 0; i < size; i += k << 1) {
					size_t to = min(i + k, size) - 1;
					size_t rotate_point = (to - i) >> 1;
					for (size_t j = 0; j <= rotate_point; ++j) {
						t = s[i + j];
						s[i + j] = s[to - j];
						s[to - j] = t;
					}
				}
				return s;
			}
		};
	}

	namespace task_543 {
		/*
		* https://leetcode.com/problems/diameter-of-binary-tree/description/
		*/
		class Solution {
		public:
			int diameterOfBinaryTree(TreeNode* root) {
				int max_length = 0;
				stack<TreeNode*> st;
				st.push(root);
				TreeNode* node = root;
				TreeNode* extra = new TreeNode(0);
				TreeNode* prev = extra;

				while (!st.empty()) {
					node = st.top();
					if (prev == node->right) {
						int left_depth = node->left ? node->left->val : -1;
						int right_depth = node->right ? node->right->val : -1;
						max_length = max(max_length, left_depth + right_depth + 2);
						node->val = 1 + max(left_depth, right_depth);
						prev = node;
						st.pop();
					}
					else if (!node->left || prev == node->left) {
						if (node->right) {
							prev = node;
							st.push(node->right);
						}
						else
							prev = node->right;
					}
					else {
						prev = node;
						st.push(node->left);
					}
				}

				delete extra;
				return max_length;
			}
		};
	}

	namespace task_551 {
		/*
		* https://leetcode.com/problems/student-attendance-record-i/
		*/
		class Solution {
		public:
			bool checkRecord(string s) {
				int count_absent = 0, count_late = 0;
				for (char c : s) {
					if (c == 'L') {
						++count_late;
						if (count_late == 3)
							return false;
						continue;
					}
					count_late = 0;
					if (c == 'A') {
						++count_absent;
						if (count_absent == 2)
							return false;
						continue;
					}
				}
				return true;
			}
		};
	}

	namespace task_552 {
		/*
		* https://leetcode.com/problems/student-attendance-record-ii/description/
		*/
		class Solution {
		public:
			const unsigned long long mod = 1000000007;
			unsigned long long f0, f1, f2, f3;
			unsigned long long a, ax0, ax1; // with A in last 2 letters
			unsigned long long a0, a1, a2, a3; // with A before 2 letters
			unsigned long long b0, b1, b2, b3; // without A

			int checkRecord(int n) {
				if (n == 1)
					return 3;
				a = 2, ax0 = 1, ax1 = 1;
				a0 = 0, a1 = 0, a2 = 0, a3 = 0;
				b0 = 1, b1 = 1, b2 = 1, b3 = 1;

				for (int i = 2; i < n; ++i)
					nextStep();

				return (a + ax0 + ax1 + a0 + a1 + a2 + a3 + b0 + b1 + b2 + b3) % mod;
			}

			void nextStep() {
				f0 = (a2 + ax0) % mod;
				f1 = (a0 + a2 + ax0) % mod;
				f2 = (a1 + a3 + ax1) % mod;
				f3 = (a1 + a3 + ax1) % mod;
				a0 = f0;
				a1 = f1;
				a2 = f2;
				a3 = f3;

				ax0 = a;
				ax1 = a;
				a = b0 + b1 + b2 + b3;

				f0 = b2;
				f1 = (b0 + b2) % mod;
				f2 = (b1 + b3) % mod;
				f3 = (b1 + b3) % mod;
				b0 = f0;
				b1 = f1;
				b2 = f2;
				b3 = f3;
			}
		};
	}

	namespace task_557 {
		/*
		* https://leetcode.com/problems/reverse-words-in-a-string-iii/description/
		*/
		class Solution {
		public:
			string reverseWords(string s, int k) {
				size_t size = s.size();
				char t;
				for (size_t i = 0; i < size;) {
					size_t to = i + 1;
					for (; to < size && s[to] != ' '; ++to) {}
					size_t rotate_point = (to - i) >> 1;
					for (size_t j = 0; j < rotate_point; ++j) {
						t = s[i + j];
						s[i + j] = s[to - j - 1];
						s[to - j - 1] = t;
					}
					i = to + 1;
				}
				return s;
			}
		};
	}

	namespace task_564 {
		/*
		* https://leetcode.com/problems/find-the-closest-palindrome/description/
		*/
		class Solution {
		public:
			string nearestPalindromic(string n) {
				size_t size = n.size(), mid = size >> 1;
				if (size == 1) {
					--n[0];
					return n;
				}
				bool isPalindromic = true;
				for (size_t i = 0; i < mid; ++i)
					if (n[i] != n[size - i - 1]) {
						isPalindromic = false;
						break;
					}

				if (isPalindromic) { // if n is already palindrom
					bool isAll9 = true;
					for (size_t i = 0; i < size; ++i)
						if (n[i] != '9') {
							isAll9 = false;
							break;
						}
					if (isAll9) {
						for (size_t i = 1; i < size; ++i)
							n[i] = '0';
						n[0] = '1';
						n.push_back('1');
						return n;
					}

					if (size & 1) { // if size is odd
						if (n[mid] != '0') // if mid is more than 0 then decrease it
							--n[mid];
						else if (n[mid + 1] != '0') // if mid is 0 and neighboring are not
							++n[mid];
						else { // if several 0 in the middle
							n[mid] = '9';
							size_t i = 1;
							for (; n[mid + i] == '0'; i++) {
								n[mid + i] = '9';
								n[mid - i] = '9';
							}
							--n[mid + i];
							--n[mid - i];
							if (n[0] == '0') {
								n[size - 1] = '9';
								n.erase(0, 1);
							}
						}
					}
					else { // if size is even
						if (n[mid] != '0') { // if mid is more than 0 then decrease it
							if (n == "11")
								return "9";
							--n[mid];
							--n[mid - 1];
						}
						else { // if several 0 in the middle
							size_t i = 0;
							for (; n[mid + i] == '0'; i++) {
								n[mid + i] = '9';
								n[mid - i - 1] = '9';
							}
							--n[mid + i];
							--n[mid - i - 1];
							if (n[0] == '0') {
								n[size - 1] = '9';
								n.erase(0, 1);
							}
						}
					}
					return n;
				}

				if (n[0] == '1') { // if n is 1000...000
					bool isRound = true;
					for (size_t i = 1; i < size; i++)
						if (n[i] != '0') {
							isRound = false;
							break;
						}
					if (isRound)
						return string(size - 1, '9');
				}

				auto orig_n = stoll(n);

				for (size_t i = 0; i < mid; i++)
					n[size - i - 1] = n[i];

				char prev_char = n[mid];
				if (size & 1) {
					auto n0 = abs(orig_n - stoll(n)), n1 = n0, n2 = n0;
					if (n[mid] < '9') {
						++n[mid];
						n1 = abs(orig_n - stoll(n));
						if (n1 < n0) {
							n0 = n1;
							prev_char = n[mid];
						}
						--n[mid];
					}
					if (n[mid] > '0') {
						--n[mid];
						n2 = abs(orig_n - stoll(n));
						if (n2 <= n0)
							prev_char = n[mid];
					}
					n[mid] = prev_char;
				}
				else {
					auto n1 = abs(orig_n - stoll(n));

					if (prev_char >= '5') {
						--n[mid];
						--n[mid - 1];
					}
					else {
						++n[mid];
						++n[mid - 1];
					}
					auto n2 = abs(orig_n - stoll(n));
					if (n1 < n2 || n1 == n2 && prev_char < n[mid]) {
						n[mid] = prev_char;
						n[mid - 1] = prev_char;
					}
				}

				return n;
			}
		};
	}

	namespace task_567 {
		/*
		* https://leetcode.com/problems/problems/permutation-in-string/description/
		*/
		class Solution {
		public:
			bool checkInclusion(string s1, string s2) {
				size_t size1 = s1.size(), size2 = s2.size(), letters_size = 'z' - 'a' + 1, letters_count = 0;
				if (size1 > size2)
					return false;
				vector<int> letters1(letters_size), letters2(letters_size);
				for (const char c : s1)
					++letters1[c - 'a'];
				size_t i = 0;
				for (; i < size1; ++i) {
					size_t index = s2[i] - 'a';
					++letters2[index];
					if (letters2[index] <= letters1[index])
						++letters_count;
				}
				if (letters_count == size1)
					return true;
				for (; i < size2; ++i) {
					size_t index = s2[i] - 'a';
					++letters2[index];
					if (letters2[index] <= letters1[index])
						++letters_count;

					index = s2[i - size1] - 'a';
					--letters2[index];
					if (letters2[index] < letters1[index])
						--letters_count;

					if (letters_count == size1)
						return true;
				}
				return false;
			}
		};
	}

	namespace task_583 {
		/*
		* https://leetcode.com/problems/delete-operation-for-two-strings/description/
		*/
		class Solution {
		public:
			int minDistance(string word1, string word2) {
				const size_t size1 = word1.size();
				const size_t size2 = word2.size();
				if (size1 == 0 || size2 == 0)
					return size1 + size2;
				vector<vector<int>> result(size1, vector<int>(size2));
				int is_first_letter_same = 0;
				for (size_t j = 0; j < size2; j++) {
					if (word1[0] == word2[j])
						is_first_letter_same = 2;
					result[0][j] = j + 2 - is_first_letter_same;
				}
				is_first_letter_same = 0;
				for (size_t i = 0; i < size1; i++) {
					if (word1[i] == word2[0])
						is_first_letter_same = 2;
					result[i][0] = i + 2 - is_first_letter_same;
				}

				for (size_t i = 1; i < size1; i++)
					for (size_t j = 1; j < size2; j++)
						result[i][j] = min(min(result[i][j - 1] + 1, result[i - 1][j] + 1),
							result[i - 1][j - 1] + (word1[i] == word2[j] ? 0 : 2));
				return result.back().back();
			}
		};
	}

	namespace task_590 {
		/*
		* https://leetcode.com/problems/n-ary-tree-postorder-traversal/description/
		*/
		class Solution {
		public:
			vector<int> postorder(NodeNTree* root) {
				vector<int> res;
				if (!root)
					return res;

				stack<NodeNTree*> stack;
				stack.push(root);

				while (!stack.empty()) {
					root = stack.top();
					stack.pop();
					res.push_back(root->val);
					for (auto node : root->children)
						stack.push(node);
				}
				reverse(res.begin(), res.end());
				return res;
			}
		};
	}

	namespace task_592 {
		/*
		* https://leetcode.com/problems/number-complement/description/
		*/
		class Solution {
		public:
			const int common_denominator = 3628800;

			string fractionAddition(string expression) {
				int multiplier = 1, search_from = 0;
				size_t size = expression.size(), next_operation_pos = 0;
				if (expression[0] == '-') {
					multiplier = -1;
					search_from = 1;
				}
				int number = 0;
				while (next_operation_pos < size) {
					next_operation_pos = min(size, min(expression.find('-', search_from), expression.find('+', search_from)));
					number += parseFraction(expression.substr(search_from, next_operation_pos - search_from)) * multiplier;
					search_from = next_operation_pos + 1;
					multiplier = next_operation_pos < size&& expression[next_operation_pos] == '+' ? 1 : -1;
				}
				if (number == 0)
					return "0/1";
				int gcd = GCD(abs(number), common_denominator);
				number /= gcd;
				int denominator = common_denominator / gcd;
				return to_string(number) + '/' + to_string(denominator);
			}

			int GCD(int x, int y) {
				while (x != y) {
					if (x > y)
						x -= y;
					else
						y -= x;
				}
				return x;
			}

			int parseFraction(string fraction) {
				size_t slach = fraction.find('/');
				int denominator = stoi(fraction.substr(slach + 1));
				return stoi(fraction.substr(0, slach)) * common_denominator / denominator;
			}
		};
	}

	namespace task_599 {
		/*
		* https://leetcode.com/problems/intersection-of-two-linked-lists/description/
		*/
		class Solution {
		public:
			vector<string> findRestaurantMap(vector<string>& list1, vector<string>& list2) {
				unordered_map<string, int> mp;
				vector<string> res;
				int size1 = list1.size(), size2 = list2.size();
				for (int sum_index = 0; sum_index < size1 + size2 - 1; sum_index++) {
					for (int i = max(0, sum_index - size2 + 1); i < size1 && i <= sum_index; i++)
						if (list1[i] == list2[sum_index - i])
							res.push_back(list1[i]);
					if (!res.empty())
						return res;
				}
				return res;
			}

			vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
				vector<string> res;
				int size1 = list1.size(), size2 = list2.size();
				for (int sum_index = 0; sum_index < size1 + size2 - 1; sum_index++) {
					for (int i = max(0, sum_index - size2 + 1); i < size1 && i <= sum_index; i++)
						if (list1[i] == list2[sum_index - i])
							res.push_back(list1[i]);
					if (!res.empty())
						return res;
				}
				return res;
			}
		};
	}

	namespace task_611 {
		/*
		* https://leetcode.com/problems/valid-triangle-number/description/
		*/
		class Solution {
		public:
			int triangleNumber(vector<int>& nums) {
				if (nums.size() < 3)
					return 0;
				sort(nums.begin(), nums.end());
				int sum = 0;
				for (size_t i = 0; i < nums.size() - 2; i++) {
					if (nums[i] == 0)
						continue;
					size_t j = i + 1;
					size_t k = i + 2;

					for (; j < nums.size() - 1; j++) {
						k = max(j + 1, k);
						while (k < nums.size() && nums[i] + nums[j] > nums[k])
							++k;
						if (k == nums.size())
							break;
						sum += k - j - 1;
					}
					sum += (k - j - 1) * (k - j) / 2;
				}
				return sum;
			}
		};
	}

	namespace task_617 {
		/*
		* https://leetcode.com/problems/merge-two-binary-trees/description/
		*/
		class Solution {
		public:
			TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
				if (!root1)
					return root2;
				if (!root2)
					return root1;

				TreeNode* root = new TreeNode(root1->val + root2->val);
				TreeNode* node = root;
				queue<pair<bool, vector<TreeNode*>>> queue;
				if (root1->left || root2->left)
					queue.push({ false, {root1->left, root2->left, node} });
				if (root1->right || root2->right)
					queue.push({ true, {root1->right, root2->right, node} });

				while (!queue.empty()) {
					bool isRight = queue.front().first;
					const vector<TreeNode*>& ptrs = queue.front().second;
					int val1 = ptrs[0] ? ptrs[0]->val : 0;
					int val2 = ptrs[1] ? ptrs[1]->val : 0;
					node = new TreeNode(val1 + val2);
					if (isRight)
						ptrs[2]->right = node;
					else
						ptrs[2]->left = node;

					TreeNode* left1 = ptrs[0] ? ptrs[0]->left : nullptr;
					TreeNode* left2 = ptrs[1] ? ptrs[1]->left : nullptr;
					TreeNode* right1 = ptrs[0] ? ptrs[0]->right : nullptr;
					TreeNode* right2 = ptrs[1] ? ptrs[1]->right : nullptr;
					if (left1 || left2)
						queue.push({ false, {left1, left2, node} });
					if (right1 || right2)
						queue.push({ true, {right1, right2, node} });
					queue.pop();
				}
				return root;
			}
		};
	}

	namespace task_621 {
		/*
		* https://leetcode.com/problems/task-scheduler/
		*/
		class Solution {
		public:
			int leastInterval(vector<char>& tasks, int n) {
				if (n == 0)
					return tasks.size();

				vector<int> sorted_tasks(26);
				for (auto v : tasks)
					++sorted_tasks[v - 'A'];
				sort(sorted_tasks.begin(), sorted_tasks.end(), greater<int>());

				while (sorted_tasks.back() == 0)
					sorted_tasks.pop_back();

				++n;
				if (sorted_tasks.size() <= n)
					return leastInterval2(sorted_tasks, n);

				std::priority_queue<int> queue;
				std::queue<int> wait_queue;
				int sum = 0;
				for (auto v : sorted_tasks) {
					sum += v;
					queue.push(v);
				}

				int count = 0;
				while (sum != 0) {
					if (wait_queue.size() == n) {
						queue.push(wait_queue.front());
						wait_queue.pop();
					}
					if (queue.top() > 0) {
						wait_queue.push(queue.top() - 1);
						--sum;
					}
					else {
						wait_queue.push(queue.top());
					}

					queue.pop();
					++count;
				}
				return count;
			}

			int leastInterval2(const vector<int>& tasks, const int n) {
				int count_max = 1;
				for (; count_max < tasks.size(); count_max++)
					if (tasks[count_max] != tasks[count_max - 1])
						break;
				return (tasks[0] - 1) * n + count_max;
			}
		};
	}

	namespace task_622 {
		/*
		* https://leetcode.com/problems/design-circular-queue/description/
		*/
		class MyCircularQueue {
		public:
			vector<int> vec;
			size_t capacity;
			size_t size;
			size_t head;
			size_t tail;

			MyCircularQueue(int k) : vec(vector<int>(k)), capacity(k), size(0), head(0), tail(k - 1) { }

			bool enQueue(int value) {
				if (size == capacity)
					return false;
				++size;
				tail = (tail + 1) % capacity;
				vec[tail] = value;
				return true;
			}

			bool deQueue() {
				if (size == 0)
					return false;
				--size;
				head = (head + 1) % capacity;
				return true;
			}

			int Front() {
				if (size == 0)
					return -1;
				return vec[head];
			}

			int Rear() {
				if (size == 0)
					return -1;
				return vec[tail];
			}

			bool isEmpty() {
				return size == 0;
			}

			bool isFull() {
				return size == capacity;
			}
		};
	}

	namespace task_624 {
		/*
		* https://leetcode.com/problems/maximum-distance-in-arrays/description/
		*/
		class Solution {
		public:
			int maxDistance(vector<vector<int>>& arrays) {
				size_t size = arrays.size(), min_index, max_index;
				int first_min = INT32_MAX, second_min = INT32_MAX, first_max = INT32_MIN, second_max = INT32_MIN;
				for (size_t i = 0; i < size; ++i) {
					int min_el = arrays[i][0], max_el = arrays[i].back();
					if (first_min > min_el) {
						second_min = first_min;
						first_min = min_el;
						min_index = i;
					}
					else if (second_min > min_el)
						second_min = min_el;

					if (first_max < max_el) {
						second_max = first_max;
						first_max = max_el;
						max_index = i;
					}
					else if (second_max < max_el)
						second_max = max_el;
				}
				return max_index != min_index ?
					first_max - first_min :
					max(first_max - second_min, second_max - first_min);
			}
		};
	}

	namespace task_632 {
		/*
		* https://leetcode.com/smallest-range-covering-elements-from-k-lists/description/
		*/
		class Solution {
		public:
			vector<int> smallestRange(vector<vector<int>>& nums) {
				vector<pair<int, int>> merged;

				// Merge all lists with their list index
				for (int i = 0; i < nums.size(); i++) {
					for (int num : nums[i]) {
						merged.push_back({ num, i });
					}
				}

				// Sort the merged list
				sort(merged.begin(), merged.end());

				// Two pointers to track the smallest range
				unordered_map<int, int> freq;
				int left = 0, count = 0;
				int rangeStart = 0, rangeEnd = INT_MAX;

				for (int right = 0; right < merged.size(); right++) {
					freq[merged[right].second]++;
					if (freq[merged[right].second] == 1) count++;

					// When all lists are represented, try to shrink the window
					while (count == nums.size()) {
						int curRange = merged[right].first - merged[left].first;
						if (curRange < rangeEnd - rangeStart) {
							rangeStart = merged[left].first;
							rangeEnd = merged[right].first;
						}

						freq[merged[left].second]--;
						if (freq[merged[left].second] == 0) count--;
						left++;
					}
				}

				return { rangeStart, rangeEnd };
			}
		};
	}

	namespace task_633 {
		/*
		* https://leetcode.com/problems/sum-of-square-numbers/
		*/
		class Solution {
		public:
			bool judgeSquareSum2(int c) {
				int max = sqrt(c >> 1) + 1;
				for (int i = 0; i < max; i++)
					if (isPerfectSquare(c - i * i))
						return true;
				return false;
			}

			bool isPerfectSquare2(int num) {
				int n = sqrt(num);
				return n * n == num;
			}

			bool judgeSquareSum(int c) {
				size_t end = mySqrt(c);
				for (size_t i = 0; i <= end; i++) 
					if (isPerfectSquare(c - i * i))
						return true;
				return false;
			}

			int mySqrt(int x) {
				int left = 0, right = 46340;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					if (mid * mid == x) { return mid; }
					else if (mid * mid > x) { right = mid - 1; }
					else { left = mid + 1; }
				}
				return right;
			}

			int isPerfectSquare(int num) {
				int left = 0, right = 46340;

				while (left <= right) {
					int mid = left + (right - left) / 2;
					if (mid * mid == num) { return true; }
					else if (mid * mid > num) { right = mid - 1; }
					else { left = mid + 1; }
				}
				return right * right == num;;
			}
		};
	}

	namespace task_641 {
		/*
		* https://leetcode.com/problems/design-circular-deque/description/
		*/
		class MyCircularDeque {
		public:
			vector<int> vec;
			size_t capacity;
			size_t size;
			size_t front;
			size_t last;

			MyCircularDeque(int k) : vec(vector<int>(k)), capacity(k), size(0), front(0), last(0) { }

			bool insertFront(int value) {
				if (size == capacity)
					return false;
				++size;
				if (size == 1) {
					vec[0] = value;
					front = 0;
					last = 0;
					return true;
				}
				front = (front + capacity - 1) % capacity;
				vec[front] = value;
				return true;
			}

			bool insertLast(int value) {
				if (size == capacity)
					return false;
				++size;
				if (size == 1) {
					vec[0] = value;
					front = 0;
					last = 0;
					return true;
				}
				last = (last + 1) % capacity;
				vec[last] = value;
				return true;
			}

			bool deleteFront() {
				if (size == 0)
					return false;
				--size;
				front = (front + 1) % capacity;
				return true;
			}

			bool deleteLast() {
				if (size == 0)
					return false;
				--size;
				last = (last + capacity - 1) % capacity;
				return true;
			}

			int getFront() {
				if (size == 0)
					return -1;
				return vec[front];
			}

			int getRear() {
				if (size == 0)
					return -1;
				return vec[last];
			}

			bool isEmpty() {
				return size == 0;
			}

			bool isFull() {
				return size == capacity;
			}
		};

		class MyCircularDeque2 {
		public:
			deque<int> deq;
			int max_size;

			MyCircularDeque2(int k) {
				max_size = k;
			}

			bool insertFront(int value) {
				if (deq.size() < max_size) {
					deq.push_front(value);
					return true;
				}
				return false;
			}

			bool insertLast(int value) {
				if (deq.size() < max_size) {
					deq.push_back(value);
					return true;
				}
				return false;
			}

			bool deleteFront() {
				if (deq.size() > 0) {
					deq.pop_front();
					return true;
				}
				return false;
			}

			bool deleteLast() {
				if (deq.size() > 0) {
					deq.pop_back();
					return true;
				}
				return false;

			}

			int getFront() {
				if (deq.size() > 0)
					return deq.front();
				return -1;
			}

			int getRear() {
				if (deq.size() > 0)
					return deq.back();
				return -1;
			}

			bool isEmpty() {
				return deq.size() == 0;
			}

			bool isFull() {
				return deq.size() == max_size;
			}
		};
	}

	namespace task_646 {
		/*
		* https://leetcode.com/problems/maximum-length-of-pair-chain/description/
		*/
		class Solution {
		public:
			int findLongestChain(vector<vector<int>>& pairs) {
				sort(pairs.begin(), pairs.end());
				const size_t size = pairs.size();
				size_t length = 0;
				vector<int> ends_of_LIS(size, INT_MAX);

				for (size_t i = 0; i < size; i++) {
					size_t j = search(ends_of_LIS, length, pairs[i][0]);
					ends_of_LIS[j] = min(ends_of_LIS[j], pairs[i][1]);
					length = max(j + 1, length);
				}

				return length;
			}

			size_t search(vector<int>& nums, size_t r, const int target) {
				size_t l = 0;
				if (nums[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_647 {
		/*
		* https://leetcode.com/problems/palindromic-substrings/description/
		*/
		class Solution {
		public:
			int countSubstrings(string s) {
				int count = 0;
				size_t length = s.size() * 2 - 1;

				for (size_t i = 0; i < length; i++) {
					int index = i / 2;
					int left = index + i % 2;
					int right = index;
					count += (i + 1) % 2;
					while (true) {
						--left;
						++right;
						if (0 > left ||
							right == s.size() ||
							s[left] != s[right]) {
							--right;
							++left;
							break;
						}
						++count;
					}
				}
				return count;
			}
		};
	}

	namespace task_648 {
		/*
		* https://leetcode.com/problems/replace-words/description/
		*/
		class Solution {
		public:
			class Trie {
			public:
				class Node {
				public:
					Node* children[26];
					int index = -1;

					~Node() {
						for (size_t i = 0; i < 26; i++)
							if (children[i])
								delete children[i];
					}
				};
				Node* root;

				Trie() : root(new Node()) { }
				~Trie() { delete root; }

				void insert(const string& word, const int index) {
					Node* node = root;
					for (const char c : word) {
						size_t i = c - 'a';
						if (!node->children[i])
							node->children[i] = new Node();
						node = node->children[i];
						if (node->index != -1)
							return;
					}
					node->index = index;
				}

				int search(const string& word) {
					Node* node = root;
					for (const char c : word) {
						size_t i = c - 'a';
						if (!node->children[i])
							return -1;
						node = node->children[i];
						if (node->index != -1)
							return node->index;
					}
					return -1;
				}
			};

			string replaceWords(vector<string>& dictionary, string sentence) {
				Trie trie;
				for (size_t i = 0; i < dictionary.size(); i++)
					trie.insert(dictionary[i], i);

				stringstream ss(sentence);
				vector<string> words;
				string res;
				while (ss >> res)
					words.push_back(res);
				res = "";

				for (const string& word : words) {
					int index = trie.search(word);
					if (index == -1)
						res += word + ' ';
					else
						res += dictionary[index] + ' ';

				}
				res.pop_back();
				return res;
			}

			string replaceWordsOld(vector<string>& dictionary, string sentence) {
				sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b) {return a.size() < b.size(); });
				stringstream ss(sentence);
				vector<string> words;
				string res;
				while (ss >> res)
					words.push_back(res);
				res = "";
				for (const string& word : words) {
					bool not_found = true;
					for (const string& dict_word : dictionary)
						if (word.find(dict_word) == 0) {
							res += dict_word;
							res.push_back(' ');
							not_found = false;
							break;
						}
					if (not_found) {
						res += word;
						res.push_back(' ');
					}
				}
				res.pop_back();
				return res;
			}
		};
	}

	namespace task_650 {
		/*
		* https://leetcode.com/problems/2-keys-keyboard/description/
		*/
		class Solution {
		public:
			int minSteps(int n) {
				if (n == 1)
					return 0;
				if (n < 6)
					return n;
				int square = sqrt(n) + 1;
				for (int i = 2; i < square; i++)
					if (n % i == 0)
						return minSteps(n / i) + i;
				return n;
			}
		};
	}

	namespace task_658 {
		/*
		* https://leetcode.com/problems/find-k-closest-elements/description/
		*/
		class Solution {
		public:
			vector<int> findClosestElements(vector<int>& arr, int k, int x) {
				const size_t size = arr.size();
				int l = search(arr, x);
				int r = l + 1;
				vector<int> res;
				while (r - l - 1 < k)
					if (l < 0 || (r < size && arr[r] - x < x - arr[l]))
						++r;
					else
						--l;

				++l;
				for (; l < r; l++)
					res.push_back(arr[l]);
				return res;
			}

			int search(vector<int>& nums, int target) {
				size_t l = 0;
				size_t r = nums.size();

				if (nums[l] == target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == target)
						return i;
					if (nums[i] > target)
						r = i;
					else
						l = i;
				}
				return l;
			}
		};
	}

	namespace task_664 {
		/*
		* https://leetcode.com/problems/strange-printer/description/
		*/
		class Solution {
		public:
			int strangePrinter(string s) {
				int res = 0, size = s.size();
				vector<vector<int>> dp(size, vector<int>(size, size));
				for (int i = 0; i < size; ++i)
					dp[i][i] = 1;
				for (int length = 1; length < size; ++length) {
					for (int i = 0; i < size - length; ++i) {
						for (int split = 0; split < length; ++split)
							if (s[i + split] == s[i + length])
								dp[i][i + length] = min(
									dp[i][i + length],
									dp[i][i + split] + dp[i + split + 1][i + length] - 1);
							else
								dp[i][i + length] = min(
									dp[i][i + length],
									dp[i][i + split] + dp[i + split + 1][i + length]);
					}
				}

				return dp[0].back();
			}

			int strangePrinterNotWorks(string s) { // NotWorks :(
				vector<int> left_appearance('z' - 'a' + 1, -1);
				int res = 0, size = s.size();
				for (int i = 0; i < size; ++i) {
					char c = s[i] - 'a';
					if (left_appearance[c] == -1) {
						left_appearance[c] = i;
						++res;
						continue;
					}
					int left_pos = left_appearance[c];
					for (int j = i - 1; j > left_pos; --j)
						if (left_appearance[s[j] - 'a'] < left_pos) {
							left_appearance[c] = i;
							++res;
							break;
						}
				}
				return res;
			}
		};
	}

	namespace task_670 {
		/*
		* https://leetcode.com/problems/longest-happy-string/description/
		*/
		class Solution {
		public:
			int maximumSwap(int num) {
				string str = to_string(num);
				size_t size = str.size(), i = 1, j, max_index;
				for (; i < size && str[i - 1] >= str[i]; ++i) {}
				if (i == size)
					return num;


				char max_value = str[i];
				max_index = i;
				for (j = i + 1; j < size; ++j) {
					if (max_value <= str[j]) {
						max_value = str[j];
						max_index = j;
					}
				}

				for (j = 0; str[j] >= max_value; ++j) {}
				swap(str[j], str[max_index]);

				return stoi(str);
			}
		};
	}

	namespace task_673 {
		/*
		* https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/
		*/
		class Solution {
		public:
			int findNumberOfLIS(vector<int>& nums) {
				const size_t size = nums.size();
				size_t length = 0;
				vector<vector<pair<int, int>>> ends_counts_of_LIS(size);

				for (size_t i = 0; i < size; i++) {
					size_t j = search(ends_counts_of_LIS, length, nums[i]);

					int count = 0;
					if (j > 0)
						for (size_t k = 0; k < ends_counts_of_LIS[j - 1].size(); k++) {
							if (ends_counts_of_LIS[j - 1][k].first < nums[i])
								count += ends_counts_of_LIS[j - 1][k].second;
						}
					else
						count = 1;
					ends_counts_of_LIS[j].push_back({ nums[i] , count });
					length = max(j + 1, length);
				}
				int count = 0;
				for (size_t k = 0; k < ends_counts_of_LIS[length - 1].size(); k++)
						count += ends_counts_of_LIS[length - 1][k].second;
				return count;
			}

			size_t search(const vector<vector<pair<int, int>>>& nums, size_t r, const int target) {
				size_t l = 0;
				if (!nums[l].empty() && nums[l].back().first >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i].back().first >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_674 {
		/*
		* https://leetcode.com/problems/longest-continuous-increasing-subsequence/description/
		*/
		class Solution {
		public:
			int findLengthOfLCIS(vector<int>& nums) {
				const size_t size = nums.size();
				size_t length = 1;
				size_t max_length = 1;

				for (size_t i = 1; i < size; i++)
					if (nums[i] > nums[i - 1])
						++length;
					else {
						if (max_length < length)
							max_length = length;
						length = 1;
					}
				if (max_length < length)
					max_length = length;
				return max_length;
			}
		};
	}

	namespace task_684 {
		/*
		* https://leetcode.com/problems/redundant-connection/description/
		*/
		class Solution {
		public:
			vector<int> findRedundantConnection(vector<vector<int>>& edges) {
				unordered_map<int, int> union_find;
				for (const auto& edge : edges) {
					int set0 = getUnion(union_find, edge[0]);
					int set1 = getUnion(union_find, edge[1]);
					if (set0 == set1)
						return edge;
					int max_set = max(set0, set1);
					set0 = min(set0, set1);
					union_find[max_set] = set0;
				}
				return {};
			}

			int getUnion(unordered_map<int, int>& union_find, const int vertex) {
				if (!union_find.contains(vertex)) {
					union_find[vertex] = vertex;
					return vertex;
				}
				int set = union_find[vertex];
				while (set != union_find[set])
					set = union_find[set];
				union_find[vertex] = set;
				return set;
			}
		};
	}

	namespace task_689 {
		/*
		* https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
		*/
		class Solution {
		public:
			vector<int> maxSumOfThreeSubarrays__leetcode(vector<int>& nums, int k) {
				// Variables to track the best indices for one, two, and three subarray
				// configurations
				int bestSingleStart = 0;
				vector<int> bestDoubleStart = { 0, k };
				vector<int> bestTripleStart = { 0, k, k * 2 };

				// Compute the initial sums for the first three subarrays
				int currentWindowSumSingle = 0;
				for (int i = 0; i < k; i++) {
					currentWindowSumSingle += nums[i];
				}

				int currentWindowSumDouble = 0;
				for (int i = k; i < k * 2; i++) {
					currentWindowSumDouble += nums[i];
				}

				int currentWindowSumTriple = 0;
				for (int i = k * 2; i < k * 3; i++) {
					currentWindowSumTriple += nums[i];
				}

				// Track the best sums found so far
				int bestSingleSum = currentWindowSumSingle;
				int bestDoubleSum = currentWindowSumSingle + currentWindowSumDouble;
				int bestTripleSum = currentWindowSumSingle + currentWindowSumDouble +
					currentWindowSumTriple;

				// Sliding window pointers for the subarrays
				int singleStartIndex = 1;
				int doubleStartIndex = k + 1;
				int tripleStartIndex = k * 2 + 1;

				// Slide the windows across the array
				while (tripleStartIndex <= nums.size() - k) {
					// Update the sums using the sliding window technique
					currentWindowSumSingle = currentWindowSumSingle -
						nums[singleStartIndex - 1] +
						nums[singleStartIndex + k - 1];
					currentWindowSumDouble = currentWindowSumDouble -
						nums[doubleStartIndex - 1] +
						nums[doubleStartIndex + k - 1];
					currentWindowSumTriple = currentWindowSumTriple -
						nums[tripleStartIndex - 1] +
						nums[tripleStartIndex + k - 1];

					// Update the best single subarray start index if a better sum is
					// found
					if (currentWindowSumSingle > bestSingleSum) {
						bestSingleStart = singleStartIndex;
						bestSingleSum = currentWindowSumSingle;
					}

					// Update the best double subarray start indices if a better sum is
					// found
					if (currentWindowSumDouble + bestSingleSum > bestDoubleSum) {
						bestDoubleStart[0] = bestSingleStart;
						bestDoubleStart[1] = doubleStartIndex;
						bestDoubleSum = currentWindowSumDouble + bestSingleSum;
					}

					// Update the best triple subarray start indices if a better sum is
					// found
					if (currentWindowSumTriple + bestDoubleSum > bestTripleSum) {
						bestTripleStart[0] = bestDoubleStart[0];
						bestTripleStart[1] = bestDoubleStart[1];
						bestTripleStart[2] = tripleStartIndex;
						bestTripleSum = currentWindowSumTriple + bestDoubleSum;
					}

					// Move the sliding windows forward
					singleStartIndex += 1;
					doubleStartIndex += 1;
					tripleStartIndex += 1;
				}

				// Return the starting indices of the three subarrays with the maximum
				// sum
				return bestTripleStart;
			}
		};
	}

	namespace task_697 {
		/*
		* https://leetcode.com/problems/degree-of-an-array/description/
		*/
		class Solution {
		public:
			int findShortestSubArray(vector<int>& nums) {
				const size_t size = nums.size();
				const size_t max_value = 50000;
				vector<int> degres(max_value);
				vector<int> starts(max_value, -1);
				vector<int> ends(max_value);

				int max_degree = 1;
				for (size_t i = 0; i < size; i++) {
					if (starts[nums[i]] == -1)
						starts[nums[i]] = i;
					ends[nums[i]] = i;
					++degres[nums[i]];

					max_degree = max(max_degree, degres[nums[i]]);
				}

				int min_length = size;
				for (size_t i = 0; i < size; i++)
					if (degres[nums[i]] == max_degree)
						min_length = min(min_length, ends[nums[i]] - starts[nums[i]] + 1);
				return min_length;
			}
		};
	}

	namespace task_703 {
		/*
		* https://leetcode.com/kth-largest-element-in-a-stream/description/
		*/
		class KthLargest { // Heap 97%, 17%
		public:
			priority_queue<int, vector<int>, greater<int>> minHeap;
			int k;
			KthLargest(int k, vector<int>& nums) {
				this->k = k;

				for (const int num : nums)
					minHeap.push(num);
				while (minHeap.size() > k)
					minHeap.pop();
			}

			int add(int val) {
				minHeap.push(val);
				if (minHeap.size() > k)
					minHeap.pop();
				return minHeap.top();
			}
		};

		class KthLargestSet { // Set 5%, 5%
		public:
			multiset<int> nums;
			int k;
			KthLargestSet(int k, vector<int>& nums) : nums(nums.begin(), nums.end()), k(k) {
				while (this->nums.size() > k)
					this->nums.erase(this->nums.begin());
			}

			int add(int val) {
				nums.insert(val);
				if (nums.size() > k)
					nums.erase(nums.begin());
				auto it = nums.end();
				advance(it, -k);
				return *it;
			}
		};
	}

	namespace task_704 {
		/*
		* https://leetcode.com/problems/binary-search/description/
		*/
		class Solution {
		public:
			int search(vector<int>& nums, int target) {
				size_t l = 0;
				size_t r = nums.size();

				if (nums[l] == target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == target)
						return i;
					if (nums[i] > target)
						r = i;
					else
						l = i;
				}
				return -1;
			}
		};
	}

	namespace task_705 {
		/*
		* https://leetcode.com/problems/design-hashset/
		*/
		class MyHashSet {
		public:
			vector<vector<int>> storage;
			MyHashSet() :storage(1001) {}

			void add(int key) {
				auto& sub_store = storage[key / 1000];
				bool not_found = true;
				for (int val : sub_store)
					if (val == key) {
						not_found = false;
						break;
					}
				if (not_found)
					sub_store.push_back(key);
			}

			void remove(int key) {
				auto& sub_store = storage[key / 1000];
				bool found = false;
				size_t i = 0;
				for (; i < sub_store.size(); i++) {
					if (sub_store[i] == key) {
						found = true;
						break;
					}
				}

				if (found)
					sub_store.erase(sub_store.begin() + i);
			}

			bool contains(int key) {
				auto& sub_store = storage[key / 1000];
				bool found = false;
				for (int val : sub_store)
					if (val == key) {
						found = true;
						break;
					}
				return found;
			}
		};
	}

	namespace task_706 {
		/*
		* https://leetcode.com/problems/design-hashmap/description/
		*/
		class MyHashMap {
		public:
			vector<vector<pair<int, int>>> storage;
			MyHashMap() :storage(1001) {}

			void put(int key, int value) {
				auto& sub_store = storage[key / 1000];
				for (auto& val : sub_store)
					if (val.first == key) {
						val.second = value;
						return;
					}
				sub_store.push_back({ key, value });
			}

			int get(int key) {
				auto& sub_store = storage[key / 1000];
				for (auto& val : sub_store)
					if (val.first == key)
						return val.second;
				return -1;
			}

			void remove(int key) {
				auto& sub_store = storage[key / 1000];
				bool found = false;
				size_t i = 0;
				for (; i < sub_store.size(); i++) {
					if (sub_store[i].first == key) {
						found = true;
						break;
					}
				}

				if (found)
					sub_store.erase(sub_store.begin() + i);
			}
		};
	}

	namespace task_707 {
		/*
		* https://leetcode.com/problems/design-linked-list/description/
		*/
		class MyLinkedList {
		public:
			ListNode* guard;
			ListNode* tail;
			size_t size;

			MyLinkedList() : guard(new ListNode()), tail(guard), size(0) { }
			~MyLinkedList() {
				ListNode* temp;
				while (guard) {
					temp = guard->next;
					delete guard;
					guard = temp;
				}
			}

			int get(int index) {
				if (size <= index)
					return -1;
				ListNode* ptr = guard->next;
				for (size_t i = 0; i < index; i++)
					ptr = ptr->next;
				return ptr->val;
			}

			ListNode* getList() {
				return guard->next;
			}

			void addAtHead(int val) {
				guard->next = new ListNode(val, guard->next);
				++size;
				if (size == 1)
					tail = guard->next;
			}

			void addAtTail(int val) {
				tail->next = new ListNode(val);
				tail = tail->next;
				++size;
			}

			void addAtIndex(int index, int val) {
				if (size == index) {
					addAtTail(val);
					return;
				}
				if (size < index)
					return;
				++size;
				ListNode* ptr = guard;
				for (size_t i = 0; i < index; i++)
					ptr = ptr->next;
				ptr->next = new ListNode(val, ptr->next);
			}

			void deleteAtIndex(int index) {
				if (size <= index)
					return;
				--size;
				ListNode* ptr = guard;
				ListNode* temp;
				for (size_t i = 0; i < index; i++)
					ptr = ptr->next;
				temp = ptr->next;
				ptr->next = ptr->next->next;
				if (index == size)
					tail = ptr;
				delete temp;
			}
		};
	}

	namespace task_712 {
		/*
		* https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/description/
		*/
		class Solution {
		public:
			int minDistance(string s1, string s2) {
				const size_t size1 = s1.size() + 1;
				const size_t size2 = s2.size() + 1;
				vector<vector<int>> result(size1, vector<int>(size2));
				result[0][0] = 0;
				for (size_t j = 1; j < size2; j++)
					result[0][j] = result[0][j - 1] + s2[j - 1];
				for (size_t i = 1; i < size1; i++)
					result[i][0] = result[i - 1][0] + s1[i - 1];

				for (size_t i = 1; i < size1; i++)
					for (size_t j = 1; j < size2; j++)
						result[i][j] = min(min(result[i][j - 1] + s2[j - 1], result[i - 1][j] + s1[i - 1]),
							result[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : (s1[i - 1] + s2[j - 1])));
				return result.back().back();
			}
		};
	}

	namespace task_714 {
		/*
		* https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
		*/
		class Solution {
		public:
			int maxProfit(vector<int>& prices, int fee) {
				int prev_buy = 0, curr_buy = 0;
				int prev_sell = 0, curr_sell = 0;
				for (int i = prices.size() - 1; i >= 0; --i)
				{
					curr_buy = max(-prices[i] + prev_sell, prev_buy);
					curr_sell = max(prices[i] - fee + prev_buy, prev_sell);
					prev_buy = curr_buy;
					prev_sell = curr_sell;
				}
				return curr_buy;
			}
		};
	}

	namespace task_725 {
		/*
		* https://leetcode.com/problems/split-linked-list-in-parts/description/
		*/
		class Solution {
		public:
			vector<ListNode*> splitListToParts(ListNode* head, int k) {
				size_t size = 0;
				ListNode* ptr = head;
				for (; ptr; ptr = ptr->next, ++size) {}

				vector<ListNode*> res(k);
				size_t length = size / k;
				size_t extra = size % k;
				size_t i = 0;
				for (; i < extra; ++i) {
					ptr = head;
					for (size_t j = 0; j < length; ++j, ptr = ptr->next) {}
					res[i] = head;
					head = ptr->next;
					ptr->next = nullptr;
				}

				if (size >= k)
					for (; i < k; ++i) {
						ptr = head;
						for (size_t j = 1; j < length; ++j, ptr = ptr->next) {}
						res[i] = head;
						head = ptr->next;
						ptr->next = nullptr;
					}
				return res;
			}
		};
	}

	namespace task_726 {
		/*
		* https://leetcode.com/problems/number-of-atoms/description/
		*/
		class Solution {
		public:
			string countOfAtoms(string formula) {
				size_t i = 0;
				string res;
				formula.push_back(')');
				auto atoms = countOfAtoms(formula, i);
				for (const auto& [atom, count] : atoms) {
					res += atom;
					if (count > 1)
						res += to_string(count);
				}
				return res;
			}

			map<string, int> countOfAtoms(const string& formula, size_t& i) {
				map<string, int> atoms;
				while (formula[i] != ')') {
					if (formula[i] == '(') {
						auto atoms_bracket = countOfAtoms(formula, ++i);
						auto mult = readNumber(formula, ++i);
						for (const auto& [atom, count] : atoms_bracket)
							if (auto it = atoms.find(atom); it != atoms.end())
								it->second += count * mult;
							else
								atoms[atom] = count * mult;
					}
					else {
						auto atom = readAtom(formula, i);
						auto count = readNumber(formula, i);
						if (auto it = atoms.find(atom); it != atoms.end())
							it->second += count;
						else
							atoms[atom] = count;
					}
				}
				return atoms;
			}

			int readNumber(const string& formula, size_t& i) {
				size_t from = i;
				for (; formula[i] >= '0' && formula[i] <= '9'; ++i) {}
				return from == i ? 1 : stoi(formula.substr(from, i - from));
			}

			string readAtom(const string& formula, size_t& i) {
				size_t from = i++;
				for (; formula[i] >= 'a' && formula[i] <= 'z'; ++i) {}
				return formula.substr(from, i - from);
			}
		};
	}

	namespace task_729 {
		/*
		* https://leetcode.com/problems/my-calendar-i/description/
		*/
		class MyCalendar {
		public:
			map<int, int, greater<int>> booking;
			MyCalendar() { }

			bool book(int start, int end) {
				auto it = booking.lower_bound(start);
				if (it != booking.end() && it->second > start)
					return false;
				it = booking.upper_bound(end);
				if (it != booking.end() && it->second > start)
					return false;
				booking[start] = end;
				return true;
			}
		};
	}

	namespace task_731 {
		/*
		* https://leetcode.com/problems/my-calendar-ii/description/
		*/
		class MyCalendarTwo {
		public:
			map<int, int, greater<int>> booking;
			map<int, int, greater<int>> double_booking;
			MyCalendarTwo() { }

			bool book(int start, int end) {
				auto it = double_booking.lower_bound(start); // check if is there double overlapping
				if (it != double_booking.end() && it->second > start)
					return false;
				it = double_booking.upper_bound(end);
				if (it != double_booking.end() && it->second > start)
					return false;

				it = booking.lower_bound(end);
				if (it == booking.end() || it->second < start) { // old interval is before new
					booking[start] = end;
					return true;
				}
				if (it->second == start) { // old interval ends on start of new
					it->second = end;
					return true;
				}

				int left = start, right = end;
				if (it->first == end) { // old interval starts on end of new
					right = it->second;
					++it;
					booking.erase(end);
					if (it == booking.end()) { // if no interval to the left
						booking[left] = right;
						return true;
					}
				}
				if (right < it->second) // it will be deleted, we can change it
					swap(right, it->second);

				while (it != booking.end() && it->second > start) {
					int key = it->first;
					int overlap_start = max(it->first, start);
					int overlap_end = it->second;
					double_booking[overlap_start] = overlap_end;
					++it;
					booking.erase(key);
					left = min(left, key);
				}

				if (it != booking.end() && it->second == start) { // unite intervals if old interval ends on start of new
					left = it->first;
					booking.erase(it);
				}

				booking[left] = right;
				return true;
			}
		};
	}

	namespace task_732 {
		/*
		* https://leetcode.com/problems/my-calendar-iii/description/
		*/
		class MyCalendarThree {
		public:
			map<int, pair<int, int>, greater<int>> booking; // depth-end
			int max_depth = 1;
			MyCalendarThree() { }

			int book(int start, int end) { // all time maximum
				auto it = booking.upper_bound(end);
				if (it == booking.end()) {
					booking[start] = { 1, end };
					return max_depth;
				}
				if (it->second.second <= start) {
					booking[start] = { 1, end };
					return max_depth;
				}


				int left = start, right = end;
				if (it->second.second > end) {
					if (it->first < start) {
						booking[end] = it->second;
						booking[start] = { it->second.first + 1, end };
						it->second.second = start;
						max_depth = max(max_depth, it->second.first + 1);
						return max_depth;
					}

					right = it->second.second;
					booking[end] = it->second;
					++it->second.first;
					it->second.second = end;
					max_depth = max(max_depth, it->second.first);
					end = it->first;
					++it;
				}

				while (it != booking.end() && it->first >= start) {
					++it->second.first;
					max_depth = max(max_depth, it->second.first);
					if (end > it->second.second)
						booking[it->second.second] = { 1, end };
					end = it->first;
					++it;
				}

				if (start != end) {
					if (it == booking.end() || it->second.second <= start) {
						booking[start] = { 1, end };
					}
					else {
						if (it->second.second < end)
							booking[it->second.second] = { 1, end };
						booking[start] = { it->second.first + 1, it->second.second };
						max_depth = max(max_depth, it->second.first + 1);
						it->second.second = start;
					}
				}
				return max_depth;
			}

			map<int, pair<int, int>, greater<int>> max_depth_booking; // depth-end
			int bookMy_not_works(int start, int end) { // maximum among the affected intervals
				auto it = booking.upper_bound(end);
				if (it == booking.end()) {
					booking[start] = { 1, end };
					max_depth_booking[start] = { 1, end };
					return 1;
				}
				if (it->second.second <= start) {
					booking[start] = { 1, end };
					max_depth_booking[start] = { 1, end };
					return 1;
				}


				int max_depth = 1, left = start, right = end;
				if (it->second.second > end) {
					if (it->first < start) {
						booking[end] = it->second;
						booking[start] = { it->second.first + 1, end };
						it->second.second = start;
						auto depth_it = max_depth_booking.lower_bound(it->first);
						depth_it->second.first = max(depth_it->second.first, it->second.first + 1);
						return depth_it->second.first;
					}

					right = it->second.second;
					booking[end] = it->second;
					++it->second.first;
					it->second.second = end;
					max_depth = max(max_depth, it->second.first);
					end = it->first;
					++it;
				}

				while (it != booking.end() && it->first >= start) {
					++it->second.first;
					max_depth = max(max_depth, it->second.first);
					if (end > it->second.second)
						booking[it->second.second] = { 1, end };
					end = it->first;
					++it;
				}

				if (start != end) {
					if (it == booking.end() || it->second.second <= start) {
						booking[start] = { 1, end };
					}
					else {
						if (it->second.second < end)
							booking[it->second.second] = { 1, end };
						booking[start] = { it->second.first + 1, it->second.second };
						max_depth = max(max_depth, it->second.first + 1);
						it->second.second = start;
					}
				}

				auto depth_it = max_depth_booking.upper_bound(right);
				right = max(right, depth_it->second.second);
				while (depth_it != max_depth_booking.end() && depth_it->second.second > start) {
					int key = depth_it->first;
					max_depth = max(max_depth, depth_it->second.first);
					++depth_it;
					max_depth_booking.erase(key);
					left = min(left, key);
				}
				max_depth_booking[left] = { max_depth , right };
				return max_depth;
			}
		};
	}

	namespace task_740 {
		/*
		* https://leetcode.com/problems/delete-and-earn/description/
		*/
		class Solution {
		public:
			int deleteAndEarn(vector<int>& nums) {
				sort(nums.begin(), nums.end());
				reverse(nums.begin(), nums.end());
				size_t size = nums.size();

				vector<vector<int>> num_count_points;
				for (size_t i = 0; i < size;) {
					int last = nums[i];
					num_count_points.push_back(vector<int>({ last , 0, 0 }));
					for (; i < size && nums[i] == last; ++i)
						++num_count_points.back()[1];
					num_count_points.back()[2] = last * num_count_points.back()[1];
				}
				size = num_count_points.size();
				int global_max_points = num_count_points[0][2];
				for (size_t i = 1; i < size; ++i) {
					int prev_points = num_count_points[i][0] + 1 != num_count_points[i - 1][0] ?
						num_count_points[i - 1][2] :
						0;
					int prev_prev_points = i > 1 ?
						num_count_points[i - 2][2] :
						0;
					int prev_prev_prev_points = i > 2 ?
						num_count_points[i - 3][2] :
						0;
					num_count_points[i][2] += max(max(prev_points, prev_prev_points), prev_prev_prev_points);

					if (global_max_points < num_count_points[i][2])
						global_max_points = num_count_points[i][2];
				}
				return global_max_points;
			}
		};
	}

	namespace task_744 {
		/*
		* https://leetcode.com/problems/find-smallest-letter-greater-than-target/description/
		*/
		class Solution {
		public:
			char nextGreatestLetter(vector<char>& letters, char target) {
				size_t l = 0;
				size_t r = letters.size() - 1;

				if (letters[l] > target || letters[r] <= target)
					return letters[l];

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (letters[i] > target)
						r = i;
					else
						l = i;
				}
				return letters[r];
			}
		};
	}

	namespace task_746 {
		/*
		* https://leetcode.com/problems/min-cost-climbing-stairs/description/
		*/
		class Solution {
		public:
			int minCostClimbingStairs(vector<int>& cost) {
				const size_t size = cost.size();
				for (size_t i = 2; i < size; i++)
					cost[i] += min(cost[i - 1], cost[i - 2]);
				return min(cost[size - 1], cost[size - 2]);
			}
		};
	}

	namespace task_763 {
		/*
		* https://leetcode.com/problems/partition-labels/description/
		*/
		class Solution {
		public:
			vector<int> partitionLabels(string s) {
				vector<pair<int, int>> firts_last_appears(26, { -1, -1 });
				const int size = s.size();
				for (int i = 0; i < size; ++i) {
					if (firts_last_appears[s[i] - 'a'].second == -1)
						firts_last_appears[s[i] - 'a'].first = i;
					firts_last_appears[s[i] - 'a'].second = i;
				}

				int start = -1, end = 0;
				vector<int> res;
				for (int i = 0; i < size; ++i) {
					end = max(end, firts_last_appears[s[i] - 'a'].second);
					if (i == end) {
						res.push_back(end - start);
						start = i;
					}
				}
				return res;
			}
		};
	}

	namespace task_769 {
		/*
		* https://leetcode.com/problems/max-chunks-to-make-sorted/description/
		*/
		class Solution {
		public:
			int maxChunksToSorted(vector<int>& arr) {
				int n = arr.size(), i = 0, max_found = 0, chunks = 0;
				while (i != n) {
					max_found = arr[i];
					while (max_found != i) {
						++i;
						max_found = max(max_found, arr[i]);
					}
					++i;
					++chunks;
				}
				return chunks;
			}
		};
	}

	namespace task_773 {
		/*
		* https://leetcode.com/problems/sliding-puzzle/description/
		*/
		class Solution {
		public:
			int slidingPuzzle__leetcode(vector<vector<int>>& board) {
				// Direction map for zero's possible moves in a 1D representation of the
				// 2x3 board
				vector<vector<int>> directions = { {1, 3}, {0, 2, 4}, {1, 5},
												  {0, 4}, {1, 3, 5}, {2, 4} };

				string target = "123450";
				string startState;

				// Convert the 2D board into a string representation
				for (int i = 0; i < board.size(); i++) {
					for (int j = 0; j < board[0].size(); j++) {
						startState += to_string(board[i][j]);
					}
				}

				unordered_set<string> visited;  // To store visited states
				queue<string> queue;
				queue.push(startState);
				visited.insert(startState);

				int moves = 0;

				// BFS to find the minimum number of moves
				while (!queue.empty()) {
					int size = queue.size();
					while (size-- > 0) {
						string currentState = queue.front();
						queue.pop();

						// Check if we reached the target solved state
						if (currentState == target) {
							return moves;
						}

						int zeroPos = currentState.find('0');
						for (int newPos : directions[zeroPos]) {
							string nextState = currentState;
							swap(nextState[zeroPos], nextState[newPos]);

							// Skip if this state has been visited
							if (visited.count(nextState)) continue;

							// Mark the new state as visited and add it to the queue
							visited.insert(nextState);
							queue.push(nextState);
						}
					}
					moves++;
				}
				return -1;
			}
		};
	}

	namespace task_781 {
		/*
		* https://leetcode.com/problems/rabbits-in-forest/description/
		*/
		class Solution {
		public:
			int numRabbits(vector<int>& answers) { //100%; 10.59%
				unordered_map<int, int> same_answers;
				for (const int a : answers)
					++same_answers[a];
				int num_rabbits = 0;
				for (auto [answer, count] : same_answers)
					num_rabbits += ceil((double)count / (answer + 1)) * (answer + 1);
				return num_rabbits;
			}

			int numRabbits__sorting(vector<int>& answers) { //100%; 96.43%
				sort(answers.begin(), answers.end());
				size_t size = answers.size();
				int answer = answers[0], count = 1, num_rabbits = 0;
				for (size_t i = 1; i < size; ++i) {
					if (answers[i] == answer) {
						++count;
					}
					else {
						num_rabbits += ceil((double)count / (answer + 1)) * (answer + 1);
						answer = answers[i];
						count = 1;
					}
				}
				num_rabbits += ceil((double)count / (answer + 1)) * (answer + 1);
				return num_rabbits;
			}
		};
	}

	namespace task_785 {
		/*
		* https://leetcode.com/problems/is-graph-bipartite/description/
		*/
		class Solution {
		public:
			int isBipartite(vector<vector<int>>& graph) {
				vector<int> visited(graph.size());
				queue<size_t> vertexes;
				for (size_t i = 0; i < graph.size(); ++i)
					if (visited[i] == 0) {
						int half = 1, next_half = 2;
						vertexes.push(i);
						visited[i] = half;
						while (!vertexes.empty()) {
							size_t q_size = vertexes.size();
							for (size_t j = 0; j < q_size; ++j)
							{
								size_t vertex = vertexes.front();
								vertexes.pop();
								for (const int neighbour : graph[vertex]) {
									if (visited[neighbour] == half)
										return false;
									if (visited[neighbour] == 0) {
										vertexes.push(neighbour);
										visited[neighbour] = next_half;
									}
								}
							}
							swap(half, next_half);
						}
					}
				return true;
			}
		};

	}

	namespace task_787 {
		/*
		* https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
		*/
		class Solution {
		public:
			int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
				vector<vector<pair<int, int>>> adjacency_list(n);
				for (const auto& flight : flights)
					adjacency_list[flight[0]].push_back({ flight[1], flight[2] });

				vector<int> dist(n, INT32_MAX);
				queue<vector<int>> q; // from, dist, count flights
				q.push({ src , 0, 0 });
				while (!q.empty()) {
					auto vertex = q.front();
					q.pop();
					if (dist[vertex[0]] > vertex[1]) {
						dist[vertex[0]] = vertex[1];
						if (vertex[2] <= k)
							for (const auto& dest : adjacency_list[vertex[0]])
								if (dist[dest.first] > vertex[1] + dest.second)
									q.push({ dest.first, vertex[1] + dest.second, vertex[2] + 1 });
					}
				}
				return dist[dst] == INT32_MAX ? -1 : dist[dst];
			}
		};
	}

	namespace task_790 {
		/*
		* https://leetcode.com/problems/domino-and-tromino-tiling/description/
		*/
		class Solution {
		public:
			const long long mod = 1000000007;

			int numTilings(int n) {
				vector<long long> last_three({ 1, 2, 5 });
				for (int i = 3; i < n; ++i)
					last_three[(i - 3) % 3] = (
						last_three[(i - 1) % 3] * 2 +
						last_three[(i - 3) % 3]) % mod;

				return last_three[(n - 1) % 3];
			}
		};
	}

	namespace task_796 {
		/*
		* https://leetcode.com/problems/rotate-string/description/
		*/
		class Solution {
		public:
			bool rotateString(string s, string goal) {
				size_t size = s.size();
				if (size != goal.size())
					return false;
				for (size_t i = 0; i < size; ++i)
					if (s[0] == goal[i] && rotateString(s, goal, i, size))
						return true;

				return false;
			}


			bool rotateString(const string& s, const string& goal, const size_t from, const size_t size) {
				size_t i = 1;
				for (; i < size && s[i] == goal[(from + i) % size]; ++i) {}
				return i == size;
			}
		};
	}

	namespace task_802 {
		/*
		* https://leetcode.com/problems/find-eventual-safe-states/description/
		*/
		class Solution {
		public:
			vector<int> used;

			vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
				const size_t size = graph.size();
				vector<int> answer;
				used = vector<int>(size);
				int count = 0, count_prev;
				for (int i = 0; i < size; ++i) {
					if (used[i] == 0)
						dfs(i, graph);
					if (used[i] == 2)
						answer.push_back(i);
				}

				return answer;
			}

			bool dfs(int v, const vector<vector<int>>& graph) {
				used[v] = 1;
				for (const int vertex : graph[v]) {
					if (used[vertex] == 1)
						return false;
					else if (used[vertex] == 0)
						if (!dfs(vertex, graph))
							return false;
				}

				used[v] = 2;
				return true;
			}
		};
	}

	namespace task_817 {
		/*
		* https://leetcode.com/problems/linked-list-components/
		*/
		class Solution {
		public:
			size_t size;
			int numComponents(ListNode* head, vector<int>& nums) {
				sort(nums.begin(), nums.end());
				size = nums.size();
				int count = 0;
				bool contain_el;
				while (head) {
					contain_el = contain(nums, head->val);
					if (contain_el) {
						++count;
						while (contain_el) {
							head = head->next;
							if (head)
								contain_el = contain(nums, head->val);
							else
								return count;
						}
					}
					head = head->next;
				}
				return count;
			}

			bool contain(const vector<int>& nums, int target) {
				size_t l = 0;
				size_t r = size;
				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] > target)
						r = i;
					else
						l = i;
				}
				return nums[l] == target;
			}
		};
	}

	namespace task_826 {
		/*
		* https://leetcode.com/problems/most-profit-assigning-work/description/
		*/
		class Solution {
		public:
			int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
				sort(worker.begin(), worker.end());
				size_t size = difficulty.size();
				vector<pair<int, int>> not_allowed_projects(size);
				priority_queue<int> profits;
				int res = 0;

				for (size_t i = 0; i < size; ++i)
					not_allowed_projects[i] = { difficulty[i],profit[i] };
				sort(not_allowed_projects.begin(), not_allowed_projects.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
					return a.first > b.first;
					});
				for (const int work : worker) {
					while (!not_allowed_projects.empty() && not_allowed_projects.back().first <= work) {
						profits.push(not_allowed_projects.back().second);
						not_allowed_projects.pop_back();
					}
					if (!profits.empty())
						res += profits.top();
				}
				return res;
			}
		};
	}

	namespace task_827 {
		/*
		* https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/description/
		*/
		class Solution {
		public:


			int largestIsland(vector<vector<int>>& grid) {
				const int n = grid.size();
				queue<pair<int, int>> queue;
				unordered_map<int, int> islands_square;
				int island_id = 2, max_square = 1;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (grid[i][j] == 1) {
							queue.push({ i, j });
							int square = 1;
							grid[i][j] = island_id;
							while (!queue.empty()) {
								auto& pos = queue.front();
								if (pos.first + 1 != n && grid[pos.first + 1][pos.second] == 1) {
									++square;
									grid[pos.first + 1][pos.second] = island_id;
									queue.push({ pos.first + 1, pos.second });
								}
								if (pos.second + 1 != n && grid[pos.first][pos.second + 1] == 1) {
									++square;
									grid[pos.first][pos.second + 1] = island_id;
									queue.push({ pos.first, pos.second + 1 });
								}
								if (pos.first - 1 != -1 && grid[pos.first - 1][pos.second] == 1) {
									++square;
									grid[pos.first - 1][pos.second] = island_id;
									queue.push({ pos.first - 1, pos.second });
								}
								if (pos.second - 1 != -1 && grid[pos.first][pos.second - 1] == 1) {
									++square;
									grid[pos.first][pos.second - 1] = island_id;
									queue.push({ pos.first, pos.second - 1 });
								}
								queue.pop();
							}
							islands_square[island_id++] = square;
							max_square = max(max_square, square);
						}
					}
				}

				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (grid[i][j] == 0) {
							int square = 1;
							unordered_set<int> islands;
							if (i + 1 != n && grid[i + 1][j] != 0) {
								square += islands_square[grid[i + 1][j]];
								islands.insert(grid[i + 1][j]);
							}
							if (j + 1 != n && grid[i][j + 1] != 0 && !islands.contains(grid[i][j + 1])) {
								square += islands_square[grid[i][j + 1]];
								islands.insert(grid[i][j + 1]);
							}
							if (i - 1 != -1 && grid[i - 1][j] != 0 && !islands.contains(grid[i - 1][j])) {
								square += islands_square[grid[i - 1][j]];
								islands.insert(grid[i - 1][j]);
							}
							if (j - 1 != -1 && grid[i][j - 1] != 0 && !islands.contains(grid[i][j - 1])) {
								square += islands_square[grid[i][j - 1]];
								islands.insert(grid[i][j - 1]);
							}
							max_square = max(max_square, square);
						}
					}
				}
				return max_square;
			}
		};
	}

	namespace task_838 {
		/*
		* https://leetcode.com/problems/push-dominoes/description/
		*/
		class Solution {
		public:

			string pushDominoes(string dominoes) {
				int size = dominoes.size();
				for (int i = 0; i < size;) {
					for (; i < size && dominoes[i] == '.'; ++i) {}
					if (i == size)
						break;
					if (dominoes[i] == 'L') {
						for (int j = i - 1; j >= 0 && dominoes[j] == '.'; --j)
							dominoes[j] = 'L';
						++i;
					}
					else {
						++i;
						int j = i;
						for (; j < size && dominoes[j] == '.'; ++j) {}
						if (j == size || dominoes[j] == 'R') {
							for (; i < j; ++i)
								dominoes[i] = 'R';
						}
						else {
							for (int k = j - 1; i < k; ++i, --k) {
								dominoes[i] = 'R';
								dominoes[k] = 'L';
							}
							i = j + 1;
						}
					}
				}
				return dominoes;
			}
		};
	}

	namespace task_840 {
		/*
		* https://leetcode.com/problems/magic-squares-in-grid/description/
		*/
		class Solution {
		public:
			vector<int> used;

			int numMagicSquaresInside(vector<vector<int>>& grid) {
				size_t height = grid.size(), width = grid[0].size();
				used = vector<int>(10);
				int count = 0;
				for (size_t i = 2; i < height; ++i)
					for (size_t j = 2; j < width; ++j)
						if (check(grid, i - 2, j - 2))
							++count;
				return count;
			}

			bool check(const vector<vector<int>>& grid, const size_t i, const size_t j) {
				bool res =
					grid[i][j] + grid[i][j + 1] + grid[i][j + 2] == 15 &&
					grid[i + 1][j] + grid[i + 1][j + 1] + grid[i + 1][j + 2] == 15 &&
					grid[i + 2][j] + grid[i + 2][j + 1] + grid[i + 2][j + 2] == 15 &&
					grid[i][j] + grid[i + 1][j] + grid[i + 2][j] == 15 &&
					grid[i][j + 1] + grid[i + 1][j + 1] + grid[i + 2][j + 1] == 15 &&
					grid[i][j + 2] + grid[i + 1][j + 2] + grid[i + 2][j + 2] == 15 &&
					grid[i][j] + grid[i + 1][j + 1] + grid[i + 2][j + 2] == 15 &&
					grid[i][j + 2] + grid[i + 1][j + 1] + grid[i + 2][j] == 15;
				if (res) {
					for (size_t a = 0; a < 3; ++a)
						for (size_t b = 0; b < 3; ++b) {
							if (grid[i + a][j + b] > 9 || grid[i + a][j + b] < 1 || used[grid[i + a][j + b]]) {
								a = 3;
								res = false;
								break;
							}
							used[grid[i + a][j + b]] = 1;
						}
					for (int& n : used)
						n = 0;
				}
				return res;
			}
		};
	}

	namespace task_844 {
		/*
		* https://leetcode.com/problems/backspace-string-compare/description/
		*/
		class Solution {
		public:
			bool backspaceCompare(string s, string t) {
				int i = s.length() - 1, j = t.length() - 1;
				while (i >= 0 || j >= 0) {
					int steps = 0;
					while (i >= 0 && (s[i] == '#' || steps > 0)) {
						if (s[i] == '#')
							++steps;
						else
							--steps;
						--i;
					}
					steps = 0;
					while (j >= 0 && (t[j] == '#' || steps > 0)) {
						if (t[j] == '#')
							++steps;
						else
							--steps;
						--j;
					}
					if (i < 0 && j < 0)
						return true;
					if (i < 0 || j < 0 || s[i] != t[j])
						return false;
					--i;
					--j;
				}

				return i == j;
			}

			bool backspaceCompare2(string s, string t) {
				string s_copy;
				string t_copy;
				for (size_t i = 0; i < s.length(); i++)
					if (i + 1 < s.length() && s[i + 1] == '#')
						++i;
					else
						s_copy.push_back(s[i]);

				for (size_t i = 0; i < t.length(); i++)
					if (i + 1 < t.length() && t[i + 1] == '#')
						++i;
					else
						t_copy.push_back(t[i]);

				return s_copy == t_copy;
			}
		};
	}

	namespace task_845 {
		/*
		* https://leetcode.com/problems/longest-mountain-in-array/description/
		*/
		class Solution { // 90.91% 39.13%
		public:
			int longestMountain(vector<int>& nums) {
				int size = nums.size(), max_len = 0, len = 0;
				for (int i = 0; i < size; i++) {
					len = 0;
					int j = i + 1;
					for (; j < size && nums[j - 1] < nums[j]; ++j) {}
					if (j == i + 1)
						continue;
					if (j == size)
						break;
					int top = j;
					for (; j < size && nums[j - 1] > nums[j]; ++j) {}

					if (top != j)
						max_len = max(max_len, j - i);
					i = j - 2;
				}
				return max_len;
			}
		};
	}

	namespace task_846 {
		/*
		* https://leetcode.com/problems/hand-of-straights/description/
		*/
		class Solution {
		public:
			bool isNStraightHandMap(vector<int>& hand, int groupSize) { // 50.56% 54.60%
				size_t size = hand.size();
				if (size % groupSize != 0)
					return false;
				if (groupSize == 1)
					return true;
				int count_group = size / groupSize;
				map<int, int> counts;
				for (const int n : hand)
					if (auto it = counts.find(n); it != counts.end())
						++it->second;
					else
						counts[n] = 1;

				for (; count_group > 0; --count_group) {
					auto it = counts.begin();
					int prev = it->first - 1;
					size_t i = 0;
					for (; i < groupSize && it != counts.end(); ++i) {
						if (prev + 1 != it->first)
							return false;
						prev = it->first;
						--it->second;
						if (it->second == 0)
							it = counts.erase(it);
						else
							++it;
					}
					if (i < groupSize)
						return false;
				}
				return true;
			}

			bool isNStraightHandCountArr(vector<int>& hand, int groupSize) { // 97.79% 88.85%
				size_t size = hand.size();
				if (size % groupSize != 0)
					return false;
				int count_group = size / groupSize;
				sort(hand.begin(), hand.end());
				vector<pair<int, int>> counts;
				for (size_t i = 0; i < size; ++i) {
					int n = hand[i];
					int count = 0;
					for (; i < size && n == hand[i]; ++i)
						++count;
					--i;
					counts.push_back({ n , count });
				}
				size = counts.size();
				for (; count_group > 0; --count_group) { // going from back to start
					int prev = counts.back().first + 1;
					int j = counts.size() - 1;
					int i = 0;
					for (; i < groupSize && j >= 0; ++i, --j) {
						if (counts[j].first + 1 != prev || counts[j].second == 0)
							return false;
						--counts[j].second;
						prev = counts[j].first;
					}
					if (i < groupSize)
						return false;
					while (!counts.empty() && counts.back().second == 0)
						counts.pop_back();
				}
				return true;
			}
		};
	}

	namespace task_852 {
		/*
		* https://leetcode.com/problems/peak-index-in-a-mountain-array/description/
		*/
		class Solution {
		public:
			int peakIndexInMountainArray(vector<int>& arr) {
				size_t l = 0;
				size_t r = arr.size() - 1;

				while (r - l > 2) {
					size_t i = (r + l) / 2;
					if (arr[i] < arr[i + 1])
						l = i;
					else
						r = i + 1;
				}
				return l + 1;
			}
		};
	}

	namespace task_860 {
		/*
		* https://leetcode.com/lemonade-change/description/
		*/
		class Solution {
		public:
			bool lemonadeChange(vector<int>& bills) {
				int count_5 = 0, count_10 = 0;
				for (const int bill : bills) {
					if (bill == 5)
						++count_5;
					else if (bill == 10) {
						if (count_5 == 0)
							return false;
						++count_10;
						--count_5;
					}
					else {
						if (count_5 > 0 && count_10 > 0) {
							--count_10;
							--count_5;
						}
						else if (count_5 > 2)
							count_5 -= 3;
						else return false;
					}
				}
				return true;
			}
		};
	}

	namespace task_861 {
		/*
		* https://leetcode.com/problems/score-after-flipping-matrix/description/
		*/
		class Solution {
		public:
			int matrixScore(vector<vector<int>>& grid) {
				const int length = grid.size();
				const int widht = grid[0].size();
				int sum = (1 << (widht - 1)) * length;

				for (size_t i = 0; i < length; ++i)
					if (!grid[i][0])
						for (size_t j = 0; j < widht; ++j)
							grid[i][j] ^= 1;

				for (int j = 1; j < widht; ++j) {
					int count = 0;
					for (size_t i = 0; i < length; ++i)
						count += grid[i][j];
					sum += (1 << (widht - j - 1)) * max(count, length - count);
				}

				return sum;
			}

			int matrixScoreSlow(vector<vector<int>>& grid) {
				const int length = grid.size();
				const int widht = grid[0].size();
				const int min_number = 1 << (widht - 1);
				const int mask = (1 << widht) - 1;
				auto numbers = getNumbers(grid);
				for (int& number : numbers)
					if (number < min_number)
						number = (~number) & mask;

				for (int j = 1; j < widht; ++j) {
					int count = 0;
					int inverter = 1 << (widht - j - 1);
					for (const int number : numbers)
						if (number & inverter)
							++count;
					if ((count << 1) < length) {
						for (int& number : numbers)
							number ^= inverter;
					}
				}

				int sum = 0;
				for (const int number : numbers)
					sum += number;
				return sum;
			}

			vector<int> getNumbers(const vector<vector<int>>& grid) {
				const int length = grid.size();
				const int widht = grid[0].size();
				vector<int> numbers(length);
				for (size_t i = 0; i < length; ++i) {
					int number = 0;
					for (size_t j = 0; j < widht; ++j)
						number += grid[i][j] << (widht - j - 1);
					numbers[i] = number;
				}
				return numbers;
			}
		};
	}

	namespace task_862 {
		/*
		* https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/description/
		*/
		class Solution {
		public:
			int shortestSubarray(vector<int>& nums, int k) {
				int size = nums.size(), minLen = INT_MAX;
				vector<long long> prefixSums(size + 1, 0);
				deque<int> indices;

				for (int i = 1; i <= size; i++)
					prefixSums[i] = prefixSums[i - 1] + nums[i - 1];

				for (int i = 0; i <= size; ++i) {
					while (!indices.empty() &&
						prefixSums[i] - prefixSums[indices.front()] >= k) {
						minLen = min(minLen, i - indices.front());
						indices.pop_front();
					}

					// Maintain monotonicity by removing indices with larger prefix sums
					while (!indices.empty() && prefixSums[i] <= prefixSums[indices.back()])
						indices.pop_back();
					indices.push_back(i);
				}
				return minLen == INT_MAX ? -1 : minLen;
			}
		};
	}

	namespace task_865 {
		/*
		* https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/description/
		*/
		class Solution {
		public:
			TreeNode* res;
			int max_depth;

			TreeNode* subtreeWithAllDeepest(TreeNode* root) {
				res = root;
				max_depth = 1;
				if (!root)
					return root;
				lcaDeepestLeavesReq(root, 1);
				return res;
			}

			int lcaDeepestLeavesReq(TreeNode* node, int depth) {
				int depth_l = 0, depth_r = 0;
				if (node->left)
					depth_l = lcaDeepestLeavesReq(node->left, depth + 1);
				if (node->right)
					depth_r = lcaDeepestLeavesReq(node->right, depth + 1);

				if (depth_l == 0 && depth_r == 0) {
					if (max_depth < depth) {
						max_depth = depth;
						res = node;
					}
					return depth;
				}
				else if (depth_l == max_depth && depth_r == max_depth)
					res = node;
				return max(depth_l, depth_r);
			}
		};
	}

	namespace task_873 {
		/*
		* https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/description/
		*/
		class Solution {
		public:
			int lenLongestFibSubseq(vector<int>& arr) {
				const size_t size = arr.size();
				int next = 0, fib = 1, prev_fib = 0, len = 0, max_len = 0;
				for (size_t i = 0; i < size; ++i) {
					for (size_t j = i + 1; j < size; ++j) {
						prev_fib = arr[j];
						fib = arr[i] + prev_fib;
						len = 2;
						for (size_t k = j + 1; k < size; ++k) {
							if (arr[k] < fib)
								continue;
							if (arr[k] == fib) {
								++len;
								next = fib + prev_fib;
								prev_fib = fib;
								fib = next;
							}
							else
								break;
						}
						max_len = max(max_len, len);
					}
				}

				return max_len < 3 ? 0 : max_len;
			}
		};
	}

	namespace task_874 {
		/*
		* https://leetcode.com/problems/walking-robot-simulation/description/
		*/
		class Solution {
		public:
			int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
				unordered_map<int, set<int>> x_obstacles, y_obstacles;
				int max_dist = 0, pos_x = 0, pos_y = 0, direction = 0;
				for (const vector<int>& obstacle : obstacles) {
					if (auto it = x_obstacles.find(obstacle[0]); it != x_obstacles.end())
						it->second.insert(obstacle[1]);
					else
						x_obstacles[obstacle[0]] = { obstacle[1] };

					if (auto it = y_obstacles.find(obstacle[1]); it != y_obstacles.end())
						it->second.insert(obstacle[0]);
					else
						y_obstacles[obstacle[1]] = { obstacle[0] };
				}

				for (const int command : commands)
					if (command == -1)
						direction = (direction + 1) % 4;
					else if (command == -2)
						direction = (direction + 3) % 4;
					else {
						switch (direction)
						{
						case 0: {
							if (auto x_it = x_obstacles.find(pos_x); x_it != x_obstacles.end()) {
								auto y_it = x_it->second.upper_bound(pos_y);
								if (y_it != x_it->second.end() && *y_it <= pos_y + command)
									pos_y = *y_it - 1;
								else
									pos_y += command;
							}
							else
								pos_y += command;
							break;
						}
						case 1: {
							if (auto y_it = y_obstacles.find(pos_y); y_it != y_obstacles.end()) {
								auto x_it = y_it->second.upper_bound(pos_x);
								if (x_it != y_it->second.end() && *x_it <= pos_x + command)
									pos_x = *x_it - 1;
								else
									pos_x += command;
							}
							else
								pos_x += command;
							break;
						}
						case 2: {
							if (auto x_it = x_obstacles.find(pos_x); x_it != x_obstacles.end()) {
								auto y_it = x_it->second.lower_bound(pos_y);
								if (y_it == x_it->second.begin())
									y_it = x_it->second.end();
								else
									--y_it;
								if (y_it != x_it->second.end() && *y_it >= pos_y - command)
									pos_y = *y_it + 1;
								else
									pos_y -= command;
							}
							else
								pos_y -= command;
							break;
						}
						case 3: {
							if (auto y_it = y_obstacles.find(pos_y); y_it != y_obstacles.end()) {
								auto x_it = y_it->second.lower_bound(pos_x);
								if (x_it == y_it->second.begin())
									x_it = y_it->second.end();
								else
									--x_it;
								if (x_it != y_it->second.end() && *x_it >= pos_x - command) {
									pos_x = *x_it + 1;
									cout << " minus " << *x_it << endl;
								}
								else
									pos_x -= command;
							}
							else
								pos_x -= command;
							break;
						}
						}
						max_dist = max(max_dist, pos_x * pos_x + pos_y * pos_y);
					}
				return max_dist;
			}

			// faster

			static const int HASH_MULTIPLIER =
				60001;  // Slightly larger than 2 * max coordinate value

			// Hash function to convert (x, y) coordinates to a unique integer value
			int hashCoordinates(int x, int y) { return x + HASH_MULTIPLIER * y; }

			int robotSim2(vector<int>& commands, vector<vector<int>>& obstacles) {
				// Store obstacles in an unordered_set for efficient lookup
				unordered_set<int> obstacleSet;
				for (auto& obstacle : obstacles)
					obstacleSet.insert(hashCoordinates(obstacle[0], obstacle[1]));

				// Define direction vectors: North, East, South, West
				const vector<vector<int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
				int max_dist = 0, pos_x = 0, pos_y = 0, rotation = 0;
				// 0: North, 1: East, 2: South, 3: West

				for (const int command : commands) {
					if (command == -1) {
						rotation = (rotation + 1) % 4;
						continue;
					}
					if (command == -2) {
						rotation = (rotation + 3) % 4;
						continue;
					}

					const vector<int>& direction = directions[rotation];
					for (int step = 0; step < command; step++) {
						int next_x = pos_x + direction[0];
						int next_y = pos_y + direction[1];
						if (obstacleSet.contains(hashCoordinates(next_x, next_y)))
							break;
						pos_x = next_x;
						pos_y = next_y;
					}
					max_dist = max(max_dist, pos_x * pos_x + pos_y * pos_y);
				}

				return max_dist;
			}
		};
	}

	namespace task_876 {
		/*
		* https://leetcode.com/problems/middle-of-the-linked-list/description/
		*/
		class Solution {
		public:
			ListNode* middleNode(ListNode* head) {
				ListNode* ptr = head;
				while (ptr) {
					ptr = ptr->next;
					if (ptr)
						ptr = ptr->next;
					else
						break;
					head = head->next;
				}
				return head;
			}
		};
	}

	namespace task_877 {
		/*
		* https://leetcode.com/problems/stone-game/description/
		*/
		class Solution {
		public:
			bool stoneGame(vector<int>& piles) {
				size_t size = piles.size(), gains_size = size >> 1;
				vector<vector<int>> gains(gains_size);
				gains[0] = vector<int>(size - 1);
				for (size_t i = 1; i < size; ++i)
					gains[0][i - 1] = max(piles[i - 1], piles[i]) - min(piles[i - 1], piles[i]);
				for (size_t i = 1; i < gains_size; ++i) {
					size_t interval_size = ((i + 1) << 1) - 1;
					for (size_t j = 0; j < size - interval_size; j++) {
						int gain_ll = piles[j] - piles[j + 1] + gains[i - 1][j + 2];
						int gain_lr = piles[j] - piles[j + interval_size] + gains[i - 1][j + 1];
						int gain_rl = piles[j + interval_size] - piles[j] + gains[i - 1][j + 1];
						int gain_rr = piles[j + interval_size] - piles[j + interval_size - 1] + gains[i - 1][j];
						gains[i].push_back(max(max(max(gain_ll, gain_lr), gain_rl), gain_rr));
					}
				}
				return gains.back()[0] > 0;
			}

			bool stoneGameFast(vector<int>& piles) { // it works
				return true;
			}
		};
	}

	namespace task_884 {
		/*
		* https://leetcode.com/problems/uncommon-words-from-two-sentences/description/
		*/
		class Solution {
		public:
			vector<string> uncommonFromSentences(string s1, string s2) {
				unordered_multiset<string> set;
				// first str
				size_t prev_pos = 0, pos = s1.find(' ');
				while (pos != string::npos) {
					set.insert(s1.substr(prev_pos, pos - prev_pos));
					prev_pos = pos + 1;
					pos = s1.find(' ', prev_pos);
				}
				set.insert(s1.substr(prev_pos));
				// second str
				prev_pos = 0, pos = s2.find(' ');
				while (pos != string::npos) {
					set.insert(s2.substr(prev_pos, pos - prev_pos));
					prev_pos = pos + 1;
					pos = s2.find(' ', prev_pos);
				}
				set.insert(s2.substr(prev_pos));

				vector<string> uncommons;
				for (const string& str : set)
					if (set.count(str) == 1)
						uncommons.push_back(str);

				return uncommons;
			}
		};
	}

	namespace task_885 {
		/*
		* https://leetcode.com/problems/spiral-matrix-iii/description/
		*/
		class Solution {
		public:
			vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
				int c = 0;
				size_t size = rows * cols;
				vector<vector<int>> matrix(rows, vector<int>(cols));
				vector<vector<int>> res;
				int i, i_end;
				int j, j_end;
				int cycle = 0;
				while (true) {
					i = rStart - cycle;
					j = max(cStart - cycle, 0);
					j_end = min(cStart + cycle + 2, cols);
					if (i >= 0) {
						for (; j < j_end; j++) {
							res.push_back(vector<int>{i, j});
							matrix[i][j] = ++c;
						}
						if (c == size)
							break;
					}

					i = max(i + 1, 0);
					i_end = min(rStart + cycle + 2, rows);
					j = cStart + cycle + 1;
					if (j < cols) {
						for (; i < i_end; i++) {
							res.push_back(vector<int>{i, j});
							matrix[i][j] = ++c;
						}
						if (c == size)
							break;
					}

					i = rStart + cycle + 1;
					j = min(j - 1, cols - 1);
					j_end = max(cStart - cycle - 2, -1);
					if (i < rows) {
						for (; j > j_end; j--) {
							res.push_back(vector<int>{i, j});
							matrix[i][j] = ++c;
						}
						if (c == size)
							break;
					}

					i = min(i - 1, rows - 1);
					i_end = max(rStart - cycle - 1, -1);
					j = cStart - cycle - 1;
					if (j >= 0) {
						for (; i > i_end; i--) {
							res.push_back(vector<int>{i, j});
							matrix[i][j] = ++c;
						}
						if (c == size)
							break;
					}
					++cycle;
				}
				return res;
			}
		};
	}

	namespace task_889 {
		/*
		* https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/description/
		*/
		class Solution {
		public:
			TreeNode* constructFromPrePost(vector<int>& preorder,
				vector<int>& postorder) {
				int preIndex = 0;
				int postIndex = 0;
				return constructTree(preIndex, postIndex, preorder, postorder);
			}

			TreeNode* constructTree(int& preIndex, int& postIndex, vector<int>& preorder, vector<int>& postorder) {
				TreeNode* root = new TreeNode(preorder[preIndex]);
				preIndex++;

				if (root->val != postorder[postIndex])
					root->left = constructTree(preIndex, postIndex, preorder, postorder);

				if (root->val != postorder[postIndex])
					root->right = constructTree(preIndex, postIndex, preorder, postorder);

				postIndex++;

				return root;
			}
		};
	}

	namespace task_898 {
		/*
		* https://leetcode.com/problems/bitwise-and-of-numbers-range/description/
		*/
		class Solution {
		public:
			int subarrayBitwiseORs(vector<int>& arr) {
				unordered_set<int> setBitOR;
				unordered_set<int> lastRoundOR;
				unordered_set<int> currentOR;
				for (auto val : arr) {
					for (auto lre : lastRoundOR)
						currentOR.insert(lre | val);
					currentOR.insert(val);
					setBitOR.insert(currentOR.begin(), currentOR.end());
					lastRoundOR = currentOR;
					currentOR.clear();
				}

				return setBitOR.size();
			}
		};
	}

	namespace task_908 {
		/*
		* https://leetcode.com/problems/smallest-range-i/description/
		*/
		class Solution {
		public:
			int smallestRangeI(vector<int>& nums, int k) {
				int min_el = nums[0];
				int max_el = nums[0];
				for (int el : nums) {
					min_el = min(min_el, el);
					max_el = max(max_el, el);
				}
				return max(max_el - min_el - 2 * k, 0);
			}

			int smallestRangeI2(vector<int>& nums, int k) {
				int min_el = nums[0];
				int max_el = nums[0];
				for (int el : nums) {
					if (min_el > el)
						min_el = el;
					else if (max_el < el)
						max_el = el;
				}
				return max(max_el - min_el - 2 * k, 0);
			}
		};
	}

	namespace task_909 {
		/*
		* https://leetcode.com/problems/snakes-and-ladders/description/
		*/
		class Solution {
		public:
			int n, len;

			int snakesAndLadders(vector<vector<int>>& board) {
				n = board.size(), len = n * n;
				vector<vector<int>> steps(n, vector<int>(n, -1));
				vector<int> visited(len + 1, -1);
				visited[1] = 0;
				queue<int> queue;
				queue.push(1);

				for (int steps = 1; !queue.empty(); ++steps) {
					int size = queue.size();
					for (int i = 0; i < size; ++i) {
						int vertex = queue.front();
						queue.pop();
						for (int j = 1; j < 7 && vertex + j <= len; ++j) {
							int next = getValue(board, vertex + j);
							if (next == -1)
								next = vertex + j;

							if (visited[next] == -1) {
								visited[next] = steps;
								queue.push(next);
							}
						}
					}
				}
				return visited[len];
			}

			int getValue(const vector<vector<int>>& board, int vertex) {
				int i = (vertex - 1) / n, j = (vertex - 1) % n;
				if (i & 1)
					j = n - j - 1;
				i = n - i - 1;
				return board[i][j];
			}
		};
	}

	namespace task_910 {
		/*
		* https://leetcode.com/problems/smallest-range-ii/description/
		*/
		class Solution {
		public:
			int smallestRangeII(vector<int>& nums, int k) {
				if (nums.size() == 1)
					return 0;

				sort(nums.begin(), nums.end());
				int min_el = nums.front();
				int max_el = nums.back();
				if (max_el - min_el <= k || k == 0)
					return max_el - min_el;
				int res = max_el - min_el;

				min_el = nums.front() + k;
				max_el = nums.back() - k;
				for (size_t i = 1; i < nums.size(); i++) {
					int min_ = min(min_el, nums[i] - k);
					int max_ = max(max_el, nums[i - 1] + k);
					res = min(res, max_ - min_);
				}
				return res;
			}
		};
	}

	namespace task_912 {
		/*
		* https://leetcode.com/problems/sort-an-array/description/
		*/
		class Solution {
		public:
			vector<int> sortArray(vector<int>& nums) {
				sort(nums.begin(), nums.end());
				return nums;
			}

			vector<int> MysortArray(vector<int>& nums) {
				heap_sort(nums);
				return nums;
			}

			void heap_sort(std::vector<int>& arr)
			{
				build_max_heap(arr);
				int sz = arr.size();
				for (int i = arr.size() - 1; i > 0; i--)
				{
					std::swap(arr[0], arr[i]);
					sz--;
					max_heapify(arr, 0, sz);
				}
			}

			void build_max_heap(std::vector<int>& arr)
			{
				for (int i = (arr.size() / 2); i >= 0; i--)
					max_heapify(arr, i, arr.size());
			}

			void max_heapify(std::vector<int>& arr, int i, int size_)
			{
				int largest, l = (2 * i) + 1, r = l + 1;

				if (l < size_ && arr[l] > arr[i])
					largest = l;
				else
					largest = i;

				if (r < size_ && arr[r] > arr[largest])
					largest = r;

				if (largest != i)
				{
					std::swap(arr[i], arr[largest]);
					max_heapify(arr, largest, size_);
				}
			}
		};
	}

	namespace task_916 {
		/*
		* https://leetcode.com/problems/word-subsets/description/
		*/
		class Solution {
		public:
			vector<string> wordSubsets(vector<string>& mainWords, vector<string>& requiredWords) {
				int maxCharFreq[26] = { 0 };
				int tempCharFreq[26];

				for (const auto& word : requiredWords) {
					memset(tempCharFreq, 0, sizeof tempCharFreq);
					for (char ch : word)
						tempCharFreq[ch - 'a']++;
					for (int i = 0; i < 26; ++i)
						maxCharFreq[i] = max(maxCharFreq[i], tempCharFreq[i]);
				}

				vector<string> universalWords;

				for (const auto& word : mainWords) {
					memset(tempCharFreq, 0, sizeof tempCharFreq);
					for (char ch : word)
						tempCharFreq[ch - 'a']++;
					bool isUniversal = true;
					for (int i = 0; i < 26; ++i) {
						if (maxCharFreq[i] > tempCharFreq[i]) {
							isUniversal = false;
							break;
						}
					}
					if (isUniversal)
						universalWords.emplace_back(word);
				}

				return universalWords;
			}
		};
	}

	namespace task_921 {
		/*
		* https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/
		*/
		class Solution {
		public:
			int minAddToMakeValid(string s) {
				size_t size = s.size();
				int opens = 0, closes = 0, add = 0;
				for (size_t i = 0; i < size; i++) {
					if (s[i] == ')')
						++closes;
					else
						++opens;
					if (closes > opens) {
						++opens;
						++add;
					}
				}
				return add + max(0, opens - closes);
			}
		};
	}

	namespace task_926 {
		/*
		* https://leetcode.com/problems/flip-string-to-monotone-increasing/description/
		*/
		class Solution {
		public:
			int minFlipsMonoIncr(string s) {
				int count_zeros = 0, count_ones = 0;
				for (char c : s)
					if (c == '0')
						++count_zeros;
				int min_flip = count_zeros;
				for (char c : s) {
					if (c == '0')
						--count_zeros;
					else
						++count_ones;
					min_flip = min(min_flip, count_zeros + count_ones);
				}
				return min_flip;
			}

			int minFlipsMonoIncrFast(string s) {
				int count_flip = 0, count_one = 0;
				for (auto c : s)
				{
					if (c == '1')
						++count_one;
					else {
						++count_flip;
						count_flip = min(count_flip, count_one);
					}
				}
				return count_flip;
			}
		};
	}

	namespace task_931 {
		/*
		* https://leetcode.com/problems/minimum-falling-path-sum/description/
		*/
		class Solution {
		public:
			int minFallingPathSum(vector<vector<int>>& matrix) {
				const size_t size = matrix.size();

				for (size_t i = 1; i < size; i++)
					for (size_t j = 0; j < size; j++)
						matrix[i][j] += min(min(j > 0 ? matrix[i - 1][j - 1] : INT_MAX,
							j + 1 < size ? matrix[i - 1][j + 1] : INT_MAX),
							matrix[i - 1][j]);

				int min_path = INT_MAX;
				for (size_t j = 0; j < size; j++)
					if (min_path > matrix.back()[j])
						min_path = matrix.back()[j];

				return min_path;
			}
		};
	}

	namespace task_941 {
		/*
		* https://leetcode.com/problems/valid-mountain-array/description/
		*/
		class Solution {
		public:
			bool validMountainArray(vector<int>& arr) {
				size_t size = arr.size(), i = 1;
				if (size < 3)
					return false;

				for (; i < size && arr[i - 1] < arr[i]; ++i) {}
				if (i == 1 || i == size)
					return false;
				for (; i < size && arr[i - 1] > arr[i]; ++i) {}
				return i == size;
			}
		};
	}

	namespace task_945 {
		/*
		* https://leetcode.com/problems/minimum-increment-to-make-array-unique/description/
		*/
		class Solution {
		public:
			int minIncrementForUnique(vector<int>& nums) {
				size_t size = nums.size();
				sort(nums.begin(), nums.end());
				int count = 0;
				for (size_t i = 1; i < size; ++i)
					if (nums[i] <= nums[i - 1]) {
						int dif = nums[i - 1] + 1 - nums[i];
						count += dif;
						nums[i] += dif;;
					}
				return count;
			}
		};
	}

	namespace task_947 {
		/*
		* https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/
		*/
		class Solution {
		public:
			int removeStones(vector<vector<int>>& stones) {
				unordered_map<int, vector<size_t>> rows, cols;
				size_t size = stones.size();
				vector<char> visited(size);
				for (size_t i = 0; i < size; ++i) {
					if (auto it = rows.find(stones[i][0]); it != rows.end())
						it->second.push_back(i);
					else
						rows[stones[i][0]] = { i };
					if (auto it = cols.find(stones[i][1]); it != cols.end())
						it->second.push_back(i);
					else
						cols[stones[i][1]] = { i };
				}
				size_t count_components = 0;
				for (size_t i = 0; i < size; ++i)
					if (visited[i] == 0) {
						++count_components;
						stack<size_t> vertexes({ i });
						visited[i] = 1;
						while (!vertexes.empty()) {
							size_t vertex = vertexes.top();
							vertexes.pop();
							int coordinate = stones[vertex][0];
							for (const size_t v : rows[coordinate])
								if (visited[v] == 0) {
									visited[v] = 1;
									vertexes.push(v);
								}
							coordinate = stones[vertex][1];
							for (const size_t v : cols[coordinate])
								if (visited[v] == 0) {
									visited[v] = 1;
									vertexes.push(v);
								}
						}
					}
				return size - count_components;
			}
		};
	}

	namespace task_951 {
		/*
		* https://leetcode.com/problems/cousins-in-binary-tree/description
		*/
		class Solution {
		public:
			bool flipEquiv(TreeNode* root1, TreeNode* root2) {
				if (!root1)
					return !root2;
				if (!root2)
					return false;
				if (root1->val != root2->val)
					return false;

				stack<TreeNode*> stack1, stack2;
				stack1.push(root1);
				stack2.push(root2);

				while (!stack1.empty()) {
					root1 = stack1.top();
					root2 = stack2.top();
					stack1.pop();
					stack2.pop();
					if (root1->left) { // sort children
						if (root1->right && root1->left->val < root1->right->val)
							swap(root1->left, root1->right);
					}
					else if (root1->right)
						swap(root1->left, root1->right);
					if (root2->left) {
						if (root2->right && root2->left->val < root2->right->val)
							swap(root2->left, root2->right);
					}
					else if (root2->right)
						swap(root2->left, root2->right);


					if (root1->left) {
						if (root2->left && root1->left->val == root2->left->val) {
							stack1.push(root1->left);
							stack2.push(root2->left);
						}
						else
							return false;

						if (root1->right) {
							if (root2->right && root1->right->val == root2->right->val) {
								stack1.push(root1->right);
								stack2.push(root2->right);
							}
							else
								return false;
						}
						else if (root2->right)
							return false;
					}
					else if (root2->left)
						return false;
				}
				return true;
			}
		};
	}

	namespace task_959 {
		/*
		* https://leetcode.com/problems/regions-cut-by-slashes/description/
		*/
		class Solution {
		public:
			int regionsBySlashes(vector<string>& grid) {
				int size = grid.size() * 3, count = 0;
				auto newGrid = makeGrid(grid);
				for (int i = 0; i < size; ++i)
					for (int j = 0; j < size; ++j)
						if (newGrid[i][j]) {
							++count;
							markRegion(newGrid, i, j, size);
						}
				return count;
			}

			vector<vector<int>> makeGrid(vector<string>& gridOrig) {
				size_t sizeOrig = gridOrig.size(), size = sizeOrig * 3;
				vector<vector<int>> grid(size, vector<int>(size, 1));
				for (int i = 0; i < sizeOrig; ++i)
					for (int j = 0; j < sizeOrig; ++j)
						if (gridOrig[i][j] == '/') {
							grid[i * 3][j * 3 + 2] = 0;
							grid[i * 3 + 1][j * 3 + 1] = 0;
							grid[i * 3 + 2][j * 3] = 0;
						}
						else if (gridOrig[i][j] == '\\') {
							grid[i * 3][j * 3] = 0;
							grid[i * 3 + 1][j * 3 + 1] = 0;
							grid[i * 3 + 2][j * 3 + 2] = 0;
						}
				return grid;
			}

			void markRegion(vector<vector<int>>& grid, int i, int j, const int size) {
				queue<pair<int, int>> queue;
				queue.push({ i, j });
				grid[i][j] = 'x';
				while (!queue.empty()) {
					auto& pos = queue.front();
					if (pos.first + 1 != size && grid[pos.first + 1][pos.second]) {
						grid[pos.first + 1][pos.second] = 0;
						queue.push({ pos.first + 1, pos.second });
					}
					if (pos.second + 1 != size && grid[pos.first][pos.second + 1]) {
						grid[pos.first][pos.second + 1] = 0;
						queue.push({ pos.first, pos.second + 1 });
					}
					if (pos.first - 1 != -1 && grid[pos.first - 1][pos.second]) {
						grid[pos.first - 1][pos.second] = 0;
						queue.push({ pos.first - 1, pos.second });
					}
					if (pos.second - 1 != -1 && grid[pos.first][pos.second - 1]) {
						grid[pos.first][pos.second - 1] = 0;
						queue.push({ pos.first, pos.second - 1 });
					}
					queue.pop();
				}
			}
		};
	}

	namespace task_962 {
		/*
		* https://leetcode.com/problems/maximum-width-ramp/description/
		*/
		class Solution {
		public:
			int maxWidthRamp(vector<int>& nums) { // best
				int n = nums.size(), maxWidth = 0;
				stack<int> indicesStack;
				for (int i = 0; i < n; ++i) {
					if (indicesStack.empty() || nums[indicesStack.top()] > nums[i])
						indicesStack.push(i);
				}

				for (int j = n - 1; j >= 0; --j) {
					while (!indicesStack.empty() &&
						nums[indicesStack.top()] <= nums[j]) {
						maxWidth = max(maxWidth, j - indicesStack.top());
						indicesStack.pop();
					}
				}

				return maxWidth;
			}

			int maxWidthRampMap(vector<int>& nums) {
				int size = nums.size(), max_width = 0, min_value = nums[0];
				map<int, int, greater<int>> map{ { min_value , 0} };
				for (int i = 1; i < size; ++i) {
					auto it = map.lower_bound(nums[i]);
					if (min_value > nums[i]) {
						min_value = nums[i];
						map[min_value] = i;
					}
					max_width = max(max_width, i - map.lower_bound(nums[i])->second);
				}
				return max_width;
			}

			int maxWidthRamp_TLE(vector<int>& nums) { // Time Limit Exceeded on reverse sorted
				int size = nums.size(), max_width = 0, j;
				for (int i = 0; i < size; ++i) {
					j = i + max_width + 1;
					for (; j < size; ++j)
						if (nums[i] <= nums[j])
							max_width = j - i;
				}
				return max_width;
			}
		};
	}

	namespace task_974 {
		/*
		* https://leetcode.com/problems/continuous-subarray-sum/description/
		*/
		class Solution {
		public:
			int subarraysDivByK(vector<int>& nums, int k) {
				int sum = 0, count = 0;
				unordered_map<int, int> set{ {0, 0} };
				for (const int n : nums) {
					sum = ((sum + n) % k + k) % k;
					if (auto it = set.find(sum); it != set.end()) count += ++it->second;
					else set.insert({ sum, 0 });
				}
				return count;
			}

			bool checkSubarraySum(vector<int>& nums, int k) {
				size_t size = nums.size();
				int sum = nums[0] % k;
				unordered_set<int> set({ sum });
				for (size_t i = 1; i < size; ++i) {
					sum = (sum + nums[i]) % k;
					if ((nums[i] + nums[i - 1]) % k == 0)
						return true;
					else if (set.contains(sum) && nums[i] % k != 0 || sum == 0)
						return true;
					set.insert(sum);
				}
				return false;
			}

			bool checkSubarraySumFaster(std::vector<int>& nums, int k) {
				int sum = 0, prev_sum = 0;
				unordered_set<int> set;
				for (const int n : nums) {
					sum = (sum + n) % k;
					if (set.count(sum)) return true;
					set.insert(prev_sum);
					prev_sum = sum;
				}
				return false;
			}
		};
	}

	namespace task_979 {
		/*
		* https://leetcode.com/problems/distribute-coins-in-binary-tree/description/
		*/
		class Solution {
		public:
			int distributeCoins(TreeNode* root) {
				int moves = 0;
				if (root->left) {
					moves += distributeCoins(root->left);
					int coins = root->left->val - 1;
					moves += abs(coins);
					root->left->val = 1;
					root->val += coins;
				}
				if (root->right) {
					moves += distributeCoins(root->right);
					int coins = root->right->val - 1;
					moves += abs(coins);
					root->right->val = 1;
					root->val += coins;
				}
				return moves;
			}
		};
	}

	namespace task_981 {
		/*
		* https://leetcode.com/time-based-key-value-store/description/
		*/
		class TimeMap {
		public:
			TimeMap() {

			}

			void set(string key, string value, int timestamp) {
				data[-timestamp][key] = value;
			}

			string get(string key, int timestamp) {
				auto outer_it = data.lower_bound(-timestamp);
				while (outer_it != data.end()) {
					auto inner_it = outer_it->second.find(key);
					if (inner_it != outer_it->second.end())
						return inner_it->second;
					++outer_it;
				}
				return "";
			}

			map<int, map<string, string>> data;
		};
	}

	namespace task_983 {
		/*
		* https://leetcode.com/problems/minimum-cost-for-tickets/description/
		*/
		class Solution {
		public:
			int mincostTickets(vector<int>& days, vector<int>& costs) {
				int lastDay = days[days.size() - 1];
				vector<int> dp(lastDay + 1, 0);

				int i = 0;
				for (int day = 1; day <= lastDay; day++) {
					if (day < days[i]) {
						dp[day] = dp[day - 1];
					}
					else {
						i++;
						dp[day] = min({ dp[day - 1] + costs[0],
									   dp[max(0, day - 7)] + costs[1],
									   dp[max(0, day - 30)] + costs[2] });
					}
				}

				return dp[lastDay];
			}
		};
	}

	namespace task_993 {
		/*
		* https://leetcode.com/problems/cousins-in-binary-tree/description
		*/
		class Solution {
		public:
			bool isCousins(TreeNode* root, int x, int y) {
				queue<TreeNode*> queue;
				if (root->left) {
					root->left->val = 0;
					queue.push(root->left);
				}
				if (root->right) {
					root->right->val = 0;
					queue.push(root->right);
				}
				size_t level_size = queue.size();
				while (level_size != 0) {
					bool found_one = false, found_at_same_parent;
					for (size_t i = 0; i < level_size; ++i) {
						root = queue.front();
						queue.pop();
						if (root->left) {
							if (root->left->val == x || root->left->val == y) {
								if (found_one)
									return true;
								found_one = true;
								found_at_same_parent = true;
							}
							queue.push(root->left);
						}
						if (root->right) {
							if (root->right->val == x || root->right->val == y) {
								if (found_one && !found_at_same_parent)
									return true;
								found_one = true;
							}
							queue.push(root->right);
						}
						found_at_same_parent = false;
					}
					level_size = queue.size();
				}
				return false;
			}
		};
	}

	namespace task_995 {
		/*
		* https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/
		*/
		class Solution {
		public:
			int minKBitFlips(vector<int>& nums, int k) {
				int size = nums.size(), i = 0, count = 0;
				deque<int> rotates;
				for (; i <= size - k; ++i) {
					if (!rotates.empty() && i - rotates.front() >= k)
						rotates.pop_front();
					if ((nums[i] ^ (rotates.size() & 1)) == 0) {
						++count;
						rotates.push_back(i);
					}
				}
				for (; i < size; ++i) {
					if (!rotates.empty() && i - rotates.front() >= k)
						rotates.pop_front();
					if ((nums[i] ^ (rotates.size() & 1)) == 0)
						return -1;
				}
				return count;
			}

			int minKBitFlipsFaster(vector<int>& nums, int k) {
				int size = nums.size(), i = 0, count = 0, flipped = 0;
				vector<int> flipps(k);
				for (; i < size; ++i) {
					flipped ^= flipps[i % k];
					if (nums[i] == flipped) {
						if (i + k > size)
							return -1;
						++count;
						flipped ^= 1;
						flipps[i % k] = 1;
					}
					else
						flipps[i % k] = 0;
				}
				return count;
			}

			int minKBitFlipsFastest(vector<int>& nums, int k) {
				int size = nums.size(), i = 0, count = 0, flipped = 0;
				vector<int> flipps(k);
				for (; i <= size - k; ++i) {
					flipped ^= flipps[i % k];
					if (nums[i] == flipped) {
						++count;
						flipped ^= 1;
						flipps[i % k] = 1;
					}
					else
						flipps[i % k] = 0;
				}

				for (; i < size; ++i) {
					flipped ^= flipps[i % k];
					if (nums[i] == flipped)
						return -1;
				}
				return count;
			}

			int minKBitFlipsTLE(vector<int>& nums, int k) {
				size_t size = nums.size(), i = 0;
				int count = 0;
				for (; i <= size - k; ++i) {
					if (nums[i] == 0) {
						++count;
						for (size_t j = 0; j < k; ++j)
							nums[j + i] ^= 1;
					}
				}
				for (; i < size; ++i)
					if (nums[i] == 0)
						return -1;
				return count;
			}
		};
	}

	namespace task_1002 {
		/*
		* https://leetcode.com/problems/find-common-characters/description/
		*/
		class Solution {
		public:
			vector<string> commonChars(vector<string>& words) {
				size_t chars = 'z' - 'a' + 1;
				vector<int> min_counts(chars, 100);
				vector<int> counts(chars);
				for (const string& word : words) {
					for (const char c : word)
						++counts[c - 'a'];
					for (size_t i = 0; i < chars; i++) {
						min_counts[i] = min(min_counts[i], counts[i]);
						counts[i] = 0;
					}
				}
				vector<string> res;
				for (size_t i = 0; i < chars; i++)
					for (size_t j = 0; j < min_counts[i]; j++)
						res.push_back(string(1, i + 'a'));
				return res;
			}
		};
	}

	namespace task_1007 {
		/*
		* https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/description/
		*/
		class Solution {
		public:
			int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
				unordered_map<int, int> mp;
				const size_t n = tops.size();

				for (size_t i = 0; i < n; ++i) {
					mp[tops[i]]++;
					mp[bottoms[i]]++;
				}

				int el = 0;

				for (auto i : mp) {
					if (i.second >= n) {
						el = i.first;
						break;
					}
				}

				int count = 0;
				int topcount = 0, bottomcount = 0;
				for (size_t i = 0; i < n; ++i) {
					if (tops[i] != el && bottoms[i] != el)
						return -1;

					if (tops[i] != bottoms[i] && bottoms[i] == el)
						topcount++;

					if (tops[i] != bottoms[i] && tops[i] == el)
						bottomcount++;

				}
				return min(topcount, bottomcount);
			}
		};
	}

	namespace task_1028 {
		/*
		* https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/description/
		*/
		class Solution {
		public:
			TreeNode* recoverFromPreorder(string traversal) {
				vector<TreeNode*> levels;
				int index = 0, n = traversal.size();

				while (index < n) {
					int depth = 0;
					while (index < n && traversal[index] == '-') {
						depth++;
						index++;
					}

					int value = 0;
					while (index < n && isdigit(traversal[index])) {
						value = value * 10 + (traversal[index] - '0');
						index++;
					}

					TreeNode* node = new TreeNode(value);

					if (depth < levels.size())
						levels[depth] = node;
					else
						levels.push_back(node);

					if (depth > 0) {
						TreeNode* parent = levels[depth - 1];
						if (parent->left == nullptr)
							parent->left = node;
						else
							parent->right = node;
					}
				}

				return levels[0];
			}
		};
	}

	namespace task_1079 {
		/*
		* https://leetcode.com/problems/letter-tile-possibilities/description/
		*/
		class Solution {
		public:
			unordered_set<string> seen;

			int numTilePossibilities(string tiles) {
				seen = unordered_set<string>();
				sort(tiles.begin(), tiles.end());

				return generateSequences(tiles, "", 0) - 1;
			}

			int factorial(int n) {
				if (n <= 1)
					return 1;

				int result = 1;
				for (int num = 2; num <= n; num++)
					result *= num;
				return result;
			}

			int countPermutations(string& seq) {
				int charCount[26] = { 0 };
				for (char ch : seq)
					charCount[ch - 'A']++;

				int total = factorial(seq.length());
				for (int count : charCount) {
					if (count > 1)
						total /= factorial(count);
				}
				return total;
			}

			int generateSequences(string& tiles, string current, int pos) {
				if (pos >= tiles.length()) {
					if (seen.insert(current).second)
						return countPermutations(current);
					return 0;
				}

				return generateSequences(tiles, current, pos + 1) + generateSequences(tiles, current + tiles[pos], pos + 1);
			}
		};
	}

	namespace task_1092 {
		/*
		* https://leetcode.com/problems/shortest-common-supersequence/description/
		*/
		class Solution {
		public:
			string shortestCommonSupersequence__leetcode(string str1, string str2) {
				int str1Length = str1.length();
				int str2Length = str2.length();

				vector<vector<int>> dp(str1Length + 1, vector<int>(str2Length + 1, 0));

				// Initialize the base cases
				// When str2 is empty, the supersequence is str1 itself
				// (length = row index)
				for (int row = 0; row <= str1Length; row++) {
					dp[row][0] = row;
				}
				// When str1 is empty, the supersequence is str2 itself
				// (length = col index)
				for (int col = 0; col <= str2Length; col++) {
					dp[0][col] = col;
				}

				// Fill the DP table
				for (int row = 1; row <= str1Length; row++) {
					for (int col = 1; col <= str2Length; col++) {
						if (str1[row - 1] == str2[col - 1]) {
							// If characters match,
							// inherit the length from the diagonal + 1
							dp[row][col] = dp[row - 1][col - 1] + 1;
						}
						else {
							// If characters do not match,
							// take the minimum length option + 1
							dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1;
						}
					}
				}

				string supersequence = "";
				int row = str1Length, col = str2Length;

				while (row > 0 && col > 0) {
					if (str1[row - 1] == str2[col - 1]) {
						// If characters match, take it from diagonal
						supersequence += str1[row - 1];
						row--;
						col--;
					}
					else if (dp[row - 1][col] < dp[row][col - 1]) {
						// If str1’s character is part of the supersequence, move up
						supersequence += str1[row - 1];
						row--;
					}
					else {
						// If str2’s character is part of the supersequence, move left
						supersequence += str2[col - 1];
						col--;
					}
				}

				// Append any remaining characters
				// If there are leftover characters in str1
				while (row > 0) {
					supersequence += str1[row - 1];
					row--;
				}
				// If there are leftover characters in str2
				while (col > 0) {
					supersequence += str2[col - 1];
					col--;
				}

				// Reverse the built sequence to get the correct order
				reverse(supersequence.begin(), supersequence.end());
				return supersequence;
			}
		};
	}

	namespace task_1105 {
		/*
		* https://leetcode.com/problems/filling-bookcase-shelves/description/
		*/
		class Solution {
		public:
			int minHeightShelves(vector<vector<int>>& books, int shelfWidth) { // not pass
				size_t size = books.size();
				vector<int> dp(size);
				dp[0] = books[0][1];
				int layer_width = books[0][0], layer_height = books[0][1];
				for (int i = 1; i < size; ++i) {
					if (layer_width + books[i][0] <= shelfWidth) {
						layer_width += books[i][0];
						dp[i] = dp[i - 1] - layer_height;
						layer_height = max(layer_height, books[i][1]);
						dp[i] += layer_height;
					}
					else {
						layer_width = books[i][0], layer_height = books[i][1];
						int height = dp[i - 1] + layer_height;
						dp[i] = height;
						int new_layer_width = layer_width;
						int new_layer_height = layer_height;

						for (size_t j = i - 1; true; --j) {
							new_layer_width += books[j][0];
							if (new_layer_width > shelfWidth)
								break;
							new_layer_height = max(new_layer_height, books[j][1]);
							height = dp[j - 1] + new_layer_height;
							if (dp[i] > height) {
								dp[i] = height;
								layer_width = new_layer_width;
								layer_height = new_layer_height;
							}
						}
					}
				}
				return dp.back();
			}

			int minHeightShelves2(vector<vector<int>>& books, int shelfWidth) {
				size_t size = books.size();
				vector<int> dp(size + 1);
				dp[0] = 0;
				dp[1] = books[0][1];
				for (int i = 1; i < size; ++i) {
					int layer_width = books[i][0], layer_height = books[i][1];
					dp[i + 1] = dp[i] + layer_height;
					for (int j = i - 1; j >= 0; --j) {
						layer_width += books[j][0];
						if (layer_width > shelfWidth)
							break;
						layer_height = max(layer_height, books[j][1]);
						dp[i + 1] = min(dp[i + 1], dp[j] + layer_height);

					}
				}
				return dp.back();
			}
		};
	}

	namespace task_1009 {
		/*
		* https://leetcode.com/problems/complement-of-base-10-integer/
		*/
		class Solution {
		public:
			int bitwiseComplement(int n) {
				if (n == 0)
					return 1;
				int rev_num = ~n, mask = n;
				do {
					mask |= n;
					n >>= 1;
				} while (n > 0);
				return rev_num & mask;
			}
		};
	}

	namespace task_1014 {
		/*
		* https://leetcode.com/problems/best-sightseeing-pair/description/
		*/
		class Solution {
		public:
			int maxScoreSightseeingPair(vector<int>& values) {
				int size = values.size(), maxLeftScore = values[0], maxScore = 0;

				for (int i = 1; i < size; ++i) {
					maxScore = max(maxScore, maxLeftScore + values[i] - i);
					maxLeftScore = max(maxLeftScore, values[i] + i);
				}

				return maxScore;
			}
		};
	}

	namespace task_1019 {
		/*
		* https://leetcode.com/problems/next-greater-node-in-linked-list/description/
		*/
		class Solution {
		public:
			vector<int> nextLargerNodesQueue(ListNode* head) {
				priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> queue;
				int size = 0;
				ListNode* ptr = head;
				for (; ptr; ++size, ptr = ptr->next) {}
				vector<int> res(size);
				for (int i = 0; i < size; ++i, head = head->next) {
					while (!queue.empty() && queue.top().first < head->val) {
						res[queue.top().second] = head->val;
						queue.pop();
					}
					queue.push({ head->val , i });
				}
				return res;
			}

			vector<int> monotonic_stack;
			int size_stack;
			vector<int> nextLargerNodesMonotonicStack(ListNode* head) {
				vector<int> res;
				for (; head; head = head->next)
					res.push_back(head->val);

				monotonic_stack = vector<int>(res.size());
				monotonic_stack[0] = res.back();
				res.back() = 0;
				size_stack = 1;

				for (int i = res.size() - 2; i >= 0; --i)
					res[i] = nextGreat(res[i]);
				return res;
			}

			int nextGreat(int value) {
				size_t l = 0;
				size_t r = size_stack;
				if (monotonic_stack[l] <= value) {
					size_stack = 1;
					monotonic_stack[l] = value;
					return 0;
				}
				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (monotonic_stack[i] > value)
						l = i;
					else
						r = i;
				}
				monotonic_stack[l + 1] = value;
				size_stack = l + 2;
				return monotonic_stack[l];
			}
		};
	}

	namespace task_1027 {
		/*
		* https://leetcode.com/problems/longest-arithmetic-subsequence/description/
		*/
		class Solution {
		public:
			int longestArithSeqLength_copied(vector<int>& nums) {
				if (nums.size() <= 2)
					return nums.size();
				int ans = 1;
				vector<unordered_map<int, int>> jd(nums.size());

				for (int i = 1; i < nums.size(); i++)
					for (int j = 0; j < i; j++)
					{
						int diff = nums[i] - nums[j];
						if (jd[j].count(diff) != 0)
							jd[i][diff] = jd[j][diff] + 1;
						else
							jd[i][diff] = 2;
						ans = max(ans, jd[i][diff]);
					}

				return ans;
			}

			int longestArithSeqLength(vector<int>& nums) {
				int max_length = 1;
				int min_elem = nums[0];
				int max_elem = nums[0];
				for (size_t i = 1; i < nums.size(); i++) {
					if (min_elem > nums[i])
						min_elem = nums[i];
					if (max_elem < nums[i])
						max_elem = nums[i];
				}
				max_elem -= min_elem;

				for (int i = 1; i <= max_elem; i++) 
					max_length = max(max_length, max (longestSubsequence(nums, i), longestSubsequence(nums, -i)));

				return max(max_length, lengthForZero(nums));
			}

			int longestSubsequence(const vector<int>& arr, int difference) {
				const size_t size = arr.size();
				int max_length = 1;
				vector<map<int, int>> mod_end_length(abs(difference));

				for (size_t i = 0; i < size; i++) {
					auto it_before = mod_end_length[arr[i] % difference].find(arr[i] - difference);
					auto it = mod_end_length[arr[i] % difference].find(arr[i]);
					int length = 1;

					if (it != mod_end_length[arr[i] % difference].end())
						length = it->second;
					if (it_before != mod_end_length[arr[i] % difference].end())
						length = max(length, it_before->second + 1);
					if (max_length < length)
						max_length = length;
					mod_end_length[arr[i] % difference][arr[i]] = length;
				}
				return max_length;
			}

			int lengthForZero(vector<int>& arr) {
				sort(arr.begin(), arr.end());
				int max_length = 1;
				int length = 1;
				const size_t size = arr.size();
				for (size_t i = 1; i < size; i++)
					if (arr[i - 1] == arr[i])
						++length;
					else {
						if (max_length < length)
							max_length = length;
						length = 1;
					}
				return max(max_length, length);
			}
		};
	}

	namespace task_1035 {
		/*
		* https://leetcode.com/problems/uncrossed-lines/description/
		*/
		class Solution {
		public:
			int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
				size_t size1 = nums1.size();
				size_t size2 = nums2.size();
				if (size1 > size2) {
					swap(size1, size2);
					swap(nums1, nums2);
				}
				vector<int> length_of_LNS(size2);

				for (size_t i = 0; i < size1; i++) {
					int length = 0;
					for (size_t j = 0; j < size2; j++) {
						int cur_length = length_of_LNS[j];
						if (nums1[i] == nums2[j])
							length_of_LNS[j] = length + 1;
						length = max(length, cur_length);
					}
				}

				int length = 0;
				for (size_t i = 0; i < size2; i++)
					length = max(length, length_of_LNS[i]);
				return length;
			}
		};
	}

	namespace task_1038 {
		/*
		* https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/description/
		*/
		class Solution {
		public:
			int sum;

			TreeNode* bstToGst(TreeNode* root) {
				sum = 0;
				bstToGstReq(root);
				return root;
			}

			void bstToGstReq(TreeNode* root) {
				if (root->right)
					bstToGstReq(root->right);
				sum += root->val;
				root->val = sum;
				if (root->left)
					bstToGstReq(root->left);
			}
		};
	}

	namespace task_1051 {
		/*
		* https://leetcode.com/problems/problems/height-checker/description/
		*/
		class Solution {
		public:
			int heightChecker(vector<int>& heights) {
				vector<int> copy = heights;
				sort(copy.begin(), copy.end());
				int count = 0;
				for (size_t i = 0, size = copy.size(); i < size; ++i)
					if (heights[i] != copy[i])
						++count;
				return count;
			}
		};
	}

	namespace task_1052 {
		/*
		* https://leetcode.com/problems/grumpy-bookstore-owner/description/
		*/
		class Solution {
		public:
			int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
				int score_max, score_after = 0, score_before = 0, score_window = 0;
				size_t size = customers.size();
				for (int& v : grumpy) // to make 1 - not grumpy, 0 - grumpy
					v ^= 1;
				for (size_t i = 0; i < minutes; ++i)
					score_window += customers[i];
				for (size_t i = minutes; i < size; ++i)
					score_after += customers[i] * grumpy[i];
				score_max = score_window + score_after;
				for (size_t i = minutes; i < size; ++i) {
					score_window += customers[i] - customers[i - minutes];
					score_after -= customers[i] * grumpy[i];
					score_before += customers[i - minutes] * grumpy[i - minutes];
					score_max = max(score_max, score_before + score_window + score_after);
				}
				return score_max;
			}
		};
	}

	namespace task_1061 {
		/*
		* https://leetcode.com/problems/lexicographically-smallest-equivalent-string/description/
		*/
		class Solution {
		public:
			vector<char> smallest_char = vector<char>(26);

			string smallestEquivalentString(string s1, string s2, string baseStr) {
				for (size_t i = 0; i < 26; ++i)
					smallest_char[i] = i;

				size_t size = s1.size();
				for (size_t i = 0; i < size; ++i) {
					auto i1 = s1[i] - 'a', i2 = s2[i] - 'a';
					auto c1 = getChar(i1), c2 = getChar(i2);
					smallest_char[max(c1, c2)] = min(c1, c2);
				}

				size = baseStr.size();
				for (size_t i = 0; i < size; ++i)
					baseStr[i] = getChar(baseStr[i] - 'a') + 'a';

				return baseStr;
			}

			char getChar(char ind) {
				char i = smallest_char[ind];
				while (i != smallest_char[i])
					i = smallest_char[i];
				smallest_char[ind] = i;
				return i;
			}
		};
	}

	namespace task_1072 {
		/*
		* https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/description/
		*/
		class Solution {
		public:
			int maxEqualRowsAfterFlips__leetcode(vector<vector<int>>& matrix) {
				unordered_map<string, int> patternFrequency;

				for (auto& currentRow : matrix) {
					string patternBuilder = "";
					for (int col = 0; col < currentRow.size(); col++) {
						if (currentRow[0] == currentRow[col])
							patternBuilder += "T";
						else
							patternBuilder += "F";
					}
					patternFrequency[patternBuilder]++;
				}
				int maxFrequency = 0;
				for (auto& entry : patternFrequency)
					maxFrequency = max(entry.second, maxFrequency);

				return maxFrequency;
			}
		};
	}

	namespace task_1106 {
		/*
		* https://leetcode.com/problems/parsing-a-boolean-expression/description/
		*/
		class Solution {
		public:
			bool parseBoolExpr_stack(string expression) {
				stack<char> st;

				// Traverse through the expression
				for (char currChar : expression) {
					if (currChar == ',' || currChar == '(')
						continue;  // Skip commas and open parentheses

					// Push operators and boolean values to the stack
					if (currChar == 't' || currChar == 'f' || currChar == '!' ||
						currChar == '&' || currChar == '|') {
						st.push(currChar);
					}
					// Handle closing parentheses and evaluate the subexpression
					else if (currChar == ')') {
						bool hasTrue = false, hasFalse = false;

						// Process the values inside the parentheses
						while (st.top() == 't' || st.top() == 'f') {
							char topValue = st.top();
							st.pop();
							if (topValue == 't') hasTrue = true;
							if (topValue == 'f') hasFalse = true;
						}

						// Pop the operator and evaluate the subexpression
						char op = st.top();
						st.pop();
						if (op == '!')
							st.push(hasTrue ? 'f' : 't');
						else if (op == '&')
							st.push(hasFalse ? 'f' : 't');
						else
							st.push(hasTrue ? 't' : 'f');
					}
				}

				// The final result is at the top of the stack
				return st.top() == 't';
			}

			bool parseBoolExpr(string expression) {
				size_t size = expression.size();
				if (size == 1)
					return expression[0] == 't';

				switch (expression[0])
				{
				case '!': {
					return !parseBoolExpr(expression.substr(2, size - 3));
				}
				case '|': {
					size_t from = 2, to = get_to(expression, from, size);
					while (from != size && !parseBoolExpr(expression.substr(from, to - from)))
					{
						from = to + 1;
						to = get_to(expression, from, size);
					}

					return from != size;
				}
				case '&': {
					size_t from = 2, to = get_to(expression, from, size);
					while (from != size && parseBoolExpr(expression.substr(from, to - from)))
					{
						from = to + 1;
						to = get_to(expression, from, size);
					}

					return from == size;
				}
				default:
					return false;
				}
			}

			size_t get_to(const string& expression, const size_t from, const size_t size) {
				int count_open = 0, count_close = 0;
				for (size_t i = from; i < size; i++) {
					if (expression[i] == '(')
						++count_open;
					else if (expression[i] == ')')
						++count_close;
					else if (expression[i] == ',' && count_open == count_close)
						return i;
				}
				return size - 1;
			}
		};
	}

	namespace task_1110 {
		/*
		* https://leetcode.com/delete-nodes-and-return-forest/description/
		*/
		class Solution {
		public:
			vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
				unordered_set<int> set_to_delete(to_delete.begin(), to_delete.end());
				stack<pair<TreeNode*, int>> stack; // node; 0 - delete, 1 - is root, 2 - is node;
				stack.push({ root, set_to_delete.contains(root->val) ? 0 : 1 });
				vector<TreeNode*> roots;
				while (!stack.empty()) {
					auto node = stack.top();
					stack.pop();
					if (node.second == 0) {
						if (node.first->left)
							stack.push({ node.first->left, set_to_delete.contains(node.first->left->val) ? 0 : 1 });
						if (node.first->right)
							stack.push({ node.first->right, set_to_delete.contains(node.first->right->val) ? 0 : 1 });
					}
					else {
						if (node.second == 1)
							roots.push_back(node.first);
						if (node.first->left)
							if (set_to_delete.contains(node.first->left->val)) {
								stack.push({ node.first->left, 0 });
								node.first->left = nullptr;
							}
							else
								stack.push({ node.first->left, 2 });
						if (node.first->right)
							if (set_to_delete.contains(node.first->right->val)) {
								stack.push({ node.first->right, 0 });
								node.first->right = nullptr;
							}
							else
								stack.push({ node.first->right, 2 });
					}
				}

				return roots;
			}

			vector<TreeNode*> delNodesVector(TreeNode* root, vector<int>& to_delete) {
				vector<int> set_to_delete(1001);
				for (const int n : to_delete)
					set_to_delete[n] = 1;
				stack<pair<TreeNode*, int>> stack; // node; 0 - delete, 1 - is root, 2 - is node;
				stack.push({ root, set_to_delete[root->val] ? 0 : 1 });
				vector<TreeNode*> roots;
				while (!stack.empty()) {
					auto node = stack.top();
					stack.pop();
					if (node.second == 0) {
						if (node.first->left)
							stack.push({ node.first->left, set_to_delete[node.first->left->val] ? 0 : 1 });
						if (node.first->right)
							stack.push({ node.first->right, set_to_delete[node.first->right->val] ? 0 : 1 });
					}
					else {
						if (node.second == 1)
							roots.push_back(node.first);
						if (node.first->left)
							if (set_to_delete[node.first->left->val]) {
								stack.push({ node.first->left, 0 });
								node.first->left = nullptr;
							}
							else
								stack.push({ node.first->left, 2 });
						if (node.first->right)
							if (set_to_delete[node.first->right->val]) {
								stack.push({ node.first->right, 0 });
								node.first->right = nullptr;
							}
							else
								stack.push({ node.first->right, 2 });
					}
				}

				return roots;
			}
		};
	}

	namespace task_1122 {
		/*
		* https://leetcode.com/problems/problems/relative-sort-array/description/
		*/
		class Solution {
		public:
			vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
				unordered_map<int, int> hash_map;
				for (const int n : arr2)
					hash_map[n] = 0;
				vector<int> not_contain;
				for (const int n : arr1)
					if (auto it = hash_map.find(n); it != hash_map.end())
						++it->second;
					else
						not_contain.push_back(n);
				sort(not_contain.begin(), not_contain.end());
				arr1.clear();
				for (const int n : arr2) {
					int length = hash_map[n];
					for (int i = 0; i < length; i++)
						arr1.push_back(n);
				}
				arr1.insert(arr1.end(), not_contain.begin(), not_contain.end());
				return arr1;
			}
		};
	}

	namespace task_1123 {
		/*
		* https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/description/
		*/
		class Solution {
		public:
			TreeNode* res;
			int max_depth;

			TreeNode* lcaDeepestLeaves(TreeNode* root) {
				res = root;
				max_depth = 1;
				if (!root)
					return root;
				lcaDeepestLeavesReq(root, 1);
				return res;
			}

			int lcaDeepestLeavesReq(TreeNode* node, int depth) {
				int depth_l = 0, depth_r = 0;
				if (node->left)
					depth_l = lcaDeepestLeavesReq(node->left, depth + 1);
				if (node->right)
					depth_r = lcaDeepestLeavesReq(node->right, depth + 1);

				if (depth_l == 0 && depth_r == 0) {
					if (max_depth < depth) {
						max_depth = depth;
						res = node;
					}
					return depth;
				}
				else if (depth_l == max_depth && depth_r == max_depth)
					res = node;
				return max(depth_l, depth_r);
			}
		};
	}

	namespace task_1128 {
		/*
		* https://leetcode.com/problems/number-of-equivalent-domino-pairs/description/
		*/
		class Solution {
		public:
			int numEquivDominoPairs(vector<vector<int>>& dominoes) {
				vector<vector<int>> values(10, vector<int>(10));
				for (vector<int>& domino : dominoes) {
					if (domino[0] > domino[1])
						swap(domino[0], domino[1]);
					++values[domino[0]][domino[1]];
				}

				int pairs = 0;
				for (const vector<int>& value : values) {
					for (const int count : value)
						pairs += count * (count - 1) / 2;
				}

				return pairs;
			}
		};
	}

	namespace task_1137 {
		/*
		* https://leetcode.com/problems/n-th-tribonacci-number/description/
		*/
		class Solution {
		public:
			int tribonacci(int n) {
				if (n < 2)
					return n;
				if (n == 2)
					return 1;
				int cur = 2;
				int prev = 1;
				int prev_prev = 1;
				for (size_t i = 3; i < n; i++) {
					int temp = cur + prev + prev_prev;
					prev_prev = prev;
					prev = cur;
					cur = temp;
				}
				return cur;
			}
		};
	}

	namespace task_1140 {
		/*
		* https://leetcode.com/problems/stone-game/description/
		*/
		class Solution {
		public:
			vector<unordered_map<int, int>> possible_gain;
			vector<int> remain_sum;
			size_t size;
			int sum;

			int stoneGameII(vector<int>& piles) {
				size = piles.size();
				sum = 0;
				for (const int n : piles)
					sum += n;
				possible_gain = vector<unordered_map<int, int>>(size);
				remain_sum = vector<int>(size);
				remain_sum[0] = sum;
				for (size_t i = 1; i < size; i++)
					remain_sum[i] = remain_sum[i - 1] - piles[i - 1];
				fillGains(piles, 0, 2);
				return possible_gain[0][2];
			}

			void fillGains(const vector<int>& piles, const int from, int m) {
				if (from + m >= size) {
					possible_gain[from][m] = remain_sum[from];
					return;
				}
				int max_gain = 0;
				for (int x = 1; x <= m; ++x) {
					int next_m = max(m, x << 1);
					if (!possible_gain[from + x].contains(next_m))
						fillGains(piles, from + x, next_m);
					max_gain = max(max_gain, remain_sum[from] - possible_gain[from + x][next_m]);
				}
				possible_gain[from][m] = max_gain;
			}
		};
	}

	namespace task_1143 {
		/*
		* https://leetcode.com/problems/longest-common-subsequence/description/
		*/
		class Solution {
		public:
			int longestCommonSubsequence(string text1, string text2) {
				size_t size1 = text1.size();
				size_t size2 = text2.size();
				if (size1 > size2) {
					swap(size1, size2);
					swap(text1, text2);
				}
				vector<int> length_of_LNS(size2);

				for (size_t i = 0; i < size1; i++) {
					int length = 0;
					for (size_t j = 0; j < size2; j++) {
						int cur_length = length_of_LNS[j];
						if (text1[i] == text2[j])
							length_of_LNS[j] =  length + 1;
						length = max(length, cur_length);
					}
				}

				int length = 0;
				for (size_t i = 0; i < size2; i++)
					length = max(length, length_of_LNS[i]);
				return length;
			}
		};
	}

	namespace task_1146 {
		/*
		* https://leetcode.com/snapshot-array/description/
		*/
		class SnapshotArray {
		public:
			SnapshotArray(int length) : id(0), data(length){
				for (size_t i = 0; i < length; i++)
					data[i][0] = 0;
			}

			void set(int index, int val) {
				data[index][-id] = val;
			}

			int snap() {
				return id++;
			}

			int get(int index, int snap_id) {
				return data[index].lower_bound(-snap_id)->second;
			}

			int id;
			vector<map<int, int>> data;
		};
	}

	namespace task_1161 {
		/*
		* https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/description
		*/
		class Solution {
		public:
			int maxLevelSum(TreeNode* root, int k) {
				queue<TreeNode*> queue;
				queue.push(root);

				size_t level_size = 1;
				int level = 1, max_level = 0, sum = 0, max_sum = INT_MIN;
				while (level_size != 0) {
					sum = 0;
					for (size_t i = 0; i < level_size; ++i) {
						root = queue.front();
						queue.pop();
						sum += root->val;
						if (root->left)
							queue.push(root->left);
						if (root->right)
							queue.push(root->right);
					}
					if (max_sum < sum) {
						max_sum = sum;
						max_level = level;
					}
					level_size = queue.size();
					++level;
				}
				return max_level;
			}
		};
	}

	namespace task_1171 {
		/*
		* https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/
		*/
		class Solution {
		public:
			ListNode* removeZeroSumSublists(ListNode* head) {
				ListNode* guard = new ListNode(0, head);
				ListNode* start = guard;
				while (start->next) {
					int sum = 0;
					ListNode* ptr = start->next;
					for (; ptr; ptr = ptr->next) {
						sum += ptr->val;
						if (sum == 0)
							break;
					}
					if (ptr)
						start->next = ptr->next;
					else
						start = start->next;
				}
				head = guard->next;
				delete guard;
				return head;
			}
		};
	}

	namespace task_1190 {
		/*
		* https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/description/
		*/
		class Solution {
		public:
			string reverseParentheses(string s) {
				string res;
				size_t size = s.size();
				for (size_t i = 0; i < size; ++i)
					if (s[i] != '(')
						res.push_back(s[i]);
					else
						res += reverseInBracket(s, i);
				return res;
			}

			string reverseInBracket(const string& s, size_t& i) {
				string res;
				++i;
				for (; s[i] != ')'; ++i)
					if (s[i] != '(')
						res.push_back(s[i]);
					else
						res += reverseInBracket(s, i);
				std::reverse(res.begin(), res.end());
				return res;
			}
		};
	}

	namespace task_1208 {
		/*
		* https://leetcode.com/problems/get-equal-substrings-within-budget/description/
		*/
		class Solution {
		public:
			int equalSubstring(string s, string t, int maxCost) {
				int max_len = 0;
				int cost = 0;
				int size = s.size();
				int j = 0;
				for (int i = 0; i < size; i++) {
					s[i] = abs(s[i] - t[i]);
					cost += s[i];
					for (; cost > maxCost; ++j)
						cost -= s[j];
					max_len = max(max_len, i - j + 1);
				}
				return max_len;
			}
		};
	}

	namespace task_1218 {
		/*
		* https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/description/
		*/
		class Solution {
		public:
			int longestSubsequence(vector<int>& arr, int difference) {
				if (difference == 0)
					return lengthForZero(arr);
				const size_t size = arr.size();
				if (difference < 0) {
					for (int& val : arr)
						val = -val;
					difference = -difference;
				}
				int min_eleml = arr[0];
				for (size_t i = 1; i < size; i++)
					if (min_eleml > arr[i])
						min_eleml = arr[i];
				if (min_eleml < 0)
					for (size_t i = 0; i < size; i++)
						arr[i] -= min_eleml;
				vector<map<int, int>> mod_end_length(difference);
				int max_length = 0;

				for (size_t i = 0; i < size; i++) {
					auto it_before = mod_end_length[arr[i] % difference].find(arr[i] - difference);
					auto it = mod_end_length[arr[i] % difference].find(arr[i]);
					int length = 1;

					if (it != mod_end_length[arr[i] % difference].end())
						length = it->second;
					if (it_before != mod_end_length[arr[i] % difference].end())
						length = max(length, it_before->second + 1);
					if (max_length < length)
						max_length = length;
					mod_end_length[arr[i] % difference][arr[i]] = length;
				}
				return max_length;
			}

			int lengthForZero(vector<int>& arr) {
				sort(arr.begin(), arr.end());
				int max_length = 1;
				int length = 1;
				const size_t size = arr.size();
				for (size_t i = 1; i < size; i++)
					if (arr[i - 1] == arr[i])
						++length;
					else {
						if (max_length < length)
							max_length = length;
						length = 1;
					}
				return max(max_length, length);
			}
		};
	}

	namespace task_1219 {
		/*
		* https://leetcode.com/problems/path-with-maximum-gold/description/
		*/
		class Solution {
		public:
			vector<vector<int>> way; // 0-gold; 1-2 index; 3-direction
			// 0 - down; 1 - right; 2 - up; 3 - left; 4 - nowhere

			int getMaximumGold(vector<vector<int>>& grid) {
				way = vector<vector<int>>(25, vector<int>(4));
				int max_sum = 0;
				size_t length = grid.size();
				size_t width = grid[0].size();
				for (size_t i = 0; i < length; i++)
					for (size_t j = 0; j < width; j++)
						if (grid[i][j])
							max_sum = max(max_sum, dfs(grid, i, j));
				return max_sum;
			}

			int dfs(vector<vector<int>>& grid, int start_i, int start_j) {
				int length = grid.size();
				int width = grid[0].size();
				int way_i = 0;
				int max_sum = 0;
				way[way_i][0] = grid[start_i][start_j];
				way[way_i][1] = start_i;
				way[way_i][2] = start_j;
				way[way_i][3] = 0;
				grid[start_i][start_j] = 0;
				int direction, i, j;
				while (way_i != -1) {
					i = way[way_i][1];
					j = way[way_i][2];
					direction = way[way_i][3];
					++way_i;

					if (i + 1 != length && direction < 1 && grid[i + 1][j]) {
						way[way_i][0] = grid[i + 1][j];
						way[way_i][1] = i + 1;
						way[way_i][2] = j;
						way[way_i - 1][3] = 1;
						grid[i + 1][j] = 0;
						continue;
					}
					else if (j + 1 != width && direction < 2 && grid[i][j + 1]) {
						way[way_i][0] = grid[i][j + 1];
						way[way_i][1] = i;
						way[way_i][2] = j + 1;
						way[way_i - 1][3] = 2;
						grid[i][j + 1] = 0;
						continue;
					}
					else if (i - 1 != -1 && direction < 3 && grid[i - 1][j]) {
						way[way_i][0] = grid[i - 1][j];
						way[way_i][1] = i - 1;
						way[way_i][2] = j;
						way[way_i - 1][3] = 3;
						grid[i - 1][j] = 0;
						continue;
					}
					else if (j - 1 != -1 && direction < 4 && grid[i][j - 1]) {
						way[way_i][0] = grid[i][j - 1];
						way[way_i][1] = i;
						way[way_i][2] = j - 1;
						way[way_i - 1][3] = 4;
						grid[i][j - 1] = 0;
						continue;
					}
					int sum = 0;
					for (size_t i = 0; i < way_i; i++)
						sum += way[i][0];
					max_sum = max(max_sum, sum);

					--way_i;
					grid[i][j] = way[way_i][0];
					way[way_i][3] = 0;
					--way_i;
				}
				return max_sum;
			}
		};
	}

	namespace task_1233 {
		/*
		* https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/description
		*/
		class Solution {
		public:
			class Trie {
			public:
				unordered_map<string, Trie*> children;
				int index = -1;
			};

			vector<string> removeSubfolders(vector<string>& folder) {
				Trie* root = new Trie(), * node = nullptr;
				int size = folder.size();
				for (int i = 0; i < size; ++i) {
					string item;
					stringstream input_stringstream(folder[i]);
					node = root;
					bool is_new = true;

					while (getline(input_stringstream, item, '/')) {
						if (item.size() > 0) {
							auto it = node->children.find(item);
							if (it == node->children.end()) {
								auto new_node = new Trie();
								node->children[item] = new_node;
								node = new_node;
							}
							else {
								node = it->second;
								if (node->index != -1) {
									is_new = false;
									break;
								}
							}
						}
					}
					if (is_new)
						node->index = i;
				}

				stack<Trie*> nodes;
				nodes.push(root);
				vector<string> folders;
				while (!nodes.empty()) {
					node = nodes.top();
					nodes.pop();

					if (node->index == -1)
						for (const auto& [key, value] : node->children)
							nodes.push(value);
					else
						folders.push_back(folder[node->index]);
				}

				return folders;
			}
		};
	}

	namespace task_1248 {
		/*
		* https://leetcode.com/problems/count-number-of-nice-subarrays/description/
		*/
		class Solution {
		public:
			int numberOfSubarrays(vector<int>& nums, int k) {
				int count = 0, count_odd = 0;
				size_t size = nums.size(), prev = 0, first = 0, last = 0, next = 0;
				for (; first < size && (nums[first] & 1) == 0; ++first) {}
				last = first;
				for (; last < size && count_odd < k; ++last)
					if (nums[last] & 1)
						++count_odd;
				if (count_odd == k) {
					next = last;
					for (; next < size && (nums[next] & 1) == 0; ++next) {}
					--last;
				}
				else
					return 0;
				while (last < size) {
					count += (next - last) * (first - prev + 1);
					last = next++;
					for (; next < size && (nums[next] & 1) == 0; ++next) {}
					prev = ++first;
					for (; first < size && (nums[first] & 1) == 0; ++first) {}
				}
				return count;
			}
		};
	}

	namespace task_1255 {
		/*
		* https://leetcode.com/problems/maximum-score-words-formed-by-letters/description/
		*/
		class Solution {
		public:
			const size_t count_letters = 26;
			size_t count_words;
			vector<int> remain_letters;
			vector<int> words_score;

			int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
				remain_letters = vector<int>(count_letters);
				for (const char letter : letters)
					++remain_letters[letter - 'a'];
				count_words = words.size();
				words_score = vector<int>(count_words);
				for (size_t i = 0; i < count_words; ++i) {
					int word_score = 0;
					for (const char letter : words[i])
						word_score += score[letter - 'a'];
					words_score[i] = word_score;
				}
				return maxScoreWordsReq(words, 0);
			}

			int maxScoreWordsReq(const vector<string>& words, size_t from) {
				int max_score = 0;
				int score = 0;
				for (size_t i = from; i < count_words; i++) {
					if (checkAddWord(words[i])) {
						max_score = max(max_score, words_score[i] + maxScoreWordsReq(words, i + 1));
						deleteWord(words[i]);
					}
				}
				return max_score;
			}

			bool checkAddWord(const string& word) {
				int i = 0;
				for (; i < word.size(); ++i) {
					--remain_letters[word[i] - 'a'];
					if (remain_letters[word[i] - 'a'] < 0) {
						for (; i >= 0; --i)
							++remain_letters[word[i] - 'a'];
						return false;
					}
				}
				return true;
			}

			void deleteWord(const string& word) {
				for (const char letter : word)
					++remain_letters[letter - 'a'];
			}
		};
	}

	namespace task_1261 {
		/*
		* https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/description/
		*/
		class FindElements {
			unordered_set<int> seen;

		public:
			FindElements(TreeNode* root) { bfs(root); }

			bool find(int target) { return seen.find(target) != seen.end(); }

		private:
			void bfs(TreeNode* root) {
				queue<TreeNode*> queue;
				root->val = 0;
				queue.push(root);

				while (!queue.empty()) {
					TreeNode* currentNode = queue.front();
					queue.pop();
					seen.insert(currentNode->val);
					if (currentNode->left) {
						currentNode->left->val = currentNode->val * 2 + 1;
						queue.push(currentNode->left);
					}
					if (currentNode->right) {
						currentNode->right->val = currentNode->val * 2 + 2;
						queue.push(currentNode->right);
					}
				}
			}
		};
	}

	namespace task_1267 {
		/*
		* https://leetcode.com/problems/count-servers-that-communicate/description/
		*/
		class Solution {
		public:
			int countServers(vector<vector<int>>& grid) {
				const size_t m = grid.size(), n = grid[0].size();
				int count = 0, count_prev;
				for (size_t i = 0; i < m; ++i) {
					size_t j = 0, first;
					for (; j < n && grid[i][j] == 0; ++j) {}
					if (j < n) {
						first = j;
						int count_prev = count;
						++j;
						for (; j < n; ++j) {
							if (grid[i][j] == 1) {
								grid[i][j] = 2;
								++count;
							}
						}
						if (count_prev != count) {
							grid[i][first] = 2;
							++count;
						}
					}
				}

				for (size_t j = 0; j < n; ++j) {
					size_t i = 0, first;
					for (; i < m && grid[i][j] == 0; ++i) {}
					if (i < m) {
						first = i;
						bool found = false;
						++i;
						for (; i < m; ++i) {
							if (grid[i][j] != 0) {
								found = true;
								if (grid[i][j] == 1)
									++count;
							}
						}
						if (found && grid[first][j] == 1)
							++count;
					}
				}

				return count;
			}
		};
	}

	namespace task_1277 {
		/*
		* https://leetcode.com/problems/count-square-submatrices-with-all-ones/description
		*/
		class Solution {
		public:
			int countSquares(vector<vector<int>>& matrix) {
				int row = matrix.size(), col = matrix[0].size();
				vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
				int ans = 0;
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < col; j++) {
						if (matrix[i][j] == 1) {
							dp[i + 1][j + 1] =
								min({ dp[i][j + 1], dp[i + 1][j], dp[i][j] }) + 1;
							ans += dp[i + 1][j + 1];
						}
					}
				}
				return ans;
			}
		};
	}

	namespace task_1295 {
		/*
		* https://leetcode.com/problems/find-numbers-with-even-number-of-digits/description/
		*/
		class Solution {
		public:
			int findNumbers(vector<int>& nums) {
				int count = 0;
				for (int n : nums) {
					int count_digit = 0;
					for (; n > 0; n /= 10, ++count_digit) {}
					count += ~count_digit & 1;
				}

				return count;
			}
		};
	}

	namespace task_1296 {
		/*
		* https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/description/
		*/
		class Solution {
		public:
			bool isPossibleDivide(vector<int>& hand, int groupSize) { // 50.56% 54.60%
				size_t size = hand.size();
				if (size % groupSize != 0)
					return false;
				if (groupSize == 1)
					return true;
				int count_group = size / groupSize;
				map<int, int> counts;
				for (const int n : hand)
					if (auto it = counts.find(n); it != counts.end())
						++it->second;
					else
						counts[n] = 1;

				for (; count_group > 0; --count_group) {
					auto it = counts.begin();
					int prev = it->first - 1;
					size_t i = 0;
					for (; i < groupSize && it != counts.end(); ++i) {
						if (prev + 1 != it->first)
							return false;
						prev = it->first;
						--it->second;
						if (it->second == 0)
							it = counts.erase(it);
						else
							++it;
					}
					if (i < groupSize)
						return false;
				}
				return true;
			}

			bool isNStraightHandCountArr(vector<int>& hand, int groupSize) { // 97.79% 88.85%
				size_t size = hand.size();
				if (size % groupSize != 0)
					return false;
				int count_group = size / groupSize;
				sort(hand.begin(), hand.end());
				vector<pair<int, int>> counts;
				for (size_t i = 0; i < size; ++i) {
					int n = hand[i];
					int count = 0;
					for (; i < size && n == hand[i]; ++i)
						++count;
					--i;
					counts.push_back({ n , count });
				}
				size = counts.size();
				for (; count_group > 0; --count_group) { // going from back to start
					int prev = counts.back().first + 1;
					int j = counts.size() - 1;
					int i = 0;
					for (; i < groupSize && j >= 0; ++i, --j) {
						if (counts[j].first + 1 != prev || counts[j].second == 0)
							return false;
						--counts[j].second;
						prev = counts[j].first;
					}
					if (i < groupSize)
						return false;
					while (!counts.empty() && counts.back().second == 0)
						counts.pop_back();
				}
				return true;
			}
		};
	}

	namespace task_1298 {
		/*
		* https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/description/
		*/
		class Solution {
		public:
			int maxCandies(vector<int>& status, vector<int>& candies,
				vector<vector<int>>& keys,
				vector<vector<int>>& containedBoxes,
				vector<int>& initialBoxes) {
				vector<char> has_box(status.size()); // 0 do not have, 1 - have closed, 2 - used
				queue<int> q;
				int sum = 0;

				for (int box : initialBoxes) {
					if (status[box]) {
						q.push(box);
						has_box[box] = 2;
						sum += candies[box];
					}
					else {
						has_box[box] = 1;
					}
				}

				while (!q.empty()) {
					int big_box = q.front();
					q.pop();
					for (int key : keys[big_box]) {
						status[key] = 1;
						if (has_box[key] == 1) {
							q.push(key);
							has_box[key] = 2;
							sum += candies[key];
						}
					}
					for (int box : containedBoxes[big_box]) {
						if (status[box]) {
							q.push(box);
							has_box[box] = 2;
							sum += candies[box];
						}
						else {
							has_box[box] = 1;
						}
					}
				}

				return sum;
			}
		};
	}

	namespace task_1306 {
		/*
		* https://leetcode.com/problems/jump-game-iii/description/
		*/
		class Solution {
		public:
			bool canReach(vector<int>& arr, int start) {
				size_t size = arr.size();
				vector<int> visited(size);
				stack<int> vertexes;
				vertexes.push(start);
				while (!vertexes.empty()) {
					auto v = vertexes.top();
					vertexes.pop();
					if (!visited[v]) {
						visited[v] = 1;
						if (arr[v]) {
							if (v + arr[v] < size)
								vertexes.push(v + arr[v]);
							if (v - arr[v] >= 0)
								vertexes.push(v - arr[v]);
						}
					}
				}

				for (size_t i = 0; i < size; i++) 
					if (arr[i] == 0 && visited[i] != 0)
						return true;

				return false;
			}
		};
	}

	namespace task_1310 {
		/*
		* https://leetcode.com/xor-queries-of-a-subarray/description/
		*/
		class Solution {
		public:
			vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
				size_t size = queries.size();
				vector<int> answers(size);
				for (size_t i = 0; i < size; i++) {
					int j = queries[i][0], to = queries[i][1] + 1;
					int value = 0;
					for (; j < to; ++j)
						value ^= arr[j];
					answers[i] = value;
				}
				return answers;
			}

			vector<int> xorQueriesFaster(vector<int>& arr, vector<vector<int>>& queries) {
				vector<int> result;

				// Step 1: Convert arr into an in-place prefix XOR array
				for (int i = 1; i < arr.size(); ++i)
					arr[i] ^= arr[i - 1];

				// Step 2: Resolve each query using the prefix XOR array
				for (const auto& q : queries)
					if (q[0] > 0)
						result.push_back(arr[q[0] - 1] ^ arr[q[1]]);
					else
						result.push_back(arr[q[1]]);

				return result;
			}
		};
	}

	namespace task_1312 {
		/*
		* https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/
		*/
		class Solution {
		public:
			int minInsertions(string s) {
				const int size = s.size();
				const int iter_size = size * 2 + 1;

				int length = size;
				for (int i = 0; i < iter_size; ++i) {
					auto s1 = s.substr(0, i >> 1);
					int j = (i >> 1) + i % 2;
					auto s2 = s.substr(j, size - j);
					reverse(s2.begin(), s2.end());
					int commenLength = longestCommonSubsequence(s1, s2);
					length = min(length, size - (commenLength << 1) - i % 2);
				}
				return length;
			}

			int longestCommonSubsequence(string text1, string text2) {
				size_t size1 = text1.size();
				size_t size2 = text2.size();
				if (size1 > size2) {
					swap(size1, size2);
					swap(text1, text2);
				}
				if (size1 == 0)
					return 0;
				vector<int> length_of_LNS(size2);

				for (size_t i = 0; i < size1; i++) {
					int length = 0;
					for (size_t j = 0; j < size2; j++) {
						int cur_length = length_of_LNS[j];
						if (text1[i] == text2[j])
							length_of_LNS[j] = length + 1;
						length = max(length, cur_length);
					}
				}

				int length = 0;
				for (size_t i = 0; i < size2; i++)
					length = max(length, length_of_LNS[i]);
				return length;
			}
		};
	}

	namespace task_1318 {
		/*
		* https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/description/
		*/
		class Solution {
		public:
			int minFlips(int a, int b, int c) {
				int count = 0;
				int a_or_b = a | b;
				for (size_t i = 0; i < 30; i++)
				{
					if ((a_or_b & 1) != (c & 1)) {
						count += (a & 1) + (b & 1) + (c & 1);
					}
					a >>= 1;
					b >>= 1;
					c >>= 1;
					a_or_b >>= 1;
				}
				return count;
			}
		};
	}

	namespace task_1325 {
		/*
		* https://leetcode.com/problems/delete-leaves-with-a-given-value/description/
		*/
		class Solution {
		public:
			TreeNode* removeLeafNodes(TreeNode* root, int target) {
				if (root->left) root->left = removeLeafNodes(root->left, target);
				if (root->right) root->right = removeLeafNodes(root->right, target);
				if (!root->left && !root->right && root->val == target) return nullptr;
				return root;
			}
		};
	}

	namespace task_1331 {
		/*
		* https://leetcode.com/rank-transform-of-an-array/description/
		*/
		class Solution {
		public:
			vector<int> arrayRankTransform(vector<int>& arr) {
				size_t size = arr.size();
				vector<pair<int, size_t>> number_pos(size);
				for (size_t i = 0; i < size; ++i)
					number_pos[i] = { arr[i], i };
				sort(number_pos.begin(), number_pos.end());
				int rank = 1;
				for (size_t i = 0; i < size; ++i, ++rank) {
					int value = number_pos[i].first;
					arr[number_pos[i].second] = rank;
					size_t j = i + 1;
					for (; j < size && number_pos[j].first == value; ++j)
						arr[number_pos[j].second] = rank;
					i = j - 1;
				}
				return arr;
			}
		};
	}

	namespace task_1334 {
		/*
		* https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/
		*/
		class Solution {
		public:
			int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
				++distanceThreshold;
				vector<vector<int>> dist_matrix(n, vector<int>(n, 1000000));
				for (int i = 0; i < n; i++)
					dist_matrix[i][i] = 0;
				for (const vector<int>& edge : edges) {
					dist_matrix[edge[0]][edge[1]] = edge[2];
					dist_matrix[edge[1]][edge[0]] = edge[2];
				}
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						for (int k = 0; k < n; k++)
							dist_matrix[j][k] = min(dist_matrix[j][k], dist_matrix[j][i] + dist_matrix[i][k]);
				int min_count = n;
				int city;
				for (int i = 0; i < n; i++) {
					int count = 0;
					for (int j = 0; j < n; j++)
						if (dist_matrix[i][j] < distanceThreshold)
							++count;
					if (min_count >= count) {
						min_count = count;
						city = i;
					}
				}
				return city;
			}

			vector<vector<int>> floydWarshall(const size_t size) {
				vector<vector<int>> dist_matrix(size, vector<int>(size, 1000000));
				for (size_t i = 0; i < size; i++)
					for (size_t j = 0; j < size; j++)
						for (size_t k = 0; k < size; k++)
							dist_matrix[j][k] = min(dist_matrix[j][k], dist_matrix[j][i] + dist_matrix[i][k]);
				return dist_matrix;
			}
		};
	}

	namespace task_1346 {
		/*
		* https://leetcode.com/problems/check-if-n-and-its-double-exist/description/
		*/
		class Solution {
		public:
			bool checkIfExist(vector<int>& arr) {
				size_t size = arr.size();
				for (size_t i = 0; i < size - 1; ++i)
					for (size_t j = i + 1; j < size; ++j)
						if ((arr[i] << 1) == arr[j] || (arr[j] << 1) == arr[i])
							return true;
				return false;
			}
		};
	}

	namespace task_1351 {
		/*
		* https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/description/
		*/
		class Solution {
		public:
			int countNegatives(vector<vector<int>>& grid) {
				const size_t length = grid.size();
				const size_t width = grid[0].size();
				int count_neg = 0;
				for (size_t i = 0; i < length; i++)
					count_neg += width - bin_search(grid[i], width);
				return count_neg;
			}

			int bin_search(vector<int> &nums, size_t r) {
				size_t l = 0;
				if (nums[l] < 0)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] < 0)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_1352 {
		/*
		* https://leetcode.com/problems/product-of-the-last-k-numbers/description/
		*/
		class ProductOfNumbers {
		public:
			vector<int> prefixProduct;
			int size = 0;

			ProductOfNumbers() {
				prefixProduct.push_back(1);
				size = 0;
			}

			void add(int num) {
				if (num == 0) {
					prefixProduct = { 1 };
					size = 0;
				}
				else {
					prefixProduct.push_back(prefixProduct[size] * num);
					size++;
				}
			}

			int getProduct(int k) {
				return k > size ? 0 : prefixProduct[size] / prefixProduct[size - k];
			}
		};
	}

	namespace task_1358 {
		/*
		* https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/
		*/
		class Solution {
		public:
			int numberOfSubstrings(string s) {
				int count_letters = 0, count_substrings = 0;
				const size_t size = s.size();
				vector<int> letters(3);

				for (size_t i = 0, start = 0; i < size; ++i) {
					if (++letters[s[i] - 'a'] == 1) {
						++count_letters;
						while (count_letters == 3) {
							count_substrings += size - i;
							if (--letters[s[start] - 'a'] == 0)
								--count_letters;
							++start;
						}
					}
				}

				return count_substrings;
			}

			int numberOfSubstrings__fast(string s) {
				const size_t size = s.length();
				// Track last position of a, b, c
				vector<int> lastPos = { -1, -1, -1 };
				int count_substrings = 0;

				for (size_t i = 0; i < size; ++i) {
					// Update last position of current character
					lastPos[s[i] - 'a'] = i;

					// Add count of valid substrings ending at current position
					// If any character is missing, min will be -1
					// Else min gives leftmost required character position
					count_substrings += 1 + min({ lastPos[0], lastPos[1], lastPos[2] });
				}

				return count_substrings;
			}
		};
	}

	namespace task_1361 {
		/*
		* https://leetcode.com/problems/validate-binary-tree-nodes/description/
		*/
		class Solution {
		public:
			bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
				const size_t size = n;
				vector<int> used(size, 0);

				for (size_t i = 0; i < size; i++)
				{
					if (leftChild[i] != -1)
						++used[leftChild[i]];
					if (rightChild[i] != -1)
						++used[rightChild[i]];
				}
				size_t count_zero = 0;
				size_t head = 0;
				for (size_t i = 0; i < size; i++) {
					if (used[i] > 1)
						return false;
					if (used[i] == 0) {
						++count_zero;
						head = i;
					}
					used[i] = 0;
				}
				if (count_zero != 1)
					return false;
				stack<int> stack;
				stack.push(head);
				while (!stack.empty()) {
					size_t node = stack.top();
					stack.pop();
					++used[node];
					if (leftChild[node] != -1)
						stack.push(leftChild[node]);
					if (rightChild[node] != -1)
						stack.push(rightChild[node]);
				}

				for (size_t i = 0; i < size; i++)
					if (used[i] != 1)
						return false;

				return true;
			}
		};
	}

	namespace task_1367 {
		/*
		* https://leetcode.com/problems/linked-list-in-binary-tree/description/
		*/
		class Solution {
		public:
			bool isSubPath(ListNode* head, TreeNode* root) {
				queue<TreeNode*> queue({ root });
				while (!queue.empty()) {
					root = queue.front();
					queue.pop();
					if (root->val == head->val) {
						bool res = isSubPathReq(head, root);
						if (res)
							return res;
					}
					if (root->left)
						queue.push(root->left);
					if (root->right)
						queue.push(root->right);
				}
				return false;
			}

			bool isSubPathReq(ListNode* head, TreeNode* root) {
				if (!head->next)
					return true;
				if (root->left && root->left->val == head->next->val) {
					bool res = isSubPathReq(head->next, root->left);
					if (res)
						return res;
				}
				if (root->right && root->right->val == head->next->val) {
					bool res = isSubPathReq(head->next, root->right);
					if (res)
						return res;
				}
				return false;
			}
		};
	}

	namespace task_1368 {
		/*
		* https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/
		*/
		class Solution {
		public:
			const vector<vector<int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

			int minCost__leetcode(vector<vector<int>>& grid) {
				int numRows = grid.size(), numCols = grid[0].size(), cost = 0;

				// Track minimum cost to reach each cell
				vector<vector<int>> minCost(numRows, vector<int>(numCols, INT_MAX));

				// Queue for BFS part - stores cells that need cost increment
				queue<pair<int, int>> queue;

				// Start DFS from origin with cost 0
				dfs(grid, 0, 0, minCost, cost, queue);

				// BFS part - process cells level by level with increasing cost
				while (!queue.empty()) {
					cost++;
					int levelSize = queue.size();

					while (levelSize-- > 0) {
						auto [row, col] = queue.front();
						queue.pop();

						// Try all 4 directions for next level
						for (int dir = 0; dir < 4; dir++) {
							dfs(grid, row + dirs[dir][0], col + dirs[dir][1], minCost,
								cost, queue);
						}
					}
				}

				return minCost[numRows - 1][numCols - 1];
			}

			// DFS to explore all reachable cells with current cost
			void dfs(vector<vector<int>>& grid, int row, int col,
				vector<vector<int>>& minCost, int cost,
				queue<pair<int, int>>& queue) {
				if (!isUnvisited(minCost, row, col)) return;

				minCost[row][col] = cost;
				queue.push({ row, col });

				// Follow the arrow direction without cost increase
				int nextDir = grid[row][col] - 1;
				dfs(grid, row + dirs[nextDir][0], col + dirs[nextDir][1], minCost, cost,
					queue);
			}

			// Check if cell is within bounds and unvisited
			bool isUnvisited(vector<vector<int>>& minCost, int row, int col) {
				return row >= 0 && col >= 0 && row < minCost.size() &&
					col < minCost[0].size() && minCost[row][col] == INT_MAX;
			}
		};
	}

	namespace task_1371 {
		/*
		* https://leetcode.com/find-the-longest-substring-containing-vowels-in-even-counts/description/
		*/
		class Solution {
		public:
			int findTheLongestSubstring(string s) {
				int size = s.size(), length = 0, prefixXOR = 0, character;
				vector<int> first_position(32, size);
				first_position[0] = -1;
				for (int i = 0; i < size; ++i) {
					switch (s[i]) {
					case 'a': character = 1; break;
					case 'e': character = 2; break;
					case 'i': character = 4; break;
					case 'o': character = 8; break;
					case 'u': character = 16; break;
					default: character = 0; break;
					}
					prefixXOR ^= character;
					first_position[prefixXOR] = min(i, first_position[prefixXOR]);
					length = max(length, i - first_position[prefixXOR]);
				}
				return length;
			}
		};
	}

	namespace task_1380
	{
		/*
		* https://leetcode.com/problems/lucky-numbers-in-a-matrix/description/
		*/
		class Solution {
		public:
			vector<int> luckyNumbers(vector<vector<int>>& matrix) {
				const size_t m = matrix.size(), n = matrix[0].size();
				vector<int> res;
				for (size_t i = 0; i < m; ++i) {
					int min_val = matrix[i][0];
					int min_j = 0;
					for (size_t j = 1; j < n; ++j)
						if (min_val > matrix[i][j]) {
							min_val = matrix[i][j];
							min_j = j;
						}

					int max_val = min_val;
					for (size_t k = 0; k < m; ++k)
						max_val = max(max_val, matrix[k][min_j]);
					if (max_val == min_val)
						res.push_back(min_val);
				}
				return res;
			}
		};
	}

	namespace task_1381 {
		/*
		* https://leetcode.com/problems/design-a-stack-with-increment-operation/description/
		*/
		class CustomStack {
		public:
			deque<int> deq;
			size_t capacity;

			CustomStack(int maxSize) {
				capacity = maxSize;
			}

			void push(int x) {
				if (deq.size() < capacity)
					deq.push_back(x);
			}

			int pop() {
				if (deq.size() != 0) {
					int back = deq.back();
					deq.pop_back();
					return back;
				}
				return -1;
			}

			void increment(int k, int val) {
				auto it = deq.begin();
				for (int i = 0; i < k && it != deq.end(); ++i, ++it)
					*it += val;
			}
		};

		class CustomStack_leetcode {
		public:
			vector<int> stackArray;
			vector<int> incrementArray; // Vector to store increments for lazy propagation
			int topIndex; // Current top index of the stack

			CustomStack_leetcode(int maxSize) {
				stackArray.resize(maxSize);
				incrementArray.resize(maxSize);
				topIndex = -1;
			}

			void push(int x) {
				if (topIndex < (int)(stackArray.size()) - 1)
					stackArray[++topIndex] = x;
			}

			int pop() {
				if (topIndex == -1) {
					return -1;
				}
				// Calculate the actual value with increment
				int result = stackArray[topIndex] + incrementArray[topIndex];

				// Propagate the increment to the element below
				if (topIndex > 0)
					incrementArray[topIndex - 1] += incrementArray[topIndex];
				incrementArray[topIndex] = 0; // Reset the increment for this position
				--topIndex;
				return result;
			}

			void increment(int k, int val) {
				if (topIndex != -1) // Apply increment to the topmost element of the range
					incrementArray[min(topIndex, k - 1)] += val;
			}
		};
	}

	namespace task_1382
	{
		/*
		* https://leetcode.com/problems/balance-a-binary-search-tree/description/
		*/
		class Solution {
		public:
			TreeNode* balanceBST(TreeNode* root) {
				stack<TreeNode*> nodes;
				TreeNode* node = nullptr;
				nodes.push(root);
				vector<int> vec;
				vector<TreeNode*> not_used;
				while (!nodes.empty()) {
					node = nodes.top();
					if (node->left && node->left->val != 0) {
						nodes.push(node->left);
						continue;
					}

					nodes.pop();
					if (node->right)
						nodes.push(node->right);
					vec.push_back(node->val);
					node->val = 0;
					node->left = nullptr;
					node->right = nullptr;
					not_used.push_back(node);
				}

				int l = 0;
				int r = vec.size();
				int m = (l + r) >> 1;

				root = not_used.back();
				root->val = vec[m];
				not_used.pop_back();
				stack<pair<vector<int>, TreeNode*>> stack;
				if (m - l > 0)
					stack.push({ {l, m, 0}, root });
				if (r - m - 1 > 0)
					stack.push({ {m + 1, r, 1}, root });

				while (!stack.empty()) {
					auto el = stack.top();
					stack.pop();
					l = el.first[0];
					r = el.first[1];
					m = (l + r) >> 1;
					node = not_used.back();
					node->val = vec[m];
					not_used.pop_back();
					if (el.first[2])
						el.second->right = node;
					else
						el.second->left = node;

					if (m - l > 0)
						stack.push({ {l, m, 0}, node });
					if (r - m - 1 > 0)
						stack.push({ {m + 1, r, 1}, node });
				}
				return root;
			}
		};
	}

	namespace task_1395 {
		/*
		* https://leetcode.com/problems/count-number-of-teams/description/
		*/
		class Solution {
		public:
			int numTeams(vector<int>& rating) {
				size_t size = rating.size();
				vector<int> count_more(size);
				vector<int> count_less(size);
				int less = 0, more = 0, teams = 0;
				for (size_t i = 1; i < size; ++i) {
					less = 0, more = 0;
					for (size_t j = i + 1; j < size; ++j)
						if (rating[i] > rating[j])
							++less;
						else
							++more;
					count_less[i] = less;
					count_more[i] = more;
				}
				less = size - 2;
				more = size - 1;
				for (size_t i = 0; i < less; ++i)
					for (size_t j = i + 1; j < more; ++j)
						if (rating[i] > rating[j])
							teams += count_less[j];
						else
							teams += count_more[j];
				return teams;
			}
		};
	}

	namespace task_1399 {
		/*
		* https://leetcode.com/problems/count-largest-group/description/
		*/
		class Solution {
		public:
			int countLargestGroup(int n) {
				vector<int> groups(37);
				++n;
				for (int i = 0; i < 10 && n != 0; ++i) {
					for (int j = 0; j < 10 && n != 0; ++j) {
						for (int k = 0; k < 10 && n != 0; ++k) {
							for (int l = 0; l < 10 && n != 0; ++l) {
								++groups[i + j + k + l];
								--n;
							}
						}
					}
				}
				--groups[0];
				sort(groups.begin(), groups.end());
				int count = 0;
				for (int size = groups.back(); size == groups.back(); ++count, groups.pop_back()) {}
				return count;
			}
		};
	}

	namespace task_1400 {
		/*
		* https://leetcode.com/problems/construct-k-palindrome-strings/description/
		*/
		class Solution {
		public:
			bool canConstruct(string s, int k) {
				// Handle edge cases
				if (s.length() < k) return false;
				if (s.length() == k) return true;

				// Initialize oddCount as an integer bitmask
				int oddCount = 0;

				// Update the bitmask for each character in the string
				for (char chr : s) {
					oddCount ^= 1 << (chr - 'a');
				}

				// Count the number of set bits in the bitmask
				int setBits = 0;// __builtin_popcount(oddCount);

				// Return if the number of odd frequencies is less than or equal to k
				return setBits <= k;
			}
		};
	}

	namespace task_1404 {
		/*
		* https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/description/
		*/
		class Solution {
		public:
			int numSteps(string s) {
				int i = s.size() - 1;
				for (; s[i] == '0'; --i) {}
				int steps = s.size() - 1 - i;
				if (i == 0)
					return steps;

				--i;
				steps += 2;
				for (; i >= 0; --i) {
					if (s[i] == '0')
						steps += 2;
					else
						++steps;
				}
				return steps;
			}
		};
	}

	namespace task_1405 {
		/*
		* https://leetcode.com/problems/longest-happy-string/description/
		*/
		class Solution {
		public:
			string longestDiverseString(int a, int b, int c) {
				vector<int> counts{ a, b, c };
				char last = -1, count_last = 0, max_index = -1, max_remain = -1;
				string res;
				while (true) {
					max_index = -1, max_remain = 0;
					for (char i = 0; i < 3; ++i)
						if ((i != last || count_last != 2) && max_remain < counts[i]) {
							max_remain = counts[i];
							max_index = i;
						}
					if (max_index == -1)
						return res;
					--counts[max_index];
					if (last == max_index) {
						++count_last;
					}
					else {
						last = max_index;
						count_last = 1;
					}
					res.push_back('a' + max_index);
				}
				return "";
			}
		};
	}

	namespace task_1408 {
		/*
		* https://leetcode.com/problems/string-matching-in-an-array/description/
		*/
		class Solution {
		public:
			vector<string> stringMatching__leetcode(vector<string>& words) {
				vector<string> matchingWords;
				TrieNode* root = new TrieNode();  // Initialize the root of the Trie.

				// Insert all suffixes of each word into the Trie.
				for (const auto& word : words) {
					for (int startIndex = 0; startIndex < word.size(); startIndex++) {
						// Insert each suffix starting from index `startIndex`.
						insertWord(root, word.substr(startIndex));
					}
				}

				// Check each word to see if it exists as a substring in the Trie.
				for (auto word : words) {
					if (isSubstring(root, word)) {
						matchingWords.push_back(word);
					}
				}

				return matchingWords;
			}

		private:
			class TrieNode {
			public:
				// Tracks how many times this substring appears in the Trie.
				int frequency;
				// Maps characters to their respective child nodes.
				unordered_map<char, TrieNode*> childNodes;
			};

			// Function to insert a word (or suffix) into the Trie.
			void insertWord(TrieNode* root, const string& word) {
				TrieNode* currentNode = root;
				for (char c : word) {
					// If the character already exists as a child node, move to it.
					if (currentNode->childNodes.find(c) !=
						currentNode->childNodes.end()) {
						currentNode = currentNode->childNodes[c];
						// Increment the frequency of the node.
						currentNode->frequency++;
					}
					else {
						// If the character does not exist, create a new node.
						TrieNode* newNode = new TrieNode();
						// Initialize the frequency to 1.
						newNode->frequency = 1;
						// Add the new node as a child.
						currentNode->childNodes[c] = newNode;
						currentNode = newNode;  // Move to the new node.
					}
				}
			}

			// Function to check if a word exists as a substring in the Trie.
			bool isSubstring(TrieNode* root, string& word) {
				TrieNode* currentNode = root;  // Start from the root node.
				for (char c : word) {
					// Traverse the Trie following the characters of the word.
					currentNode = currentNode->childNodes[c];
				}
				// A word is a substring or a different string if its frequency in the
				// Trie is greater than 1.
				return currentNode->frequency > 1;
			}
		};
	}

	namespace task_1415 {
		/*
		* https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/description/
		*/
		class Solution {
		public:
			vector<string> strs;
			string getHappyString__slow(int n, int k) {
				--n;
				if ((1 << n) * 3 < k)
					return "";
				strs = vector<string>();
				string str = "a";
				genStrings(n, str);
				str[0] = 'b';
				genStrings(n, str);
				str[0] = 'c';
				genStrings(n, str);
				return strs[k - 1];
			}

			void genStrings(int n, string& str) {
				if (n == 0) {
					strs.push_back(str);
					return;
				}
				switch (str.back())
				{
				case 'a': {
					str.push_back('b');
					genStrings(n - 1, str);
					str.pop_back();
					str.push_back('c');
					genStrings(n - 1, str);
					str.pop_back();
					break;
				}case 'b': {
					str.push_back('a');
					genStrings(n - 1, str);
					str.pop_back();
					str.push_back('c');
					genStrings(n - 1, str);
					str.pop_back();
					break;
				}case 'c': {
					str.push_back('a');
					genStrings(n - 1, str);
					str.pop_back();
					str.push_back('b');
					genStrings(n - 1, str);
					str.pop_back();
					break;
				}
				}
			}

			string getHappyString__fast(int n, int k) {
				int count = (1 << (n - 1)) * 3;
				if (count < k)
					return "";
				--k;
				string res;
				if (k * 3 < count)
					res.push_back('a');
				else if (k * 3 < count * 2)
					res.push_back('b');
				else
					res.push_back('c');
				count /= 3;
				k %= count;
				while (count != 1) {
					switch (res.back())
					{
					case 'a': {
						if (k << 1 < count)
							res.push_back('b');
						else
							res.push_back('c');
						break;
					}case 'b': {
						if (k << 1 < count)
							res.push_back('a');
						else
							res.push_back('c');
						break;
					}case 'c': {
						if (k << 1 < count)
							res.push_back('a');
						else
							res.push_back('b');
						break;
					}
					}
					count >>= 1;
					k %= count;
				}

				return res;
			}
		};
	}

	namespace task_1422 {
		/*
		* https://leetcode.com/problems/maximum-score-after-splitting-a-string/description/
		*/
		class Solution {
		public:
			int maxScore(string s) {
				int ones = 0;
				int zeros = 0;
				int best = INT_MIN;

				for (int i = 0; i < s.size() - 1; i++) {
					if (s[i] == '1')
						ones++;
					else
						zeros++;

					best = max(best, zeros - ones);
				}

				if (s[s.size() - 1] == '1')
					ones++;

				return best + ones;
			}
		};
	}

	namespace task_1438 {
		/*
		* https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/description/
		*/
		class Solution {
		public:
			int longestSubarray(vector<int>& nums, int limit) {
				multiset<int> set{ nums[0] };
				size_t size = nums.size(), first = 0, last = 1;
				int max_length = 1;
				for (; last < size; ++last) {
					set.insert(nums[last]);
					while (*(--set.end()) - *set.begin() > limit) {
						set.extract(nums[first]);
						++first;
					}
					max_length = max(max_length, (int)set.size());
				}
				return max_length;
			}

			int longestSubarrayLinear(vector<int>& nums, int limit) {
				deque<int> maxDeque{ nums[0] }, minDeque{ nums[0] };
				size_t size = nums.size(), left = 0, right = 1;
				int max_length = 1;

				for (; right < size; ++right) {
					int value = nums[right];
					while (!maxDeque.empty() && value > maxDeque.back())
						maxDeque.pop_back();
					maxDeque.push_back(value);

					while (!minDeque.empty() && value < minDeque.back())
						minDeque.pop_back();
					minDeque.push_back(value);

					while (maxDeque.front() - minDeque.front() > limit) {
						if (nums[left] == maxDeque.front())
							maxDeque.pop_front();
						if (nums[left] == minDeque.front())
							minDeque.pop_front();
						++left;
					}

					max_length = max(max_length, int(right - left + 1));
				}

				return max_length;
			}
		};
	}

	namespace task_1442 {
		/*
		* https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/
		*/
		class Solution {
		public:
			// if a = b^c^d, then a^b = b^c^d^b = c^d
			int countTriplets(vector<int>& arr) {
				size_t size = arr.size();
				int count = 0;
				for (size_t i = 0; i < size - 1; ++i) {
					int i_j_xor = arr[i];
					int j_k_xor = 0;
					for (size_t k = i + 1; k < size; ++k) {
						j_k_xor ^= arr[k];
						if (i_j_xor == j_k_xor)
							count += k - i;
					}
				}
				return count;
			}
		};
	}

	namespace task_1455 {
		/*
		* https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/description/
		*/
		class Solution {
		public:
			int isPrefixOfWord(string sentence, string searchWord) {
				size_t size = sentence.size(), size_word = searchWord.size();
				int words = 1;
				for (size_t i = 0; i < size; ++i) {
					size_t j = 0;
					for (; i < size && j < size_word && sentence[i] == searchWord[j]; ++i, ++j) {}
					if (j == size_word)
						return words;
					++words;
					for (; i < size && sentence[i] != ' '; ++i) {}
				}
				return -1;
			}
		};
	}

	namespace task_1460 {
		/*
		* https://leetcode.com/problems/make-two-arrays-equal-by-reversing-subarrays/description/
		*
		*/
		class Solution {
		public:
			bool canBeEqual(vector<int>& target, vector<int>& arr) {
				unordered_multiset<int> set;
				for (const int n : target)
					set.insert(n);
				for (const int n : arr)
					if (auto it = set.find(n); it != set.end())
						set.erase(it);
					else
						return false;
				return true;
			}
		};
	}

	namespace task_1462 {
		/*
		* https://leetcode.com/problems/course-schedule-iv/description/
		*/
		class Solution {
		public:
			vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
				vector<vector<int>> dp(numCourses, vector<int>(numCourses));
				for (const auto& edge : prerequisites)
					dp[edge[0]][edge[1]] = 1;

				for (int i = 0; i < numCourses; i++)
					dp[i][i] = 1;

				for (int k = 0; k < numCourses; k++) {
					for (int i = 0; i < numCourses; i++)
						for (int j = 0; j < numCourses; j++)
							dp[i][j] = dp[i][j] | dp[i][k] & dp[k][j];
				}

				vector<bool> res;
				for (const auto& query : queries)
					res.push_back(dp[query[0]][query[1]] == 1);
				return res;
			}
		};

	}

	namespace task_1475 {
		/*
		* https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/
		*/
		class Solution {
		public:
			vector<int> finalPrices(vector<int>& prices) {
				const size_t size = prices.size();
				for (size_t i = 0; i < size; ++i)
				{
					int first = 0;
					for (size_t j = i + 1; j < size && first == 0; ++j)
						if (prices[i] >= prices[j])
							first = prices[j];
					prices[i] -= first;
				}
				return prices;
			}
		};
	}

	namespace task_1482 {
		/*
		* https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/description/
		*/
		class Solution {
		public:
			size_t size;

			int minDays(vector<int>& bloomDay, int m, int k) {
				const size_t size = bloomDay.size();
				if ((long long)m * k > size)
					return -1;
				if (m * k == size)
					return *max_element(bloomDay.begin(), bloomDay.end());
				vector<pair<int, size_t>> bloomDate(size);
				for (size_t i = 0; i < size; i++) {
					bloomDate[i] = { bloomDay[i], i };
					bloomDay[i] = -1;
				}
				sort(bloomDate.begin(), bloomDate.end());
				size_t i = 0, ind, left, right;
				for (; i < m * k; ++i) {
					ind = bloomDate[i].second;
					left = ind;
					right = ind;
					bloomDay[ind] = ind;
					if (ind > 0 && bloomDay[ind - 1] != -1) {
						left = bloomDay[ind - 1];
						bloomDay[ind - 1] = -1;
						bloomDay[left] = right;
						bloomDay[ind] = left;
					}
					if (ind + 1 < size && bloomDay[ind + 1] != -1) {
						right = bloomDay[ind + 1];
						bloomDay[ind + 1] = -1;
						bloomDay[right] = left;
						bloomDay[left] = right;
					}
					if (left != ind && right != ind)
						bloomDay[ind] = -1;
				}

				int countBouqet = 0;
				for (size_t j = 0; j < size; ++j) {
					if (bloomDay[j] == -1)
						continue;
					countBouqet += (bloomDay[j] - j + 1) / k;
					j = bloomDay[j];
				}

				int leftBouqet, rightBouqet;
				for (; countBouqet < m; ++i) {
					ind = bloomDate[i].second;
					left = ind;
					right = ind;
					leftBouqet = 0;
					rightBouqet = 0;
					bloomDay[ind] = ind;
					if (ind > 0 && bloomDay[ind - 1] != -1) {
						left = bloomDay[ind - 1];
						leftBouqet = (ind - left) / k;
						bloomDay[ind - 1] = -1;
						bloomDay[left] = right;
						bloomDay[ind] = left;
					}
					if (ind + 1 < size && bloomDay[ind + 1] != -1) {
						right = bloomDay[ind + 1];
						rightBouqet = (right - ind) / k;
						bloomDay[ind + 1] = -1;
						bloomDay[right] = left;
						bloomDay[left] = right;
					}
					if (left != ind && right != ind)
						bloomDay[ind] = -1;
					countBouqet += (right - left + 1) / k - leftBouqet - rightBouqet;
				}

				return bloomDate[--i].first;
			}

			int minDaysBinSearch(vector<int>& bloomDay, int m, int k) {
				size = bloomDay.size();
				if ((long long)m * k > size)
					return -1;
				int startDay = 0;
				int endDay = *max_element(bloomDay.begin(), bloomDay.end());

				while (startDay + 1 < endDay) {
					int mid = (endDay + startDay) / 2;
					if (canMakeBouqe(bloomDay, mid, k) < m)
						startDay = mid;
					else
						endDay = mid;
				}
				return endDay;
			}

			int canMakeBouqe(vector<int>& bloomDay, int day, int k) {
				int bouqeCount = 0;
				int consequtiveFlowers = 0;
				for (int i = 0; i < size; ++i) {
					if (bloomDay[i] <= day)
						++consequtiveFlowers;
					else
						consequtiveFlowers = 0;
					if (consequtiveFlowers == k) {
						++bouqeCount;
						consequtiveFlowers = 0;
					}
				}
				return bouqeCount;
			}
		};
	}

	namespace task_1497 {
		/*
		* https://leetcode.com/problems/problems/check-if-array-pairs-are-divisible-by-k/description/
		*/
		class Solution {
		public:
			bool canArrange(vector<int>& arr, int k) {
				unordered_map<int, int> remains;
				for (const int n : arr) ++remains[(n % k + k) % k];

				for (auto& [key, value] : remains) {
					if (key == 0) {
						if ((value & 1) == 1)
							return false;
					}
					else {
						auto it = remains.find(k - key);
						if (it == remains.end() || it->second != value)
							return false;
					}
				}
				return true;
			}
		};
	}

	namespace task_1498 {
		/*
		* https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/description/
		*/
		class Solution {
		public:
			int numSubseq(vector<int>& nums, int target) {
				sort(nums.begin(), nums.end());
				unsigned long long sum = 0;
				const int size = nums.size();
				int i = 0;
				int j = size - 1;
				const int modul = 1000000007;

				for (; i < size; i++) {
					while (j >= i && nums[i] + nums[j] > target) 
						--j;
					if (j < i)
						break;
					sum = (sum + pow(j - i, modul)) % modul;
				}
				return sum;
			}

			unsigned long long pow(int degree, const int modul) {
				unsigned long long res = 1;
				unsigned long long mult = 2;
				while (degree) {
					if (degree & 1) {
						res *= mult;
						res %= modul;
					}
					mult *= mult;
					mult %= modul;
					degree >>= 1;
				}
				return res;
			}
		};
	}

	namespace task_1508 {
		/*
		* https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/description/
		*
		*/
		class Solution {
		public:
			int rangeSum(vector<int>& nums, int n, int left, int right) {
				--left;
				size_t size = n * (n + 1) / 2;
				vector<int> sums;
				for (int i = 0; i < n; ++i) {
					int sum = 0;
					for (int j = i; j < n; ++j) {
						sum += nums[j];
						sums.push_back(sum);
					}
				}
				sort(sums.begin(), sums.end());
				long long sum = 0;
				for (; left < right; ++left)
					sum += sums[left];
				return sum % 1000000007;
			}
		};
	}

	namespace task_1509 {
		/*
		* https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/description/
		*/
		class Solution {
		public:
			int minDifference(vector<int>& nums) {
				const size_t size = nums.size();
				if (size < 5)
					return 0;
				sort(nums.begin(), nums.end());
				int min_dif = nums[size - 4] - nums[0];
				min_dif = min(min_dif, nums[size - 3] - nums[1]);
				min_dif = min(min_dif, nums[size - 2] - nums[2]);
				min_dif = min(min_dif, nums[size - 1] - nums[3]);
				return min_dif;
			}

			int minDifferenceFast(vector<int>& nums) {
				int numsSize = nums.size(), minDiff = INT_MAX;
				if (numsSize <= 4) return 0;

				// Partially sort the first four elements
				partial_sort(nums.begin(), nums.begin() + 4, nums.end());
				// Find the 4th largest element
				nth_element(nums.begin() + 4, nums.begin() + (numsSize - 4),
					nums.end());
				// Sort the last four elements
				sort(nums.begin() + (numsSize - 4), nums.end());

				// Four scenarios to compute the minimum difference
				for (int left = 0, right = numsSize - 4; left < 4; left++, right++) {
					minDiff = min(minDiff, nums[right] - nums[left]);
				}

				return minDiff;
			}
		};
	}

	namespace task_1514 {
		/*
		* https://leetcode.com/problems/path-with-maximum-probability/description/
		*/
		class Solution {
		public:
			double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
				size_t size = edges.size();
				vector<vector<pair<double, int>>> adjacency_list(n);
				for (size_t i = 0; i < size; ++i) {
					adjacency_list[edges[i][0]].push_back({ succProb[i], edges[i][1] });
					adjacency_list[edges[i][1]].push_back({ succProb[i], edges[i][0] });
				}

				vector<double> vertexes(n);
				priority_queue<pair<double, int>> queue;
				queue.push({ 1, start_node });
				while (!queue.empty()) {
					auto node = queue.top();
					queue.pop();
					if (vertexes[node.second] >= node.first)
						continue;
					vertexes[node.second] = node.first;
					for (const auto& neighbor : adjacency_list[node.second])
						if (vertexes[neighbor.second] < neighbor.first * node.first)
							queue.push({ neighbor.first * node.first , neighbor.second });
				}
				return vertexes[end_node];
			}
		};
	}

	namespace task_1518 {
		/*
		* https://leetcode.com/problems/water-bottles/description/
		*/
		class Solution {
		public:
			int numWaterBottles(int numBottles, int numExchange) {
				int empty = 0, res = 0;
				while (numBottles + empty >= numExchange) {
					res += numBottles;
					empty += numBottles;
					numBottles = empty / numExchange;
					empty %= numExchange;
				}
				return res + numBottles;
			}
		};
	}

	namespace task_1524 {
		/*
		* https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description/
		*/
		class Solution {
		public:
			int numOfSubarrays(vector<int>& arr) {
				int mod = 1000000007, count = 0, prev_count = 0, prev_prev_count = 0, sum = 0;
				int last_odd_i = -1, size = arr.size();
				for (int i = 0; i < size; ++i) {
					if ((arr[i] & 1) == 1) {
						count = (i - last_odd_i) + prev_prev_count;
						sum = (sum + count) % mod;
						last_odd_i = i;
						prev_prev_count = prev_count;
						prev_count = count;
					}
					else {
						sum = (sum + prev_count) % mod;
					}
				}
				return sum;
			}
		};
	}

	namespace task_1530
	{
		/*
		* https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/description/
		*/
		class Solution {
		public:

			int countPairsDFS(TreeNode* root, int distance) {
				vector<TreeNode*> leafs;
				queue<TreeNode*> queue;
				int count = 0, dist;
				queue.push(root);
				while (queue.empty()) {
					TreeNode* node = queue.front();
					queue.pop();
					if (node->left)
						queue.push(node->left);
					if (node->right)
						queue.push(node->right);
					else if (!node->left)
						leafs.push_back(node);
				}

				for (TreeNode* leaf : leafs) {
					dist = 0;
					while (queue.empty() && dist < distance) {
						TreeNode* node = queue.front();
						queue.pop();
						if (node->left)
							queue.push(node->left);
						if (node->right)
							queue.push(node->right);
						else if (!node->left)
							++count;
					}
				}

				return count >> 1;
			}

			int max_dist;
			int count;

			int countPairs(TreeNode* root, int distance) {
				count = 0;
				max_dist = distance;
				getLeafsdistance(root);
				return count;
			}

			vector<int> getLeafsdistance(TreeNode* root) {
				if (root->left && root->right) {
					auto left = getLeafsdistance(root->left);
					auto right = getLeafsdistance(root->right);
					if (!left.empty() && !right.empty())
						return merge(left, right);
					else if (!left.empty()) {
						plusDist(left);
						return left;
					}
					else if (!right.empty()) {
						plusDist(right);
						return right;
					}
					else
						return {};
				}
				else if (root->left) {
					auto leafs = getLeafsdistance(root->left);
					plusDist(leafs);
					return leafs;
				}
				else if (root->right) {
					auto leafs = getLeafsdistance(root->right);
					plusDist(leafs);
					return leafs;
				}
				return { 1 };
			}

			void plusDist(vector<int>& vec) {
				for (int& dist : vec)
					++dist;
			}

			vector<int> merge(const vector<int>& left, const vector<int>& right) {
				int left_i = 0, right_i = right.size() - 1;
				for (; left_i < left.size() && right_i >= 0; ++left_i) {
					for (; right_i >= 0 && left[left_i] + right[right_i] > max_dist; --right_i) {}
					count += right_i + 1;
				}
				vector<int> merged;
				left_i = 0, right_i = 0;
				while (left_i < left.size() && right_i < right.size()) {
					if (left[left_i] < right[right_i]) {
						merged.push_back(left[left_i] + 1);
						++left_i;
					}
					else {
						merged.push_back(right[right_i] + 1);
						++right_i;
					}
				}
				for (; left_i < left.size(); ++left_i)
					merged.push_back(left[left_i] + 1);
				for (; right_i < right.size(); ++right_i)
					merged.push_back(right[right_i] + 1);
				while (!merged.empty() && merged.back() + 1 > max_dist)
					merged.pop_back();
				return merged;
			}
		};
	}

	namespace task_1534 {
		/*
		* https://leetcode.com/problems/count-good-triplets/description/
		*/
		class Solution {
		public:
			int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
				size_t size = arr.size();
				int count = 0;
				for (size_t i = 0; i < size; ++i) {
					for (size_t j = i + 1; j < size; ++j) {
						if (abs(arr[i] - arr[j]) <= a) {
							for (size_t k = j + 1; k < size; ++k) {
								if (abs(arr[i] - arr[k]) <= b && abs(arr[k] - arr[j]) <= c)
									++count;
							}
						}
					}
				}
				return count;
			}
		};
	}

	namespace task_1539 {
		/*
		* https://leetcode.com/problems/kth-missing-positive-number/description/
		*/
		class Solution {
		public:
			int findKthPositive(vector<int>& arr, int k) {
				size_t l = 0;
				size_t r = arr.size() - 1;

				if (arr[l] > k)
					return k;
				if (arr[r] - r - 1 < k)
					return k + r + 1;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					size_t count_missed = arr[i] - i - 1;
					if (count_missed >= k)
						r = i;
					else
						l = i;
				}
				return k + r;
			}
		};
	}

	namespace task_1545 {
		/*
		* https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/description/
		*/
		class Solution {
		public:
			char findKthBit(int n, int k) {
				int degree = 1, _xor = 0;
				char c = 0;
				while (degree < k) { degree <<= 1; }
				while (k != 1) {
					while (degree > k) { degree >>= 1; }
					if (degree == k)
						return '0' + (c ^ (char)1);
					c ^= (char)1;
					k = (degree << 1) - k;
				}
				return '0' + c;
			}

			char findKthBit_leetcode(int n, int k) {
				// Find the position of the rightmost set bit in k
				// This helps determine which "section" of the string we're in
				int positionInSection = k & -k;

				// Determine if k is in the inverted part of the string
				// This checks if the bit to the left of the rightmost set bit is 1
				bool isInInvertedPart = ((k / positionInSection) >> 1 & 1) == 1;

				// Determine if the original bit (before any inversion) would be 1
				// This is true if k is even (i.e., its least significant bit is 0)
				bool originalBitIsOne = (k & 1) == 0;

				if (isInInvertedPart) {
					// If we're in the inverted part, we need to flip the bit
					return originalBitIsOne ? '0' : '1';
				}
				else {
					// If we're not in the inverted part, return the original bit
					return originalBitIsOne ? '1' : '0';
				}
			}

			char findKthBit_leetcode_compact(int n, int k) {
				return (((k / (k & -k)) >> 1 & 1) == 1) ?
					(k & 1) == 0 ? '0' : '1' :
					(k & 1) == 0 ? '1' : '0';
			}
		};
	}

	namespace task_1550 {
		/*
		* https://leetcode.com/problems/three-consecutive-odds/description/
		*/
		class Solution {
		public:
			bool threeConsecutiveOdds(vector<int>& arr) {
				for (size_t i = 2; i < arr.size(); i++)
					if (arr[i] & 1 && arr[i - 1] & 1 && arr[i - 2] & 1)
						return true;
				return false;
			}
		};
	}

	namespace task_1552 {
		/*
		* https://leetcode.com/problems/magnetic-force-between-two-balls/description/
		*/
		class Solution {
		public:
			size_t size;
			int count_balls;

			int maxDistance(vector<int>& position, int m) {
				size = position.size();
				count_balls = m;
				sort(position.begin(), position.end());
				int min_pos = position[0], max_pos = position.back();
				size_t l = 1, r = 1 + (max_pos - min_pos) / (m - 1);

				while (r - l > 1) {
					size_t i = (r + l) >> 1;
					if (check(position, i))
						l = i;
					else
						r = i;
				}
				return l;
			}

			bool check(const vector<int>& position, const int min_dist) {
				int last_pos = position[0], balls = 1;

				for (size_t i = 1; i < size && balls < count_balls; ++i)
					if (position[i] - last_pos >= min_dist) {
						++balls;
						last_pos = position[i];
					}
				return balls == count_balls;
			}
		};
	}

	namespace task_1568 {
		/*
		* https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/description/
		*/
		class Solution {
		public:
			int minDays(vector<vector<int>>& grid) {
				size_t m = grid.size(), n = grid[0].size(), count_lands = 0, size_first = 0;
				int min_degree = 4;
				for (size_t i = 0; i < m; ++i)
					for (size_t j = 0; j < n; ++j)
						if (grid[i][j]) {
							if (size_first == 0)
								size_first = sizeOfLand(grid, i, j, m, n);
							++count_lands;
							min_degree = min(min_degree,
								(i > 0 ? grid[i - 1][j] : 0) +
								(i + 1 < m ? grid[i + 1][j] : 0) +
								(j > 0 ? grid[i][j - 1] : 0) +
								(j + 1 < n ? grid[i][j + 1] : 0));
						}
				if (size_first != count_lands)
					return 0;
				if (count_lands < 3)
					return count_lands;
				if (min_degree == 1)
					return min_degree;

				for (size_t i = 0; i < m; ++i)
					for (size_t j = 0; j < n; ++j)
						if (grid[i][j]) {
							grid[i][j] = 0;
							size_t land_size = (i > 0 && grid[i - 1][j]) ?
								sizeOfLand(grid, i - 1, j, m, n) :
								(i + 1 < m && grid[i + 1][j]) ?
								sizeOfLand(grid, i + 1, j, m, n) :
								(j > 0 && grid[i][j - 1]) ?
								sizeOfLand(grid, i, j + 1, m, n) :
								sizeOfLand(grid, i, j - 1, m, n);
							if (land_size + 1 < count_lands)
								return 1;
							grid[i][j] = 1;
						}
				return 2;
			}

			size_t sizeOfLand(vector<vector<int>>& grid, size_t i, size_t j, size_t m, size_t n) {
				vector<pair<size_t, size_t>> retrun_back;
				queue<pair<size_t, size_t>> queue;
				grid[i][j] = 0;
				queue.push({ i, j });
				while (!queue.empty()) {
					auto pos = queue.front();
					queue.pop();
					if (pos.first + 1 != m && grid[pos.first + 1][pos.second]) {
						grid[pos.first + 1][pos.second] = 0;
						queue.push({ pos.first + 1, pos.second });
					}
					if (pos.second + 1 != n && grid[pos.first][pos.second + 1]) {
						grid[pos.first][pos.second + 1] = 0;
						queue.push({ pos.first, pos.second + 1 });
					}
					if (pos.first > 0 && grid[pos.first - 1][pos.second]) {
						grid[pos.first - 1][pos.second] = 0;
						queue.push({ pos.first - 1, pos.second });
					}
					if (pos.second > 0 && grid[pos.first][pos.second - 1]) {
						grid[pos.first][pos.second - 1] = 0;
						queue.push({ pos.first, pos.second - 1 });
					}
					retrun_back.push_back(pos);
				}
				for (const auto& pos : retrun_back)
					grid[pos.first][pos.second] = 1;
				return retrun_back.size();
			}
		};
	}

	namespace task_1574 {
		/*
		* https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/description/
		*/
		class Solution {
		public:
			int findLengthOfShortestSubarray_leetcode(vector<int>& arr) {
				int right = arr.size() - 1;
				for (; right > 0 && arr[right] >= arr[right - 1]; --right) {}

				int ans = right, left = 0;
				for (; left < right && (left == 0 || arr[left - 1] <= arr[left]); ++left) {
					for (; right < arr.size() && arr[left] > arr[right]; ++right) {}
					ans = min(ans, right - left - 1);
				}
				return ans;
			}

			int findLengthOfShortestSubarray(vector<int>& arr) {
				size_t size = arr.size();
				vector<char> is_right_subarray(size); // 1 from start, 2 from end, 3 both
				is_right_subarray[0] = 1;
				is_right_subarray[size - 1] += 2;
				for (size_t i = 1; i < size && arr[i] >= arr[i - 1]; ++i)
					is_right_subarray[i] += 1;
				for (int i = size - 2; i > -1 && arr[i] <= arr[i + 1]; --i)
					is_right_subarray[i] += 2;

				if (is_right_subarray[0] == 3)
					return 0;

				size_t l = 0, r = size - 1;
				while (r - l > 1) {
					int i = (r + l) / 2;
					if (isSorted(size, i, arr, is_right_subarray))
						r = i;
					else
						l = i;
				}
				return r;
			}

			bool isSorted(const size_t size, const size_t remove,
				const vector<int>& arr,
				const vector<char>& is_right_subarray) {
				if (is_right_subarray[remove] & (char)2)
					return true;
				if (is_right_subarray[size - remove - 1] & (char)1)
					return true;
				for (size_t i = 0; i < size - remove - 1; ++i)
					if (is_right_subarray[i] & (char)1 &&
						is_right_subarray[i + remove + 1] & (char)2 &&
						arr[i] <= arr[i + remove + 1])
						return true;
				return false;
			}
		};
	}

	namespace task_1579 {
		/*
		* https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/description/
		*/
		class Solution {
		public:
			vector<vector<size_t>> union_vertexes;
			int count, union_count;

			int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
				union_vertexes = vector<vector<size_t>>(2, vector<size_t>(n));
				for (size_t i = 0; i < n; ++i)
					union_vertexes[0][i] = i;
				count = 0;
				union_count = n;
				for (vector<int>& edge : edges) {
					--edge[1];
					--edge[2];
					if (edge[0] == 3)
						join_union(union_vertexes[0], min(edge[1], edge[2]), max(edge[1], edge[2]));
				}
				union_vertexes[1] = union_vertexes[0];
				union_count <<= 1;
				for (const vector<int>& edge : edges) {
					switch (edge[0]) {
					case 1: {
						join_union(union_vertexes[0], min(edge[1], edge[2]), max(edge[1], edge[2]));
						break;
					}
					case 2: {
						join_union(union_vertexes[1], min(edge[1], edge[2]), max(edge[1], edge[2]));
						break;
					}
					}
				}

				return union_count == 2 ? count : -1;
			}

			void join_union(vector<size_t>& vertexes, const size_t a, const size_t b) { // a < b
				size_t union_a = vertexes[a], union_b = vertexes[b];
				while (union_a != vertexes[union_a])
					union_a = vertexes[union_a];
				while (union_b != vertexes[union_b])
					union_b = vertexes[union_b];

				vertexes[a] = union_a;
				vertexes[b] = union_a;
				if (union_a == union_b) {
					++count;
					return;
				}
				--union_count;
				vertexes[union_b] = union_a;
			}
		};
	}

	namespace task_1590 {
		/*
		* https://leetcode.com/problems/problems/make-sum-divisible-by-p/description/
		*/
		class Solution {
		public:
			int minSubarray(vector<int>& nums, int p) {
				int size = nums.size(), totalSum = 0;

				for (int num : nums)
					totalSum = (totalSum + num) % p;

				int target = totalSum % p;
				if (target == 0) return 0;  // The array is already divisible by p

				// Step 2: Use a hash map to track prefix sum mod p
				unordered_map<int, int> modMap;
				modMap[0] =
					-1;  // To handle the case where the whole prefix is the answer
				int currentSum = 0, minLen = size;

				// Step 3: Iterate over the array
				for (int i = 0; i < size; ++i) {
					currentSum = (currentSum + nums[i]) % p;

					// Calculate what we need to remove
					int needed = (currentSum - target + p) % p;

					// If we have seen the needed remainder, we can consider this
					// subarray
					if (modMap.find(needed) != modMap.end())
						minLen = min(minLen, i - modMap[needed]);

					// Store the current remainder and index
					modMap[currentSum] = i;
				}

				return minLen == size ? -1 : minLen;
			}
		};
	}

	namespace task_1593 {
		/*
		* https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/description
		*/
		class Solution {
		public:
			size_t size, max_sub;

			int maxUniqueSplit(string s) {
				size = s.size();
				max_sub = 1;
				unordered_set<string> set;
				maxUniqueSplit(s, 0, set);
				return max_sub;
			}

			void maxUniqueSplit(const string& s, const size_t from, unordered_set<string>& set) {
				if (set.size() + size - from <= max_sub)
					return; // if we can not build more than max_sub with this splitting
				if (from == size) {
					max_sub = max(max_sub, set.size());
					return;
				}
				int count = 0;
				for (size_t i = from + 1; i <= size; ++i) {
					string sub = s.substr(from, i - from);
					if (!set.contains(sub)) {
						set.insert(sub);
						maxUniqueSplit(s, i, set);
						set.erase(sub);
					}
				}
			}
		};
	}

	namespace task_1598 {
		/*
		* https://leetcode.com/problems/crawler-log-folder/description/
		*/
		class Solution {
		public:
			int minOperations(vector<string>& logs) {
				int level = 0;
				for (const string& str : logs) {
					if (str[0] == '.') {
						if (str[1] == '.')
							level = max(0, level - 1);
					}
					else
						++level;
				}
				return level;
			}
		};
	}

	namespace task_1605
	{
		/*
		* https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/description/
		*/
		class Solution {
		public:
			vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
				size_t const rows = rowSum.size(), cols = colSum.size();
				vector<vector<int>> mat(rows, vector<int>(cols));
				for (size_t i = 0; i < rows; i++)
					for (size_t j = 0; j < cols; j++) {
						int min_sum = min(rowSum[i], colSum[j]);
						rowSum[i] -= min_sum;
						colSum[j] -= min_sum;
						mat[i][j] = min_sum;
					}
				return mat;
			}
		};
	}

	namespace task_1608 {
		/*
		* https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/description/
		*/
		class Solution {
		public:
			int specialArray(vector<int>& nums) {
				sort(nums.begin(), nums.end());
				int size = nums.size();
				for (int i = 0; i < size; i++) {
					int x = size - i;
					if (x <= nums[i] && (i == 0 || x > nums[i - 1]))
						return x;
				}
				return -1;
			}
		};
	}

	namespace task_1609 {
		/*
		* https://leetcode.com/problems/even-odd-tree/description/
		*/
		class Solution {
		public:
			bool isEvenOddTree(TreeNode* root) {
				int last_level = 0;
				int value = root->val;
				TreeNode* node = nullptr;
				queue<TreeNode*> odd;
				queue<TreeNode*> even;
				odd.push(root);
				while (!odd.empty()) {
					value = INT32_MIN;
					while (!odd.empty()) {
						node = odd.front();
						odd.pop();
						if (!(node->val % 2) || value >= node->val)
							return false;
						value = node->val;
						if (node->left)
							even.push(node->left);
						if (node->right)
							even.push(node->right);
					}

					if (even.empty())
						break;
					value = INT32_MAX;
					while (!even.empty()) {
						node = even.front();
						even.pop();
						if (node->val % 2 || value <= node->val)
							return false;
						value = node->val;
						if (node->left)
							odd.push(node->left);
						if (node->right)
							odd.push(node->right);
					}
				}
				return true;
			}
		};
	}

	namespace task_1631 {
		/*
		* https://leetcode.com/problems/path-with-minimum-effort/
		*/
		class Solution {
		public:
			struct my_comparator
			{
				bool operator()(std::vector<int> const& a, std::vector<int> const& b) const {
					return a[0] > b[0];
				}
			};

			int minimumEffortPath(vector<vector<int>>& heights) {
				size_t length = heights.size();
				size_t width = heights[0].size();
				vector<vector<int>> efforts(length, vector<int>(width, 100000));
				priority_queue<vector<int>, vector<vector<int>>, my_comparator> queue;
				queue.push(vector<int>({ 0, 0, 0 }));
				int i, j, effort, next_effort;

				while (!queue.empty()) {
					auto point = queue.top();
					queue.pop();
					i = point[0];
					j = point[1];
					effort = point[2];
					if (efforts[i][j] < effort)
						continue;
					efforts[i][j] = effort;
					if (i + 1 < length) {
						next_effort = max(abs(heights[i][j] - heights[i + 1][j]), effort);
						if (next_effort < efforts[i + 1][j])
							queue.push(vector<int>({ i + 1, j, next_effort }));
					}
					if (j + 1 < width) {
						next_effort = max(abs(heights[i][j] - heights[i][j + 1]), effort);
						if (next_effort < efforts[i][j + 1])
							queue.push(vector<int>({ i, j + 1, next_effort }));
					}
					if (i - 1 > -1) {
						next_effort = max(abs(heights[i][j] - heights[i - 1][j]), effort);
						if (next_effort < efforts[i - 1][j])
							queue.push(vector<int>({ i - 1, j, next_effort }));
					}
					if (j - 1 > -1) {
						next_effort = max(abs(heights[i][j - 1] - heights[i][j - 1]), effort);
						if (next_effort < efforts[i][j - 1])
							queue.push(vector<int>({ i, j - 1, next_effort }));
					}
				}
				return efforts[length - 1][width - 1];
			}

			vector<vector<int>> queue;

			int minimumEffortPath2(vector<vector<int>>& heights) {
				size_t length = heights.size();
				size_t width = heights[0].size();
				if (length == 1 && width == 1)
					return 0;
				queue = vector<vector<int>>(length * width, vector<int>(3));
				int effort_max = 999999;
				int effort_min = -1;
				int effort;

				while (effort_min + 1 != effort_max) {
					effort = (effort_max + effort_min) >> 1;
					if (dfsSearch(heights, effort, length, width))
						effort_max = effort;
					else
						effort_min = effort;
				}
				return effort_max;
			}

			bool dfsSearch(vector<vector<int>>& grid, const int effort, const size_t length, const size_t width) {
				int queue_end = 1;
				int queue_top = 0;
				int i, j, height;
				bool res = false;
				queue[0][0] = 0;
				queue[0][1] = 0;
				queue[0][2] = grid[0][0];
				grid[0][0] = 10000000;
				while (queue_top != queue_end) {
					i = queue[queue_top][0];
					j = queue[queue_top][1];
					height = queue[queue_top][2];
					++queue_top;
					if (i + 1 < length && abs(height - grid[i + 1][j]) <= effort) {
						if (i + 1 == length - 1 && j == width - 1) {
							res = true;
							break;
						}
						queue[queue_end][0] = i + 1;
						queue[queue_end][1] = j;
						queue[queue_end][2] = grid[i + 1][j];
						grid[i + 1][j] = 10000000;
						++queue_end;
					}
					if (j + 1 < width && abs(height - grid[i][j + 1]) <= effort) {
						if (i == length - 1 && j + 1 == width - 1) {
							res = true;
							break;
						}
						queue[queue_end][0] = i;
						queue[queue_end][1] = j + 1;
						queue[queue_end][2] = grid[i][j + 1];
						grid[i][j + 1] = 10000000;
						++queue_end;
					}
					if (i - 1 > -1 && abs(height - grid[i - 1][j]) <= effort) {
						queue[queue_end][0] = i - 1;
						queue[queue_end][1] = j;
						queue[queue_end][2] = grid[i - 1][j];
						grid[i - 1][j] = 10000000;
						++queue_end;
					}
					if (j - 1 > -1 && abs(height - grid[i][j - 1]) <= effort) {
						queue[queue_end][0] = i;
						queue[queue_end][1] = j - 1;
						queue[queue_end][2] = grid[i][j - 1];
						grid[i][j - 1] = 10000000;
						++queue_end;
					}
				}
				for (size_t i = 0; i < queue_end; i++)
					grid[queue[i][0]][queue[i][1]] = queue[i][2];
				return res;
			}
		};
	}

	namespace task_1636 {
		/*
		* https://leetcode.com/problems/sort-the-people/description/
		*/
		class Solution {
		public:
			vector<int> frequencySort(vector<int>& nums) {
				vector<int> freq(201);
				for (const int num : nums)
					++freq[num + 100];
				sort(nums.begin(), nums.end(), [&](const int a, const int b) {
					if (freq[a + 100] == freq[b + 100])
						return a > b;
					return freq[a + 100] < freq[b + 100];
					});
				return nums;
			}
		};
	}

	namespace task_1639 {
		/*
		* https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/description/
		*/
		class Solution {
		public:
			int numWays(vector<string>& words, string target) {
				int wordLength = words[0].size();
				int targetLength = target.size();
				const int MOD = 1000000007;

				// Step 1: Calculate frequency of each character at every index in
				// "words".
				vector<vector<int>> charFrequency(wordLength, vector<int>(26, 0));
				for (const string& word : words) {
					for (int j = 0; j < wordLength; ++j) {
						charFrequency[j][word[j] - 'a']++;
					}
				}

				// Step 2: Initialize two DP arrays: prev and curr.
				vector<long> prevCount(targetLength + 1, 0);
				vector<long> currCount(targetLength + 1, 0);

				// Base case: There is one way to form an empty target string.
				prevCount[0] = 1;

				// Step 3: Fill the DP arrays.
				for (int currWord = 1; currWord <= wordLength; ++currWord) {
					// Copy the previous row into the current row for DP.
					currCount = prevCount;
					for (int currTarget = 1; currTarget <= targetLength; ++currTarget) {
						// If characters match, add the number of ways.
						int curPos = target[currTarget - 1] - 'a';
						currCount[currTarget] += (charFrequency[currWord - 1][curPos] *
							prevCount[currTarget - 1]) %
							MOD;
						currCount[currTarget] %= MOD;
					}
					// Move current row to previous row for the next iteration.
					prevCount = currCount;
				}

				// Step 4: The result is in prev[targetLength].
				return currCount[targetLength];
			}
		};
	}

	namespace task_1652 {
		/*
		* https://leetcode.com/problems/defuse-the-bomb/description/
		*/
		class Solution {
		public:
			vector<int> decrypt(vector<int>& code, int k) {
				int size = code.size();
				if (k == 0) {
					for (int i = 0; i < size; ++i)
						code[i] = 0;
					return code;
				}
				vector<int>decode(size);
				int dir = k > 0 ? 1 : -1, from = k > 0 ? 1 : size - 1, sum = 0, pos = dir;
				for (; pos != k; pos += dir)
					sum += code[(pos + size) % size];
				sum += code[(pos + size) % size];
				decode[0] = sum;
				for (int i = 1; i < size; ++i) {
					pos = (pos + dir + size) % size;
					sum += code[pos] - code[from];
					decode[from] = sum;
					from += dir;
				}

				return decode;
			}
		};
	}

	namespace task_1653 {
		/*
		* https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/description/
		*/
		class Solution {
		public:
			int minimumDeletions(string s) {
				int count_a = 0, count_b = 0;
				for (const char c : s)
					if (c == 'a')
						++count_a;
				int min_delete = count_a;
				for (const char c : s)
					if (c == 'a')
						--count_a;
					else {
						min_delete = min(min_delete, count_a + count_b);
						++count_b;
					}
				return min(min_delete, count_b);
			}
		};
	}

	namespace task_1671 {
		/*
		* https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/description/
		*/
		class Solution { // 90.91% 39.13%
		public:
			size_t size;
			vector<int> LIS;
			vector<int> LDS;
			vector<int> ends_of_LIS;

			int minimumMountainRemovals(vector<int>& nums) {
				size = nums.size();
				ends_of_LIS = vector<int>(size);

				calculateLIS(nums);
				calculateLDS(nums);

				int max_len = 3;
				for (size_t i = 1; i < size; i++) {
					int left = LIS[i];
					int right = LDS[i];
					if (left != 0 && right != 0)
						max_len = max(max_len, 1 + left + right);
				}
				return size - max_len;
			}

			void calculateLIS(vector<int>& nums) {
				size_t length = 0;
				LIS = vector<int>(size);
				for (size_t i = 0; i < size; ++i)
					ends_of_LIS[i] = INT_MAX;

				for (size_t i = 0; i < size; ++i) {
					size_t j = search(ends_of_LIS, length, nums[i]);
					LIS[i] = j;
					ends_of_LIS[j] = min(ends_of_LIS[j], nums[i]);
					length = max(j + 1, length);
				}
			}

			void calculateLDS(vector<int>& nums) {
				size_t length = 0;
				LDS = vector<int>(size);
				for (size_t i = 0; i < size; ++i)
					ends_of_LIS[i] = INT_MAX;

				for (size_t i = size - 1; i > 0; --i) {
					size_t j = search(ends_of_LIS, length, nums[i]);
					LDS[i] = j;
					ends_of_LIS[j] = min(ends_of_LIS[j], nums[i]);
					length = max(j + 1, length);
				}
			}

			size_t search(vector<int>& nums, size_t r, const int target) {
				size_t l = 0;
				if (nums[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};

		class Solution_slow {// 6.06% 94.12%
		public:
			size_t size;
			vector<int> ends_of_LIS;

			int minimumMountainRemovals(vector<int>& nums) {
				size = nums.size();
				ends_of_LIS = vector<int>(size);

				int max_len = 3;
				for (size_t i = 0; i < size; i++) {
					int left = lengthOfLIS(nums, 0, i, nums[i]);
					int right = lengthOfLIS(nums, size - 1, i, nums[i]);
					if (left != 0 && right != 0)
						max_len = max(max_len, 1 + left + right);
				}
				return size - max_len;
			}

			int lengthOfLIS(vector<int>& nums, const int from, const int to, const int top) {

				int dir = to > from ? 1 : -1;
				size_t length = 0, max_length = (to - from) * dir;
				for (size_t i = 0; i < max_length; ++i)
					ends_of_LIS[i] = INT_MAX;

				for (int i = from; i != to; i += dir) {
					if (nums[i] >= top)
						continue;
					size_t j = search(ends_of_LIS, length, nums[i]);
					ends_of_LIS[j] = min(ends_of_LIS[j], nums[i]);
					length = max(j + 1, length);
				}

				return length;
			}

			size_t search(vector<int>& nums, size_t r, const int target) {
				size_t l = 0;
				if (nums[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_1684 {
		/*
		* https://leetcode.com/path-sum/count-the-number-of-consistent-strings/description/
		*/
		class Solution {
		public:
			int countConsistentStrings(string allowed, vector<string>& words) {
				vector<int> allowed_hash('z' - 'a' + 1);
				int count = 0;
				for (const char c : allowed)
					allowed_hash[c - 'a'] = 1;
				for (const string& word : words) {
					bool isConsistent = true;
					for (const char c : word)
						if (allowed_hash[c - 'a'] == 0) {
							isConsistent = false;
							break;
						}
					if (isConsistent)
						++count;
				}
				return count;
			}
		};
	}

	namespace task_1701 {
		/*
		* https://leetcode.com/problems/average-waiting-time/description/
		*/
		class Solution {
		public:
			double averageWaitingTime(vector<vector<int>>& customers) {
				double wait_time = customers[0][1];
				int curr_time = customers[0][0] + customers[0][1];
				size_t size = customers.size();
				for (size_t i = 1; i < size; ++i)
					if (curr_time > customers[i][0]) {
						curr_time += customers[i][1];
						wait_time += curr_time - customers[i][0];
					}
					else {
						curr_time = customers[i][0] + customers[i][1];
						wait_time += customers[i][1];
					}
				return wait_time / size;
			}
		};
	}

	namespace task_1713 {
		/*
		* https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/description/
		*/
		class Solution {
		public:
			int minOperations(vector<int>& target, vector<int>& arr) {
				map<int, int> target_index_map;
				const size_t size_target = target.size();
				const size_t size_arr = arr.size();

				for (size_t i = 0; i < size_target; ++i)
					target_index_map[target[i]] = i;

				for (size_t i = 0; i < size_arr; ++i)
					if (auto it = target_index_map.find(arr[i]); it != target_index_map.end())
						arr[i] = it->second;
					else
						arr[i] = -1;
				return size_target - lengthOfLIS(arr);
			}

			size_t lengthOfLIS(const vector<int>& nums) {
				const size_t size = nums.size();
				size_t length = 0;
				vector<int> ends_of_LIS(size, INT_MAX);

				for (size_t i = 0; i < size; i++) {
					if (nums[i] == -1)
						continue;
					size_t j = search(ends_of_LIS, length, nums[i]);
					ends_of_LIS[j] = min(ends_of_LIS[j], nums[i]);
					length = max(j + 1, length);
				}

				return length;
			}

			size_t search(const vector<int>& nums, size_t r, const int target) {
				size_t l = 0;
				if (nums[l] >= target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_1717 {
		/*
		* https://leetcode.com/problems/maximum-score-from-removing-substrings/description/
		*/
		class Solution {
		public:
			int maximumGain(string s, int x, int y) {
				const size_t size = s.size();
				char first_profit_char, second_profit_char;
				int count_first, count_second, count_max;
				if (x > y) {
					first_profit_char = 'a';
					second_profit_char = 'b';
				}
				else {
					first_profit_char = 'b';
					second_profit_char = 'a';
					swap(x, y);
				}
				int gain = 0;
				for (size_t i = 0; i < size; ++i)
					if (s[i] == 'a' || s[i] == 'b') {
						count_first = 0, count_second = 0, count_max = 0;
						for (; i < size && (s[i] == 'a' || s[i] == 'b'); ++i) {
							if (s[i] == first_profit_char)
								++count_first;
							else {
								if (count_first > count_max)
									++count_max;
								++count_second;
							}
						}
						gain += x * count_max + (min(count_first, count_second) - count_max) * y;
						--i;
					}
				return gain;
			}
		};
	}

	namespace task_1718 {
		/*
		* https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/description/
		*/
		class Solution {
		public:
			vector<int> constructDistancedSequence(int targetNumber) {
				vector<int> resultSequence(targetNumber * 2 - 1, 0);
				vector<bool> isNumberUsed(targetNumber + 1, false);

				findLexicographicallyLargestSequence(0, resultSequence, isNumberUsed, targetNumber);

				return resultSequence;
			}

			bool findLexicographicallyLargestSequence(int currentIndex,
				vector<int>& resultSequence,
				vector<bool>& isNumberUsed,
				int targetNumber) {
				if (currentIndex == resultSequence.size())
					return true;

				if (resultSequence[currentIndex] != 0)
					return findLexicographicallyLargestSequence(currentIndex + 1, resultSequence, isNumberUsed, targetNumber);


				for (int numberToPlace = targetNumber; numberToPlace >= 1;
					numberToPlace--) {
					if (isNumberUsed[numberToPlace]) continue;

					isNumberUsed[numberToPlace] = true;
					resultSequence[currentIndex] = numberToPlace;

					if (numberToPlace == 1) {
						if (findLexicographicallyLargestSequence(currentIndex + 1, resultSequence, isNumberUsed, targetNumber))
							return true;
					}

					else if (currentIndex + numberToPlace < resultSequence.size() &&
						resultSequence[currentIndex + numberToPlace] == 0) {
						resultSequence[currentIndex + numberToPlace] = numberToPlace;

						if (findLexicographicallyLargestSequence(currentIndex + 1, resultSequence, isNumberUsed, targetNumber))
							return true;
						resultSequence[currentIndex + numberToPlace] = 0;
					}

					resultSequence[currentIndex] = 0;
					isNumberUsed[numberToPlace] = false;
				}

				return false;
			}
		};
	}

	namespace task_1720 {
		/*
		* https://leetcode.com/problems/decode-xored-array/description/
		*/
		class Solution {
		public:
			vector<int> decode(vector<int>& encoded, int first) {
				size_t size = encoded.size();
				vector<int> decoded(size + 1);
				decoded[0] = first;
				for (size_t i = 0; i < size; i++)
					decoded[i + 1] = encoded[i] ^ decoded[i];
				return decoded;
			}
		};
	}

	namespace task_1721 {
		/*
		* https://leetcode.com/problems/swapping-nodes-in-a-linked-list/description/
		*/
		struct ListNode {
			int val;
			ListNode* next;
			ListNode() : val(0), next(nullptr) {}
			ListNode(int x) : val(x), next(nullptr) {}
			ListNode(int x, ListNode* next) : val(x), next(next) {}

		};

		class Solution {
		public:
			ListNode* swapNodes(ListNode* head, int k) {
				size_t size = 0;
				auto ptr_k = head;
				while (ptr_k)
				{
					++size;
					ptr_k = ptr_k->next;
				}
				int j = size + 1 - k;
				if (k == j)
					return head;
				if (k > j)
					swap(k, j);
				
				ptr_k = head;
				for (size_t i = 2; i < k; ++i)
					ptr_k = ptr_k->next;

				auto ptr_j = head;
				for (size_t i = 2; i < j; ++i)
					ptr_j = ptr_j->next;

				if (k == 1) {
					if (size == 2) {
						head = ptr_j->next;
						head->next = ptr_k;
						ptr_k->next = nullptr;
						return head;
					}
					head = ptr_j->next;
					head->next = ptr_k->next;
					ptr_k->next = nullptr;
					ptr_j->next = ptr_k;
					return head;
				}

				if (k + 1 == j) {
					ptr_k->next = ptr_j->next;
					ptr_j->next = ptr_k->next->next;
					ptr_k->next->next = ptr_j;
				}
				else {
					swap(ptr_k->next->next, ptr_j->next->next);
					swap(ptr_k->next, ptr_j->next);
				}
				return head;
			}
		};
	}

	namespace task_1726 {
		/*
		* https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/description/
		*/
		class Solution {
		public:
			int tupleSameProduct(vector<int>& nums) {
				const size_t size = nums.size() - 1;
				sort(nums.begin(), nums.end());
				int count = 0;
				for (size_t i = 0; i < size; ++i) {
					for (size_t j = i + 1; j < size; ++j) {
						for (size_t k = j + 1; k < size; ++k) {
							int left = nums[i], right = nums[j] * nums[k];
							if (right % left != 0)
								continue;
							right /= left;
							if (right < nums[k + 1] || right > nums[size])
								continue;
							size_t ind = bin_search(nums, right, k + 1, size + 1);
							if (ind != 0)
								count += 8;
						}
					}
				}
				return count;
			}

			size_t bin_search(const vector<int>& nums, const int value, size_t l, size_t r) {
				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] == value)
						return i;
					if (nums[i] > value)
						r = i;
					else
						l = i;
				}
				return nums[l] == value ? l : 0;
			}

			int tupleSameProduct__leetcode(vector<int>& nums) {
				size_t size = nums.size();
				unordered_map<int, int> pairProductsFrequency;
				int count = 0;

				for (size_t i = 0; i < size; ++i) {
					for (size_t j = i + 1; j < size; ++j)
						pairProductsFrequency[nums[i] * nums[j]]++;
				}

				for (const auto [product, frequency] : pairProductsFrequency)
					count += ((frequency - 1) * frequency) << 2; // 8 * (frequency - 1) * frequency / 2;

				return count;
			}
		};
	}

	namespace task_1749 {
		/*
		* https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/
		*/
		class Solution {
		public:
			int maxAbsoluteSum(vector<int>& nums) {
				size_t size = nums.size();
				int pos_sum = 0, neg_sum = 0, max_sum = 0;
				for (size_t i = 0; i < size; ++i) {
					pos_sum += nums[i];
					neg_sum -= nums[i];
					if (pos_sum < 0)
						pos_sum = 0;
					if (neg_sum < 0)
						neg_sum = 0;
					max_sum = max(max_sum, max(pos_sum, neg_sum));
				}
				return max_sum;
			}
		};
	}

	namespace task_1752 {
		/*
		* https://leetcode.com/problems/special-array-i/description/
		*/
		class Solution {
		public:
			bool check(vector<int>& nums) {
				const size_t size = nums.size();
				int count_less = nums[size - 1] > nums[0] ? 1 : 0;
				for (size_t i = 1; i < size; i++) {
					if (nums[i - 1] > nums[i])
						++count_less;
				}
				return count_less < 2;
			}
		};
	}

	namespace task_1760 {
		/*
		* https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/description
		*/
		class Solution {
		public:
			int minimumSize(vector<int>& nums, int maxOperations) {
				int l = 0, r = 1;
				for (int n : nums)
					r = max(r, n);
				while (r - l > 1) {
					int max_el = (r + l) / 2;
					int count = 0;

					for (int n : nums) {
						if (n > max_el)
							count += n / max_el - (n % max_el == 0 ? 1 : 0);
					}

					if (count <= maxOperations)
						r = max_el;
					else
						l = max_el;
				}
				return r;
			}
		};
	}

	namespace task_1765 {
		/*
		* https://leetcode.com/problems/map-of-highest-peak/description/
		*/
		class Solution {
		public:
			vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
				const int m = isWater.size(), n = isWater[0].size();
				queue<pair<int, int>> queue;
				for (int i = 0; i < m; ++i) {
					for (int j = 0; j < n; ++j) {
						--isWater[i][j];
						if (isWater[i][j] == 0)
							queue.push({ i, j });
					}
				}

				while (!queue.empty()) {
					int i = queue.front().first, j = queue.front().second;
					queue.pop();
					if (i > 0 && isWater[i - 1][j] == -1) {
						queue.push({ i - 1, j });
						isWater[i - 1][j] = isWater[i][j] + 1;
					}
					if (i + 1 < m && isWater[i + 1][j] == -1) {
						queue.push({ i + 1, j });
						isWater[i + 1][j] = isWater[i][j] + 1;
					}
					if (j > 0 && isWater[i][j - 1] == -1) {
						queue.push({ i, j - 1 });
						isWater[i][j - 1] = isWater[i][j] + 1;
					}
					if (j + 1 < n && isWater[i][j + 1] == -1) {
						queue.push({ i, j + 1 });
						isWater[i][j + 1] = isWater[i][j] + 1;
					}
				}

				return isWater;
			}
		};
	}

	namespace task_1769 {
		/*
		* https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/description/
		*/
		class Solution {
		public:
			vector<int> minOperations(string boxes) {
				int n = boxes.size();
				vector<int> answer(n, 0);

				int ballsToLeft = 0, movesToLeft = 0;
				int ballsToRight = 0, movesToRight = 0;

				// Single pass: calculate moves from both left and right
				for (int i = 0; i < n; i++) {
					// Left pass
					answer[i] += movesToLeft;
					ballsToLeft += boxes[i] - '0';
					movesToLeft += ballsToLeft;

					// Right pass
					int j = n - 1 - i;
					answer[j] += movesToRight;
					ballsToRight += boxes[j] - '0';
					movesToRight += ballsToRight;
				}

				return answer;
			}
		};
	}

	namespace task_1780 {
		/*
		* https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/description/
		*/
		class Solution {
		public:
			bool checkPowersOfThree(int n) {
				int degree = 1;
				while (degree * 3 <= n)
					degree *= 3;
				while (degree != 0) {
					n -= degree;
					degree /= 3;
					while (degree > n)
						degree /= 3;
				}
				return n == 0;
			}
		};
	}

	namespace task_1790 {
		/*
		* https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/description/
		*/
		class Solution {
		public:
			bool areAlmostEqual(string s1, string s2) {
				size_t size = s1.size(), i1 = size, i2 = size;
				for (size_t i = 0; i < size; i++) {
					if (s1[i] != s2[i]) {
						if (i1 == size)
							i1 = i;
						else if (i2 == size)
							i2 = i;
						else
							return false;
					}
				}
				if (i1 == i2)
					return true;
				if (i2 == size)
					return false;
				return s1[i1] == s2[i2] && s1[i2] == s2[i1];
			}
		};
	}

	namespace task_1791 {
		/*
		* https://leetcode.com/problems/find-center-of-star-graph/description/
		*/
		class Solution {
		public:
			int findCenter(vector<vector<int>>& edges) {
				return edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1] ? edges[0][0] : edges[0][1];
			}
		};
	}

	namespace task_1792 {
		/*
		* https://leetcode.com/problems/maximum-average-pass-ratio/description
		*/
		class Solution {
		public:
			double maxAverageRatio__leetcode(vector<vector<int>>& classes, int extraStudents) {
				// Lambda to calculate the gain of adding an extra student
				auto calculateGain = [](int passes, int totalStudents) {
					return (double)(passes + 1) / (totalStudents + 1) -
						(double)passes / totalStudents;
				};

				// Max heap to store (-gain, passes, totalStudents)
				priority_queue<pair<double, pair<int, int>>> maxHeap;
				for (const auto& singleClass : classes) {
					maxHeap.push({ calculateGain(singleClass[0], singleClass[1]),
								  {singleClass[0], singleClass[1]} });
				}

				// Distribute extra students
				while (extraStudents--) {
					auto [currentGain, classInfo] = maxHeap.top();
					maxHeap.pop();
					int passes = classInfo.first;
					int totalStudents = classInfo.second;
					maxHeap.push({ calculateGain(passes + 1, totalStudents + 1),
								  {passes + 1, totalStudents + 1} });
				}

				// Calculate the final average pass ratio
				double totalPassRatio = 0;
				while (!maxHeap.empty()) {
					auto [_, classInfo] = maxHeap.top();
					maxHeap.pop();
					totalPassRatio += (double)classInfo.first / classInfo.second;
				}

				return totalPassRatio / classes.size();
			}
		};
	}

	namespace task_1798 {
		/*
		* https://leetcode.com/problems/problems/maximum-number-of-consecutive-values-you-can-make/
		*/
		class Solution {
		public:
			int getMaximumConsecutive(vector<int>& coins) {
				sort(coins.begin(), coins.end());
				size_t size = coins.size();
				int sum = 1;
				for (size_t i = 0; i < size; ++i)
					if (i < size && coins[i] <= sum)
						sum += coins[i];
					else
						return sum;
				return sum;
			}
		};
	}

	namespace task_1800 {
		/*
		* https://leetcode.com/problems/maximum-ascending-subarray-sum/description/
		*/
		class Solution {
		public:
			int maxAscendingSum(vector<int>& nums) {
				int max_sum = nums[0], sum = nums[0];
				const size_t size = nums.size();
				for (size_t i = 1; i < size; i++) {
					if (nums[i] - nums[i - 1] > 0) {
						sum += nums[i];
					}
					else {
						max_sum = max(max_sum, sum);
						sum = nums[i];
					}
				}
				return max(max_sum, sum);
			}
		};
	}

	namespace task_1813 {
		/*
		* https://leetcode.com/problems/problems/sentence-similarity-iii/description/
		*/
		class Solution {
		public:
			bool areSentencesSimilar(string sentence1, string sentence2) {
				size_t pos1 = 0, pos2 = 0, index;
				vector<string> words1, words2;

				int count = 0;
				while ((index = sentence1.find(' ', pos1)) != std::string::npos) {
					index = sentence1.find(' ', pos1);
					words1.push_back(sentence1.substr(pos1, index - pos1));
					pos1 = index + 1;
				}
				words1.push_back(sentence1.substr(pos1));

				while ((index = sentence2.find(' ', pos2)) != std::string::npos) {
					index = sentence2.find(' ', pos2);
					words2.push_back(sentence2.substr(pos2, index - pos2));
					pos2 = index + 1;
				}
				words2.push_back(sentence2.substr(pos2));

				size_t size1 = words1.size(), size2 = words2.size();
				pos1 = 0, pos2 = 0, index = 0;
				for (; index < size1 && index < size2 && words1[index] == words2[index]; ++index) {}
				if (index == size1 || index == size2)
					return true;

				if (size1 == size2)
					return false;

				if (size1 > size2) {
					pos1 = size1 - size2 + index;
					for (; index < size2 && words1[pos1] == words2[index]; ++index, ++pos1) {}
					return index == size2;
				}
				else {
					pos2 = size2 - size1 + index;
					for (; index < size1 && words1[index] == words2[pos2]; ++index, ++pos2) {}
					return index == size1;
				}
			}

			bool areSentencesSimilar2(string s1, string s2) {
				// Convert sentences to lists of words
				stringstream ss1(s1), ss2(s2);
				string word;
				vector<string> s1Words, s2Words;
				while (ss1 >> word) s1Words.push_back(word);
				while (ss2 >> word) s2Words.push_back(word);

				int start = 0, ends1 = s1Words.size() - 1, ends2 = s2Words.size() - 1;

				// If words in s1 are more than s2, swap them and return the answer.
				if (s1Words.size() > s2Words.size()) return areSentencesSimilar(s2, s1);

				// Find the maximum words matching from the beginning.
				while (start < s1Words.size() && s1Words[start] == s2Words[start])
					++start;

				// Find the maximum words matching in the end.
				while (ends1 >= 0 && s1Words[ends1] == s2Words[ends2]) {
					--ends1;
					--ends2;
				}

				// If ends1 index is less than start, then sentence is similar.
				return ends1 < start;
			}
		};
	}

	namespace task_1823 {
		/*
		* https://leetcode.com/problems/water-bottles-ii/
		*/
		class Solution {
		public:
			int findTheWinner(int n, int k) {
				list<int> l;
				--k;
				for (int i = 1; i <= n; ++i)
					l.push_back(i);
				int moves = k % l.size();
				auto it = l.begin();
				while (l.size() > 1) {
					for (int i = 0; i < moves; ++i) {
						if (it == l.end())
							it = l.begin();
						++it;
					}
					if (it == l.end())
						it = l.begin();
					it = l.erase(it);
					moves = k % l.size();
				}
				return l.front();
			}
		};
	}

	namespace task_1827 {
		/*
		* https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/description/
		*/
		class Solution {
		public:
			int minOperations(vector<int>& nums) {
				size_t size = nums.size();
				int count = 0;
				for (size_t i = 1; i < size; ++i)
					if (nums[i] <= nums[i - 1]) {
						int dif = nums[i - 1] + 1 - nums[i];
						count += dif;
						nums[i] += dif;;
					}
				return count;
			}
		};
	}

	namespace task_1829 {
		/*
		* https://leetcode.com/problems/maximum-xor-for-each-query/description/
		*/
		class Solution {
		public:
			vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
				size_t size = nums.size(), start = 0;
				vector<int> queries(size);
				int XOR = 0, mask = (1 << maximumBit) - 1;
				for (int n : nums)
					XOR ^= n;

				for (size_t i = 0; i < size; ++i) {
					queries[i] = XOR ^ mask;
					XOR ^= nums[size - i - 1];
				}
				return queries;
			}
		};
	}

	namespace task_1857 {
		/*
		* https://leetcode.com/problems/largest-color-value-in-a-directed-graph/description/
		*/
		class Solution {
		public:
			int largestPathValue__not__my(string colors, vector<vector<int>>& edges) {
				int n = colors.size();
				vector<vector<int>> adj(n);
				vector<int> indegree(n, 0);

				for (auto& edge : edges) {
					adj[edge[0]].push_back(edge[1]);
					indegree[edge[1]]++;
				}

				vector<vector<int>> dp(n, vector<int>(26, 0));
				queue<int> q;

				for (int i = 0; i < n; ++i) {
					if (indegree[i] == 0) q.push(i);
					dp[i][colors[i] - 'a'] = 1;
				}

				int visited = 0;
				int maxColor = 0;

				while (!q.empty()) {
					int node = q.front(); q.pop();
					visited++;

					for (int neighbor : adj[node]) {
						for (int c = 0; c < 26; ++c) {
							int inc = (colors[neighbor] - 'a' == c) ? 1 : 0;
							dp[neighbor][c] = max(dp[neighbor][c], dp[node][c] + inc);
						}

						indegree[neighbor]--;
						if (indegree[neighbor] == 0) q.push(neighbor);
					}

					maxColor = max(maxColor, *max_element(dp[node].begin(), dp[node].end()));
				}

				return visited == n ? maxColor : -1;
			}
		};
	}

	namespace task_1861 {
		/*
		* https://leetcode.com/problems/rotating-the-box/description/
		*/
		class Solution {
		public:
			vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
				size_t m = box.size(), n = box[0].size();
				vector<vector<char>> reversed(n, vector<char>(m));
				for (size_t i = 0; i < m; ++i)
					for (size_t j = 0; j < n; ++j)
						reversed[j][m - i - 1] = box[i][j];

				for (size_t c = 0; c < m; ++c) {
					int bottom = n - 1;
					for (int i = bottom; i > -1; --i) {
						if (reversed[i][c] == '.')
							continue;
						if (reversed[i][c] == '#') {
							if (bottom != i) {
								reversed[bottom][c] = '#';
								reversed[i][c] = '.';
							}
							--bottom;
						}
						else
							bottom = i - 1;
					}
				}

				return reversed;
			}
		};
	}

	namespace task_1863 {
		/*
		* https://leetcode.com/problems/sum-of-all-subset-xor-totals/description/
		*/
		class Solution {
		public:
			size_t size;

			int subsetXORSum(vector<int>& nums) {
				size = nums.size();
				return subsetXORSum(nums, 0, 0);
			}

			int subsetXORSum(vector<int>& nums, const size_t from, int acc) {
				if (from == size)
					return acc;
				return subsetXORSum(nums, from + 1, acc) + subsetXORSum(nums, from + 1, acc ^ nums[from]);
			}

			int subsetXORSum__fast__leetcode(vector<int>& nums) {
				int result = 0;
				// Capture each bit that is set in any of the elements
				for (int num : nums) {
					result |= num;
				}
				// Multiply by the number of subset XOR totals that will have each bit set
				return result << (nums.size() - 1);
			}
		};
	}

	namespace task_1871 {
		/*
		* https://leetcode.com/problems/jump-game-iii/description/
		*/
		class Solution {
		public:
			bool canReach(string s, int minJump, int maxJump) {
				int size = s.size();
				queue<int> vertexes;
				vertexes.push(0);
				int max_visited = 0;
				while (!vertexes.empty()) {
					auto v = vertexes.front();
					vertexes.pop();
					int end = min(v + maxJump, size - 1);
					int start = min(end + 1, max(max_visited + 1, v + minJump));
					int soft_start = min(end + 1, max(start, v + maxJump + 1 - minJump));

					for (int i = soft_start; i >= start; --i)
						if (s[i] == '0') {
							max_visited = i;
							vertexes.push(i);
							break;
						}

					for (int i = soft_start + 1; i <= end; ++i)
						if (s[i] == '0') {
							max_visited = i;
							vertexes.push(i);
						}
				}

				return max_visited == size - 1;
			}
		};
	}

	namespace task_1884 {
		/*
		* https://leetcode.com/problems/egg-drop-with-2-eggs-and-n-floors/description/
		*/
		class Solution {
		public:
			int twoEggDrop(int n) {
				return ceil((sqrt(1 + (n << 3)) - 1) / 2);
			}

			int twoEggDrop2(int n) {
				int i = 1, steps = 0;
				while (n > 0) {
					n -= i;
					++i;
					++steps;
				}
				return steps;
			}
		};
	}

	namespace task_1894 {
		/*
		* https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/description/
		*/
		class Solution {
		public:
			int chalkReplacer(vector<int>& chalk, int k) {
				long long sum = 0;
				for (const int c : chalk)
					sum += c;
				int size = chalk.size(), i = 0;
				k %= sum;
				for (; k >= chalk[i]; ++i)
					k -= chalk[i];
				return i;
			}
		};
	}

	namespace task_1901 {
		/*
		* https://leetcode.com/problems/find-a-peak-element-ii/
		* false peak is a peak, which peak only in column or only in row,
		* exist row or column, which does not contain false peak,
		* it means peak in this row or column is true
		*/
		class Solution {
		public:
			vector<int> findPeakGrid(vector<vector<int>>& mat) {
				const size_t length = mat.size();
				const size_t width = mat[0].size();

				for (int i = 0; i < length; i++)
				{
					int j = findPeakElementRow(mat[i]);
					if ((i == 0 || mat[i - 1][j] < mat[i][j]) &&
						(i == length - 1 || mat[i + 1][j] < mat[i][j]))
						return vector<int>({ i, j });
				}

				for (int j = 0; j < width; j++)
				{
					int i = findPeakElementColumn(mat, j, length);
					if ((j == 0 || mat[i][j - 1] < mat[i][j]) &&
						(j == mat.size() - 1 || mat[i][j + 1] < mat[i][j]))
						return vector<int>({ i, j });
				}
				return vector<int>({ -1, -1 });
			}

			int findPeakElementRow(vector<int>& nums) {
				const size_t size = nums.size();
				if (size == 1 || nums[1] < nums[0])
					return 0;

				size_t l = 0;
				size_t r = size;

				while (r - l > 2) {
					size_t i = (r + l) / 2;
					if (nums[i] > nums[i + 1])
						r = i + 1;
					else
						l = i;
				}
				return l + 1;
			}

			int findPeakElementColumn(vector<vector<int>>& mat, const size_t j, const size_t length) {
				if (length == 1 || mat[1][j] < mat[0][j])
					return 0;

				size_t l = 0;
				size_t r = length;

				while (r - l > 2) {
					size_t i = (r + l) / 2;
					if (mat[i][j] > mat[i + 1][j])
						r = i + 1;
					else
						l = i;
				}
				return l + 1;
			}
		};
	}

	namespace task_1905 {
		/*
		* https://leetcode.com/problems/count-sub-islands/description/
		*/
		class Solution {
		public:
			int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
				size_t m = grid1.size(), n = grid1[0].size();
				int count = 0;
				for (size_t i = 0; i < m; ++i)
					for (size_t j = 0; j < n; ++j) {
						if (grid2[i][j]) {
							bool isSubisland = true;
							stack<pair<size_t, size_t>> nodes({ pair<size_t, size_t>({i, j}) });
							grid2[i][j] = 0;
							while (!nodes.empty()) {
								size_t a = nodes.top().first, b = nodes.top().second;
								nodes.pop();
								if (grid1[a][b] == 0)
									isSubisland = false;
								if (a > 0 && grid2[a - 1][b]) {
									grid2[a - 1][b] = 0;
									nodes.push({ a - 1, b });
								}
								if (a + 1 < m && grid2[a + 1][b]) {
									grid2[a + 1][b] = 0;
									nodes.push({ a + 1, b });
								}
								if (b > 0 && grid2[a][b - 1]) {
									grid2[a][b - 1] = 0;
									nodes.push({ a, b - 1 });
								}
								if (b + 1 < n && grid2[a][b + 1]) {
									grid2[a][b + 1] = 0;
									nodes.push({ a, b + 1 });
								}
							}
							if (isSubisland)
								++count;
						}
					}
				return count;
			}
		};
	}

	namespace task_1910 {
		/*
		* https://leetcode.com/problems/remove-all-occurrences-of-a-substring/description/
		*/
		class Solution {
		public:
			string removeOccurrences__leetcode(string s, string part) {
				size_t p_size = part.length();
				vector<size_t> prefix = constructPrefix(part);
				string res;
				vector<size_t> patternIndexes(s.length() + 1, 0);

				for (size_t strIndex = 0, patternIndex = 0; strIndex < s.length(); strIndex++) {
					res.push_back(s[strIndex]);

					if (s[strIndex] == part[patternIndex]) {
						patternIndexes[res.size()] = ++patternIndex;

						if (patternIndex == part.length()) {
							for (size_t i = 0; i < p_size; i++)
								res.pop_back();

							patternIndex = res.empty() ? 0 : patternIndexes[res.size()];
						}
					}
					else {
						if (patternIndex != 0) {
							strIndex--;
							patternIndex = prefix[patternIndex - 1];
							res.pop_back();
						}
						else {
							patternIndexes[res.size()] = 0;
						}
					}
				}

				return res;
			}

			string removeOccurrences(string s, string part) {
				size_t t_size = s.length(), p_size = part.length(), i = 0, j = 0;
				size_t;
				vector<pair<size_t, size_t>> intervals(1, { 0, t_size });

				vector<size_t> prefix = constructPrefix(part);
				vector<int> part_indexes(t_size, -1);
				vector<int> part_start_indexes(t_size, -1);

				while (i < t_size) {
					if (s[i] == part[j]) {
						part_indexes[i] = ++j;
						++i;
						if (j == p_size) {
							intervals.back().second = i - j;
							j = prefix[j - 1];
						}
					}
					else {

						if (j != 0)
							j = prefix[j - 1];
						else
							i++;
					}
				}

				string res;
				for (const auto& inter : intervals)
					res += s.substr(inter.first, inter.second - inter.first);
				return res;
			}

			vector<size_t> constructPrefix(string& pat) {
				size_t len = 0, i = 1, size = pat.length();
				vector<size_t> prefix(size);
				prefix[0] = 0;

				while (i < size) {
					if (pat[i] == pat[len]) {
						len++;
						prefix[i] = len;
						i++;
					}
					else {
						if (len != 0) {
							len = prefix[len - 1];
						}
						else {
							prefix[i] = 0;
							i++;
						}
					}
				}
				return prefix;
			}

			vector<int> searchKMP(string& pat, string& txt) {
				size_t t_size = txt.length(), p_size = pat.length(), i = 0, j = 0;
				size_t;
				vector<int> res;

				vector<size_t> prefix = constructPrefix(pat);

				while (i < t_size) {
					if (txt[i] == pat[j]) {
						i++;
						j++;
						if (j == p_size) {
							res.push_back(i - j);
							j = prefix[j - 1];
						}
					}
					else {

						if (j != 0)
							j = prefix[j - 1];
						else
							i++;
					}
				}
				return res;
			}
		};
	}

	namespace task_1920 {
		/*
		* https://leetcode.com/problems/build-array-from-permutation/description/
		*/
		class Solution {
		public:
			vector<int> buildArray(vector<int>& nums) {
				const size_t size = nums.size();
				vector<int> ans(size);
				for (size_t i = 0; i < size; ++i)
					ans[i] = nums[nums[i]];

				return ans;
			}
		};
	}

	namespace task_1922 {
		/*
		* https://leetcode.com/problems/count-good-numbers/description/
		*/
		class Solution {
		public:
			const long long mod = 1000000007;
			int countGoodNumbers(long long n) {
				return myPow(4, n >> 1) * myPow(5, (n + 1) >> 1) % mod;
			}

			long long myPow(long long x, long long n) {
				long long acc_odd = 1, acc_even = x;
				while (n > 0) {
					if (n & 1)
						acc_odd = acc_odd * acc_even % mod;
					acc_even = acc_even * acc_even % mod;
					n >>= 1;
				}
				return acc_odd;
			}

			int countGoodNumbers2(long long n) {
				return (myPow2(5, (n + 1) / 2) % mod * myPow2(4, n / 2) % mod) % mod;
			}

			long long myPow2(long long a, long long b) {
				if (b == 0)
					return 1;
				if (b & 1)
					return (a % mod * myPow2((a * a) % mod, b / 2) % mod) % mod;
				return myPow2((a * a) % mod, b / 2);
			}
		};
	}

	namespace task_1930 {
		/*
		* https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/
		*/
		class Solution {
		public:
			int countPalindromicSubsequence(string s) {
				vector<int> first = vector(26, -1);
				vector<int> last = vector(26, -1);

				for (int i = 0; i < s.size(); i++) {
					int curr = s[i] - 'a';
					if (first[curr] == -1) {
						first[curr] = i;
					}

					last[curr] = i;
				}

				int ans = 0;
				for (int i = 0; i < 26; i++) {
					if (first[i] == -1) {
						continue;
					}

					unordered_set<char> between;
					for (int j = first[i] + 1; j < last[i]; j++) {
						between.insert(s[j]);
					}

					ans += between.size();
				}

				return ans;
			}
		};
	}

	namespace task_1931 {
		/*
		* https://leetcode.com/problems/painting-a-grid-with-three-different-colors/description/
		*/
		class Solution {
		public:
			static const long long mod = 1000000007;
			unordered_map<int, int> cnt, nxt;
			unordered_map<int, vector<int>> valid_prev;
			vector<int> masks;
			size_t count_masks;

			int colorTheGrid(int m, int n) {
				cnt.clear();
				nxt.clear();
				generateBase(0, 0, m);
				generateValidPrev();

				for (int round = 1; round < n; ++round) {
					for (const int mask : masks) {
						long long next_count = 0;
						for (const int neighbour : valid_prev[mask])
							next_count += cnt[neighbour];
						nxt[mask] = next_count % mod;
					}

					swap(cnt, nxt);
					for (auto& [key, value] : nxt)
						value = 0;
				}

				long long ans = 0;
				for (const auto& [key, value] : cnt)
					ans = ans + value;
				return ans % mod;
			}

			void generateBase(const int base, const int last, const int m) {
				if (m == 0) {
					cnt[base] = 1;
					masks.push_back(base);
					return;
				}
				if (1 != last)
					generateBase(base * 10 + 1, 1, m - 1);
				if (2 != last)
					generateBase(base * 10 + 2, 2, m - 1);
				if (3 != last)
					generateBase(base * 10 + 3, 3, m - 1);
			}

			void generateValidPrev() {
				count_masks = masks.size();
				for (size_t i = 0; i < count_masks; ++i)
					valid_prev[masks[i]] = {};
				for (size_t i = 0; i < count_masks; ++i) {
					for (size_t j = i + 1; j < count_masks; ++j) {
						if (canBeNeighbour(masks[i], masks[j])) {
							valid_prev[masks[i]].push_back(masks[j]);
							valid_prev[masks[j]].push_back(masks[i]);
						}
					}
				}
			}

			bool canBeNeighbour(int a, int b) {
				while (a > 0) {
					if (a % 10 == b % 10)
						return false;
					a /= 10;
					b /= 10;
				}
				return true;
			}
		};
	}

	namespace task_1937 {
		/*
		* https://leetcode.com/problems/maximum-number-of-points-with-cost/description/
		*/
		class Solution {
		public:
			long long maxPoints(vector<vector<int>>& points) {
				size_t m = points.size(), n = points[0].size();
				vector<long long> prev_points_row(n), cur_points_row(n);
				for (size_t i = 0; i < n; ++i)
					prev_points_row[i] = points[0][i];
				for (size_t i = 1; i < m; ++i) {
					long long max_points = 0;
					for (size_t j = 0; j < n; ++j, --max_points) {
						if (prev_points_row[j] > max_points) {
							cur_points_row[j] = prev_points_row[j];
							max_points = prev_points_row[j];
						}
						else
							cur_points_row[j] = max_points;
					}
					max_points = 0;
					for (int j = n - 1; j > -1; --j, --max_points) {
						if (prev_points_row[j] > max_points) {
							cur_points_row[j] = max(cur_points_row[j], prev_points_row[j]);
							max_points = prev_points_row[j];
						}
						else
							cur_points_row[j] = max(cur_points_row[j], max_points);
					}
					for (size_t j = 0; j < n; ++j)
						cur_points_row[j] += points[i][j];
					swap(prev_points_row, cur_points_row);
				}
				long long max_points = 0;
				for (const long long points : prev_points_row)
					max_points = max(max_points, points);
				return max_points;
			}
		};
	}

	namespace task_1942 {
		/*
		* https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/description/
		*/
		class Solution {
		public:
			int smallestChair(vector<vector<int>>& times, int targetFriend) {
				int size = times.size();
				priority_queue<pair<int, int>> busy_chairs; // time, number
				priority_queue<int, std::vector<int>, std::greater<int>> free_chairs;
				for (int i = 0; i < size; ++i) {
					times[i].push_back(i);
					free_chairs.push(i);
				}
				sort(times.begin(), times.end());
				for (const vector<int>& time : times) {
					while (!busy_chairs.empty() && -busy_chairs.top().first <= time[0]) {
						free_chairs.push(busy_chairs.top().second);
						busy_chairs.pop();
					}

					int chair = free_chairs.top();
					free_chairs.pop();
					if (targetFriend == time[2])
						return chair;
					busy_chairs.push({ -time[1], chair });
				}
				return 0;
			}
		};
	}

	namespace task_1945 {
		/*
		* https://leetcode.com/problems/sum-of-digits-of-string-after-convert/description/
		*/
		class Solution {
		public:
			int getLucky(string s, int k) {
				string lucky;
				for (char c : s) {
					c -= 'a' - 1;
					if (c > 9)
						lucky.push_back('0' + c / 10);
					lucky.push_back('0' + c % 10);
				}
				int n = 0;
				for (; k > 0; --k) {
					n = 0;
					for (const char c : lucky)
						n += c - '0';
					lucky = to_string(n);
				}
				return n;
			}

			int getLuckyFaster(string s, int k) {
				int n = 0;
				for (char c : s) {
					c -= 'a' - 1;
					n += c / 10 + c % 10;
				}
				for (; k > 1; --k) {
					int new_n = 0;
					while (n > 0) {
						new_n += n % 10;
						n /= 10;
					}
					n = new_n;
				}
				return n;
			}
		};
	}

	namespace task_1953 {
		/*
		* https://leetcode.com/problems/maximum-number-of-weeks-for-which-you-can-work/description/
		*/
		class Solution {
		public:
			long long numberOfWeeks(vector<int>& milestones) {
				long long max_value = 1;
				long long sum = 0;
				for (auto v : milestones) {
					sum += v;
					if (max_value < v)
						max_value = v;
				}

				sum -= max_value;
				return sum < max_value ?
					(sum << 1) + 1 :
					sum + max_value;
			}
		};
	}

	namespace task_1957 {
		/*
		* https://leetcode.com/problems/delete-characters-to-make-fancy-string/description/
		*/
		class Solution {
		public:
			string makeFancyString(string s) {
				string res;
				char last = 0, count_last = 0;
				for (const char c : s) {
					if (c != last) {
						res.push_back(c);
						last = c;
						count_last = 1;
					}
					else if (count_last == 1) {
						++count_last;
						res.push_back(c);
					}
				}
				return res;
			}
		};
	}

	namespace task_1963 {
		/*
		* https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/description/
		*/
		class Solution {
		public:
			int minSwaps(string s) {
				size_t size = s.size(), j = size - 1;
				int opens = 0, closes = 0, swaps = 0;
				for (size_t i = 0; i < size; i++) {
					if (s[i] == ']')
						++closes;
					else
						++opens;
					if (closes > opens) {
						--closes;
						++opens;
						++swaps;
						for (; s[j] == ']'; --j) {}
						swap(s[i], s[j]);
					}
				}
				return swaps;
			}
		};
	}

	namespace task_1964 {
		/*
		* https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/description/
		*/
		class Solution {
		public:
			vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
				const size_t size = obstacles.size();
				size_t length = 0;
				vector<int> ans(size);
				vector<int> ends_of_LIS(size, INT_MAX);

				for (size_t i = 0; i < size; i++) {
					size_t j = search(ends_of_LIS, length, obstacles[i]);
					ends_of_LIS[j] = min(ends_of_LIS[j], obstacles[i]);
					length = max(j + 1, length);
					ans[i] = j + 1;
				}
				return ans;
			}

			size_t search(vector<int>& nums, size_t r, const int target) {
				size_t l = 0;
				if (nums[l] > target)
					return l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] > target)
						r = i;
					else
						l = i;
				}
				return r;
			}
		};
	}

	namespace task_1975 {
		/*
		* https://leetcode.com/problems/maximum-matrix-sum/description/
		*/
		class Solution {
		public:
			long long maxMatrixSum__leetcode(vector<vector<int>>& matrix) {
				long long totalSum = 0;
				int minAbsVal = INT_MAX;
				int negativeCount = 0;

				for (auto& row : matrix) {
					for (int val : row) {
						totalSum += abs(val);
						if (val < 0) {
							negativeCount++;
						}
						minAbsVal = min(minAbsVal, abs(val));
					}
				}

				// Adjust if the count of negative numbers is odd
				if (negativeCount % 2 != 0) {
					totalSum -= 2 * minAbsVal;
				}

				return totalSum;
			}
		};
	}

	namespace task_1976 {
		/*
		* https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/
		*/
		class Solution {
		public:
			int countPaths(int n, vector<vector<int>>& roads) {
				int mod = 1000000007;
				vector<long long> count_ways(n);
				vector<long long> dists(n, LLONG_MAX);
				count_ways[0] = 1;
				dists[0] = 0;
				vector<vector<pair<int, int>>> adjacency_list(n);
				for (const vector<int>& edge : roads) {
					adjacency_list[edge[0]].push_back({ edge[1], edge[2] });
					adjacency_list[edge[1]].push_back({ edge[0], edge[2] });
				}
				priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> queue;
				queue.push({ 0, 0 });

				while (!queue.empty()) {
					long long dist = queue.top().first;
					int vertex = queue.top().second;
					queue.pop();
					if (dist > dists[vertex])
						continue;

					for (const pair<int, int>& v : adjacency_list[vertex]) {
						if (dist + v.second == dists[v.first]) {
							count_ways[v.first] = (count_ways[v.first] + count_ways[vertex]) % mod;
						}
						else if (dist + v.second < dists[v.first]) {
							dists[v.first] = dist + v.second;
							count_ways[v.first] = count_ways[vertex];
							queue.push({ dist + v.second , v.first });
						}
					}

				}

				return count_ways[n - 1];
			}
		};
	}

	namespace task_1980 {
		/*
		* https://leetcode.com/problems/find-unique-binary-string/description/
		*/
		class Solution {
		public:
			string findDifferentBinaryString(vector<string>& nums) {
				size_t length = nums[0].size();
				vector<int> numbers(nums.size());
				for (size_t i = 0; i < length; ++i)
					numbers[i] = getNumber(nums[i]);
				sort(numbers.begin(), numbers.end());
				int number = 0, size = numbers.size();
				for (; number < size && number == numbers[number]; ++number) {}

				return getString(number, length);
			}

			int getNumber(const string& num) {
				int n = 0;
				for (const char c : num)
					n = (n << 1) + (c == '1' ? 1 : 0);
				return n;
			}

			string getString(int number, const size_t length) {
				string num(length, '0');
				for (int i = length - 1; i >= 0; --i) {
					if (number & 1)
						num[i] = '1';
					number >>= 1;
				}
				return num;
			}
		};
	}

	namespace task_2017 {
		/*
		* https://leetcode.com/problems/grid-game/description/
		*/
		class Solution {
		public:
			long long gridGame(vector<vector<int>>& grid) {
				size_t size = grid[0].size();
				if (size == 1)
					return 0;
				long long upperSum = 0, lowerSum = 0;
				for (int n : grid[0])
					upperSum += n;
				upperSum -= grid[0][0];
				long long minValue = upperSum;
				for (size_t i = 1; true; ++i) {
					upperSum -= grid[0][i];
					lowerSum += grid[1][i - 1];
					if (lowerSum < upperSum) {
						minValue = upperSum;
					}
					else {
						minValue = min(minValue, lowerSum);
						break;
					}
				}
				return minValue;
			}
		};
	}

	namespace task_2022 {
		/*
		* https://leetcode.com/convert-1d-array-into-2d-array/description/
		*/
		class Solution {
		public:
			vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
				int size = original.size();
				if (m * n != size)
					return vector<vector<int>>();
				vector<vector<int>> res(m, vector<int>(n));
				for (int i = 0; i < size; ++i)
					res[i / n][i % n] = original[i];
				return res;
			}
		};
	}

	namespace task_2027 {
		/*
		* https://leetcode.com/problems/minimum-moves-to-convert-string/
		*/
		class Solution {
		public:
			int minimumMoves(string s) {
				int count = 0;
				size_t size = s.size();
				for (size_t i = 0; i < size; ++i)
					if (s[i] == 'X') {
						++count;
						i += 2;
					}
				return count;
			}
		};
	}

	namespace task_2028 {
		/*
		* https://leetcode.com/problems/find-missing-observations/description/
		*/
		class Solution {
		public:
			vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
				int m = rolls.size();
				int req_sum = mean * (n + m), sum = 0;
				for (const int roll : rolls)
					sum += roll;
				req_sum -= sum + n; // substract another rolls fiiled with 1
				if (0 > req_sum || 5 * n < req_sum)
					return {};

				int count_six = req_sum / 5; // 5 because 1 os already substructed
				vector<int> rolls_n(n, 1);
				for (int i = 0; i < count_six; i++)
					rolls_n[i] = 6;
				req_sum -= 5 * count_six;
				rolls_n.back() += req_sum;
				return rolls_n;
			}

			vector<int> missingRolls2(vector<int>& rolls, int mean, int n) {
				int sum = 0;
				for (int i = 0; i < rolls.size(); i++) {
					sum = sum + rolls[i];
				}
				// Find the remaining sum.
				int remainingSum = mean * (n + rolls.size()) - sum;
				// Check if sum is valid or not.
				if (remainingSum > 6 * n or remainingSum < n) {
					return {};
				}
				int distributeMean = remainingSum / n;
				int mod = remainingSum % n;
				// Distribute the remaining mod elements in nElements array.
				vector<int> nElements(n, distributeMean);
				for (int i = 0; i < mod; i++) {
					nElements[i]++;
				}
				return nElements;
			}
		};
	}

	namespace task_2033 {
		/*
		* https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/description/
		*/
		class Solution {
		public:
			int minOperations(vector<vector<int>>& grid, int x) {
				int mod = grid[0][0] % x;
				vector<int> numsArray;
				for (const vector<int>& row : grid) {
					for (const int n : row)
						if (n % x != mod)
							return -1;
					numsArray.insert(numsArray.begin(), row.begin(), row.end());
				}
				sort(numsArray.begin(), numsArray.end());
				int target = numsArray[numsArray.size() / 2], count = 0;

				for (const vector<int>& row : grid) {
					for (const int n : row)
						count += abs(target - n) / x;
				}
				return count;
			}
		};
	}

	namespace task_2037 {
		/*
		* https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/description/
		*/
		class Solution {
		public:
			int minMovesToSeat(vector<int>& seats, vector<int>& students) {
				sort(seats.begin(), seats.end());
				sort(students.begin(), students.end());
				size_t size = students.size();
				int res = 0;
				for (size_t i = 0; i < size; i++)
					res += abs(seats[i] - students[i]);
				return res;
			}
		};
	}

	namespace task_2044 {
		/*
		* https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/description/
		*/
		class Solution {
		public:
			int countMaxOrSubsets(vector<int>& nums) {
				int maxOR = OR(nums), count = 0;
				auto sets = subsets(nums);
				for (const vector<int>& set : sets)
					if (maxOR == OR(set))
						++count;
				return count;
			}

			vector<vector<int>> subsets(vector<int>& nums) {
				size_t size = nums.size();
				vector<vector<int>> res(1 << size);
				for (size_t i = 0; i < size; i++) {
					size_t count_pieces = 1 << (i + 1);
					size_t size_of_piece = 1 << (size - i - 1);
					size_t t = 0;
					for (size_t j = 0; j < count_pieces; j++)
						if (j & 1)
							for (size_t k = 0; k < size_of_piece; k++, t++)
								res[t].push_back(nums[i]);
						else
							t += size_of_piece;
				}
				return res;
			}

			int OR(const vector<int>& nums) {
				int OR = 0;
				for (const int n : nums)
					OR |= n;
				return OR;
			}
		};
	}

	namespace task_2045 {
		/*
		* https://leetcode.com/problems/second-minimum-time-to-reach-destination/description/
		*/
		class Solution {
		public:
			int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
				vector<int> visited(n + 1);
				vector<vector<int>> adjacency_list(n + 1);
				for (const vector<int>& edge : edges) {
					adjacency_list[edge[0]].push_back(edge[1]);
					adjacency_list[edge[1]].push_back(edge[0]);
				}
				queue<int> queue;
				queue.push(1);
				vector<int> added_in_queue(n);
				int count_added = 0;
				size_t cycles = 0;
				for (; visited[n] != 4; ++cycles) {
					size_t size = queue.size();
					for (size_t i = 0; i < size; ++i) {
						int node = queue.front();
						queue.pop();
						for (const int neighbour : adjacency_list[node])
							if (visited[neighbour] == 0 || visited[neighbour] == 2) {
								++visited[neighbour];
								added_in_queue[count_added++] = neighbour;
								queue.push(neighbour);
							}
					}
					for (size_t i = 0; i < count_added; ++i)
						++visited[added_in_queue[i]];
					count_added = 0;
				}
				int time_travel = 0;
				for (size_t i = 0; i < cycles; ++i) {
					if (((time_travel / change) & 1) == 1)
						time_travel += change - (time_travel % change);
					time_travel += time;
				}
				return time_travel;
			}
		};
	}

	namespace task_2053 {
		/*
		* https://leetcode.com/problems/kth-distinct-string-in-an-array/description/
		*/
		class Solution {
		public:
			string kthDistinct(vector<string>& arr, int k) {
				unordered_multiset<string> set;
				for (const string& str : arr)
					set.insert(str);
				int count = 0;
				for (const string& str : arr)
					if (set.count(str) == 1) {
						++count;
						if (count == k)
							return str;
					}
				return "";
			}
		};
	}

	namespace task_2054 {
		/*
		* https://leetcode.com/problems/two-best-non-overlapping-events/description/
		*/
		class Solution {
		public:
			int maxTwoEvents(vector<vector<int>>& events) {
				sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b)
					{
						return a[1] < b[1];
					});
				vector<pair<int, int>> monotonic_stack{ {0, 0} };
				for (const vector<int>& event : events)
					monotonic_stack.push_back({ event[1], max(monotonic_stack.back().second, event[2]) });
				sort(events.begin(), events.end());
				int max_profit = 0;
				size_t i = 0, size = monotonic_stack.size();
				for (const vector<int>& event : events) {
					for (; i < size && monotonic_stack[i].first < event[0]; ++i) {}
					--i;
					max_profit = max(max_profit, monotonic_stack[i].second + event[2]);
				}
				return max_profit;
			}
		};
	}

	namespace task_2058 {
		/*
		* https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/description/
		*/
		class Solution {
		public:
			vector<int> nodesBetweenCriticalPoints(ListNode* head) {
				int min_dist = INT32_MAX, dist = 0, first_crit = 1, last_crit, i;

				while (head->next && head->next->next) {
					if (head->next->val > head->val && head->next->val > head->next->next->val ||
						head->next->val < head->val && head->next->val < head->next->next->val)
						break;
					++first_crit;
					head = head->next;
				}
				i = first_crit + 1;
				head = head->next;
				while (head->next && head->next->next) {
					++dist;
					if (head->next->val > head->val && head->next->val > head->next->next->val ||
						head->next->val < head->val && head->next->val < head->next->next->val) {
						min_dist = min(min_dist, dist);
						last_crit = i;
						dist = 0;
					}
					++i;
					head = head->next;
				}

				if (min_dist == INT32_MAX)
					return { -1, -1 };
				else
					return { min_dist , last_crit - first_crit };
			}
		};
	}

	namespace task_2064 {
		/*
		* https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/description/
		*/
		class Solution {
		public:
			int minimizedMaximum(int n, vector<int>& quantities) {
				long long sum_quantities = 0;
				int r = 1;
				for (const int q : quantities) {
					r = max(r, q);
					sum_quantities += q;
				}
				int l = max(sum_quantities / n - 1, 0ll);
				while (r - l > 1) {
					int i = (r + l) / 2;
					if (canDistribute(n, i, quantities))
						r = i;
					else
						l = i;
				}
				return r;
			}


			bool canDistribute(int n, const int count, const vector<int>& quantities) {
				for (const int q : quantities)
					n -= q / count + (q % count != 0 ? 1 : 0);
				return n >= 0;
			}
		};
	}

	namespace task_2070 {
		/*
		* https://leetcode.com/problems/most-beautiful-item-for-each-query/description/
		*/
		class Solution {
		public:
			vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
				items.push_back({ 0, 0 });
				size_t size_i = items.size(), size_q = queries.size();
				sort(items.begin(), items.end());
				for (int i = size_i - 1; i > 1; --i)
					if (items[i - 1][0] == items[i][0])
						items[i - 1][1] == items[i][1];
				for (size_t i = 2; i < size_i; ++i)
					if (items[i][1] < items[i - 1][1])
						items[i] = items[i - 1];

				vector<int> answers(size_q);
				for (size_t i = 0; i < size_q; ++i)
					answers[i] = bin_search(items, size_i, queries[i]);
				return answers;
			}


			int bin_search(const vector<vector<int>>& items, size_t r, int value) {
				size_t l = 0;
				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (items[i][0] > value)
						r = i;
					else
						l = i;
				}
				return items[l][1];
			}
		};
	}

	namespace task_2071 {
		/*
		* https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/description/
		*/
		class Solution {
		public:
			int maxTaskAssign__leetcode(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
				int n = tasks.size(), m = workers.size();
				sort(tasks.begin(), tasks.end());
				sort(workers.begin(), workers.end());

				auto check = [&](int mid) -> bool {
					int p = pills;
					deque<int> ws;
					int ptr = m - 1;
					// Enumerate each task from largest to smallest
					for (int i = mid - 1; i >= 0; --i) {
						while (ptr >= m - mid && workers[ptr] + strength >= tasks[i]) {
							ws.push_front(workers[ptr]);
							--ptr;
						}
						if (ws.empty()) {
							return false;
						}
						// If the largest element in the deque is greater than or equal
						// to tasks[i]
						else if (ws.back() >= tasks[i]) {
							ws.pop_back();
						}
						else {
							if (!p) {
								return false;
							}
							--p;
							ws.pop_front();
						}
					}
					return true;
				};

				int left = 1, right = min(m, n), ans = 0;
				while (left <= right) {
					int mid = (left + right) / 2;
					if (check(mid)) {
						ans = mid;
						left = mid + 1;
					}
					else {
						right = mid - 1;
					}
				}
				return ans;
			}
		};
	}

	namespace task_2074 {
		/*
		* https://leetcode.com/problems/reverse-nodes-in-even-length-groups/
		*/
		class Solution {
		public:
			ListNode* reverseEvenLengthGroups(ListNode* head) {
				size_t size = 0;
				auto ptr = head;
				while (ptr)
				{
					++size;
					ptr = ptr->next;
				}
				if (size < 2)
					return head;

				ptr = head;
				
				--size;
				size_t k = 2;
				size_t size_group = min(k, size);
				vector<ListNode*> stack(sqrt(size << 1) + 1);
				while (size_group > 0) {
					++k;
					size -= size_group;
					if (size_group & 1) {
						for (size_t i = 0; i < size_group; i++)
							ptr = ptr->next;
						size_group = min(k, size);
						continue;
					}
					auto j = ptr->next;
					for (size_t i = 0; i < size_group; i++) {
						stack[i] = j;
						j = j->next;
					}

					ptr->next = stack[size_group - 1];
					for (int i = size_group - 2; i >= 0; --i)
						stack[i + 1]->next = stack[i];
					stack[0]->next = j;

					ptr = stack[0];
					size_group = min(k, size);
				}
				return head;
			}
		};
	}

	namespace task_2094 {
		/*
		* https://leetcode.com/problems/finding-3-digit-even-numbers/description/
		*/
		class Solution {
		public:
			vector<int> findEvenNumbers(vector<int>& digits) {
				set<int> nums;
				size_t size = digits.size();
				for (size_t i = 0; i < size; ++i) {
					if (digits[i] % 2 == 0) {
						for (size_t j = 0; j < i; ++j) {
							for (size_t k = 0; k < size; ++k) {
								if (digits[k] != 0 && k != i && k != j)
									nums.insert(digits[k] * 100 + digits[j] * 10 + digits[i]);
							}
						}
						for (size_t j = i + 1; j < size; ++j) {
							for (size_t k = 0; k < size; ++k) {
								if (digits[k] != 0 && k != i && k != j)
									nums.insert(digits[k] * 100 + digits[j] * 10 + digits[i]);
							}
						}
					}
				}
				return vector<int>(nums.begin(), nums.end());
			}
		};
	}

	namespace task_2095 {
		/*
		* https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/description/
		*/
		class Solution {
		public:
			ListNode* deleteMiddle(ListNode* head) {
				if (!head->next)
					return nullptr;
				ListNode* ptr1 = head;
				ListNode* ptr2 = head->next->next;
				while (ptr2) {
					ptr2 = ptr2->next;
					if (ptr2)
						ptr2 = ptr2->next;
					else
						break;
					ptr1 = ptr1->next;
				}
				ptr1->next = ptr1->next->next;
				return head;
			}
		};
	}

	namespace task_2096 {
		/*
		* https://leetcode.com/step-by-step-directions-from-a-binary-tree-node-to-another/description/
		*/
		class Solution {
		public:
			string getDirections(TreeNode* root, int startValue, int destValue) {
				queue<TreeNode*> queue;
				unordered_map<int, TreeNode*> parents;
				int start_level = 0, dest_level = 0, level = 0;
				TreeNode* start = nullptr, * dest = nullptr;
				string start_path, dest_path;
				queue.push(root);
				while (!start || !dest) {
					size_t size = queue.size();
					for (size_t i = 0; i < size; ++i) {
						TreeNode* node = queue.front();
						queue.pop();
						if (node->val == startValue) {
							start_level = level;
							start = node;
						}
						else if (node->val == destValue) {
							dest_level = level;
							dest = node;
						}
						if (node->left) {
							parents[node->left->val] = node;
							queue.push(node->left);
						}
						if (node->right) {
							parents[node->right->val] = node;
							queue.push(node->right);
						}
					}
					++level;
				}

				if (start_level > dest_level)
					start_path = string(start_level - dest_level, 'U');
				for (; start_level > dest_level; --start_level)
					start = parents[start->val];
				for (; dest_level > start_level; --dest_level) {
					TreeNode* parent = parents[dest->val];
					dest_path.push_back(parent->left == dest ? 'L' : 'R');
					dest = parent;
				}
				while (start != dest) {
					TreeNode* parent_s = parents[start->val];
					TreeNode* parent_d = parents[dest->val];
					start_path.push_back('U');
					dest_path.push_back(parent_d->left == dest ? 'L' : 'R');
					start = parent_s;
					dest = parent_d;
				}
				reverse(dest_path.begin(), dest_path.end());
				return start_path + dest_path;
			}
		};
	}

	namespace task_2097 {
		/*
		* https://leetcode.com/problems/valid-arrangement-of-pairs/description/
		*/
		class Solution {
		public:
			vector<vector<int>> validArrangement__leetcode(vector<vector<int>>& pairs) {
				unordered_map<int, deque<int>> adjacencyMatrix;
				unordered_map<int, int> inDegree, outDegree;

				// Build the adjacency list and track in-degrees and out-degrees
				for (const auto& pair : pairs) {
					int start = pair[0], end = pair[1];
					adjacencyMatrix[start].push_back(end);
					outDegree[start]++;
					inDegree[end]++;
				}

				vector<int> result;

				// Find the start node (outDegree == inDegree + 1)
				int startNode = -1;
				for (const auto& entry : outDegree) {
					int node = entry.first;
					if (outDegree[node] == inDegree[node] + 1) {
						startNode = node;
						break;
					}
				}

				// If no such node exists, start from the first pair's first element
				if (startNode == -1) {
					startNode = pairs[0][0];
				}

				stack<int> nodeStack;
				nodeStack.push(startNode);

				// Iterative DFS using stack
				while (!nodeStack.empty()) {
					int node = nodeStack.top();
					if (!adjacencyMatrix[node].empty()) {
						// Visit the next node
						int nextNode = adjacencyMatrix[node].front();
						adjacencyMatrix[node].pop_front();
						nodeStack.push(nextNode);
					}
					else {
						// No more neighbors to visit, add node to result
						result.push_back(node);
						nodeStack.pop();
					}
				}

				// Reverse the result since we collected nodes in reverse order
				reverse(result.begin(), result.end());

				// Construct the result pairs
				vector<vector<int>> pairedResult;
				for (int i = 1; i < result.size(); ++i) {
					pairedResult.push_back({ result[i - 1], result[i] });
				}

				return pairedResult;
			}
		};
	}

	namespace task_2109 {
		/*
		* https://leetcode.com/problems/adding-spaces-to-a-string/description/
		*/
		class Solution {
		public:
			string addSpaces(string s, vector<int>& spaces) {
				string res;
				size_t size = s.size(), size_sp = spaces.size(), s_i = 0, i = 0;
				for (; i < size && s_i < size_sp; ++i) {
					if (i == spaces[s_i]) {
						res.push_back(' ');
						++s_i;
					}
					res.push_back(s[i]);
				}
				for (; i < size; ++i)
					res.push_back(s[i]);
				return res;
			}
		};
	}

	namespace task_2115 {
		/*
		* https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/description/
		*/
		class Solution {
		public:
			size_t size;
			unordered_set<string> supplies_set;
			map<string, size_t> recipes_map;
			vector<int> visited; // 0 - not visited, 1 - opened, 2 - can not cook, 3 can cook

			vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
				size = recipes.size();
				supplies_set = unordered_set<string>(supplies.begin(), supplies.end());
				recipes_map.clear();
				for (size_t i = 0; i < size; ++i)
					recipes_map[recipes[i]] = i;
				visited = vector<int>(size);
				vector<string> res;


				for (size_t i = 0; i < size; ++i)
					if (visited[i] == 3 || canCook(recipes, ingredients, i))
						res.push_back(recipes[i]);

				return res;
			}

			bool canCook(const vector<string>& recipes, const vector<vector<string>>& ingredients, const size_t i) {
				visited[i] = 1;
				for (const string& ingredient : ingredients[i]) {
					if (!supplies_set.contains(ingredient)) {
						if (auto it = recipes_map.find(ingredient); it != recipes_map.end()) {
							size_t j = it->second;
							if (visited[j] == 3) {
								continue;
							}
							else if (visited[j] == 0) {
								if (!canCook(recipes, ingredients, j)) {
									visited[i] = 2;
									return false;
								}
							}
							else {
								visited[i] = 2;
								return false;
							}
						}
						else {
							visited[i] = 2;
							return false;
						}
					}
				}

				visited[i] = 3;
				return true;
			}
		};
	}

	namespace task_2116 {
		/*
		* https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/description/
		*/
		class Solution {
		public:
			bool canBeValid(string s, string locked) {
				if (s.size() % 2 == 1)
					return false;
				int count = 0;
				int count_flex = 0;
				for (size_t i = 0; i < s.size(); ++i) {
					if (s[i] == '(' || locked[i] == '0')
						++count;
					else
						--count;
					if (locked[i] == '0')
						++count_flex;

					if (count < 0)
						return false;
				}
				count = 0;
				count_flex = 0;
				for (int i = s.size() - 1; i >= 0; --i) {
					if (s[i] == ')' || locked[i] == '0')
						++count;
					else
						--count;
					if (locked[i] == '0')
						++count_flex;

					if (count < 0)
						return false;
				}
				return true;
			}

			bool old(string s, string locked) {
				int open_flex = 0;
				int open_locked = 0;
				int close_flex = 0;
				for (size_t i = 0; i < s.size(); i++) {
					if (s[i] == '(' && locked[i] == '0')
						++open_flex;
					else if (s[i] == '(' && locked[i] == '1')
						++open_locked;
					else if (s[i] == ')' && locked[i] == '0')
						++close_flex;
					else {
						if (open_locked > 0)
							--open_locked;
						else
							--open_flex;
					}

					int diff = open_flex + open_locked - close_flex;
					if (diff == -1) {
						--close_flex;
						++open_locked;
						if (close_flex == -1)
							return false;
					}
				}
				int diff = open_flex + open_locked - close_flex;
				return diff <= open_flex * 2;
			}

			bool canBeValid__leetcode(string s, string locked) {
				int length = s.size();
				// If length of string is odd, return false.
				if (length % 2 == 1) {
					return false;
				}
				int openBrackets = 0, unlocked = 0;
				// Iterate through the string to handle '(' and ')'.
				for (int i = 0; i < length; i++) {
					if (locked[i] == '0') {
						unlocked++;
					}
					else if (s[i] == '(') {
						openBrackets++;
					}
					else if (s[i] == ')') {
						if (openBrackets > 0) {
							openBrackets--;
						}
						else if (unlocked > 0) {
							unlocked--;
						}
						else {
							return false;
						}
					}
				}
				// Match remaining open brackets with unlocked characters.
				int balance = 0;
				for (int i = length - 1; i >= 0; i--) {
					if (locked[i] == '0') {
						balance--;
						unlocked--;
					}
					else if (s[i] == '(') {
						balance++;
						openBrackets--;
					}
					else if (s[i] == ')') {
						balance--;
					}
					if (balance > 0) {
						return false;
					}
					if (unlocked == 0 and openBrackets == 0) {
						break;
					}
				}

				if (openBrackets > 0) {
					return false;
				}

				return true;
			}
		};
	}

	namespace task_2131 {
		/*
		* https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/description/
		*/
		class Solution {
		public:
			int longestPalindrome(vector<string>& words) {
				vector<vector<int>> count_words(26, vector<int>(26));
				for (const string& word : words)
					++count_words[word[0] - 'a'][word[1] - 'a'];
				int has_odd_symmetric = 0, count_pair = 0, count_symmetric_pair = 0;
				for (size_t i = 0; i < 26; ++i) {
					if (count_words[i][i] & 1 == 1)
						has_odd_symmetric = 2;
					count_symmetric_pair += count_words[i][i] >> 1;
				}
				for (size_t i = 1; i < 26; i++) {
					for (size_t j = 0; j < i; ++j)
						count_pair += min(count_words[i][j], count_words[j][i]);
				}

				return has_odd_symmetric + ((count_symmetric_pair + count_pair) << 2);
			}
		};
	}

	namespace task_2134 {
		/*
		* https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/description/
		*/
		class Solution {
		public:
			int minSwaps(vector<int>& nums) {
				size_t i = 0, j = 0, size = nums.size();
				int count_ones = 0, count_window = 0, count;
				for (const int n : nums)
					if (n)
						++count_ones;
				for (; j < count_ones; ++j)
					if (nums[j])
						++count_window;
				count = count_ones - count_window;
				for (size_t i = 0; i < size; ++i, ++j) {
					j %= size;
					if (nums[j])
						++count_window;
					if (nums[i])
						--count_window;
					count = min(count, count_ones - count_window);
				}
				return count;
			}
		};
	}

	namespace task_2140 {
		/*
		* https://leetcode.com/problems/solving-questions-with-brainpower/description/
		*/
		class Solution {
		public:
			long long mostPoints(vector<vector<int>>& questions) {
				int size = questions.size();
				vector<long long> points(size);
				points[size - 1] = questions[size - 1][0];
				for (int i = size - 2; i >= 0; --i) {
					int index = i + questions[i][1] + 1;
					long long point = questions[i][0] + (index < size ? points[index] : 0);
					points[i] = max(points[i + 1], point);
				}
				return points[0];
			}
		};
	}

	namespace task_2145 {
		/*
		* https://leetcode.com/problems/count-the-hidden-sequences/description/
		*/
		class Solution {
		public:
			int numberOfArrays(vector<int>& differences, int lower, int upper) {
				long long min_value = 0, max_value = 0, value = 0;
				for (int diff : differences) {
					value += diff;
					min_value = min(min_value, value);
					max_value = max(max_value, value);
				}

				return max(upper - lower + min_value - max_value + 1, (long long)0);
			}
		};
	}

	namespace task_2161 {
		/*
		* https://leetcode.com/problems/partition-array-according-to-given-pivot/description/
		*/
		class Solution {
		public:
			vector<int> pivotArray(vector<int>& nums, int pivot) {
				const size_t size = nums.size();
				vector<int> res(size);
				size_t less_i = 0, greater_i = size - 1;
				for (int i = 0, j = size - 1; i < size; i++, j--) {
					if (nums[i] < pivot) {
						res[less_i] = nums[i];
						++less_i;
					}
					if (nums[j] > pivot) {
						res[greater_i] = nums[j];
						--greater_i;
					}
				}
				for (; less_i <= greater_i; ++less_i)
					res[less_i] = pivot;

				return res;
			}
		};
	}

	namespace task_2172 {
		/*
		* https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/description/
		*/
		class Solution {
		public:
			int maximumInvitations__leetcode(vector<int>& favorite) {
				int n = favorite.size();
				vector<int> inDegree(n, 0);

				// Calculate in-degree for each node
				for (int person = 0; person < n; ++person) {
					inDegree[favorite[person]]++;
				}

				// Topological sorting to remove non-cycle nodes
				queue<int> q;
				for (int person = 0; person < n; ++person) {
					if (inDegree[person] == 0) {
						q.push(person);
					}
				}

				vector<int> depth(n, 1);  // Depth of each node
				while (!q.empty()) {
					int currentNode = q.front();
					q.pop();
					int nextNode = favorite[currentNode];
					depth[nextNode] = max(depth[nextNode], depth[currentNode] + 1);
					if (--inDegree[nextNode] == 0) {
						q.push(nextNode);
					}
				}

				int longestCycle = 0;
				int twoCycleInvitations = 0;

				// Detect cycles
				for (int person = 0; person < n; ++person) {
					if (inDegree[person] == 0) continue;  // Already processed

					int cycleLength = 0;
					int current = person;
					while (inDegree[current] != 0) {
						inDegree[current] = 0;  // Mark as visited
						cycleLength++;
						current = favorite[current];
					}

					if (cycleLength == 2) {
						// For 2-cycles, add the depth of both nodes
						twoCycleInvitations += depth[person] + depth[favorite[person]];
					}
					else {
						longestCycle = max(longestCycle, cycleLength);
					}
				}

				return max(longestCycle, twoCycleInvitations);
			}
		};
	}

	namespace task_2176 {
		/*
		* https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/description/
		*/
		class Solution {
		public:
			int countPairs(vector<int>& nums, int k) {
				int count = 0;
				size_t size = nums.size();
				for (size_t i = 0; i < size; ++i)
					for (size_t j = i + 1; j < size; ++j)
						if (nums[i] == nums[j] && i * j % k == 0)
							++count;
				return count;
			}
		};
	}

	namespace task_2179 {
		/*
		* https://leetcode.com/problems/count-good-triplets-in-an-array/description/
		*/
		class Solution {
		public:
			class FenwickTree {
			private:
				vector<int> tree;

			public:
				FenwickTree(int size) : tree(size + 1, 0) {}

				void update(int index, int delta) {
					index++;
					while (index < tree.size()) {
						tree[index] += delta;
						index += index & -index;
					}
				}

				int query(int index) {
					index++;
					int res = 0;
					while (index > 0) {
						res += tree[index];
						index -= index & -index;
					}
					return res;
				}
			};

			long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
				int n = nums1.size();
				vector<int> pos2(n), reversedIndexMapping(n);
				for (int i = 0; i < n; i++)
					pos2[nums2[i]] = i;
				for (int i = 0; i < n; i++)
					reversedIndexMapping[pos2[nums1[i]]] = i;

				FenwickTree tree(n);
				long long res = 0;
				for (int value = 0; value < n; value++) {
					int pos = reversedIndexMapping[value];
					int left = tree.query(pos);
					tree.update(pos, 1);
					int right = (n - 1 - pos) - (value - left);
					res += (long long)left * right;
				}
				return res;
			}
		};
	}

	namespace task_2181 {
		/*
		* https://leetcode.com/problems/merge-nodes-in-between-zeros/description/
		*/
		class Solution {
		public:
			ListNode* mergeNodes(ListNode* head) {
				int sum = 0;
				head = head->next;
				ListNode* guard = new ListNode();
				ListNode* ptr = guard;
				while (head) {
					sum += head->val;
					if (head->val == 0) {
						ptr->next = new ListNode(sum);
						ptr = ptr->next;
						sum = 0;
					}
					head = head->next;
				}
				ptr = guard->next;
				delete guard;
				return ptr;
			}
		};
	}

	namespace task_2182 {
		/*
		* https://leetcode.com/problems/construct-string-with-repeat-limit/description/
		*/
		class Solution {
		public:
			string repeatLimitedString(string s, int repeatLimit) {
				vector<int> counts(26);
				for (char c : s)
					++counts[c - 'a'];
				string res;
				int last = 25, prev = 24;
				while (last != -1) {
					int use = min(counts[last], repeatLimit);
					res.append(use, last + 'a');

					counts[last] -= use;
					if (counts[last] > 0) {
						for (; prev != -1 && counts[prev] == 0; --prev) {}
						if (prev == -1)
							return res;

						res.push_back(prev + 'a');
						--counts[prev];
					}
					else {
						for (; last != -1 && counts[last] == 0; --last) {}
						if (last <= prev)
							prev = last - 1;
					}
				}
				return res;
			}
		};
	}

	namespace task_2185 {
		/*
		* https://leetcode.com/problems/counting-words-with-a-given-prefix/description/
		*/
		class Solution {
		public:
			int prefixCount(vector<string>& words, string pref) {
				int count = 0;
				for (string& word : words) {
					if (word.find(pref) == 0) {
						count++;  // Found a string with pref as prefix
					}
				}
				return count;
			}
		};
	}

	namespace task_2191 {
		/*
		* https://leetcode.com/problems/sort-the-jumbled-numbers/description/
		*/
		class Solution {
		public:
			vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
				const int size = nums.size();
				vector<vector<int>> mapped(size);
				for (int i = 0; i < size; ++i)
					mapped[i] = { transform(nums[i], mapping), i, nums[i] };
				sort(mapped.begin(), mapped.end());
				for (int i = 0; i < size; ++i)
					nums[i] = mapped[i][2];
				return nums;
			}

			vector<int> sortJumbledFaster(vector<int>& mapping, vector<int>& nums) {
				const size_t size = nums.size();
				vector<pair<int, size_t>> mapped(size);
				for (size_t i = 0; i < size; ++i)
					mapped[i] = { transform(nums[i], mapping), i };
				sort(mapped.begin(), mapped.end());
				for (size_t i = 0; i < size; ++i)
					mapped[i].first = nums[mapped[i].second];
				for (size_t i = 0; i < size; ++i)
					nums[i] = mapped[i].first;
				return nums;
			}

			int transform(int value, const vector<int>& mapping) {
				int mult = 10, res = mapping[value % 10];
				value /= 10;
				for (; value > 0; value /= 10, mult *= 10)
					res += mapping[value % 10] * mult;
				return res;
			}
		};
	}

	namespace task_2192 {
		/*
		* https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/description/
		*/
		class Solution {
		public:
			vector<char> visited;
			vector<set<int>> adjacency_list;

			vector<vector<int>> getAncestorsTLE(int n, vector<vector<int>>& edges) {
				visited = vector<char>(n);
				adjacency_list = vector<set<int>>(n);
				for (const vector<int>& edge : edges)
					adjacency_list[edge[1]].insert(edge[0]);
				for (int i = 0; i < n; i++)
					if (visited[i] == 0)
						dfs(i, n);

				vector<vector<int>> ancestors(n);
				for (size_t i = 0; i < n; ++i)
					ancestors[i].insert(ancestors[i].end(), adjacency_list[i].begin(), adjacency_list[i].end());
				return ancestors;
			}

			void dfs(const size_t from, const size_t size) {
				stack<size_t> vertexes;
				vertexes.push(from);
				while (!vertexes.empty()) {
					size_t vertex = vertexes.top();
					if (visited[vertex] == 2) {
						vertexes.pop();
						continue;
					}
					if (visited[vertex] == 1) {
						visited[vertex] = 2;
						for (const int neighbour : adjacency_list[vertex])
							adjacency_list[vertex].insert(adjacency_list[neighbour].begin(), adjacency_list[neighbour].end());
						vertexes.pop();
						continue;
					}
					visited[vertex] = 1;
					for (const int neighbour : adjacency_list[vertex])
						if (visited[neighbour] == 0)
							vertexes.push(neighbour);
				}
			}

			vector<vector<int>> getAncestorsSlow(int n, vector<vector<int>>& edges) {
				vector<set<int>> adjacency_list(n);
				for (const vector<int>& edge : edges)
					adjacency_list[edge[1]].insert(edge[0]);
				vector<size_t> sorted = topologySort(adjacency_list, n);
				for (const size_t vertex : sorted) {
					set<int> new_ancestors;
					for (const int neighbour : adjacency_list[vertex])
						new_ancestors.insert(adjacency_list[neighbour].begin(), adjacency_list[neighbour].end());
					adjacency_list[vertex].insert(new_ancestors.begin(), new_ancestors.end());
				}

				vector<vector<int>> ancestors(n);
				for (size_t i = 0; i < n; ++i)
					ancestors[i].insert(ancestors[i].end(), adjacency_list[i].begin(), adjacency_list[i].end());
				return ancestors;
			}

			vector<size_t> topologySort(const vector<set<int>>& adjacency_list, const size_t size) {
				vector<int> visited(size);
				stack<size_t> vertexes;
				vector<size_t> sorted;
				for (size_t i = 0; i < size; ++i)
					if (visited[i] == 0) {
						vertexes.push(i);
						while (!vertexes.empty()) {
							size_t vertex = vertexes.top();
							if (visited[vertex] == 2) {
								vertexes.pop();
								continue;
							}
							if (visited[vertex] == 1) {
								visited[vertex] = 2;
								sorted.push_back(vertex);
								vertexes.pop();
								continue;
							}
							visited[vertex] = 1;
							for (const int neighbour : adjacency_list[vertex])
								if (visited[neighbour] == 0)
									vertexes.push(neighbour);
						}
					}
				return sorted;
			}
		};
	}

	namespace task_2196 {
		/*
		* https://leetcode.com/create-binary-tree-from-descriptions/description/
		*/
		class Solution {
		public:
			TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
				map<int, pair<TreeNode*, bool>> nodes;
				for (const auto& desc : descriptions) {
					auto parent = nodes.find(desc[0]);
					if (parent == nodes.end())
						parent = nodes.insert({ desc[0] , {new TreeNode(desc[0]), true} }).first;
					auto child = nodes.find(desc[1]);
					if (child == nodes.end())
						child = nodes.insert({ desc[1] , {new TreeNode(desc[1]), false} }).first;
					else
						child->second.second = false;

					if (desc[2])
						parent->second.first->left = child->second.first;
					else
						parent->second.first->right = child->second.first;
				}
				for (const auto& [key, value] : nodes)
					if (value.second)
						return value.first;
				return nullptr;
			}
		};
	}

	namespace task_2206 {
		/*
		* https://leetcode.com/problems/divide-array-into-equal-pairs/description/
		*/
		class Solution {
		public:
			bool divideArray(vector<int>& nums) {
				unordered_set<int> unpaired;
				for (int num : nums) {
					if (unpaired.contains(num))
						unpaired.erase(num);
					else
						unpaired.insert(num);
				}

				return unpaired.empty();
			}

			bool divideArray_sort(vector<int>& nums) {
				sort(nums.begin(), nums.end());
				const size_t size = nums.size();
				for (size_t i = 0; i < size; i += 2)
					if (nums[i] != nums[i + 1])
						return false;

				return true;
			}
		};
	}

	namespace task_2220 {
		/*
		* https://leetcode.com/problems/minimum-bit-flips-to-convert-number/description/
		*/
		class Solution {
		public:
			int minBitFlips(int start, int goal) {
				int count = 0;
				start ^= goal;
				while (start != 0)
				{
					count += start & 1;
					start >>= 1;
				}
				return count;
			}
		};
	}

	namespace task_2226 {
		/*
		* https://leetcode.com/problems/maximum-candies-allocated-to-k-children/description/
		*/
		class Solution {
		public:
			int maximumCandies(vector<int>& candies, long long k) {
				long long sum = 0;
				for (const int candy : candies)
					sum += candy;
				int l = 0, r = min((long long)INT32_MAX, (sum / k) + 1);

				while (r - l > 1) {
					int count = (r + l) / 2;
					sum = 0;

					for (const int candy : candies)
						sum += candy / count;

					if (sum >= k)
						l = count;
					else
						r = count;
				}
				return l;
			}
		};
	}

	namespace task_2257 {
		/*
		* https://leetcode.com/problems/defuse-the-bomb/description/
		*/
		class Solution {
		public:
			int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
				vector<vector<int>> map(m, vector<int>(n)); // 1 - wall, 2 - gurd horiz, 4 - guard vertical
				for (const vector<int>& wall : walls)
					map[wall[0]][wall[1]] = 1;

				for (const vector<int>& guard : guards) {
					int x = guard[0], y = guard[1];
					map[x][y] |= 6;
					for (int j = y + 1; j < n && (map[x][j] & 3) == 0; ++j)
						map[x][j] |= 2;
					for (int j = y - 1; j > -1 && (map[x][j] & 3) == 0; --j)
						map[x][j] |= 2;
					for (int i = x + 1; i < m && (map[i][y] & 5) == 0; ++i)
						map[i][y] |= 4;
					for (int i = x - 1; i > -1 && (map[i][y] & 5) == 0; --i)
						map[i][y] |= 4;
				}

				int count = 0;
				for (const vector<int>& row : map)
					for (const int value : row)
						if (value == 0)
							++count;
				return count;
			}
		};
	}

	namespace task_2270 {
		/*
		* https://leetcode.com/problems/number-of-ways-to-split-array/description/
		*/
		class Solution {
		public:
			int waysToSplitArray__leetcode(vector<int>& nums) {
				// Keep track of sum of elements on left and right sides
				long long leftSum = 0, rightSum = 0;

				// Initially all elements are on right side
				for (int num : nums) {
					rightSum += num;
				}

				int count = 0;
				// Try each possible split position
				for (int i = 0; i < nums.size() - 1; i++) {
					// Move current element from right to left side
					leftSum += nums[i];
					rightSum -= nums[i];

					// Check if this creates a valid split
					if (leftSum >= rightSum) {
						count++;
					}
				}

				return count;
			}
		};
	}

	namespace task_2275 {
		/*
		* https://leetcode.com/problems/find-if-array-can-be-sorted/description/
		*/
		class Solution {
		public:
			int largestCombination(vector<int>& candidates) {
				size_t size = candidates.size(), size_bits = 24;
				vector<int> count_bits(size_bits);
				for (int n : candidates)
					for (size_t i = 0; n > 0; n >>= 1, ++i)
						count_bits[i] += n & 1;

				int max_bits = 0;
				for (int count : count_bits)
					max_bits = max(max_bits, count);
				return max_bits;
			}
		};
	}

	namespace task_2285 {
		/*
		* https://leetcode.com/problems/find-center-of-star-graph/description/
		*/
		class Solution {
		public:
			long long maximumImportance(int n, vector<vector<int>>& roads) {
				vector<int> degree(n);
				for (const vector<int>& road : roads) {
					++degree[road[0]];
					++degree[road[1]];
				}
				sort(degree.begin(), degree.end());
				long long res = 0;
				for (long long i = 0; i < n; ++i)
					res += (i + 1) * degree[i];
				return res;
			}
		};
	}

	namespace task_2290 {
		/*
		* https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/description/
		*/
		class Solution {
		public:
			size_t m, n;

			int minimumObstacles(vector<vector<int>>& grid) {
				m = grid.size(), n = grid[0].size();
				vector<unordered_set<int>> adjacency_void(2);
				for (size_t i = 0; i < m; ++i)
					for (size_t j = 0; j < n; ++j)
						if (grid[i][j] == 0) {
							adjacency_void.push_back(unordered_set<int>());
							feel_void(grid, adjacency_void.back(), adjacency_void.size() - 1, i, j);
						}

				if (grid[m - 1][n - 1] == 2)
					return 0;

				vector<int> visited_vertex(m * n);
				vector<int> visited_void(adjacency_void.size());
				visited_void[2] = 1;
				int length = 1, goal = grid[m - 1][n - 1];
				queue<int> q;
				for (int vertex : adjacency_void[2]) {
					visited_vertex[vertex] = 1;
					q.push(vertex);
				}

				while (true) {
					size_t size = q.size();
					for (size_t k = 0; k < size; ++k)
					{
						int vertex = q.front(), neighbour;
						q.pop();
						size_t i = vertex / n, j = vertex % n;

						if (i + 1 < m) {
							neighbour = (i + 1) * n + j;
							if (grid[i + 1][j] == 1 && visited_vertex[neighbour] == 0) {
								visited_vertex[neighbour] = 1;
								q.push(neighbour);
							}
							else if (visited_void[grid[i + 1][j]] == 0) {
								visited_void[grid[i + 1][j]] = 1;
								if (grid[i + 1][j] == goal)
									return length;
								for (int vertex : adjacency_void[grid[i + 1][j]]) {
									if (visited_vertex[vertex] == 0) {
										visited_vertex[vertex] = 1;
										q.push(vertex);
									}
								}
							}
						}
						if (i > 0) {
							neighbour = (i - 1) * n + j;
							if (grid[i - 1][j] == 1 && visited_vertex[neighbour] == 0) {
								visited_vertex[neighbour] = 1;
								q.push(neighbour);
							}
							else if (visited_void[grid[i - 1][j]] == 0) {
								visited_void[grid[i - 1][j]] = 1;
								if (grid[i - 1][j] == goal)
									return length;
								for (int vertex : adjacency_void[grid[i - 1][j]]) {
									if (visited_vertex[vertex] == 0) {
										visited_vertex[vertex] = 1;
										q.push(vertex);
									}
								}
							}
						}
						if (j + 1 < n) {
							neighbour = i * n + j + 1;
							if (grid[i][j + 1] == 1 && visited_vertex[neighbour] == 0) {
								visited_vertex[neighbour] = 1;
								q.push(neighbour);
							}
							else if (visited_void[grid[i][j + 1]] == 0) {
								visited_void[grid[i][j + 1]] = 1;
								if (grid[i][j + 1] == goal)
									return length;
								for (int vertex : adjacency_void[grid[i][j + 1]]) {
									if (visited_vertex[vertex] == 0) {
										visited_vertex[vertex] = 1;
										q.push(vertex);
									}
								}
							}
						}
						if (j > 0) {
							neighbour = i * n + j - 1;
							if (grid[i][j - 1] == 1 && visited_vertex[neighbour] == 0) {
								visited_vertex[neighbour] = 1;
								q.push(neighbour);
							}
							else if (visited_void[grid[i][j - 1]] == 0) {
								visited_void[grid[i][j - 1]] = 1;
								if (grid[i][j - 1] == goal)
									return length;
								for (int vertex : adjacency_void[grid[i][j - 1]]) {
									if (visited_vertex[vertex] == 0) {
										visited_vertex[vertex] = 1;
										q.push(vertex);
									}
								}
							}
						}
					}
					++length;
				}
				return 0;
			}

			void feel_void(vector<vector<int>>& grid,
				unordered_set<int>& voids,
				const int number,
				size_t i, size_t j) {
				grid[i][j] = number;
				queue<pair<size_t, size_t>> q;
				q.push({ i, j });
				while (!q.empty()) {
					i = q.front().first;
					j = q.front().second;
					q.pop();
					if (i + 1 < m) {
						if (grid[i + 1][j] == 0) {
							grid[i + 1][j] = number;
							q.push({ i + 1, j });
						}
						else if (grid[i + 1][j] == 1) {
							voids.insert((i + 1) * n + j);
						}
					}
					if (i > 0) {
						if (grid[i - 1][j] == 0) {
							grid[i - 1][j] = number;
							q.push({ i - 1, j });
						}
						else if (grid[i - 1][j] == 1) {
							voids.insert((i - 1) * n + j);
						}
					}
					if (j + 1 < n) {
						if (grid[i][j + 1] == 0) {
							grid[i][j + 1] = number;
							q.push({ i, j + 1 });
						}
						else if (grid[i][j + 1] == 1) {
							voids.insert(i * n + j + 1);
						}
					}
					if (j > 0) {
						if (grid[i][j - 1] == 0) {
							grid[i][j - 1] = number;
							q.push({ i, j - 1 });
						}
						else if (grid[i][j - 1] == 1) {
							voids.insert(i * n + j - 1);
						}
					}
				}
			}
		};
	}

	namespace task_2300 {
		/*
		* https://leetcode.com/problems/successful-pairs-of-spells-and-potions/description/
		*/
		class Solution {
		public:
			vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
				sort(potions.begin(), potions.end());
				const size_t spells_size = spells.size();
				vector<int> res(spells_size);
				for (size_t i = 0; i < spells_size; i++)
					res[i] = search(potions, spells[i], success);
				return res;
			}

			int search(vector<int>& nums, const long long mult, const long long target) {
				size_t l = 0;
				size_t r = nums.size();
				if (nums[l] * mult >= target)
					return r;
				if (nums[r - 1] * mult < target)
					return 0;

				while (r - l > 1) {
					size_t i = (r + l) >> 1;
					if (nums[i] * mult >= target)
						r = i;
					else
						l = i;
				}
				return nums.size() - r;
			}
		};
	}

	namespace task_2302 {
		/*
		* https://leetcode.com/problems/count-subarrays-with-score-less-than-k/description/
		*/
		class Solution {
		public:
			long long countSubarrays(vector<int>& nums, long long k) {
				const size_t size = nums.size();
				long long sum = 0, count = 0;
				for (size_t i = 0, j = 0; i < size; ++i) {
					sum += nums[i];
					for (; sum * (i + 1 - j) >= k; ++j)
						sum -= nums[j];
					count += i + 1 - j;
				}
				return count;
			}
		};
	}

	namespace task_2326 {
		/*
		* https://leetcode.com/problems/spiral-matrix-iv/description/
		*/
		class Solution {
		public:
			vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
				int left = 0, right = n, up = 0, down = m;
				vector<vector<int>> matrix(m, vector<int>(n, -1));

				while (head) {
					int j = left;
					int i = up;
					for (; head && j < right; j++, head = head->next)
						matrix[i][j] = head->val;

					++i;
					--j;
					for (; head && i < down; i++, head = head->next)
						matrix[i][j] = head->val;

					--i;
					--j;
					for (; head && j >= left; j--, head = head->next)
						matrix[i][j] = head->val;

					--i;
					++j;
					for (; head && i > up; i--, head = head->next)
						matrix[i][j] = head->val;

					++left;
					++up;
					--right;
					--down;
				}

				return matrix;
			}
		};
	}

	namespace task_2331 {
		/*
		* https://leetcode.com/problems/evaluate-boolean-binary-tree/description/
		*/
		class Solution {
		public:
			bool evaluateTree(TreeNode* root) {
				if (root->val == 2) return evaluateTree(root->left) || evaluateTree(root->right);
				if (root->val == 3) return evaluateTree(root->left) && evaluateTree(root->right);
				return root->val;
			}
		};
	}

	namespace task_2337 {
		/*
		* https://leetcode.com/problems/move-pieces-to-obtain-a-string/description/
		*/
		class Solution {
		public:
			bool canChange(string start, string target) {
				size_t size = start.size(), i = 0, j = 0;
				for (; i < size; ++i, ++j) {
					for (; i < size && start[i] == '_'; ++i) {}
					for (; j < size && target[j] == '_'; ++j) {}
					if (i == size)
						return j == size;
					if (j == size ||
						start[i] != target[j] ||
						start[i] == 'L' && i < j ||
						start[i] == 'R' && i > j)
						return false;
				}
				for (; j < size && target[j] == '_'; ++j) {}
				return j == size;
			}
		};
	}

	namespace task_2338 {
		/*
		* https://leetcode.com/problems/count-the-number-of-ideal-arrays/description/
		*/
		class Solution {
		public:
			static const int MOD = 1e9 + 7, MAX_N = 1e4 + 10, MAX_P = 15;  // There are up to 15 prime factors
			int c[MAX_N + MAX_P][MAX_P + 1];
			vector<int> ps[MAX_N];  // List of prime factor counts
			int sieve[MAX_N];	   // Minimum prime factor

			Solution() {
				if (c[0][0]) {
					return;
				}
				for (int i = 2; i < MAX_N; i++) {
					if (sieve[i] == 0) {
						for (int j = i; j < MAX_N; j += i) {
							sieve[j] = i;
						}
					}
				}
				for (int i = 2; i < MAX_N; i++) {
					int x = i;
					while (x > 1) {
						int p = sieve[x];
						int cnt = 0;
						while (x % p == 0) {
							x /= p;
							cnt++;
						}
						ps[i].push_back(cnt);
					}
				}
				c[0][0] = 1;
				for (int i = 1; i < MAX_N + MAX_P; i++) {
					c[i][0] = 1;
					for (int j = 1; j <= min(i, MAX_P); j++) {
						c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
					}
				}
			}

			int idealArrays(int n, int maxValue) {
				long long ans = 0;
				for (int x = 1; x <= maxValue; x++) {
					long long mul = 1;
					for (int p : ps[x]) {
						mul = mul * c[n + p - 1][p] % MOD;
					}
					ans = (ans + mul) % MOD;
				}
				return ans;
			}
		};
	}

	namespace task_2342 {
		/*
		* https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/description/
		*/
		class Solution {
		public:
			int maximumSum(vector<int>& nums) {
				int digit_sums[82] = {}; // vector<int> digit_sums(82);
				int max_sum = -1;
				for (const int num : nums) {
					int digit_sum = 0, n = num;
					while (n != 0) {
						digit_sum += n % 10;
						n /= 10;
					}
					if (digit_sums[digit_sum] == 0) {
						digit_sums[digit_sum] = num;
					}
					else {
						max_sum = max(max_sum, digit_sums[digit_sum] + num);
						digit_sums[digit_sum] = max(digit_sums[digit_sum], num);
					}
				}
				return max_sum;
			}
		};
	}

	namespace task_2349 {
		/*
		* https://leetcode.com/problems/design-a-number-container-system/description/
		*/
		class NumberContainers {
		public:
			unordered_map<int, set<int>> numbers_indexes;
			unordered_map<int, int> index_number;
			NumberContainers() { }

			void change(int index, int number) {
				auto ind = index_number.find(index);
				if (ind == index_number.end()) {
					numbers_indexes[number].insert(index);
					index_number[index] = number;
				}
				else if (ind->second != number) {
					auto old_number = numbers_indexes.find(ind->second);
					old_number->second.erase(index);
					if (old_number->second.size() == 0)
						numbers_indexes.erase(old_number);
					numbers_indexes[number].insert(index);
					index_number[index] = number;
				}
			}

			int find(int number) {
				auto _number = numbers_indexes.find(number);
				return _number == numbers_indexes.end() ? -1 : *_number->second.begin();
			}
		};
	}

	namespace task_2359 {
		/*
		* https://leetcode.com/problems/find-closest-node-to-given-two-nodes/description/
		*/
		class Solution {
		public:
			int closestMeetingNode(vector<int>& edges, int node1, int node2) {
				if (node1 == node2)
					return node1;
				const int size = edges.size();
				int meet_point = size;

				queue<int> queue1;
				queue<int> queue2;
				queue1.push(node1);
				queue2.push(node2);
				vector<int> visited(size);
				visited[node1] = 1;
				visited[node2] = 2;
				int count_odd = 0, count_even = 0;
				while ((!queue1.empty() || !queue2.empty()) && meet_point == size) {
					int q1_size = queue1.size(), q2_size = queue2.size();
					for (int i = 0; i < q1_size; ++i) {
						int vertex = edges[queue1.front()];
						queue1.pop();
						if (vertex == -1)
							continue;
						if (visited[vertex] == 0) {
							visited[vertex] = 1;
							queue1.push(vertex);
						}
						else if (visited[vertex] == 2) {
							meet_point = min(meet_point, vertex);
						}
					}
					for (int i = 0; i < q2_size; ++i) {
						int vertex = edges[queue2.front()];
						queue2.pop();
						if (vertex == -1)
							continue;
						if (visited[vertex] == 0) {
							visited[vertex] = 2;
							queue2.push(vertex);
						}
						else if (visited[vertex] == 1) {
							meet_point = min(meet_point, vertex);
						}
					}
				}

				return meet_point == size ? -1 : meet_point;
			}
		};
	}

	namespace task_2364 {
		/*
		* https://leetcode.com/problems/count-number-of-bad-pairs/description/
		*/
		class Solution {
		public:
			long long countBadPairs(vector<int>& nums) {
				long long badPairs = 0;
				unordered_map<int, int> diffCount;

				for (int i = 0; i < nums.size(); ++i) {
					int diff = i - nums[i];
					int goodPairsCount = diffCount[diff];
					badPairs += i - goodPairsCount;
					diffCount[diff] = goodPairsCount + 1;
				}

				return badPairs;
			}
		};
	}

	namespace task_2375 {
		/*
		* https://leetcode.com/problems/construct-smallest-number-from-di-string/description/
		*/
		class Solution {
		public:
			string smallestNumber__leetcode(string pattern) {
				int patternLength = pattern.length();
				int maxSoFar = 0, currMax = 0, temp;
				vector<int> arrD(patternLength + 1, 0);
				for (int patternIndex = patternLength - 1; patternIndex >= 0;
					patternIndex--) {
					if (pattern[patternIndex] == 'D')
						arrD[patternIndex] = arrD[patternIndex + 1] + 1;
				}

				string result = "";

				for (int position = 0; position <= patternLength; position++) {
					if (pattern[position] == 'I') {

						maxSoFar++;
						result += '0' + maxSoFar;

						maxSoFar = max(maxSoFar, currMax);

						currMax = 0;
					}
					else {
						temp = 1 + maxSoFar + arrD[position];
						result += '0' + temp;

						currMax = max(currMax, temp);
					}
				}

				return result;
			}
		};
	}

	namespace task_2379 {
		/*
		* https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/description/
		*/
		class Solution {
		public:
			int minimumRecolors(string blocks, int k) {
				int count_w = 0, count_min = k;
				const size_t size = blocks.size();
				for (size_t i = 0; i < k; ++i)
					if (blocks[i] == 'W')
						++count_w;
				count_min = count_w;
				for (size_t i = k; i < size; ++i) {
					if (blocks[i] == 'W')
						++count_w;
					if (blocks[i - k] == 'W')
						--count_w;
					count_min = min(count_min, count_w);
				}
				return count_min;
			}
		};
	}

	namespace task_2381 {
		/*
		* https://leetcode.com/problems/shifting-letters-ii/description/
		*/
		class Solution {
		public:
			string shiftingLetters(string s, vector<vector<int>>& shifts) {
				int n = s.size();
				vector<int> diffArray(
					n, 0);  // Initialize a difference array with all elements set to 0.

				for (auto shift : shifts) {
					if (shift[2] == 1) {        // If direction is forward (1):
						diffArray[shift[0]]++;  // Increment at the start index to
												// indicate a forward shift.
						if (shift[1] + 1 < n) {
							diffArray[shift[1] +
								1]--;  // Decrement at the end+1 index to stop the
									   // effect of the shift.
						}
					}
					else {                    // If direction is backward (0):
						diffArray[shift[0]]--;  // Decrement at the start index to
												// indicate a backward shift.
						if (shift[1] + 1 < n) {
							diffArray[shift[1] +
								1]++;  // Increment at the end+1 index to stop the
									   // effect of the shift.
						}
					}
				}

				string result(n, ' ');
				int numberOfShifts = 0;

				for (int i = 0; i < s.size(); i++) {
					numberOfShifts = (numberOfShifts + diffArray[i]) %
						26;  // Update cumulative shifts, keeping within
							 // the alphabet range.
					if (numberOfShifts < 0)
						numberOfShifts +=
						26;  // Ensure `numberOfShifts` is non-negative.

				// Calculate the new character by shifting `s[i]`
					result[i] = 'a' + (s[i] - 'a' + numberOfShifts) % 26;
				}

				return result;
			}
		};
	}

	namespace task_2384 {
		/*
		* https://leetcode.com/problems/largest-palindromic-number/
		*/
		class Solution {
		public:
			string largestPalindromic(string num) { // 56.96%-42.16%
				vector<int> counts('9' - '0' + 1);
				for (const char c : num)
					++counts[c - '0'];
				string maxx_odd;
				string res;
				for (size_t i = 0; i < 10; ++i)
					if (counts[i] & 1)
						maxx_odd = '0' + i;
				for (int i = 9; i >= 0; --i)
					res += string(counts[i] >> 1, '0' + i);

				if (res.size() > 0 && res[0] == '0')
					return maxx_odd.size() == 0 ? "0" : maxx_odd;
				string rev = res;
				reverse(rev.begin(), rev.end());
				return maxx_odd.size() == 0 ? res + rev : res + maxx_odd + rev;
			}

			string largestPalindromic2(string num) {
				vector<string> nums('9' - '0' + 1);
				for (const char c : num)
					nums[c - '0'].push_back(c);
				string res;
				for (int i = 9; i >= 0; --i)
					if (nums[i].size() & 1) {
						res = '0' + i;
						break;
					}

				int max_not_empty = 9;
				for (; max_not_empty > 0; --max_not_empty)
					if (nums[max_not_empty].size() > 1)
						break;
				if (max_not_empty == 0)
					return res.size() == 0 ? "0" : res;

				for (string& str : nums) {
					str.erase(str.size() >> 1);
					res = str + res + str;
				}

				return res;;
			}
		};
	}

	namespace task_2392
	{
		/*
		* https://leetcode.com/problems/build-a-matrix-with-conditions/description/
		*/
		class Solution {
		public:
			vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
				++k;
				auto rowOrder = topologySort(getAdjacencyList(rowConditions, k), k);
				if (rowOrder.empty())
					return {};
				auto colOrder = topologySort(getAdjacencyList(colConditions, k), k);
				if (colOrder.empty())
					return {};
				vector<pair<size_t, size_t>> values(k);
				--k;
				for (size_t i = 0; i < k; i++) {
					values[rowOrder[i]].first = i;
					values[colOrder[i]].second = i;
				}
				vector<vector<int>> matrix(k, vector<int>(k));
				++k;
				for (size_t i = 1; i < k; i++)
					matrix[values[i].first][values[i].second] = i;
				return matrix;
			}

			vector<vector<int>> getAdjacencyList(const vector<vector<int>>& edges, const size_t size) {
				vector<vector<int>> adjacency_list(size);
				for (const vector<int>& edge : edges)
					adjacency_list[edge[0]].push_back(edge[1]);
				return adjacency_list;
			}

			vector<int> topologySort(const vector<vector<int>>& adjacency_list, const size_t size) {
				vector<int> visited(size);
				stack<size_t> vertexes;
				vector<int> sorted;
				for (size_t i = 1; i < size; ++i)
					if (visited[i] == 0) {
						vertexes.push(i);
						while (!vertexes.empty()) {
							size_t vertex = vertexes.top();
							if (visited[vertex] == 2) {
								vertexes.pop();
								continue;
							}
							if (visited[vertex] == 1) {
								visited[vertex] = 2;
								sorted.push_back(vertex);
								vertexes.pop();
								continue;
							}
							visited[vertex] = 1;
							for (const int neighbour : adjacency_list[vertex]) {
								if (visited[neighbour] == 1)
									return {};
								if (visited[neighbour] == 0)
									vertexes.push(neighbour);
							}
						}
					}
				reverse(sorted.begin(), sorted.end());
				return sorted;
			}
		};
	}

	namespace task_2401 {
		/*
		* https://leetcode.com/problems/longest-nice-subarray/description/
		*/
		class Solution {
		public:
			int longestNiceSubarray(vector<int>& nums) {
				int max_len = 1;
				int size = nums.size();
				int acc = nums[0];
				int j = 0;
				for (int i = 1; i < size; i++) {
					if (acc & nums[i]) {
						acc = nums[i];
						for (j = i - 1; j >= 0 && (nums[j] & acc) == 0; --j)
							acc |= nums[j];
						++j;
					}
					else
						acc |= nums[i];
					max_len = max(max_len, i - j + 1);
				}
				return max_len;
			}

			int longestNiceSubarrayBitMap(vector<int>& nums) {
				int res = 1;
				int start = 0, end = 0;
				int bMap[31] = { 0 }; // Binary frequency Map

				while (end < nums.size()) {
					bool flag = false;

					// Storing the binary representation of the current number
					for (int i = 0; i < 31; i++) {
						if (nums[end] & (1 << i)) {
							bMap[i]++;

							if (bMap[i] > 1)
								flag = true;
						}
					}

					// Check if any bit is repeating
					while (flag) {
						int num = nums[start];

						for (int i = 0; i < 31; i++) {
							if (num & (1 << i))
								--bMap[i];
						}

						bool f = false;
						for (int i = 0; i < 31; i++) {
							if (bMap[i] > 1)
								f = true;
						}

						start++;
						if (!f)
							flag = false;
					}
					res = max(res, end - start + 1);
					end++;
				}
				return res;
			}
		};
	}

	namespace task_2404 {
		/*
		* https://leetcode.com/problems/most-frequent-even-element/
		*/
		class Solution {
		public:
			int mostFrequentEven(vector<int>& nums) {
				unordered_map<int, int> map;
				for (int n : nums)
					if ((n & 1) == 0)
						++map[n];
				if (map.size() == 0)
					return -1;
				int count = 0, num = INT_MAX;
				for (const auto& [key, value] : map) {
					if (count < value) {
						count = value;
						num = key;
					}
					else if (count == value)
						num = min(num, key);
				}
				return num;
			}
		};
	}

	namespace task_2406 {
		/*
		* https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/description/
		*/
		class Solution {
		public:
			int minGroups(vector<vector<int>>& intervals) {
				priority_queue<int, vector<int>, greater<int>> intervals_ends;
				sort(intervals.begin(), intervals.end());
				size_t count_groups = 0;
				for (const vector<int>& interval : intervals) {
					while (!intervals_ends.empty() && intervals_ends.top() < interval[0])
						intervals_ends.pop();
					intervals_ends.push(interval[1]);
					count_groups = max(count_groups, intervals_ends.size());
				}
				return count_groups;
			}
		};
	}

	namespace task_2415 {
		/*
		* https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/description/
		*/
		class Solution {
		public:
			TreeNode* reverseOddLevels(TreeNode* root) {
				queue<TreeNode*> queue;
				queue.push(root);
				deque<TreeNode*> deque;
				int size;
				bool level = false;
				while (!queue.empty()) {
					size = queue.size();
					if (level) {
						for (int i = 0; i < size; ++i) {
							auto node = queue.front();
							queue.pop();
							if (node->left) {
								queue.push(node->left);
								queue.push(node->right);
							}
						}
					}
					else {
						for (int i = 0; i < size; ++i) {
							auto node = queue.front();
							queue.pop();
							if (node->left) {
								queue.push(node->left);
								queue.push(node->right);
								deque.push_back(node->left);
								deque.push_back(node->right);

							}
						}
						while (!deque.empty()) {
							auto front = deque.front(), back = deque.back();
							swap(front->val, back->val);
							deque.pop_front();
							deque.pop_back();
						}
					}
					level = !level;
				}
				return root;
			}
		};
	}

	namespace task_2416 {
		/*
		* https://leetcode.com/problems/sum-of-prefix-scores-of-strings/description/
		*/
		class Solution {
		public:
			class TrieNode {
			public:
				unordered_map<char, TrieNode*> children;
				int count = 0;
			};

			vector<int> sumPrefixScores(vector<string>& words) {
				size_t size = words.size(), length;
				vector<int> scores;
				unordered_map<string, int> prefix_map;
				TrieNode* root = new TrieNode(), * node;

				for (const string& word : words) {
					node = root;
					for (const char c : word) {
						if (node->children.find(c) == node->children.end())
							node->children[c] = new TrieNode();
						node = node->children[c];
						++node->count;
					}
				}

				for (const string& word : words) {
					length = word.size() + 1;
					int score = 0;
					node = root;
					for (const char c : word) {
						node = node->children[c];
						score += node->count;
					}
					scores.push_back(score);
				}

				return scores;
			}

			vector<int> sumPrefixScoresHash(vector<string>& words) { // Time Limit Exceeded
				size_t size = words.size(), length;
				vector<int> scores;
				unordered_map<string, int> prefix_map;

				for (const string& word : words) {
					length = word.size();
					string prefix;
					for (size_t i = 0; i < length; i++) {
						prefix.push_back(word[i]);
						if (auto it = prefix_map.find(prefix); it != prefix_map.end())
							++it->second;
						else
							prefix_map[prefix] = 1;
					}
				}

				for (const string& word : words) {
					length = word.size() + 1;
					int score = 0;
					string prefix;
					for (size_t i = 0; i < length; i++) {
						prefix.push_back(word[i]);
						score += prefix_map[prefix];
					}
					scores.push_back(score);
				}

				return scores;
			}
		};
	}

	namespace task_2418 {
		/*
		* https://leetcode.com/problems/sort-the-people/description/
		*/
		class Solution {
		public:
			vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
				const size_t size = heights.size();
				for (size_t i = 0; i < size - 1; i++) {
					int max_height = heights[i];
					size_t max_ind = i;
					for (size_t j = i + 1; j < size; j++)
						if (max_height < heights[j]) {
							max_height = heights[j];
							max_ind = j;
						}
					swap(heights[i], heights[max_ind]);
					swap(names[i], names[max_ind]);
				}
				return names;
			}
		};
	}

	namespace task_2419 {
		/*
		* https://leetcode.com/path-sum/description/
		*/
		class Solution {
		public:
			int longestSubarray(vector<int>& nums) {
				int max_el = nums[0], max_len = 0;
				int size = nums.size();
				for (int i = 0; i < size; ++i) {
					if (max_el < nums[i]) {
						max_el = nums[i];
						max_len = 0;
					}
					if (max_el == nums[i]) {
						int j = i + 1;
						for (; j < size && max_el == nums[j]; ++j) {}
						max_len = max(max_len, j - i);
						i = j - 1;
					}
				}
				return max_len;
			}
		};
	}

	namespace task_2425 {
		/*
		* https://leetcode.com/problems/bitwise-xor-of-all-pairings/description/
		*/
		class Solution {
			int xorAllNums__leetcode(vector<int>& nums1, vector<int>& nums2) {
				// Initialize XOR results for both arrays
				int xor1 = 0;
				int xor2 = 0;

				// Get lengths of both arrays
				int len1 = nums1.size();
				int len2 = nums2.size();

				// If nums2 length is odd, each element in nums1 appears odd times in
				// final result
				if (len2 % 2 != 0) {
					for (int num : nums1) {
						xor1 ^= num;
					}
				}

				// If nums1 length is odd, each element in nums2 appears odd times in
				// final result
				if (len1 % 2 != 0) {
					for (int num : nums2) {
						xor2 ^= num;
					}
				}

				// Return XOR of both results
				return xor1 ^ xor2;
			}
		};
	}

	namespace task_2429 {
		/*
		* https://leetcode.com/problems/minimize-xor/description/
		*/
		class Solution {
			int minimizeXor__leetcode(int num1, int num2) {
				int result = 0;

				int targetSetBitsCount = 0; // __builtin_popcount(num2);
				int setBitsCount = 0;
				int currentBit = 31;  // Start from the most significant bit.

				// While x has fewer set bits than num2
				while (setBitsCount < targetSetBitsCount) {
					// If the current bit of num1 is set or we must set all remaining
					// bits in result
					if (isSet(num1, currentBit) ||
						(targetSetBitsCount - setBitsCount > currentBit)) {
						setBit(result, currentBit);
						setBitsCount++;
					}
					currentBit--;  // Move to the next bit.
				}

				return result;
			}

		private:
			// Helper function to check if the given bit position in x is set (1).
			bool isSet(int x, int bit) { return x & (1 << bit); }

			// Helper function to set the given bit position in x to 1.
			void setBit(int& x, int bit) { x |= (1 << bit); }
		};
	}



	namespace task_2433 {
		/*
		* https://leetcode.com/problems/find-the-original-array-of-prefix-xor/description/
		*/
		class Solution {
		public:
			vector<int> findArray(vector<int>& pref) {
				int acc_xor = 0;
				for (int& val : pref) {
					val ^= acc_xor;
					acc_xor ^= val;
				}
				return pref;
			}

			vector<int> findArray2(vector<int>& pref) {
				for (int i = pref.size() - 1; i > 0; i--) pref[i] ^= pref[i - 1];
				return pref;
			}
		};
	}

	namespace task_2434 {
		/*
		* https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/description/
		*/
		class Solution {
		public:
			string robotWithString__leetcode(string s) {
				unordered_map<char, int> cnt;
				for (char c : s) {
					cnt[c]++;
				}

				stack<char> stk;
				string res;
				char minCharacter = 'a';
				for (char c : s) {
					stk.emplace(c);
					cnt[c]--;
					while (minCharacter != 'z' && cnt[minCharacter] == 0) {
						minCharacter++;
					}
					while (!stk.empty() && stk.top() <= minCharacter) {
						res.push_back(stk.top());
						stk.pop();
					}
				}

				return res;
			}
		};
	}

	namespace task_2444 {
		/*
		* https://leetcode.com/problems/count-subarrays-with-fixed-bounds/description/
		*/
		class Solution {
		public:
			long long countSubarrays(vector<int>& nums, int minK, int maxK) {
				int n = nums.size();
				long long ans = 0;
				int lastInvalid = -1; // last index where nums[i] < minK or nums[i] > maxK
				int lastMin = -1;     // last index where nums[i] == minK
				int lastMax = -1;     // last index where nums[i] == maxK

				for (int i = 0; i < n; ++i) {
					if (nums[i] < minK || nums[i] > maxK) {
						lastInvalid = i;
						lastMin = -1;
						lastMax = -1;
						continue;
					}
					if (nums[i] == minK)
						lastMin = i;
					if (nums[i] == maxK)
						lastMax = i;

					int validStart = min(lastMin, lastMax);
					if (validStart > lastInvalid) {
						ans += (validStart - lastInvalid);
					}
				}
				return ans;
			}
		};
	}

	namespace task_2458 {
		/*
		* https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/description
		*/
		class Solution {
		public:
			vector<int> treeQueries2(TreeNode* root, vector<int>& queries) {
				int n = 100000;
				// Vectors to store node depths and heights
				vector<int> nodeDepths(n + 1, 0);
				vector<int> subtreeHeights(n + 1, 0);

				// Vectors to store the first and second largest heights at each level
				vector<int> firstLargestHeight(n + 1, 0);
				vector<int> secondLargestHeight(n + 1, 0);

				// Perform DFS to calculate depths and heights
				dfs(root, 0, nodeDepths, subtreeHeights, firstLargestHeight,
					secondLargestHeight);

				vector<int> results;
				results.reserve(queries.size());

				// Process each query
				for (int queryNode : queries) {
					int nodeLevel = nodeDepths[queryNode];

					// Calculate the height of the tree after removing the query node
					if (subtreeHeights[queryNode] == firstLargestHeight[nodeLevel]) {
						results.push_back(nodeLevel + secondLargestHeight[nodeLevel] -
							1);
					}
					else {
						results.push_back(nodeLevel + firstLargestHeight[nodeLevel] -
							1);
					}
				}

				return results;
			}

		private:
			// Depth-first search to calculate node depths and subtree heights
			int dfs(TreeNode* node, int level, vector<int>& nodeDepths,
				vector<int>& subtreeHeights, vector<int>& firstLargestHeight,
				vector<int>& secondLargestHeight) {
				if (node == nullptr) return 0;

				nodeDepths[node->val] = level;

				// Calculate the height of the current subtree
				int leftHeight = dfs(node->left, level + 1, nodeDepths, subtreeHeights,
					firstLargestHeight, secondLargestHeight);
				int rightHeight =
					dfs(node->right, level + 1, nodeDepths, subtreeHeights,
						firstLargestHeight, secondLargestHeight);
				int currentHeight = 1 + max(leftHeight, rightHeight);

				subtreeHeights[node->val] = currentHeight;

				// Update the largest and second largest heights at the current level
				if (currentHeight > firstLargestHeight[level]) {
					secondLargestHeight[level] = firstLargestHeight[level];
					firstLargestHeight[level] = currentHeight;
				}
				else if (currentHeight > secondLargestHeight[level]) {
					secondLargestHeight[level] = currentHeight;
				}

				return currentHeight;
			}

			vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
				int n = 10, m = queries.size(), height = 0, parent;

				vector<int> answers(n + 1);
				vector<int> depth(n + 1);
				vector<vector<int>> nodes(n + 1); // parent, height, child-leftm child-right
				nodes[0] = { 0, 0, 0, 0 };
				queue<TreeNode*> queue; // node
				queue.push(root);
				while (!queue.empty()) {
					size_t size = queue.size();
					for (size_t i = 0; i < size; ++i) {
						TreeNode* node = queue.front();
						queue.pop();
						if (n < node->val) {
							for (; n < node->val; ++n)
								depth.push_back(0);
						}
						depth[node->val] = height;
						if (node->left)
							queue.push(node->left);
						if (node->right)
							queue.push(node->right);
					}
					++height;
				}

				/*
				stack<TreeNode*> stack; // node
				stack.push(root); \
					while (!stack.empty()) {
						TreeNode* node = stack.top();
						stack.pop();
						if (node->left && node->right) {

						}
						parent = queue.front().second;
						queue.pop();
						if (n < node->val) {
							for (; n < node->val; ++n)
								nodes.push_back({});
						}
						nodes[node->val] = { parent, height, node->left ? node->left->val : 0, node->right ? node->right->val : 0 };
						if (node->left)
							queue.push({ node->left , node->val });
						if (node->right)
							queue.push({ node->right , node->val });
					}

				stack<TreeNode*> stack; // node
				stack.push(root);\
				while (!stack.empty()) {
					for (size_t i = 0; i < size; ++i) {
						TreeNode* node = queue.front().first;
						parent = queue.front().second;
						queue.pop();
						if (n < node->val) {
							for (; n < node->val; ++n)
								nodes.push_back({});
						}
						nodes[node->val] = { parent, height, node->left ? node->left->val : 0, node->right ? node->right->val : 0 };
						if (node->left)
							queue.push({ node->left , node->val });
						if (node->right)
							queue.push({ node->right , node->val });
					}
				}

				for (const int query : queries) {

				}
				*/
				return {};
			}

			void push(vector<vector<int>>& nodes, TreeNode* node, int& n, const int parent, const int height) {
			}
		};
	}

	namespace task_2460 {
		/*
		* https://leetcode.com/problems/apply-operations-to-an-array/description/
		*/
		class Solution {
		public:
			vector<int> applyOperations(vector<int>& nums) {
				const size_t size = nums.size();
				for (size_t i = 1; i < size; ++i) {
					if (nums[i - 1] == nums[i]) {
						nums[i - 1] <<= 1;
						nums[i] = 0;
					}
				}

				size_t nulls = 0;

				for (size_t i = 0; i < size; ++i) {
					if (nums[i] != 0) {
						nums[nulls] = nums[i];
						++nulls;
					}
				}

				for (nulls; nulls < size; ++nulls)
					nums[nulls] = 0;

				return nums;
			}
		};
	}

	namespace task_2461 {
		/*
		* https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/description/
		*/
		class Solution {
		public:
			long long maximumSubarraySum(vector<int>& nums, int k) {
				int size = nums.size();
				long long sum = 0, max_sum = 0;
				unordered_map<int, int> set;
				for (int i = 0; i < k; ++i) {
					sum += nums[i];
					++set[nums[i]];
				}
				if (set.size() == k)
					max_sum = sum;

				for (int i = k; i < size; ++i) {
					sum += nums[i] - nums[i - k];
					++set[nums[i]];
					auto it = set.find(nums[i - k]);
					--it->second;
					if (it->second == 0)
						set.erase(it);
					if (set.size() == k)
						max_sum = max(sum, max_sum);
				}

				return max_sum;
			}
		};
	}

	namespace task_2467 {
		/*
		* https://leetcode.com/problems/most-profitable-path-in-a-tree/description/
		*/
		class Solution {
		public:
			vector<vector<int>> tree;
			vector<int> distanceFromBob;
			int n;

			int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount) {
				n = amount.size();
				tree.resize(n, vector<int>());

				// Form tree with edges
				for (vector<int> edge : edges) {
					tree[edge[0]].push_back(edge[1]);
					tree[edge[1]].push_back(edge[0]);
				}
				distanceFromBob.resize(n);
				return findPaths(0, 0, 0, bob, amount);
			}

			// Depth-first Search
			int findPaths(int sourceNode, int parentNode, int time, int bob,
				vector<int>& amount) {
				int maxIncome = 0, maxChild = INT_MIN;

				// Find the node distances from Bob
				if (sourceNode == bob)
					distanceFromBob[sourceNode] = 0;
				else
					distanceFromBob[sourceNode] = n;
				for (int adjacentNode : tree[sourceNode]) {
					if (adjacentNode != parentNode) {
						maxChild = max(maxChild, findPaths(adjacentNode, sourceNode,
							time + 1, bob, amount));
						distanceFromBob[sourceNode] =
							min(distanceFromBob[sourceNode],
								distanceFromBob[adjacentNode] + 1);
					}
				}
				// Alice reaches the node first
				if (distanceFromBob[sourceNode] > time) maxIncome += amount[sourceNode];

				// Alice and Bob reach the node at the same time
				else if (distanceFromBob[sourceNode] == time)
					maxIncome += amount[sourceNode] / 2;

				// Return max income of leaf node
				if (maxChild == INT_MIN)
					return maxIncome;
				else
					return maxIncome + maxChild;
			}
		};
	}

	namespace task_2466 {
		/*
		* https://leetcode.com/problems/count-ways-to-build-good-strings/description/
		*/
		class Solution {
		public:
			int countways(int length, int low, int high, int zero, int one, vector<int>& dp) {
				if (length > high) return 0;

				if (dp[length] != -1) return dp[length];

				dp[length] = 0;

				if (length >= low) dp[length] = 1;

				dp[length] = (dp[length] + countways(length + zero, low, high, zero, one, dp)) % (int)(1e9 + 7);
				dp[length] = (dp[length] + countways(length + one, low, high, zero, one, dp)) % (int)(1e9 + 7);

				return dp[length];
			}

			int countGoodStrings__leetcode(int low, int high, int zero, int one) {
				int mod = 1e9 + 7;
				vector<int> dp(high + 1, 0);
				dp[0] = 1;

				int count = 0;
				for (int i = 0; i <= high; i++) {
					if (i - zero >= 0) dp[i] = (dp[i] + dp[i - zero]) % mod;
					if (i - one >= 0) dp[i] = (dp[i] + dp[i - one]) % mod;
					if (i >= low) count = (count + dp[i]) % mod;
				}

				return count;
			}
		};
	}

	namespace task_2471 {
		/*
		* https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/description/
		*/
		class Solution {
		public:
			int minimumOperations(TreeNode* root) {
				queue<TreeNode*> queue;
				vector<int> vec;
				size_t size;
				int count = 0;
				while (!queue.empty()) {
					size = queue.size();
					for (size_t i = 0; i < size; ++i) {
						auto node = queue.front();
						queue.pop();
						if (node->left) {
							queue.push(node->left);
							vec.push_back(node->left->val);
						}
						if (node->right) {
							queue.push(node->right);
							vec.push_back(node->right->val);
						}
					}
					size = vec.size();
					for (size_t i = 0; i < size; ++i) {
						int min_value = vec[i];
						size_t ind;
						for (size_t j = i + 1; j < size; ++j) {
							if (min_value < vec[j]) {
								min_value = vec[j];
								ind = j;
							}
						}
						if (vec[i] != min_value) {
							swap(vec[i], vec[ind]);
							++count;
						}
						vec.clear();
					}
				}
				return count;
			}
		};
	}

	namespace task_2463 {
		/*
		* https://leetcode.com/problems/minimum-total-distance-traveled/description/
		*/
		class Solution {
		public:
			vector<queue<int>> factory_robots;
			int r_i;
			int f_i;
			int free_left_fac;
			long long way_len;

			long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
				set<int> robots(robot.begin(), robot.end());
				int size_factories = factory.size();
				for (int i = 0; i < size_factories; ++i) {
					if (factory[i][1] == 0) {
						factory.erase(factory.begin() + i);
						--i;
						--size_factories;
						continue;
					}

					if (robots.contains(factory[i][0])) {
						--factory[i][1];
						robots.erase(factory[i][0]);
						if (factory[i][1] == 0) {
							factory.erase(factory.begin() + i);
							--i;
							--size_factories;
						}
					}
				}
				sort(factory.begin(), factory.end());
				robot = vector<int>(robots.begin(), robots.end());
				int size_robots = robot.size();

				factory_robots = vector<queue<int>>(size_factories);
				r_i = 0, f_i = 0, free_left_fac = 0, way_len = 0;

				for (; r_i < size_robots; ++r_i) {
					for (; f_i < size_factories && factory[f_i][0] < robot[r_i]; ++f_i, ++free_left_fac) {}

					if (f_i < size_factories &&
						(free_left_fac == 0 || factory[f_i][0] - robot[r_i] < robot[r_i] - factory[f_i - 1][0])) {
						way_len += factory[f_i][0] - robot[r_i];
						factory_robots[f_i].push(r_i);
						--factory[f_i][1];
						if (factory[f_i][1] == 0)
							++f_i;
						continue;
					}

					if (factory[f_i - 1][1] > 0) {
						--f_i;
						way_len += robot[r_i] - factory[f_i][0];
						factory_robots[f_i].push(r_i);
						--factory[f_i][1];
						if (factory[f_i][1] == 0) {
							--free_left_fac;
							++f_i;
						}
						continue;
					}

					if (f_i == size_factories || try_shift_robot(robot, factory)) {
						shift_robot(robot, factory);
					}
					else {
						way_len += factory[f_i][0] - robot[r_i];
						factory_robots[f_i].push(r_i);
						--factory[f_i][1];
						if (factory[f_i][1] == 0)
							++f_i;
						continue;
					}
				}
				return way_len;
			}

			bool try_shift_robot(const vector<int>& robot, const vector<vector<int>>& factory) {
				int f = f_i - 1, r = r_i;
				long long dif_way = 0;
				for (; factory[f][1] == 0; --f) {
					dif_way += abs(robot[r] - factory[f + 1][0]) - abs(robot[r] - factory[f][0]);
					r = factory_robots[f].front();
				}
				dif_way += abs(robot[r] - factory[f + 1][0]) - abs(robot[r] - factory[f][0]);
				return dif_way > 0;
			}

			void shift_robot(const vector<int>& robot, vector<vector<int>>& factory) {
				int f = f_i - 1, r = r_i;
				for (; factory[f][1] == 0; --f) {
					factory_robots[f].push(r);
					way_len += abs(robot[r] - factory[f][0]);

					r = factory_robots[f].front();
					factory_robots[f].pop();
					way_len -= abs(robot[r] - factory[f][0]);
				}
				factory_robots[f].push(r);
				way_len += abs(robot[r] - factory[f][0]);
				--factory[f][1];
				if (factory[f][1] == 0)
					--free_left_fac;
			}
		};
	}

	namespace task_2486 {
		/*
		* https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/description/
		*/
		class Solution {
		public:
			int appendCharacters(string s, string t) {
				size_t size_s = s.size(), size_t_ = t.size(), j = 0;
				for (size_t i = 0; i < size_s; ++i) {
					if (s[i] == t[j]) {
						++j;
						if (j == size_t_)
							return 0;
					}
				}
				return size_t_ - j;
			}
		};
	}

	namespace task_2487
	{
		/*
		* https://leetcode.com/problems/remove-nodes-from-linked-list/description/
		*/
		class Solution {
		public:
			ListNode* removeNodes(ListNode* head) {
				stack<int> stack;
				while (head) {
					stack.push(head->val);
					head = head->next;
				}
				int max_val = stack.top();
				int val;
				stack.pop();
				head = new ListNode(max_val);
				while (!stack.empty()) {
					val = stack.top();
					stack.pop();
					if (val >= max_val)
						head = new ListNode(val, head);
					max_val = max(max_val, val);
				}
				return head;
			}
		};
	}

	namespace task_2490 {
		/*
		* https://leetcode.com/problems/circular-sentence/description/
		*/
		class Solution {
		public:
			bool isCircularSentence(string sentence) {
				size_t size = sentence.size();
				if (sentence[0] != sentence[size - 1])
					return false;
				for (size_t i = sentence.find(' '); i != string::npos; i = sentence.find(' ', i + 1))
					if (sentence[i - 1] != sentence[i + 1])
						return false;
				return true;
			}
		};
	}

	namespace task_2491 {
		/*
		* https://leetcode.com/problems/problems/divide-players-into-teams-of-equal-skill/description/
		*/
		class Solution {
		public:
			long long dividePlayers(vector<int>& skill) {
				int size = skill.size(), sum = 0;
				vector<int> counts(1001);
				for (const int n : skill) {
					sum += n;
					++counts[n];
				}
				if ((sum * 2) % size != 0)
					return -1;

				int team_target = (sum * 2) / size;
				long long team_score = 0;
				for (long long i = 1; i < 1001; ++i) {
					if (counts[i] == 0)
						continue;
					if (team_target - i == i) {
						if (counts[i] & 1 == 1)
							return -1;
						team_score += i * i * (counts[i] >> 1);
						counts[i] = 0;
					}
					else {
						if (counts[i] != counts[team_target - i])
							return -1;
						team_score += i * (team_target - i) * counts[i];
						counts[i] = 0;
						counts[team_target - i] = 0;
					}
				}
				return team_score;
			}
		};
	}

	namespace task_2493 {
		/*
		* https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/description/
		*/
		class Solution {
		public:
			int magnificentSets(int n, vector<vector<int>>& edges) {
				++n;
				vector<vector<int>> adjacency_list(n);
				for (const auto& edge : edges) {
					adjacency_list[edge[0]].push_back(edge[1]);
					adjacency_list[edge[1]].push_back(edge[0]);
				}

				return countGroups(adjacency_list, n);
			}


			int countGroups(const vector<vector<int>>& adjacency_list, const size_t size) {
				vector<int> visited(size);
				vector<int> visited_dist(size);
				queue<size_t> vertexes;
				int count = 0;
				for (size_t i = 1; i < size; ++i)
					if (visited[i] == 0) {
						int half = 1, next_half = 2, connected_count = 0;
						vertexes.push(i);
						visited[i] = half;
						while (!vertexes.empty()) {
							size_t q_size = vertexes.size();
							for (size_t j = 0; j < q_size; ++j) {
								size_t vertex = vertexes.front();
								connected_count = max(connected_count, getDist(adjacency_list, visited_dist, vertex, size));
								vertexes.pop();
								for (const int neighbour : adjacency_list[vertex]) {
									if (visited[neighbour] == half)
										return -1;
									if (visited[neighbour] == 0) {
										vertexes.push(neighbour);
										visited[neighbour] = next_half;
									}
								}
							}
							swap(half, next_half);
						}
						count += connected_count;
					}
				return count;
			}

			int getDist(const vector<vector<int>>& adjacency_list, vector<int>& visited, size_t vertex, const size_t size) {
				queue<size_t> vertexes;
				vertexes.push(vertex);
				visited[vertex] = 1;
				int dist = 0;
				while (!vertexes.empty()) {
					++dist;
					size_t q_size = vertexes.size();
					for (size_t j = 0; j < q_size; ++j)
					{
						vertex = vertexes.front();
						vertexes.pop();
						for (const int neighbour : adjacency_list[vertex]) {
							if (visited[neighbour] == 0) {
								vertexes.push(neighbour);
								visited[neighbour] = 1;
							}
						}
					}
				}
				for (size_t i = 1; i < size; ++i)
					visited[i] = 0;
				return dist;
			}
		};

	}

	namespace task_2501 {
		/*
		* https://leetcode.com/problems/longest-square-streak-in-an-array/
		*/
		class Solution {
		public:
			int longestSquareStreak(vector<int>& nums) {
				unordered_set<int> set;
				for (const int num : nums)
					set.insert(num);

				int max_len = -1;
				for (int num : nums) {
					int len = 1;
					while (num < 317 && set.contains(num * num)) {
						++len;
						num *= num;
					}
					if (len > 1)
						max_len = max(max_len, len);
				}
				return max_len;
			}
		};
	}

	namespace task_2503 {
		/*
		* https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/description/
		*/
		class Solution {
		public:
			vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
				int m = grid.size(), n = grid[0].size(), k = queries.size();
				vector<int> answer(k);
				vector<pair<int, int>> sorted_queries(k);
				for (int i = 0; i < k; ++i)
					sorted_queries[i] = { queries[i], i };
				sort(sorted_queries.begin(), sorted_queries.end());

				int i = 0;
				for (; i < k; ++i)
					if (sorted_queries[i].first > grid[0][0])
						break;
					else
						answer[sorted_queries[i].second] = 0;

				if (i == k)
					return answer;
				answer[sorted_queries[i].second] = 1;
				grid[0][0] = 0;
				vector<pair<int, int>> cells_to_check(1, { 0, 0 });
				for (; i < k; ++i) {
					if (i > 0 && sorted_queries[i].first == sorted_queries[i - 1].first) {
						answer[sorted_queries[i].second] = answer[sorted_queries[i - 1].second];
						continue;
					}
					int value = sorted_queries[i].first, points = 0;
					for (int j = 0; j < cells_to_check.size(); ++j) {
						int x = cells_to_check[j].first, y = cells_to_check[j].second;
						bool neighbour_zero = true;
						if (x + 1 < m && grid[x + 1][y] != 0) {
							if (grid[x + 1][y] >= value) {
								neighbour_zero = false;
							}
							else {
								++points;
								grid[x + 1][y] = 0;
								cells_to_check.push_back({ x + 1 , y });
							}
						}
						if (y + 1 < n && grid[x][y + 1] != 0) {
							if (grid[x][y + 1] >= value) {
								neighbour_zero = false;
							}
							else {
								++points;
								grid[x][y + 1] = 0;
								cells_to_check.push_back({ x , y + 1 });
							}
						}
						if (x - 1 > -1 && grid[x - 1][y] != 0) {
							if (grid[x - 1][y] >= value) {
								neighbour_zero = false;
							}
							else {
								++points;
								grid[x - 1][y] = 0;
								cells_to_check.push_back({ x - 1 , y });
							}
						}
						if (y - 1 > -1 && grid[x][y - 1] != 0) {
							if (grid[x][y - 1] >= value) {
								neighbour_zero = false;
							}
							else {
								++points;
								grid[x][y - 1] = 0;
								cells_to_check.push_back({ x , y - 1 });
							}
						}

						if (neighbour_zero) {
							swap(cells_to_check[j], cells_to_check.back());
							cells_to_check.pop_back();
							--j;
						}
					}

					answer[sorted_queries[i].second] += points + (i == 0 ? 0 : answer[sorted_queries[i - 1].second]);
				}

				return answer;
			}
		};
	}

	namespace task_2516 {
		/*
		* https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/description/
		*/
		class Solution {
		public:
			int takeCharacters(string s, int k) {
				if (k == 0)
					return 0;
				vector<int> letters(3);
				int size = s.size(), left = 0, right = size - 1, count_full = 0;
				for (; left < size && count_full != 3; ++left)
					if (++letters[s[left] - 'a'] == k)
						++count_full;
				if (count_full != 3)
					return -1;
				int min_letters = left;
				--left;

				while (left != -1) {
					for (; left != -1 && count_full == 3; --left)
						if (--letters[s[left] - 'a'] < k)
							--count_full;

					min_letters = min(min_letters, left + 1 + size - right);

					for (; count_full != 3; --right)
						if (++letters[s[right] - 'a'] == k)
							++count_full;
				}
				return min(min_letters, left + size - right);
			}
		};
	}

	namespace task_2523 {
		/*
		* https://leetcode.com/problems/closest-prime-numbers-in-range/description/
		*/
		class Solution {
		public:
			vector<int> closestPrimes(int left, int right) {
				if (left == 1)
					++left;
				vector<int> primes = generatePrimes(++right);
				int n1 = nextPrime(primes, left), n2 = nextPrime(primes, n1 + 1), dist = INT32_MAX, min_n1 = -1, min_n2 = -1;
				while (n2 < right) {
					if (n2 - n1 < dist) {
						min_n1 = n1;
						min_n2 = n2;
						dist = n2 - n1;
					}
					n1 = n2;
					n2 = nextPrime(primes, n2 + 1);
				}
				return { min_n1, min_n2 };
			}

			vector<int> generatePrimes(int to) {
				vector<int> primes{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199 };
				for (int n = 211; n < to; ++n) {
					int square = sqrt(n) + 1;
					bool is_prime = true;
					for (size_t i = 0; primes[i] < square; ++i) {
						if (n % primes[i] == 0) {
							is_prime = false;
							break;
						}
					}
					if (is_prime)
						primes.push_back(n);
				}
				return primes;
			}

			int nextPrime(const vector<int>& primes, int n) {
				for (;; ++n) {
					int square = sqrt(n) + 1;
					bool is_prime = true;
					for (size_t i = 0; primes[i] < square; ++i) {
						if (n % primes[i] == 0) {
							is_prime = false;
							break;
						}
					}
					if (is_prime)
						return n;
				}
				return n;
			}
		};
	}

	namespace task_2529 {
		/*
		* https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/description/
		*/
		class Solution {
		public:
			int maximumCount(vector<int>& nums) {
				const size_t size = nums.size();
				size_t l = 0;
				size_t r = size;
				if (nums[l] > 0)
					return size;
				if (nums[l] == 0)
					r = l;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] >= 0)
						r = i;
					else
						l = i;
				}
				if (r == size)
					return r;
				size_t count_neg = r;
				l = r - 1;
				r = size;

				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (nums[i] > 0)
						r = i;
					else
						l = i;
				}

				return max(count_neg, size - r);
			}
		};
	}

	namespace task_2530 {
		/*
		* https://leetcode.com/problems/two-sum/
		*/
		class Solution {
		public:
			long long maxKelements(vector<int>& nums, int k) {
				long long score = 0;
				priority_queue<int> queue;
				for (const int n : nums)
					queue.push(n);
				for (size_t i = 0; i < k; i++) {
					int value = queue.top();
					queue.pop();
					score += value;
					queue.push(value / 3 + (value % 3 == 0 ? 0 : 1));
				}
				return score;
			}
		};
	}

	namespace task_2537 {
		/*
		* https://leetcode.com/problems/count-the-number-of-good-subarrays/description/
		*/
		class Solution {
		public:
			long long countGood(vector<int>& nums, int k) {
				size_t size = nums.size(), j = 0, i = 0;
				unordered_map<int, int> nums_count;
				long long count = 0;
				int pairs = 0;
				for (size_t i = 0; i < size; ++i) {
					pairs += nums_count[nums[i]]++;
					if (pairs >= k) {
						for (; pairs >= k; ++j)
							pairs -= --nums_count[nums[j]];
						count += j;
						pairs += nums_count[nums[--j]]++; // return pairs to maintain good subsequence
					}
				}
				return count;
			}
		};
	}

	namespace task_2542 {
		/*
		* https://leetcode.com/problems/problems/maximum-subsequence-score/description/
		*/
		class Solution {
		public:
			long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {

			}
		};
	}

	namespace task_2551 {
		/*
		* https://leetcode.com/problems/put-marbles-in-bags/description/
		*/
		class Solution {
		public:
			long long putMarbles(vector<int>& weights, int k) {
				size_t size = weights.size();
				for (size_t i = 1; i < size; ++i)
					weights[i - 1] += weights[i];
				weights.pop_back();
				sort(weights.begin(), weights.end());
				long long res = 0;
				--size;
				for (int i = 1; i < k; ++i)
					res += weights[size - i] - weights[i - 1];
				return res;
			}
		};
	}

	namespace task_2554 {
		/*
		* https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/description
		*/
		class Solution {
		public:
			int maxCount(vector<int>& banned, int n, int maxSum) {
				sort(banned.begin(), banned.end());
				int sum = 0, count = 0;
				size_t size = banned.size(), i = 0;
				++n;
				for (int j = 1; j < n; ++j) {
					for (; i < size && j > banned[i]; ++i) {}
					if (i < size && j == banned[i])
						continue;
					sum += j;
					if (sum > maxSum)
						return count;
					++count;
				}
				return count;
			}
		};
	}

	namespace task_2558 {
		/*
		* https://leetcode.com/problems/take-gifts-from-the-richest-pile/description
		*/
		class Solution {
		public:
			long long pickGifts(vector<int>& gifts, int k) {
				priority_queue<int> queue(gifts.begin(), gifts.end());
				for (int i = 0; i < k; ++i) {
					int value = queue.top();
					queue.pop();
					queue.push(floor(sqrt(value)));
				}
				long long sum = 0;
				while (!queue.empty()) {
					sum += queue.top();
					queue.pop();
				}
				return sum;
			}
		};
	}

	namespace task_2559 {
		/*
		* https://leetcode.com/problems/count-vowel-strings-in-ranges/description/
		*/
		class Solution {
		public:
			vector<int> vowelStrings(vector<string>& words,
				vector<vector<int>>& queries) {
				vector<int> ans(queries.size());
				unordered_set<char> vowels{ 'a', 'e', 'i', 'o', 'u' };
				vector<int> prefixSum(words.size());
				int sum = 0;
				for (int i = 0; i < words.size(); i++) {
					string currentWord = words[i];
					if (vowels.count(currentWord[0]) &&
						vowels.count(currentWord[currentWord.size() - 1])) {
						sum++;
					}
					prefixSum[i] = sum;
				}

				for (int i = 0; i < queries.size(); i++) {
					vector<int> currentQuery = queries[i];
					ans[i] =
						prefixSum[currentQuery[1]] -
						(currentQuery[0] == 0 ? 0 : prefixSum[currentQuery[0] - 1]);
				}

				return ans;
			}
		};
	}

	namespace task_2560 {
		/*
		* https://leetcode.com/problems/house-robber-iv/description/
		*/
		class Solution {
		public:
			int minCapability(vector<int>& nums, int k) {
				const size_t size = nums.size();
				if (size == 1)
					return nums[0];
				if (size == 2)
					return min(nums[0], nums[1]);
				if (size == 3) {
					if (k == 1)
						return min(nums[0], min(nums[1], nums[2]));
					else
						return max(nums[0], nums[2]);
				}

				int l = INT32_MAX, r = 1;
				for (const int num : nums) {
					l = min(l, num);
					r = max(r, num);
				}
				++r;

				while (r - l > 1) {
					int max_value = (r + l) / 2;
					int sum_3 = nums[0] < max_value ? 1 : 0;
					int sum_2 = nums[1] < max_value ? 1 : 0;
					int sum_1 = sum_3 + (nums[2] < max_value ? 1 : 0);
					int sum = 0;
					for (size_t i = 3; i < size; i++) {
						sum = max(sum_2, sum_3) + (nums[i] < max_value ? 1 : 0);
						sum_3 = sum_2;
						sum_2 = sum_1;
						sum_1 = sum;
					}
					sum = max(sum_1, sum_2);

					if (sum >= k)
						r = max_value;
					else
						l = max_value;
				}
				return l;
			}
		};
	}

	namespace task_2563 {
		/*
		* https://leetcode.com/problems/count-the-number-of-fair-pairs/description/
		*/
		class Solution {
		public:
			long long countFairPairs(vector<int>& nums, int lower, int upper) {
				long long count = 0;
				int size = nums.size(), to = size - 1, from = size - 1;
				sort(nums.begin(), nums.end());

				for (int i = 0; i < size; ++i) {
					for (; from >= 0 && nums[i] + nums[from] >= lower; --from) {}
					for (; to >= 0 && nums[i] + nums[to] > upper; --to) {}
					count += to - from;
					if (i > from && i <= to)
						--count;
				}
				return count >> 1;
			}

			long long countFairPairs_leetcode(vector<int>& nums, int lower, int upper) {
				sort(nums.begin(), nums.end());
				return lower_bound(nums, upper + 1) - lower_bound(nums, lower);
			}
			// count pairs less upper - count pairs less lower

			long long lower_bound(vector<int>& nums, int value) {
				int left = 0, right = nums.size() - 1;
				long long result = 0;
				while (left < right) {
					int sum = nums[left] + nums[right];
					// If sum is less than value, add the size of window to result and
					// move to the next index.
					if (sum < value) {
						result += (right - left);
						left++;
					}
					else {
						// Otherwise, shift the right pointer backwards, until we get a
						// valid window.
						right--;
					}
				}
				return result;
			}
		};
	}

	namespace task_2570 {
		/*
		* https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/description/
		*/
		class Solution {
		public:
			vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
				const size_t size1 = nums1.size(), size2 = nums2.size();
				size_t i1 = 0, i2 = 0;
				vector<vector<int>> res;
				while (i1 < size1 && i2 < size2) {
					if (nums1[i1][0] < nums2[i2][0]) {
						res.push_back(nums1[i1]);
						++i1;
					}
					else if (nums1[i1][0] > nums2[i2][0]) {
						res.push_back(nums2[i2]);
						++i2;
					}
					else {
						res.push_back({ nums1[i1][0] , nums1[i1][1] + nums2[i2][1] });
						++i1;
						++i2;
					}
				}
				for (; i1 < size1; ++i1)
					res.push_back(nums1[i1]);
				for (; i2 < size2; ++i2)
					res.push_back(nums2[i2]);
				return res;
			}
		};
	}

	namespace task_2577 {
		/*
		* https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/description/
		*/
		class Solution {
		public:
			int minimumTime__leetcode(vector<vector<int>>& grid) {
				if (grid[0][1] > 1 && grid[1][0] > 1)
					return -1;

				int rows = grid.size(), cols = grid[0].size();
				// Possible movements: down, up, right, left
				vector<vector<int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
				vector<vector<bool>> visited(rows, vector<bool>(cols, false));

				// Priority queue stores {time, row, col}
				// Ordered by minimum time to reach each cell
				priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
				pq.push({ grid[0][0], 0, 0 });

				while (!pq.empty()) {
					auto curr = pq.top();
					pq.pop();
					int time = curr[0], row = curr[1], col = curr[2];

					// Check if reached target
					if (row == rows - 1 && col == cols - 1)
						return time;

					// Skip if cell already visited
					if (visited[row][col])
						continue;
					visited[row][col] = true;

					// Try all four directions
					for (auto& d : directions) {
						int nextRow = row + d[0], nextCol = col + d[1];
						if (!isValid(visited, nextRow, nextCol))
							continue;

						// Calculate the wait time needed to move to next cell
						int waitTime =
							((grid[nextRow][nextCol] - time) % 2 == 0) ? 1 : 0;
						int nextTime = max(grid[nextRow][nextCol] + waitTime, time + 1);
						pq.push({ nextTime, nextRow, nextCol });
					}
				}
				return -1;
			}

			// Checks if given cell coordinates are valid and unvisited
			bool isValid(vector<vector<bool>>& visited, int row, int col) {
				return row >= 0 && col >= 0 && row < visited.size() &&
					col < visited[0].size() && !visited[row][col];
			}
		};
	}

	namespace task_2579 {
		/*
		* https://leetcode.com/problems/count-total-number-of-colored-cells/description/
		*/
		class Solution {
		public:
			long long coloredCells(int n) {
				return  1 + (long long)n * (n - 1) * 2;
			}

			long long coloredCells__slow(int n) {
				long long count = 1;
				--n;
				for (int i = 0; i < n; ++i)
					count += (i << 2) + 4;
				return count;
			}
		};
	}

	namespace task_2582 {
		/*
		* https://leetcode.com/problems/pass-the-pillow/description/
		*/
		class Solution {
		public:
			int passThePillow(int n, int time) {
				time %= (n - 1) << 1;
				return time < n ? 1 + time : 2 * n - time - 1;
			}
		};
	}

	namespace task_2583 {
		/*
		* https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/description
		*/
		class Solution {
		public:
			long long kthLargestLevelSum(TreeNode* root, int k) {
				queue<TreeNode*> queue;
				queue.push(root);
				vector<long long> sums;
				size_t level_size = 1;
				while (level_size != 0) {
					long long sum = 0;
					for (size_t i = 0; i < level_size; ++i) {
						root = queue.front();
						queue.pop();
						sum += root->val;
						if (root->left)
							queue.push(root->left);
						if (root->right)
							queue.push(root->right);
					}
					sums.push_back(sum);
					level_size = queue.size();
				}
				if (sums.size() < k)
					return -1;
				sort(sums.begin(), sums.end());
				return sums[sums.size() - k];
			}
		};
	}

	namespace task_2593 {
		/*
		* https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/description
		*/
		class Solution {
		public:
			long long findScore(vector<int>& nums) {
				priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
				int size = nums.size();
				for (int i = 0; i < size; ++i) {
					queue.push(make_pair(nums[i], i));
					nums[i] = 0;
				}
				long long sum = 0;
				while (!queue.empty()) {
					auto top = queue.top();
					queue.pop();
					if (nums[top.second] == 1)
						continue;
					sum += top.first;
					nums[top.second] = 1;
					if (top.second > 0)
						nums[top.second - 1] = 1;
					if (top.second + 1 < size)
						nums[top.second + 1] = 1;
				}
				return sum;
			}
		};
	}

	namespace task_2594 {
		/*
		* https://leetcode.com/problems/minimum-time-to-repair-cars/description/
		*/
		class Solution {
		public:
			int long long repairCars(vector<int>& ranks, int cars) {
				int min_rank = INT32_MAX, max_rank = 0;
				for (const int rank : ranks) {
					max_rank = max(max_rank, rank);
					min_rank = min(min_rank, rank);
				}
				long long car_per_mech = cars / ranks.size();
				long long l = car_per_mech * car_per_mech * min_rank - 1;
				long long r = (car_per_mech + 1) * (car_per_mech + 1) * max_rank;


				while (r - l > 1) {
					long long time = (r + l) / 2;
					int count = cars;
					for (const int rank : ranks)
						count -= floor(sqrt(time / rank));

					if (count <= 0)
						r = time;
					else
						l = time;
				}
				return r;
			}
		};
	}

	namespace task_2597 {
		/*
		* https://leetcode.com/problems/the-number-of-beautiful-subsets/description/
		*/
		class SolutionFast { // 75% time; 6% memory
		public:
			size_t size;
			int _k;

			int beautifulSubsets(vector<int>& nums, int k) {
				size = nums.size();
				vector<vector<int>> mods(k, vector<int>());
				vector<int> count_in_mods(k, 1);
				_k = k;

				for (auto el : nums)
					mods[el % k].push_back(el);
				for (size_t i = 0; i < k; i++)
					if (!mods[i].empty()) {
						sort(mods[i].begin(), mods[i].end());
						count_in_mods[i] = beautifulSubsetsRec(mods[i], 0, -k);
					}

				int res = 1;
				for (auto mod : count_in_mods)
					res *= mod;
				return res - 1;
			}

			int beautifulSubsetsRec(const vector<int>& nums, int from, int last_chosen) {
				int count_subsets = 1;
				for (size_t i = from; i < nums.size(); i++)
					if (nums[i] - last_chosen != _k)
						count_subsets += beautifulSubsetsRec(nums, i + 1, nums[i]);
				return count_subsets;
			}
		};

		class SolutionMemorySave { // 49% time; 90% memory
		public:
			size_t size;
			int _k;
			int count_chosen;
			vector<int> chosen;

			int beautifulSubsets(vector<int>& nums, int k) {
				size = nums.size();
				_k = k;
				count_chosen = 0;
				chosen = vector<int>(size);
				return beautifulSubsetsReq(nums, 0) - 1;
			}

			int beautifulSubsetsReq(const vector<int>& nums, int from) {
				int count_subsets = 1;
				++count_chosen;
				for (size_t i = from; i < size; i++) {
					bool can_add = true;
					for (size_t j = 0; j + 1 < count_chosen; j++)
						if (abs(chosen[j] - nums[i]) == _k) {
							can_add = false;
							break;
						}
					if (can_add) {
						chosen[count_chosen - 1] = nums[i];
						count_subsets += beautifulSubsetsReq(nums, i + 1);
					}
				}
				--count_chosen;
				return count_subsets;
			}
		};
	}

	namespace task_2601 {
		/*
		* https://leetcode.com/problems/prime-subtraction-operation/description/
		*/
		class Solution {
		public:
			const vector<int> prime_numbers{
				2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
				31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
				73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
				127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
				179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
				233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
				283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
				353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
				419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
				467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
				547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
				607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
				661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
				739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
				811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
				877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
				947, 953, 967, 971, 977, 983, 991, 997 };

			bool primeSubOperation(vector<int>& nums) {
				if (nums[0] > 2)
					nums[0] -= bin_search(nums[0]);
				size_t size = nums.size();
				for (size_t i = 1; i < size; ++i) {
					int dif = nums[i] - nums[i - 1];
					if (dif <= 0)
						return false;
					if (dif > 2)
						nums[i] -= bin_search(dif);
				}
				return true;
			}


			int bin_search(int value) {
				size_t l = 0, r = 168;
				while (r - l > 1) {
					size_t i = (r + l) / 2;
					if (prime_numbers[i] < value)
						l = i;
					else
						r = i;
				}
				return prime_numbers[l];
			}
		};
	}

	namespace task_2641 {
		/*
		* https://leetcode.com/problems/cousins-in-binary-tree-ii/description
		*/
		class Solution {
		public:
			TreeNode* replaceValueInTree(TreeNode* root) {
				root->val = 0;
				int level_sum = 0, next_level_sum = 0, child_sum = 0;

				TreeNode* node;
				queue<TreeNode*> queue;
				if (root->left) {
					root->left->val = 0;
					queue.push(root->left);
				}
				if (root->right) {
					root->right->val = 0;
					queue.push(root->right);
				}
				size_t level_size = queue.size();
				while (level_size != 0) {
					next_level_sum = 0;
					for (size_t i = 0; i < level_size; ++i) {
						node = queue.front();
						queue.pop();
						node->val = level_sum - node->val;
						child_sum = 0;
						if (node->left) {
							child_sum += node->left->val;
							queue.push(node->left);
						}
						if (node->right) {
							child_sum += node->right->val;
							queue.push(node->right);
						}
						if (node->left)
							node->left->val = child_sum;
						if (node->right)
							node->right->val = child_sum;
						next_level_sum += child_sum;
					}
					level_sum = next_level_sum;
					level_size = queue.size();
				}
				return root;
			}
		};
	}

	namespace task_2643 {
		/*
		* https://leetcode.com/problems/row-with-maximum-ones/description/
		*/
		class Solution {
		public:
			vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
				int max_count = 0;
				int max_row = 0;

				for (size_t i = 0; i < mat.size(); i++) {
					int count = 0;
					for (size_t j = 0; j < mat[i].size(); j++)
						if (mat[i][j] == 1)
							++count;
					if (max_count < count) {
						max_count = count;
						max_row = i;
					}
				}
				return { max_row, max_count };
			}
		};
	}

	namespace task_2657 {
		/*
		* https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/description/
		*/
		class Solution {
		public:
			vector<int> findThePrefixCommonArray__leetcode(vector<int>& A, vector<int>& B) {
				int n = A.size();
				vector<int> prefixCommonArray(n), frequency(n + 1, 0);
				int commonCount = 0;

				// Iterate through the elements of both arrays
				for (int currentIndex = 0; currentIndex < n; ++currentIndex) {
					// Increment frequency of current elements in A and B
					// Check if the element in A has appeared before (common in prefix)
					if (++frequency[A[currentIndex]] == 2) ++commonCount;

					// Check if the element in B has appeared before (common in prefix)
					if (++frequency[B[currentIndex]] == 2) ++commonCount;

					// Store the count of common elements for the current prefix
					prefixCommonArray[currentIndex] = commonCount;
				}

				// Return the final array with counts of common elements in each prefix
				return prefixCommonArray;
			}
		};
	}

	namespace task_2658 {
		/*
		* https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/description/
		*/
		class Solution {
		public:
			int findMaxFish(vector<vector<int>>& grid) {
				int m = grid.size(), n = grid[0].size();
				queue<pair<int, int>> queue;
				int count_fish = 0;
				for (int i = 0; i < m; i++) {
					for (int j = 0; j < n; j++) {
						if (grid[i][j] != 0) {
							queue.push({ i, j });
							int sum = grid[i][j];
							grid[i][j] = 0;
							while (!queue.empty()) {
								auto& pos = queue.front();
								if (pos.first + 1 != m && grid[pos.first + 1][pos.second]) {
									sum += grid[pos.first + 1][pos.second];
									grid[pos.first + 1][pos.second] = 0;
									queue.push({ pos.first + 1, pos.second });
								}
								if (pos.second + 1 != n && grid[pos.first][pos.second + 1]) {
									sum += grid[pos.first][pos.second + 1];
									grid[pos.first][pos.second + 1] = 0;
									queue.push({ pos.first, pos.second + 1 });
								}
								if (pos.first - 1 != -1 && grid[pos.first - 1][pos.second]) {
									sum += grid[pos.first - 1][pos.second];
									grid[pos.first - 1][pos.second] = 0;
									queue.push({ pos.first - 1, pos.second });
								}
								if (pos.second - 1 != -1 && grid[pos.first][pos.second - 1]) {
									sum += grid[pos.first][pos.second - 1];
									grid[pos.first][pos.second - 1] = 0;
									queue.push({ pos.first, pos.second - 1 });
								}
								queue.pop();
							}
							count_fish = max(count_fish, sum);
						}
					}
				}
				return count_fish;
			}
		};
	}

	namespace task_2661 {
		/*
		* https://leetcode.com/problems/first-completely-painted-row-or-column/description/
		*/
		class Solution {
		public:
			int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
				const size_t m = mat.size(), n = mat[0].size(), size = m * n;
				vector<int> rows(m, n), columns(n, m);
				vector<vector<int>> positions(size + 1, vector<int>(2));
				for (size_t i = 0; i < m; ++i) {
					for (size_t j = 0; j < n; ++j) {
						positions[mat[i][j]][0] = i;
						positions[mat[i][j]][1] = j;
					}
				}
				for (size_t i = 0; true; ++i) {
					--rows[positions[arr[i]][0]];
					--columns[positions[arr[i]][1]];
					if (rows[positions[arr[i]][0]] == 0 || columns[positions[arr[i]][1]] == 0)
						return i;
				}
				return 0;
			}
		};
	}

	namespace task_2678 {
		/*
		* https://leetcode.com/problems/number-of-senior-citizens/description/
		*/
		class Solution {
		public:
			int countSeniors(vector<string>& details) {
				int count = 0;
				for (const string& str : details)
					if (str[11] > '6' || str[11] == '6' && str[12] > '0')
						++count;
				return count;
			}
		};
	}

	namespace task_2683 {
		/*
		* https://leetcode.com/problems/neighboring-bitwise-xor/description/
		*/
		class Solution {

			bool doesValidArrayExist__leetcode(vector<int>& derived) {
				int XOR = 0;
				for (auto element : derived) {
					XOR = XOR ^ element;
				}
				return XOR == 0;
			}
		};
	}

	namespace task_2684 {
		/*
		* https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/description/
		*/
		class Solution {
		public:
			int maxMoves(vector<vector<int>>& grid) {
				size_t row = grid.size(), col = grid[0].size();
				vector<vector<int>> dp(row, vector<int>(col));
				int ans = 0;
				for (size_t j = col - 2; j > 0; --j) {
					for (size_t i = 0; i < row; ++i) {
						int max_steps = 0;
						if (i > 0 && grid[i - 1][j + 1] > grid[i][j])
							max_steps = dp[i - 1][j + 1] + 1;
						if (grid[i][j + 1] > grid[i][j])
							max_steps = max(max_steps, dp[i][j + 1] + 1);
						if (i < row - 1 && grid[i + 1][j + 1] > grid[i][j])
							max_steps = max(max_steps, dp[i + 1][j + 1] + 1);
						dp[i][j] = max_steps;
					}
				}

				for (size_t i = 0; i < row; ++i) {
					if (i > 0 && grid[i - 1][1] > grid[i][0])
						ans = max(ans, dp[i - 1][1] + 1);
					if (grid[i][1] > grid[i][0])
						ans = max(ans, dp[i][1] + 1);
					if (i < row - 1 && grid[i + 1][1] > grid[i][0])
						ans = max(ans, dp[i + 1][1] + 1);
				}
				return ans;
			}
		};
	}

	namespace task_2685 {
		/*
		* https://leetcode.com/problems/count-the-number-of-complete-components/description/
		*/
		class Solution {
		public:
			int countCompleteComponents(int n, vector<vector<int>>& edges) {
				int count = 0;
				vector<vector<int>> adjacency_list(n);
				vector<char> visited(n);
				for (const vector<int>& edge : edges) {
					adjacency_list[edge[0]].push_back(edge[1]);
					adjacency_list[edge[1]].push_back(edge[0]);
				}

				for (int i = 0; i < n; ++i) {
					if (visited[i] == 0) {
						size_t count_vertexes = 0;
						visited[i] = 1;
						queue<int> q;
						q.push(i);
						size_t min_component_degree = adjacency_list[i].size();
						while (!q.empty()) {
							++count_vertexes;
							int vertex = q.front();
							min_component_degree = min(min_component_degree, adjacency_list[vertex].size());
							q.pop();

							for (const int v : adjacency_list[vertex]) {
								if (visited[v] == 0) {
									visited[v] = 1;
									q.push(v);
								}
							}
						}

						if (min_component_degree + 1 == count_vertexes)
							++count;
					}
				}

				return count;
			}
		};
	}

	namespace task_2696 {
		/*
		* https://leetcode.com/problems/minimum-string-length-after-removing-substrings/description/
		*/
		class Solution {
		public:
			int minLength(string s) {
				size_t size = s.size(), i = 1, count_delete = 0;
				stack<char> stack;
				for (const char c : s) {
					if (!stack.empty() &&
						(stack.top() == 'A' && c == 'B' || stack.top() == 'C' && c == 'D'))
						stack.pop();
					else
						stack.push(c);
				}
				return stack.size();
			}
		};
	}

	namespace task_2698 {
		/*
		* https://leetcode.com/problems/text-justification/description/
		*/
		class Solution {
		public:
			bool canPartition(string stringNum, int target) {
				if (stringNum == "" && target == 0) return true;

				if (target < 0) return false;

				for (int index = 0; index < stringNum.size(); index++) {
					string left = stringNum.substr(0, index + 1);
					string right = stringNum.substr(index + 1);
					int leftNum = stoi(left);

					if (canPartition(right, target - leftNum)) return true;
				}
				return false;
			}

			int punishmentNumber(int n) {
				int punishmentNum = 0;

				for (int currentNum = 1; currentNum <= n; currentNum++) {
					int squareNum = currentNum * currentNum;
					if (canPartition(to_string(squareNum), currentNum))
						punishmentNum += squareNum;
				}
				return punishmentNum;
			}
		};
	}

	namespace task_2699 {
		/*
		* https://leetcode.com/problems/n-ary-tree-postorder-traversal/description/
		*/
		class Solution {
		public:
			const int INF = 2e9;

			vector<vector<int>> modifiedGraphEdges(int nodeCount,
				vector<vector<int>>& edges,
				int source, int destination,
				int target) {
				// Step 1: Compute the initial shortest distance from source to
				// destination
				long long currentShortestDistance =
					runDijkstra(edges, nodeCount, source, destination);

				// If the current shortest distance is less than the target, return an
				// empty result
				if (currentShortestDistance < target) return {};

				bool matchesTarget = (currentShortestDistance == target);

				// Step 2: Iterate through each edge to adjust its weight if necessary
				for (vector<int>& edge : edges) {
					// Skip edges that already have a positive weight
					if (edge[2] > 0) continue;

					// Set edge weight to a large value if current distance matches
					// target else set to 1
					edge[2] = matchesTarget ? INF : 1;

					// Step 3: If current shortest distance does not match target
					if (!matchesTarget) {
						// Compute the new shortest distance with the updated edge
						// weight
						long long newDistance =
							runDijkstra(edges, nodeCount, source, destination);
						// If the new distance is within the target range, update edge
						// weight to match target
						if (newDistance <= target) {
							matchesTarget = true;
							edge[2] += target - newDistance;
						}
					}
				}

				// Return modified edges if the target distance is achieved, otherwise
				// return an empty result
				return matchesTarget ? edges : vector<vector<int>>{};
			}

			// Dijkstra's algorithm to find the shortest path distance
			long long runDijkstra(const vector<vector<int>>& edges, int nodeCount,
				int sourceNode, int destinationNode) {
				// Step 1: Initialize adjacency matrix and distance arrays
				vector<vector<long long>> adjMatrix(nodeCount,
					vector<long long>(nodeCount, INF));
				vector<long long> minDistance(nodeCount, INF);
				vector<bool> visited(nodeCount, false);

				// Set the distance to the source node as 0
				minDistance[sourceNode] = 0;

				// Step 2: Fill the adjacency matrix with edge weights
				for (const vector<int>& edge : edges) {
					if (edge[2] != -1) {
						adjMatrix[edge[0]][edge[1]] = edge[2];
						adjMatrix[edge[1]][edge[0]] = edge[2];
					}
				}

				// Step 3: Perform Dijkstra's algorithm
				for (int i = 0; i < nodeCount; ++i) {
					// Find the nearest unvisited node
					int nearestUnvisitedNode = -1;
					for (int j = 0; j < nodeCount; ++j) {
						if (!visited[j] &&
							(nearestUnvisitedNode == -1 ||
								minDistance[j] < minDistance[nearestUnvisitedNode])) {
							nearestUnvisitedNode = j;
						}
					}
					// Mark the nearest node as visited
					visited[nearestUnvisitedNode] = true;

					// Update the minimum distance for each adjacent node
					for (int v = 0; v < nodeCount; ++v) {
						minDistance[v] =
							min(minDistance[v], minDistance[nearestUnvisitedNode] +
								adjMatrix[nearestUnvisitedNode][v]);
					}
				}

				// Return the shortest distance to the destination node
				return minDistance[destinationNode];
			}

			vector<vector<int>> myModifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
				int size = edges.size();
				vector<vector<vector<int>>> adjacency_list(n); // {vertex, dist, index in edges}
				vector<int> isNegative(size);
				for (int i = 0; i < size; ++i)
					if (edges[i][2] == -1)
						isNegative[i] = 1;
					else {
						adjacency_list[edges[i][0]].push_back({ edges[i][1], edges[i][2], i });
						adjacency_list[edges[i][1]].push_back({ edges[i][0], edges[i][2], i });
					}
				auto distances = dijkstraShort(n, adjacency_list, source, destination);
				int dist = distances[destination];
				if (dist < target)
					return {};
				else if (dist == target) {
					for (int i = 0; i < size; ++i)
						if (edges[i][2] == -1)
							edges[i][2] = 1000000001;
					return edges;
				}

				for (int i = 0; i < size; ++i)
					if (edges[i][2] == -1) {
						edges[i][2] = 1;
						adjacency_list[edges[i][0]].push_back({ edges[i][1], edges[i][2], i });
						adjacency_list[edges[i][1]].push_back({ edges[i][0], edges[i][2], i });
					}

				auto res = dijkstra(n, adjacency_list, source, destination);
				dist = target - res.first;
				const auto& path_vertex = res.second.first;
				const auto& path_edge = res.second.second;
				size_t path_size = path_edge.size();
				if (dist > target)
					return {};
				else if (dist == target) {
					for (const int edge : path_edge)
						if (isNegative[edge])
							isNegative[edge] = 2;

					for (int i = 0; i < size; ++i)
						if (isNegative[i] == 1)
							edges[i][2] = 1000000001;
					return edges;
				}

				bool is_not_modified = true;
				for (const int edge : path_edge)
					if (isNegative[edge]) {
						isNegative[edge] = 2;
						if (is_not_modified) {
							edges[edge][2] += target - res.first;
							is_not_modified = false;
						}
					}

				for (int i = 0; i < size; ++i)
					if (isNegative[i] == 1)
						edges[i][2] = 1000000001;
				return edges;
			}

			vector<int> dijkstraShort(
				const int n,
				const vector<vector<vector<int>>>& adjacency_list,
				const int source,
				const int destination) {
				vector<int> distances(n, INT32_MAX);
				priority_queue<pair<int, int>> queue;
				queue.push({ 0, source });
				distances[source] = 0;
				while (!queue.empty()) {
					int dist = -queue.top().first, vertex = queue.top().second;
					queue.pop();
					if (distances[vertex] < dist)
						continue;
					for (const auto& neighbor : adjacency_list[vertex])
						if (distances[neighbor[0]] > dist + neighbor[1]) {
							distances[neighbor[0]] = dist + neighbor[1];
							queue.push({ -dist - neighbor[1] , neighbor[0] });
						}
				}
				return distances;
			}

			pair<int, pair<vector<int>, vector<int>>> dijkstra(
				const int n,
				const vector<vector<vector<int>>>& adjacency_list,
				const int source,
				const int destination) {
				vector<int> distances(n, INT32_MAX);
				vector<int> from_edge(n, -1); // edge number
				vector<int> from_vertex(n, -1); // vertex number
				priority_queue<pair<int, int>> queue;
				queue.push({ 0, source });
				distances[source] = 0;
				while (!queue.empty()) {
					int dist = -queue.top().first, vertex = queue.top().second;
					queue.pop();
					if (distances[vertex] < dist)
						continue;
					if (vertex == destination)
						break;
					for (const auto& neighbor : adjacency_list[vertex])
						if (distances[neighbor[0]] > dist + neighbor[1]) {
							distances[neighbor[0]] = dist + neighbor[1];
							from_edge[neighbor[0]] = neighbor[2];
							from_vertex[neighbor[0]] = vertex;
							queue.push({ -dist - neighbor[1] , neighbor[0] });
						}
				}
				vector<int> path_edge, path_vertex;
				for (int vertex = destination; vertex != source; vertex = from_vertex[vertex]) {
					path_edge.push_back(from_edge[vertex]);
					path_vertex.push_back(from_vertex[vertex]);
				}
				reverse(path_edge.begin(), path_edge.end());
				reverse(path_vertex.begin(), path_vertex.end());
				return { distances[destination], {path_vertex, path_edge} };
			}
		};
	}

	namespace task_2707 {
		/*
		* https://leetcode.com/problems/extra-characters-in-a-string/description/
		*/
		class Solution {
		public:
			int minExtraChar(string s, vector<string>& dictionary) { // 97.13% 97.30%
				size_t size = s.size();
				vector<int> dp(size + 1, size);
				dp[size] = 0;

				for (int i = size - 1; i >= 0; --i) {
					dp[i] = dp[i + 1] + 1;
					for (const string& str : dictionary)
						if (i + str.size() <= size) {
							int j = 0;
							for (; j < str.size() && s[i + j] == str[j]; ++j) {}
							if (j == str.size())
								dp[i] = min(dp[i], dp[i + j]);
						}
				}
				return dp[0];
			}

			class TrieNode { // 82.77% 32.60%
			public:
				unordered_map<char, TrieNode*> children;
				bool is_word;
			};

			int minExtraCharTrie(string s, vector<string>& dictionary) {
				int size = s.size();
				auto root = buildTrie(dictionary);
				vector<int> dp(size + 1, size);
				dp[size] = 0;

				for (int i = size - 1; i >= 0; --i) {
					dp[i] = dp[i + 1] + 1;
					TrieNode* node = root;

					for (int j = i; j < size; ++j) {
						if (node->children.find(s[j]) == node->children.end())
							break;
						node = node->children[s[j]];
						if (node->is_word)
							dp[i] = min(dp[i], dp[j + 1]);
					}
				}
				return dp[0];
			}

			int minExtraCharTrieReq(string s, vector<string>& dictionary) {
				int n = s.length();
				auto root = buildTrie(dictionary);
				unordered_map<int, int> memo;

				function<int(int)> dp = [&](int start) {
					if (start == n) {
						return 0;
					}
					if (memo.count(start)) {
						return memo[start];
					}
					// To count this character as a left over character 
					// move to index 'start + 1'
					int ans = dp(start + 1) + 1;
					TrieNode* node = root;
					for (int end = start; end < n; end++) {
						char c = s[end];
						if (node->children.find(c) == node->children.end()) {
							break;
						}
						node = node->children[c];
						if (node->is_word) {
							ans = min(ans, dp(end + 1));
						}
					}

					return memo[start] = ans;
				};

				return dp(0);
			}

			TrieNode* buildTrie(vector<string>& dictionary) {
				auto root = new TrieNode();
				for (const string& word : dictionary) {
					auto node = root;
					for (const char c : word) {
						if (node->children.find(c) == node->children.end())
							node->children[c] = new TrieNode();
						node = node->children[c];
					}
					node->is_word = true;
				}
				return root;
			}
		};
	}

	namespace task_2751 {
		/*
		* https://leetcode.com/problems/robot-collisions/description/
		*/
		class Solution {
		public:
			vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
				size_t size = positions.size();
				if (size == 1)
					return { healths[0] };
				list<size_t> sorted_positions;
				vector<pair<int, size_t>> pos(size);
				for (size_t i = 0; i < size; ++i)
					pos[i] = { positions[i], i };
				sort(pos.begin(), pos.end());
				for (const pair<int, size_t>& p : pos)
					sorted_positions.push_back(p.second);
				bool hasChanged;
				do {
					hasChanged = false;
					auto left = sorted_positions.begin();
					auto right = next(left);
					while (left != sorted_positions.end() && right != sorted_positions.end()) {
						if (directions[*left] == 'R' && directions[*right] == 'L') {
							if (healths[*left] > healths[*right]) {
								--healths[*left];
								healths[*right] = 0;
								right = sorted_positions.erase(right);
							}
							else if (healths[*left] < healths[*right]) {
								healths[*left] = 0;
								--healths[*right];
								sorted_positions.erase(left);
								--left;
							}
							else {
								healths[*left] = 0;
								healths[*right] = 0;
								sorted_positions.erase(left);
								left = sorted_positions.erase(right);
								right = next(left);
							}
							hasChanged = true;
						}
						else {
							++left;
							++right;
						}
					}
				} while (hasChanged && sorted_positions.size() > 1);
				vector<int> res;
				for (const int h : healths)
					if (h != 0)
						res.push_back(h);
				return res;
			}
		};
	}

	namespace task_2762 {
		/*
		* https://leetcode.com/problems/continuous-subarrays/description
		*/
		class Solution {
		public:
			long long continuousSubarrays(vector<int>& nums) {
				int size = nums.size(), i = 0, j = 0, r = 1;
				long long sum = 1, len, prev_len;
				map<int, int> map{ {nums[0], 1} };
				while (j < size) {
					++j;
					for (; j < size; ++j) {
						++map[nums[j]];
						if (map.rbegin()->first - map.begin()->first > 2)
							break;
					}
					len = j - i;
					prev_len = r - i;
					sum += (len * (len + 1) - prev_len * (prev_len + 1)) / 2;
					r = j;
					for (; i < size && map.rbegin()->first - map.begin()->first > 2; ++i) {
						auto it = map.find(nums[i]);
						--it->second;
						if (it->second == 0)
							map.erase(it);
					}
				}
				return sum;
			}
		};
	}

	namespace task_2779 {
		/*
		* https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/description
		*/
		class Solution {
		public:
			int maximumBeauty(vector<int>& nums, int k) {
				sort(nums.begin(), nums.end());
				int max_len = 1, i = 0, j = 0, size = nums.size();
				k <<= 1;
				for (; i < size; ++i) {
					for (; nums[i] - nums[j] > k; ++j) {}
					max_len = max(max_len, i - j + 1);
				}
				return max_len;
			}
		};
	}

	namespace task_2780 {
		/*
		* https://leetcode.com/problems/minimum-index-of-a-valid-split/description/
		*/
		class Solution {
		public:
			int minimumIndex(vector<int>& nums) {
				unordered_map<int, int> count_num;
				const int size = nums.size();
				int dominant = 0;
				for (const int n : nums)
					if ((++count_num[n]) << 1 > size)
						dominant = n;

				int i = 0, count = count_num[dominant], count_left = 0;
				for (; i < size; ++i) {
					if (nums[i] == dominant) {
						++count_left;
						--count;
					}
					if (count_left << 1 > i + 1 &&
						count << 1 > size - i - 1)
						return i;
				}
				return -1;
			}

			int minimumIndex__fast(vector<int>& nums) {
				// Find the majority element by Boyer-Moore majority voting algorithm
				int dominant = nums[0], count = 0, count_left = 0, size = nums.size();
				for (const int n : nums) {
					if (n == dominant)
						++count;
					else
						--count;
					if (count == 0) {
						dominant = n;
						count = 1;
					}
				}

				count = 0;
				for (const int n : nums)
					if (n == dominant)
						count++;

				for (int i = 0; i < size; ++i) {
					if (nums[i] == dominant) {
						++count_left;
						--count;
					}
					if (count_left << 1 > i + 1 &&
						count << 1 > size - i - 1)
						return i;
				}
				return -1;
			}
		};
	}

	namespace task_2785 {
		/*
		* https://leetcode.com/problems/sort-vowels-in-a-string/description/
		*/
		class Solution {
		public:
			string sortVowels(string s) { // 56%-85%
				vector<char> vowels;
				size_t size = s.size();
				char t;
				for (size_t i = 0; i < size; ++i) {
					t = s[i];
					if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u' ||
						t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U')
						vowels.push_back(t);
				}
				sort(vowels.begin(), vowels.end());
				size_t j = 0;
				for (size_t i = 0; i < size; ++i) {
					t = s[i];
					if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u' ||
						t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U') {
						s[i] = vowels[j];
						++j;
					}
				}
				return s;
			}

			string sortVowelsIndexes(string s) { // 76%-15%
				vector<char> vowels;
				vector<int> indexes;
				size_t size = s.size();
				char t;
				for (size_t i = 0; i < size; ++i) {
					t = s[i];
					if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u' ||
						t == 'A' || t == 'E' || t == 'I' || t == 'O' || t == 'U') {
						vowels.push_back(t);
						indexes.push_back(i);
					}
				}
				sort(vowels.begin(), vowels.end());
				size = vowels.size();
				for (size_t i = 0; i < size; ++i)
					s[indexes[i]] = vowels[i];
				return s;
			}
		};
	}

	namespace task_2799 {
		/*
		* https://leetcode.com/problems/count-complete-subarrays-in-an-array/description/
		*/
		class Solution {
		public:
			int countCompleteSubarrays(vector<int>& nums) {
				unordered_map<int, int> unique;
				for (int n : nums)
					unique[n] = 1;
				const size_t size = nums.size(), count_unique = unique.size();
				unique.clear();
				int count = 0;
				for (size_t i = 0, j = 0; i < size; ++i) {
					++unique[nums[i]];
					if (unique.size() == count_unique) {
						while (unique.size() == count_unique) {
							if (--unique[nums[j]] == 0)
								unique.erase(nums[j]);
							++j;
						}
						--j;
						++unique[nums[j]];
						count += j + 1;
					}
				}
				return count;
			}
		};
	}

	namespace task_2807 {
		/*
		* https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/description/
		*/
		class Solution {
		public:
			ListNode* insertGreatestCommonDivisors(ListNode* head) {
				auto ptr = head;
				while (ptr->next) {
					ptr->next = new ListNode(GCD(ptr->val, ptr->next->val), ptr->next);
					ptr = ptr->next->next;
				}
				return head;
			}

			int GCD(int x, int y) {
				while (x != y)
					if (x > y)
						x -= y;
					else
						y -= x;
				return x;
			}

			int GCD2(int x, int y) {
				int z = 0;
				while (x > 0) {
					z = x;
					x = y % x;
					y = z;
				}
				return y;
			}
		};
	}

	namespace task_2810 {
		/*
		* https://leetcode.com/problems/faulty-keyboard/description/
		*/
		class Solution {
		public:
			string finalString(string s) {
				string res;
				for (char c : s)
					if (c == 'i')
						reverseString(res);
					else
						res.push_back(c);
				return res;
			}

			void reverseString(string& s) {
				size_t size = s.size();
				char t;
				for (size_t i = size >> 1; i < size; ++i) {
					t = s[i];
					s[i] = s[size - i - 1];
					s[size - i - 1] = t;
				}
			}
		};
	}

	namespace task_2812 {
		/*
		* https://leetcode.com/problems/find-the-safest-path-in-a-grid/description/
		*/
		class Solution {
		public:
			vector<vector<int>> queue;

			int maximumSafenessFactor(vector<vector<int>>& grid) {
				size_t size = grid.size();
				queue = vector<vector<int>>(size * size, vector<int>(3));
				for (size_t i = 0; i < size; i++)
					for (size_t j = 0; j < size; j++)
						if (grid[i][j])
							grid[i][j] = 0;
						else
							grid[i][j] = size;

				for (size_t i = 0; i < size; i++)
					for (size_t j = 0; j < size; j++)
						if (grid[i][j] == 0)
							dfsThief(grid, i, j, size);

				int safety_max = min(grid[0][0], grid[size - 1][size - 1]) + 1;
				int safety_min = 0;
				int safety;

				while (safety_min + 1 != safety_max) {
					safety = (safety_max + safety_min) >> 1;
					if (dfsSearch(grid, safety, size))
						safety_min = safety;
					else
						safety_max = safety;
				}
				return safety_min;
			}

			void dfsThief(vector<vector<int>>& grid, int start_i, int start_j, const size_t size) {
				int queue_end = 1;
				int queue_top = 0;
				int i, j, grid_value;
				queue[0][0] = start_i;
				queue[0][1] = start_j;
				while (queue_top != queue_end) {
					i = queue[queue_top][0];
					j = queue[queue_top][1];
					++queue_top;
					grid_value = grid[i][j] + 1;
					if (i + 1 < size && grid[i + 1][j] > grid_value) {
						grid[i + 1][j] = grid_value;
						queue[queue_end][0] = i + 1;
						queue[queue_end][1] = j;
						++queue_end;
					}
					if (j + 1 < size && grid[i][j + 1] > grid_value) {
						grid[i][j + 1] = grid_value;
						queue[queue_end][0] = i;
						queue[queue_end][1] = j + 1;
						++queue_end;
					}
					if (i - 1 > -1 && grid[i - 1][j] > grid_value) {
						grid[i - 1][j] = grid_value;
						queue[queue_end][0] = i - 1;
						queue[queue_end][1] = j;
						++queue_end;
					}
					if (j - 1 > -1 && grid[i][j - 1] > grid_value) {
						grid[i][j - 1] = grid_value;
						queue[queue_end][0] = i;
						queue[queue_end][1] = j - 1;
						++queue_end;
					}
				}
			}

			bool dfsSearch(vector<vector<int>>& grid, const int safety, const size_t size) {
				int queue_end = 1;
				int queue_top = 0;
				int i, j, grid_value;
				bool res = false;
				queue[0][0] = 0;
				queue[0][1] = 0;
				queue[0][2] = grid[0][0];
				grid[0][0] = 0;
				while (queue_top != queue_end) {
					i = queue[queue_top][0];
					j = queue[queue_top][1];
					++queue_top;
					if (i + 1 < size && grid[i + 1][j] >= safety) {
						if (i + 1 == size - 1 && j == size - 1) {
							res = true;
							break;
						}
						queue[queue_end][0] = i + 1;
						queue[queue_end][1] = j;
						queue[queue_end][2] = grid[i + 1][j];
						grid[i + 1][j] = 0;
						++queue_end;
					}
					if (j + 1 < size && grid[i][j + 1] >= safety) {
						if (i == size - 1 && j + 1 == size - 1) {
							res = true;
							break;
						}
						queue[queue_end][0] = i;
						queue[queue_end][1] = j + 1;
						queue[queue_end][2] = grid[i][j + 1];
						grid[i][j + 1] = 0;
						++queue_end;
					}
					if (i - 1 > -1 && grid[i - 1][j] >= safety) {
						queue[queue_end][0] = i - 1;
						queue[queue_end][1] = j;
						queue[queue_end][2] = grid[i - 1][j];
						grid[i - 1][j] = 0;
						++queue_end;
					}
					if (j - 1 > -1 && grid[i][j - 1] >= safety) {
						queue[queue_end][0] = i;
						queue[queue_end][1] = j - 1;
						queue[queue_end][2] = grid[i][j - 1];
						grid[i][j - 1] = 0;
						++queue_end;
					}
				}
				for (size_t i = 0; i < queue_end; i++)
					grid[queue[i][0]][queue[i][1]] = queue[i][2];
				return res;
			}
		};
	}

	namespace task_2816
	{
		/*
		* https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/description/
		*/
		class Solution {
		public:
			ListNode* doubleItFast(ListNode* head) {
				ListNode* ptr = head;
				if (head->val > 4)
					head = new ListNode(1, head);

				int remainder = 0;
				int sum = 0;
				for (; ptr->next; ptr = ptr->next)
					ptr->val = ((ptr->val << 1) + (ptr->next->val > 4 ? 1 : 0)) % 10;
				ptr->val = (ptr->val << 1) % 10;

				return head;
			}

			ListNode* doubleIt(ListNode* head) {
				head = rotate(head);

				int remainder = 0;
				int sum = 0;
				ListNode* ptr = head;
				for (; ptr->next; ptr = ptr->next) {
					sum = (ptr->val << 1) + remainder;
					ptr->val = sum % 10;
					remainder = sum / 10;
				}
				sum = (ptr->val << 1) + remainder;
				ptr->val = sum % 10;
				remainder = sum / 10;
				if (remainder != 0)
					ptr->next = new ListNode(remainder);

				return rotate(head);
			}

			ListNode* rotate(ListNode* head) {
				ListNode* next = head->next;
				ListNode* tmp = nullptr;
				head->next = nullptr;
				while (next)
				{
					tmp = next->next;
					next->next = head;
					head = next;
					next = tmp;
				}
				return head;
			}
		};
	}

	namespace task_2818 {
		/*
		* https://leetcode.com/problems/apply-operations-to-maximize-score/description/
		*/
		class Solution {
		public:
			const int MOD = 1e9 + 7;

			int maximumScore(vector<int>& nums, int k) {
				int n = nums.size();
				vector<int> primeScores(n, 0);

				// Find the maximum element in nums to determine the range for prime
				// generation
				int maxElement = 0;
				for (int index = 0; index < n; index++)
					maxElement = max(maxElement, nums[index]);

				// Get all prime numbers up to maxElement using the Sieve of
				// Eratosthenes
				vector<int> primes = getPrimes(maxElement);

				// Calculate the prime score for each number in nums
				for (int index = 0; index < n; index++) {
					int num = nums[index];

					// Iterate over the generated primes to count unique prime factors
					for (int prime : primes) {
						if (prime * prime > num)
							break;  // Stop early if prime^2 exceeds num
						if (num % prime != 0)
							continue;  // Skip if the prime is not a factor

						primeScores[index]++;  // Increment prime score for the factor
						while (num % prime == 0)
							num /= prime;  // Remove all occurrences of this factor
					}

					// If num is still greater than 1, it is a prime number itself
					if (num > 1) primeScores[index]++;
				}

				// Initialize next and previous dominant index arrays
				vector<int> nextDominant(n, n);
				vector<int> prevDominant(n, -1);

				// Stack to store indices for a monotonic decreasing prime score
				stack<int> decreasingPrimeScoreStack;

				// Calculate the next and previous dominant indices for each number
				for (int index = 0; index < n; index++) {
					// While the stack is not empty and the current prime score is
					// greater than the stack's top, update nextDominant
					while (!decreasingPrimeScoreStack.empty() &&
						primeScores[decreasingPrimeScoreStack.top()] <
						primeScores[index]) {
						int topIndex = decreasingPrimeScoreStack.top();
						decreasingPrimeScoreStack.pop();

						// Set the next dominant element for the popped index
						nextDominant[topIndex] = index;
					}

					// If the stack is not empty, set the previous dominant element for
					// the current index
					if (!decreasingPrimeScoreStack.empty())
						prevDominant[index] = decreasingPrimeScoreStack.top();

					// Push the current index onto the stack
					decreasingPrimeScoreStack.push(index);
				}

				// Calculate the number of subarrays in which each element is dominant
				vector<long long> numOfSubarrays(n);
				for (int index = 0; index < n; index++) {
					numOfSubarrays[index] = (long long)(nextDominant[index] - index) *
						(index - prevDominant[index]);
				}

				// Sort elements in decreasing order based on their values
				vector<pair<int, int>> sortedArray(n);
				for (int index = 0; index < n; index++) {
					sortedArray[index] = { nums[index], index };
				}

				sort(sortedArray.begin(), sortedArray.end(), greater<>());

				long long score = 1;
				int processingIndex = 0;

				// Process elements while there are operations left
				while (k > 0) {
					// Get the element with the maximum value
					auto [num, index] = sortedArray[processingIndex++];

					// Calculate the number of operations to apply on the current
					// element
					long long operations = min((long long)k, numOfSubarrays[index]);

					// Update the score by raising the element to the power of
					// operations
					score = (score * power(num, operations)) % MOD;

					// Reduce the remaining operations count
					k -= operations;
				}

				return score;
			}

			// Helper function to compute the power of a number modulo MOD
			long long power(long long base, long long exponent) {
				long long res = 1;

				// Calculate the exponentiation using binary exponentiation
				while (exponent > 0) {
					// If the exponent is odd, multiply the result by the base
					if (exponent % 2 == 1)
						res = ((res * base) % MOD);

					// Square the base and halve the exponent
					base = (base * base) % MOD;
					exponent /= 2;
				}

				return res;
			}

			// Function to generate prime numbers up to a given limit using the Sieve of
			// Eratosthenes
			vector<int> getPrimes(int limit) {
				vector<bool> isPrime(limit + 1, true);
				vector<int> primes;

				// Start marking from the first prime number (2)
				for (int number = 2; number <= limit; number++) {
					if (!isPrime[number]) continue;

					// Store the prime number
					primes.push_back(number);

					// Mark multiples of the prime number as non-prime
					for (long long multiple = (long long)number * number;
						multiple <= limit; multiple += number) {
						isPrime[multiple] = false;
					}
				}

				return primes;
			}
		};
	}

	namespace task_2825 {
		/*
		* https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/description/
		*/
		class Solution {
		public:
			bool canMakeSubsequence(string str1, string str2) {
				size_t size1 = str1.size(), size2 = str2.size(), i = 0, j = 0;
				for (; j < size2; j++) {
					for (; i < size1 &&
						str1[i] != str2[j] &&
						str1[i] + 1 != str2[j] &&
						!(str1[i] == 'z' && str2[j] == 'a'); ++i) {
					}
					if (i == size1)
						return false;
					++i;
				}
				return true;
			}
		};
	}

	namespace task_2843 {
		/*
		* https://leetcode.com/problems/count-symmetric-integers/description/
		*/
		class Solution {
		public:
			int countSymmetricIntegers(int low, int high) {
				int res = 0;
				for (int a = low; a <= high; ++a) {
					if (a < 100 && a % 11 == 0)
						++res;
					else if (1000 <= a && a < 10000) {
						int left = a / 1000 + (a % 1000) / 100;
						int right = (a % 100) / 10 + a % 10;
						if (left == right)
							++res;
					}
				}
				return res;
			}
		};
	}

	namespace task_2845 {
		/*
		* https://leetcode.com/problems/count-of-interesting-subarrays/description/
		*/
		class Solution {
		public:
			long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
				int n = nums.size();
				unordered_map<int, int> cnt;
				long long res = 0;
				int prefix = 0;
				cnt[0] = 1;
				for (int i = 0; i < n; i++) {
					prefix += nums[i] % modulo == k;
					res += cnt[(prefix - k + modulo) % modulo];
					cnt[prefix % modulo]++;
				}
				return res;
			}
		};
	}

	namespace task_2872 {
		/*
		* https://leetcode.com/problems/maximum-number-of-k-divisible-components/description/
		*/
		class Solution {
		public:
			int maxKDivisibleComponents__leetcode(int n, vector<vector<int>>& edges,
				vector<int>& values, int k) {
				if (n < 2) return 1;

				int componentCount = 0;
				vector<vector<int>> graph(n);
				vector<int> inDegree(n, 0);

				// Build the graph and calculate in-degrees
				for (const auto& edge : edges) {
					int node1 = edge[0], node2 = edge[1];
					graph[node1].push_back(node2);
					graph[node2].push_back(node1);
					inDegree[node1]++;
					inDegree[node2]++;
				}

				// Convert values to long long to prevent overflow
				vector<long long> longValues(values.begin(), values.end());

				// Initialize the queue with nodes having in-degree of 1 (leaf nodes)
				queue<int> queue;
				for (int node = 0; node < n; node++) {
					if (inDegree[node] == 1) {
						queue.push(node);
					}
				}

				while (!queue.empty()) {
					int currentNode = queue.front();
					queue.pop();
					inDegree[currentNode]--;

					long long addValue = 0;

					// Check if the current node's value is divisible by k
					if (longValues[currentNode] % k == 0) {
						componentCount++;
					}
					else {
						addValue = longValues[currentNode];
					}

					// Propagate the value to the neighbor nodes
					for (int neighborNode : graph[currentNode]) {
						if (inDegree[neighborNode] == 0) {
							continue;
						}

						inDegree[neighborNode]--;
						longValues[neighborNode] += addValue;

						// If the neighbor node's in-degree becomes 1, add it to the
						// queue
						if (inDegree[neighborNode] == 1) {
							queue.push(neighborNode);
						}
					}
				}

				return componentCount;
			}
		};
	}

	namespace task_2873 {
		/*
		* https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/description/
		*/
		class Solution {
		public:
			long long maximumTripletValue(vector<int>& nums) {
				size_t size = nums.size();
				long long max_value = 0;
				for (size_t i = 0; i < size; ++i) {
					for (size_t j = i + 1; j < size; ++j) {
						for (size_t k = j + 1; k < size; ++k)
							max_value = max(max_value, (nums[i] - nums[j]) * (long long)nums[k]);
					}
				}
				return max_value;
			}

			long long maximumTripletValue_faster(vector<int>& nums) {
				size_t size = nums.size();
				long long max_value = 0;
				for (size_t k = 2; k < size; ++k) {
					int maxPrefix = nums[0];
					for (size_t j = 1; j < k; ++j) {
						max_value = max(max_value, (maxPrefix - nums[j]) * (long long)nums[k]);
						maxPrefix = max(maxPrefix, nums[j]);
					}
				}
				return max_value;
			}
		};
	}

	namespace task_2874 {
		/*
		* https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/description/
		*/
		class Solution {
		public:
			long long maximumTripletValue_faster(vector<int>& nums) {
				size_t size = nums.size();
				long long max_value = 0;
				vector<int> prefix_max(size), suffix_max(size);
				prefix_max[0] = nums[0];
				suffix_max[size - 1] = nums[size - 1];
				for (size_t i = 1; i < size; ++i)
					prefix_max[i] = max(prefix_max[i - 1], nums[i - 1]);
				for (int i = size - 2; i >= 0; --i)
					suffix_max[i] = max(suffix_max[i + 1], nums[i + 1]);

				--size;
				for (size_t j = 1; j < size; ++j)
					max_value = max(max_value, (prefix_max[j] - nums[j]) * (long long)suffix_max[j]);
				return max_value;
			}

			long long maximumTripletValue__fast(vector<int>& nums) {
				size_t size = nums.size();
				long long res = 0, imax = 0, dmax = 0;
				for (size_t k = 0; k < size; ++k) {
					res = max(res, dmax * nums[k]);
					dmax = max(dmax, imax - nums[k]);
					imax = max(imax, static_cast<long long>(nums[k]));
				}
				return res;
			}
		};
	}

	namespace task_2894 {
		/*
		* https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/description/
		*/
		class Solution {
		public:
			int differenceOfSums(int n, int m) {
				int sum = 0;
				for (int i = 0; i <= n; ++i) {
					if (i % m == 0)
						sum -= i;
					else
						sum += i;
				}
				return sum;
			}
		};
	}

	namespace task_2900 {
		/*
		* https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/description/
		*/
		class Solution {
		public:
			vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
				const size_t size = words.size();
				vector<string> res(1, words[0]);
				int bit = groups[0];
				for (size_t i = 1; i < size; ++i) {
					if (bit != groups[i]) {
						bit = groups[i];
						res.push_back(words[i]);
					}
				}
				return res;
			}
		};
	}

	namespace task_2901 {
		/*
		* https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/description/
		*/
		class Solution {
		public:
			vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
				const int size = words.size();
				vector<int> lengths(size, 1), prevs(size, -1);
				int max_len = 1, ind = 0;
				for (int i = 1; i < size; ++i) {
					size_t len = words[i].size();
					int seq_len = 0, prev_ind = -1;
					for (int j = i - 1; j > -1; --j) {
						if (groups[i] != groups[j] &&
							words[j].size() == len &&
							lengths[j] > seq_len &&
							isDistanceOne(words[i], words[j], len)) {
							seq_len = lengths[j];
							prev_ind = j;
						}
					}

					if (seq_len != 0) {
						++seq_len;
						lengths[i] = seq_len;
						prevs[i] = prev_ind;
						if (max_len < seq_len) {
							max_len = seq_len;
							ind = i;
						}
					}
				}

				vector<string> res;
				for (; ind != -1; ind = prevs[ind])
					res.push_back(words[ind]);
				reverse(res.begin(), res.end());

				return res;
			}

			int isDistanceOne(const string& s1, const string& s2, const size_t size) {
				size_t i = 0;
				for (; i < size && s1[i] == s2[i]; ++i) {}
				if (i == size)
					return false;

				for (++i; i < size && s1[i] == s2[i]; ++i) {}
				return i == size;
			}
		};
	}

	namespace task_2914 {
		/*
		* https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/description/
		*/
		class Solution {
		public:
			int minChanges(string s) {
				size_t size = s.size();
				int count = 0;
				for (size_t i = 1; i < size; i += 2)
					if (s[i - 1] != s[i])
						++count;
				return count;
			}
		};
	}

	namespace task_2918 {
		/*
		* https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/description/
		*/
		class Solution {
		public:
			long long minSum(vector<int>& nums1, vector<int>& nums2) {
				long long sum1 = 0, sum2 = 0, count_zeros1 = 0, count_zeros2 = 0;
				for (const int n : nums1) {
					sum1 += n;
					if (n == 0)
						++count_zeros1;
				}
				for (const int n : nums2) {
					sum2 += n;
					if (n == 0)
						++count_zeros2;
				}
				sum1 += count_zeros1;
				sum2 += count_zeros2;
				if (sum1 < sum2) {
					swap(sum1, sum2);
					swap(count_zeros1, count_zeros2);
				}
				return sum1 <= sum2 + count_zeros2 * (INT32_MAX - 1) ? sum1 : -1;
			}
		};
	}

	namespace task_2924 {
		/*
		* https://leetcode.com/problems/find-champion-ii/description/
		*/
		class Solution {
		public:
			int findChampion(int n, vector<vector<int>>& edges) {
				vector<int> champions(n, 1);
				for (const vector<int >& edge : edges)
					champions[edge[1]] = 0;
				int i = 0;
				for (; i < n && champions[i] == 0; ++i) {}
				int champion = i;
				++i;
				for (; i < n && champions[i] == 0; ++i) {}
				return i == n ? champion : -1;
			}
		};
	}

	namespace task_2929 {
		/*
		* https://leetcode.com/problems/distribute-candies-among-children-ii/description/
		*/
		class Solution {
		public:
			long long distributeCandies(int n, int limit) {
				long long ans = 0;
				for (int i = max(0, n - 2 * limit); i <= min(limit, n); i++)
					ans += min(n - i, limit) - max(0, n - i - limit) + 1;
				return ans;
			}
		};
	}

	namespace task_2938 {
		/*
		* https://leetcode.com/problems/separate-black-and-white-balls/description/
		*/
		class Solution {
		public:
			long long minimumSteps(string s) {
				int count_black = 0;
				long long moves = 0;
				for (const char c : s)
					if (c == '0')
						moves += count_black;
					else
						++count_black;
				return moves;
			}
		};
	}

	namespace task_2940 {
		/*
		* https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/
		*/
		class Solution {
		public:
			vector<int> leftmostBuildingQueries__leetsode(vector<int>& heights,
				vector<vector<int>>& queries) {
				vector<vector<vector<int>>> storeQueries(heights.size());
				priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>
					maxIndex;
				vector<int> result(queries.size(), -1);

				// Store the mappings for all queries in storeQueries.
				for (int currQuery = 0; currQuery < queries.size(); currQuery++) {
					int a = queries[currQuery][0], b = queries[currQuery][1];
					if (a < b && heights[a] < heights[b]) {
						result[currQuery] = b;
					}
					else if (a > b && heights[a] > heights[b]) {
						result[currQuery] = a;
					}
					else if (a == b) {
						result[currQuery] = a;
					}
					else {
						storeQueries[max(a, b)].push_back(
							{ max(heights[a], heights[b]), currQuery });
					}
				}

				for (int index = 0; index < heights.size(); index++) {
					// If the priority queue's minimum pair value is less than the
					// current index of height, it is an answer to the query.
					while (!maxIndex.empty() && maxIndex.top()[0] < heights[index]) {
						result[maxIndex.top()[1]] = index;
						maxIndex.pop();
					}
					// Push the with their maximum index as the current index in the
					// priority queue.
					for (auto& element : storeQueries[index]) {
						maxIndex.push(element);
					}
				}
				return result;
			}
		};
	}

	namespace task_2942 {
		/*
		* https://leetcode.com/problems/find-words-containing-character/description/
		*/
		class Solution {
		public:
			vector<int> findWordsContaining(vector<string>& words, char x) {
				vector<int> res;
				const int size = words.size();
				for (int i = 0; i < size; i++)
					if (contain(words[i], x))
						res.push_back(i);
				return res;
			}

			bool contain(const string& s, const char x) {
				for (const char c : s)
					if (c == x)
						return true;
				return false;
			}
		};
	}

	namespace task_2948 {
		/*
		* https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/description/
		*/
		class Solution {
		public:
			vector<int> lexicographicallySmallestArray__leetcode(vector<int>& nums, int limit) {
				vector<int> numsSorted(nums);
				sort(numsSorted.begin(), numsSorted.end());

				int currGroup = 0;
				unordered_map<int, int> numToGroup;
				numToGroup.insert(pair<int, int>(numsSorted[0], currGroup));

				unordered_map<int, list<int>> groupToList;
				groupToList.insert(
					pair<int, list<int>>(currGroup, list<int>(1, numsSorted[0])));

				for (int i = 1; i < nums.size(); i++) {
					if (abs(numsSorted[i] - numsSorted[i - 1]) > limit) {
						// new group
						currGroup++;
					}

					// assign current element to group
					numToGroup.insert(pair<int, int>(numsSorted[i], currGroup));

					// add element to sorted group list
					if (groupToList.find(currGroup) == groupToList.end()) {
						groupToList[currGroup] = list<int>();
					}
					groupToList[currGroup].push_back(numsSorted[i]);
				}

				// iterate through input and overwrite each element with the next
				// element in its corresponding group
				for (int i = 0; i < nums.size(); i++) {
					int num = nums[i];
					int group = numToGroup[num];
					nums[i] = *groupToList[group].begin();
					groupToList[group].pop_front();
				}

				return nums;
			}
		};
	}

	namespace task_2962 {
		/*
		* https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/description/
		*/
		class Solution {
		public:
			long long countSubarrays(vector<int>& nums, long long k) {
				int max_value = 0, count_max = 0;
				for (int n : nums)
					max_value = max(max_value, n);
				const size_t size = nums.size();
				long long count = 0;
				for (size_t i = 0, j = 0; i < size; ++i) {
					if (nums[i] == max_value)
						++count_max;
					if (count_max >= k) {
						for (; count_max >= k; ++j)
							if (nums[j] == max_value)
								--count_max;
						count += j;
						--j;
						++count_max;
					}
				}
				return count;
			}
		};
	}

	namespace task_2965 {
		/*
		* https://leetcode.com/problems/find-missing-and-repeated-values/description/
		*/
		class Solution {
		public:
			vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
				int n = grid.size();
				vector<int> res;
				for (int i = 0; i < n; ++i)
				{
					for (int j = 0; j < n; ++j) {
						if (grid[i][j] != i * n + j + 1) {
							int num = grid[i][j];
							do
							{
								int num_i = (num - 1) / n, num_j = (num - 1) % n;
								if (num == grid[num_i][num_j]) {
									grid[i][j] = 0;
									res.push_back(num);
									break;
								}
								swap(grid[i][j], grid[num_i][num_j]);
								num = grid[i][j];
							} while (num != 0 && num != i * n + j + 1);
						}
					}
				}


				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < n; ++j)
						if (grid[i][j] == 0)
							res.push_back(i * n + j + 1);
				}
				return res;
			}

			vector<int> findMissingAndRepeatedValues__fast(vector<vector<int>>& grid) {
				long long sum = 0, sqrSum = 0;
				long long n = grid.size();
				long long total = n * n;

				// Calculate actual sum and squared sum from grid
				for (int row = 0; row < n; ++row) {
					for (int col = 0; col < n; ++col) {
						sum += grid[row][col];
						sqrSum += static_cast<long long>(grid[row][col]) * grid[row][col];
					}
				}

				// Calculate differences from expected sums
				// Expected sum: n(n+1)/2, Expected square sum: n(n+1)(2n+1)/6
				long long sumDiff = sum - total * (total + 1) / 2;
				long long sqrDiff = sqrSum - total * (total + 1) * (2 * total + 1) / 6;

				// Using math: If x is repeated and y is missing
				// sumDiff = x - y
				// sqrDiff = x² - y²
				int repeat = (sqrDiff / sumDiff + sumDiff) / 2;
				int missing = (sqrDiff / sumDiff - sumDiff) / 2;

				return { repeat, missing };
			}
		};
	}

	namespace task_2976 {
		/*
		* https://leetcode.com/problems/minimum-cost-to-convert-string-i/description/
		*/
		class Solution {
		public:
			long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
				size_t size = 'z' - 'a' + 1, size_orig = cost.size(), size_str = source.size();
				vector<vector<long long>> dist_matrix(size, vector<long long>(size, INT_MAX));

				for (size_t i = 0; i < size; ++i)
					dist_matrix[i][i] = 0;
				for (size_t i = 0; i < size_orig; ++i)
					dist_matrix[original[i] - 'a'][changed[i] - 'a'] = min((long long)cost[i], dist_matrix[original[i] - 'a'][changed[i] - 'a']);

				for (size_t i = 0; i < size; ++i)
					for (size_t j = 0; j < size; ++j)
						for (size_t k = 0; k < size; ++k)
							dist_matrix[j][k] = min(dist_matrix[j][k], dist_matrix[j][i] + dist_matrix[i][k]);

				long long costs = 0;
				for (size_t i = 0; i < size_str; ++i)
					if (source[i] != target[i]) {
						long long dist = dist_matrix[source[i] - 'a'][target[i] - 'a'];
						if (dist == INT_MAX)
							return -1;
						costs += dist;
					}
				return costs;
			}
		};
	}

	namespace task_2981 {
		/*
		* https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/description
		*/
		class Solution {
		public:
			int maximumLength(string s) {
				vector<char> letters(26);
				int res = -1;
				for (char c : s) {
					++letters[c - 'a'];
					if (letters[c - 'a'] > 2) {
						res = 1;
						break;
					}
				}
				if (res == -1)
					return -1;
				int size = s.size(), count = 0;
				for (char c = 'a'; c <= 'z'; ++c) {
					bool found = true;
					for (int len = 2; len < size && found; ++len) {
						count = 0;
						for (int i = 0; i <= size - len; ++i) {
							int j = 0;
							for (; j < len && s[i + j] == c; ++j) {}
							if (j == len)
								++count;
						}
						if (count > 2)
							res = max(res, len);
						else
							found = false;
					}
				}
				return res;
			}
		};
	}

	namespace task_2997 {
		/*
		* https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/description/
		*/
		class Solution {
		public:
			int minOperations(vector<int>& nums, int k) {
				int count = 0;
				for (const int num : nums)
					k ^= num;
				while (k != 0)
				{
					count += k & 1;
					k >>= 1;
				}
				return count;
			}
		};
	}

	namespace task_2999 {
		/*
		* https://leetcode.com/problems/count-the-number-of-powerful-integers/description/
		*/
		class Solution {
		public:
			long long numberOfPowerfulInt(long long start, long long finish, int limit,
				string s) {
				string start_ = to_string(start - 1), finish_ = to_string(finish);
				return calculate(finish_, s, limit) - calculate(start_, s, limit);
			}

			long long calculate(string x, string s, int limit) {
				if (x.length() < s.length())
					return 0;
				if (x.length() == s.length())
					return x >= s ? 1 : 0;

				string suffix = x.substr(x.length() - s.length(), s.length());
				long long count = 0;
				int preLen = x.length() - s.length();

				for (int i = 0; i < preLen; i++) {
					if (limit < (x[i] - '0')) {
						count += (long)pow(limit + 1, preLen - i);
						return count;
					}
					count += (long)(x[i] - '0') * (long)pow(limit + 1, preLen - 1 - i);
				}
				if (suffix >= s)
					++count;
				return count;
			}
		};
	}

	namespace task_3011 {
		/*
		* https://leetcode.com/problems/find-if-array-can-be-sorted/description/
		*/
		class Solution {
		public:
			bool canSortArray(vector<int>& nums) {
				size_t size = nums.size(), start = 0;
				int bits = 0, section_bits = countBits(nums[0]);
				int sec_max = nums[0], prev_sec_max = -1;
				for (size_t i = 1; i < size; ++i) {
					bits = countBits(nums[i]);
					if (bits == section_bits) {

						sec_max = max(sec_max, nums[i]);
					}
					else {
						prev_sec_max = sec_max;
						sec_max = nums[i];
						section_bits = bits;
					}
					if (nums[i] < prev_sec_max)
						return false;
				}
				return true;
			}

			int countBits(int n) {
				int bits = 0;
				for (; n > 0; n >>= 1)
					if (n & 1)
						++bits;
				return bits;
			}
		};
	}

	namespace task_3016 {
		/*
		* https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/description/
		*/
		class Solution {
		public:
			int minimumPushes(string word) {
				size_t size = 'z' - 'a' + 1;
				vector<int> counts(size);
				for (const char c : word)
					++counts[c - 'a'];
				sort(counts.begin(), counts.end(), greater<int>());
				int count = 0;
				for (size_t i = 0; i < size && counts[i] > 0; ++i)
					count += counts[i] * (i / 8 + 1);
				return count;
			}
		};
	}

	namespace task_3024 {
		/*
		* https://leetcode.com/problems/type-of-triangle/description/
		*/
		class Solution {
		public:
			string triangleType(vector<int>& nums) {
				if (nums[1] + nums[2] <= nums[0] ||
					nums[0] + nums[2] <= nums[1] ||
					nums[0] + nums[1] <= nums[2])
					return "none";
				if (nums[0] == nums[1] &&
					nums[0] == nums[2])
					return "equilateral";
				if (nums[0] == nums[1] ||
					nums[0] == nums[2] ||
					nums[1] == nums[2])
					return "isosceles";
				return "scalene";
			}
		};
	}

	namespace task_3042 {
		/*
		* https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/description/
		*/
		class Solution {
		public:
			class Node {
			public:
				Node* links[26] = {};

				// Check if the character is present in the current node
				bool contains(char c) { return links[c - 'a'] != NULL; }

				// Insert a new node for the character
				void put(char c, Node* node) { links[c - 'a'] = node; }

				// Get the next node for the character
				Node* next(char c) { return links[c - 'a']; }
			};

			class Trie {
			public:
				Node* root;

				Trie() { root = new Node(); }

				// Insert a word into the Trie
				void insert(string& word) {
					Node* node = root;
					for (char c : word) {
						if (!node->contains(c)) {
							node->put(c, new Node());
						}
						node = node->next(c);
					}
				}

				// Check if the Trie contains a given prefix
				bool startsWith(string& prefix) {
					Node* node = root;
					for (char c : prefix) {
						if (!node->contains(c)) {
							return false;
						}
						node = node->next(c);
					}
					return true;
				}
			};

			int countPrefixSuffixPairs(vector<string>& words) {
				int n = words.size();
				int count = 0;

				// Step 1: Iterate over each word
				for (int i = 0; i < n; i++) {
					Trie prefixTrie, suffixTrie;

					// Step 2: Insert the current word into the prefix Trie
					prefixTrie.insert(words[i]);

					// Step 3: Reverse the word and insert it into the suffix Trie
					string revWord = words[i];
					reverse(revWord.begin(), revWord.end());
					suffixTrie.insert(revWord);

					// Step 4: Iterate over all previous words
					for (int j = 0; j < i; j++) {
						// Step 5: Skip words[j] if it is longer than words[i]
						if (words[j].size() > words[i].size()) continue;

						// Step 6: Extract the prefix and reversed prefix of words[j]
						string prefixWord = words[j];
						string revPrefixWord = prefixWord;
						reverse(revPrefixWord.begin(), revPrefixWord.end());

						// Step 7: Check if words[j] is both a prefix and suffix of
						// words[i]
						if (prefixTrie.startsWith(prefixWord) &&
							suffixTrie.startsWith(revPrefixWord)) {
							count++;
						}
					}
				}

				// Step 8: Return the total count of valid pairs
				return count;
			}
		};
	}

	namespace task_3043 {
		/*
		* https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/description/
		*/
		class Solution {
		public:
			class TrieNode {
			public:
				TrieNode* children[10];

				TrieNode() {
					for (int i = 0; i < 10; ++i)
						children[i] = nullptr;
				}
				~TrieNode() {
					for (int i = 0; i < 10; ++i)
						if (children[i])
							delete children[i];
				}
			};

			TrieNode* root;

			int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
				root = buildTrie(arr1);
				int length = 0;

				for (const int number : arr2)
					length = max(length, findLongestPrefix(number));
				return length;
			}

			int findLongestPrefix(int num) {
				TrieNode* node = root;
				string str = to_string(num);
				int len = 0;

				for (char c : str) {
					c -= '0';
					if (!node->children[c])
						break;
					node = node->children[c];
					++len;
				}
				return len;
			}

			TrieNode* buildTrie(const vector<int>& numbers) {
				TrieNode* node, * root = new TrieNode();
				for (const int number : numbers) {
					string str = to_string(number);
					node = root;
					for (char c : str) {
						c -= '0';
						if (!node->children[c])
							node->children[c] = new TrieNode();
						node = node->children[c];
					}
				}
				return root;
			}
		};
	}

	namespace task_3065 {
		/*
		* https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/description/
		*/
		class Solution {
		public:
			int minOperations(vector<int>& nums, int k) {
				int count = 0;
				for (int n : nums)
					if (n < k)
						++count;
				return count;
			}
		};
	}

	namespace task_3066 {
		/*
		* https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/description/
		*/
		class Solution {
		public:
			int minOperations(vector<int>& nums, int k) {
				int count = 0;
				priority_queue<long, vector<long>, greater<>> queue(nums.begin(), nums.end());

				for (; queue.top() < k; ++count) {
					long n1 = queue.top();
					queue.pop();
					long n2 = queue.top();
					queue.pop();
					n2 = min(n1, n2) * 2 + max(n1, n2);
					queue.push(n2);
				}
				return count;
			}

			int minOperations_faster(vector<int>& nums, int k) {
				int count = 0;
				bool no_greater = true;
				//priority_queue<long, vector<long>, greater<>> queue(nums.begin(), nums.end());
				priority_queue<long, vector<long>, greater<>> queue;
				for (int n : nums)
					if (n < k)
						queue.push(n);
					else if (no_greater) {
						queue.push(n);
						no_greater = false;
					}

				for (; queue.top() < k; ++count) {
					long n1 = queue.top();
					queue.pop();
					long n2 = queue.top();
					queue.pop();
					n2 = min(n1, n2) * 2 + max(n1, n2);

					if (n2 < k)
						queue.push(n2);
					else if (no_greater) {
						queue.push(n2);
						no_greater = false;
					}
				}
				return count;
			}
		};
	}

	namespace task_3068 {
		/*
		* https://leetcode.com/problems/find-the-maximum-sum-of-node-values/description/
		*/
		class Solution {
		public:
			/*
			we can make xor of 2 any vertex, becouse there exists path between them,
			and for path a->b->c^ we have a^k, b^k^k = b, c^k.
			we just need track counts of cases when xor is profitable, than not xor.
			if count of xor is odd, we need make one extra max profit xor
			or reject one less profit made xor.
			
			*/
			long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
				long long sum = 0;
				long long min_positive = INT32_MAX;
				long long max_negative = INT32_MAX;
				int count_negative = 0;
				long long difference;

				for (const int vertex : nums) {
					difference = (vertex ^ k) - vertex;
					if (difference > 0) {
						max_negative = min(max_negative, difference);
						sum += vertex ^ k;
						++count_negative;
					}
					else {
						min_positive = min(min_positive, -difference);
						sum += vertex;
					}
				}

				if (count_negative & 1)
					return min_positive < max_negative ? sum - min_positive : sum - max_negative;
				return sum;
			}

			vector<vector<size_t>> getAdjacencyList(const vector<vector<int>>& edges, const size_t length) {
				vector<vector<size_t>> adjacency_list(length);
				for (size_t i = 0; i < edges.size(); i++) {
					adjacency_list[edges[i][0]].push_back(edges[i][1]);
					adjacency_list[edges[i][1]].push_back(edges[i][0]);
				}
				return adjacency_list;
			}
		};
	}

	namespace task_3095 {
		/*
		* https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/description/
		*/
		class Solution {
		public:
			int minimumSubarrayLength(vector<int>& nums, int k) {
				int minLength = INT_MAX;
				int from = 0;
				int to = 0;
				vector<int> bitCounts(32);

				while (to < nums.size()) {
					updateBitCounts(bitCounts, nums[to], 1);
					while (from <= to && convertBitCountsToNumber(bitCounts) >= k) {
						minLength = min(minLength, to - from + 1);
						updateBitCounts(bitCounts, nums[from], -1);
						from++;
					}
					to++;
				}

				return minLength == INT_MAX ? -1 : minLength;
			}

			void updateBitCounts(vector<int>& bitCounts, int number, int delta) {
				for (int bitPosition = 0; bitPosition < 32; bitPosition++)
					if ((number >> bitPosition) & 1)
						bitCounts[bitPosition] += delta;
			}

			int convertBitCountsToNumber(const vector<int>& bitCounts) {
				int result = 0;
				for (int bitPosition = 0; bitPosition < 32; bitPosition++)
					if (bitCounts[bitPosition] != 0)
						result |= 1 << bitPosition;
				return result;
			}
		};
	}

	namespace task_3097 {
		/*
		* https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/description/
		*/
		class Solution {
		public:
			int minimumSubarrayLength(vector<int>& nums, int k) {
				int minLength = INT_MAX;
				int from = 0;
				int to = 0;
				vector<int> bitCounts(32);

				while (to < nums.size()) {
					updateBitCounts(bitCounts, nums[to], 1);
					while (from <= to && convertBitCountsToNumber(bitCounts) >= k) {
						minLength = min(minLength, to - from + 1);
						updateBitCounts(bitCounts, nums[from], -1);
						from++;
					}
					to++;
				}

				return minLength == INT_MAX ? -1 : minLength;
			}

			void updateBitCounts(vector<int>& bitCounts, int number, int delta) {
				for (int bitPosition = 0; bitPosition < 32; bitPosition++)
					if ((number >> bitPosition) & 1)
						bitCounts[bitPosition] += delta;
			}

			int convertBitCountsToNumber(const vector<int>& bitCounts) {
				int result = 0;
				for (int bitPosition = 0; bitPosition < 32; bitPosition++)
					if (bitCounts[bitPosition] != 0)
						result |= 1 << bitPosition;
				return result;
			}
		};
	}

	namespace task_3100 {
		/*
		* https://leetcode.com/problems/water-bottles-ii/
		*/
		class Solution {
		public:
			int maxBottlesDrunk(int numBottles, int numExchange) {
				int res = numBottles;
				while (numBottles >= numExchange) {
					++res;
					numBottles -= numExchange - 1;
					++numExchange;
				}
				return res;
			}
		};
	}

	namespace task_3105 {
		/*
		* https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/description/
		*/
		class Solution {
		public:
			int longestMonotonicSubarray(vector<int>& nums) {
				int length = 1, len = 1, mult = 1;
				const size_t size = nums.size();
				for (size_t i = 1; i < size; i++) {
					int comp = (nums[i] - nums[i - 1]) * mult;
					if (comp > 0) {
						++len;
					}
					else {
						length = max(length, len);
						if (comp == 0) {
							len = 1;
						}
						else {
							len = 2;
							mult *= -1;
						}
					}
				}
				return max(length, len);
			}
		};
	}

	namespace task_3108 {
		/*
		* https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/description/
		*/
		class Solution {
		public:
			vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
				size_t queries = query.size();
				vector<vector<pair<int, int>>> adjacency_list(n);
				vector<int> components(n);
				vector<int> components_length(1);
				vector<int> res(queries);
				int count = 0;
				for (const vector<int>& edge : edges) {
					adjacency_list[edge[0]].push_back({ edge[1], edge[2] });
					adjacency_list[edge[1]].push_back({ edge[0], edge[2] });
				}

				for (int i = 0; i < n; ++i) {
					if (components[i] == 0) {
						++count;
						components[i] = count;
						queue<int> q;
						q.push(i);
						int length = ~0;
						while (!q.empty()) {
							int vertex = q.front();
							q.pop();

							for (const pair<int, int>& p : adjacency_list[vertex]) {
								length &= p.second;
								if (components[p.first] == 0) {
									components[p.first] = count;
									q.push(p.first);
								}
							}
						}
						components_length.push_back(length);
					}
				}

				for (size_t i = 0; i < queries; ++i) {
					if (components[query[i][0]] == components[query[i][1]])
						res[i] = components_length[components[query[i][0]]];
					else
						res[i] = -1;
				}

				return res;
			}
		};
	}

	namespace task_3110 {
		/*
		* https://leetcode.com/problems/score-of-a-string/description/
		*/
		class Solution {
		public:
			int scoreOfString(string s) {
				int score = 0;
				for (size_t i = 1; i < s.size(); i++)
					score += abs(s[i] - s[i - 1]);
				return score;
			}
		};
	}

	namespace task_3133 {
		/*
		* https://leetcode.com/problems/minimum-array-end/description/
		*/
		class Solution {
		public:
			long long minEnd(int n, int x) {
				--n;
				long long answer = x, bit = 1;
				for (; n > 0; n >>= 1, bit <<= 1) {
					while (bit & answer)
						bit <<= 1;
					if (n & 1)
						answer |= bit;
				}
				return answer;
			}
		};
	}

	namespace task_3151 {
		/*
		* https://leetcode.com/problems/special-array-i/description/
		*/
		class Solution {
		public:
			bool isArraySpecial(vector<int>& nums) {
				int size = nums.size();
				for (int i = 1; i < size; ++i)
					if (((nums[i] + nums[i - 1]) & 1) == 0)
						return false;
				return true;
			}
		};
	}

	namespace task_3152 {
		/*
		* https://leetcode.com/problems/special-array-ii/description/
		*/
		class Solution {
		public:
			vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
				vector<bool> res;
				set<int> set_parity;
				int size = nums.size() - 1;
				for (int i = 0; i < size; ++i)
					if (((nums[i] + nums[i + 1]) & 1) == 0)
						set_parity.insert(i);
				for (const vector<int>& query : queries) {
					bool res_query = true;
					auto it = set_parity.lower_bound(query[0]);
					if (it == set_parity.end()) {
						res.push_back(true);
						continue;
					}
					res.push_back(*it >= query[1]);
				}
				return res;
			}

			vector<bool> isArraySpecial__leetcode(vector<int>& nums, vector<vector<int>>& queries) {
				vector<bool> res(queries.size());
				vector<int> prefix(nums.size());

				for (int i = 1; i < nums.size(); i++) {
					if ((nums[i] & 1) == (nums[i - 1] & 1))
						prefix[i] = prefix[i - 1] + 1;
					else
						prefix[i] = prefix[i - 1];
				}

				for (int i = 0; i < queries.size(); i++)
					res[i] = prefix[queries[i][1]] == prefix[queries[i][0]];

				return res;
			}
		};
	}

	namespace task_3158 {
		/*
		* https://leetcode.com/problems/find-the-xor-of-numbers-which-appear-twice/description/
		*/
		class Solution {
		public:
			int duplicateNumbersXOR(vector<int>& nums) {
				sort(nums.begin(), nums.end());
				int res = 0;
				for (size_t i = 1; i < nums.size(); i++)
					if (nums[i] == nums[i - 1])
						res ^= nums[i];
				return res;
			}
		};
	}

	namespace task_3160 {
		/*
		* https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/description/
		*/
		class Solution {
		public:
			vector<int> queryResults(int limit, vector<vector<int>>& queries) {
				const size_t size = queries.size();
				unordered_map<int, int> colors_count, ball_color;
				vector<int> res(size);
				for (size_t i = 0; i < size; ++i) {
					auto ball = ball_color.find(queries[i][0]);
					if (ball == ball_color.end()) {
						ball_color[queries[i][0]] = queries[i][1];
						++colors_count[queries[i][1]];
					}
					else if (ball->second != queries[i][1]) {
						auto old_color = colors_count.find(ball->second);
						--old_color->second;
						if (old_color->second == 0)
							colors_count.erase(old_color);
						ball_color[queries[i][0]] = queries[i][1];
						++colors_count[queries[i][1]];
					}
					res[i] = colors_count.size();
				}
				return res;
			}
		};
	}

	namespace task_3163 {
		/*
		* https://leetcode.com/problems/string-compression-iii/description/
		*/
		class Solution {
		public:
			string compressedString(string word) {
				size_t size = word.size();
				string res;
				for (size_t i = 0; i < size; ++i) {
					size_t j = 1;
					for (; i + j < size && j < 9 && word[i] == word[i + j]; ++j) {}
					res.push_back('0' + j);
					res.push_back(word[i]);
					i += j - 1;
				}
				return res;
			}
		};
	}

	namespace task_3169 {
		/*
		* https://leetcode.com/problems/count-days-without-meetings/description/
		*/
		class Solution {
		public:
			int countDays(int days, vector<vector<int>>& meetings) {
				sort(meetings.begin(), meetings.end());
				int count_days = 0, last_end = 0;
				for (const vector<int>& meeting : meetings) {
					if (meeting[0] - 1 > last_end)
						count_days += meeting[0] - 1 - last_end;
					last_end = max(last_end, meeting[1]);
				}
				return count_days + days - last_end;
			}
		};
	}

	namespace task_3170 {
		/*
		* https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/description/
		*/
		class Solution {
		public:
			string clearStars__leetcode(string s) {
				vector<stack<int>> cnt(26);
				for (int i = 0; i < s.size(); i++) {
					if (s[i] != '*') {
						cnt[s[i] - 'a'].push(i);
					}
					else {
						for (int j = 0; j < 26; j++) {
							if (!cnt[j].empty()) {
								s[cnt[j].top()] = '*';
								cnt[j].pop();
								break;
							}
						}
					}
				}

				string ans;
				for (int i = 0; i < s.size(); i++) {
					if (s[i] != '*')
						ans.push_back(s[i]);
				}
				return ans;
			}
		};
	}

	namespace task_3174 {
		/*
		* https://leetcode.com/problems/clear-digits/description/
		*/
		class Solution {
		public:
			string clearDigits(string s) {
				string res;
				for (char c : s) {
					if (c >= '0' && c <= '9') {
						if (!res.empty())
							res.pop_back();
					}
					else
						res.push_back(c);
				}
				return res;
			}
		};
	}

	namespace task_3191 {
		/*
		* https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/description/
		*/
		class Solution {
		public:
			int minOperations(vector<int>& nums) {
				size_t size = nums.size(), i = 0;
				int count = 0;
				for (; i <= size - 3; ++i) {
					if (nums[i] == 0) {
						++count;
						for (size_t j = 0; j < 3; ++j)
							nums[j + i] ^= 1;
					}
				}
				for (; i < size; ++i)
					if (nums[i] == 0)
						return -1;
				return count;
			}

			int minOperations2(vector<int>& nums) {
				const size_t size = nums.size() - 2;
				int count = 0;
				for (size_t i = 0; i < size; ++i) {
					if (nums[i] == 0) {
						++count;
						nums[i] ^= 1;
						nums[i + 1] ^= 1;
						nums[i + 2] ^= 1;
					}
				}
				return (nums[size] == 1 && nums[size + 1] == 1) ? count : -1;
			}
		};
	}

	namespace task_3203 {
		/*
		* https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/
		*/
		class Solution {
		public:
			int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
				size_t n = edges1.size() + 1, m = edges2.size() + 1;
				vector<vector<int>> adjacency_list1(n), adjacency_list2(m);
				vector<int> visited1(n), visited2(m);
				for (const auto& edge : edges1) {
					adjacency_list1[edge[0]].push_back(edge[1]);
					adjacency_list1[edge[1]].push_back(edge[0]);
				}
				for (const auto& edge : edges2) {
					adjacency_list2[edge[0]].push_back(edge[1]);
					adjacency_list2[edge[1]].push_back(edge[0]);
				}
				int diameter1 = 0, diameter2 = 0;
				visited1[0] = 1;
				visited2[0] = 1;
				getDiameter(adjacency_list1, visited1, 0, diameter1);
				getDiameter(adjacency_list2, visited2, 0, diameter2);
				if (diameter1 < diameter2)
					swap(diameter1, diameter2);
				return (diameter1 >> 1) + (diameter1 & 1) + max(diameter1 >> 1, (diameter2 >> 1) + (diameter1 & 1) + 1);
			}

			int getDiameter(const vector<vector<int>>& adjacency_list, vector<int>& visited, int v, int& diameter) {
				int max_deep1 = 0, max_deep2 = 0, node_deep = 0;
				for (int neighbour : adjacency_list[v]) {
					if (visited[neighbour] == 0) {
						visited[neighbour] = 1;
						int deep = getDiameter(adjacency_list, visited, neighbour, diameter) + 1;
						if (max_deep1 <= deep) {
							max_deep2 = max_deep1;
							max_deep1 = deep;
							node_deep = deep;
						}
						else if (max_deep2 < deep) {
							max_deep2 = deep;
						}
					}
				}
				diameter = max(diameter, max_deep1 + max_deep2);
				return node_deep;
			}
		};
	}

	namespace task_3206 {
		/*
		* https://leetcode.com/problems/alternating-groups-i/
		*/
		class Solution {
		public:
			int numberOfAlternatingGroups(vector<int>& colors) {
				size_t size = colors.size();
				int count = 0;
				if (colors[0] != colors[size - 1] && colors[0] != colors[1])
					++count;
				if (colors[0] != colors[size - 1] && colors[size - 2] != colors[size - 1])
					++count;
				--size;
				for (size_t i = 1; i < size; ++i) {
					if (colors[i] != colors[i - 1] && colors[i] != colors[i + 1])
						++count;
				}
				return count;
			}
		};
	}

	namespace task_3208 {
		/*
		* https://leetcode.com/problems/alternating-groups-ii/description/
		*/
		class Solution {
		public:
			int numberOfAlternatingGroups(vector<int>& colors, int k) {
				const size_t size = colors.size();
				int count = 0, len = 1;
				for (size_t i = 1; i < size; ++i) {
					if (colors[i] != colors[i - 1])
						++len;
					else
						len = 1;
					if (len >= k)
						++count;
				}
				if (colors[0] != colors[size - 1]) {
					++len;
					--k;
					if (len > k)
						++count;
					for (size_t i = 1; i < k; ++i) {
						if (colors[i] != colors[i - 1])
							++len;
						else
							len = 1;
						if (len > k)
							++count;
					}
				}
				return count;
			}
		};
	}

	namespace task_3217 {
		/*
		* https://leetcode.com/problems/remove-linked-list-elements/
		*/
		class Solution {
		public:
			ListNode* modifiedList(vector<int>& nums, ListNode* head) {
				auto guard = new ListNode(0, head);
				head = guard;
				unordered_set set(nums.begin(), nums.end());
				while (head && head->next) {
					if (set.contains(head->next->val)) {
						auto temp = head->next->next;
						delete head->next;
						head->next = temp;
					}
					else
						head = head->next;
				}

				head = guard->next;
				delete guard;
				return head;
			}
		};
	}

	namespace task_3223 {
		/*
		* https://leetcode.com/problems/minimum-length-of-string-after-operations/description/
		*/
		class Solution {
		public:
			int minimumLength__leetcode(string s) {
				// Step 1: Initialize a frequency array to count occurrences of each
				// character
				vector<int> charFrequency(26, 0);
				int totalLength = 0;

				// Step 2: Count the frequency of each character in the string
				for (char currentChar : s) {
					charFrequency[currentChar - 'a']++;
				}

				// Step 3: Calculate the total length after deletions count
				for (int frequency : charFrequency) {
					if (frequency == 0) continue;  // Skip characters that don't appear
					if (frequency % 2 == 0) {
						totalLength += 2;  // If frequency is even, add 2
					}
					else {
						totalLength += 1;  // If frequency is odd, add 1
					}
				}

				// Step 4: Return the minimum length after deletions count
				return totalLength;
			}
		};
	}

	namespace task_3243 {
		/*
		* https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/description/
		*/
		class Solution {
		public:
			vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
				vector<int> res;
				vector<vector<int>> adjacency_list(n);
				vector<char> visited(n);
				for (int i = 0; i < n - 1; ++i)
					adjacency_list[i].push_back(i + 1);

				for (const vector<int>& query : queries) {
					adjacency_list[query[0]].push_back(query[1]);
					for (int i = 1; i < n; ++i)
						visited[i] = 1;

					int length = 0;
					bool not_found = true;
					queue<int> queue;
					queue.push(0);
					while (not_found) {
						size_t size = queue.size();
						for (size_t i = 0; i < size && not_found; ++i) {
							int v = queue.front();
							queue.pop();
							for (const int neighbour : adjacency_list[v]) {
								if (visited[neighbour]) {
									visited[neighbour] = 0;
									if (neighbour == n - 1) {
										not_found = false;
										break;
									}
									queue.push(neighbour);
								}
							}
						}
						++length;
					}
					res.push_back(length);
				}
				return res;
			}
		};
	}

	namespace task_3254 {
		/*
		* https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/description/
		*/
		class Solution {
		public:
			vector<int> resultsArray_leetcode(vector<int>& nums, int k) {
				if (k == 1)
					return nums;

				size_t length = nums.size();
				vector<int> result(length - k + 1, -1);
				int consecutiveCount = 1;

				for (size_t i = 0; i < length - 1; i++) {
					if (nums[i] + 1 == nums[i + 1])
						consecutiveCount++;
					else
						consecutiveCount = 1;
					if (consecutiveCount >= k)
						result[i - k + 2] = nums[i + 1];
				}

				return result;
			}
		};
	}

	namespace task_3264 {
		/*
		* https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/description/
		*/
		class Solution {
		public:
			vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
				priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
				int size = nums.size();
				for (int i = 0; i < size; ++i)
					queue.push({ nums[i], i });
				for (int i = 0; i < k; ++i) {
					auto top = queue.top();
					queue.pop();
					top.first *= multiplier;
					queue.push(top);
				}
				while (!queue.empty()) {
					auto top = queue.top();
					queue.pop();
					nums[top.second] = top.first;
				}
				return nums;
			}
		};
	}

	namespace task_3272 {
		/*
		* https://leetcode.com/problems/find-the-count-of-good-integers/description/
		*/
		class Solution {
		public:
			long long countGoodIntegers(int n, int k) {
				unordered_set<string> dict;
				int base = pow(10, (n - 1) / 2);
				int skip = n & 1;
				/* Enumerate the number of palindrome numbers of n digits */
				for (int i = base; i < base * 10; i++) {
					string s = to_string(i);
					s += string(s.rbegin() + skip, s.rend());
					long long palindromicInteger = stoll(s);
					/* If the current palindrome number is a k-palindromic integer */
					if (palindromicInteger % k == 0) {
						sort(s.begin(), s.end());
						dict.emplace(s);
					}
				}

				vector<long long> factorial(n + 1, 1);
				long long ans = 0;
				for (int i = 1; i <= n; i++)
					factorial[i] = factorial[i - 1] * i;
				for (const string& s : dict) {
					vector<int> cnt(10);
					for (char c : s)
						cnt[c - '0']++;
					/* Calculate permutations and combinations */
					long long tot = (n - cnt[0]) * factorial[n - 1];
					for (int x : cnt)
						tot /= factorial[x];
					ans += tot;
				}

				return ans;
			}
		};
	}

	namespace task_3305 {
		/*
		* https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/description/
		*/
		class Solution {
		public:
			int countOfSubstrings(string word, int k) {
				return atLeastK(word, k) - atLeastK(word, k + 1);
			}

			int atLeastK(string word, int k) {
				int count_consonants = 0;
				unordered_map<char, int> vowels;
				const size_t size = word.size();
				int count_substrings = 0;

				for (size_t i = 0, start = 0; i < size; ++i) {
					char c = word[i];
					if (isVowel(c))
						++vowels[c];
					else
						count_consonants++;

					while (vowels.size() == 5 && count_consonants >= k) {
						count_substrings += size - i;
						char start_c = word[start];
						if (isVowel(start_c)) {
							if (--vowels[start_c] == 0)
								vowels.erase(start_c);
						}
						else {
							count_consonants--;
						}
						start++;
					}
				}

				return count_substrings;
			}

			bool isVowel(char c) {
				return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
			}
		};
	}

	namespace task_3306 {
		/*
		* https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/description/
		*/
		class Solution {
		public:
			long long countOfSubstrings(string word, int k) {
				return atLeastK(word, k) - atLeastK(word, k + 1);
			}

			long long atLeastK(string word, int k) {
				int count_consonants = 0;
				unordered_map<char, int> vowels;
				const size_t size = word.size();
				long long count_substrings = 0;

				for (size_t i = 0, start = 0; i < size; ++i) {
					char c = word[i];
					if (isVowel(c))
						++vowels[c];
					else
						count_consonants++;

					while (vowels.size() == 5 && count_consonants >= k) {
						count_substrings += size - i;
						char start_c = word[start];
						if (isVowel(start_c)) {
							if (--vowels[start_c] == 0)
								vowels.erase(start_c);
						}
						else {
							count_consonants--;
						}
						start++;
					}
				}

				return count_substrings;
			}

			bool isVowel(char c) {
				return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
			}
		};
	}

	namespace task_3335 {
		/*
		* https://leetcode.com/problems/total-characters-in-string-after-transformations-i/description/
		*/
		class Solution {
		public:
			static const long long mod = 1000000007;

			int lengthAfterTransformations(string s, int t) {
				size_t size = s.size(), count = t + 26;
				vector<int> dp(count, 1);
				long long length = 0;
				for (size_t i = 26; i < count; ++i)
					dp[i] = (dp[i - 26] + dp[i - 25]) % mod;
				for (const char c : s)
					length = (length + dp[t + c - 'a']) % mod;
				return length;
			}

			int lengthAfterTransformations__leetcode(string s, int t) {
				vector<int> cnt(26);
				for (char ch : s)
					++cnt[ch - 'a']; // count of letters

				for (int round = 0; round < t; ++round) {
					vector<int> nxt(26);
					nxt[0] = cnt[25]; // count 'a' is count of 'z' of previous step
					nxt[1] = (cnt[25] + cnt[0]) % mod;  // count 'b' is count of 'z' and 'a' of previous step
					for (int i = 2; i < 26; ++i)
						nxt[i] = cnt[i - 1];

					cnt = move(nxt);
				}
				int ans = 0;
				for (int i = 0; i < 26; ++i)
					ans = (ans + cnt[i]) % mod;

				return ans;
			}
		};
	}

	namespace task_3337 {
		/*
		* https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/description/
		*/

		static constexpr int L = 26;
		static constexpr int mod = 1000000007;


		// matrix multiplication
		struct Mat {
			Mat() { memset(a, 0, sizeof(a)); }
			Mat(const Mat& that) {
				for (int i = 0; i < L; ++i) {
					for (int j = 0; j < L; ++j) {
						a[i][j] = that.a[i][j];
					}
				}
			}
			Mat& operator=(const Mat& that) {
				if (this != &that) {
					for (int i = 0; i < L; ++i) {
						for (int j = 0; j < L; ++j) {
							a[i][j] = that.a[i][j];
						}
					}
				}
				return *this;
			}

			int a[L][L];
		};

		Mat operator*(const Mat& u, const Mat& v) {
			Mat w;
			for (int i = 0; i < L; ++i) {
				for (int j = 0; j < L; ++j) {
					for (int k = 0; k < L; ++k) {
						w.a[i][j] =
							(w.a[i][j] + (long long)u.a[i][k] * v.a[k][j]) % mod;
					}
				}
			}
			return w;
		}

		// identity matrix
		Mat I() {
			Mat w;
			for (int i = 0; i < L; ++i) {
				w.a[i][i] = 1;
			}
			return w;
		}

		// matrix exponentiation by squaring
		Mat quickmul(const Mat& x, int y) {
			Mat ans = I(), cur = x;
			while (y) {
				if (y & 1) {
					ans = ans * cur;
				}
				cur = cur * cur;
				y >>= 1;
			}
			return ans;
		}

		class Solution {
		public:
			int lengthAfterTransformations(string s, int t, vector<int>& nums) {
				Mat T;
				for (int i = 0; i < 26; ++i) {
					for (int j = 1; j <= nums[i]; ++j) {
						T.a[(i + j) % 26][i] = 1;
					}
				}
				Mat res = quickmul(T, t);
				int ans = 0;
				vector<int> f(26);
				for (char ch : s) {
					++f[ch - 'a'];
				}
				for (int i = 0; i < 26; ++i) {
					for (int j = 0; j < 26; ++j) {
						ans = (ans + (long long)res.a[i][j] * f[j]) % mod;
					}
				}
				return ans;
			}
		};
	}

	namespace task_3341 {
		/*
		* https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/
		*/
		class Solution {
		public:
			int minTimeToReach(vector<vector<int>>& moveTime) {
				const int n = moveTime.size(), m = moveTime[0].size();
				vector<vector<int>> min_time(n, vector<int>(m, INT32_MAX));
				min_time[0][0] = 0;
				priority_queue<vector<int>, vector<vector<int>>, greater<>> queue;
				queue.push({ 0,0,0 });
				while (!queue.empty())
				{
					const vector<int>& pos = queue.top();
					int time = pos[0], i = pos[1], j = pos[2];
					queue.pop();

					if (i + 1 < n && min_time[i + 1][j] == INT32_MAX) {
						min_time[i + 1][j] = max(moveTime[i + 1][j], time) + 1;
						queue.push({ min_time[i + 1][j], i + 1, j });
					}
					if (j + 1 < m && min_time[i][j + 1] == INT32_MAX) {
						min_time[i][j + 1] = max(moveTime[i][j + 1], time) + 1;
						queue.push({ min_time[i][j + 1], i, j + 1 });
					}
					if (i > 0 && min_time[i - 1][j] == INT32_MAX) {
						min_time[i - 1][j] = max(moveTime[i - 1][j], time) + 1;
						queue.push({ min_time[i - 1][j], i - 1, j });
					}
					if (j > 0 && min_time[i][j - 1] == INT32_MAX) {
						min_time[i][j - 1] = max(moveTime[i][j - 1], time) + 1;
						queue.push({ min_time[i][j - 1], i, j - 1 });
					}
				}

				return min_time[n - 1][m - 1];
			}
		};
	}

	namespace task_3342 {
		/*
		* https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/description/
		*/
		class Solution {
		public:
			int minTimeToReach(vector<vector<int>>& moveTime) {
				const int n = moveTime.size(), m = moveTime[0].size();
				vector<vector<int>> min_time(n, vector<int>(m, INT32_MAX));
				min_time[0][0] = 0;
				priority_queue<vector<int>, vector<vector<int>>, greater<>> queue;
				queue.push({ 0,0,0,0 }); // extra_time to check wait another second or not
				while (!queue.empty())
				{
					const vector<int>& pos = queue.top();
					int time = pos[0], extra_time = pos[1], i = pos[2], j = pos[3];
					queue.pop();

					if (i + 1 < n && min_time[i + 1][j] == INT32_MAX) {
						min_time[i + 1][j] = max(moveTime[i + 1][j], time) + 1 + extra_time;
						queue.push({ min_time[i + 1][j], extra_time ^ 1, i + 1, j });
					}
					if (j + 1 < m && min_time[i][j + 1] == INT32_MAX) {
						min_time[i][j + 1] = max(moveTime[i][j + 1], time) + 1 + extra_time;
						queue.push({ min_time[i][j + 1], extra_time ^ 1, i, j + 1 });
					}
					if (i > 0 && min_time[i - 1][j] == INT32_MAX) {
						min_time[i - 1][j] = max(moveTime[i - 1][j], time) + 1 + extra_time;
						queue.push({ min_time[i - 1][j], extra_time ^ 1, i - 1, j });
					}
					if (j > 0 && min_time[i][j - 1] == INT32_MAX) {
						min_time[i][j - 1] = max(moveTime[i][j - 1], time) + 1 + extra_time;
						queue.push({ min_time[i][j - 1], extra_time ^ 1, i, j - 1 });
					}
				}

				return min_time[n - 1][m - 1];
			}
		};
	}

	namespace task_3343 {
		/*
		* https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/description/
		*/
		class Solution {
		public:
			constexpr static long long MOD = 1e9 + 7;

			int countBalancedPermutations(string num) {
				int tot = 0, n = num.size();
				vector<int> cnt(10);
				for (char ch : num) {
					int d = ch - '0';
					cnt[d]++;
					tot += d;
				}
				if (tot % 2 != 0) {
					return 0;
				}

				int target = tot / 2;
				int maxOdd = (n + 1) / 2;
				vector<vector<long long>> comb(maxOdd + 1,
					vector<long long>(maxOdd + 1));
				vector<vector<long long>> f(target + 1, vector<long long>(maxOdd + 1));
				for (int i = 0; i <= maxOdd; i++) {
					comb[i][i] = comb[i][0] = 1;
					for (int j = 1; j < i; j++) {
						comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
					}
				}

				f[0][0] = 1;
				int psum = 0, totSum = 0;
				for (int i = 0; i <= 9; i++) {
					/* Sum of the number of the first i digits */
					psum += cnt[i];
					/* Sum of the first i numbers */
					totSum += i * cnt[i];
					for (int oddCnt = min(psum, maxOdd);
						oddCnt >= max(0, psum - (n - maxOdd)); oddCnt--) {
						/* The number of bits that need to be filled in even numbered
						 * positions */
						int evenCnt = psum - oddCnt;
						for (int curr = min(totSum, target);
							curr >= max(0, totSum - target); curr--) {
							long long res = 0;
							for (int j = max(0, cnt[i] - evenCnt);
								j <= min(cnt[i], oddCnt) && i * j <= curr; j++) {
								/* The current digit is filled with j positions at odd
								 * positions, and cnt[i] - j positions at even positions
								 */
								long long ways =
									comb[oddCnt][j] * comb[evenCnt][cnt[i] - j] % MOD;
								res = (res + ways * f[curr - i * j][oddCnt - j] % MOD) %
									MOD;
							}
							f[curr][oddCnt] = res % MOD;
						}
					}
				}

				return f[target][maxOdd];
			}
		};
	}

	namespace task_3355 {
		/*
		* https://leetcode.com/problems/zero-array-transformation-i/
		*/
		class Solution {
		public:
			bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
				sort(queries.begin(), queries.end());
				priority_queue<int, std::vector<int>, std::greater<int>> ends;
				int q_size = queries.size(), q_i = 0, size = nums.size();
				for (int i = 0; i < size; ++i) {
					while (!ends.empty() && ends.top() < i)
						ends.pop();
					for (; q_i < q_size && queries[q_i][0] == i; ++q_i)
						ends.push(queries[q_i][1]);

					if (nums[i] > ends.size())
						return false;
				}
				return true;
			}

			bool isZeroArray__new(vector<int>& nums, vector<vector<int>>& queries) {
				sort(queries.begin(), queries.end());
				priority_queue<int, vector<int>, greater<>> queue;
				size_t size = nums.size(), size_q = queries.size(), j = 0;
				for (size_t i = 0; i < size; ++i) {
					for (; j < size_q && i == queries[j][0]; ++j)
						queue.push(queries[j][1]);
					while (!queue.empty() && queue.top() < i)
						queue.pop();
					if (nums[i] > queue.size())
						return false;
				}
				return true;
			}

			bool isZeroArray__leetcode(vector<int>& nums, vector<vector<int>>& queries) {
				vector<int> deltaArray(nums.size() + 1, 0);
				for (const auto& query : queries) {
					int left = query[0];
					int right = query[1];
					deltaArray[left] += 1;
					deltaArray[right + 1] -= 1;
				}
				vector<int> operationCounts;
				int currentOperations = 0;
				for (int delta : deltaArray) {
					currentOperations += delta;
					operationCounts.push_back(currentOperations);
				}
				for (int i = 0; i < nums.size(); ++i) {
					if (operationCounts[i] < nums[i])
						return false;
				}
				return true;
			}
		};
	}

	namespace task_3356 {
		/*
		* https://leetcode.com/problems/zero-array-transformation-ii/description/
		*/
		class Solution {
		public:
			int minZeroArray__leetcode(vector<int>& nums, vector<vector<int>>& queries) {
				int size = nums.size(), sum = 0, k = -1;
				vector<int> differenceArray(size + 1);

				// Iterate through nums
				for (int i = 0; i < size; ++i) {
					// Iterate through queries while current index of nums cannot equal
					// zero
					while (sum + differenceArray[i] < nums[i]) {
						++k;
						// Zero array isn't formed after all queries are processed
						if (k == queries.size())
							return -1;

						int left = queries[k][0], right = queries[k][1], val = queries[k][2];

						// Process start and end of range
						if (right >= i) {
							differenceArray[max(left, i)] += val;
							differenceArray[right + 1] -= val;
						}
					}
					// Update prefix sum at current index
					sum += differenceArray[i];
				}
				return k + 1;
			}
		};
	}

	namespace task_3362 {
		/*
		* https://leetcode.com/problems/zero-array-transformation-iii/description/
		*/
		class Solution {
		public:
			int maxRemoval__leetcode(vector<int>& nums, vector<vector<int>>& queries) {
				sort(queries.begin(), queries.end());

				priority_queue<int> heap;
				vector<int> deltaArray(nums.size() + 1, 0);
				int operations = 0;
				for (int i = 0, j = 0; i < nums.size(); ++i) {
					operations += deltaArray[i];
					while (j < queries.size() && queries[j][0] == i) {
						heap.push(queries[j][1]);
						++j;
					}
					while (operations < nums[i] && !heap.empty() && heap.top() >= i) {
						operations += 1;
						deltaArray[heap.top() + 1] -= 1;
						heap.pop();
					}
					if (operations < nums[i]) {
						return -1;
					}
				}
				return heap.size();
			}
		};
	}

	namespace task_3372 {
		/*
		* https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/description/
		*/
		class Solution {
		public:
			int K, n, m;
			vector<int> visited;

			vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
				n = 0, m = 0;
				for (const auto& edge : edges1) {
					n = max(n, edge[0]);
					n = max(n, edge[1]);
				}
				for (const auto& edge : edges2) {
					m = max(m, edge[0]);
					m = max(m, edge[1]);
				}
				++n, ++m;
				visited = vector<int>(max(n, m));
				vector<vector<int>> adjacency_list1(n), adjacency_list2(m);
				for (const auto& edge : edges1) {
					adjacency_list1[edge[0]].push_back(edge[1]);
					adjacency_list1[edge[1]].push_back(edge[0]);
				}
				for (const auto& edge : edges2) {
					adjacency_list2[edge[0]].push_back(edge[1]);
					adjacency_list2[edge[1]].push_back(edge[0]);
				}
				K = k;
				int max_degree = 0;
				for (int i = 0; i < m; ++i)
					max_degree = max(max_degree, BFS_count(adjacency_list2, i, m));
				++K;
				vector<int> res(n);
				for (int i = 0; i < n; ++i)
					res[i] = BFS_count(adjacency_list1, i, n) + max_degree;

				return res;
			}

			int BFS_count(const vector<vector<int>>& adjacency_list, int vertex, int vertexes) {
				queue<int> queue;
				queue.push(vertex);
				visited[vertex] = 1;
				int count = 0;
				for (int i = 0; i < K && !queue.empty(); ++i) {
					int size = queue.size();
					for (int j = 0; j < size; ++j) {
						++count;
						vertex = queue.front();
						queue.pop();
						for (const int neighbour : adjacency_list[vertex])
							if (visited[neighbour] == 0) {
								visited[neighbour] = 1;
								queue.push(neighbour);
							}
					}
				}
				for (int i = 0; i < vertexes; ++i)
					visited[i] = 0;

				return count;
			}
		};
	}

	namespace task_3373 {
		/*
		* https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-iш/description/
		*/
		class Solution {
		public:
			vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
				int n = 0, m = 0;
				int groupCounts[2];
				groupCounts[0] = 0, groupCounts[1] = 0;
				for (const auto& edge : edges1) {
					n = max(n, edge[0]);
					n = max(n, edge[1]);
				}
				for (const auto& edge : edges2) {
					m = max(m, edge[0]);
					m = max(m, edge[1]);
				}
				++n, ++m;
				vector<vector<int>> adjacency_list1(n), adjacency_list2(m);
				for (const auto& edge : edges1) {
					adjacency_list1[edge[0]].push_back(edge[1]);
					adjacency_list1[edge[1]].push_back(edge[0]);
				}
				for (const auto& edge : edges2) {
					adjacency_list2[edge[0]].push_back(edge[1]);
					adjacency_list2[edge[1]].push_back(edge[0]);
				}

				// calculate the maximum number of odd or even group in tree 2
				queue<int> queue;
				queue.push(0);
				vector<int> visited(m);
				visited[0] = 1;
				int count_odd = 0, count_even = 0;
				for (int i = 0; !queue.empty(); ++i) {
					int size = queue.size();
					if (i & 1)
						count_odd += size;
					else
						count_even += size;
					for (int j = 0; j < size; ++j) {
						int vertex = queue.front();
						queue.pop();
						for (const int neighbour : adjacency_list2[vertex])
							if (visited[neighbour] == 0) {
								visited[neighbour] = 1;
								queue.push(neighbour);
							}
					}
				}

				int secondTreeCount = max(count_odd, count_even);
				// calculate groups and their count in tree 2
				queue.push(0);
				vector<int> groups(n, 2);
				groups[0] = 0;
				for (int i = 0; !queue.empty(); ++i) {
					int size = queue.size();
					int group = i & 1;
					groupCounts[group] += size;
					group ^= 1;
					for (int j = 0; j < size; ++j) {
						int vertex = queue.front();
						queue.pop();
						for (const int neighbour : adjacency_list1[vertex])
							if (groups[neighbour] == 2) {
								groups[neighbour] = group;
								queue.push(neighbour);
							}
					}
				}

				for (int i = 0; i < n; ++i)
					groups[i] = groupCounts[groups[i]] + secondTreeCount;

				return groups;
			}
		};
	}

	namespace task_3375 {
		/*
		* https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/description/
		*/
		class Solution {
		public:
			int minOperations(vector<int>& nums, int k) {
				unordered_set<int> set;
				for (int n : nums) {
					if (n > k)
						set.insert(n);
					else if (n < k)
						return -1;
				}
				return set.size();
			}
		};
	}

	namespace task_3392 {
		/*
		* https://leetcode.com/problems/count-of-interesting-subarrays/description/
		*/
		class Solution {
		public:
			int countSubarrays(vector<int>& nums) {
				size_t size = nums.size() - 2;
				int count = 0;
				for (size_t i = 0; i < size; ++i)
					if (((nums[i] + nums[i + 2]) << 1) == nums[i + 1])
						++count;
				return count;
			}
		};
	}

	namespace task_3394 {
		/*
		* https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/description/
		*/
		class Solution {
		public:
			bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
				// we need only start_x, end_x and sort by them
				for (vector<int>& rect : rectangles)
					swap(rect[1], rect[2]);
				if (checkValidCuts(rectangles))
					return true;

				// we need only start_y, end_y and sort by them
				for (vector<int>& rect : rectangles) {
					swap(rect[0], rect[2]);
					swap(rect[1], rect[3]);
				}
				return checkValidCuts(rectangles);
			}

			bool checkValidCuts(vector<vector<int>>& rectangles) {
				sort(rectangles.begin(), rectangles.end());
				int count_section = 1, last_end = rectangles[0][1];
				for (const vector<int>& rect : rectangles) {
					if (last_end <= rect[0])
						++count_section;
					last_end = max(last_end, rect[1]);
				}
				return count_section > 2;
			}
		};
	}

	namespace task_3396 {
		/*
		* https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/description/
		*/
		class Solution {
		public:
			int minimumOperations(vector<int>& nums) {
				unordered_set<int> set;
				int i = nums.size() - 1;
				for (; i >= 0 && !set.contains(nums[i]); --i)
					set.insert(nums[i]);
				return ceil(++i / (double)3);
			}
		};
	}

	namespace task_3403 {
		/*
		* https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/description/
		*/
		class Solution {
		public:
			int size;

			string answerString(string word, int numFriends) {
				if (numFriends == 1)
					return word;
				size = word.size();
				char max_char = word[0];
				string max_str = getStr(word, numFriends, 0);
				for (int i = 1; i < size; ++i) {
					if (max_char < word[i]) {
						max_char = word[i];
						max_str = getStr(word, numFriends, i);
					}
					else if (max_char == word[i]) {
						string str = getStr(word, numFriends, i);
						if (max_str < str)
							max_str = str;
					}
				}
				return max_str;
			}

			string getStr(const string& word, const int numFriends, const int ind) const {
				return word.substr(ind, size - ind - max(numFriends - ind - 1, 0));
			}
		};
	}
}
