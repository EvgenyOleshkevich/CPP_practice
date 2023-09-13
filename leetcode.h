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
}