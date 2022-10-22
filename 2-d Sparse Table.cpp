#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
#define watch(x) cout << (#x) << " = " << (x) << endl

template<class T> bool ckmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool ckmin(T& a, const T& b) {
    return a > b ? a = b, 1 : 0;
}

template<typename T_vector>
void output_vector(const T_vector &v, bool add_one = false, int start = -1, int end = -1) {
    if (start < 0) start = 0;
    if (end < 0) end = int(v.size());
 
    for (int i = start; i < end; i++)
        cout << v[i] + (add_one ? 1 : 0) << (i < end - 1 ? ' ' : '\n');
}

void setIO(string name = "") { 
    ios_base::sync_with_stdio(0); cin.tie(0); 
    if(name.size()){
        freopen((name+".in").c_str(), "r", stdin);
        freopen((name+".out").c_str(), "w", stdout);
    }
}

/*
---------1---------2---------3---------4---------5---------6---------7---------
1234567890123456789012345678901234567890123456789012345678901234567890123456789
*/

const int mxN = 105;
const int mxM = 105;
const int LOG = 8;
int st[LOG][mxN][LOG][mxM];
int mat[mxN][mxM];

int validate(int x1, int y1, int x2, int y2) {
    int mn = 1e9+9;
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            ckmin(mn, mat[i][j]);
        }
    }
    return mn;
}

void solve() {
    //queries will be of the form x1, y1, x2, y2. This means we need to find the minimum of the subrectangle in those bounds.
    int n, m, q; cin >> n >> m >> q;
    for(int ir = 0; ir < n; ir++) {
        for(int ic = 0; ic < m; ic++) {
            cin >> mat[ir][ic];
            st[0][ir][0][ic] = mat[ir][ic];
        }

        for(int jc = 1; jc <= __lg(m+1); jc++) {
            for(int ic = 0; ic + (1<<jc) <= m; ic++) {
                st[0][ir][jc][ic] = min(st[0][ir][jc-1][ic], st[0][ir][jc-1][ic+(1<<(jc-1))]);
            }
        }
    }

    for(int jr = 1; jr <= __lg(n+1); jr++) {
        for(int ir = 0; ir + (1<<jr) <= n; ir++) {
            for(int jc = 0; jc <= __lg(m+1); jc++) {
                for(int ic = 0; ic + (1<<jc) <= m; ic++) {
                    st[jr][ir][jc][ic] = min(st[jr-1][ir][jc][ic], st[jr-1][ir+(1<<(jr-1))][jc][ic]);
                }
            }
        }
    }

    auto rmq = [&] (int x1, int y1, int x2, int y2) {
        int kr = __lg(x2 - x1 + 1);
        int kc = __lg(y2 - y1 + 1);
        int op1 = min(st[kr][x1][kc][y1], st[kr][x1][kc][y2 - (1<<kc) + 1]);
        int op2 = min(st[kr][x2 - (1<<kr) + 1][kc][y1], st[kr][x2 - (1<<kr) + 1][kc][y2 - (1<<kc) + 1]);
        return min(op1, op2);
    };

    while(q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        cout << (rmq(x1, y1, x2, y2) == validate(x1, y1, x2, y2) ? "SUCCESS" : "FAIL") << endl;
    }
}   

int main() {
    setIO();
    int t; cin >> t;
    while(t--) {
        solve();
    }
}
