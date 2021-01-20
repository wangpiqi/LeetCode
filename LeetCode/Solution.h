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

#pragma endregion

class Solution {
public:
	//1356. �������ֶ������� 1 ����Ŀ����
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		99.99%
		���û�
		�ڴ����ģ�
		9.7 MB
		, ������ C++ �ύ�л�����
		99.90%
		���û�*/
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

	//1374. ����ÿ���ַ��������������ַ���
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.4 MB
		, ������ C++ �ύ�л�����
		75.27%
		���û�*/
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

	//1704. �ж��ַ����������Ƿ�����
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		82.51%
		���û�
		�ڴ����ģ�
		6.4 MB
		, ������ C++ �ύ�л�����
		99.66%
		���û�*/
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

	//1528. ���������ַ���
	/*ִ����ʱ��
		8 ms
		, ������ C++ �ύ�л�����
		96.78%
		���û�
		�ڴ����ģ�
		14.8 MB
		, ������ C++ �ύ�л�����
		96.24%
		���û�*/
	string restoreString(string s, vector<int>& indices) {
		vector<char> result;
		result.resize(s.length());
		for (int i = 0; i < (int)indices.size(); i++)
		{
			result[indices[i]] = s[i];
		}
		return string{ result.begin(), result.end() };
	}

	//1460. ͨ����ת������ʹ�����������
	/*ִ����ʱ��
		8 ms
		, ������ C++ �ύ�л�����
		99.81%
		���û�
		�ڴ����ģ�
		13.6 MB
		, ������ C++ �ύ�л�����
		99.81%
		���û�*/
	bool canBeEqual(vector<int>& target, vector<int>& arr) {
		sort(target.begin(), target.end());
		sort(arr.begin(), arr.end());
		return target == arr;
	}

	//1710. �����ϵ����Ԫ��
	/*ִ����ʱ��
		52 ms
		, ������ C++ �ύ�л�����
		98.92%
		���û�
		�ڴ����ģ�
		15.6 MB
		, ������ C++ �ύ�л�����
		98.01%
		���û�*/
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

	//628. �����������˻�
	/*ִ����ʱ��
		52 ms
		, ������ C++ �ύ�л�����
		92.07%
		���û�
		�ڴ����ģ�
		26.9 MB
		, ������ C++ �ύ�л�����
		83.92%
		���û�*/
	int maximumProduct(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int size = (int)nums.size();
		return std::max(std::max(nums[size - 1] * nums[size - 2] * nums[size - 3],
			nums[0] * nums[1] * nums[2]),
			nums[0] * nums[1] * nums[size - 1]);
	}

	//1688. �����е���Դ���
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		5.9 MB
		, ������ C++ �ύ�л�����
		97.10%
		���û�*/
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

