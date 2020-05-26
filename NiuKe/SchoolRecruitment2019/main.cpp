#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits>

using namespace std;

// 网易：牛牛找工作
struct Work {
    int d, p;
    Work (int d, int p) : d(d), p(p) {}
};

bool Compare (Work w1, Work w2) {
    if (w1.d < w2.d) return true;
    else if (w1.d == w2.d && w1.p >= w2.p) return true;
    return false;
}

int NNFindJob () {
    int N, M;
    cin >> N >> M;
    vector<Work> w;
    for (int i = 0; i < N; i ++) {
        int di, pi;
        cin >> di >> pi;
        w.push_back ( Work (di, pi) );
    }

    // 按难度排序
    sort (w.begin(), w.end(), Compare);

    vector<pair<int, int>> A (M);
    for (int i = 0; i < M; i ++) {
        cin >> A[i].first;
        A[i].second = i;
    }
    // 按能力排序，但是需要记录伙伴位置
    sort (A.begin(), A.end());

    int result[M], pos1 = 0, pos2 = 0, cuSalary = 0;
    memset (result, 0, sizeof(result));
    while (pos1 < N && pos2 < M) {
        if (w[pos1].d <= A[pos2].first) {
            cuSalary = max (cuSalary, w[pos1++].p); // 该伙伴可以获得更高的工资
        }
        else {
            result[A[pos2 ++].second] = cuSalary; // 伙伴最高获得工资
        }
    }
    while (pos2 < M) result[A[pos2++].second] = cuSalary;
    for (int i = 0; i < M; i ++) cout << result[i] << endl;

    return 0;
}

// 网易：被3整除
int DivideBy3 () {
    int l, r;
    while (cin >> l >> r) {
        int sum = 0;
        for (int i = 0; i < l; i ++) {
            int k = i + 1;
            while (k % 10 != 0) {
                sum += k % 10;
                k /= 10;
            }
        }
        int count = 0;
        for (int i = l; i <= r; i ++) {
            if (sum % 3 == 0) count ++;
            int k = i + 1;
            while (k % 10 != 0) {
                sum += k % 10;
                k /= 10;
            }
        }
        cout << count << endl;
    }
    return 0;
}

// 网易：安置路灯
int StreetLamp () {
    int t;
    cin >> t;
    for (int i = 0; i < t; i ++) {
        int n;
        string road;
        cin >> n >> road;
        int light = 0;
        for (int j = 0; j < n;) {
            while (j < n && road[j] == 'X') j ++;
            if (j == n) break;
            light ++;
            j += 3;
        }
        cout << light << endl;
    }
    return 0;
}

// 网易：迷路的牛牛
int FindDirection () {
    int N;
    string str;
    // 0-L, 1-R, N-0, E-1, S-2, W-3
    int next[2][4] = {{3, 0, 1, 2}, {1, 2, 3, 0}};

    while (cin >> N >> str) {
        int direction = 0;
        for (int i = 0; i < N; i ++) {
            int lr = 0;
            if (str[i] == 'R') lr = 1;
            direction = next[lr][direction];
        }
        switch (direction) {
            case 0 : cout << "N" << endl; break;
            case 1 : cout << "E" << endl; break;
            case 2 : cout << "S" << endl; break;
            case 3 : cout << "W" << endl; break;
        }
    }
    return 0;
}

// 网易：数对
int NumberPairs () {
    int n, k;
    while (cin >> n >> k) {
        // k < y <= n
        // x = a*y + [k,y)
        // a <= n / y, a >= 0
        long count = 0;
        for (int y = k + 1; y <= n; y ++) {
            long a = n / y;
            count += a * (y - k); // a < n / y
            if (k == 0) count --;
            long p = n - a * y - k + 1;
            if (p > 0) count += p;
        }
        cout << count << endl;
    }
    return 0;
}

// 网易：矩形重叠
int MatrixOverlapping() {
    int n;
    cin >> n;
    int x1[n], y1[n], x2[n], y2[n];
    for (int i = 0; i < n; i ++) {
        cin >> x1[i];
    }
    for (int i = 0; i < n; i ++) {
        cin >> y1[i];
    }
    for (int i = 0; i < n; i ++) {
        cin >> x2[i];
    }
    for (int i = 0; i < n; i ++) {
        cin >> y2[i];
    }
    int result = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            // 每个重叠矩形必然包含某个点(x1[i], y1[j])
            // 所以只需要记录每个(x1[i], y1[j])点被多少矩形包含
            int cNum = 0;
            for (int k = 0; k < n; k ++) {
                if (x1[i] >= x1[k] && x1[i] < x2[k] && y1[j] >= y1[k] && y1[j] < y2[k]) {
                    cNum ++;
                }
            }
            result = max(result, cNum);
        }
    }
    cout << result << endl;
    return 0;
}

