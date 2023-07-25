#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
 
#define foru(i, l, r) for(int i=(l); i<=(r); ++i)
#define ford(i, l, r) for(int i=(l); i>=(r); --i)
#define fore(x, v) for(auto &x : v)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second
 
void setIO(string name="") {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  if (!name.empty()) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

const ll LINF = 1e18;
const int INF = 1e9;
const int N = 5e5+5;
const int MOD = 998244353;

int n, k, m;
int lst[N], pw[N], cnt[N];
vector<ii> you[30];
int init[30][N], dp[N], pre[N];

int solve(int z) {
  foru(i, 1, n) lst[i] = 0;
  fore(e, you[z]) { lst[e.se] = max(lst[e.se], e.fi); }
  foru(i, 1, n+1) lst[i] = max(lst[i], lst[i-1]);

  dp[0] = pre[0] = 1;
  foru(i, 1, n+1) {
    pre[i] = pre[i-1];
    if (init[z][i] >= 1) continue;
    int nax = lst[i-1];
    if (nax == 0) dp[i] = pre[i-1];
    else dp[i] = (pre[i-1] - pre[nax-1] + MOD) % MOD;
    pre[i] = (pre[i] + dp[i]) % MOD;
  }
  return dp[n+1];
}

int main() {
  setIO("input");

  cin >> n >> k >> m;

  foru(i, 1, m) {
    int l, r, x;
    cin >> l >> r >> x;
    foru(j, 0, k-1) {
      if (x >> j & 1) init[j][l] += 1, init[j][r+1] -= 1;
      else you[j].emplace_back(l, r);
    }
  }

  foru(i, 0, k-1)
    foru(j, 1, n)
      init[i][j] += init[i][j-1];

  // cout << solve(1);
  ll ans = 1; 
  foru(i, 0, k-1) {
    (ans *= solve(i)) %= MOD;
    // cout << solve(i) << "\n";
  }

  cout << ans;
}