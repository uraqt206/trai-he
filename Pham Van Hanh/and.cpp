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

const int N = 3e5+5, LOG = 29;
int n, q, a[N], dp[N][LOG+1], nxt[LOG+1];

int main() {
  setIO("input");
  cin >> n >> q;

  foru(i, 1, n) {
    cin >> a[i];
  }

  memset(dp, 0x3f, sizeof(dp));
  fill(nxt, nxt+LOG+1, n+1);

  ford(i, n, 1) {
    foru(j, 0, LOG) if (a[i] >> j & 1) {
      dp[i][j] = i;
      foru(k, 0, LOG) dp[i][k] = min(dp[i][k], dp[nxt[j]][k]);
      nxt[j] = i;
    }
  }

  foru(i, 1, q) {
    int u, v;
    cin >> u >> v;  
    bool ans = 0;
    foru(j, 0, LOG) if (a[v] >> j & 1) ans |= (dp[u][j] <= v);
    cout << (ans ? "Yes\n" : "No\n");
  }
}