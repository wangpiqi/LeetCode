#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <ctype.h>
#include <string>
#include <sstream>
#include <mutex>
#include <map>
#include <bitset>
#include <set>
#include <unordered_set>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

#pragma region
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
	}));
}

void trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
		return !isspace(ch);
	}).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
	vector<int> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim)) {
		output.push_back(stoi(item));
	}
	return output;
}

TreeNode* stringToTreeNode(string input) {
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	if (!input.size()) {
		return nullptr;
	}

	string item;
	stringstream ss;
	ss.str(input);

	getline(ss, item, ',');
	TreeNode* root = new TreeNode(stoi(item));
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);

	while (true) {
		TreeNode* node = nodeQueue.front();
		nodeQueue.pop();

		if (!getline(ss, item, ',')) {
			break;
		}

		trimLeftTrailingSpaces(item);
		if (item != "null") {
			int leftNumber = stoi(item);
			node->left = new TreeNode(leftNumber);
			nodeQueue.push(node->left);
		}

		if (!getline(ss, item, ',')) {
			break;
		}

		trimLeftTrailingSpaces(item);
		if (item != "null") {
			int rightNumber = stoi(item);
			node->right = new TreeNode(rightNumber);
			nodeQueue.push(node->right);
		}
	}
	return root;
}

string treeNodeToString(TreeNode* root) {
	if (root == nullptr) {
		return "[]";
	}

	string output = "";
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();

		if (node == nullptr) {
			output += "null, ";
			continue;
		}

		output += to_string(node->val) + ", ";
		q.push(node->left);
		q.push(node->right);
	}
	return "[" + output.substr(0, output.length() - 2) + "]";
}

unsigned long long factorial(int n)
{
	if (n < 2)
	{
		return 1;
	}
	return n * factorial(n - 1);
}

unsigned long long permutation(int n, int m)
{
	return factorial(n) / factorial(n - m);
}

unsigned long long combination(int n, int m)
{
	return permutation(n, m) / factorial(m);
}

vector<string> splitString(const char* s, const char* delim = " ")
{
	vector<string> result;

	string temp(s);

	int pos{};
	while ((pos = temp.find(delim)) != string::npos)
	{
		result.emplace_back(temp.substr(0, pos));
		temp = temp.substr(pos + strlen(delim));
	}
	result.emplace_back(temp);
	return result;
}

string combinString(const vector<string>& array, const char* delim = " ")
{
	string result;
	for (const auto& str : array)
	{
		result += (str + delim);
	}
	result = result.substr(0, result.length() - strlen(delim));
	return result;
}

#pragma endregion

class Solution {
public:
	//1859. 将句子排序
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		31.19 %
		的用户
		内存消耗：
		5.9 MB
		, 在所有 C++ 提交中击败了
		97.69 %
		的用户*/
	string sortSentence(string s) {
		auto result = splitString(s.c_str());
		sort(result.begin(), result.end(), [](const string& a, const string& b) {
			return *a.rbegin() < *b.rbegin();
		});

		s = "";
		for (const auto& word : result)
		{
			s += word.substr(0, word.length() - 1) + " ";
		}
		s = s.substr(0, s.length() - 1);
		return s;
	}

	//面试题 16.05. 阶乘尾数
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		5.8 MB
		, 在所有 C++ 提交中击败了
		47.49 %
		的用户*/
	int trailingZeroes(int n) {
		int res = 0;
		while (n >= 5)
		{
			res += n / 5;
			n /= 5;
		}
		return res;
	}

	//1346. 检查整数及其两倍数是否存在
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		78.73 %
		的用户
		内存消耗：
		11 MB
		, 在所有 C++ 提交中击败了
		17.11 %
		的用户*/
	bool checkIfExist(vector<int>& arr) {
		unordered_set<int> temp;
		for (int n : arr)
		{
			if (abs(n) < 2 && temp.find(n) != temp.end())
				return true;
			temp.insert(n);
		}

		temp.erase(0);
		temp.erase(1);
		temp.erase(-1);

		for (int i = 0; i < (int)arr.size(); i++)
		{
			if ((arr[i] & 1) != 0)
				continue;

			if (temp.find(arr[i] * 2) != temp.end()
				|| temp.find(int(arr[i] * 0.5)) != temp.end())
				return true;
		}
		return false;
	}

	//1854. 人口最多的年份
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		91.76 %
		的用户
		内存消耗：
		8.3 MB
		, 在所有 C++ 提交中击败了
		13.08 %
		的用户*/
	int maximumPopulation(vector<vector<int>>& logs) {
		vector<int> temp;
		temp.resize(2050, 0);

		int maxNum{};
		int ret{ 2050 };

		for (const auto& log : logs)
		{
			for (int i = log[0]; i < log[1]; ++i)
			{
				++temp[i];
				if (temp[i] > maxNum || (temp[i] == maxNum && i < ret))
				{
					maxNum = temp[i];
					ret = i;
				}
			}
		}

		return ret;
	}

	//206. 反转链表
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		66.74 %
		的用户
		内存消耗：
		7.9 MB
		, 在所有 C++ 提交中击败了
		95.86 %
		的用户*/
		/*ListNode* reverseList(ListNode* head) {
			ListNode* prev{ nullptr };
			while (head) {
				ListNode* next = head->next;

				head->next = prev;
				prev = head;
				head = next;
			}
			return prev;
		}*/

	ListNode* reverseList(ListNode* head) {
		if (!head || !head->next) {
			return head;
		}
		ListNode* newHead = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return newHead;
	}

	//1848. 到目标元素的最小距离
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		9.4 MB
		, 在所有 C++ 提交中击败了
		71.57 %
		的用户*/
	int getMinDistance(vector<int>& nums, int target, int start) {
		int offset{};
		int size = (int)nums.size();
		while (start - offset >= 0 || start + offset < size)
		{
			int left{ start - offset };
			if (left >= 0 && nums[left] == target)
				return offset;

			int right{ start + offset };
			if (right < size && nums[right] == target)
				return offset;

			++offset;
		}
		return offset;
	}

	//剑指 Offer 03. 数组中重复的数字
	/*执行用时：
		36 ms
		, 在所有 C++ 提交中击败了
		91.86 %
		的用户
		内存消耗：
		22.9 MB
		, 在所有 C++ 提交中击败了
		46.86 %
		的用户*/
	int findRepeatNumber(vector<int>& nums) {
		vector<bool> vector;
		vector.resize(100000, false);
		for (const auto& n : nums)
		{
			if (vector[n])
				return n;
			else
				vector[n] = true;
		}
		return -1;
	}

	//剑指 Offer 57. 和为s的两个数字
	/*执行用时：
		196 ms
		, 在所有 C++ 提交中击败了
		91.79 %
		的用户
		内存消耗：
		98.1 MB
		, 在所有 C++ 提交中击败了
		93.59 %
		的用户*/
	vector<int> twoSum(vector<int>& nums, int target) {
		int first{ 0 };
		int last{ (int)nums.size() - 1 };
		while (first < last)
		{
			int sum = nums[first] + nums[last];
			if (sum < target)
				++first;
			else if (sum > target)
				--last;
			else
				return { nums[first], nums[last] };
		}
		return {};
	}

