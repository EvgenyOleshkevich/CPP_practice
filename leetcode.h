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
#include <set>
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

    namespace task_124 {
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

    namespace task_367 {
        /*
        * https://leetcode.com/problems/valid-perfect-square/description/
        */
        class Solution {
        public:
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

    namespace task_633 {
        /*
        * https://leetcode.com/problems/sum-of-square-numbers/
        */
        class Solution {
        public:
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
}
