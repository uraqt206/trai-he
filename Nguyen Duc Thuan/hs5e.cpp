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

int n, m, a, b, vi[N];
vector<int> graph[N];
vector<pair<int, ii>> at, that;

void dfs(int u) {
  vi[u] = 1;
  if (vi[b]) return;
  for(int v : graph[u]) if (!vi[v]) {
    dfs(v);
  }
}

bool check() {
  foru(i, 1, n) {
    graph[i].clear();
    vi[i] = 0;
  }
  
  fore(e, that) {
    graph[e.se.fi].push_back(e.se.se);
  }

  dfs(a);
  return vi[b];
}

int main() {
  setIO("input");

  cin >> n >> m >> a >> b;

  vector<pair<int, ii>> at;

  foru(i, 1, m) {
    int u, v, w;
    cin >> u >> v >> w;
    at.push_back({w, {u, v}});
  }

  that = at;
  if (!check()) {
    cout << "-1";
    return 0;
  }

  int ans = 0;
  ford(i, 29, 0) {
    that.clear();
    fore(x, at) if ((x.fi >> i & 1) == 0) {
      that.emplace_back(x);
    }
    if (check()) 
      at = that;
    else
      ans += (1 << i);
  }

  cout << ans;
}