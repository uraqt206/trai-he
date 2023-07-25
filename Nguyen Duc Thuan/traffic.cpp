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

const int N = 3e5+5, LOG = 19;
int n, q, a[N], id[N], lg[N];

// graph and lca
vector<int> graph[N];
int high[N], anc[LOG][N];

void prep(int u, int p) {
  anc[0][u] = p;
  high[u] = high[p] + 1;
  foru(i, 1, lg[high[u]]) anc[i][u] = anc[i-1][anc[i-1][u]];

  fore(v, graph[u])
    if (v != p) 
      prep(v, u);
}

int lca(int u, int v) {
  if (high[u] < high[v]) swap(u, v);
  ford(i, lg[high[u]-high[v]], 0) if (high[anc[i][u]] >= high[v])
    u = anc[i][u];
  if (u == v) return u;
  ford(i, lg[high[u]], 0) if (anc[i][u] != anc[i][v]) {
    u = anc[i][u];
    v = anc[i][v];
  }
  return anc[0][u];
}

// answer queries
int cnt[N];
ll ft[2][N], sum[N];
vector<ii> query1[N], query2[N];

void upd(int t, int i, int v) { 
  for(; i<=q; i+=i&-i) ft[t][i] += v; 
}

ll query(int t, int i) {
  ll ans = 0;
  for(; i>=1; i-=i&-i) ans += ft[t][i];
  return ans;
}

void add(int u, int v, int w, int t) {
  int l = lca(u, v);
  query1[u].emplace_back(w, t); query2[u].emplace_back(1, t);
  query1[v].emplace_back(w, t); query2[v].emplace_back(1, t);
  query1[l].emplace_back(-w, t); query2[l].emplace_back(-1, t);
  query1[anc[0][l]].emplace_back(-w, t); query2[anc[0][l]].emplace_back(-1, t);
}

void dfs(int u, int p) {
  ll del1 = query(0, id[u]);
  ll del2 = query(1, id[u]);

  fore(v, graph[u]) if (v != p) {
    dfs(v, u);
  }

  fore(x, query1[u]) {
    upd(0, x.se, x.fi);
  }

  fore(x, query2[u]) {
    upd(1, x.se, x.fi);
  }


  sum[u] = query(0, id[u]) - del1;
  cnt[u] = query(1, id[u]) - del2;
}

int main() {
  setIO("input");
  cin >> n >> q;

  foru(i, 2, n) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
    lg[i] = lg[i >> 1] + 1;
  }

  vector<pair<int, ii>> evts, ac, bc;
  
  foru(i, 1, n) {
    cin >> a[i];
    ac.push_back({a[i], {0, i}});
  }

  foru(i, 1, q) {
    int u, v, w;
    cin >> u >> v >> w;
    bc.push_back({w, {u, v}});
  }

  sort(all(ac));
  sort(all(bc));
  evts.resize(ac.size() + bc.size());
  merge(all(ac), all(bc), evts.begin());

  sort(all(evts));
  reverse(all(evts));
  prep(1, 0);

  int idx = 0;
  fore(x, evts) {
    if (x.se.fi == 0) id[x.se.se] = idx;
    else { ++idx; add(x.se.fi, x.se.se, x.fi, idx);}
  }

  dfs(1, 0);
  foru(i, 1, n) cout << sum[i] - 1LL * a[i] * cnt[i] << " ";
}