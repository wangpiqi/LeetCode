#pragma once

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
	//1502. �ж��ܷ��γɵȲ�����
	bool canMakeArithmeticProgression(vector<int>& arr) {
		if (arr.size() < 3)
		{
			return true;
		}

		sort(arr.begin(), arr.end());

		int diff = arr[1] - arr[0];
		for (int i = 1; i < arr.size() - 1; i++)
		{
			if (arr[i + 1] - arr[i] != diff)
				return false;
		}
		return true;
	}

	//1464. ��������Ԫ�ص����˻�
	int maxProduct(vector<int>& nums) {
		nth_element(nums.begin(), nums.begin() + 2, nums.end(), std::greater<int>());
		return (nums[0] - 1) * (nums[1] - 1);
	}

	//LCP 06. ��Ӳ��
	int minCount(vector<int>& coins) {
		int count{0};
		for (auto coin : coins)
		{
			count += (coin >> 1) + (coin & 1);
		}
		return count;
	}
};
