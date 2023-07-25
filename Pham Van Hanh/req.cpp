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

const int N = 4e5+5, Q = 1e6+1, V = 1e7;
int MOD;
int theta, n, q, a[N], ans[Q];
vector<ii> block[N];

int lpd[V+1], lst[V+1];
vector<int> prime;

void prep() {
  iota(lpd, lpd+V+1, 0);

  foru(i, 2, V) {
    if (lpd[i] == i) {
      prime.push_back(i);
    }
    fore(j, prime) {
      if (1LL * i * j > V) break;
      lpd[i * j] = j;
      if (i % j == 0) break;
    }
  }
}

int prod[N * 2];

void built() {
  fill(prod, prod+N*2, 1);
}

void upd(int i, int v) {
  prod[(i+=n)] = v;
  for(i>>=1; i>=1; i>>=1) prod[i] = 1LL * prod[i*2] * prod[i*2+1] % MOD;
}

int query(int l, int r) {
  int ans = 1;
  for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
    if (l & 1) ans = 1LL * ans * prod[l++] % MOD;
    if (!(r & 1)) ans = 1LL * ans * prod[r--] % MOD;
  }
  return ans;
}

int main() {
  setIO("input");
  
  prep();
  cin >> theta >> n >> q >> MOD;

  foru(i, 1, n) {
    cin >> a[i];
  }

  foru(i, 1, q) {
    int u, v;
    cin >> u >> v;
    block[v].emplace_back(u, i);
  }
  
  built();
  foru(i, 1, n) {
    int num = a[i];
    while (num > 1) {
      int p = lpd[num];
      while (num % p == 0) num /= p;
      if (lst[p] > 0) {
        a[lst[p]] /= (p - 1);
        a[lst[p]] *= p;
        upd(lst[p], a[lst[p]]);
      }
      lst[p] = i;
      a[i] /= p;
      a[i] *= (p - 1);
    }
    upd(i, a[i]);
    for(ii ask : block[i]) {
      ans[ask.se] = query(ask.fi, i);
    }
  }

  foru(i, 1, q) {
    cout << ans[i] << " ";
  }
}