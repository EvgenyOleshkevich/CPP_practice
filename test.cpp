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


using namespace leetcode::task_802;

int main() {
    //func();
    //return 0;
    vector<int> v1({ 1,3,4,2 });
    vector<int> v2({ 0,0,0 });
    vector<vector<int>> mat({{ 1,2},{2,3},{5},{0},{5},{},{} });
    vector<vector<int>> mat2({ {0,1},{2,2}, {1,4} });
    vector<vector<char>> mat_char(1);
    vector<string> words1({ "//","/ " });
    vector<string> words2({ "/a","/a/b","/c/d","/c/d/e","/c/f" });
    vector<char> vec_char1({ 'a','b','c','c','e','d' });
    vector<char> vec_char2({ 'b','c','b','e','b','e' });
    //auto head = vector2list({ 5,3,1,2,5,1,2 });

    mat_char[0] = { '#','.','#' };
    map<int, int> m{ {1,1} };
    auto it = m.find(1);
    it->second = 2;
    --it;
    //cout << (it == m.end()) << endl;
   
    Solution k;
    cout << k.eventualSafeNodes(mat) << endl;

    return 0;
}