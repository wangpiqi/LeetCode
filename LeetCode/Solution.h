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
	//226. 翻转二叉树
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
	vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
		std::unordered_map<int, int> temp;
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
		return set.size();
	}

	//剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
	vector<int> exchange(vector<int>& nums) {
		/*sort(nums.begin(), nums.end(), [](int a, int b) {
			return (a & 1) > (b & 1);
		});
		return nums;*/

		int i = 0; int j = nums.size() - 1;
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
	double average(vector<int>& salary) {
		sort(salary.begin(), salary.end());
		double sum = accumulate(salary.begin() + 1, salary.end() - 1, 0);
		return sum / (salary.size() - 2);
	}

	//LCP 17. 速算机器人
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
	int game(vector<int>& guess, vector<int>& answer) {
		int result{};
		for (int i = 0; i < 3; ++i)
		{
			result += (guess[i] == answer[i] ? 1 : 0);
		}
		return result;
	}

	//1572. 矩阵对角线元素的和
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
	bool isUnique(string astr) {
		std::sort(astr.begin(), astr.end());
		return std::unique(astr.begin(), astr.end()) == astr.end();
	}

	//1512. 好数对的数目
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
	int xorOperation(int n, int start) {
		int result{ start };
		for (int i = 1; i < n; i++)
		{
			result ^= (start + 2 * i);
		}
		return result;
	}

	//剑指 Offer 10- II. 青蛙跳台阶问题
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
	bool containsDuplicate(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return std::unique(nums.begin(), nums.end()) != nums.end();
	}

	//1475. 商品折扣后的最终价格
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
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;
	}

	//5539. 按照频率将数组升序排序
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
	vector<int> runningSum(vector<int>& nums) {
		for (int i = 1; i < (int)nums.size(); i++)
		{
			nums[i] += nums[i - 1];
		}
		return nums;
	}

	//1394. 找出数组中的幸运数
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
	double trimMean(vector<int>& arr) {
		sort(arr.begin(), arr.end());
		int size = arr.size();
		int num = (int)(size * 0.05);
		double sum = accumulate(arr.begin() + num, arr.end() - num, 0);
		return sum / (size - 2 * num);
	}

	//剑指 Offer 25. 合并两个排序的链表
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
	int maxProduct(vector<int>& nums) {
		nth_element(nums.begin(), nums.begin() + 2, nums.end(), std::greater<int>());
		return (nums[0] - 1) * (nums[1] - 1);
	}

	//LCP 06. 拿硬币
	int minCount(vector<int>& coins) {
		int count{0};
		for (auto coin : coins)
		{
			count += (coin >> 1) + (coin & 1);
		}
		return count;
	}
};

//1114. 按序打印
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
