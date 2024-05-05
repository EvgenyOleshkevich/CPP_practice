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
using namespace leetcode::task_56;

int main() {
    vector<int> v1({ 0,3,0,6,3,3,4 });
    vector<int> v2({ 1,2,4,2,5,7,2,4,9,0 });
    vector<vector<int>> mat({{1, 3}, {2, 6}, {8, 10}, {15, 18}} );
    //mat{0} = { 0,1,100 };
    //mat{1} = { 1,2,100 };
    //mat{2} = { 0,2,500 };
    vector<vector<char>> mat_char(4);
    //mat_char{0} = { '1','0','1','0','0' };
    //mat_char{1} = { '1','0','1','1','1' };
    //mat_char{2} = { '1','1','1','1','1' };
    //mat_char{3} = { '1','0','0','1','0' };

    vector<string> words({ "eat","tea","tan","ate","nat","bat" });
    Solution k;
    vector<char> vec({ 'A','A','A','B','B','B','C','D','E','F','G','H','I','J','K' });
    cout << k.merge(mat) << endl;

    return 0;
}