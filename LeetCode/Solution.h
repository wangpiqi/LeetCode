#pragma once

#include "utility.h"

using namespace std;

class Solution {
public:
	//387. 字符串中的第一个唯一字符
	int firstUniqChar(string s) {
		std::unordered_map<char, int> hashtable;
		for (int i = 0; i < (int)s.length() ; i++)
		{
			const char& c = s[i];
			auto it = hashtable.find(c);
			if (it != hashtable.end())
				it->second = -1;
			else
				hashtable.insert({ c, i });
		}

		int result{ INT_MAX };
		for (const auto& p : hashtable)
		{
			if (p.second != -1)
				result = min(p.second, result);
		}
		return result != INT_MAX ? result : -1;
	}

	//73. 矩阵置零
	/*执行用时：
		12 ms
		, 在所有 C++ 提交中击败了
		88.19 %
		的用户
		内存消耗：
		13.1 MB
		, 在所有 C++ 提交中击败了
		6.97 %
		的用户*/
	void setZeroes(vector<vector<int>>& matrix) {
		int m = (int)matrix.size();
		int n = (int)matrix[0].size();

		unordered_set<int> row;
		for (int i = 0; i < m; i++)
		{
			auto it = std::find(matrix[i].begin(), matrix[i].end(), 0);
			if (it != matrix[i].end())
				row.emplace(i);
		}

		unordered_set<int> col;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (matrix[j][i] == 0)
				{
					col.emplace(i);
					break;
				}
			}
		}

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (matrix[i][j] == 0)
					continue;
				if (row.find(i) != row.end() || col.find(j) != col.end())
					matrix[i][j] = 0;
			}
		}
	}

	//36. 有效的数独
	/*执行用时：
		12 ms
		, 在所有 C++ 提交中击败了
		98.63 %
		的用户
		内存消耗：
		17.4 MB
		, 在所有 C++ 提交中击败了
		93.39 %
		的用户*/
	bool isValidSudoku(vector<vector<char>>& board) {
		//check row
		for (int i = 0; i < 9; i++)
		{
			bool hashtable[9] = { false };
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] == '.') continue;
				if (hashtable[board[i][j] - '1']) 
					return false;
				hashtable[board[i][j] - '1'] = true;
			}
		}

		//check col
		for (int i = 0; i < 9; i++)
		{
			bool hashtable[9] = { false };
			for (int j = 0; j < 9; j++)
			{
				if (board[j][i] == '.') continue;
				if (hashtable[board[j][i] - '1']) 
					return false;
				hashtable[board[j][i] - '1'] = true;
			}
		}

		//check 3X3
		for (int i = 0; i < 9; i += 3)
		{
			for (int j = 0; j < 9; j += 3)
			{
				bool hashtable[9] = { false };
				for (int m = i; m < i + 3; m++)
				{
					for (int n = j; n < j + 3; n++)
					{
						if (board[m][n] == '.') continue;
						if (hashtable[board[m][n] - '1']) 
							return false;
						hashtable[board[m][n] - '1'] = true;
					}
				}
			}
		}

		return true;
	}

	//118. 杨辉三角
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.5 MB
		, 在所有 C++ 提交中击败了
		14.46 %
		的用户*/
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> result;
		result.resize(numRows);
		result[0] = { 1 };

		for (int row = 2; row <= numRows; row++)
		{
			for (int col = 0; col < row; col++)
			{
				if (col == 0 || col == row - 1)
					result[row - 1].emplace_back(1);
				else
					result[row - 1].emplace_back(result[row - 2][col - 1] + result[row - 2][col]);
			}
		}
		return result;
	}

	//566. 重塑矩阵
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		91.90 %
		的用户
		内存消耗：
		10.5 MB
		, 在所有 C++ 提交中击败了
		29.79 %
		的用户*/
	vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
		if (mat.empty() || mat[0].empty())
			return mat;

		int row = (int)mat.size();
		int col = (int)mat[0].size();
		if (row * col != r * c)
			return mat;

		vector<vector<int>> result;
		result.resize(r);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				result[(i * col + j) / c].emplace_back(mat[i][j]);
		}
		return result;
	}

	//350. 两个数组的交集 II
	/*执行用时：0 ms, 在所有 C++ 提交中击败了100.00 % 的用户
	内存消耗：9.8 MB, 在所有 C++ 提交中击败了63.37 % 的用户*/
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		std::sort(nums1.begin(), nums1.end());
		std::sort(nums2.begin(), nums2.end());

		std::vector<int> v_intersection;
		std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), std::back_inserter(v_intersection));
		return v_intersection;
	}

	//88. 合并两个有序数组
	/*执行用时：0 ms, 在所有 C++ 提交中击败了100.00 % 的用户
	内存消耗：8.8 MB, 在所有 C++ 提交中击败了73.45 % 的用户*/
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		vector<int> temp;
		temp.reserve(m + n);

		int i = 0, j = 0;
		while (i < m && j < n)
		{
			if (nums1[i] < nums2[j])
			{
				temp.emplace_back(nums1[i]);
				++i;
			}
			else
			{
				temp.emplace_back(nums2[j]);
				++j;
			}
		}

		for (; i < m; i++)
			temp.emplace_back(nums1[i]);

		for (; j < n; j++)
			temp.emplace_back(nums2[j]);

		nums1 = std::move(temp);
	}

	//1. 两数之和
	/*执行用时：8 ms, 在所有 C++ 提交中击败了85.15 % 的用户
	内存消耗：10.5 MB, 在所有 C++ 提交中击败了30.84 % 的用户*/
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> hashtable;
		for (int i = 0; i < nums.size(); ++i) {
			auto it = hashtable.find(target - nums[i]);
			if (it != hashtable.end()) {
				return { it->second, i };
			}
			hashtable[nums[i]] = i;
		}
		return {};
	}

	//53. 最大子序和
	/*执行用时：4 ms, 在所有 C++ 提交中击败了95.21 % 的用户
		内存消耗：12.7 MB, 在所有 C++ 提交中击败了89.34 % 的用户*/
	int maxSubArray(vector<int>& nums) {
		for (int i = 1; i < (int)nums.size(); i++)
			nums[i] = max(nums[i - 1] + nums[i], nums[i]);
		return *max_element(nums.begin(), nums.end());
	}

	//1846. 减小和重新排列数组后的最大元素
	/*执行用时：
		88 ms
		, 在所有 C++ 提交中击败了
		98.68 %
		的用户
		内存消耗：
		50.1 MB
		, 在所有 C++ 提交中击败了
		52.48 %
		的用户*/
	int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
		sort(arr.begin(), arr.end());
		arr[0] = 1;
		for (int i = 1; i < arr.size() - 1; i++)
		{
			if (arr[i + 1] > arr[i])
				arr[i + 1] = arr[i] + 1;
		}
		return std::min(*arr.rbegin(), (int)arr.size());
	}

	//1331. 数组序号转换
	/*执行用时：
		132 ms
		, 在所有 C++ 提交中击败了
		74.58 %
		的用户
		内存消耗：
		46.9 MB
		, 在所有 C++ 提交中击败了
		20.67 %
		的用户*/
	vector<int> arrayRankTransform(vector<int>& arr) {
		std::map<int, vector<int>> temp;
		for (int i = 0; i < (int)arr.size(); ++i)
			temp[arr[i]].emplace_back(i);

		int index{ 1 };
		for (const auto& p : temp)
		{
			for (const auto& n : p.second)
				arr[n] = index;
			++index;
		}
		return arr;
	}

	//1646. 获取生成数组中的最大值
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.1 MB
		, 在所有 C++ 提交中击败了
		51.00 %
		的用户*/
	int getMaximumGenerated(int n) {
		if (n < 2)
			return n;

		vector<int> result{ 0, 1 };
		for (int i = 2; i <= n; i++)
		{
			int value = (i % 2 == 0) ? result[i / 2] : (result[(i - 1) / 2] + result[(i - 1) / 2 + 1]);
			result.emplace_back(value);
		}
		return *max_element(result.begin(), result.end());
	}

	//LCP 07. 传递信息
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		70.68 %
		的用户
		内存消耗：
		7 MB
		, 在所有 C++ 提交中击败了
		37.46 %
		的用户*/
	int numWays(int n, vector<vector<int>>& relation, int k) {
		vector<vector<int>> edges(n);
		for (auto& edge : relation) {
			int src = edge[0], dst = edge[1];
			edges[src].push_back(dst);
		}

		int ways = 0;
		function<void(int, int)> dfs = [&](int index, int steps) {
			if (steps == k) {
				if (index == n - 1) {
					++ways;
				}
				return;
			}
			for (int to : edges[index]) {
				dfs(to, steps + 1);
			}
		};
		dfs(0, 0);
		return ways;
	}

	//面试题 17.10. 主要元素
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		91.20 %
		的用户
		内存消耗：
		18.4 MB
		, 在所有 C++ 提交中击败了
		17.51 %
		的用户*/
	int majorityElement(vector<int>& nums) {
		std::unordered_map<int, int> temp;
		int half{ (int)nums.size() / 2 };
		for (auto n : nums)
		{
			int& value = temp[n];
			++value;
			if (value > half)
				return n;
		}
		return -1;
	}

	//168. Excel表列名称
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		5.8 MB
		, 在所有 C++ 提交中击败了
		55.45 %
		的用户*/
	string convertToTitle(int n) {
		string result;
		while (n != 0)
		{
			int mod = (n - 1) % 26; //[0,25]
			n = (n - 1) / 26;
			result += ('A' + mod);
		}
		reverse(result.begin(), result.end());
		return result;
	}

	//401. 二进制手表
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.3 MB
		, 在所有 C++ 提交中击败了
		58.60 %
		的用户*/
	vector<string> readBinaryWatch(int turnedOn) {
		vector<string> ans;
		for (int h = 0; h < 12; ++h) {
			for (int m = 0; m < 60; ++m) {
				std::bitset<4> hour(h);
				std::bitset<6> minute(m);
				if (hour.count() + minute.count() == turnedOn) {
					ans.push_back(to_string(h) + ":" + (m < 10 ? "0" : "") + to_string(m));
				}
			}
		}
		return ans;
	}

	//852. 山脉数组的峰顶索引
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		94.97 %
		的用户
		内存消耗：
		11.3 MB
		, 在所有 C++ 提交中击败了
		23.53 %
		的用户*/
	int peakIndexInMountainArray(vector<int>& arr) {
		for (int i = 0; i < (int)arr.size() - 2; i++)
		{
			const int& a = arr[i];
			const int& b = arr[i + 1];
			const int& c = arr[i + 2];
			if (b > a && b > c)
				return i + 1;
		}
		return -1;
	}

	//1876. 长度为三且各字符不同的子字符串
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		59.53 %
		的用户*/
	int countGoodSubstrings(string s) {
		int result{};
		for (int i = 0; i < (int)s.length() - 2; i++)
		{
			char a = s[i];
			char b = s[i + 1];
			char c = s[i + 2];
			if (a != b && a != c && b != c)
				++result;
		}
		return result;
	}

	//1668. 最大重复子字符串
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.2 MB
		, 在所有 C++ 提交中击败了
		14.45 %
		的用户*/
	int maxRepeating(string sequence, string word) {
		int result{};
		string temp{ word };
		while (sequence.find(temp) != string::npos)
		{
			++result;
			temp += word;
		}
		return result;
	}

	//1629. 按键持续时间最长的键
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		99.65 %
		的用户
		内存消耗：
		10.3 MB
		, 在所有 C++ 提交中击败了
		87.02 %
		的用户*/
	char slowestKey(vector<int>& releaseTimes, string keysPressed) {
		vector<int> temp;
		temp.resize(26, 0);

		int pressTime{};
		for (int i = 0; i < (int)keysPressed.length(); i++)
		{
			char key = keysPressed[i];
			temp[key - 'a'] = std::max(releaseTimes[i] - pressTime, temp[key - 'a']);
			pressTime = releaseTimes[i];
		}
		
		auto it = max_element(temp.rbegin(), temp.rend());
		return (char)distance(temp.begin(), (++it).base()) + 'a';
	}

	//剑指 Offer 53 - I. 在排序数组中查找数字 I
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		80.67 %
		的用户
		内存消耗：
		12.8 MB
		, 在所有 C++ 提交中击败了
		72.45 %
		的用户*/
	int search(vector<int>& nums, int target) {
		int ret{};
		for (auto n : nums)
		{
			if (n > target)
				break;
			if (n == target)
				++ret;
		}
		return ret;
	}

	//523. 连续的子数组和
	/*执行用时：
		176 ms
		, 在所有 C++ 提交中击败了
		64.91 %
		的用户
		内存消耗：
		94.3 MB
		, 在所有 C++ 提交中击败了
		32.67 %
		的用户*/
	bool checkSubarraySum(vector<int>& nums, int k) {
		int size = (int)nums.size();
		if (size < 2)
			return false;

		unordered_map<int, int> remainder;

		int sum{ 0 };
		for (int i = 0; i < size; i++)
		{
			sum += nums[i]; //sum[0,i]
			int mod = (sum % k);
			if (i > 0 && mod == 0)
				return true;
			else if (remainder.find(mod) == remainder.end())
				remainder.insert({ mod, i });
			else if (i - remainder[mod] > 1)
				return true;
		}
		return false;
	}

	//1422. 分割字符串的最大得分
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.2 MB
		, 在所有 C++ 提交中击败了
		62.22 %
		的用户*/
	int maxScore(string s) {
		int left{};
		int right{};

		int ptr{ 1 };
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (i < ptr && s[i] == '0')
				++left;
			if (i >= ptr && s[i] == '1')
				++right;
		}

		int score{ left + right };
		int ret{ score };
		for (int i = ptr; i < (int)s.length() - 1; i++)
		{
			if (s[i] == '0')
				++score;
			else
				--score;

			ret = std::max(score, ret);
		}
		return ret;
	}

	//面试题 10.05. 稀疏数组搜索
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		86.81 %
		的用户
		内存消耗：
		11.7 MB
		, 在所有 C++ 提交中击败了
		5.07 %
		的用户*/
	int findString(vector<string>& words, string s) {
		std::unordered_map<string, int> temp;
		for (int i = 0; i < (int)words.size(); i++)
			temp[words[i]] = i + 1;
		return temp[s] - 1;
	}

	//面试题 01.04. 回文排列
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6.1 MB
		, 在所有 C++ 提交中击败了
		64.75 %
		的用户*/
	bool canPermutePalindrome(string s) {
		std::unordered_map<char, int> temp;
		for (auto c : s)
		{
			++temp[c];
		}

		int flag{};
		for (const auto& p : temp)
		{
			if (p.second % 2 != 0)
			{
				++flag;
				if (flag > 1)
					return false;
			}
		}
		return true;
	}

	//面试题 10.01. 合并排序的数组
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		8.9 MB
		, 在所有 C++ 提交中击败了
		8.37 %
		的用户*/
		/*void merge(vector<int>& A, int m, vector<int>& B, int n) {
			vector<int> temp;
			temp.reserve(m + n);

			int i = 0, j = 0;
			while (i < m && j < n)
			{
				if (A[i] < B[j])
				{
					temp.emplace_back(A[i]);
					++i;
				}
				else
				{
					temp.emplace_back(B[j]);
					++j;
				}
			}

			for (; i < m ; i++)
				temp.emplace_back(A[i]);

			for (; j < n; j++)
				temp.emplace_back(B[j]);

			A = std::move(temp);
		}*/

	//面试题 01.09. 字符串轮转
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		91.36 %
		的用户
		内存消耗：
		7.6 MB
		, 在所有 C++ 提交中击败了
		73.31 %
		的用户*/
	bool isFlipedString(string s1, string s2) {
		if (s1.length() != s2.length())
			return false;
		return (s2 + s2).find(s1) != string::npos;
	}

	//面试题 08.10. 颜色填充
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		84.22 %
		的用户
		内存消耗：
		13.2 MB
		, 在所有 C++ 提交中击败了
		44.01 %
		的用户*/
	void floodFill(vector<vector<int>>& image, int sr, int sc, int oldColor, int newColor) {
		if ((sr < 0 || sr >= (int)image.size()) || (sc < 0 || sc >= (int)image[0].size()))
		{
			return;
		}

		if (image[sr][sc] != oldColor || image[sr][sc] == newColor)
		{
			return;
		}

		image[sr][sc] = newColor;

		floodFill(image, sr, sc + 1, oldColor, newColor);
		floodFill(image, sr, sc - 1, oldColor, newColor);
		floodFill(image, sr - 1, sc, oldColor, newColor);
		floodFill(image, sr + 1, sc, oldColor, newColor);
	}

	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		floodFill(image, sr, sc, image[sr][sc], newColor);
		return image;
	}

	//剑指 Offer 11. 旋转数组的最小数字
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		92.24 %
		的用户
		内存消耗：
		11.8 MB
		, 在所有 C++ 提交中击败了
		22.04 %
		的用户*/
	int minArray(vector<int>& numbers) {
		for (int i = 0; i < (int)numbers.size() - 1; i++)
		{
			if (numbers[i] > numbers[i + 1])
				return numbers[i + 1];
		}
		return numbers[0];
	}

	//1869. 哪种连续子字符串更长
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		5.9 MB
		, 在所有 C++ 提交中击败了
		62.44 %
		的用户*/
	bool checkZeroOnes(string s) {
		char last{};
		int size{};

		vector<int> ret{ 0, 0 };
		for (int i = 0; i < (int)s.size(); i++)
		{
			if (last != '\0' && s[i] != last)
			{
				int index = (last == '1' ? 1 : 0);
				ret[index] = std::max(size, ret[index]);
				size = 0;
			}
			last = s[i];
			++size;
		}
		if (size != 0)
		{
			int index = (last == '1' ? 1 : 0);
			ret[index] = std::max(size, ret[index]);
		}
		return ret[1] > ret[0];
	}

	//面试题 01.06. 字符串压缩
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		90.43 %
		的用户
		内存消耗：
		7.1 MB
		, 在所有 C++ 提交中击败了
		90.81 %
		的用户*/
	string compressString(string S) {
		char last{ '0' };
		int size{};

		string ret;
		for (int i = 0; i < (int)S.size(); i++)
		{
			if (last != '0' && last != S[i])
			{
				ret.push_back(last);
				ret += to_string(size);
				size = 0;
			}
			last = S[i];
			++size;
		}

		if (size != 0)
		{
			ret.push_back(last);
			ret += to_string(size);
		}

		return ret.length() < S.length() ? ret : S;
	}

	//面试题 02.06. 回文链表
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		79.83 %
		的用户
		内存消耗：
		13.5 MB
		, 在所有 C++ 提交中击败了
		55.77 %
		的用户*/
	bool isPalindrome(ListNode* head) {
		string str;
		while (head)
		{
			str.push_back(head->val + '0');
			head = head->next;
		}
		return ::isPalindrome(str);
	}

	//1380. 矩阵中的幸运数
	/*执行用时：
		24 ms
		, 在所有 C++ 提交中击败了
		79.18 %
		的用户
		内存消耗：
		11.3 MB
		, 在所有 C++ 提交中击败了
		22.43 %
		的用户*/
	vector<int> luckyNumbers(vector<vector<int>>& matrix) {
		vector<int> columnMax;
		columnMax.resize((int)matrix[0].size(), 0);

		auto getColumnMax = [&matrix, &columnMax](int col) {
			if (columnMax[col] == 0)
			{
				for (int i = 0; i < (int)matrix.size(); i++)
					columnMax[col] = std::max(matrix[i][col], columnMax[col]);
			}
			return columnMax[col];
		};

		vector<int> ret;
		for (int i = 0; i < (int)matrix.size(); i++)
		{
			auto it = min_element(matrix[i].begin(), matrix[i].end());
			int j = (int)distance(matrix[i].begin(), it);
			if (*it == getColumnMax(j))
				ret.emplace_back(*it);
		}
		return ret;
	}

	//1455. 检查单词是否为句中其他单词的前缀
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		56.76 %
		的用户*/
	int isPrefixOfWord(string sentence, string searchWord) {
		auto words = splitString(sentence.c_str());
		for (int i = 0; i < (int)words.size(); i++)
		{
			size_t pos = words[i].find(searchWord);
			if (pos == 0)
				return i + 1;
		}
		return -1;
	}

	//696. 计数二进制子串
	/*执行用时：
		20 ms
		, 在所有 C++ 提交中击败了
		86.11 %
		的用户
		内存消耗：
		10.2 MB
		, 在所有 C++ 提交中击败了
		75.84 %
		的用户*/
	int countBinarySubstrings(string s) {
		int ptr = 0, n = (int)s.size(), last = 0, ans = 0;
		while (ptr < n) {
			char c = s[ptr];
			int count = 0;
			while (ptr < n && s[ptr] == c) {
				++ptr;
				++count;
			}
			ans += min(count, last);
			last = count;
		}
		return ans;
	}

	//874. 模拟行走机器人
	int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
		enum Direction
		{
			North = 0,
			East = 1,
			South = 2,
			West = 3,
		};

		vector<int> pos{ 0, 0 };
		int dir = Direction::North;

		auto changeDir = [&dir](int command) {
			switch (command)
			{
			case -2:
				--dir;
				break;
			case -1:
				++dir;
				break;
			default:
				break;
			}
			
			if (dir == -1)
				dir = West;
			else if (dir == 4)
				dir = North;
		};

		auto isCollision = [&obstacles](const vector<int>& pos) {
			return find(obstacles.begin(), obstacles.end(), pos) != obstacles.end();
		};

		auto doMove = [&pos, &dir, &obstacles, &isCollision](int command) {
			for (int i = 0; i < command ; i++)
			{
				vector<int> temp(pos);
				switch (dir)
				{
				case North:
					++temp[1];
					break;
				case East:
					++temp[0];
					break;
				case South:
					--temp[1];
					break;
				case West:
					--temp[0];
					break;
				default:
					break;
				}

				if (!isCollision(temp))
					pos = std::move(temp);
				else
					break;
			}
		};

		for (int i = 0; i < (int)commands.size(); i++)
		{
			switch (commands[i])
			{
			case -2:
			case -1:
				changeDir(commands[i]);
				break;
			default:
				doMove(commands[i]);
				break;
			}
		}

		return pos[0] * pos[0] + pos[1] * pos[1];
	}

	//342. 4的幂
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		5.9 MB
		, 在所有 C++ 提交中击败了
		22.30 %
		的用户*/
	bool isPowerOfFour(int n) {
		if (n <= 0)
			return false;

		while (n > 1)
		{
			if (n % 4 != 0)
				return false;
			n >>= 2;
		};

		return true;
	}

	//1576. 替换所有的问号
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		20.04 %
		的用户*/
	string modifyString(string s) {
		for (int i = 0; i < (int)s.length(); i++)
		{
			if (s[i] == '?')
			{
				char prev = i > 0 ? s[i - 1] : '/0';
				char next = i < (int)s.length() - 1 ? s[i + 1] : '/0';
				char c = 'a';
				while (c == prev || c == next)
					++c;
				s[i] = c;
			}
		}
		return std::move(s);
	}

	//477. 汉明距离总和
	/*执行用时：
		40 ms
		, 在所有 C++ 提交中击败了
		95.65 %
		的用户
		内存消耗：
		18.6 MB
		, 在所有 C++ 提交中击败了
		7.61 %
		的用户*/
	int totalHammingDistance(vector<int>& nums) {
		int ans = 0, n = (int)nums.size();
		for (int i = 0; i < 30; ++i) {
			int c = 0;
			for (int val : nums) {
				c += (val >> i) & 1;
			}
			ans += c * (n - c);
		}
		return ans;
	}

	//461. 汉明距离
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		5.8 MB
		, 在所有 C++ 提交中击败了
		47.70 %
		的用户*/
	int hammingDistance(int x, int y) {
		bitset<32> bs(x ^ y);
		return (int)bs.count();
	}

	//1828. 统计一个圆中点的数目
	/*执行用时：
		104 ms
		, 在所有 C++ 提交中击败了
		72.42 %
		的用户
		内存消耗：
		15.7 MB
		, 在所有 C++ 提交中击败了
		91.26 %
		的用户*/
	vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
		vector<int> ret;
		for (const auto& querie : queries)
		{
			int count{};
			for (const auto& point : points)
			{
				if (pointInCircle(point, querie))
					++count;
			}
			ret.emplace_back(count);
		}
		return ret;
	}

	//面试题 16.01. 交换数字
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		7 MB
		, 在所有 C++ 提交中击败了
		75.13 %
		的用户*/
	vector<int> swapNumbers(vector<int>& numbers) {
		swap2(numbers[0], numbers[1]);
		return numbers;
	}

	//1833. 雪糕的最大数量
	/*执行用时：
		168 ms
		, 在所有 C++ 提交中击败了
		84.23 %
		的用户
		内存消耗：
		74.7 MB
		, 在所有 C++ 提交中击败了
		20.70 %
		的用户*/
	int maxIceCream(vector<int>& costs, int coins) {
		sort(costs.begin(), costs.end());

		int i{};
		for (; i < (int)costs.size(); i++)
		{
			coins -= costs[i];
			if (coins <= 0)
				return coins == 0 ? i + 1 : i;
		}
		return i;
	}

	//剑指 Offer 64. 求1+2+…+n
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		6 MB
		, 在所有 C++ 提交中击败了
		63.71 %
		的用户*/
	int sumNums(int n) {
		if (n == 1)
			return 1;
		return n + sumNums(n - 1);
	}

	//剑指 Offer 57 - II. 和为s的连续正数序列
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		61.75 %
		的用户
		内存消耗：
		6.4 MB
		, 在所有 C++ 提交中击败了
		97.62 %
		的用户*/
	vector<vector<int>> findContinuousSequence(int target) {
		vector<vector<int>> ret;
		for (int i = 1; i <= target * 0.5; i++)
		{
			int sum{};
			int n{ i };
			while (sum < target)
				sum += n++;

			if (sum == target)
			{
				vector<int> temp;
				for (int j = i; j < n ; j++)
					temp.emplace_back(j);
				ret.emplace_back(temp);
			}
		}
		return ret;
	}

	//338. 比特位计数
	/*执行用时：
		4 ms
		, 在所有 C++ 提交中击败了
		95.07 %
		的用户
		内存消耗：
		8.3 MB
		, 在所有 C++ 提交中击败了
		15.15 %
		的用户*/
	vector<int> countBits(int n) {
		vector<int> ret;
		for (int i = 0; i <= n ; i++)
		{
			bitset<32> bs(i);
			ret.emplace_back((int)bs.count());
		}
		return ret;
	}

	//1837. K 进制表示下的各位数字总和
	/*执行用时：
		0 ms
		, 在所有 C++ 提交中击败了
		100.00 %
		的用户
		内存消耗：
		5.9 MB
		, 在所有 C++ 提交中击败了
		30.66 %
		的用户*/
	int sumBase(int n, int k) {
		int ret{};
		while (n != 0)
		{
			ret += (n % k);
			n /= k;
		}
		return ret;
	}

	//1796. 字符串中第二大的数字
	/*执行用时：
		12 ms
		, 在所有 C++ 提交中击败了
		22.30 %
		的用户
		内存消耗：
		9.1 MB
		, 在所有 C++ 提交中击败了
		5.08 %
		的用户*/
	int secondHighest(string s) {
		std::set<int> temp;
		for (const char& c : s)
		{
			if (isdigit(c))
				temp.emplace(c - '0');
		}
		return temp.size() > 1 ? *(++temp.rbegin()) : -1;
	}

	//剑指 Offer 53 - II. 0～n-1中缺失的数字
	/*执行用时：
		16 ms
		, 在所有 C++ 提交中击败了
		84.23 %
		的用户
		内存消耗：
		16.6 MB
		, 在所有 C++ 提交中击败了
		88.02 %
		的用户*/
	int missingNumber2(vector<int>& nums) {
		vector<bool> temp;
		temp.resize(nums.size() + 1, false);
		for (auto n : nums)
			temp[n] = true;
		for (int i = 0; i < (int)temp.size(); i++)
		{
			if (!temp[i])
				return i;
		}
		return -1;
	}

	//1742. 盒子中小球的最大数量
	/*执行用时：
		8 ms
		, 在所有 C++ 提交中击败了
		90.09 %
		的用户
		内存消耗：
		5.7 MB
		, 在所有 C++ 提交中击败了
		97.41 %
		的用户*/
	int countBalls(int lowLimit, int highLimit) {
		vector<int> temp;
		temp.resize(50, 0);
		for (int i = lowLimit; i <= highLimit; i++)
		{
			int index = digitSum(i);
			++temp[index];
		}
		return *max_element(temp.begin(), temp.end());
	}

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
		/*vector<int> twoSum(vector<int>& nums, int target) {
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
		}*/

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
		int left = 0, right = (int)nums.size();
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
		return sortedArrayToBST(nums, 0, (int)nums.size() - 1);
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
		return (int)bs.count();
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
			int countA = (int)bitset<14>(a).count();
			int countB = (int)bitset<14>(b).count();
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
		int a = (int)count_if(s.begin(), s.begin() + length, func);
		int b = (int)count_if(s.begin() + length, s.end(), func);
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
			return 0;

		int result{ 0 };
		int minPrice{ prices[0] };
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

