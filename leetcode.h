#pragma once

#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>
#include <cassert>
#include <tuple>
#include <list>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <functional>
using namespace std;

namespace leetcode {
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

        //Definition for singly - linked list.
        struct ListNode {
            int val;
            ListNode* next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode* next) : val(x), next(next) {}

        };
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
}