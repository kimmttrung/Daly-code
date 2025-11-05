#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

class Solution
{
private:
    // Dùng kiểu 'Entry' cho cặp {tần suất, giá trị}
    using Entry = pair<int, long long>;

    // Biến thành viên để theo dõi trạng thái
    unordered_map<long long, int> freq; // Đếm tần suất
    set<Entry> top_x;                   // Set chứa top X
    set<Entry> others;                  // Set chứa phần còn lại
    long long current_x_sum;            // Tổng x-sum hiện tại
    int x_limit;                        // Giá trị của x

    /**
     * @brief Cân bằng lại 'top_x' và 'others' sau khi cập nhật.
     * Đảm bảo 'top_x' luôn giữ đúng số lượng phần tử tốt nhất.
     */
    void rebalance()
    {
        // Tính kích thước mục tiêu cho top_x
        int total_distinct = top_x.size() + others.size();
        int target_top_x_size = min(total_distinct, x_limit);

        // 1. Nếu 'top_x' quá nhỏ, lấy từ 'others' sang
        while (top_x.size() < target_top_x_size && !others.empty())
        {
            Entry best_other = *others.rbegin(); // Lớn nhất của 'others'
            others.erase(best_other);

            top_x.insert(best_other);
            current_x_sum += best_other.first * best_other.second; // freq * value
        }

        // 2. Nếu 'top_x' quá lớn, chuyển bớt sang 'others'
        while (top_x.size() > target_top_x_size)
        {
            Entry worst_top = *top_x.begin(); // Nhỏ nhất của 'top_x'
            top_x.erase(worst_top);

            others.insert(worst_top);
            current_x_sum -= worst_top.first * worst_top.second; // freq * value
        }

        // 3. Kiểm tra tráo đổi (trường hợp cạnh)
        // Phần tử nhỏ nhất của top_x có thể tệ hơn phần tử lớn nhất của others
        while (!top_x.empty() && !others.empty() && *top_x.begin() < *others.rbegin())
        {
            Entry worst_top = *top_x.begin();
            Entry best_other = *others.rbegin();

            // Tráo đổi chúng
            top_x.erase(worst_top);
            others.erase(best_other);

            top_x.insert(best_other);
            others.insert(worst_top);

            // Cập nhật lại sum
            current_x_sum -= worst_top.first * worst_top.second;
            current_x_sum += best_other.first * best_other.second;
        }
    }

    /**
     * @brief Cập nhật một giá trị trong cửa sổ, delta = +1 (thêm) hoặc -1 (xóa).
     */
    void update(long long val, int delta)
    {
        // 1. Lấy tần suất cũ và xóa entry cũ
        int old_count = freq[val];
        if (old_count > 0)
        {
            Entry old_entry = {old_count, val};
            if (top_x.count(old_entry))
            {
                top_x.erase(old_entry);
                current_x_sum -= old_entry.first * old_entry.second;
            }
            else
            {
                others.erase(old_entry);
            }
        }

        // 2. Cập nhật tần suất mới
        int new_count = old_count + delta;
        freq[val] = new_count;

        // 3. Thêm entry mới (nếu nó vẫn còn)
        if (new_count > 0)
        {
            // Luôn thêm vào 'others' trước, rebalance sẽ lo phần còn lại
            others.insert({new_count, val});
        }

        // 4. Cân bằng lại 2 set
        rebalance();
    }

    /**
     * @brief Dọn dẹp trạng thái (phòng trường hợp object bị tái sử dụng).
     */
    void resetState()
    {
        freq.clear();
        top_x.clear();
        others.clear();
        current_x_sum = 0;
        x_limit = 0;
    }

public:
    /**
     * @brief Tính X-Sum cho tất cả các cửa sổ con độ dài k.
     */
    vector<long long> findXSum(vector<int> &nums, int k, int x)
    {
        // Dọn dẹp trạng thái cũ (quan trọng nếu LeetCode tái sử dụng object)
        resetState();
        this->x_limit = x;
        int n = nums.size();

        vector<long long> answer;
        answer.reserve(n - k + 1); // Tối ưu hóa việc cấp phát bộ nhớ

        // 1. Xử lý cửa sổ đầu tiên (0 đến k-1)
        for (int i = 0; i < k; ++i)
        {
            update(nums[i], +1); // Thêm
        }
        answer.push_back(current_x_sum);

        // 2. Trượt cửa sổ (từ k đến hết)
        for (int i = k; i < n; ++i)
        {
            long long leaving_val = nums[i - k]; // Phần tử bị đẩy ra
            long long entering_val = nums[i];    // Phần tử mới đi vào

            update(leaving_val, -1);  // Bớt
            update(entering_val, +1); // Thêm

            answer.push_back(current_x_sum);
        }

        return answer;
    }
};