//1656. 设计有序流
//执行用时：
//112 ms
//, 在所有 C++ 提交中击败了
//96.72 %
//的用户
//内存消耗：
//81.6 MB
//, 在所有 C++ 提交中击败了
//82.83 %
//的用户
class OrderedStream {
public:
	OrderedStream(int n) {
		m_data.resize(n, "");
	}

	vector<string> insert(int idKey, string value) {
		m_data[idKey - 1] = value;

		vector<string> ret;
		for (; m_ptr < (int)m_data.size(); m_ptr++)
		{
			if (m_data[m_ptr] == "")
				break;
			ret.emplace_back(m_data[m_ptr]);
		}
		return ret;
	}

private:
	vector<string> m_data;
	int m_ptr{};
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */

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

//面试题 03.01. 三合一
//执行用时：
//72 ms
//, 在所有 C++ 提交中击败了
//88.51 %
//的用户
//内存消耗：
//32.2 MB
//, 在所有 C++ 提交中击败了
//54.39 %
//的用户
class TripleInOne {
public:
	TripleInOne(int stackSize) {
		m_data.resize(stackSize * 3, 0);
		m_stackSize = stackSize;
	}

	void push(int stackNum, int value) {
		if (m_ptr[stackNum] == m_stackSize)
			return;
		m_data[stackNum * m_stackSize + m_ptr[stackNum]] = value;
		++m_ptr[stackNum];
	}

	int pop(int stackNum) {
		if (isEmpty(stackNum))
			return -1;
		int value = m_data[stackNum * m_stackSize + m_ptr[stackNum] - 1];
		--m_ptr[stackNum];
		return value;
	}

	int peek(int stackNum) {
		if (isEmpty(stackNum))
			return -1;
		return m_data[stackNum * m_stackSize + m_ptr[stackNum] - 1];
	}

	bool isEmpty(int stackNum) {
		return m_ptr[stackNum] == 0;
	}

private:
	vector<int> m_data;
	vector<int> m_ptr{ 0, 0, 0 };
	int m_stackSize{};
};

/**
 * Your TripleInOne object will be instantiated and called as such:
 * TripleInOne* obj = new TripleInOne(stackSize);
 * obj->push(stackNum,value);
 * int param_2 = obj->pop(stackNum);
 * int param_3 = obj->peek(stackNum);
 * bool param_4 = obj->isEmpty(stackNum);
 */
