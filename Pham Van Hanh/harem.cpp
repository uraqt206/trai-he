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

const int N = 3e5+5;
int n, m, deg[N];
vector<ii> e;
vector<int> graph[N], ans;

void make(int test) {
  foru(i, 1, n) {
    graph[i].clear();
    deg[i] = 0;
  }

  foru(i, 0, test) {
    graph[e[i].fi].push_back(e[i].se);
    deg[e[i].se] += 1;
  }

  vector<int> nxt;
  foru(i, 1, n) if (deg[i] == 0) {
    nxt.push_back(i);
  }

  ans.clear();
  while (nxt.size() == 1) {
    int at = nxt.back();
    nxt.pop_back();
    ans.push_back(at);

    for(int v : graph[at]) if (--deg[v] == 0) {
      nxt.push_back(v);
    }
  }
}

bool f(int test) {
  foru(i, 1, n) {
    graph[i].clear();
    deg[i] = 0;
  }

  foru(i, 0, test) {
    graph[e[i].fi].push_back(e[i].se);
    deg[e[i].se] += 1;
  }

  int at = -1;
  foru(i, 1, n) if (deg[i] == 0) {
    if (at == -1) at = i;
    else return 0;
  }
  
  while (at !=)

  return nxt.empty();
}

int main() {
  setIO("input");

  cin >> n >> m;
  
  foru(i, 1, m) {
    int u, v;
    cin >> u >> v;
    e.emplace_back(u, v);
  }

  int lb = 0, rb = m, mb;
  while (lb < rb) {
    mb = (lb + rb) >> 1;
    if (f(mb)) rb = mb;
    else lb = mb+1;
  }

  if (lb == m) cout << "-1";
  else {
    cout << lb+1 << "\n";
    make(lb);
    for(int x : ans) cout << x << " ";
  }
}