// 网易：牛牛的闹钟
int ClockOfNN() {
    int N;
    int X;
    pair<int, int> AB;
    const int minutesPerHour = 60;
    const int minutesPerDay = 24 * 60;
    while (cin >> N) {
        vector<pair<int, int>> clock (N);
        for (int i = 0; i < N; i ++) {
            cin >> clock[i].first >> clock[i].second;
        }
        cin >> X;
        cin >> AB.first >> AB.second;
        // 从零点开始算，到上课的分钟数
        int tmp = AB.first * minutesPerHour + AB.second;
        if (tmp - X >= 0) {
            // 可以在今天起床
            tmp = tmp - X;
        }
        else {
            // 需要提前一天起床
            tmp = minutesPerDay + tmp - X;
        }
        sort(clock.begin(), clock.end());
        pair<int, int> result;
        for (int i = 0; i < N; i ++) {
            if (clock[i].first * minutesPerHour + clock[i].second <= tmp) {
                result = clock[i];
            }
            else break;
        }
        cout << result.first << " " << result.second << endl;
    }
    return 0;
}

// 网易：牛牛的背包问题
long NNsBackpackDp(long *x, long n, long w);
int NNsBackpack() {
    long n, w;
    while (cin >> n >> w) {
        long result = 0;
        long v[n];
        long long sum = 0;
        for (long i = 0; i < n; i ++) {
            cin >> v[i];
            sum += v[i];
        }
        // 第i种零食放+第i种零食不放
        if (sum <= w) {
            // 部分用例可以用此判定条件筛除来减少运行时间
            cout << (1 << n) << endl;
        }
        else cout << NNsBackpackDp(v, n, w) << endl;
    }
    return 0;
}
long NNsBackpackDp(long *v, long n, long w) {
    if (w < 0) return 0;
    else if (n == 0) return 1;

    return (NNsBackpackDp(v + 1, n - 1, w) + NNsBackpackDp(v + 1, n - 1, w - v[0]));
}

// 网易：俄罗斯方块
int Tetris() {
    int n, m;
    while (cin >> n >> m) {
        // 记录每列落下了多少方块
        int tmp;
        int c[n] = {};
        for (int i = 0; i < m; i ++) {
            cin >> tmp;
            c[tmp - 1] ++;
        }
        int result = m;
        for (int i = 0; i < n; i ++) result = min(result, c[i]);
        cout << result << endl;
    }
    return 0;
}

// 网易：瞌睡
int Sleep() {
    int n, k;
    while (cin >> n >> k) {
        int a[n] = {};
        for (int i = 0; i < n; i ++) cin >> a[i];
        int t[n] = {};
        int interestWithNoWake = 0;
        for (int i = 0; i < n; i ++) {
            cin >> t[i];
            if (t[i] == 1) interestWithNoWake += a[i];
        }
        // 第0分钟叫醒的收益
        int income = 0;
        for (int i = 0; i < k && i < n; i ++) {
            if (t[i] == 0) income += a[i];
        }
        int result = interestWithNoWake + income;
        for (int i = 1; i < n && i + k - 1 < n; i ++) {
            if (t[i - 1] == 0) income -= a[i - 1];
            if (t[i + k - 1] == 0) income += a[i + k - 1];
            // 每分钟叫醒的收益
            result = max(result, interestWithNoWake + income);
        }
        cout << result << endl;
    }
    return 0;
}

// 网易：丰收
int Harvest() {
    int n;
    while (cin >> n) {
        int a[n];
        int sum = 0;
        for (int i = 0; i < n; i ++) {
            cin >> a[i];
            a[i] += sum;
            sum = a[i];
        }
        int m;
        cin >> m;
        vector<pair<int, int>> q (m);
        for (int i = 0; i < m; i ++) {
            cin >> q[i].first;
            q[i].second = i;
        }
        // 对询问排序，后面使用两个指针交替在两个数组上移动来确定堆数
        // 时间复杂度：O(m + n)
        sort(q.begin(), q.end());

        int result[m] = {};
        int posA = 0, posQ = 0;
        while (posA < n && posQ < m) {
            if (a[posA] < q[posQ].first) posA ++;
            else {
                result[q[posQ].second] = posA + 1;
                posQ ++;
            }
        }
        for (int i = 0; i < m; i ++) cout << result[i] << endl;
    }
    return 0;
}

// 网易：整理房间
struct Point {
    double a, b, x, y;
    int x1, y1;
    Point (double a, double b, double x, double y) : a(a), b(b), x(x), y(y) {}
    Point (int x1, int y1) : x1(x1), y1(y1) {}
};

Point AnticlockwiseRotate(Point p) {
    // 逆时针旋转特性：可构造全等三角形
    // 旋转之前：p(a1, b1, x1, y1)
    // 旋转之后：p(a2, b2, x1, y1)
    // 公式：a2 - x1 = y1 - b1, b2 - y1 = a1 - x1
    return Point (p.x + p.y - p.b, p.y - p.x + p.a, p.x, p.y);
}

