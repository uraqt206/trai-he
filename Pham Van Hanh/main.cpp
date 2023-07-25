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
using sv = pair<ii, int>;
const int N = 3e5+5, V = 1e7;
int MOD;
int theta, n, q, a[N], prod[N*4], ans[N];
vector<pair<ii, int>> querys;
int lpd[V+1];
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

int exp(int n, int k) {
  if (k == 0) return 1;
  int tmp = exp(n, k/2);
  tmp = 1LL * tmp * tmp % MOD;
  if (k & 1) tmp = 1LL * tmp * n % MOD;
  return tmp;
}

void upd(int id, int lb, int rb, int i, int v) { 
  if (lb ^ rb) {
    int mb = (lb + rb) >> 1;
    if (i <= mb) upd(id*2, lb, mb, i, v);
    else upd(id*2+1, mb+1, rb, i, v);
    prod[id] = 1LL * prod[id*2] * prod[id*2+1] % MOD;
  } else prod[id] = 1LL * prod[id] * v % MOD;
}

int query(int id, int lb, int rb, int l, int r) {
  if (l <= lb && rb <= r) return prod[id];
  if (rb < l || lb > r) return 1;
  int mb = (lb + rb) >> 1;
  return 1LL * query(id*2, lb, mb, l, r) * query(id*2+1, mb+1, rb, l, r);
}

void sub1() {
  sort(all(querys), [&](sv a, sv b){
    return a.fi.se < b.fi.se;
  });

  map<int, int> mp;
  int j = 0;
  
  foru(i, 1, n) {
    int num = a[i];
    while (num > 1) {
      int p = lpd[num];
      while (num % p == 0) {
        num /= p;
      }
      int in = (1 - exp(p, MOD-2) + MOD) % MOD, out = exp(in, MOD-2);
      if (mp.count(p)) upd(1, 1, n, mp[p], out);
      mp[p] = i;
      upd(1, 1, n, i, in);
    }

    while (j < querys.size() && querys[j].fi.se <= i) {
      auto cur = querys[j];
      ans[cur.se] = query(1, 1, n, cur.fi.fi, cur.fi.se);
    }
  }

  foru(i, 1, q) {
    cout << ans[i] << "\n";
  }
}

void sub2() {

}

int main() {
  setIO("input");

  cin >> theta >> n >> q >> MOD;
  prep();

  foru(i, 1, n) {
    cin >> a[i];
  }

  foru(i, 1, q) {
    int l, r;
    cin >> l >> r;
    querys.emplace_back(l, r);
  }

  if (MOD == 998244353) sub1();
  // else sub2();
}