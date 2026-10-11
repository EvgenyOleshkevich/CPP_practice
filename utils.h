#pragma once
#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstring>
#include <string>
#include <sstream>
#include <cassert>
#include <tuple>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <algorithm>
#include <random>
#include <numeric>
#include <array>
#include <bitset>
using namespace std;


namespace leetcode {
	struct ListNode {
		int val;
		ListNode* next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode* next) : val(x), next(next) {}
	};

	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	};

	struct Node {
		int val;
		Node* left;
		Node* right;
		Node* next;

		Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
		Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
		Node(int x, Node* left, Node* right, Node* next) : val(x), left(left), right(right), next(next) {}
	};

	class NodeNTree {
	public:
		int val;
		vector<NodeNTree*> children;

		NodeNTree() {}

		NodeNTree(int _val) {
			val = _val;
		}

		NodeNTree(int _val, vector<NodeNTree*> _children) {
			val = _val;
			children = _children;
		}
	};

	struct NodeRandom {
		int val;
		NodeRandom* next;
		NodeRandom* random;

		NodeRandom() : val(0), next(nullptr), random(nullptr) {}
		NodeRandom(int x) : val(x), next(nullptr), random(nullptr) {}
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

		ostream& operator<<(ostream& os, const vector<string>& v) {
			for (const string& val : v)
				os << val << endl;
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

		ListNode* reverse(ListNode* head) {
			if (head == nullptr)
				return nullptr;
			ListNode* next = head->next;
			head->next = nullptr;

			while (next != nullptr) {
				ListNode* temp = next->next;
				next->next = head;
				head = next;
				next = temp;
			}
			return head;
		}

		ListNode* findMiddle(ListNode* head) {
			/*
				for odd return middle
				for even return left to middle
			*/
			if (head == nullptr)
				return nullptr;
			ListNode* fast = head, * slow = head;
			head->next = nullptr;

			while (fast->next && fast->next->next) {
				slow = slow->next;
				fast = fast->next->next;
			}
			return slow;
		}

		int GCD(int x, int y) {
			while (x != y) {
				if (x > y)
					x -= y;
				else
					y -= x;
			}
			return x;
		}

		int GCD_fast(int x, int y) {
			while (y != 0) {
				int remainder = x % y;
				x = y;
				y = remainder;
			}
			return x;
		}

		size_t bin_search(const vector<int>& nums, const int value) {
			size_t l = 0, r = nums.size();
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

		size_t bin_search(const vector<int>& nums, const int value, size_t l, size_t r) {
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

		vector<string> split(const string& s, const string delimiter) {
			vector<string> tokens;
			size_t pos_from = 0, pos_to = 0, del_size = delimiter.size();
			string token;
			while ((pos_to = s.find(delimiter, pos_from)) != string::npos) {
				token = s.substr(pos_from, pos_to - pos_from);
				if (!token.empty())
					tokens.push_back(token);
				pos_from = pos_to + del_size;
			}
			token = s.substr(pos_from);
			if (!token.empty())
				tokens.push_back(token);

			return tokens;
		}

		vector<string> split(const string& s, const char delimiter = '.') {
			vector<string> tokens;
			size_t pos_from = 0, pos_to = 0;
			string token;
			while ((pos_to = s.find(delimiter, pos_from)) != string::npos) {
				token = s.substr(pos_from, pos_to - pos_from);
				tokens.push_back(token);
				pos_from = pos_to + 1;
			}
			tokens.push_back(s.substr(pos_from));

			return tokens;
		}

		vector<string> split(const string& s) {
			const char delimiter = ' ';
			vector<string> tokens;
			size_t pos_from = 0, pos_to = 0;
			string token;
			while ((pos_to = s.find(delimiter, pos_from)) != string::npos) {
				if (pos_to - pos_from > 0) {
					token = s.substr(pos_from, pos_to - pos_from);
					tokens.push_back(token);
				}
				pos_from = pos_to + 1;
			}
			if (pos_from != s.size())
				tokens.push_back(s.substr(pos_from));

			return tokens;
		}

		string concat(const vector<string>& words) {
			string res;
			for (const string& word : words) {
				res += word;
				res.push_back(' ');
			}
			if (!res.empty())
				res.pop_back();
			return res;
		}

		vector<vector<int>> get_adjacency_list(vector<vector<int>>& edges, int vertexes) {
			vector<vector<int>> adjacency_list(vertexes);
			for (const auto& edge : edges) {
				adjacency_list[edge[0]].push_back(edge[1]);
				adjacency_list[edge[1]].push_back(edge[0]);
			}
			return adjacency_list;
		}

		void BFS(const vector<vector<int>>& adjacency_list) {
			queue<int> queue;
			queue.push(0);
			vector<int> visited(adjacency_list.size());
			visited[0] = 1;
			int count = 0;
			while (!queue.empty()) {
				int size = queue.size();
				for (int j = 0; j < size; ++j) {
					auto vertex = queue.front();
					queue.pop();
					for (const int neighbour : adjacency_list[vertex]) {
						if (visited[neighbour] == 0) {
							visited[neighbour] = 1;
							queue.push(neighbour);
						}
					}
				}
			}
		}

		int countBits(int n) {
			int count = 0;
			while (n != 0) {
				count += n & 1;
				n >>= 1;
			}
			return count;
		}

		// KMP
		vector<size_t> prefix_function(string s) {
			size_t n = s.length();
			vector<size_t> pi(n);
			// в i-м элементе (его индекс i-1) количество совпавших символов в начале и конце для подстроки длины i
			// p[0]=0 всегда, p[1]=1, если начинается с двух одинаковых
			for (size_t i = 1; i < n; ++i) {
				// ищем, какой префикс-суффикс можно расширить
				size_t j = pi[i - 1]; // длина предыдущего префикса-суффикса, возможно нулевая
				while (j > 0 && s[i] != s[j]) // этот нельзя расширить,
					j = pi[j - 1];   // берем длину меньшего префикса-суффикса

				if (s[i] == s[j])
					++j;  // расширяем найденный (возможно пустой) префикс-суффикс
				pi[i] = j;
			}
			return pi;
		}

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
	}

}