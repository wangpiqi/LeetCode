#pragma once

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	//21. 合并两个有序链表
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		//是否l1<l2
		auto compare = [](ListNode* l1, ListNode* l2) -> bool {
			if (!l1) return false;
			if (!l2) return true;
			return l1->val < l2->val;
		};

		ListNode* head{ compare(l1, l2) ? l1 : l2 };

		ListNode* last{ nullptr };
		while (l1 || l2)
		{
			ListNode*& node = compare(l1, l2) ? l1 : l2;
			if (last)
			{
				last->next = node;
			}
			last = node;
			node = node->next;
		}
		
		return head;
	}

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
