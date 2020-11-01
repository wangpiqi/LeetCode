#pragma once

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
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
