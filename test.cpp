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
//#include "leetcode_0000_0500.h"
#include "some_test_code.h"
using namespace std;
using namespace leetcode;
using namespace leetcode::utils;


using namespace leetcode::task_3629;

int main() {
	//cout << split("id1 id0 idididid", "id") << endl;
	//cout << -4 % 3;
	//func();
	//return 0;
	vector<int> v1({ 2,3,4,7,9 });
	vector<int> v2({ 9,2,3,7,-9,1,-8,5,-1,-1 });
	vector<vector<int>> mat1({ {0, 0, 0, 0, 0}, {0, 0, 3, 0, 0}, {0, 1, 0, 0, 0}, {5, 0, 0, 3, 0}, {0, 0, 0, 0, 2} });
	vector<vector<int>> mat2({ {1,3} ,{2,1},{1,1},{2,2},{1,2} });
	vector<vector<char>> mat_char({ {'a','b','b'},{'b','z','b'},{'b','b','a'} });
	vector<string> words1({ "iarapqqk" });
	vector<string> words2({ "apahhijt","larapqqk","isukkcws","siqqoacj","nloynmpm" });
	vector<vector<string>> texts({ {"MESSAGE","2","HERE"} ,{"OFFLINE","2","1"},{"OFFLINE","1","0"},{"MESSAGE","61","HERE"} });
	vector<char> vec_char1({ 'a','b','c','c','e','d' });
	vector<char> vec_char2({ 'b','c','b','e','b','e' });
	//auto head = vector2list({ 5,3,1,2,5,1,2 });

	map<int, int> m{ {1,1} };
	auto it = m.find(1);
	it->second = 2;
	--it;
	//cout << (it == m.end()) << endl;
	//TreeNode* root = new TreeNode(3, new TreeNode(5, new TreeNode(6), new TreeNode(2, new TreeNode(7), new TreeNode(4))), new TreeNode(1, new TreeNode(0), new TreeNode(8)));
	Solution k;
	cout << k.minJumps(v1) << endl;

	return 0;
}