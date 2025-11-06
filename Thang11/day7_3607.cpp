#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <numeric>
#include <functional>

using namespace std;

class Solution
{
public:
    vector<int> processQueries(int c, vector<vector<int>> &connections, vector<vector<int>> &queries)
    {
        // --- DSU ---
        vector<int> parent(c + 1), sz(c + 1, 1);
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> findp = [&](int x)
        {
            return parent[x] == x ? x : parent[x] = findp(parent[x]);
        };

        auto uni = [&](int a, int b)
        {
            a = findp(a), b = findp(b);
            if (a == b)
                return;
            if (sz[a] < sz[b])
                swap(a, b);
            parent[b] = a;
            sz[a] += sz[b];
        };

        // Build DSU
        for (auto &e : connections)
            uni(e[0], e[1]);

        // Mỗi root có một set quản lý node online
        vector<set<int>> online(c + 1);
        vector<bool> isOnline(c + 1, true);

        // Insert all nodes
        for (int i = 1; i <= c; i++)
        {
            int r = findp(i);
            online[r].insert(i);
        }

        vector<int> ans;

        for (auto &q : queries)
        {
            int type = q[0], x = q[1];
            int r = findp(x);

            if (type == 1)
            {
                // Query
                if (isOnline[x])
                {
                    ans.push_back(x);
                }
                else
                {
                    if (online[r].empty())
                        ans.push_back(-1);
                    else
                        ans.push_back(*online[r].begin());
                }
            }
            else
            {
                // Turn offline
                if (isOnline[x])
                {
                    isOnline[x] = false;
                    online[r].erase(x);
                }
            }
        }

        return ans;
    }
};
