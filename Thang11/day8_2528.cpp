#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution
{
public:
    long long maxPower(vector<int> &stations, int r, int k)
    {
        int n = stations.size();
        // prefix sum để tính power ban đầu nhanh
        vector<ll> pref(n + 1, 0);
        ll totalStations = 0;
        for (int i = 0; i < n; ++i)
        {
            pref[i + 1] = pref[i] + stations[i];
            totalStations += stations[i];
        }

        // power[i] = sum of stations in [i-r, i+r]
        vector<ll> power(n, 0);
        for (int i = 0; i < n; ++i)
        {
            int L = max(0, i - r);
            int R = min(n - 1, i + r);
            power[i] = pref[R + 1] - pref[L];
        }

        // upper bound cho binary search: tổng trạm hiện có + k (không thể vượt tổng số trạm)
        ll left = 0, right = totalStations + k, ans = 0;

        auto can = [&](ll x) -> bool
        {
            // difference array cho các trạm đã thêm để mô phỏng ảnh hưởng lên các city
            vector<ll> diff(n + 1, 0); // diff[end] dùng để giảm curAdd
            ll curAdd = 0;             // hiện tại (tại i) có bao nhiêu trạm mới đang ảnh hưởng
            ll used = 0;               // số trạm đã dùng
            for (int i = 0; i < n; ++i)
            {
                curAdd += diff[i]; // apply diff at position i
                ll have = power[i] + curAdd;
                if (have < x)
                {
                    ll need = x - have; // cần thêm bấy nhiêu trạm
                    used += need;
                    if (used > k)
                        return false;
                    // đặt tất cả 'need' trạm ở vị trí xa nhất vẫn che được i:
                    int placePos = min(n - 1, i + r);
                    // các trạm này sẽ ảnh hưởng từ (placePos - r) tới (placePos + r)
                    // ở i chúng ta chỉ cần cập nhật curAdd (từ i tới endPos)
                    curAdd += need;
                    int endPos = min(n, placePos + r + 1); // exclusive index để trừ diff
                    diff[endPos] -= need;
                }
            }
            return used <= k;
        };

        while (left <= right)
        {
            ll mid = left + (right - left) / 2;
            if (can(mid))
            {
                ans = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return ans;
    }
};
