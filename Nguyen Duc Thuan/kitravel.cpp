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
const int N = 10100;
int n, k, root, sub[N];
ll ans = LINF;

vector<ll> dp[N][2];
vector<ii> graph[N];

void minimize(ll &a, ll b) {
  if (a > b) { a = b;}
}

void dfs(int u, int p) {
  sub[u] = 1;
  foru(r, 0, 1) dp[u][r].resize(2, INF);
  dp[u][0][1] = dp[u][1][1] = 0;

  for(auto e : graph[u]) if (e.fi != p) {
    int v = e.fi, w = e.se;
    dfs(v, u);
    dp[u][0].resize(sub[u]+sub[v]+1, INF);
    dp[u][1].resize(sub[u]+sub[v]+1, INF);
    ford(i, sub[u], 0) {
      ford(j, sub[v], 1) {
        minimize(dp[u][0][i+j], dp[u][0][i] + dp[v][0][j] + w*2);
        minimize(dp[u][1][i+j], dp[u][0][i] + dp[v][1][j] + w);
        minimize(dp[u][1][i+j], dp[u][1][i] + dp[v][0][j] + w*2);
      }
    }
    sub[u] += sub[v];
  }
}

int main() {
  setIO("input");

  cin >> n >> k >> root;

  foru(i, 2, n) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }

  dfs(root, root);
  cout << dp[root][1][k];
}