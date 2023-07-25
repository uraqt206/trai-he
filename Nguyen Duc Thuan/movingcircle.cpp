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

double dist(ii a, ii b) {
  return sqrt((a.fi - b.fi) * (a.fi - b.fi) + (a.se - b.se) * (a.se - b.se));
}

const int N = 1e5+5;

int n, e[N+2];
vector<pair<double, ii>> edges;
vector<ii> a;

int root(int u) {
  return e[u] < 0 ? u : e[u] = root(e[u]);
}

void join(int u, int v) {
  if ((u = root(u)) == (v = root(v))) return;
  if (e[u] > e[v]) swap(u, v);
  e[u] += e[v];
  e[v] = u;
}

int main() {
  setIO("input");

  cin >> n;
  foru(i, 0, n+1) {
    e[i] = -1;
  }

  foru(i, 1, n) {
    int x, y;
    cin >> x >> y;
    a.emplace_back(x, y);
    edges.push_back({100 - y, {i-1, n}});
    edges.push_back({y + 100, {i-1, n+1}});
  }

  foru(i, 0, n-1)
    foru(j, i+1, n-1)
      edges.push_back({dist(a[i], a[j]), {i, j}});

  sort(all(edges));
  double ans = 0;
  fore(x, edges) {
    int u = x.se.fi, v = x.se.se;
    join(u, v);
    ans = x.fi;
    if (root(n) == root(n+1)) break;
  }
  cout << setprecision(10) << fixed << ans/2.0;
}