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
#include "some_test_code.h"
using namespace std;
using namespace leetcode::utils;
using namespace leetcode::task_415;

int main() {
    vector<int> v1({ 2,3,6,7 });
    vector<int> v2({ 1,2,4,2,5,7,2,4,9,0 });
    vector<vector<int>> mat(3);
    mat[0] = { 2,1,3 };
    mat[1] = { 6,5,4 };
    mat[2] = { 7,8,9 };
    vector<vector<char>> mat_char(4);
    mat_char[0] = { '1','0','1','0','0' };
    mat_char[1] = { '1','0','1','1','1' };
    mat_char[2] = { '1','1','1','1','1' };
    mat_char[3] = { '1','0','0','1','0' };

    vector<string> words({ "leet","code" });
    Solution k;
    cout << k.addStrings("1", "99999999") << endl;

    return 0;
}