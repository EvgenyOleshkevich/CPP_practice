#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <tuple>
#include <list>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include "leetcode.h"
#include "leetcode2.h"
#include "some_test_code.h"
using namespace std;
using namespace leetcode;
using namespace leetcode::utils;
using namespace leetcode::task_2699;

/*
Solution::Node* nodes(int from, int to) {
    auto head = new Solution::Node(from);
    Solution::Node* ptr = head;
    for (size_t i = from +1; i <= to; i++) {
        ptr->next = new Solution::Node(i);
        ptr->next->prev = ptr;
        ptr = ptr->next;
    }
    return head;
}
*/

void func() {
    size_t size = 70001;
    vector<string> instructions(size);
    vector<vector<int>> steps(1, { 1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20 });
    vector<pair<int, int>> count_used(size);
    vector<int> not_used(size, 1);
    size_t count = steps[0].size();
    for (const int n : steps[0]) {
        instructions[n] = to_string(n);
        not_used[n] = 0;
    }

    for (size_t i = 1; i < 10 && count < size; i++) {
        vector<int> new_numbers;
        int n;
        for (size_t j = 0; (j << 1) < i; ++j)
            for (const int n1 : steps[j])
                for (const int n2 : steps[i - j - 1]) {
                    n = n1 + n2;
                    if (n > 0 && n < size && not_used[n]) {
                        new_numbers.push_back(n);
                        not_used[n] = 0;
                        instructions[n] = "(" + instructions[n1] + ")+(" + instructions[n2] + ")";
                        ++count_used[n1].first;
                        ++count_used[n2].first;
                        ++count;
                    }
                    n = n1 * n2;
                    if (n > 0 && n < size && not_used[n]) {
                        new_numbers.push_back(n);
                        not_used[n] = 0;
                        instructions[n] = "(" + instructions[n1] + ")*(" + instructions[n2] + ")";
                        ++count_used[n1].first;
                        ++count_used[n2].first;
                        ++count;
                    }
                    n = n1 - n2;
                    if (n > 0 && n < size && not_used[n]) {
                        new_numbers.push_back(n);
                        not_used[n] = 0;
                        instructions[n] = "(" + instructions[n1] + ")-(" + instructions[n2] + ")";
                        ++count_used[n1].first;
                        ++count_used[n2].first;
                        ++count;
                    }
                    n = n2 - n1;
                    if (n > 0 && n < size && not_used[n]) {
                        new_numbers.push_back(n);
                        not_used[n] = 0;
                        instructions[n] = "(" + instructions[n2] + ")-(" + instructions[n1] + ")";
                        ++count_used[n1].first;
                        ++count_used[n2].first;
                        ++count;
                    }
                    long double n_big;
                    if (n2 < 21) {
                        n_big = pow(n1, n2);
                        n = n_big;
                        if (n_big > 0 && n_big < size && not_used[n]) {
                            new_numbers.push_back(n);
                            not_used[n] = 0;
                            instructions[n] = "(" + instructions[n1] + ")^(" + instructions[n2] + ")";
                            ++count_used[n1].first;
                            ++count_used[n2].first;
                            ++count;
                        }
                    }
                    if (n1 < 21) {
                        n_big = pow(n2, n1);
                        n = n_big;
                        if (n_big > 0 && n_big < size && not_used[n]) {
                            new_numbers.push_back(n);
                            not_used[n] = 0;
                            instructions[n] = "(" + instructions[n2] + ")^(" + instructions[n1] + ")";
                            ++count_used[n1].first;
                            ++count_used[n2].first;
                            ++count;
                        }
                    }
                }
        steps.push_back(new_numbers);
    }
    ofstream file("number.txt");
    for (size_t i = 1; i < size; ++i) {
        file << i << " : " << instructions[i] << endl;
        count_used[i].second = i;
    }
    sort(count_used.begin(), count_used.end());
    reverse(count_used.begin(), count_used.end());
    file.close();
    file.open("count_used.txt");
    for (const auto& n : count_used)
        file << n.second << " : " << n.first << endl;
    file.close();
    cout << steps.size() << endl;
}


int main() {
    //func();
    //return 0;
    vector<int> v1({ 1,2,3,4 });
    vector<int> v2({ 0,0,0 });
    vector<vector<int>> mat({ {0,1,-1},{2,0,2},{3,2,6},{2,1,10},{3,0,-1} });
    vector<vector<int>> mat2();
    vector<vector<char>> mat_char(4);
    vector<string> words1({ "//","/ " });
    vector<string> words2({ "KNN","KFC","Burger King","Tapioca Express","Shogun" });
    vector<char> vec_char1({ 'a','b','c','c','e','d' });
    vector<char> vec_char2({ 'b','c','b','e','b','e' });

    mat_char[0] = { '1','0','1','0','0' };
    mat_char[1] = { '1','0','1','1','1' };
    mat_char[2] = { '1','1','1','1','1' };
    mat_char[3] = { '1','0','0','1','0' };

    auto head = vector2list({ 5,3,1,2,5,1,2 });
    Solution k; // 348
    cout << k.modifiedGraphEdges(4, mat, 1, 3, 12) << endl;

    return 0;
}