	//1450. �ڼȶ�ʱ������ҵ��ѧ������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		11.1 MB
		, ������ C++ �ύ�л�����
		63.30%
		���û�*/
	int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
		int result{};
		for (int i = 0; i < (int)startTime.size(); i++)
		{
			if (queryTime >= startTime[i] && queryTime <= endTime[i])
				++result;
		}
		return result;
	}

	//1678. ��� Goal ������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.2 MB
		, ������ C++ �ύ�л�����
		98.90%
		���û�*/
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

	//1684. ͳ��һ���ַ�������Ŀ
	/*ִ����ʱ��
		136 ms
		, ������ C++ �ύ�л�����
		44.81%
		���û�
		�ڴ����ģ�
		29.8 MB
		, ������ C++ �ύ�л�����
		86.51%
		���û�*/
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

	//1720. �������������
	/*ִ����ʱ��
		80 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		25.8 MB
		, ������ C++ �ύ�л�����
		100.00%
		���û�*/
	vector<int> decode(vector<int>& encoded, int first) {
		vector<int> result{ first };
		for (auto e : encoded)
			result.emplace_back(first ^= e);
		return result;
	}

	//605. �ֻ�����
	/*ִ����ʱ��36 ms, ������ C++ �ύ�л�����85.15%���û�
	�ڴ����ģ�20.3 MB, ������ C++ �ύ�л�����35.64%���û�*/
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

	//1033. �ƶ�ʯ��ֱ������
	/*ִ����ʱ��0 ms, ������ C++ �ύ�л�����100.00%���û�
	�ڴ����ģ�6.6 MB, ������ C++ �ύ�л�����18.48%���û�*/
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

	//������ 08.01. ��������
	/*ִ����ʱ��4 ms, ������ C++ �ύ�л�����98.76%���û�
	�ڴ����ģ�6.2 MB, ������ C++ �ύ�л�����65.83%���û�*/
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

	//1652. ��ը��
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		87.81%
		���û�
		�ڴ����ģ�
		8.7 MB
		, ������ C++ �ύ�л�����
		5.07%
		���û�*/
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

	//1266. �������е����Сʱ��
	/*ִ����ʱ��
		12 ms
		, ������ C++ �ύ�л�����
		82.35%
		���û�
		�ڴ����ģ�
		9.8 MB
		, ������ C++ �ύ�л�����
		23.53%
		���û�*/
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

	//1108. IP ��ַ��Ч��
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.3 MB
		, ������ C++ �ύ�л�����
		14.88%
		���û�*/
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

	//1389. ���ȶ�˳�򴴽�Ŀ������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		8.7 MB
		, ������ C++ �ύ�л�����
		7.07%
		���û�*/
	vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
		vector<int> ret;
		int size = (int)nums.size();
		for (int i = 0; i < size; ++i)
		{
			ret.emplace(ret.begin() + index[i], nums[i]);
		}
		return ret;
	}

	//5613. ��пͻ����ʲ�����
	/*ִ����ʱ��
		12 ms
		, ������ C++ �ύ�л�����
		66.09%
		���û�
		�ڴ����ģ�
		8 MB
		, ������ C++ �ύ�л�����
		94.68%
		���û�*/
	int maximumWealth(vector<vector<int>>& accounts) {
		std::set<int> set;
		for (const auto& account : accounts)
		{
			set.insert(accumulate(account.begin(), account.end(), 0));
		}
		return *set.rbegin();
	}

	//976. �����ε�����ܳ�
	/*ִ����ʱ��
		100 ms
		, ������ C++ �ύ�л�����
		84.63%
		���û�
		�ڴ����ģ�
		20.6 MB
		, ������ C++ �ύ�л�����
		10.99%
		���û�*/
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

	//1370. �����½��ַ���
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		93.95%
		���û�
		�ڴ����ģ�
		7.8 MB
		, ������ C++ �ύ�л�����
		69.86%
		���û�*/
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

	//��ָ Offer 54. �����������ĵ�k��ڵ�
	/*ִ����ʱ��
		24 ms
		, ������ C++ �ύ�л�����
		94.89%
		���û�
		�ڴ����ģ�
		24.2 MB
		, ������ C++ �ύ�л�����
		15.41%
		���û�*/
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

	//������ 17.04. ��ʧ������
	/*ִ����ʱ��
		32 ms
		, ������ C++ �ύ�л�����
		96.88%
		���û�
		�ڴ����ģ�
		17.3 MB
		, ������ C++ �ύ�л�����
		10.53%
		���û�*/
	int missingNumber(vector<int>& nums) {
		int size = (int)nums.size();
		return int(size * (size + 1) * 0.5) - accumulate(nums.begin(), nums.end(), 0);
	}

	//226. ��ת������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		9.3 MB
		, ������ C++ �ύ�л�����
		35.65%
		���û�*/
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

	//1122. ������������
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		90.26%
		���û�
		�ڴ����ģ�
		8.1 MB
		, ������ C++ �ύ�л�����
		21.61%
		���û�*/
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

	//832. ��תͼ��
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		97.72%
		���û�
		�ڴ����ģ�
		8.6 MB
		, ������ C++ �ύ�л�����
		54.41%
		���û�*/
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

	//938. �����������ķ�Χ��
	/*ִ����ʱ��
		208 ms
		, ������ C++ �ύ�л�����
		90.06%
		���û�
		�ڴ����ģ�
		63.7 MB
		, ������ C++ �ύ�л�����
		36.20%
		���û�*/
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

	//922. ����ż�������� II
	/*ִ����ʱ��
		32 ms
		, ������ C++ �ύ�л�����
		99.05%
		���û�
		�ڴ����ģ�
		20.5 MB
		, ������ C++ �ύ�л�����
		29.90%
		���û�*/
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

	//804. ΨһĦ��˹�����
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		9 MB
		, ������ C++ �ύ�л�����
		13.23%
		���û�*/
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

	//��ָ Offer 21. ��������˳��ʹ����λ��ż��ǰ��
	/*ִ����ʱ��
		36 ms
		, ������ C++ �ύ�л�����
		92.57%
		���û�
		�ڴ����ģ�
		18.1 MB
		, ������ C++ �ύ�л�����
		25.92%
		���û�*/
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

	//1491. ȥ����͹��ʺ���߹��ʺ�Ĺ���ƽ��ֵ
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		7.3 MB
		, ������ C++ �ύ�л�����
		39.40%
		���û�*/
	double average(vector<int>& salary) {
		sort(salary.begin(), salary.end());
		double sum = accumulate(salary.begin() + 1, salary.end() - 1, 0);
		return sum / (salary.size() - 2);
	}

	//LCP 17. ���������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.2 MB
		, ������ C++ �ύ�л�����
		10.74%
		���û�*/
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

	//LCP 01. ������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.7 MB
		, ������ C++ �ύ�л�����
		5.41%
		���û�*/
	int game(vector<int>& guess, vector<int>& answer) {
		int result{};
		for (int i = 0; i < 3; ++i)
		{
			result += (guess[i] == answer[i] ? 1 : 0);
		}
		return result;
	}

	//1572. ����Խ���Ԫ�صĺ�
	/*ִ����ʱ��
		24 ms
		, ������ C++ �ύ�л�����
		99.85%
		���û�
		�ڴ����ģ�
		11.6 MB
		, ������ C++ �ύ�л�����
		5.25%
		���û�*/
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

	//������ 01.01. �ж��ַ��Ƿ�Ψһ
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.2 MB
		, ������ C++ �ύ�л�����
		42.31%
		���û�*/
	bool isUnique(string astr) {
		std::sort(astr.begin(), astr.end());
		return std::unique(astr.begin(), astr.end()) == astr.end();
	}

	//1512. �����Ե���Ŀ
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		7.5 MB
		, ������ C++ �ύ�л�����
		32.68%
		���û�*/
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

	//121. ������Ʊ�����ʱ��
	/*ִ����ʱ��
		8 ms
		, ������ C++ �ύ�л�����
		94.76%
		���û�
		�ڴ����ģ�
		13 MB
		, ������ C++ �ύ�л�����
		18.14%
		���û�*/
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

	//1431. ӵ������ǹ��ĺ���
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		84.61%
		���û�
		�ڴ����ģ�
		9.3 MB
		, ������ C++ �ύ�л�����
		6.24%
		���û�*/
	vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
		int maxCandies = *std::max_element(candies.begin(), candies.end());

		vector<bool> result;
		for (const auto& e : candies)
		{
			result.emplace_back(e + extraCandies >= maxCandies);
		}
		return result;
	}

	//643. ���������ƽ���� I
	/*ִ����ʱ��
		256 ms
		, ������ C++ �ύ�л�����
		88.19%
		���û�
		�ڴ����ģ�
		70.4 MB
		, ������ C++ �ύ�л�����
		15.61%
		���û�*/
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

	//1486. ����������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.3 MB
		, ������ C++ �ύ�л�����
		17.35%
		���û�*/
	int xorOperation(int n, int start) {
		int result{ start };
		for (int i = 1; i < n; i++)
		{
			result ^= (start + 2 * i);
		}
		return result;
	}

	//��ָ Offer 10- II. ������̨������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.3 MB
		, ������ C++ �ύ�л�����
		15.72%
		���û�*/
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

	//70. ��¥��
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.3 MB
		, ������ C++ �ύ�л�����
		21.95%
		���û�*/
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

	//941. ��Ч��ɽ������
	/*ִ����ʱ��
		52 ms
		, ������ C++ �ύ�л�����
		90.83%
		���û�
		�ڴ����ģ�
		22.2 MB
		, ������ C++ �ύ�л�����
		5.15%
		���û�*/
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

	//219. �����ظ�Ԫ�� II
	/*ִ����ʱ��
		72 ms
		, ������ C++ �ύ�л�����
		34.73%
		���û�
		�ڴ����ģ�
		15.6 MB
		, ������ C++ �ύ�л�����
		90.79%
		���û�*/
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

	//217. �����ظ�Ԫ��
	/*ִ����ʱ��
		56 ms
		, ������ C++ �ύ�л�����
		97.26%
		���û�
		�ڴ����ģ�
		14.8 MB
		, ������ C++ �ύ�л�����
		91.53%
		���û�*/
	bool containsDuplicate(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return std::unique(nums.begin(), nums.end()) != nums.end();
	}

	//1475. ��Ʒ�ۿۺ�����ռ۸�
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		98.24%
		���û�
		�ڴ����ģ�
		10 MB
		, ������ C++ �ύ�л�����
		45.91%
		���û�*/
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

	//1342. �����ֱ�� 0 �Ĳ�������
	/*ִ����ʱ��
		0 ms
		, ������ C++ �ύ�л�����
		100.00%
		���û�
		�ڴ����ģ�
		6.3 MB
		, ������ C++ �ύ�л�����
		8.92%
		���û�*/
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

	//������ 02.03. ɾ���м�ڵ�
	/*ִ����ʱ��
		12 ms
		, ������ C++ �ύ�л�����
		95.32%
		���û�
		�ڴ����ģ�
		8.2 MB
		, ������ C++ �ύ�л�����
		5.53%
		���û�*/
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;
	}

	//5539. ����Ƶ�ʽ�������������
	/*ִ����ʱ��
		36 ms
		, ������ C++ �ύ�л�����
		15.56%
		���û�
		�ڴ����ģ�
		11.2 MB
		, ������ C++ �ύ�л�����
		90.58%
		���û�*/
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

	//1480. һά����Ķ�̬��
	/*ִ����ʱ��
		4 ms
		, ������ C++ �ύ�л�����
		89.33%
		���û�
		�ڴ����ģ�
		8.7 MB
		, ������ C++ �ύ�л�����
		12.23%
		���û�*/
	vector<int> runningSum(vector<int>& nums) {
		for (int i = 1; i < (int)nums.size(); i++)
		{
			nums[i] += nums[i - 1];
		}
		return nums;
	}

	//1394. �ҳ������е�������
	/*ִ����ʱ��
		12 ms
		, ������ C++ �ύ�л�����
		88.72%
		���û�
		�ڴ����ģ�
		10.3 MB
		, ������ C++ �ύ�л�����
		63.12%
		���û�*/
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

	//349. ��������Ľ���
	/*ִ����ʱ��
		8 ms
		, ������ C++ �ύ�л�����
		96.25%
		���û�
		�ڴ����ģ�
		10.3 MB
		, ������ C++ �ύ�л�����
		79.93%
		���û�*/
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		std::sort(nums1.begin(), nums1.end());
		std::sort(nums2.begin(), nums2.end());

		std::vector<int> v_intersection;
		std::set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), std::back_inserter(v_intersection));

		auto last = std::unique(v_intersection.begin(), v_intersection.end());
		v_intersection.erase(last, v_intersection.end());

		return v_intersection;
	}

	//1619. ɾ��ĳЩԪ�غ�������ֵ
	/*ִ����ʱ��
		16 ms
		, ������ C++ �ύ�л�����
		92.65%
		���û�
		�ڴ����ģ�
		9.5 MB
		, ������ C++ �ύ�л�����
		75.66%
		���û�*/
	double trimMean(vector<int>& arr) {
		sort(arr.begin(), arr.end());
		int size = (int)arr.size();
		int num = (int)(size * 0.05);
		double sum = accumulate(arr.begin() + num, arr.end() - num, 0);
		return sum / (size - 2 * num);
	}

	//��ָ Offer 25. �ϲ��������������
	/*ִ����ʱ��
		32 ms
		, ������ C++ �ύ�л�����
		98.48%
		���û�
		�ڴ����ģ�
		19.2 MB
		, ������ C++ �ύ�л�����
		41.90%
		���û�*/
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

	//21. �ϲ�������������
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

	//1502. �ж��ܷ��γɵȲ�����
	/*ִ����ʱ��
		8 ms
		, ������ C++ �ύ�л�����
		85.00%
		���û�
		�ڴ����ģ�
		9.1 MB
		, ������ C++ �ύ�л�����
		34.72%
		���û�*/
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

	//1464. ��������Ԫ�ص����˻�
	/*ִ����ʱ��
		8 ms
		, ������ C++ �ύ�л�����
		94.42%
		���û�
		�ڴ����ģ�
		10 MB
		, ������ C++ �ύ�л�����
		50.88%
		���û�*/
	int maxProduct(vector<int>& nums) {
		nth_element(nums.begin(), nums.begin() + 2, nums.end(), std::greater<int>());
		return (nums[0] - 1) * (nums[1] - 1);
	}

	//LCP 06. ��Ӳ��
	/*ִ����ʱ��0 ms, ������ C++ �ύ�л�����100.00%���û�
	�ڴ����ģ�8.4 MB, ������ C++ �ύ�л�����12.28%���û�*/
	int minCount(vector<int>& coins) {
		int count{0};
		for (auto coin : coins)
		{
			count += (coin >> 1) + (coin & 1);
		}
		return count;
	}
};

//1114. �����ӡ
//ִ����ʱ��128 ms, ������ C++ �ύ�л�����84.99%���û�
//�ڴ����ģ�7.7 MB, ������ C++ �ύ�л�����14.63%���û�
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

//1603. ���ͣ��ϵͳ
//ִ����ʱ��116 ms, ������ C++ �ύ�л�����82.20%���û�
//�ڴ����ģ�32.7 MB, ������ C++ �ύ�л�����36.14%���û�
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