	//1816. 截断句子
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		68.42 %
		的用户*/
	string truncateSentence(string s, int k) {
		int i = 0;
		for (;i < (int)s.length();++i)
		{
			if (s[i] == ' ')
				--k;
			if (k == 0)
				break;
		}
		return s.substr(0, i);
	}

	//1812. 判断国际象棋棋盘中一个格子的颜色
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		5.8 MB
		, 在所有 C++ 提交中击败了
		63.54 %
		的用户*/
	bool squareIsWhite(string coordinates) {
		int value{};
		value += coordinates[0] - 'a';
		value += coordinates[1] - '1';
		return value % 2 != 0;
	}

	//1827. 最少操作使数组递增
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		99.04 %
		的用户
		内存消耗：
		15.4 MB
		, 在所有 C++ 提交中击败了
		59.63 %
		的用户*/
	int minOperations(vector<int>& nums) {
		if (nums.size() < 2)
		{
			return 0;
		}

		int ret{};
		for (int i = 0; i < (int)nums.size() - 1; i++)
		{
			if (nums[i] >= nums[i + 1])
			{
				int diff = nums[i] - nums[i + 1] + 1;
				nums[i + 1] += diff;
				ret += diff;
			}
		}
		return ret;
	}

	//1844. 将所有数字用字符替换
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		40.64 %
		的用户*/
	string replaceDigits(string s) {
		for (int i = 1; i < (int)s.length(); i += 2)
		{
			s[i] = s[i - 1] + (s[i] - '0');
		}
		return s;
	}

	//1832. 判断句子是否为全字母句
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		79.89 %
		的用户*/
	bool checkIfPangram(string sentence) {
		std::bitset<26> bs;
		for (auto c : sentence)
		{
			bs.set(c - 'a', true);
		}
		return bs.all();
	}

	//1822. 数组元素积的符号
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		90.09 %
		的用户
		内存消耗：
		9.9 MB
		, 在所有 C++ 提交中击败了
		39.89 %
		的用户*/
	int arraySign(vector<int>& nums) {
		bool ret{ true };
		for (auto n : nums)
		{
			if (n == 0)
				return 0;
			else if (n < 0)
				ret = !ret;
		}
		return ret ? 1 : -1;
	}

	//897. 递增顺序搜索树
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		7.7 MB
		, 在所有 C++ 提交中击败了
		50.00 %
		的用户*/
	void traverseBST(TreeNode* root, vector<TreeNode*>& result) {
		if (!root)
		{
			return;
		}
		traverseBST(root->left, result);
		//cout<<root->val<<endl;
		if (!result.empty())
		{
			auto last = *result.rbegin();
			last->left = nullptr;
			last->right = root;
		}
		result.emplace_back(root);
		traverseBST(root->right, result);
	}

	TreeNode* increasingBST(TreeNode* root) {
		vector<TreeNode*> result;
		traverseBST(root, result);
		auto last = *result.rbegin();
		last->left = nullptr;
		last->right = nullptr;
		return *result.begin();
	}

	//27. 移除元素
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		8.5 MB
		, 在所有 C++ 提交中击败了
		72.86 %
		的用户*/
	int removeElement(vector<int>& nums, int val) {
		int left = 0, right = nums.size();
		while (left < right) {
			if (nums[left] == val) {
				nums[left] = nums[right - 1];
				right--;
			}
			else {
				left++;
			}
		}
		return left;
	}