bool IsSquare(Point p1, Point p2, Point p3, Point p4) {
    const double accuracy = 1e-8;

    // 首先判断点不能重合
    if (p1.a == p2.a && p1.b == p2.b) return false;
    if (p1.a == p3.a && p1.b == p3.b) return false;
    if (p1.a == p4.a && p1.b == p4.b) return false;
    if (p2.a == p3.a && p2.b == p3.b) return false;
    if (p2.a == p4.a && p2.b == p4.b) return false;
    if (p3.a == p4.a && p3.b == p4.b) return false;

    double distP1P2 = (p1.a - p2.a) * (p1.a - p2.a) + (p1.b - p2.b) * (p1.b - p2.b);
    double distP1P3 = (p1.a - p3.a) * (p1.a - p3.a) + (p1.b - p3.b) * (p1.b - p3.b);
    double distP1P4 = (p1.a - p4.a) * (p1.a - p4.a) + (p1.b - p4.b) * (p1.b - p4.b);
    double distP2P3 = (p2.a - p3.a) * (p2.a - p3.a) + (p2.b - p3.b) * (p2.b - p3.b);
    double distP2P4 = (p2.a - p4.a) * (p2.a - p4.a) + (p2.b - p4.b) * (p2.b - p4.b);
    double distP3P4 = (p3.a - p4.a) * (p3.a - p4.a) + (p3.b - p4.b) * (p3.b - p4.b);

    // p1, p2对角
    if (fabs(distP1P3 - distP1P4) < accuracy && fabs(distP1P3 - distP2P3) < accuracy && fabs(distP1P3 - distP2P4) < accuracy) {
        // 四边相等判断垂直
        if (fabs(distP1P3 + distP1P3 - distP1P2) < accuracy) return true;
    }
    // p1, p3对角
    if (fabs(distP1P2 - distP1P4) < accuracy && fabs(distP1P2 - distP2P3) < accuracy && fabs(distP1P2 - distP3P4) < accuracy) {
        if (fabs(distP1P2 + distP1P2 - distP1P3) < accuracy) return true;
    }
    // p1, p4对角
    if (fabs(distP1P2 - distP1P3) < accuracy && fabs(distP1P2 - distP2P4) < accuracy && fabs(distP1P2 - distP3P4) < accuracy) {
        if (fabs(distP1P2 + distP1P2 - distP1P4) < accuracy) return true;
    }
    return false;
}

int TidyRoom() {
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i ++) {
            vector<Point> point;
            for (int j = 0; j < 4; j ++) {
                double a, b, x, y;
                cin >> a >> b >> x >> y;
                point.push_back(Point(a, b, x, y));
            }
            int result = 13;
            for (int r1 = 0; r1 < 4; r1 ++) {
                for (int r2 = 0; r2 < 4; r2 ++) {
                    for (int r3 = 0; r3 < 4; r3 ++) {
                        for (int r4 = 0; r4 < 4; r4 ++) {
                            if (IsSquare(point[0], point[1], point[2], point[3])) result = min(result, r1 + r2 + r3 + r4);
                            point[3] = AnticlockwiseRotate(point[3]);
                        }
                        point[2] = AnticlockwiseRotate(point[2]);
                    }
                    point[1] = AnticlockwiseRotate(point[1]);
                }
                point[0] = AnticlockwiseRotate(point[0]);
            }
            if (result > 12) cout << -1 << endl;
            else cout << result << endl;
        }
    }
    return 0;
}

// 网易：表达式求值
int ExpresionValue() {
    int a, b, c;
    while (cin >> a >> b >> c) {
        int r1 = a + b + c;
        int result = r1;
        int r2 = a * b * c;
        result = max(result, r2);
        int r3 = (a + b) * c;
        result = max(result, r3);
        int r4 = a + b * c;
        result = max(result, r4);
        int r5 = a * b + c;
        result = max(result, r5);
        int r6 = a * (b + c);
        result = max(result, r6);
        cout << result << endl;
    }
    return 0;
}

// 网易：塔
int Tower() {
    int n, k;
    while (cin >> n >> k) {
        pair<int, int> a[n];
        for (int i = 0; i < n; i ++) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort (a, a + n);
        int s = a[n - 1].first - a[0].first;
        int m = 0;
        pair<int, int> fromTo[k];
        // s <= 1则无交换必要
        while (s > 1 && m < k) {
            // 最高值减1，向左移
            a[n - 1].first --;
            fromTo[m].first = a[n - 1].second;
            int posExchange = n - 2;
            while (posExchange >= 0 && a[posExchange].first > a[n - 1].first) posExchange --;
            swap(a[n - 1], a[posExchange + 1]);
            // 最低值加1，向右移
            a[0].first ++;
            fromTo[m].second = a[0].second;
            posExchange = 1;
            while (posExchange < n - 1 && a[posExchange].first < a[0].first) posExchange ++;
            swap(a[0], a[posExchange - 1]);
            // 更新差值
            s = a[n - 1].first - a[0].first;
            m ++;
        }
        cout << s << " " << m << endl;
        for (int i = 0; i < m; i ++) {
            cout << fromTo[i].first + 1 << " " << fromTo[i].second + 1 << endl;
        }
    }
    return 0;
}

