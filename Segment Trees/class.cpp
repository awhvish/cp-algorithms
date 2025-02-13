#include <iostream>
#include<vector>
#include<climits>

#define ll long long
using namespace std;

class SGTree {
private:
    vector<int> seg;
    vector<int> a;
    int n;

public:
    SGTree(vector<int>& arr) {
        n = arr.size();
        a = arr;
        seg.resize(4 * n + 1);
        build(0, 0, n - 1);
    }

    void build(int ind, int low, int high) {
        if (low == high) {
            seg[ind] = a[low];
            return;
        }
        int mid = (high + low) / 2;
        build(2 * ind + 1, low, mid);
        build(2 * ind + 2, mid + 1, high);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r) {
        // No overlap
        if (high < l || low > r) {
            return INT_MAX;
        }
        // Complete overlap
        if (low >= l && high <= r) {
            return seg[ind];
        }
        // Partial overlap
        int mid = (high + low) / 2;
        int left = query(2 * ind + 1, low, mid, l, r);
        int right = query(2 * ind + 2, mid + 1, high, l, r);
        return min(left, right);
    }

    void update(int ind, int low, int high, int pos, int val) {
        if (low == high) {
            seg[ind] = val;
            return;
        }
        int mid = (high + low) / 2;
        if (pos <= mid)
            update(2 * ind + 1, low, mid, pos, val);
        else
            update(2 * ind + 2, mid + 1, high, pos, val);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};
