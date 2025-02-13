#include <iostream>
#include<vector>
#include<climits>
#include<cmath>

#define ll long long
using namespace std;

class SGTree {
private:
    vector<int> seg;
    vector<int> a;
    int n;
public:
    SGTree(vector<int>& arr, int initial) {
        n = arr.size();
        a = arr;
        seg.resize(4 * n + 1);
        build(0, 0, n - 1, initial);
    }

    void build(int ind, int low, int high, int orr) {
        if (low == high) {
            seg[ind] = a[low];
            return;
        }
        int mid = (high + low) / 2;
        build(2 * ind + 1, low, mid, !orr);
        build(2 * ind + 2, mid + 1, high, !orr);

        if (orr == 1) seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
        else seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];

    }

    int query(int ind, int low, int high, int l, int r, int orr) {
        // No overlap
        if (high < l || low > r) {
            return 0;
        }
        // Complete overlap
        if (low >= l && high <= r) {
            return seg[ind];
        }
        // Partial overlap
        int mid = (high + low) / 2;
        int left = query(2 * ind + 1, low, mid, l, r, !orr);
        int right = query(2 * ind + 2, mid + 1, high, l, r, !orr);

        return (orr == 1) ? left | right : left ^ right;
    }

    void update(int ind, int low, int high, int pos, int val, int orr) {
        if (low == high) {
            seg[ind] = val;
            return;
        }
        int mid = (high + low) / 2;
        if (pos <= mid)
            update(2 * ind + 1, low, mid, pos, val, !orr);
        else
            update(2 * ind + 2, mid + 1, high, pos, val, !orr);
        if (orr == 1) seg[ind] = seg[2 * ind + 1] | seg[2 * ind + 2];
        else seg[ind] = seg[2 * ind + 1] ^ seg[2 * ind + 2];
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    int e = pow(2, n);

    vector<int> v(e);

    for (int i = 0;i < e;i++) {
        cin >> v[i];
    }

    SGTree tree(v, n % 2);

    int p, b;

    while (m--) {
        cin >> p >> b;
        p--;

        tree.update(0, 0, e - 1, p, b, n % 2);
        cout << tree.query(0, 0, e - 1, 0, e - 1, n % 2) << endl;
    }

    return 0;
}
