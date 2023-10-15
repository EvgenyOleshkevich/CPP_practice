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
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <algorithm>
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
            for (const T val : v)
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
                int n = nums1.size();
                int m = nums2.size();
                bool odd = (n + m) & 1;
                int i1 = n >> 1;
                int i2 = m >> 1;
                if (n == 0)
                    return odd ? nums2[i2] : (nums2[i2] + nums2[i2 - 1]) / 2.0;
                if (m == 0)
                    return odd ? nums1[i1] : (nums1[i1] + nums1[i1 - 1]) / 2.0;


                int l1 = 0;
                int r1 = n;
                int l2 = 0;
                int r2 = m;
                int target = (m + n) >> 1;
                i1 = 0;

                while (i1 + i2 != target) {
                    i1 = (l1 + r1) >> 1;
                    i2 = (l2 + r2) >> 1;
                    if (nums1[i1] > nums2[i2]) {
                        if (i1 + i2 > target)
                            r1 = i1 + 1;
                        else
                            l2 = i2;
                    }
                    else {
                        if (i1 + i2 > target)
                            r2 = i2 + 1;
                        else
                            l1 = i1;
                    }

                }


                return 0;
            }

            int bin_search(vector<int>& nums, int value, int l, int r) {
                while (r - l > 1) {
                    size_t i = (r + l) / 2;
                    if (nums[i] == value)
                        return i;
                    if (nums[i] > value)
                        r = i;
                    else
                        l = i;
                }
                return l;
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

    namespace task_33 {
        /*
        * https://leetcode.com/search-in-rotated-sorted-array/description/
        */
        class Solution {
        public:
            int search(vector<int>& nums, int target) {
                const size_t size = nums.size();
                if (size < 3) {
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
}