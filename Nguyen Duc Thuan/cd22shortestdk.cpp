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

const int N = 1e5+5, LOG = 19;
int n, m, k;
ll dist[N][LOG];
bool vi[N][LOG];
vector<ii> graph[N];

int main() {
  setIO("input");

  cin >> n >> m >> k;

  foru(i, 1, m) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].emplace_back(v, w);
    graph[v].emplace_back(u, w);
  }

  memset(dist, 0x3f, sizeof(dist));
  priority_queue<pair<ll, ii>> pq;
  dist[1][0] = 0;
  pq.push({0, {1, 0}});

  while (!pq.empty()) {
    auto top = pq.top(); pq.pop();
    int u = top.se.fi, used = top.se.se;
    if (vi[u][used]) continue;
    vi[u][used] = 1;
    
    for(ii e : graph[u]) {
      int v = e.fi, w = e.se;
      
      // free this edge
      if (used < k && dist[v][used+1] > -top.fi) {
        dist[v][used+1] = -top.fi;
        pq.push({-top.fi, {v, used+1}});
      }

      // continue normal
      if (dist[v][used] > w - top.fi) {
        dist[v][used] = w - top.fi;
        pq.push({w - top.fi, {v, used}});
      }
    }
  }

  foru(i, 1, n) {
    cout << *min_element(dist[i], dist[i]+k+1) << " ";
  }
}