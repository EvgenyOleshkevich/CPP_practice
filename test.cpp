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
using namespace leetcode::task_1871;

int main() {
    vector<int> v1({ 0,3,0,6,3,3,4 });
    vector<int> v2({ 1,2,4,2,5,7,2,4,9,0 });
    vector<vector<int>> mat({{0, 3, 3}, {3, 4, 3}, {4, 1, 3}, {0, 5, 1}, {5, 1, 100}, {0, 6, 2}, {6, 1, 100}, {0, 7, 1}, {7, 8, 1}, {8, 9, 1}, {9, 1, 1}, {1, 10, 1}, {10, 2, 1}, {1, 2, 100}} );
    //mat{0} = { 0,1,100 };
    //mat{1} = { 1,2,100 };
    //mat{2} = { 0,2,500 };
    vector<vector<char>> mat_char(4);
    //mat_char{0} = { '1','0','1','0','0' };
    //mat_char{1} = { '1','0','1','1','1' };
    //mat_char{2} = { '1','1','1','1','1' };
    //mat_char{3} = { '1','0','0','1','0' };

    vector<string> words({ "leet","code" });
    Solution k;
    cout << k.canReach("0101001110", 2, 4) << endl;

    return 0;
}