// 网易：小易的字典
int CofMN(int m, int n) {
    long long result = 1;
    m = min(m, n - m);
    for (int i = 0; i < m; i ++) {
        result = result * (n - m + 1 + i) / (i + 1);
    }
    return result;
}
int XiaoYisDictionary() {
    int n, m, k;
    while (cin >> n >> m >> k) {
        string result;
        int numOfA = -1;
        long long sum = 1;
        for (int i = 0; i <= n; i ++) {
            // m个z与i个a排列组合
            if (sum < k) sum = sum * (m + i + 1) / (i + 1);
            else {
                numOfA = i;
                break;
            }
        }
        if (numOfA == -1) {
            cout << -1 << endl;
            continue;
        }
        for (int i = 0; i < n - numOfA; i ++) result += 'a';
        int Cmn = CofMN(numOfA - 1, m + numOfA - 1);
        while (k != Cmn) {
            // 第一位取a时，若后续位排列组合数仍达不到k，则说明第一位必须是z
            if (k > Cmn) {
                result += 'z';
                k -= Cmn;
                m --;
            }
            else if (k < Cmn) {
                result += 'a';
                numOfA --;
            }
            Cmn = CofMN(numOfA - 1, m + numOfA - 1);
        }
        numOfA --;
        result += 'a';
        while (m -- > 0) result += 'z';
        while (numOfA -- > 0) result += 'a';
        cout << result << endl;
    }
    return 0;
}

// 快手：获得更多的奖金
int EarnMoreMoney() {
    int n;
    while (cin >> n) {
        int d[n];
        for (int i = 0; i < n; i ++) cin >> d[i];
        int pos1 = 0, pos2 = n - 1;
        long sum1 = 0, sum2 = 0;
        int cut1 = 0, cut2 = n - 1;
        while (pos1 <= pos2 + 1) {
            if (sum1 == sum2) {
                cut1 = pos1;
                cut2 = pos2;
                sum1 += d[pos1 ++];
                sum2 += d[pos2 --];
            }
            else if (sum1 > sum2) {
                sum2 += d[pos2];
                pos2 --;
            }
            else if (sum1 < sum2) {
                sum1 += d[pos1];
                pos1 ++;
            }
        }
        long result = 0;
        for (int i = 0; i < cut1; i ++) {
            result += d[i];
        }
        cout << result << endl;
    }
    return 0;
}

// 快手：将满二叉树转化为求和树
struct TreeNode {
    int val;
    int sum;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int val) : val(val), sum(0), left(NULL), right(NULL) {}
};
TreeNode *ConstructTree(vector<int> qx, vector<int> zx) {
    if (qx.size() == 0) return NULL;
    vector<int> qx1, qx2, zx1, zx2;
    bool ch = 0;
    for (int i = 0; i < zx.size(); i ++) {
        if (zx[i] == qx[0]) ch = true;
        else if (ch) zx2.push_back(zx[i]);
        else zx1.push_back(zx[i]);
    }
    for (int i = 1; i < qx.size(); i ++) {
        if (i <= zx1.size()) qx1.push_back(qx[i]);
        else qx2.push_back(qx[i]);
    }
    TreeNode *result = new TreeNode (qx[0]);
    result -> left = ConstructTree(qx1, zx1);
    result -> right = ConstructTree(qx2, zx2);
    return result;
}
int ConstructSumTree(TreeNode *root) {
    if (root == NULL) return 0;
    root -> sum = ConstructSumTree(root -> left) + ConstructSumTree(root -> right);
    return root -> sum + root -> val;
}
void TraverseTreeInZX(TreeNode *root) {
    if (root == NULL) return;
    TraverseTreeInZX(root -> left);
    cout << root -> sum << " ";
    TraverseTreeInZX(root -> right);
}
int TranslateToSumTree() {
    int n = 0;
    vector<int> qx;
    vector<int> zx;
    int tmp;
    while (cin >> tmp) {
        qx.push_back(tmp);
        n ++;
        if (cin.get() == '\n') break;
    }
    while (cin >> tmp) {
        zx.push_back(tmp);
        if (cin.get() == '\n') break;
    }
    TreeNode *root = ConstructTree(qx, zx);
    ConstructSumTree(root);
    TraverseTreeInZX(root);
    return 0;
}

// 快手：搭积木
int BuildingBlocks() {
    int N;
    while (cin >> N) {
        pair<int, int> WL[N];
        for (int i = 0; i < N; i ++) {
            cin >> WL[i].first >> WL[i].second;
        }
        sort(WL, WL + N);
        int length[N] = {};
        int result = 1;
        length[0] = WL[0].second;
        // 问题转化为查找最长升序子序列长度
        for (int i = 1; i < N; i ++) {
            if (WL[i].second >= length[result - 1]) {
                length[result ++] = WL[i].second;
            }
            else {
                // 此处使用upper_bound查找出保证升序状态下的可替换元素位置
                // 替换掉该元素的作用：基于当前的最长升序子序列来为WL[i]重建一个属于它的当前最长升序子序列，该子序列对后续扩展要求的值更低
                // 如果WL[i]的最长升序子序列 < 当前，则该替换不会影响当前序列的扩展
                // 如果WL[i]的最长升序子序列 == 当前（替换的元素是当前序列的最后元素），则WL[i]的序列晋升为当前最长升序子序列
                *(upper_bound(length, length + result, WL[i].second)) = WL[i].second;
            }
        }
        cout << result << endl;
    }
    return 0;
}

static int climbinSt [1001] = {};

// 快手：魔法深渊
int ClimbinStairs(int N) {
    const int maxR = 1e9 + 3;
    int result = 0;
    if (N == 0) return 1;
    else if (climbinSt[N] > 0) return climbinSt[N];
    for (int step = 1; step <= N; step *= 2) {
        result += ClimbinStairs(N - step);
        result %= maxR;
    }
    climbinSt[N] = result;
    return result;
}
int MagicAbyss() {
    int M;
    cin >> M;
    for (int i = 0; i < M; i ++) {
        int N;
        cin >> N;
        int result = ClimbinStairs(N);
        cout << result << endl;
    }
    return 0;
}

