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
  if (fopen((name + ".inp").c_str(), "r")) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

const int MOD = 1e9+7;
const int N = 1e6+5;
int n, m, dp[N], sub[N], f[N], inv[N];
vector<int> graph[N];

int exp(int n, int k) {
  if (k == 0) return 1;
  int tmp = exp(n, k/2);
  tmp = 1LL * tmp * tmp % MOD;
  if (k & 1) tmp = 1LL * tmp * n % MOD;
  return tmp;
}
 
void prep() {
  f[0] = inv[0] = 1;
  foru(i, 1, n+1) {
    f[i] = 1LL * f[i-1] * i % MOD;
    inv[i] = exp(f[i], MOD-2);
  }
}
 
int comb(int n, int k) {
  if (k < 0) return 0;
  int ans = f[n];
  ans = 1LL * ans * inv[k] % MOD;
  ans = 1LL * ans * inv[n-k] % MOD;
  return ans;
}

void dfs(int u) {
  sub[u] = 1;
  dp[u] = 1;

  for(int v : graph[u]) {
    dfs(v);
    sub[u] += sub[v];
  }

  int can = sub[u]-1;
  for(int v : graph[u]) {
    int tmp = comb(can, sub[v]);
    dp[u] = 1LL * dp[u] * tmp % MOD;
    dp[u] = 1LL * dp[u] * dp[v] % MOD;
    can -= sub[v];
  }
}

int main() {
  setIO("input");

  cin >> n >> m;
  prep();

  for(int i=1; i<=n; ++i)
    graph[i/m].push_back(i);

  if (m == 1) {
    cout << f[n];
    return 0;
  }

  dfs(0);
  cout << dp[0] << "\n";
  // foru(i, 0, n) cout << sub[i] << " ";
}

/*
*/