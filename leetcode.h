#pragma once

#include <iostream>
#include <cstddef>
#include <cstring>
#include <string>
#include <cassert>
#include <tuple>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <algorithm>
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

        struct ListNode {
            int val;
            ListNode* next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode* next) : val(x), next(next) {}
        };


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
        struct ListNode {
            int val;
            ListNode* next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode* next) : val(x), next(next) {}

        };

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
        struct ListNode {
            int val;
            ListNode* next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode* next) : val(x), next(next) {}

        };

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
                        if (min < lists[i]->val) {
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
        struct ListNode {
            int val;
            ListNode* next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode* next) : val(x), next(next) {}

        };

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
        };
    }
}