// 快手：善变的同伴
// C++11(clang++ 3.9): 100%
// C++14(g++5.4): 80%
int FicklePartner() {
    int N, M;
    while (cin >> N >> M) {
        int combineA[N];
        int maxIndex = 0;
        cin >> combineA[0];
        int maxResult = 0;
        if (combineA[0] > 0) maxResult += combineA[0];
        for (int i = 1; i < N; i ++) {
            // 合并连续的正数和连续的负数
            int tmp;
            cin >> tmp;
            if (tmp > 0) maxResult += tmp;
            if ((tmp > 0 && combineA[maxIndex] < 0) || (tmp < 0 && combineA[maxIndex] > 0)) combineA[++ maxIndex] = tmp;
            else combineA[maxIndex] += tmp;
        }
        int maxM = 0; // 打菜maxM次就可以得到全局最大值
        if (maxIndex % 2 == 1) {
            // 元素个数为偶数
            maxM = (maxIndex + 1) / 2;
        }
        else {
            // 元素个数为奇数时，正数个数受排列影响
            if (combineA[0] > 0) maxM = maxIndex / 2 + 1;
            else maxM = maxIndex / 2;
        }

        // M次表示需要取出M个正数
        // maxM表示能够提供的正数
        if (maxM <= M) {
            cout << maxResult << endl;
        }
        else {
            // 最大m段子段和问题
            // 元素dp[i][j]表示前j个数取i段所能达到的最大值，第i段必须以第j个数结尾
            // 状态转移方程：
            // 第j个数与前面段相连：dp[i][j] = dp[i][j - 1] + combineA[j]
            // 第j个数单独一段：dp[i][j] = max(dp[i - 1][k]) + combineA[j] {0 < k < j}
            // int dp[M + 1][maxIndex + 2] = {};
            int maxA[M + 1];
            int dp01[2][M + 1];
            for (int i = 0; i < 2; i ++) {
                for (int j = 0; j < M + 1; j ++) {
                    dp01[i][j] = 0;
                }
            }
            for (int i = 0; i < M + 1; i ++) {
                maxA[i] = 0;
            }
            int result = 0;
            bool ch = 0;
            for (int j = 1; j <= maxIndex + 1; j ++) {
                ch = !ch;
                for (int i = 1; i <= M; i ++) {
                    // maxA[i] = max(dp[i - 1][j - 1], maxA[i]);
                    maxA[i] = max(dp01[ch][i - 1], maxA[i]);
                    dp01[!ch][i] = max(dp01[ch][i] + combineA[j - 1], maxA[i] + combineA[j - 1]);
                    // dp[i][j] = max(dp[i][j - 1] + combineA[j - 1], maxA[i] + combineA[j - 1]);
                    // result = max(result, dp[i][j]);
                    result = max(result, dp01[!ch][i]);
                }
            }
            cout << result << endl;
        }
    }

    return 0;
}

// 快手：字符串归一化
int StringNormalized() {
    const int cSize = 'z' - 'a' + 1;
    string str;
    while (cin >> str) {
        int count[cSize];
        memset(count, 0, sizeof(count));
        for (int i = 0; i < str.length(); i ++) count[str[i] - 'a'] ++;
        for (int i = 0; i < cSize; i ++) {
            if (count[i] > 0) {
                char c = 'a' + i;
                cout << c << count[i];
            }
        }
        cout << endl;
    }
    return 0;
}

// 快手：字符串排序
bool StrSortCompare(string s1, string s2) {
    if (s1.length() > s2.length()) return false;
    else return (s1.compare(s2) <= 0);
}
int StrSort() {
    int M;
    string str;
    vector<string> result;
    cin >> M;
    cin.get();
    for (int i = 0; i < M; i ++) {
        cin >> str;
        result.push_back(str.substr(str.length() - 6, 6));
    }
    sort(result.begin(), result.end(), StrSortCompare);
    for (int i = 0; i < M; i ++) {
        cout << result[i] << endl;
    }
    return 0;
}