	//74. 搜索二维矩阵
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		9.3 MB
		, 在所有 C++ 提交中击败了
		48.16%
		的用户*/
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		for (int i = 0; i < (int)matrix.size(); i++)
		{
			for (int j = 0; j < (int)matrix[i].size(); j++) {
				if (matrix[i][j] == target)
				{
					return true;
				}
				else if (matrix[i][j] > target)
				{
					return false;
				}
			}
		}
		return false;
	}

	//190. 颠倒二进制位
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		24.63%
		的用户*/
	uint32_t reverseBits(uint32_t n) {
		string&& str = bitset<32>(n).to_string();
		reverse(str.begin(), str.end());
		return bitset<32>(str).to_ulong();
	}

	//面试题 04.02. 最小高度树
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		96.18%
		的用户
		内存消耗：
		23.7 MB
		, 在所有 C++ 提交中击败了
		82.70%
		的用户*/
	TreeNode* sortedArrayToBST(vector<int>& nums, int first, int last) {
		if (first > last)
			return nullptr;
		int mid = first + (int)((last - first + 1) * 0.5);
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = sortedArrayToBST(nums, first, mid - 1);
		root->right = sortedArrayToBST(nums, mid + 1, last);
		return root;
	}

	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return sortedArrayToBST(nums, 0, nums.size() - 1);
	}

	//1614. 括号的最大嵌套深度
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		80.02%
		的用户*/
	int maxDepth(string s) {
		int stack{};
		int ret{};
		for (const char& c : s)
		{
			if (c == '(')
				++stack;
			else if (c == ')')
				--stack;
			ret = std::max(stack, ret);
		}
		return ret;
	}

	//191. 位1的个数
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		5.8 MB
		, 在所有 C++ 提交中击败了
		91.58%
		的用户*/
	int hammingWeight(uint32_t n) {
		std::bitset<32> bs(n);
		return bs.count();
	}

	//1768. 交替合并字符串
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.2 MB
		, 在所有 C++ 提交中击败了
		54.38%
		的用户*/
	string mergeAlternately(string word1, string word2) {
		string ret;
		int index{};
		while (index < (int)word1.length() || index < (int)word2.length())
		{
			if (index < (int)word1.length())
			{
				ret.push_back(word1[index]);
			}
			if (index < (int)word2.length())
			{
				ret.push_back(word2[index]);
			}
			++index;
		}
		return ret;
	}

	//1773. 统计匹配检索规则的物品数量
	/*执行用时：
		80 ms
		, 在所有 C++ 提交中击败了
		86.82%
		的用户
		内存消耗：
		30.1 MB
		, 在所有 C++ 提交中击败了
		66.63%
		的用户*/
	int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
		int ret{};
		int index{};
		if (ruleKey == "color")
			index = 1;
		else if (ruleKey == "name")
			index = 2;
		for (const auto& item : items)
		{
			if (item[index] == ruleValue)
				++ret;
		}
		return ret;
	}

	//599. 两个列表的最小索引总和
	/*执行用时：
		232 ms
		, 在所有 C++ 提交中击败了
		7.22%
		的用户
		内存消耗：
		29.4 MB
		, 在所有 C++ 提交中击败了
		96.53%
		的用户*/
	vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
		vector<string> ret;
		int lastSum{ INT_MAX };
		for (int i = 0; i < (int)list1.size(); i++)
		{
			for (int j = 0; j < (int)list2.size(); j++) 
			{
				int indexSum = i + j;
				if (list1[i] == list2[j] && indexSum <= lastSum)
				{
					if (indexSum < lastSum)
						ret.clear();
					ret.emplace_back(list1[i]);
					lastSum = indexSum;
				}
			}
		}
		return ret;
	}

	//面试题 16.11. 跳水板
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		88.49%
		的用户
		内存消耗：
		19.6 MB
		, 在所有 C++ 提交中击败了
		71.43%
		的用户*/
	vector<int> divingBoard(int shorter, int longer, int k) {
		vector<int> result;
		if (k <= 0)
			return result;

		result.emplace_back(shorter * k);

		int length = (longer - shorter);
		if (length <= 0)
			return result;

		for (int i = 0; i < k; i++)
			result.emplace_back(*result.rbegin() + length);
		return result;
	}

	//925. 长按键入
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.2 MB
		, 在所有 C++ 提交中击败了
		84.57%
		的用户*/
	bool isLongPressedName(string name, string typed) {
		int i = 0, j = 0;
		for (; i < (int)name.length() && j < (int)typed.length();)
		{
			char a = name[i]; char b = typed[j];
			if (a != b)
				return false;
			else if (i < (int)name.length() - 1 && a == name[i + 1])
			{
				++i; ++j;
			}
			else //最长匹配
			{
				++i;

				do
				{
					++j;
				} while (j < (int)typed.length() && a == typed[j]);
			}
		}
		return (i == (int)name.length()) && (j == (int)typed.length());
	}

	//剑指 Offer 61. 扑克牌中的顺子
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		9.9 MB
		, 在所有 C++ 提交中击败了
		84.85%
		的用户*/
	bool isStraight(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int zero{};
		for (int i = 0; i < (int)nums.size() - 1; i++)
		{
			if (nums[i] == 0)
				++zero;
			else
			{
				if (nums[i] == nums[i + 1])
					return false;

				zero -= (nums[i + 1] - nums[i] - 1);
				if (zero < 0)
				{
					return false;
				}
			}
		}
		return true;
	}

	//1550. 存在连续三个奇数的数组
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		91.73%
		的用户
		内存消耗：
		8.1 MB
		, 在所有 C++ 提交中击败了
		81.98%
		的用户*/
	bool threeConsecutiveOdds(vector<int>& arr) {
		int count{};
		for (int i = 0; i < (int)arr.size(); i++)
		{
			if (arr[i] & 1)
				++count; 
			else
				count = 0;

			if (count >= 3)
				return true;
		}
		return false;
	}

	//766. 托普利茨矩阵
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		94.22%
		的用户
		内存消耗：
		16.9 MB
		, 在所有 C++ 提交中击败了
		93.84%
		的用户*/
	bool isToeplitzMatrix(vector<vector<int>>& matrix, int m, int n) {
		for (int i = m, j = n; i < (int)matrix.size() && j < (int)matrix[0].size(); i++, j++)
		{
			if (matrix[i][j] != matrix[m][n])
				return false;
		}
		return true;
	}

	bool isToeplitzMatrix(vector<vector<int>>& matrix) {
		for (int i = 0; i < (int)matrix.size(); i++)
		{
			if (!isToeplitzMatrix(matrix, i, 0))
			{
				return false;
			}
		}

		for (int j = 1; j < (int)matrix[0].size(); j++)
		{
			if (!isToeplitzMatrix(matrix, 0, j))
			{
				return false;
			}
		}

		return true;
	}

	//1337. 矩阵中战斗力最弱的 K 行
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		86.74%
		的用户
		内存消耗：
		10.1 MB
		, 在所有 C++ 提交中击败了
		96.58%
		的用户*/
	vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
		vector<int> result;
		for (int j = 0; j < (int)mat[0].size(); j++)
		{
			for (int i = 0; i < (int)mat.size(); i++)
			{
				//cout<<mat[i][j]<<" ";
				if (mat[i][j] == 0 && find_if(result.begin(), result.end(), [&i](int index) {
					return index == i;
				}) == result.end())
				{
					result.emplace_back(i);
					if ((int)result.size() == k)
					{
						return result;
					}
				}
			}
			//cout << endl;
		}
		for (int i = 0; i < (int)mat.size(); i++)
		{
			if (find_if(result.begin(), result.end(), [&i](int index) {
				return index == i;
			}) == result.end())
			{
				result.emplace_back(i);
				if ((int)result.size() == k)
				{
					return result;
				}
			}
		}
		return result;
	}

	//1732. 找到最高海拔
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		7.8 MB
		, 在所有 C++ 提交中击败了
		35.65%
		的用户*/
	int largestAltitude(vector<int>& gain) {
		int result{};
		int sum{};
		for (int i = 0; i < (int)gain.size(); i++)
		{
			sum += gain[i];
			result = std::max(sum, result);
		}
		return result;
	}

	//1725. 可以形成最大正方形的矩形数目
	/*执行用时：
		44 ms
		, 在所有 C++ 提交中击败了
		87.37%
		的用户
		内存消耗：
		18 MB
		, 在所有 C++ 提交中击败了
		50.89%
		的用户*/
	int countGoodRectangles(vector<vector<int>>& rectangles) {
		std::map<int, int> result;
		for (const auto& rectangle : rectangles)
		{
			++result[std::min(rectangle[0], rectangle[1])];
		}
		return (*result.rbegin()).second;
	}

	//剑指 Offer 17. 打印从1到最大的n位数
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		99.03%
		的用户
		内存消耗：
		10.3 MB
		, 在所有 C++ 提交中击败了
		99.45%
		的用户*/
	vector<int> printNumbers(int n) {
		n = stoi(string(n, '9'));
		vector<int> result;
		result.resize(n);
		for (int i = 1; i <= n ; i++)
		{
			result[i - 1] = i;
		}
		return result;
	}

	//1232. 缀点成线
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		92.01%
		的用户
		内存消耗：
		9.8 MB
		, 在所有 C++ 提交中击败了
		68.49%
		的用户*/
	bool checkStraightLine(vector<vector<int>>& coordinates) {
		int deltaX = coordinates[1][0] - coordinates[0][0]; //x1 - x0
		int deltaY = coordinates[1][1] - coordinates[0][1]; //y1 - y0
		return find_if(coordinates.begin() + 2, coordinates.end(), [&](const vector<int>& coordinate) {
			//(x - x0) * (y1 - y0) != (y - y0) * (x1 - x0)
			return (coordinate[0] - coordinates[0][0]) * deltaY != (coordinate[1] - coordinates[0][1]) * deltaX;
		}) == coordinates.end();
	}

	//1716. 计算力扣银行的钱
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		5.8 MB
		, 在所有 C++ 提交中击败了
		92.86%
		的用户*/
	int totalMoney(int n) {
		int result{};
		for (int i = 0; i < n ; i++)
		{
			result += (i % 7 + 1) + (i / 7);
		}
		return result;
	}

	//1436. 旅行终点站
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		97.49%
		的用户
		内存消耗：
		10.9 MB
		, 在所有 C++ 提交中击败了
		69.72%
		的用户*/
	string destCity(vector<vector<string>>& paths) {
		std::unordered_set<string> cityA;
		std::unordered_set<string> cityB;

		for (const auto& path : paths)
		{
			cityA.insert(path[0]);
			cityB.insert(path[1]);
		}

		for (auto it = cityB.begin();it != cityB.end();)
		{
			if (cityA.find(*it) != cityA.end())
				it = cityB.erase(it);
			else
				++it;
		}

		return *cityB.begin();
	}

	//1356. 根据数字二进制下 1 的数目排序
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		99.99%
		的用户
		内存消耗：
		9.7 MB
		, 在所有 C++ 提交中击败了
		99.90%
		的用户*/
	vector<int> sortByBits(vector<int>& arr) {
		sort(arr.begin(), arr.end(), [](int a, int b) {
			int countA = bitset<14>(a).count();
			int countB = bitset<14>(b).count();
			if (countA == countB)
				return a < b;
			else
				return countA < countB;
		});
		return arr;
	}

	//1374. 生成每种字符都是奇数个的字符串
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.4 MB
		, 在所有 C++ 提交中击败了
		75.27%
		的用户*/
	string generateTheString(int n) {
		if (n & 1)
			return string(n, 'a');
		else
		{
			string s(n - 1, 'a');
			s.push_back('b');
			return s;
		}
	}

	//1704. 判断字符串的两半是否相似
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		82.51%
		的用户
		内存消耗：
		6.4 MB
		, 在所有 C++ 提交中击败了
		99.66%
		的用户*/
	bool halvesAreAlike(string s) {
		auto func = [](char c) -> bool {
			return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' 
				|| c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
		};

		int length = (int)s.length() >> 1;
		int a = count_if(s.begin(), s.begin() + length, func);
		int b = count_if(s.begin() + length, s.end(), func);
		return a == b;
	}

	//1528. 重新排列字符串
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		96.78%
		的用户
		内存消耗：
		14.8 MB
		, 在所有 C++ 提交中击败了
		96.24%
		的用户*/
	string restoreString(string s, vector<int>& indices) {
		vector<char> result;
		result.resize(s.length());
		for (int i = 0; i < (int)indices.size(); i++)
		{
			result[indices[i]] = s[i];
		}
		return string{ result.begin(), result.end() };
	}

	//1460. 通过翻转子数组使两个数组相等
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		99.81%
		的用户
		内存消耗：
		13.6 MB
		, 在所有 C++ 提交中击败了
		99.81%
		的用户*/
	bool canBeEqual(vector<int>& target, vector<int>& arr) {
		sort(target.begin(), target.end());
		sort(arr.begin(), arr.end());
		return target == arr;
	}

	//1710. 卡车上的最大单元数
	/*执行用时：
		52 ms
		, 在所有 C++ 提交中击败了
		98.92%
		的用户
		内存消耗：
		15.6 MB
		, 在所有 C++ 提交中击败了
		98.01%
		的用户*/
	int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
		std::sort(boxTypes.begin(), boxTypes.end(), [](vector<int>& boxTypeA, vector<int>& boxTypeB) -> bool {
			return boxTypeA[1] > boxTypeB[1];
		});

		int result{};
		for (const auto& boxType : boxTypes)
		{
			result += std::min(boxType[0], truckSize) * boxType[1];
			if ((truckSize -= boxType[0]) <= 0)
				break;
		}
		return result;
	}

	//628. 三个数的最大乘积
	/*执行用时：
		52 ms
		, 在所有 C++ 提交中击败了
		92.07%
		的用户
		内存消耗：
		26.9 MB
		, 在所有 C++ 提交中击败了
		83.92%
		的用户*/
	int maximumProduct(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int size = (int)nums.size();
		return std::max(std::max(nums[size - 1] * nums[size - 2] * nums[size - 3],
			nums[0] * nums[1] * nums[2]),
			nums[0] * nums[1] * nums[size - 1]);
	}

	//1688. 比赛中的配对次数
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		5.9 MB
		, 在所有 C++ 提交中击败了
		97.10%
		的用户*/
	int numberOfMatches(int n) {
		int result{};
		while (n > 1)
		{
			if (n % 2 == 0)
			{
				n /= 2;
				result += n;
			}
			else
			{
				n = (n - 1) / 2;
				result += n + 1;
			}
		}
		return result;
	}

	//1450. 在既定时间做作业的学生人数
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		11.1 MB
		, 在所有 C++ 提交中击败了
		63.30%
		的用户*/
	int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
		int result{};
		for (int i = 0; i < (int)startTime.size(); i++)
		{
			if (queryTime >= startTime[i] && queryTime <= endTime[i])
				++result;
		}
		return result;
	}

	//1678. 设计 Goal 解析器
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.2 MB
		, 在所有 C++ 提交中击败了
		98.90%
		的用户*/
	string interpret(string command) {
		string result;
		for (int i = 0; i < (int)command.length();)
		{
			if (command[i] == 'G')
			{
				result.push_back('G');
				++i;
			}
			else if (command[i] == '(' && command[i + 1] == ')')
			{
				result.push_back('o');
				i += 2;
			}
			else
			{
				result.push_back('a');
				result.push_back('l');
				i += 4;
			}
		}
		return result;
	}

	//1684. 统计一致字符串的数目
	/*执行用时：
		136 ms
		, 在所有 C++ 提交中击败了
		44.81%
		的用户
		内存消耗：
		29.8 MB
		, 在所有 C++ 提交中击败了
		86.51%
		的用户*/
	int countConsistentStrings(string allowed, vector<string>& words) {
		int result{};
		for (const auto& word : words)
		{
			if (std::find_if(word.begin(), word.end(), [&allowed](char c) {
				return allowed.find(c) == std::string::npos;
			}) == word.end())
				++result;
		}
		return result;
	}

	//1720. 解码异或后的数组
	/*执行用时：
		80 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		25.8 MB
		, 在所有 C++ 提交中击败了
		100.00%
		的用户*/
	vector<int> decode(vector<int>& encoded, int first) {
		vector<int> result{ first };
		for (auto e : encoded)
			result.emplace_back(first ^= e);
		return result;
	}

	//605. 种花问题
	/*执行用时：36 ms, 在所有 C++ 提交中击败了85.15%的用户
	内存消耗：20.3 MB, 在所有 C++ 提交中击败了35.64%的用户*/
	bool canPlaceFlowers(vector<int>& flowerbed, int n) {
		int count{ 0 };
		int size = (int)flowerbed.size();
		for (int i = 0; i < size; ++i)
		{
			if (flowerbed[i] == 0)
			{
				int left = i == 0 ? 0 : flowerbed[i - 1];
				int right = i == size - 1 ? 0 : flowerbed[i + 1];
				if (left == 0 && right == 0)
				{
					++count;
					++i;
				}
			}
			else
			{
				++i;
			}
		}
		return count >= n;
	}

	//1033. 移动石子直到连续
	/*执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
	内存消耗：6.6 MB, 在所有 C++ 提交中击败了18.48%的用户*/
	vector<int> numMovesStones(int a, int b, int c) {
		vector<int> pos{ a, b, c };
		sort(pos.begin(), pos.end());

		int left = pos[1] - pos[0] - 1;
		int right = pos[2] - pos[1] - 1;
		int minimum_moves = (left > 0 ? 1 : 0) + (right > 0 ? 1 : 0);
		if (left == 1 || right == 1)
			minimum_moves = 1;
		int maximum_moves = left + right;
		return { minimum_moves, maximum_moves };
	}

	//面试题 08.01. 三步问题
	/*执行用时：4 ms, 在所有 C++ 提交中击败了98.76%的用户
	内存消耗：6.2 MB, 在所有 C++ 提交中击败了65.83%的用户*/
	int waysToStep(int n) {
		if (n == 1)
			return 1;

		if (n == 2)
			return 2;

		if (n == 3)
			return 4;

		uint64_t a = 1; uint64_t b = 2; uint64_t c = 4;

		uint64_t ret{ 0 };
		for (int i = 4;i <= n;++i)
		{
			ret = (a + b + c) % 1000000007;
			a = b;
			b = c;
			c = ret;
		}
		return (int)ret;
	}

	/*int waysToStep(int n) {
		if (n == 1)
			return 1;

		if (n == 2)
			return 2;

		if (n == 3)
			return 4;

		return waysToStep(n - 1) + waysToStep(n - 2) + waysToStep(n - 3);
	}*/

	//1652. 拆炸弹
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		87.81%
		的用户
		内存消耗：
		8.7 MB
		, 在所有 C++ 提交中击败了
		5.07%
		的用户*/
	vector<int> decrypt(vector<int>& code, int k) {
		int size = (int)code.size();
		vector<int> ret(size);
		code.insert(code.end(), code.begin(), code.end());
		if (k > 0)
		{
			for (int i = 0; i < size; i++)
			{
				ret[i] = accumulate(code.begin() + 1 + i, code.begin() + 1 + i + k, 0);
			}
		}
		else if (k < 0)
		{
			for (int i = size - 1; i >= 0 ; i--)
			{
				ret[i] = accumulate(code.rbegin() + size - i, code.rbegin() + size - i - k, 0);
			}
		}
		return ret;
	}

	//1266. 访问所有点的最小时间
	/*执行用时：
		12 ms
		, 在所有 C++ 提交中击败了
		82.35%
		的用户
		内存消耗：
		9.8 MB
		, 在所有 C++ 提交中击败了
		23.53%
		的用户*/
	int minTimeToVisitAllPoints(vector<vector<int>>& points) {
		int ret{};
		for (int i = 0; i < (int)points.size() - 1; i++)
		{
			const auto& pointA = points[i];
			const auto& pointB = points[i + 1];
			ret += std::max(std::abs(pointB[0] - pointA[0]), std::abs(pointB[1] - pointA[1]));
		}
		return ret;
	}

	//1108. IP 地址无效化
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		14.88%
		的用户*/
	string defangIPaddr(string address) {
		string str;
		for (const char& c : address)
		{
			if (c == '.')
			{
				str.push_back('[');
				str.push_back('.');
				str.push_back(']');
			}
			else
				str.push_back(c);
		}
		return str;
	}

	//1389. 按既定顺序创建目标数组
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		8.7 MB
		, 在所有 C++ 提交中击败了
		7.07%
		的用户*/
	vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
		vector<int> ret;
		int size = (int)nums.size();
		for (int i = 0; i < size; ++i)
		{
			ret.emplace(ret.begin() + index[i], nums[i]);
		}
		return ret;
	}

	//5613. 最富有客户的资产总量
	/*执行用时：
		12 ms
		, 在所有 C++ 提交中击败了
		66.09%
		的用户
		内存消耗：
		8 MB
		, 在所有 C++ 提交中击败了
		94.68%
		的用户*/
	int maximumWealth(vector<vector<int>>& accounts) {
		std::set<int> set;
		for (const auto& account : accounts)
		{
			set.insert(accumulate(account.begin(), account.end(), 0));
		}
		return *set.rbegin();
	}

	//976. 三角形的最大周长
	/*执行用时：
		100 ms
		, 在所有 C++ 提交中击败了
		84.63%
		的用户
		内存消耗：
		20.6 MB
		, 在所有 C++ 提交中击败了
		10.99%
		的用户*/
	int largestPerimeter(vector<int>& A) {
		std::sort(A.begin(), A.end(), std::greater<int>());
		for (int i = 0; i < (int)A.size() - 2 ; i++)
		{
			int a = A[i];
			int b = A[i + 1];
			int c = A[i + 2];

			if (a < b + c)
			{
				return a + b + c;
			}
		}
		return 0;
	}

	//1370. 上升下降字符串
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		93.95%
		的用户
		内存消耗：
		7.8 MB
		, 在所有 C++ 提交中击败了
		69.86%
		的用户*/
	string sortString(string s) {
		int arr[26] = { 0 };
		for (const auto& c : s)
		{
			++arr[c - 'a'];
		}

		string ret;
		while (ret.length() < s.length())
		{
			for (int i = 0; i < 26 ; i++)
			{
				if (arr[i] == 0)
					continue;
				ret.push_back(i + 'a');
				--arr[i];
			}

			for (int i = 25; i >= 0 ; i--)
			{
				if (arr[i] == 0)
					continue;
				ret.push_back(i + 'a');
				--arr[i];
			}
		}
		return ret;
	}

	//剑指 Offer 54. 二叉搜索树的第k大节点
	/*执行用时：
		24 ms
		, 在所有 C++ 提交中击败了
		94.89%
		的用户
		内存消耗：
		24.2 MB
		, 在所有 C++ 提交中击败了
		15.41%
		的用户*/
	void kthLargest(TreeNode* root, int k, std::vector<int>& q) {
		if (!root || (int)q.size() >= k) return;
		kthLargest(root->right, k, q);
		if ((int)q.size() < k)
			q.emplace_back(root->val);
		else
			return;
		kthLargest(root->left, k, q);
	}

	int kthLargest(TreeNode* root, int k) {
		std::vector<int> q;
		kthLargest(root, k, q);
		return *q.rbegin();
	}

	//面试题 17.04. 消失的数字
	/*执行用时：
		32 ms
		, 在所有 C++ 提交中击败了
		96.88%
		的用户
		内存消耗：
		17.3 MB
		, 在所有 C++ 提交中击败了
		10.53%
		的用户*/
	int missingNumber(vector<int>& nums) {
		int size = (int)nums.size();
		return int(size * (size + 1) * 0.5) - accumulate(nums.begin(), nums.end(), 0);
	}

	//226. 翻转二叉树
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		9.3 MB
		, 在所有 C++ 提交中击败了
		35.65%
		的用户*/
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		}
		TreeNode* left = invertTree(root->left);
		TreeNode* right = invertTree(root->right);
		root->left = right;
		root->right = left;
		return root;
	}

	//1122. 数组的相对排序
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		90.26%
		的用户
		内存消耗：
		8.1 MB
		, 在所有 C++ 提交中击败了
		21.61%
		的用户*/
	vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
		vector<int> temp(1001);
		int size = (int)arr2.size();
		for (int i = 0; i < size; i++)
		{
			temp[arr2[i]] = size - i;
		}
		std::sort(arr1.begin(), arr1.end(), [&temp](int a, int b) {
			if (temp[a] == temp[b])
			{
				return a < b;
			}
			return temp[a] > temp[b];
		});
		return arr1;
	}

	//832. 翻转图像
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		97.72%
		的用户
		内存消耗：
		8.6 MB
		, 在所有 C++ 提交中击败了
		54.41%
		的用户*/
	vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A)
	{
		for (int i = 0; i < (int)A.size(); ++i)
		{
			vector<int>& temp = A[i];
			reverse(temp.begin(), temp.end());
			for (int j = 0; j < (int)temp.size(); ++j)
			{
				temp[j] = !temp[j];
			}
		}
		return A;
	}

	//938. 二叉搜索树的范围和
	/*执行用时：
		208 ms
		, 在所有 C++ 提交中击败了
		90.06%
		的用户
		内存消耗：
		63.7 MB
		, 在所有 C++ 提交中击败了
		36.20%
		的用户*/
	void search(TreeNode* root, int low, int high, int& sum)
	{
		if (!root)
			return;
		if (root->val > low)
		{
			search(root->left, low, high, sum);
		}
		if (root->val >= low && root->val <= high)
		{
			sum += root->val;
		}
		if (root->val < high)
		{
			search(root->right, low, high, sum);
		}
	}

	int rangeSumBST(TreeNode* root, int low, int high) {
		int sum{ 0 };
		search(root, low, high, sum);
		return sum;
	}

	//922. 按奇偶排序数组 II
	/*执行用时：
		32 ms
		, 在所有 C++ 提交中击败了
		99.05%
		的用户
		内存消耗：
		20.5 MB
		, 在所有 C++ 提交中击败了
		29.90%
		的用户*/
	vector<int> sortArrayByParityII(vector<int>& A) {
		int i = 0; int j = 1;
		while (i < (int)A.size() && j < (int)A.size())
		{
			if ((A[i] & 1) == 0)
				i += 2;
			else if ((A[j] & 1) == 1)
				j += 2;
			else
				swap(A[i], A[j]);
		}
		return A;
	}

	//804. 唯一摩尔斯密码词
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		9 MB
		, 在所有 C++ 提交中击败了
		13.23%
		的用户*/
	int uniqueMorseRepresentations(vector<string>& words) {
		static const char* const password[] =
		{
			".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",
		};

		auto func = [](const string& str) -> string {
			string ret = "";
			for (const auto& c : str)
			{
				ret += password[c - 'a'];
			}
			return ret;
		};

		set<string> set;
		for (const auto& s : words)
		{
			set.emplace(func(s));
		}
		return (int)set.size();
	}

	//剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
	/*执行用时：
		36 ms
		, 在所有 C++ 提交中击败了
		92.57%
		的用户
		内存消耗：
		18.1 MB
		, 在所有 C++ 提交中击败了
		25.92%
		的用户*/
	vector<int> exchange(vector<int>& nums) {
		/*sort(nums.begin(), nums.end(), [](int a, int b) {
			return (a & 1) > (b & 1);
		});
		return nums;*/

		int i = 0; int j = (int)nums.size() - 1;
		while (i < j)
		{
			if ((nums[i] & 1) == 1)
				++i;
			else if ((nums[j] & 1) == 0)
				--j;
			else
				swap(nums[i], nums[j]);
		}
		return nums;
	}

	//1491. 去掉最低工资和最高工资后的工资平均值
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		7.3 MB
		, 在所有 C++ 提交中击败了
		39.40%
		的用户*/
	double average(vector<int>& salary) {
		sort(salary.begin(), salary.end());
		double sum = accumulate(salary.begin() + 1, salary.end() - 1, 0);
		return sum / (salary.size() - 2);
	}

	//LCP 17. 速算机器人
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.2 MB
		, 在所有 C++ 提交中击败了
		10.74%
		的用户*/
	int calculate(string s) {
		int x{ 1 }; int y{ 0 };
		for (const auto& c : s)
		{
			if (c == 'A')
				x = 2 * x + y;
			else if (c == 'B')
				y = 2 * y + x;
		}
		return x + y;
	}

	//LCP 01. 猜数字
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.7 MB
		, 在所有 C++ 提交中击败了
		5.41%
		的用户*/
	int game(vector<int>& guess, vector<int>& answer) {
		int result{};
		for (int i = 0; i < 3; ++i)
		{
			result += (guess[i] == answer[i] ? 1 : 0);
		}
		return result;
	}

	//1572. 矩阵对角线元素的和
	/*执行用时：
		24 ms
		, 在所有 C++ 提交中击败了
		99.85%
		的用户
		内存消耗：
		11.6 MB
		, 在所有 C++ 提交中击败了
		5.25%
		的用户*/
	int diagonalSum(vector<vector<int>>& mat) {
		int sum{ 0 };
		for (int i = 0; i < (int)mat.size(); i++)
		{
			int size = (int)mat[i].size();
			for (int j = 0; j < size; j++) {
				if (i == j || i == size - 1 - j)
					sum += mat[i][j];
			}
		}
		return sum;
	}

	//面试题 01.01. 判定字符是否唯一
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.2 MB
		, 在所有 C++ 提交中击败了
		42.31%
		的用户*/
	bool isUnique(string astr) {
		std::sort(astr.begin(), astr.end());
		return std::unique(astr.begin(), astr.end()) == astr.end();
	}

	//1512. 好数对的数目
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		7.5 MB
		, 在所有 C++ 提交中击败了
		32.68%
		的用户*/
	int numIdenticalPairs(vector<int>& nums) {
		std::map<int, int> temp;
		for (auto e : nums)
		{
			++temp[e];
		}

		int result{0};
		for (auto p : temp)
		{
			if (p.second >= 2)
			{
				result += p.second * (p.second - 1) / 2;
			}
		}
		return result;
	}

	//121. 买卖股票的最佳时机
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		94.76%
		的用户
		内存消耗：
		13 MB
		, 在所有 C++ 提交中击败了
		18.14%
		的用户*/
	int maxProfit(vector<int>& prices) {
		if (prices.empty())
		{
			return 0;
		}

		int minPrice = prices[0];

		int result{ 0 };
		for (int i = 1; i < (int)prices.size(); i++)
		{
			result = std::max(prices[i] - minPrice, result);
			minPrice = std::min(prices[i], minPrice);
		}
		return result;
	}

	//1431. 拥有最多糖果的孩子
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		84.61%
		的用户
		内存消耗：
		9.3 MB
		, 在所有 C++ 提交中击败了
		6.24%
		的用户*/
	vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
		int maxCandies = *std::max_element(candies.begin(), candies.end());

		vector<bool> result;
		for (const auto& e : candies)
		{
			result.emplace_back(e + extraCandies >= maxCandies);
		}
		return result;
	}

	//643. 子数组最大平均数 I
	/*执行用时：
		256 ms
		, 在所有 C++ 提交中击败了
		88.19%
		的用户
		内存消耗：
		70.4 MB
		, 在所有 C++ 提交中击败了
		15.61%
		的用户*/
	double findMaxAverage(vector<int>& nums, int k) {
		double sum = accumulate(nums.begin(), nums.begin() + k, 0);
		double avg = sum / k;

		for (int i = 1; i <= (int)nums.size() - k; i++)
		{
			sum = sum - nums[i - 1] + nums[i - 1 + k];
			avg = std::max(sum / k, avg);
		}

		return avg;
	}

	//1486. 数组异或操作
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		17.35%
		的用户*/
	int xorOperation(int n, int start) {
		int result{ start };
		for (int i = 1; i < n; i++)
		{
			result ^= (start + 2 * i);
		}
		return result;
	}

	//剑指 Offer 10- II. 青蛙跳台阶问题
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		15.72%
		的用户*/
	int numWays(int n) {
		int a{ 0 };
		int b{ 1 };

		int sum{ 1 };
		for (int i = 1; i <= n; i++)
		{
			sum = (a + b);
			sum = sum > 1000000007 ? sum % 1000000007 : sum;
			a = b;
			b = sum;
		}
		return sum;
	}

	//70. 爬楼梯
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		21.95%
		的用户*/
	int climbStairs(int n) {
		int a{ 0 };
		int b{ 1 };

		int sum{ 0 };
		for (int i = 1; i <= n; i++)
		{
			sum = (a + b);
			a = b;
			b = sum;
		}
		return sum;
	}

	//941. 有效的山脉数组
	/*执行用时：
		52 ms
		, 在所有 C++ 提交中击败了
		90.83%
		的用户
		内存消耗：
		22.2 MB
		, 在所有 C++ 提交中击败了
		5.15%
		的用户*/
	bool validMountainArray(vector<int>& A) {
		if (A.size() < 3)
			return false;

		if (A[0] >= A[1])
			return false;

		bool rise{ true };
		for (int i = 1; i < (int)A.size() - 1; ++i)
		{
			if (A[i] == A[i + 1])
				return false;
			else if (A[i] > A[i + 1])
				rise = false;
			else
			{
				if (!rise)
					return false;
			}
		}

		return !rise;
	}

	//219. 存在重复元素 II
	/*执行用时：
		72 ms
		, 在所有 C++ 提交中击败了
		34.73%
		的用户
		内存消耗：
		15.6 MB
		, 在所有 C++ 提交中击败了
		90.79%
		的用户*/
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_set<int> temp;
		for (int i = 0; i < (int)nums.size(); i++)
		{
			if (temp.find(nums[i]) != temp.end()) return true;
			temp.emplace(nums[i]);
			if ((int)temp.size() > k) {
				temp.erase(nums[i - k]);
			}
		}
		return false;
	}

	//217. 存在重复元素
	/*执行用时：
		56 ms
		, 在所有 C++ 提交中击败了
		97.26%
		的用户
		内存消耗：
		14.8 MB
		, 在所有 C++ 提交中击败了
		91.53%
		的用户*/
	bool containsDuplicate(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return std::unique(nums.begin(), nums.end()) != nums.end();
	}

	//1475. 商品折扣后的最终价格
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		98.24%
		的用户
		内存消耗：
		10 MB
		, 在所有 C++ 提交中击败了
		45.91%
		的用户*/
	vector<int> finalPrices(vector<int>& prices) {
		for (int i = 0; i < (int)prices.size(); i++)
		{
			for (int j = i + 1; j < (int)prices.size(); j++) {
				if (prices[j] <= prices[i])
				{
					prices[i] -= prices[j];
					break;
				}
			}
		}
		return prices;
	}

	//1342. 将数字变成 0 的操作次数
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		8.92%
		的用户*/
	int numberOfSteps(int num) {
		bitset<32> bs(num);

		int count{ 0 };
		while (bs.count())
		{
			if (bs.test(0))
				bs.reset(0);
			else
				bs >>= 1;
			++count;
		}
		return count;
	}

	//面试题 02.03. 删除中间节点
	/*执行用时：
		12 ms
		, 在所有 C++ 提交中击败了
		95.32%
		的用户
		内存消耗：
		8.2 MB
		, 在所有 C++ 提交中击败了
		5.53%
		的用户*/
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;
	}

	//5539. 按照频率将数组升序排序
	/*执行用时：
		36 ms
		, 在所有 C++ 提交中击败了
		15.56%
		的用户
		内存消耗：
		11.2 MB
		, 在所有 C++ 提交中击败了
		90.58%
		的用户*/
	vector<int> frequencySort(vector<int>& nums) {
		map<int, int> temp;
		for (auto e : nums)
		{
			++temp[e];
		}

		sort(nums.begin(), nums.end(), [&temp](int a, int b) {
			if (temp[a] == temp[b])
			{
				return a > b;
			}
			return temp[a] < temp[b];
		});
		return nums;
	}

	//1480. 一维数组的动态和
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		89.33%
		的用户
		内存消耗：
		8.7 MB
		, 在所有 C++ 提交中击败了
		12.23%
		的用户*/
	vector<int> runningSum(vector<int>& nums) {
		for (int i = 1; i < (int)nums.size(); i++)
		{
			nums[i] += nums[i - 1];
		}
		return nums;
	}

	//1394. 找出数组中的幸运数
	/*执行用时：
		12 ms
		, 在所有 C++ 提交中击败了
		88.72%
		的用户
		内存消耗：
		10.3 MB
		, 在所有 C++ 提交中击败了
		63.12%
		的用户*/
	int findLucky(vector<int>& arr) {
		map<int, int> temp;
		for (auto e : arr)
		{
			++temp[e];
		}

		for (auto it = temp.rbegin();it != temp.rend();++it)
		{
			if (it->first == it->second)
			{
				return it->first;
			}
		}
		return -1;
	}

	//349. 两个数组的交集
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		96.25%
		的用户
		内存消耗：
		10.3 MB
		, 在所有 C++ 提交中击败了
		79.93%
		的用户*/
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		std::sort(nums1.begin(), nums1.end());
		std::sort(nums2.begin(), nums2.end());

		std::vector<int> v_intersection;
		std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), std::back_inserter(v_intersection));

		auto last = std::unique(v_intersection.begin(), v_intersection.end());
		v_intersection.erase(last, v_intersection.end());

		return v_intersection;
	}

	//1619. 删除某些元素后的数组均值
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		92.65%
		的用户
		内存消耗：
		9.5 MB
		, 在所有 C++ 提交中击败了
		75.66%
		的用户*/
	double trimMean(vector<int>& arr) {
		sort(arr.begin(), arr.end());
		int size = (int)arr.size();
		int num = (int)(size * 0.05);
		double sum = accumulate(arr.begin() + num, arr.end() - num, 0);
		return sum / (size - 2 * num);
	}

	//剑指 Offer 25. 合并两个排序的链表
	/*执行用时：
		32 ms
		, 在所有 C++ 提交中击败了
		98.48%
		的用户
		内存消耗：
		19.2 MB
		, 在所有 C++ 提交中击败了
		41.90%
		的用户*/
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* head{ new ListNode() };
		ListNode* node{ head };
		while (l1 && l2)
		{
			if (l1->val < l2->val)
			{
				node->next = l1;
				l1 = l1->next;
			}
			else
			{
				node->next = l2;
				l2 = l2->next;
			}
			node = node->next;
		}
		node->next = l1 ? l1 : l2;
		return head->next;
	}

	//21. 合并两个有序链表
	/*ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr) {
			return l2;
		}
		else if (l2 == nullptr) {
			return l1;
		}
		else if (l1->val < l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	}*/

	//1502. 判断能否形成等差数列
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		85.00%
		的用户
		内存消耗：
		9.1 MB
		, 在所有 C++ 提交中击败了
		34.72%
		的用户*/
	bool canMakeArithmeticProgression(vector<int>& arr) {
		if (arr.size() < 3)
		{
			return true;
		}

		sort(arr.begin(), arr.end());

		int diff = arr[1] - arr[0];
		for (int i = 1; i < (int)arr.size() - 1; i++)
		{
			if (arr[i + 1] - arr[i] != diff)
				return false;
		}
		return true;
	}

	//1464. 数组中两元素的最大乘积
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		94.42%
		的用户
		内存消耗：
		10 MB
		, 在所有 C++ 提交中击败了
		50.88%
		的用户*/
	int maxProduct(vector<int>& nums) {
		nth_element(nums.begin(), nums.begin() + 2, nums.end(), std::greater<int>());
		return (nums[0] - 1) * (nums[1] - 1);
	}

	//LCP 06. 拿硬币
	/*执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
	内存消耗：8.4 MB, 在所有 C++ 提交中击败了12.28%的用户*/
	int minCount(vector<int>& coins) {
		int count{0};
		for (auto coin : coins)
		{
			count += (coin >> 1) + (coin & 1);
		}
		return count;
	}

	//面试题 01.02. 判定是否互为字符重排
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		76.20%
		的用户*/
	bool CheckPermutation(string s1, string s2) {
		std::sort(s1.begin(), s1.end());
		std::sort(s2.begin(), s2.end());
		return s1 == s2;
	}

	//面试题 08.03. 魔术索引
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		89.19%
		的用户
		内存消耗：
		12.5 MB
		, 在所有 C++ 提交中击败了
		71.03%
		的用户*/
	int findMagicIndex(vector<int>& nums) {
		for (int i = 0; i < (int)nums.size();)
		{
			if (nums[i] == i)
				return i;
			else if (nums[i] > i)
				i += (nums[i] - i);
			else
				i++;
		}
		return -1;
	}

	//1748. 唯一元素的和
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00%
		的用户
		内存消耗：
		7.9 MB
		, 在所有 C++ 提交中击败了
		5.19%
		的用户*/
	int sumOfUnique(vector<int>& nums) {
		std::map<int, int> map;
		for (auto n : nums)
		{
			++map[n];
		}

		int sum{};
		for (auto p : map)
		{
			if (p.second == 1)
				sum += p.first;
		}
		return sum;
	}
};

