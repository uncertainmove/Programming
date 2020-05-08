#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <limits.h>

using namespace std;

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode (int x) : val (x), next (NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode (int x) : val (x), left (NULL), right (NULL) {}
};

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode (int x) :
        label (x), next (NULL), random (NULL) {

    }
};

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode (int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

bool mycompare (const string s1, const string s2) {
    string s1_c = s1;
    string s2_c = s2;
    for (int i = s1.length(); i < s2.length(); i ++) {
        s1_c += s1[0];
    }
    for (int i = s2.length(); i < s1.length(); i ++) {
        s2_c += s2[0];
    }
    // cout << s1_c << " " << s2_c << " " << s2_c.compare(s1_c) << endl;
    if (s1_c.compare(s2_c) <= 0) return true;
    else return false;
}

class Solution {
private:
    vector<int> data;
    int hashArray [128];
    deque<char> deq;
    vector<string> permutationResult;
    stack<int> stack1;
    stack<int> stack2;
    int min_v;
public:
    Solution () {
    }
    char * longestPalindrome(char *s) {
        int s_length = 0;
        int max_length = 0;
        int left_position = 0;
        if (s == NULL) return NULL;
        for (int i = 0; s[i] != '\0'; i ++) {
            s_length ++;
        }
        if (s_length == 0) return s;
        // 思想：为了避免考虑奇数回文串和偶数回文串的区别，首先将原始字符串进行处理：
        // 如：abc => #a#b#c#（处理过后的字符串所包含的最长回文子串一定是奇数的）
        // 以每个原字符为中心，找出与其相关的最长回文串
        char *s_c = (char *) calloc (s_length * 2 + 2, sizeof(char));
        for (int i = 0; i < s_length * 2 + 1; i += 2) {
            s_c[i] = '#';
        }
        for (int i = 1; i < s_length * 2 + 1; i += 2) {
            s_c[i] = s[i / 2];
        }
        s_c[s_length * 2 + 1] = '\0';

        for (int i = 1; i < s_length * 2 + 1; i ++) {
            int step;
            for (step = 0; i - step >= 0 && i + step < s_length * 2 + 1; step ++) {
                if (s_c[i - step] != s_c[i + step]) break;
            }
            left_position = max_length > step - 1 ? left_position : (i - step + 1) / 2;
            max_length = max_length > step - 1 ? max_length : step - 1;
        }
        char *result = (char *) calloc (max_length + 1, sizeof(char));
        for (int i = 0; i < max_length; i ++) {
            result[i] = s[left_position + i];
        }
        result[max_length] = '\0';
        return result;
    }
        int lengthOfLongestSubString (char *s) {
        int left = 0;
        int max_length = 0;
        int letter[127]; // 记录字母最后出现的位置
        for (int i = 0; i < 127; i ++) {
            letter[i] = -1;
        }
        // 思路：从左至右扫描字母，并更新其位置。向右扫描一个字母，检查其当前位置：
        // 若当前位置小于left，则该字母目前不在序列中，更新该字母当前位置；
        // 若当前位置大于等于left，则该字母在序列中，此时更新left、该字母当前位置，以及max_length。
        for (int i = 0; s[i] != '\0'; i ++) {
            if (letter[s[i] - ' '] < left) letter[s[i] - ' '] = i;
            else if (letter[s[i] - ' '] >= left) {
                left = letter[s[i] - ' '] + 1;
                letter[s[i] - ' '] = i;
            }
            max_length = max_length > i - left + 1 ? max_length : i - left + 1;
        }

        return max_length;
    }
    int cutRope (int number) {
        int a [number + 1];
        if (number == 2) return 1;
        if (number == 3) return 2;
        if (number == 4) return 4;
        a[0] = 0;
        a[1] = 1;
        a[2] = 2;
        a[3] = 3;
        a[4] = 4;
        for (int i = 5; i <= number; i ++) {
            int max_v = 0;
            for (int j = 1; j <= number / 2; j ++) {
                max_v = max_v > a[j] * a[i - j] ? max_v : a[j] * a[i - j];
            }
            a[i] = max_v;
        }
        return a[number];
    }
    int movingCount (int threshold, int rows, int cols) {
        bool **visited = new bool*[rows];
        int result = 0;
        for (int i = 0; i < rows; i ++) {
            visited[i] = new bool[cols];
            for (int j = 0; j < cols; j ++) {
                visited[i][j] = false;
                int sum = 0;
                int data1 = i;
                int data2 = j;
                while (data1 != 0) {
                    sum += data1 % 10;
                    data1 /= 10;
                }
                while (data2 != 0) {
                    sum += data2 % 10;
                    data2 /= 10;
                }
                if (sum > threshold) visited[i][j] = true;
            }
        }
        movingCountHelper (rows, cols, 0, 0, visited, result);
        return result;
    }
    void movingCountHelper (int rows, int cols, int cur_rows, int cur_cols, bool **visited, int &result) {
        if (visited[cur_rows][cur_cols]) return;
        visited[cur_rows][cur_cols] = true;
        result ++;
        if (cur_rows != rows - 1) movingCountHelper (rows, cols, cur_rows + 1, cur_cols, visited, result);
        if (cur_rows != 0) movingCountHelper (rows, cols, cur_rows - 1, cur_cols, visited, result);
        if (cur_cols != cols - 1) movingCountHelper (rows, cols, cur_rows, cur_cols + 1, visited, result);
        if (cur_cols != 0) movingCountHelper (rows, cols, cur_rows, cur_cols - 1, visited, result);
    }
    bool hasPath (char *matrix, int rows, int cols, char *str) {
        bool **visited = new bool*[rows];
        for (int i = 0; i < rows; i ++) {
            visited[i] = new bool[cols];
            for (int j = 0; j < cols; j ++) visited[i][j] = false;
        }
        for (int i = 0; i < rows; i ++) {
            for (int j = 0; j < cols; j ++) {
                if (matrix[i * cols + j] == str[0]) {
                    visited[i][j] = true;
                    bool r = hasPathHelper (matrix, rows, cols, str + 1, i, j, visited);
                    visited[i][j] = false;
                    if (r == true) return true;
                }
            }
        }
        return false;
    }
    bool hasPathHelper (char *matrix, int rows, int cols, char *str, int pre_rows, int pre_cols, bool **visited) {
        if (*str == '\0') return true;
        bool r1 = false, r2 = false, r3 = false, r4 = false;
        if (pre_rows != rows - 1 && matrix[(pre_rows + 1) * cols + pre_cols] == *str && !visited[pre_rows + 1][pre_cols]) {
            visited[pre_rows + 1][pre_cols] = true;
            r1 = hasPathHelper (matrix, rows, cols, str + 1, pre_rows + 1, pre_cols, visited);
            visited[pre_rows + 1][pre_cols] = false;
        }
        if (r1) return true;
        if (pre_rows != 0 && matrix[(pre_rows - 1) * cols + pre_cols] == *str && !visited[pre_rows - 1][pre_cols]) {
            visited[pre_rows - 1][pre_cols] = true;
            r2 = hasPathHelper (matrix, rows, cols, str + 1, pre_rows - 1, pre_cols, visited);
            visited[pre_rows - 1][pre_cols] = false;
        }
        if (r2) return true;
        if (pre_cols != cols - 1 && matrix[pre_rows * cols + pre_cols + 1] == *str && !visited[pre_rows][pre_cols + 1]) {
            visited[pre_rows][pre_cols + 1] = true;
            r3 = hasPathHelper (matrix, rows, cols, str + 1, pre_rows, pre_cols + 1, visited);
            visited[pre_rows][pre_cols + 1] = false;
        }
        if (r3) return true;
        if (pre_cols != 0 && matrix[pre_rows * cols + pre_cols - 1] == *str && !visited[pre_rows][pre_cols - 1]) {
            visited[pre_rows][pre_cols - 1] = true;
            r4 = hasPathHelper (matrix, rows, cols, str + 1, pre_rows, pre_cols - 1, visited);
            visited[pre_rows][pre_cols - 1] = false;
        }
        if (r4) return true;
        return false;
    }
    vector<int> maxInWindows (const vector<int>& num, unsigned int size) {
        int st = 0, ed = size - 1;
        vector<int> result;
        if (num.size() == 0 || size == 0) return result;
        int max = num[0];
        if (size > num.size()) {
            return result;
        }
        for (int i = 0; i < size; i ++) max = max > num[i] ? max : num[i];
        result.push_back(max);
        st ++;
        ed ++;
        while (ed < num.size()) {
            if (num[st - 1] == max) {
                max = num[st];
                for (int i = st; i <= ed; i ++) max = max > num[i] ? max : num[i];
            }
            result.push_back(max > num[ed] ? max : num[ed]);
            st ++;
            ed ++;
        }
        return result;
    }
    void Insert (int num) {
        data.push_back(num);
        for (int i = data.size() - 1; i > 0; i --) {
            if (data[i] < data[i - 1]) {
                int tmp = data[i - 1];
                data[i - 1] = data[i];
                data[i] = tmp;
            }
            else break;
        }
    }
    double GetMedian () {
        if (data.size() % 2 == 1) return data[data.size() / 2];
        else {
            double d1 = data[data.size() / 2 - 1];
            double d2 = data[data.size() / 2];
            return (d1 + d2) / 2;
        }
    }
    TreeNode *KthNode (TreeNode *pRoot, int k) {
        TreeNode *result = NULL;
        KthNodeHelper (pRoot, k, result);
        return result;
    }
    void KthNodeHelper (TreeNode *pRoot, int &k, TreeNode *&result) {
        if (pRoot == NULL) return;
        if (k == 0) return;

        KthNodeHelper (pRoot -> left, k, result);

        if (k == 1) {
            result = pRoot;
            k --;
            return;
        }
        k --;
        KthNodeHelper (pRoot -> right, k, result);
    }
    char *Serialize (TreeNode *root) {
        // level order
        string result;
        bool sign = true;
        queue<TreeNode *> q[2];
        if (root == NULL) return NULL;
        q[0].push(root);
        int level = 0;
        while (!q[0].empty() || !q[1].empty()) {
            string result_p;
            while (!q[level % 2].empty()) {
                TreeNode *t = q[level % 2].front();
                if (t == NULL) {
                    result_p += "#";
                    q[(level + 1) % 2].push(NULL);
                    q[(level + 1) % 2].push(NULL);
                    q[level % 2].pop();
                }
                else {
                    sign = false;
                    result_p += to_string(t -> val);
                    result_p += "!";
                    q[(level + 1) % 2].push(t -> left);
                    q[(level + 1) % 2].push(t -> right);
                    q[level % 2].pop();
                }
            }
            // cout << result_p << " " << sign << endl;
            if (sign == true) break;
            sign = true;
            level ++;
            result += result_p;
            // cout << result << " " << sign << endl;
        }
        char *a = new char[result.length() + 1];
        for (int i = 0; i < result.length(); i ++) a[i] = result[i];
        a[result.length()] = '\0';
        return a;
    }
    TreeNode *Deserialize (char *str) {
        int length = 0;
        if (str == NULL) return NULL;
        while (str[length] != '\0') length ++;
        int pos = 0;
        string root_v;
        while (str[pos] != '!') root_v.push_back(str[pos ++]);
        pos ++;
        TreeNode *root = new TreeNode(stoi(root_v));
        queue<TreeNode *> q;
        q.push(root);
        bool sign = true;
        while (pos < length) {
            TreeNode *t = q.front();
            if (str[pos] == '#') {
                q.push(NULL);
                pos ++;
            }
            else {
                string stoint;
                while (str[pos] != '!') {
                    stoint.push_back(str[pos ++]);
                }
                pos ++;
                if (sign) {
                    t -> left = new TreeNode(stoi(stoint));
                    q.push(t -> left);
                }
                else {
                    t -> right = new TreeNode(stoi(stoint));
                    q.push(t -> right);
                }
            }
            if (!sign) q.pop();
            sign = !sign;
        }
        return root;
    }
    vector<vector<int>> Print (TreeNode *pRoot) {
        queue<TreeNode *> q[2];
        vector<vector<int>> result;
        if (pRoot == NULL) return result;
        q[0].push(pRoot);
        int level = 0;
        while (!q[0].empty() || !q[1].empty()) {
            vector<int> v_p;
            while (!q[level % 2].empty()) {
                TreeNode *t =  q[level % 2].front();
                v_p.push_back(t -> val);
                if (t -> left != NULL) q[(level + 1) % 2].push(t -> left);
                if (t -> right != NULL) q[(level + 1) % 2].push(t -> right);
                q[level % 2].pop();
            }
            result.push_back(v_p);
            level ++;
        }
        return result;
    }
    /*
    vector<vector<int>> Print (TreeNode *pRoot) {
        deque<TreeNode *> q[2];
        vector<vector<int>> result;
        int v_pos = 0;
        if (pRoot == NULL) return result;
        q[0].push_back(pRoot);
        while (!q[0].empty() || !q[1].empty()) {
            if (!q[0].empty()) {
                // left -> right
                vector<int> v_p;
                for (auto pt = q[0].begin(); pt != q[0].end(); pt ++) {
                    v_p.push_back((*pt) -> val);
                    cout << (*pt) -> val << " ";
                }
                cout << endl;
                result.push_back(v_p);
                while (!q[0].empty()) {
                    TreeNode *a = q[0].back();
                    if (a -> right != NULL) q[1].push_back (a -> right);
                    if (a -> left != NULL) q[1].push_back (a -> left);
                    q[0].pop_back();
                }
            }
            if (!q[1].empty()) {
                vector<int> v_p;
                for (auto pt = q[1].begin(); pt != q[1].end(); pt ++) {
                    v_p.push_back((*pt) -> val);
                    cout << (*pt) -> val << " ";
                }
                cout << endl;
                result.push_back(v_p);
                while (!q[1].empty()) {
                    TreeNode *a = q[1].back();
                    if (a -> left != NULL) q[0].push_back (a -> left);
                    if (a -> right != NULL) q[0].push_back (a -> right);
                    q[1].pop_back();
                }
            }
        }
        return result;
    }
    */
    bool isSymmetrical (TreeNode *pRoot) {
        if (pRoot == NULL) return true;
        TreeNode *pRoot_mirror = TreeDeepCopySymmetrical(pRoot);
        return isSymmetricalHelper (pRoot, pRoot_mirror);
    }
    bool isSymmetricalHelper (TreeNode *t1, TreeNode *t2) {
        if (t1 == NULL && t2 == NULL) return true;
        else if (t1 == NULL || t2 == NULL) return false;
        else if (t1 -> val != t2 -> val) return false;

        return isSymmetricalHelper (t1 -> left, t2 -> left) && isSymmetricalHelper (t1 -> right, t2 -> right);
    }
    TreeNode *TreeDeepCopySymmetrical (TreeNode *pRoot) {
        if (pRoot == NULL) return NULL;
        TreeNode *pRoot_mirror = new TreeNode(pRoot -> val);
        pRoot_mirror -> left = TreeDeepCopySymmetrical (pRoot -> right);
        pRoot_mirror -> right = TreeDeepCopySymmetrical (pRoot -> left);
        return pRoot_mirror;
    }
    TreeLinkNode *GetNext (TreeLinkNode *pNode) {
        int status = 0;
        TreeLinkNode *result = NULL;
        TreeLinkNode *root = pNode;
        while (root -> next != NULL) root = root -> next;
        GetNextHelper (root, pNode, status, result);
        return result;
    }
    void GetNextHelper (TreeLinkNode *root, TreeLinkNode *pNode, int &status, TreeLinkNode *&result) {
        if (root == NULL) return;
        GetNextHelper (root -> left, pNode, status, result);
        if (status == 1) {
            result = root;
            status = 2;
        }
        if (root == pNode) status = 1;
        if (status == 2) return;
        GetNextHelper (root -> right, pNode, status, result);
    }
    ListNode *deleteDuplication (ListNode *pHead) {
        if (pHead == NULL) return NULL;
        else if (pHead -> next == NULL) return pHead;
        int cur_val = pHead -> val;
        if (pHead -> next -> val == cur_val) {
            pHead = pHead -> next;
            while (pHead != NULL && pHead -> val == cur_val) pHead = pHead -> next;
            return deleteDuplication (pHead);
        }
        pHead -> next = deleteDuplication (pHead -> next);
        return pHead;
    }
    ListNode *EntryNodeOfLoop (ListNode *pHead) {
        set<ListNode*> s;
        if (pHead == NULL) return NULL;
        ListNode *p = pHead;
        while (p != NULL) {
            if (s.count(p) == 0) s.insert(p);
            else return p;
            p = p -> next;
        }
        return NULL;
    }
    void Insert (char ch) {
        ++ hashArray[ch - '\0'];
        if (hashArray[ch - '\0'] <= 1) deq.push_back(ch);
    }
    char FirstAppearingOnce () {
        while (hashArray[*(deq.begin()) - '\0'] > 1) deq.pop_front();
        if (deq.empty()) return '#';
        return *(deq.begin());
    }
    bool isNumeric (char *string) {
        int status = 0;
        int pos = 0;
        while (string[pos] != '\0') {
            switch (status) {
                case 0 :
                    if (string[pos] == '+' || string[pos] == '-') {
                        status = 1;
                        pos ++;
                    }
                    else if (string[pos] >= '0' && string[pos] <= '9') status = 1;
                    else return false;
                break;
                case 1 :
                    if (string[pos] >= '0' && string[pos] <= '9') pos ++;
                    else if (string[pos] == '.') {
                        status = 2;
                        pos ++;
                    }
                    else if ((string[pos] == 'e' || string[pos] == 'E') && string[pos + 1] != '\0') {
                        status = 3;
                        pos ++;
                    }
                    else return false;
                break;
                case 2 :
                    if (string[pos] >= '0' && string[pos] <= '9') pos ++;
                    else if (string[pos - 1] != '.' && (string[pos] == 'e' || string[pos] == 'E') && string[pos + 1] != '\0') {
                        status = 3;
                        pos ++;
                    }
                    else return false;
                break;
                case 3 :
                    if ((string[pos] == '+' || string[pos] == '-') && string[pos + 1] != '\0') {
                        status = 4;
                        pos ++;
                    }
                    else if (string[pos] >= '0' && string[pos] <= '9') status = 4;
                    else return false;
                break;
                case 4 :
                    if (string[pos] >= '0' && string[pos] <= '9') {
                        status = 4;
                        pos ++;
                    }
                    else return false;
                break;
            }
        }
        return true;
    }
    bool match (char *str, char *pattern) {
        if (*str != '\0' && *pattern == '\0') return false;
        if (*str == '\0' && *pattern == '\0') return true;

        if (*(pattern + 1) != '*') {
            if (*str == *pattern) {
                return match (str + 1, pattern + 1);
            } else if (*str != '\0' && *pattern == '.') {
                return match (str + 1, pattern + 1);
            } else return false;
        }
        else {
            if (*str == *pattern) {
                return match (str + 1, pattern) || match (str, pattern + 2);
            }
            else if (*str != '\0' && *pattern == '.') {
                return match (str + 1, pattern) || match (str, pattern + 2);
            }
            else {
                return match (str, pattern + 2);
            }
        }
    }
    vector<int> multiply (const vector<int> &A) {
        vector<int> B;
        for (int i = 0; i < A.size(); i ++) {
            B.push_back(1);
        }
        for (int i = 0; i < A.size(); i ++) {
            for (int j = 0; j < B.size(); j ++) {
                B[j] = (j == i ? B[j] : B[j] * A[i]);
            }
        }
        return B;
    }
    bool duplicate (int numbers[], int length, int *duplication) {
        set<int> s;
        int i = 0;
        for (i = 0; i < length; i ++) {
            if (s.count(numbers[i]) == 0) s.insert(numbers[i]);
            else {
                *duplication = numbers[i];
                break;
            }
        }
        if (i == length) return false;
        return true;
    }
    long StrToInt (string str) {
        if (str.length() == 0) return 0;
        if (str[0] != '+' && str[0] != '-' && (str[0] < '0' || str[0] > '9')) return 0;
        int st = 0;
        bool sign = true;
        if (str[0] == '+') {
            st ++;
            sign = true;
        }
        else if (str[0] == '-') {
            st ++;
            sign = false;
        }
        long result = 0;
        for (int i = st; i < str.length(); i ++) {
            if (str[i] >= '0' && str[i] <= '9') {
                if (sign) result = result * 10 + (str[i] - '0');
                else {
                    result = result * 10 - (str[i] - '0');
                }
            }
            else return 0;
        }
        return result;
    }
    int Add (int num1, int num2) {
        // 65 + 67 = 110 + 22 = 132
        int data = num1;
        int carry = num2;
        while (carry != 0) {
            int data_p = data;
            int carry_p = carry;
            data = data_p ^ carry_p;
            carry = ((data_p & carry_p) << 1);
        }
        return data;
    }
    int Sum_Solution (int n) {
        int sum = n;
        n > 0 && (sum += Sum_Solution(n - 1));
        return sum;
    }
    int LastRemaining_Solution (int n, int m) {
        // note: winner in (n - 1) is winner is n.
        if (n == 0 || m == 0) return -1;
        int sum = 0;
        for (int i = 2; i <= n; i ++) {
            sum = (sum + m % i) % i;
        }
        return sum;
    }
    bool IsContinuous (vector<int> numbers) {
        if (numbers.size() == 0) return false;
        sort (numbers.begin(), numbers.end());
        int gap = 0;
        int zero_count = (numbers[numbers.size() - 1] == 0);
        for (int i = 1; i < numbers.size(); i ++) {
            if (numbers[i - 1] == 0) zero_count ++;
            else if (numbers[i - 1] != 0 && numbers[i - 1] == numbers[i]) return false;
            else gap += numbers[i] - numbers[i - 1] - 1;
        }
        cout << gap << " " << zero_count << endl;
        if (gap <= zero_count) return true;
        return false;
    }
    string ReverseSentence (string str) {
        if (str.length() == 0) return str;
        vector<string> v;
        string p_str;
        string result;
        for (int i = 0; i < str.length(); i ++) {
            if (str[i] != ' ') p_str += str[i];
            else if (str[i] == ' ') {
                v.push_back(p_str);
                p_str.clear();
            }
        }
        v.push_back(p_str);
        for (int i = v.size() - 1; i > 0; i --) {
            result += v[i];
            result += " ";
        }
        result += v[0];
        return result;
    }
    string LeftRotateString (string str, int n) {
        if (str.length() == 0) return str;
        int n_real = n % str.length();
        string result;
        for (int i = n_real; i < str.length(); i ++) {
            result += str[i];
        }
        for (int i = 0; i < n_real; i ++) {
            result += str[i];
        }
        return result;
    }
    vector<int> FindNumbersWithSum (vector<int> array, int sum) {
        vector<int> result;
        int left = 0, right = array.size() - 1;
        while (right > left) {
            if (array[left] + array[right] > sum) right --;
            else if (array[left] + array[right] < sum) left ++;
            else {
                result.push_back(array[left]);
                result.push_back(array[right]);
                break;
            }
        }
        return result;
    }
    vector<vector<int>> FindContinuousSequence (int num) {
        int pos1 = 1, pos2 = 2;
        vector<vector<int>> result;
        while (pos1 <= (num / 2 + 1) || pos2 <= (num / 2 + 1)) {
            int sum = 0;
            for (int i = pos1; i <= pos2; i ++) sum += i;
            if (sum < num) pos2 ++;
            else if (sum > num) pos1 ++;
            else {
                vector<int> r;
                for (int i = pos1; i <= pos2; i ++) r.push_back(i);
                result.push_back(r);
                pos1 ++;
                pos2 ++;
            }
        }
        return result;
    }
    void FindNumsAppearOnce (vector<int> data, int *num1, int *num2) {
        set<int> s;
        if (data.size() < 2) return;
        for (int i = 0; i < data.size(); i ++) {
            if (s.count(data[i])) s.erase(data[i]);
            else s.insert(data[i]);
        }
        *num1 = *s.begin();
        *num2 = *(++s.begin());
    }
    bool IsBalanced_Solution (TreeNode *pRoot) {
        if (pRoot == NULL) return true;
        bool balanced1 = IsBalanced_Solution(pRoot -> left);
        bool balanced2 = IsBalanced_Solution(pRoot -> right);
        int depth1 = TreeDepth(pRoot -> left);
        int depth2 = TreeDepth(pRoot -> right);
        bool balanced3 = true;
        if (depth1 - depth2 > 1 || depth2 - depth1 > 1) balanced3 = false;
        return balanced1 && balanced2 && balanced3;
    }

    int TreeDepth (TreeNode *pRoot) {
        return TreeDepthHelper(pRoot, 0);
    }
    int TreeDepthHelper (TreeNode *pRoot, int depth) {
        if (pRoot == NULL) return depth;
        int ld = TreeDepthHelper(pRoot -> left, depth + 1);
        int lr = TreeDepthHelper(pRoot -> right, depth + 1);
        return ld > lr ? ld : lr;
    }
    int GetNumberOfK (vector<int> data, int k) {
        auto resultPair = equal_range (data.begin(), data.end(), k);
        return resultPair.second - resultPair.first;
    }
    ListNode *FindFirstCommonNode (ListNode *pHead1, ListNode *pHead2) {
        ListNode *p1 = pHead1, *p2 = pHead2;
        bool sign = false;
        if (pHead1 == NULL || pHead2 == NULL) return NULL;
        while (p1 != NULL && p2 != NULL) {
            if (p1 == p2) break;
            p1 = p1 -> next;
            p2 = p2 -> next;
            if (p1 == NULL) {
                if (sign) return NULL;
                p1 = pHead2;
                sign = true;
            }
            if (p2 == NULL) p2 = pHead1;
        }
        return p1;
    }
    int InversePairs (vector<int> data) {
        int result = InversePairsHelper (data, 0, data.size() - 1);
        return result % 1000000007;
    }
    int InversePairsHelper (vector<int>& data, int start, int end) {
        if (start != end) {
            int p1 = InversePairsHelper (data, start, (start + end) / 2) % 1000000007;
            int p2 = InversePairsHelper (data, (start + end) / 2 + 1, end) % 1000000007;
            int copy[end - start + 1];
            int t1 = (start + end) / 2, t2 = end, t3 = end - start;
            int p = 0;
            while (t1 >= start && t2 >= (start + end) / 2 + 1) {
                if (data[t1] > data[t2]) {
                    copy[t3--] = data[t1--];
                    p += t2 - (start + end) / 2;
                    if (p > 1000000007) p %= 1000000007;
                } else {
                    copy[t3--] = data[t2--];
                }
            }
            while (t1 >= start) copy[t3--] = data[t1--];
            while (t2 >= (start + end) / 2 + 1) copy[t3--] = data[t2--];
            for (int i = 0; i < end - start + 1; i ++) {
                data[start + i] = copy[i];
            }
            return (p1 + p2 + p);
        }
        else if (start == end) return 0;
    }
    int FirstNotRepeatingChar (string str) {
        int hashMap_small [26];
        int firstPos_small [26];
        int hashMap_big [26];
        int firstPos_big [26];
        for (int i = 0; i < 26; i ++) {
            hashMap_small[i] = 0;
            hashMap_big[i] = 0;
            firstPos_small[i] = -1;
            firstPos_big[i] = -1;
        }
        for (int i = 0; i < str.length(); i ++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                hashMap_small[str[i] - 'a'] += 1;
                firstPos_small[str[i] - 'a'] = firstPos_small[str[i] - 'a'] == -1 ? i : firstPos_small[str[i] - 'a'];
            }
            else {
                hashMap_big[str[i] - 'A'] += 1;
                firstPos_big[str[i] - 'A'] = firstPos_big[str[i] - 'A'] == -1 ? i : firstPos_big[str[i] - 'A'];
            }
        }
        int result = -1;
        for (int i = 0; i < 26; i ++) {
            if (hashMap_small[i] == 1) result = result == -1 ? firstPos_small[i] : std::min(result, firstPos_small[i]);
            if (hashMap_big[i] == 1) result = result == -1 ? firstPos_big[i] : std::min(result, firstPos_big[i]);
        }
        return result;
    }
    int GetUglyNumber_Solution (int index) {
        if (index < 7) return index;
        int res[index];
        res[0] = 1;
        int t0 = 0, t1 = 0, t2 = 0;
        for (int i = 1; i < index; i ++) {
            res[i] = std::min (res[t0] * 2, std::min (res[t1] * 3, res[t2] * 5));
            if (res[i] == res[t0] * 2) t0 ++;
            if (res[i] == res[t1] * 3) t1 ++;
            if (res[i] == res[t2] * 5) t2 ++;
        }
        return res[index - 1];
    }
    string PrintMinNumber (vector<int> numbers) {
        vector<string> numbers_s;
        for (int i = 0; i < numbers.size(); i ++) {
            numbers_s.push_back(to_string(numbers[i]));
        }
        sort (numbers_s.begin(), numbers_s.end(), mycompare);
        // sort (numbers_s.begin(), numbers_s.end());
        string result;
        for (int i = 0; i < numbers_s.size(); i ++) {
            result += numbers_s[i];
        }
        return result;
    }
    int NumberOf1Between1AndN_Solution (int n) {
        int sum = 0;
        if (n < 1) return 0;
        for (int i = 1; i <= n; i ++) {
            int tmp = i;
            while (tmp > 0) {
                if (tmp % 10 == 1) sum ++;
                tmp /= 10;
            }
        }
        return sum;
    }
    int FindGreatestSumOfSubArray (vector<int> array) {
        int result = 0;
        int pre_sum = 0;
        if (array.size() == 0) return 0;
        result = array[0];
        for (int i = 0; i < array.size(); i ++) {
            if (pre_sum + array[i] > 0) {
                pre_sum += array[i];
                result = result > pre_sum ? result : pre_sum;
            }
            else {
                pre_sum = 0;
                result = result > array[i] ? result : array[i];
            }
        }
        return result;
    }
    vector<int> GetLeastNumbers_Solution (vector<int> input, int k) {
        vector<int> result;
        if (k > input.size()) return result;
        for (int i = input.size(); i > 0; i --) {
            for (int j = i / 2 - 1; j >= 0; j --) {
                adjustHeap (input, j, i);
            }
            int tmp = input[0];
            input[0] = input[i - 1];
            input[i - 1] = tmp;
        }
        for (int i = 0; i < k; i ++) {
            result.push_back(input[input.size() - i - 1]);
        }
        return result;
    }
    void adjustHeap (vector<int>& input, int father, int length) {
        int child1 = father * 2 + 1;
        int child2 = child1 + 1;
        // cout << child1 << " " << child2 << " " << length << endl;
        if (child2 >= length) {
            if (input[child1] < input[father]) {
                int tmp = input[child1];
                input[child1] = input[father];
                input[father] = tmp;
            }
        }
        else {
            if (input[child1] <= input[child2] && input[child1] < input[father]) {
                int tmp = input[child1];
                input[child1] = input[father];
                input[father] = tmp;
            }
            else if (input[child2] < input[child1] && input[child2] < input[father]) {
                int tmp = input[child2];
                input[child2] = input[father];
                input[father] = tmp;
            }
        }
    }
    int MoreThanHalfNum_Solution (vector<int> numbers) {
        int hashArray [10];
        for (int i = 0; i < 10; i ++) {
            hashArray[i] = 0;
        }
        for (int i = 0; i < numbers.size(); i ++) {
            hashArray[numbers[i]] ++;
        }
        for (int i = 0; i < 10; i ++) {
            if (hashArray[i] > numbers.size() / 2) return i;
        }
        return 0;
    }
    vector<string> Permutation (string str) {
        sort (str.begin(), str.end());
        if (str.length() == 0) return permutationResult;
        PermutationHelper (str, 0);
        sort (permutationResult.begin(), permutationResult.end());
        return permutationResult;
    }
    void PermutationHelper (string str, int begin) {
        if (begin == str.length()) {
            permutationResult.push_back (str);
            return;
        }
        for (int i = begin; i < str.length(); i ++) {
            if (i != begin && str[begin] == str[i]) continue;
            swap (str[begin], str[i]);
            PermutationHelper (str, begin + 1);
            swap (str[begin], str[i]);
        }
    }
    TreeNode *Convert (TreeNode *pRootOfTree) {
        TreeNode *pre = NULL;
        if (pRootOfTree == NULL) return NULL;
        ConvertHelper (pRootOfTree, pre);

        TreeNode *res = pRootOfTree;
        while (res -> left != NULL) res = res -> left;
        return res;
    }
    void ConvertHelper (TreeNode *root, TreeNode *&pre) {
        if (root == NULL) return;
        ConvertHelper (root -> left, pre);

        root -> left = pre;
        if (pre) pre -> right = root;
        pre = root;

        ConvertHelper (root -> right, pre);
    }
    RandomListNode *Clone (RandomListNode *pHead) {
        if (pHead == NULL) return NULL;
        // step 1: clone node
        RandomListNode *cur = pHead;
        while (cur != NULL) {
            RandomListNode *tmp = cur -> next;
            cur -> next = new RandomListNode(cur -> label);
            cur -> next -> next = tmp;
            cur = tmp;
        }
        // step 2: set random
        cur = pHead;
        while (cur != NULL) {
            if (cur -> random != NULL) {
                cur -> next -> random = cur -> random -> next;
            } else {
                cur -> next -> random = NULL;
            }
            cur = cur -> next -> next;
        }
        // step 3: split list
        RandomListNode *new_pHead = pHead -> next;
        RandomListNode *cur_old = pHead;
        RandomListNode *cur_new = new_pHead;
        while (cur_new -> next != NULL) {
            cur_old -> next = cur_old -> next -> next;
            cur_new -> next = cur_new -> next -> next;
            cur_old = cur_old -> next;
            cur_new = cur_new -> next;
        }
        cur_old -> next = NULL;

        return new_pHead;
    }
    vector<vector<int>> FindPath (TreeNode *root, int expectNumber) {
        vector<vector<int>> result;
        if (expectNumber <= 0) return result;
        if (root -> left == NULL && root -> right == NULL && root -> val == expectNumber) {
            vector<int> t;
            t.push_back(root -> val);
            result.push_back(t);
        }
        else {
            if (root -> left != NULL) {
                vector<vector<int>> r1 = FindPath (root -> left, expectNumber - root -> val);
                for (int i = 0; i < r1.size(); i ++) {
                    // r1[i].push_back(root -> val);
                    r1[i].insert (r1[i].begin(), root -> val);
                    result.push_back (r1[i]);
                }
            }
            if (root -> right != NULL) {
                vector<vector<int>> r2 = FindPath (root -> right, expectNumber - root -> val);
                for (int i = 0; i < r2.size(); i ++) {
                    // r2[i].push_back(root -> val);
                    r2[i].insert (r2[i].begin(), root -> val);
                    result.push_back (r2[i]);
                }
            }
        }
        return result;
    }
    bool VerifySquenceOfBST (vector<int> sequence) {
        vector<int> s1, s2;
        bool ch = false;
        if (sequence.size() == 0) return false;
        if (sequence.size() == 1) return true;
        for (int i = 0; i < sequence.size() - 1; i ++) {
            if (sequence[i] < sequence[sequence.size() - 1] && !ch) s1.push_back(sequence[i]);
            else if (sequence[i] < sequence[sequence.size() - 1] && ch) return false;
            else if (sequence[i] > sequence[sequence.size() - 1]) {
                s2.push_back(sequence[i]);
                ch = true;
            }
        }
        bool r1 = true;
        if (s1.size() != 0) r1 = VerifySquenceOfBST(s1);
        bool r2 = true;
        if (s2.size() != 0) r2 = VerifySquenceOfBST(s2);
        return r1 && r2;
    }
    vector<int> PrintFromTopToBottom (TreeNode *root) {
        queue<TreeNode *> q;
        vector<int> result;
        if (root == NULL) return result;
        q.push (root);
        while (!q.empty()) {
            result.push_back(q.front() -> val);
            if (q.front() -> left) q.push(q.front() -> left);
            if (q.front() -> right) q.push(q.front() -> right);
            q.pop();
        }
        return result;
    }
    bool IsPopOrder (vector<int> pushV, vector<int> popV) {
        stack<int> sp;
        int popV_pos = 0;
        if (pushV.size() != popV.size()) return false;
        if (pushV.size() == 0) return true;

        for (int i = 0; i < pushV.size(); i ++) {
            if (!sp.empty() && popV[popV_pos] == sp.top()) {
                sp.pop();
                sp.push(pushV[i]);
            }
            else if (pushV[i] != popV[popV_pos]) sp.push(pushV[i]);
            else popV_pos ++;
        }
        while (!sp.empty()) {
            if (sp.top() != popV[popV_pos ++]) return false;
            sp.pop();
        }
        return true;
    }
    void push (int value) {
        if (stack1.empty()) min_v = value;
        else min_v = min_v > value ? value : min_v;
        stack1.push(value);
    }
    void pop () {
        if (stack1.top() == min_v) {
            stack1.pop();
            if (!stack1.empty()) min_v = stack1.top();
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                min_v = min_v > stack1.top() ? stack1.top() : min_v;
                stack1.pop();
            }
            while (!stack2.empty()) {
                stack1.push(stack2.top());
                stack2.pop();
            }
        }
        else stack1.pop();
    }
    int top () {
        return stack1.top();
    }
    int min () {
        return min_v;
    }
    vector<int> printMatrix (vector<vector<int>> matrix) {
        vector<int> result;
        int x = 0, y = -1;
        if (matrix.size() == 0) return result;
        if (matrix[0].size() == 0) return result;
        bool visited_x [matrix.size()];
        bool visited_y [matrix[0].size()];
        for (int i = 0; i < matrix.size(); i ++) visited_x[i] = false;
        for (int i = 0; i < matrix[0].size(); i ++) visited_y[i] = false;

        while (!visited_x[x]) {
            for (y += 1; y < matrix[0].size() && visited_y[y] == false; y ++) {
                result.push_back (matrix[x][y]);
            }
            visited_x[x] = true;
            y --;
            for (x += 1; x < matrix.size() && visited_x[x] == false && visited_y[y] == false; x ++) {
                result.push_back (matrix[x][y]);
            }
            visited_y[y] = true;
            x --;
            for (y -= 1; y >= 0 && visited_y[y] == false && visited_x[x] == false; y --) {
                result.push_back (matrix[x][y]);
            }
            visited_x[x] = true;
            y ++;
            for (x -= 1; x >= 0 && visited_x[x] == false && visited_y[y] == false; x --) {
                result.push_back (matrix[x][y]);
            }
            visited_y[y] = true;
            x ++;
        }

        return result;
    }
    void Mirror (TreeNode *pRoot) {
        TreeNode *tmp;
        if (pRoot == NULL) return;
        tmp = pRoot -> left;
        pRoot -> left = pRoot -> right;
        pRoot -> right = tmp;
        Mirror (pRoot -> left);
        Mirror (pRoot -> right);
    }
    bool IsSubtree (TreeNode *pRoot1, TreeNode *pRoot2) {
        if (pRoot2 == NULL) return true;
        if (pRoot1 == NULL) return false;
        if (pRoot1 -> val == pRoot2 -> val) {
            return IsSubtree (pRoot1 -> left, pRoot2 -> left) && IsSubtree (pRoot1 -> right, pRoot2 -> right);
        }
        return false;
    }
    bool HasSubtree (TreeNode *pRoot1, TreeNode *pRoot2) {
        if (pRoot2 == NULL || pRoot1 == NULL) return false;
        return IsSubtree (pRoot1, pRoot2) || HasSubtree (pRoot1 -> left, pRoot2) || HasSubtree (pRoot1 -> right, pRoot2);
    }
    ListNode* Merge (ListNode *pHead1, ListNode *pHead2) {
        ListNode *head, *cuNodeHead, *cuNode1, *cuNode2;
        if (pHead1 == NULL) return pHead2;
        if (pHead2 == NULL) return pHead1;
        head = new ListNode (0);
        cuNodeHead = head;
        cuNode1 = pHead1;
        cuNode2 = pHead2;
        while (cuNode1 != NULL && cuNode2 != NULL) {
            if (cuNode1 -> val < cuNode2 -> val) {
                cuNodeHead -> next = cuNode1;
                cuNode1 = cuNode1 -> next;
                cuNodeHead = cuNodeHead -> next;
            }
            else {
                cuNodeHead -> next = cuNode2;
                cuNode2 = cuNode2 -> next;
                cuNodeHead = cuNodeHead -> next;
            }
        }
        if (cuNode1 == NULL) cuNodeHead -> next = cuNode2;
        else if (cuNode2 == NULL) cuNodeHead -> next = cuNode1;
        return head -> next;
    }
    ListNode* ReverseList (ListNode *pHead) {
        ListNode *preNode, *nextNode, *cuNode;
        if (pHead == NULL) return NULL;
        preNode = NULL;
        cuNode = pHead;
        nextNode = pHead -> next;
        while (cuNode != NULL) {
            cuNode -> next = preNode;
            preNode = cuNode;
            cuNode = nextNode;
            nextNode = nextNode == NULL ? NULL : nextNode -> next;
        }
        return preNode;
    }
    ListNode* FindKthToTail (ListNode *pListHead, unsigned int k) {
        ListNode *tmp = pListHead;
        int nodeCount = 0;
        while (tmp != NULL) {
            nodeCount ++;
            tmp = tmp -> next;
        }
        if (nodeCount < k) return NULL;
        tmp = pListHead;
        for (int i = 0; i < nodeCount - k; i ++) tmp = tmp -> next;
        return tmp;
    }
    void reOrderArray (vector<int> &array) {
        vector<int> tmp_odd, tmp_even;
        for (int i = 0; i < array.size(); i ++) {
            if (array[i] % 2) tmp_odd.push_back (array[i]);
            else tmp_even.push_back (array[i]);
        }
        for (int i = 0; i < tmp_odd.size(); i ++) array[i] = tmp_odd[i];
        for (int i = 0; i < tmp_even.size(); i ++) array[tmp_odd.size() + i] = tmp_even[i];
    }
    double Power (double base, int exponent) {
        double r = 1.0;
        if (base == 0) return 0;
        if (exponent == 0) return 1;
        if (exponent > 0) {
            for (int i = 0; i < exponent; i ++) r *= base;
        }
        else {
            for (int i = 0; i < 0 - exponent; i ++) r /= base;
        }
        return r;
    }
    int NumberOf1 (int n) {
        int r = 0;
        for (int i = 0; i < 32; i ++) {
            if (((n >> i) & 1) == 1) r ++;
        }
        return r;
    }
    int rectCover (int number) {
        int r[number + 1];
        r[0] = 0;
        r[1] = 1;
        r[2] = 2;
        for (int i = 3; i <= number; i ++) r[i] = r[i - 1] + r[i - 2];
        return r[number];
    }
    int jumpFloor (int number) {
        int r = 1;

        if (number == 1) return 1;
        else if (number == 2) return 2;

        for (int i = 1; i < number; i ++) r += jumpFloor(i);
        return r;
    }
    int Fibonacci (int n) {
        static int r[40];
        if (n == 0) return 0;
        else if (n == 1) return 1;
        else if (r[n] != 0) return r[n];
        else {
            r[n] = Fibonacci (n - 1) + Fibonacci (n - 2);
            return r[n];
        }
    }
    int minNumberInRotateArray (vector<int> rotateArray) {
        if (rotateArray.size() == 0) return 0;
        int st = 0;
        int ed = rotateArray.size() - 1;

        for (st = 0; st < rotateArray.size(); st ++) {
            ed = rotateArray.size() - st - 1;
            if (st == ed || rotateArray[st] < rotateArray[ed]) break;
        }
        return rotateArray[st] > rotateArray[ed + 1] ? rotateArray[ed + 1] : rotateArray[st];
    }
    /*
    void push (int node) {
        stack1.push (node);
    }
    int pop () {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push (stack1.top());
                stack1.pop ();
            }
        }
        int top = stack2.top();
        
        stack2.pop ();
        return top;
    }
    */

    TreeNode *reConstructBinaryTree (vector<int> pre, vector<int> vin) {
        // first reconstruct root
        // second reconstruct left
        // final reconstruct right
        vector<int> pre_left, pre_right;
        vector<int> vin_left, vin_right;

        if (pre.size() <= 0 || vin.size() <= 0) return NULL;

        TreeNode *root = new TreeNode(pre[0]);

        bool direction_ch = false; // false is left
        for (int i = 0; i < vin.size(); i ++) {
            if (!direction_ch && vin[i] != pre[0]) vin_left.push_back (vin[i]);
            else if (vin[i] == pre[0]) direction_ch = true;
            else if (direction_ch) vin_right.push_back (vin[i]);
        }
        for (int i = 0; i < vin_left.size(); i ++) pre_left.push_back (pre[i + 1]);
        for (int i = 0; i < vin_right.size(); i ++) pre_right.push_back (pre[i + 1 + vin_left.size()]);

/*
        cout << pre_left.size () << endl;
        cout << pre_right.size () << endl;
        cout << vin_left.size () << endl;
        cout << vin_right.size () << endl;
*/

        root -> left = reConstructBinaryTree (pre_left, vin_left);
        root -> right = reConstructBinaryTree (pre_right, vin_right);

        return root;
    }
    vector<int> printListFromTailToHead (ListNode *head) {
        vector<int> head_to_tail;
        vector<int> tail_to_head;
        while (head != NULL) {
            head_to_tail.push_back (head -> val);
            head = head -> next;
        }
        for (int i = head_to_tail.size() - 1; i >= 0; i --) {
            tail_to_head.push_back (head_to_tail[i]);
        }
        return tail_to_head;
    }
    void replaceSpace (char *str, int length) {
        if (length <= 0) return;
        char ori_str [length];
        for (int i = 0; i < length; i ++) {
            ori_str[i] = str[i];
        }
        int str_pos = 0;
        for (int i = 0; i < length; i ++) {
            if (ori_str[i] == ' ') {
                str[str_pos ++] = '%';
                str[str_pos ++] = '2';
                str[str_pos ++] = '0';
            } else {
                str[str_pos ++] = ori_str[i];
            }
        }
    }
    bool Find (int target, vector<vector<int>> array) {
        int lines = array.size();

        if (lines == 0) return false;

        int columns = array[0].size();

        if (columns == 0) return false;

        int line = 0;
        int column = columns - 1;

        while (0 <= line && line < lines && 0 <= column && column < columns) {
            if (array[line][column] == target) return true;
            else if (array[line][column] > target) {
                column -= 1;
            }
            else {
                line += 1;
            }
        }
        return false;
    }
    void traverseTree (TreeNode *root) {
        if (root == NULL) return;
        cout << root -> val << endl;
        traverseTree (root -> left);
        traverseTree (root -> right);
    }
};

int main (int argc, char **argv) {
    Solution s;
    int r = s.cutRope(15);
    cout << r << endl;
    return 0;
}