// 快手：回文字符串（不要求字串连续）
int PalindromeStringNoContinuous() {
    string str;
    while (cin >> str) {
        int length = str.length();
        int dp[length][length];
        memset(dp, 0, sizeof(dp));
        for (int r = 0; r < length; r ++) {
            dp[r][r] = 1;
            for (int l = r - 1; l >= 0; l --) {
                if (str[l] == str[r]) dp[l][r] = dp[l + 1][r - 1] + 2;
                else dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
            }
        }
        cout << dp[0][length - 1] << endl;
    }
    return 0;
}
// 要求字符串连续
int PalindromeStringContinuous() {
    string str;
    while (cin >> str) {
        int length = str.length();
        string result;
        int resultLen = 0;
        bool dp[length][length];
        memset(dp, 0, sizeof(dp));
        for (int r = 0; r < length; r ++) {
            dp[r][r] = true;
            for (int l = r - 1; l >= 0; l --) {
                if (str[l] == str[r]) dp[l][r] = l + 1 > r - 1 ? true : dp[l + 1][r - 1];
                if (dp[l][r] && resultLen < r - l + 1) {
                    resultLen = r - l + 1;
                    result = str.substr(l, r - l + 1);
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}

// 快手：Latex爱好者
int LatexLover() {
    int N, P, H, W;
    // S*S*SUM(a)=H*W*P
    while (cin >> N >> P >> H >> W) {
        int a[N];
        int sumA = 0;
        for (int i = 0; i < N; i ++) {
            cin >> a[i];
            sumA += a[i];
        }
        int S = sqrt(double(H * W * P) / sumA);
        S = min(S, W);
        S = min(S, H);
        while (S > 0) {
            int oneLineWords = W / S;
            int linesOnePage = H / S;
            int lineLimit = linesOnePage * P;
            int sumLines = 0;
            for (int i = 0; i < N; i ++) sumLines += a[i] / oneLineWords + (a[i] % oneLineWords > 0);
            if (sumLines > lineLimit) S --;
            else break;
        }
        cout << S << endl;
    }
    return 0;
}

// 快手：游戏海报
int GamePoster() {
    string str;
    const int len = 'z' - 'a' + 1;
    while (cin >> str) {
        int count[len];
        memset(count, 0, sizeof(count));
        int result = 0;
        for (int i = 0; i < str.length(); i ++) count[str[i] - 'a'] ++;
        for (int i = 0; i < len; i ++) result += str.length() + 1 - count[i];
        cout << result << endl;
    }
    return 0;
}

// 快手：合并数组
int CombinedArray() {
    vector<int> a1, a2;
    int tmp;
    while (cin >> tmp) {
        a1.clear();
        a2.clear();
        a1.push_back(tmp);
        while (cin.get() == ',') {
            cin >> tmp;
            a1.push_back(tmp);
        }
        while (cin >> tmp) {
            a2.push_back(tmp);
            if (cin.get() == '\n') break;
        }
        int pos1 = 0, pos2 = 0;
        vector<int> result;
        while (pos1 < a1.size() && pos2 < a2.size()) {
            if (a1[pos1] > a2[pos2]) {
                result.push_back(a2[pos2 ++]);
            }
            else result.push_back(a1[pos1 ++]);
        }
        while (pos1 < a1.size()) result.push_back(a1[pos1 ++]);
        while (pos2 < a2.size()) result.push_back(a2[pos2 ++]);
        for (int i = 0; i < result.size() - 1; i ++) cout << result[i] << ",";
        cout << result[result.size() - 1] << endl;
    }
    return 0;
}

// 快手：字符串包含
int SubString() {
    string str1, str2;
    while (cin >> str1 >> str2) {
        if (str1.find(str2) != str1.npos || str2.find(str1) != str2.npos) cout << 1 << endl;
        else cout << 0 << endl;
    }
    return 0;
}

// 快手：最多数量货物装箱问题
int MaxNumber() {
    int X;
    while (cin >> X) {
        int pos1 = 0, pos2 = 0, pos3 = 0;
        vector<pair<int, int>> v;
        v.push_back(pair<int, int>(0, 0));
        int minV = 0;
        while (minV < X) {
            // 生成k个数的和组合升序列
            minV = min(v[pos1].first + 3, v[pos2].first + 5);
            minV = min(minV, v[pos3].first + 7);
            if (minV == v[pos1].first + 3) {
                v.push_back(pair<int, int>(minV, v[pos1].second + 1));
                pos1 ++;
            }
            if (minV == v[pos2].first + 5) {
                v.push_back(pair<int, int>(minV, v[pos2].second + 1));
                pos2 ++;
            }
            if (minV == v[pos3].first + 7) {
                v.push_back(pair<int, int>(minV, v[pos3].second + 1));
                pos3 ++;
            }
        }
        if (minV == X) cout << v[v.size() - 1].second << endl;
        else cout << -1 << endl;
    }
    return 0;
}

// 快手：最少数量货物装箱问题
int MinNumberHelper(int weight) {
    if (weight < 0) return -1;
    else if (weight == 0) return 0;
    int n1 = MinNumberHelper(weight - 7);
    int n2 = MinNumberHelper(weight - 5);
    int n3 = MinNumberHelper(weight - 3);
    if (n1 < 0) n1 = max(n2, n3);
    if (n2 < 0) n2 = max(n1, n3);
    if (n3 < 0) n3 = max(n1, n2);
    int result;
    result = min(n1, n2);
    result = min(result, n3);
    if (result < 0) return -1;
    else return result + 1;
}
int MinNumberOfGoods() {
    int X;
    while (cin >> X) {
        cout << MinNumberHelper(X) << endl;
    }
    return 0;
}

// 快手：回文子串
int PalindromeSubStrCount() {
    string str;
    while (cin >> str) {
        int len = str.length();
        bool dp[len][len];
        memset(dp, 0, sizeof(dp));
        int count = 0;
        for (int r = 0; r < len; r ++) {
            dp[r][r] = true;
            count ++;
            for (int l = r - 1; l >= 0; l --) {
                if (str[l] == str[r]) dp[l][r] = (l == r - 1) ? true : dp[l + 1][r - 1];
                if (dp[l][r]) count ++;
            }
        }
        cout << count << endl;
    }
    return 0;
}

// 快手：字符串压缩
int StringCompression() {
    string str;
    while (cin >> str) {
        char cuChar = str[0];
        int count = 1;
        for (int i = 1; i < str.length(); i ++) {
            if (str[i] == cuChar) count ++;
            else {
                cout << count << cuChar;
                cuChar = str[i];
                count = 1;
            }
        }
        cout << count << cuChar << endl;
    }
    return 0;
}

// 快手：解析加减法运算
int ParseAddSubOp() {
    int num = 0;
    while (cin >> num) {
        int result = num;
        char op;
        while ((op = cin.get()) != '\n') {
            cin >> num;
            switch (op) {
                case '+': result += num; break;
                case '-': result -= num; break;
            }
        }
        cout << result << endl;
    }
    return 0;
}

// 快手：求连续子数组的最大和
int MaxSumOfContinuousSubArray() {
    int num;
    while (cin >> num) {
        vector<int> v;
        v.push_back(num);
        while (cin.get() == ',') {
            cin >> num;
            v.push_back(num);
        }
        int len = v.size();
        int dp[len][len];
        // dp[l][r]表示连续子数组为l~r
        int result = 0;
        for (int r = 0; r < len; r ++) {
            dp[r][r] = v[r];
            result = max(result, v[r]);
            for (int l = r - 1; l >= 0; l --) {
                dp[l][r] = dp[l][r - 1] + v[r];
                result = max(result, dp[l][r]);
            }
        }
        cout << result << endl;
    }
    return 0;
}

// 快手：字符串长度最大面积
int MaxAreaOfStringLength() {
    string str;
    getline(cin, str);
    // 为每个字符串增加标记，表示有无a~z
    vector<pair<string, int>> v;
    for (int i = 0; i < str.length(); i ++) {
        if (str[i] == '\"') {
            string tmp = "";
            int sign = 0;
            i ++;
            while (str[i] != '\"') {
                sign |= (1 << (str[i] - 'a'));
                tmp += str[i ++];
            }
            v.push_back(pair<string, int>(tmp, sign));
        }
    }
    int result = 0;
    for (int i = 0; i < v.size(); i ++) {
        for (int j = i + 1; j < v.size(); j ++) {
            if ((v[i].second & v[j].second) == 0) {
                int tmp = v[i].first.length() * v[j].first.length();
                result = max(result, tmp);
            }
        }
    }
    cout << result << endl;
    return 0;
}

// 快手：今年的第几天
int DayOfThisYear() {
    int Y, M, D;
    int Day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (cin >> Y >> M >> D) {
        int runYear = 0;
        if ((Y % 4) == 0 && (Y % 100) != 0) runYear = 1;
        if ((Y % 400) == 0) runYear = 1;
        if (runYear) Day[1] = 29;
        int result = D;
        for (int i = 0; i < M - 1; i ++) result += Day[i];
        cout << result << endl;
    }
    return 0;
}

// 快手：数字序列第n位的值
int ValueOfNth() {
    int n;
    while (cin >> n) {
        int count = 0;
        int sum = 0;
        while (sum < n) sum += (++ count);
        cout << count << endl;
    }
    return 0;
}

// 快手：a/b
int ADivB() {
    int a, b;
    while (cin >> a >> b) {
        if (a % b == 0) cout << a / b << endl;
        else {
            string result;
            int tmp = a / b;
            int c_tmp = 10;
            while (tmp / c_tmp > 0) c_tmp *= 10;
            c_tmp /= 10;
            while (c_tmp != 0) {
                result += (char)(tmp / c_tmp + '0');
                tmp = tmp % c_tmp;
                c_tmp /= 10;
            }
            result += '.';
            // 计算循环部分
            // 通过余数判断，如果后续余数与前面某个余数相等，则说明进入循环
            int yuShuPos[b];
            memset(yuShuPos, 0, sizeof(yuShuPos));
            int cuA = (a % b) * 10;
            yuShuPos[a % b] = result.length();
            while (cuA != 0) {
                tmp = (cuA / b) + '0';
                result += tmp;
                if (yuShuPos[cuA % b] > 0) {
                    result += ')';
                    result.insert(yuShuPos[cuA % b], "(");
                    break;
                }
                yuShuPos[cuA % b] = result.length();
                cuA = (cuA % b) * 10;
            }
            cout << result << endl;
        }
    }
    return 0;
}

// 快手：最小代价爬楼梯
int ClimbStairsWithLowestCost() {
    vector<int> v;
    int cost;
    while (cin >> cost) {
        v.push_back(cost);
        if (cin.get() == '\n') break;
    }
    if (v.size() == 0) cout << 0 << endl;
    else {
        // 动态规划
        // dp[i]表示跳到第i层所需的最小代价
        // dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])
        int dp[v.size() + 1];
        dp[0] = 0;
        dp[1] = 0;
        for (unsigned int i = 0; i < v.size() - 1; i ++) {
            dp[i + 2] = min(dp[i] + v[i], dp[i + 1] + v[i + 1]);
        }
        cout << dp[v.size()] << endl;
    }
    return 0;
}

// 招商银行：鸡鸭分类问题
int ClassifyChickenDuck() {
    string str;
    cin >> str;
    // 最后只有两种情况：所有鸡在左边，或者所有鸡在右边
    int chicken = 0;
    int duck = 0;
    // 所有鸡在左边
    int posC = 0;
    int result1 = 0;
    for (int i = 0; i < str.length(); i ++) {
        if (str[i] == 'C') {
            result1 += (i - posC);
            posC ++;
        }
    }
    // 所有鸡在右边
    int posD = 0;
    int result2 = 0;
    for (int i = 0; i < str.length(); i ++) {
        if (str[i] == 'D') {
            result2 += (i - posD);
            posD ++;
        }
    }
    int result = min(result1, result2);
    cout << result << endl;
    return 0;
}

// 招商银行：比特币最佳买卖时机
int BestTimeOfBuySoldBitcoin() {
    vector<int> price;
    int p;
    while (cin >> p) {
        price.push_back(p);
        if (cin.get() == '\n') break;
    }
    // dp[i][j]表示第i天买入第j天卖出的收益
    int result = 0;
    int dp[price.size()][price.size()];
    for (int i = 0; i < price.size(); i ++) {
        for (int j = i; j < price.size(); j ++) {
            dp[i][j] = price[j] - price[i];
            result = max(dp[i][j], result);
        }
    }
    cout << result << endl;
    return 0;
}

// 招商银行：爱吃喵粮的小招喵
int EatingCat() {
    int N = 0;
    vector<int> p;
    int tmp;
    int sumP = 0;
    while (cin >> tmp) {
        N ++;
        sumP += tmp;
        p.push_back(tmp);
        if (cin.get() == '\n') break;
    }
    int H;
    cin >> H;
    // 平均速度为：sum(p) / H
    int K = sumP / H + (sumP % H > 0);
    while (true) {
        int time = 0;
        for (int i = 0; i < p.size(); i ++) {
            time += p[i] / K + (p[i] % K > 0);
        }
        if (time > H) K ++;
        else break;
    }
    cout << K << endl;
    return 0;
}

// 招商银行：X游戏
int XGame() {
    int N;
    cin >> N;
    // 只有含2，5，6，9的数为好数
    int count = 0 ;
    for (int i = 1; i <= N; i ++) {
        int num = i;
        int sign = 0;
        while (num > 0) {
            int ys = num % 10;
            if (sign != -1 && (ys == 2 || ys == 5 || ys == 6 || ys == 9)) sign = 1;
            else if (ys == 3 || ys == 4 || ys == 7) sign = -1;
            num = num / 10;
        }
        if (sign == 1) count ++;
    }
    cout << count << endl;
    return 0;
}

// 招商银行：糖果分配
int CandyDistribution() {
    vector<int> g, s;
    int gi, sj;
    while (cin >> gi) {
        g.push_back(gi);
        if (cin.get() == '\n') break;
    }
    while (cin >> sj) {
        s.push_back(sj);
        if (cin.get() == '\n') break;
    }
    // 将糖果尺寸和小孩胃口降序排序，每次试图满足剩余最大胃口的孩子
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());

    int posS = 0, posG = 0;
    int result = 0;
    while (posS < s.size() && posG < g.size()) {
        if (g[posG] <= s[posS]) {
            posS ++;
            posG ++;
            result ++;
        } else posS ++;
    }
    cout << result << endl;
    return 0;
}

// 招商银行：员工考勤记录
int WorkerAttendance() {
    // 连续N天只有0个A，1个A或者2个A都符合
    // 1 + C(1, N) + C(2, N)
    int N;
    while (cin >> N) {
        int result = 1 + N + N * (N - 1) / 2;
        cout << result << endl;
    }
    return 0;
}

// 招商银行：解码方法
int Decode() {
    string str;
    while (cin >> str) {
        // 动态规划，dp[i]表示i个字符的解码方法
        // (1) s[i - 1] ~ s[i]为有效编码：dp[i] = dp[i - 1] + dp[i - 2];
        // (2) s[i - 1] ~ s[i]为无效编码：dp[i] = dp[i - 1]
        vector<int> dp;
        dp.push_back(1);
        dp.push_back(1);
        for (int i = 1; i < str.length(); i ++) {
            if ((str[i - 1] == '1' && str[i] >= '0' && str[i] <= '9') || (str[i - 1] == '2' && str[i - 1] >= '0' && str[i - 1] <= '6')) {
                dp.push_back(dp[i] + dp[i - 1]);
            } else dp.push_back(dp[i]);
        }
        cout << dp[dp.size() - 1] << endl;
    }
    return 0;
}

// 招商：飘流船问题
int DriftingBoat() {
    vector<int> people;
    int limit;
    int weight;
    while (cin >> weight) {
        people.push_back(weight);
        if (cin.get() == '\n') break;
    }
    cin >> limit;
    sort(people.begin(), people.end());
    int posSt = 0, posEd = people.size() - 1;
    int result = 0;
    while (posEd >= posSt) {
        if (people[posEd] + people[posSt] > limit) {
            result ++;
            posEd --;
        }
        else {
            posSt ++;
            posEd --;
            result ++;
        }
    }
    cout << result << endl;
    return 0;
}