//1114. 按序打印
//执行用时：128 ms, 在所有 C++ 提交中击败了84.99%的用户
//内存消耗：7.7 MB, 在所有 C++ 提交中击败了14.63%的用户
class Foo {
public:
	Foo() {

	}

	void first(function<void()> printFirst) {

		// printFirst() outputs "first". Do not change or remove this line.
		printFirst();
		++m_flag;
		m_cv.notify_all();
	}

	void second(function<void()> printSecond) {
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, [this] {return m_flag == 1; });
		// printSecond() outputs "second". Do not change or remove this line.
		printSecond();
		++m_flag;
		m_cv.notify_one();
	}

	void third(function<void()> printThird) {
		std::unique_lock<std::mutex> lk(m_mutex);
		m_cv.wait(lk, [this] {return m_flag == 2; });
		// printThird() outputs "third". Do not change or remove this line.
		printThird();
	}

private:
	std::mutex m_mutex;
	std::condition_variable m_cv;
	int m_flag{0};
};

//1603. 设计停车系统
//执行用时：116 ms, 在所有 C++ 提交中击败了82.20%的用户
//内存消耗：32.7 MB, 在所有 C++ 提交中击败了36.14%的用户
class ParkingSystem {
public:
	ParkingSystem(int big, int medium, int small) {
		m_data[0] = big;
		m_data[1] = medium;
		m_data[2] = small;
	}

