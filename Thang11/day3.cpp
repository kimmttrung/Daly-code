/*
2259.Count Ungruared Cells in th Grid
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int countUnguarded(int m, int n, vector<vector<int>> &guards, vector<vector<int>> &walls)
    {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        vector<vector<bool>> seen(m, vector<bool>(n, false));

        // Mark guards as 1, walls as 2
        for (auto &g : guards)
        {
            grid[g[0]][g[1]] = 1;
        }
        for (auto &w : walls)
        {
            grid[w[0]][w[1]] = 2;
        }

        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (auto &g : guards)
        {
            int r = g[0], c = g[1];

            for (auto &d : dirs)
            {
                int nr = r + d[0];
                int nc = c + d[1];

                while (nr >= 0 && nr < m && nc >= 0 && nc < n)
                {
                    // Stop if wall or guard
                    if (grid[nr][nc] == 2 || grid[nr][nc] == 1)
                        break;

                    seen[nr][nc] = true; // Mark as visible
                    nr += d[0];
                    nc += d[1];
                }
            }
        }

        // Count unguarded empty cells
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0 && !seen[i][j])
                    ans++;
            }
        }
        return ans;
    }
};