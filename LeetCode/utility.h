#pragma once

#include <vector>
#include <array>
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
#include <fstream>

using namespace std;

#pragma region

string readDataFile()
{
	ifstream file("./data.txt");
	if (!file.is_open())
	{
		return "";
	}

	ostringstream buf;
	char ch{};
	while (buf && file.get(ch))
		buf.put(ch);

	return buf.str();
}

int mystrlen(const char* str)
{
	if (!str)
		return 0;

	int len{};
	while (*str++ != '\0')
		++len;
	return len;
}

const char* mystrcpy(char* desc, const char* src)
{
	const char* ret = desc;
	if (!desc || !src)
		return ret;
	while ((*desc++ = *src++) != '\0');
	return ret;
}

const char* mystrcat(char* desc, const char* src)
{
	const char* ret = desc;
	if (!desc || !src)
		return ret;
	while (*desc != '\0')
		++desc;
	while ((*desc++ = *src++) != '\0');
	return ret;
}

class String
{
public:
	String(const char* str = "") noexcept
	{
		m_data = new char[mystrlen(str) + 1];
		mystrcpy(m_data, str);
	};

	String(String& other) noexcept
	{
		m_data = new char[mystrlen(other.m_data) + 1];
		mystrcpy(m_data, other.m_data);
	}

	String(String&& other) noexcept
	{
		m_data = other.m_data;
		other.m_data = nullptr;
	}

	String& operator=(String& other) noexcept
	{
		if (this == &other)
			return *this;

		delete[] m_data;
		m_data = new char[mystrlen(other.m_data) + 1];
		mystrcpy(m_data, other.m_data);
		return *this;
	}

	String& operator=(String&& other) noexcept
	{
		m_data = other.m_data;
		other.m_data = nullptr;
		return *this;
	}

	String operator+(String& other) noexcept
	{
		String sum;
		delete[] sum.m_data;
		sum.m_data = new char[mystrlen(m_data) + mystrlen(other.m_data) + 1];
		mystrcpy(sum.m_data, m_data);
		mystrcat(sum.m_data, other.m_data);
		return std::move(sum);
	}

	String& operator+=(String& other) noexcept
	{
		char* old = m_data;
		m_data = new char[mystrlen(old) + mystrlen(other.m_data) + 1];
		mystrcpy(m_data, old);
		mystrcat(m_data, other.m_data);
		delete[] old;
		return *this;
	}

	~String() noexcept
	{
		delete[] m_data;
	}

	const char* c_str() noexcept
	{
		return m_data;
	}

private:
	char* m_data{ nullptr };
};

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

void trimLeftTrailingSpaces(string& input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
		return !isspace(ch);
		}));
}

void trimRightTrailingSpaces(string& input) {
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
	return std::move(output);
}

vector<char> stringToCharVector(string input) {
	vector<char> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	char delim = ',';
	while (getline(ss, item, delim)) {
		output.push_back(item[1]);
	}
	return std::move(output);
}

vector<vector<int>> stringToIntegerVectorVector(string input, char delim = ',') {
	vector<vector<int>> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	while (getline(ss, item, delim)) {
		output.push_back(stringToIntegerVector(item));
	}
	return std::move(output);
}

vector<vector<char>> stringToCharVectorVector(string input, char delim = ',') {
	vector<vector<char>> output;
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	stringstream ss;
	ss.str(input);
	string item;
	while (getline(ss, item, delim)) {
		output.push_back(stringToCharVector(item));
	}
	return std::move(output);
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

	size_t pos{ 0 };
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

bool isPalindrome(const string& str)
{
	string temp(str);
	reverse(temp.begin(), temp.end());
	return str == temp;
}

int digitSum(int n) {
	int ret{};
	while (n != 0)
	{
		ret += n % 10;
		n /= 10;
	}
	return ret;
}

template <class T>
void clearContainer(T& container)
{
	T temp{};
	container.swap(temp);
}

void swap1(int& a, int& b)
{
	a += b;
	b = a - b;
	a -= b;
}

void swap2(int& a, int& b)
{
	a *= b;
	b = a / b;
	a /= b;
}

void swap3(int& a, int& b)
{
	a ^= b;
	b = a ^ b;
	a ^= b;
}

bool pointInCircle(const vector<int>& point, const vector<int>& circle)
{
	const int& x1 = point[0]; const int& y1 = point[1];
	const int& x0 = circle[0]; const int& y0 = circle[1];
	const int& radius = circle[2];

	const int& diffX = x1 - x0; const int& diffY = y1 - y0;
	if (diffX > radius || diffY > radius)
		return false;

	return pow(diffX, 2) + pow(diffY, 2) <= radius * radius;
}

vector<vector<int>> initMatrix(int m, int n)
{
	vector<vector<int>> matrix;
	matrix.resize(m);
	for (auto& row : matrix)
		row.resize(n, 0);
	return std::move(matrix);
}

//√∞≈›≈≈–Ú
void bubble_sort(vector<int>& array)
{
	for (int i = 0; i < (int)array.size() - 1; i++) {
		for (int j = 0; j < (int)array.size() - 1 - i; j++) {
			if (array[j] > array[j + 1])
				swap(array[j], array[j + 1]);
		}
	}
}

//—°‘Ò≈≈–Ú
void selection_sort(vector<int>& array)
{
	for (int i = 0; i < (int)array.size() - 1; i++)
	{
		int index{ i };
		for (int j = i + 1; j < (int)array.size(); j++)
		{
			if (array[j] < array[index])
				index = j;
		}
		swap(array[i], array[index]);
	}
}

#pragma endregion