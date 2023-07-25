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

const ll LINF = 1e18+1;
const int N = 110;

ll n, m, w;

struct matrix {
  ll n, m;
  vector<vector<ll>> mat;

  matrix(ll _n=0, ll _m=0) : n(_n), m(_m) {
    mat.resize(n);
    foru(i, 0, n-1) mat[i].resize(m);
  } 

  matrix operator * (const matrix &b) {
    matrix c(n, b.m);
    foru(i, 0, n-1)
      foru(j, 0, b.m-1) {
        c.mat[i][j] = w+1;
        foru(k, 0, m-1) {
          c.mat[i][j] = min(c.mat[i][j], mat[i][k] + b.mat[k][j]);
        }
      }
    return c;
  }

  bool ok() {
    foru(i, 0, n-1)
      foru(j, 0, m-1)
        if (mat[i][j] <= w) return 1;
    return 0;
  }
};

matrix pw[60];

int main() {
  setIO("input");

  cin >> n >> m >> w;
  matrix base(n, n);
  matrix cur = base;
  foru(i, 0, n-1) base.mat[i].assign(n, w+1);
  foru(i, 1, m) {
    ll u, v, w; cin >> u >> v >> w;
    --u; --v;
    base.mat[v][u] = min(base.mat[v][u], w);
  }
  pw[0] = base;
  foru(i, 1, 59) pw[i] = pw[i-1] * pw[i-1];
  ll ans = 0;
  ford(i, 59, 0) {
    matrix tmp = cur * pw[i];
    if (tmp.ok()) {
      ans += (1LL << i);
      cur = tmp;
    }
  }
  cout << ans;
}