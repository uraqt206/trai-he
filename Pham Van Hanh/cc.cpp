#include<bits/stdc++.h>
#define X first
#define Y second
#define all(x) begin(x), end(x)
#define FOR(i, a, b) for(int i = (a); i <= (b); i++)
#define FORD(i, b, a) for(int i = (b); i >= (a); i--)
#define REP(i, a, b) for (int i = (a); i < (b); i++)
#define mxx max_element
#define mnn min_element
#define SQR(x) (1LL * (x) * (x))
#define MASK(i) (1LL << (i))
#define Point Vector
#define left Left
#define right Right
#define div Div
#pragma GCC optimize(" unroll-loops")
#pragma gcc optimize("Ofast")
#pragma GCC optimization("Ofast")
#pragma optimize(Ofast)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
typedef pair<db, db> pdb;
typedef pair<ld, ld> pld;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<ll, ll> pll;
typedef pair<ll, pll> plll;
typedef pair<ll, int> pli;
typedef pair<ll, pii> plii;

template<class A, class B>
    bool maximize(A& x, B y) {
        if (x < y) return x = y, true; else return false;
    }
template<class A, class B>
    bool minimize(A& x, B y) {
        if (x > y) return x = y, true; else return false;
    }
/* END OF TEMPLATE */

const int N = 1e6 + 7;
const int mod = 998244353;


int n,  pos[N], t[N];


void add(int& x, int y) {
    if ((x+=y) >= mod) x-=mod;
}

namespace sub1 {
    int dp[23][23][23];
    int dq(int x, int y, int z) {
        if (x > n) return 1;
        int& res = dp[x][y][z];
        if (res > 0) return res;
        // dien dc tu y -> 1, z -> n
        if (y > 0 && t[y] == x) {
            add(res, dq(x + 1, y - 1, z));
        }
        if (z <= n && t[z] == x) {
            add(res, dq(x + 1, y, z + 1));
        }
        if (y > 0 && t[y] == 0) add(res, dq(x + 1, y - 1, z));
        if (z <= n && t[z] == 0) add(res, dq(x + 1, y, z + 1));
    //    cout<<x<<" "<<y<<" "<<z<<" | "<<res<<"\n";
        return res;
    }
    void Process() {
        int res = 0;
        FOR(i, 1, n)
            if (t[i] == 0) add(res, dq(2, i - 1, i + 1)); else
            if (t[i] == 1) add(res, dq(2, i - 1, i + 1));
        cout<<res;
    }
}

namespace sub5 {
    const int N = 5007;
    int dp[N][N];
    void Process() {
        FORD(x, n + 1, 1)
            FOR(y, 0, n) {
                int& res = dp[x][y];
                int z = x + y;
                if (z > n + 1) break;
                if (x > n) {
                    res = 1;
                    continue;
                }
                if (y > 0 && t[y] == x) add(res, dp[x + 1][y - 1]);
                if (z <= n && t[z] == x) add(res, dp[x + 1][y]);
                if (y > 0 && t[y] == 0) add(res, dp[x + 1][y - 1]);
                if (z <= n && t[z] == 0) add(res, dp[x + 1][y]);
            }
        int res = 0;
        FOR(i, 1, n)
            if (t[i] == 0) add(res, dp[2][i - 1]); else
            if (t[i] == 1) add(res, dp[2][i - 1]);
        cout<<res;
    }
}

int main() {
    freopen("input.inp", "r", stdin);
    freopen("input.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    FOR(i, 0, n) pos[i] = 0;
    FOR(i, 1, n) {
        int x;
        cin>>x;
        t[i] = x;
    }
    if (n > 5000 && *mxx(t + 1, t + 1 + n) > 0) return cout<<0, 0;
    if (n <= 20) {
        sub1::Process();
        return 0;
    }
    if (n <= 5000) sub5::Process(); else {
        int res = 1;
        FOR(i, 1, n - 1) res = res * 2 % mod;
        cout<<res;
    }
    return 0;
}
