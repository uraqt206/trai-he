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

using state = pair<ll, int>;
const ll LINF = 1e18;
const int N = 1e5+5, M = 2e5+5, K = 101;
priority_queue<state, vector<state>, greater<state>> pq;

int n, m, k;
ll dist[2][N], ans = LINF;
bool vi[N];
vector<ii> graph[N];

void dijkstra(int t) {
  memset(vi, 0, sizeof(vi));
  foru(i, 1, n) {
    if (dist[t][i] > LINF) continue;
    pq.push({dist[t][i], i});
  }

  while (!pq.empty()) { 
    auto top = pq.top(); pq.pop();
    int at = top.se;
    if (vi[at]) continue;
    vi[at] = 1;
    ll cost = top.fi;

    fore(e, graph[at]) {
      int to = e.fi, w = e.se;
      if (dist[t][to] > cost + w) {
        dist[t][to] = cost + w;
        pq.push({cost + w, to});
      }
    }
  }
}

int main() {
  setIO("flights");

  cin >> n >> m >> k;

  foru(i, 1, m) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
  }

  memset(dist[0], 0x3f, sizeof(dist[0]));
  dist[0][1] = 0;
  dijkstra(0);
  ans = dist[0][n];

  foru(i, 1, k) {
    int at = i&1, that = at^1;
    memset(dist[at], 0x3f, sizeof(dist[at]));
    foru(u, 1, n) fore(e, graph[u]) dist[at][e.fi] = min(dist[at][e.fi], dist[that][u] - e.se);
    dijkstra(at);
    ans = min(ans, dist[at][n]);
  }

  cout << ans;
}