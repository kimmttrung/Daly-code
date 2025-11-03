/*
1578.Minimum Time to Make Rope Colorfull
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int minCost(string colors, vector<int> &neededTime)
    {
        int total = 0;
        int sum = neededTime[0];
        int maxArr = neededTime[0];
        for (int i = 1; i < colors.length(); i++)
        {
            if (colors[i] == colors[i - 1])
            {
                sum += neededTime[i];                // 7
                maxArr = max(maxArr, neededTime[i]); // 4
            }
            else
            {
                total += sum - maxArr;  // 3
                sum = neededTime[i];    // 4
                maxArr = neededTime[i]; // 4
            }
        }
        total += sum - maxArr;

        return total;
    }
};
