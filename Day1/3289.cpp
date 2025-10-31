/*
In the town of Digitville, there was a list of numbers called nums containing integers from 0 to n - 1.
Each number was supposed to appear exactly once in the list, however,
two mischievous numbers sneaked in an additional time, making the list longer than usual.
As the town detective, your task is to find these two sneaky numbers.
Return an array of size two containing the two numbers (in any order), so peace can return to Digitville.

Example 1:
Input: nums = [0,1,1,0]
Output: [0,1]
Explanation:
The numbers 0 and 1 each appear twice in the array.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<int> getSneakyNumbers(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<int> res;
        unordered_map<int, int> freq;

        for (int i = 0; i < nums.size(); i++)
        {
            freq[nums[i]]++;
        }
        for (auto &p : freq)
        {
            if (p.second > 1)
            {
                res.push_back(p.first);
            }
        }
        return res;
    }
};

// pythonclass Solution:
// def getSneakyNumbers(self, nums):
//     nums.sort()
//     res = []
//     freq = {}

//     for x in nums:
//         freq[x] = freq.get(x, 0) + 1

//     for k, v in freq.items():
//         if v > 1:
//             res.append(k)

//     return res