#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <limits.h>
#include <map>

using namespace std;

class Solution {
public:
    long long minimumValueAfterDispel (vector<int> &nums) {
        // 从最后运行结果来看：第一次取数要么是数组中的某个元素，要么是数组中两个元素的差值
        long maxDelete = 0;
        int size = nums.size();

        sort (nums.begin(), nums.end());
        long reduction [size];
        int tmp [size];
        for (int i = 0; i < size; i ++) reduction[i] = (long)(size - i) * (long)nums[i];
        // 第一次取某个元素
        for (int i = 0; i < size; i ++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            // 第一次取nums[i]
            int l = 0, r = i, index = 0;
            while (l < i && r < size) {
                if (nums[l] <= nums[r] - nums[i]) tmp[index ++] = nums[l ++];
                else tmp[index ++] = nums[r ++] - nums[i];
            }
            while (l < i) tmp[index ++] = nums[l ++];
            while (r < size) tmp[index ++] = nums[r ++] - nums[i];
            // 从tmp中取数tmp[j]
            for (int j = 0; j < size; j ++) {
                if (j > 0 && tmp[j] == tmp[j - 1]) continue;
                if (tmp[j] >= nums[i]) break;
                maxDelete = max (maxDelete, reduction[i] + (long)(nums.size() - j) * (long)tmp[j]);
            }
        }

        // 第一次取某个差值k=a-b，a和b均为数组元素，且a>b
        for (int i = 0; i < size; i ++) {
            // 需要限制aindex的值来使得第三重循环不会超时
            int aindex = i + 1;
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < size; j ++) {
                if (nums[j] == nums[j - 1] || nums[j] - nums[i] <= nums[i]) continue;
                // int aindex = 0;
                while (nums[aindex] < nums[j] - nums[i]) aindex ++; // 0~i之间不取数，i~aindex之间取数nums[i]，aindex~j之间取数nums[j]-nums[i]，j之后取数nums[j]
                maxDelete = max (maxDelete, reduction[j] + (long)(aindex - i) * (long)nums[i] + (long)(j - aindex) * (long)(nums[j] - nums[i]));
            }
        }

        long sum_all = 0;
        for (int i = 0; i < nums.size(); i ++) sum_all += nums[i];