	bool addCar(int carType) {
		return m_data[carType - 1]-- > 0;
	}

private:
	vector<int> m_data{ 0, 0, 0 };
};

// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const {};

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const {};

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const {};
};

//341. 扁平化嵌套列表迭代器
//执行用时：
//8 ms
//, 在所有 C++ 提交中击败了
//90.84%
//的用户
//内存消耗：
//13.1 MB
//, 在所有 C++ 提交中击败了
//60.70%
//的用户
class NestedIterator {
public:
	NestedIterator(vector<NestedInteger> &nestedList) {
		for (const auto& n : nestedList)
			visit(n);
	}

	int next() {
		return m_data[m_index++];
	}

	bool hasNext() {
		return m_index < (int)m_data.size();
	}

private:
	void visit(const NestedInteger& n)
	{
		if (n.isInteger())
			m_data.emplace_back(n.getInteger());
		else
		{
			for (const auto& n : n.getList())
				visit(n); 
		}
	}

	std::vector<int> m_data;
	int m_index{ 0 };
};

//剑指 Offer 09. 用两个栈实现队列
//执行用时：
//316 ms
//, 在所有 C++ 提交中击败了
//88.60%
//的用户
//内存消耗：
//101.1 MB
//, 在所有 C++ 提交中击败了
//64.77%
//的用户
class CQueue {
public:
	CQueue() {
		//
	}

	void appendTail(int value) {
		m_stack1.push(value);
	}

	int deleteHead() {
		if (m_stack2.empty())
		{
			while (!m_stack1.empty())
			{
				m_stack2.push(m_stack1.top());
				m_stack1.pop();
			}
		}

		int value{ -1 };
		if (!m_stack2.empty())
		{
			value = m_stack2.top();
			m_stack2.pop();
		}
		return value;
	}

private:
	std::stack<int> m_stack1;
	std::stack<int> m_stack2;
};
