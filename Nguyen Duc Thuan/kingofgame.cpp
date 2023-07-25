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

const ll LINF = 1e18;
const int INF = 1e9;
const int N = 1e6+1;

int n, m, p, d;
vector<ii> graph[N];
ll dp[N];

int main() {
  setIO("input");

  int t; 
  cin >> t;
  
  while (t--) {
    cin >> n >> m >> p >> d;

    foru(i, 1, n) {
      dp[i] = -LINF;
      graph[i].clear();
    }

    foru(i, 1, m) {
      int u, v, l;
      cin >> l >> u >> v;
      graph[u].emplace_back(v, l);
    }

    dp[1] = p;

    foru(i, 1, n) {
      ll cur = dp[i];
      fore(e, graph[i]) {
        ll nxt;
        if (cur > e.se) nxt = cur + e.se/2;
        else nxt = cur/2;
        dp[e.fi] = max(dp[e.fi], nxt);
      }
    }

    if (dp[n] < d) cout << "Impossible\n";
    else cout << dp[n] << "\n";
  }
}