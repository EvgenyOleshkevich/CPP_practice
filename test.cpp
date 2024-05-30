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
using namespace leetcode::task_1442;

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
    vector<int> v1({ 2,3,1,6,7 });
    vector<int> v2({ 0, 1, 2, 3 });
    vector<vector<int>> mat({ {7,6},{7,2},{5,2},{5,1},{8,1},{9,1},{1,11},{0,12},{0,4},{3,4},{11,3},{11,10},{10,13} });
    vector<vector<char>> mat_char(4);
    vector<string> words1({ "Shogun","Tapioca Express","Burger King","KFC" });
    vector<string> words2({ "KNN","KFC","Burger King","Tapioca Express","Shogun" });
    vector<char> vec({ 'A','A','A','B','B','B','C','D','E','F','G','H','I','J','K' });
    
    mat[0] = { 0,1,100 };
    mat[1] = { 1,2,100 };
    mat[2] = { 0,2,500 };
    mat_char[0] = { '1','0','1','0','0' };
    mat_char[1] = { '1','0','1','1','1' };
    mat_char[2] = { '1','1','1','1','1' };
    mat_char[3] = { '1','0','0','1','0' };
    

    Solution k;
    cout << k.countTriplets(v1) << endl;

    return 0;
}