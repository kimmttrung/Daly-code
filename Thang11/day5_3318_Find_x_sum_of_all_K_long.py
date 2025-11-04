# 3318. Find x_sum of all K-Long Subarrays

from collections import Counter
import heapq

# class Solution:
#     def findXSum(self, nums, k, x):
#         n = len(nums)
#         res = []

#         for i in range(n - k + 1):
#             # Đếm tần suất
#             freq = Counter(nums[i:i+k])

#             # Chuyển freq → list dạng (value, count)
#             arr = [(val, cnt) for val, cnt in freq.items()]

#             # Sort: count giảm dần → value giảm dần
#             arr.sort(key=lambda p: (-p[1], -p[0]))

#             # Lấy top-x
#             total = 0
#             count = 0
#             for val, cnt in arr:
#                 if count == x:
#                     break
#                 total += val * cnt
#                 count += 1

#             res.append(total)

#         return res

class Solution:
    def findXSum(self, nums, k, x):
        n = len(nums)
        ans = []

        for i in range(n - k + 1):
            sub = nums[i:i+k]

# #Đếm tần suất
            freq = Counter(sub)

#Max - heap(dùng số âm vì Python chỉ có min - heap)
            pq = [(-cnt, -val) for val, cnt in freq.items()]
            heapq.heapify(pq)

            total = 0
            take = x
            while take > 0 and pq:
                cnt, val = heapq.heappop(pq)
                cnt = -cnt
                val = -val
                total += cnt * val
                take -= 1

            ans.append(total)

        return ans