        return (sum_all - maxDelete);
    }
    int countLR (vector<int>& a, vector<int>& b) {
        // sum[r] - sum[l] + a[l] = b[l] + b[r]
        // sum[r] - b[r] = sum[l] + b[l] - a[l]
        long sum[a.size()];
        int p_sum = 0;
        for (int i = 0; i < a.size(); i ++) {
            p_sum += a[i];
            sum[i] = p_sum;
        }
        map<long, int> m;
        int count = 0;
        for (int i = 0; i < a.size(); i ++) {
            m[sum[i] + b[i] - a[i]] ++;
            if (m[sum[i] - b[i]] != 0) count += m[sum[i] - b[i]];
        }
        return count;
    }
    int largestSubTriangle (int a, vector<int> &maps) {
        int result = largestSubTriangleHelper (a, maps);
        reverse (maps.begin(), maps.end());
        result = max (result, largestSubTriangleHelper (a, maps));
        return result;
    }
    int largestSubTriangleHelper (int a, vector<int> &maps) {
        int row = 0; // 从0行开始
        int count = 0; // row行第count个元素
        int row_number = 2 * a + 1; // 第0行的元素个数
        int n = 3 * a * a;
        int nn = n << 1;
        int maxlen [maps.size()];
        int result = 0;
        for (int i = 0; i < n; i ++) {
            count ++;
            // 从第0行开始构造三角形
            if (count == row_number + 1) {
                row ++;
                row_number += 2;
                count = 1;
            }
            // 奇数三角形不参与构造
            if (count % 2 == 1) {
                maxlen[i] = 0;
                continue;
            }
            // 任意行的第二个三角形和倒数第二个三角形不会作为头三角形参与构造
            if (count == 2 || count == row_number - 1) {
                maxlen[i] = maps[i];
                continue;
            }
            // 第0行的三角形仅保留属性
            if (row == 0) {
                maxlen[i] = maps[i];
                continue;
            }
            // 上一行与当前元素邻接的元素
            int up = i - (row_number - 1); // up 一定是第奇数个三角形
            int up_l = up - 1, up_r = up + 1;
            if (!maps[up] || !maps[i]) {
                maxlen[i] = maps[i];
            }
            else {
                maxlen[i] = maps[i] + min (maxlen[up_l], maxlen[up_r]);
            }
        }

        // 构造多边形下半部分
        row = 0;
        row_number = 4 * a - 1;
        count = 0;
        for (int i = n; i < nn; i ++) {
            count ++;
            if (count == row_number + 1) {
                row ++;
                row_number -= 2;
                count = 1;
            }
            // 偶数三角形不参与构造
            if (count % 2 == 0) {
                maxlen[i] = 0;
                continue;
            }
            // 第0行的第一个三角形和倒数第一个三角形不作为头三角参与构造
            if ((row == 0 && count == 1) || (row == 0 && count == row_number)) {
                maxlen[i] = maps[i];
                continue;
            }
            int up;
            if (row == 0) {
                up = i - row_number;
            }
            else up = i - (row_number + 1);
            int up_l = up - 1;
            int up_r = up + 1;
            if (!maps[up] || !maps[i]) {
                maxlen[i] = maps[i];
            }
            else {
                maxlen[i] = maps[i] + min (maxlen[up_l], maxlen[up_r]);
            }
        }
        for (int i = 0; i < maps.size(); i ++) result = max (result, maxlen[i]);
        return result;
    }
};
/*
int main () {
    Solution s;
    string a, b;
    cout << 'A' - '0' << endl;
    return 0;
}
*/
/*
class Record {
public:
    string filename;
    int line;
    int count;
    int order;
    Record (string s, int l, int c, int o) : filename(s), line(l), count(c), order(o) {}
};

bool Compare (Record r1, Record r2) {
    if (r1.count < r2.count) return false;
    else if (r1.count == r2.count && r1.order > r2.order) return false;
    else return true;
}

// 简单的错误记录
int main () {
    string str;
    int line;
    map<pair<string, int>, int> m;
    map<pair<string, int>, int> order_m;
    int order = 0;
    while (cin >> str >> line) {
        stringstream ss(str);
        while (getline(ss, str, '\\'));
        pair<string, int> p (str, line);
        if (order_m.find(p) == order_m.end()) {
            order_m[p] = order ++;
        }
        m[p] ++;
    }

    vector<Record> v;
    for (auto iter = m.begin(); iter != m.end(); iter ++) {
        Record r((iter -> first).first, (iter -> first).second, iter -> second, order_m[iter -> first]);
        v.push_back(r);
    }
    sort (v.begin(), v.end(), Compare);

    for (int i = 0; i < v.size() && i < 8; i ++) {
        if (v[i].filename.length() <= 16) cout << v[i].filename << " " << v[i].line << " " << v[i].count << endl;
        else cout << v[i].filename.substr(v[i].filename.length() - 16) << " " << v[i].line << " " << v[i].count << endl;
    }
    return 0;
}
*/
/*
// 扑克牌大小
int main () {
    int a[5];
    int b[5];
    int pos1 = 0, pos2 = 0;
    int status = 0;
    int sign = 0;
    string str;
    while (cin >> str) {
        for (int i = 0; i < str.length(); i ++) {
            if (str[i] == '-') sign = 1;
        }
        if (status == 0 && sign == 0) {
            if (str.length() == 5 && str[0] == 'j') a[pos1 ++] = 100;
            else if (str.length() == 5 && str[0] == 'J') a[pos1 ++] = 200;
            else if (str.length() == 2) a[pos1 ++] = 10;
            else a[pos1 ++] = str[0] - '0';
        }
        else if (status == 0 && sign == 1) {
            stringstream ss(str);
            string p_str;
            getline(ss, p_str, '-');
            if (p_str.length() == 5 && p_str[0] == 'j') a[pos1 ++] = 100;
            else if (p_str.length() == 5 && p_str[0] == 'J') a[pos1 ++] = 200;
            else if (p_str.length() == 2) a[pos1 ++] = 10;
            else a[pos1 ++] = p_str[0] - '0';
            getline(ss, p_str, '-');
            if (p_str.length() == 5 && p_str[0] == 'j') b[pos2 ++] = 100;
            else if (p_str.length() == 5 && p_str[0] == 'J') b[pos2 ++] = 200;
            else if (p_str.length() == 2) b[pos2 ++] = 10;
            else b[pos2 ++] = p_str[0] - '0';
            status = 1;
        }
        else if (status == 1) {
            if (str.length() == 5 && str[0] == 'j') b[pos2 ++] = 100;
            else if (str.length() == 5 && str[0] == 'J') b[pos2 ++] = 200;
            else if (str.length() == 2) b[pos2 ++] = 10;
            else b[pos2 ++] = str[0] - '0';
        }
    }
    // joker
    if ((pos1 == 2 && a[0] >= 100) || (pos2 == 2 && b[0] >= 100)) {
        if (a[0] == 100 || b[0] == 100) cout << "joker JOKER" << endl;
        else cout << "JOKER joker" << endl;
    }
    // 炸弹
    else if (pos1 == 4 || pos2 == 4) {
        char c;
        if (pos1 == 4 && pos2 != 4) {
            c = a[0] + '0';
        }
        else if (pos1 != 4 && pos2 == 4) {
            c = b[0] + '0';
        }
        else c = (a[0] > b[0] ? a[0] : b[0]) + '0';
        cout << c << " " << c << " " << c << " " << c << endl;
    }
    // 单张
    else if (pos1 == 1 && pos2 == 1) {
        int c = a[0] > b[0] ? a[0] : b[0];
        if (c == 100) cout << "joker" << endl;
        else if (c == 200) cout << "JOKER" << endl;
        else if (c == 10) cout << "10" << endl;
        else {
            char tmp = c + '0';
            cout << tmp << endl;
        }
    }
    // 对子
    else if (pos1 == 2 && pos2 == 2) {
        int c = a[0] > b[0] ? a[0] : b[0];
        if (c == 10) cout << "10 10" << endl;
        else {
            char tmp = c + '0';
            cout << tmp << " " << tmp << endl;
        }
    }
    // 三张
    else if (pos1 == 3 && pos2 == 3) {
        int c = a[0] > b[0] ? a[0] : b[0];
        if (c == 10) cout << "10 10 10" << endl;
        else {
            char tmp = c + '0';
            cout << c << " " << c << " " << c << endl;
        }
    }
    // 顺子
    else if (pos1 == 5 && pos2 == 5) {
        int c = a[0] > b[0] ? a[0] : b[0];
        if (c == 10) cout << "10 J Q K A" << endl;
        else if (c == 9) cout << "9 10 J Q K" << endl;
        else if (c == 8) cout << "8 9 10 J Q" << endl;
        else if (c == 7) cout << "7 8 9 10 J" << endl;
        else if (c == 6) cout << "6 7 8 9 10" << endl;
        else {
            char tmp = c + '0';
            cout << c << " " << c + 1 << " " << c + 2 << " " << c + 3 << " " << c + 4 << endl;
        }
    }
    else cout << "ERROR" << endl;
    return 0;
}
*/
// 华为2016校园招聘上机笔试题
// 最高分
int main () {
    int N, M;
    char c;
    int A, B;
    while (cin >> N >> M) {
        int score[N];
        for (int i = 0; i < N; i ++) cin >> score[i];
        while (M --) {
            cin >> c >> A >> B;
            if (c == 'Q') {
                int highest = 0;
                if (A > B) {
                    swap (A, B);
                }
                for (int i = A - 1; i < B; i ++) {
                    highest = max (highest, score[i]);
                }
                cout << highest << endl;
            }
            else {
                score[A - 1] = B;
            }
        }
    }
}