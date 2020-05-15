#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

/*
// 拼多多：最大乘积
int main () {
    int n, k;
    int A[n];
    cin >> n;
    // 两正+一正，两负+一正
    sort (A, A + n);
    long result = max ((long)A[n - 1] * (long)A[n - 2] * (long)A[n - 3], (long)A[0] * (long)A[1] * (long)A[n - 1]);
    cout << result << endl;
    return 0;
}
*/
// 拼多多：大整数相乘
/*
int main () {
    string s1, s2;
    cin >> s1 >> s2;
    vector<int> r (s1.length() + s2.length() + 1, 0);
    string result;
    int carry = 0;
    reverse (s1.begin(), s1.end());
    reverse (s2.begin(), s2.end());
    for (int i = 0; i < s1.length(); i ++) {
        for (int j = 0; j < s2.length(); j ++) {
            int tmp = (s2[j] - '0') * (s1[i] - '0') + carry + r[i + j];
            r[i + j] = tmp % 10;
            carry = tmp / 10;
        }
        r[i + s2.length()] += carry;
        carry = 0;
    }
    if (r[s1.length() + s2.length() - 1] != 0) result += ('0' + r[s1.length() + s2.length() - 1]);
    for (int i = s1.length() + s2.length() - 2; i >= 0; i --) {
        result += (r[i] + '0');
    }
    cout << result << endl;
}
*/
/*
// 拼多多：迷宫寻路
struct Node {
    int x;
    int y;
    int key;
    int step;
    Node (int x, int y, int key, int step) : x(x), y(y), key(key), step(step) {}
};

int main () {
    int M, N;
    cin >> M >> N;
    char mg[M][N];
    int key_status [M][N][1024];
    memset (key_status, sizeof(key_status), 0);
    queue<Node> q;

    for (int i = 0; i < M; i ++) {
        for (int j = 0; j < N; j ++) {
            cin >> mg[i][j];
            if (mg[i][j] == '2') q.push(Node(i, j, 0, 0));
        }
    }
    // 题目重点在于标记某点的访问状态需要与钥匙状态相关联
    // key = 0000000011表示拥有第一和第二两把钥匙
    // max(key) = 1023
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        int nx[4], ny[4];
        nx[0] = node.x + 1; ny[0] = node.y;
        nx[1] = node.x - 1; ny[1] = node.y;
        nx[2] = node.x; ny[2] = node.y + 1;
        nx[3] = node.x; ny[3] = node.y - 1;
        for (int i = 0; i < 4; i ++) {
            if (nx[i] >= M || nx[i] < 0 || ny[i] >= N || ny[i] < 0 || mg[nx[i]][ny[i]] == '0') continue;
            else if (mg[nx[i]][ny[i]] == '3') {
                cout << node.step + 1 << endl;
                return 0;
            }
            else {
                int key = node.key;
                if ('a' <= mg[nx[i]][ny[i]] && mg[nx[i]][ny[i]] <= 'z') key |= (1 << (mg[nx[i]][ny[i]] - 'a'));
                else if ('A' <= mg[nx[i]][ny[i]] && mg[nx[i]][ny[i]] <= 'Z') {
                    if ((key & (1 << (mg[nx[i]][ny[i]] - 'A'))) == 0) continue;
                }
                if (!key_status[nx[i]][ny[i]][key]) {
                    // 在钥匙为key状态下未访问过该点
                    key_status[nx[i]][ny[i]][key] = 1;
                    q.push(Node(nx[i], ny[i], key, node.step + 1));
                }
            }
        }
    }

    return 0;
}
*/
/*
// 拼多多：彩色的砖块
int main () {
    string str;
    cin >> str;
    sort (str.begin(), str.end());
    int count = 0;
    if (str.length() == 1) cout << 1 << endl;
    for (int i = 1; i < str.length(); i ++) {
        if (str[i] != str[i - 1]) count ++;
    }
    if (count <= 2) cout << count << endl;
    else cout << 0 << endl;
    return 0;
}
*/

// 拼多多：等差数列
/*
int main () {
    int n;
    while (cin >> n) {
        int x[n];
        for (int i = 0; i < n; i ++) cin >> x[i];
        sort (x, x + n);
        if (n <= 2) cout << "Possible" << endl;
        else {
            int difference = x[1] - x[0];
            for (int i = 1; i < n; i ++) {
                if (x[i] - x[i - 1] != difference) {
                    cout << "Impossible" << endl;
                    return 0;
                }
            }
        }
    }
   return 0;
}
*/
// 网易：交错01串
int main () {
    string s;
    cin >> s;
    if (s.length() == 1) {
        cout << 1 << endl;
        reutrn 0;
    }
    int result = 0;
    int count = 0;
    for (int i = 1; i < s.length(); i ++) {
        if (s[i] == s[i - 1]) {
            result = max (result, count);
            count = 0;
        }
        else count ++;
    }
}
