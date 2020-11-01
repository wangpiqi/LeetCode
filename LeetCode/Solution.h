#pragma once

#include <vector>

using namespace std;

class Solution {
public:
	//LCP 06. ÄÃÓ²±Ò
	int minCount(vector<int>& coins) {
		int count{0};
		for (auto coin : coins)
		{
			count += (coin >> 1) + (coin & 1);
		}
		return count;
	}
};
