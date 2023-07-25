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

const int MOD = 1e9+7;
const int N = 1e5+1, V = 1e5;
ll n, a[N];
vector<int> divs[N], pos[N];
int e[N];

void prep() {
  for(int i=1; i<=V; ++i)
    for(int j=i; j<=V; j+=i)
      divs[j].push_back(i);
}

int root(int u) {
  return e[u] < 0 ? u : e[u] = root(e[u]);
}

bool join(int u, int v) {
  if ((u = root(u)) == (v = root(v))) return 0;
  if (e[u] > e[v]) swap(u, v);
  e[u] += e[v];
  e[v] = u;
  return 1;
}

int main() {
  setIO("input");

  cin >> n;
  memset(e, -1, sizeof(e));
  prep();

  foru(i, 1, n) {
    int num;
    cin >> num;
    for(int x : divs[num]) pos[x].push_back(i);
  }

  ll ans = 0;
  ford(i, V, 1) {
    int lst = -1;
    for(int j : pos[i]) {
      if (lst != -1 && join(lst, j)) ans += i;
      lst = j;
    }
  }
  
  cout << ans;
}