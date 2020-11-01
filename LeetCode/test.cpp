#include "Solution.h"

int main()
{
	Solution s;

	//vector<int> temp{ 4,2,1 };
	//s.minCount(temp);
	//s.mergeTwoLists(nullptr, nullptr);
	auto temp = stringToIntegerVector("[6,0,7,0,7,5,7,8,3,4,0,7,8,1,6,8,1,1,2,4,8,1,9,5,4,3,8,5,10,8,6,6,1,0,6,10,8,2,3,4]");
	s.trimMean(temp);

	system("pause");
	return 0;
}