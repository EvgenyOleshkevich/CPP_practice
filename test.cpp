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
#include "leetcode.h"
#include "leetcode2.h"
#include "some_test_code.h"
using namespace std;
using namespace leetcode;
using namespace leetcode::utils;
using namespace leetcode::task_726;

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
int main() {
    vector<int> v1({ 4,2,2,2,4,4,2,2 });
    vector<int> v2({ 0,0,0 });
    vector<vector<int>> mat({ {5,1},{2,3},{5,3},{0,2},{3,1},{5,2},{4,0} });
    vector<vector<char>> mat_char(4);
    vector<string> words1({ "cat","bat","rat" });
    vector<string> words2({ "KNN","KFC","Burger King","Tapioca Express","Shogun" });
    vector<char> vec({ 'h','e','l','l','o' });

    mat_char[0] = { '1','0','1','0','0' };
    mat_char[1] = { '1','0','1','1','1' };
    mat_char[2] = { '1','1','1','1','1' };
    mat_char[3] = { '1','0','0','1','0' };

    auto head = vector2list({ 5,3,1,2,5,1,2 });
    Solution k; // 348
    cout << k.countOfAtoms("Mg(OH)2") << endl;

    return 0;
}