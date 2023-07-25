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

int MOD;
const int N = 1e6+1;
bool prime[N];

int n, k, f[N], inv[N];

int exp(int n, int k) {
  if (k == 0) return 1;
  int tmp = exp(n, k/2);
  tmp = 1LL * tmp * tmp % MOD;
  if (k & 1) tmp = 1LL * tmp * n % MOD;
  return tmp;
}

void prep() {
  f[0] = inv[0] = 1;
  foru(i, 1, N-1) {
    f[i] = 1LL * f[i-1] * i % MOD;
    inv[i] = exp(f[i], MOD-2);
  }

  fill(prime, prime+N, 1);
  prime[0] = prime[1] = 0;
  for(int i=2; i*i<N; ++i) if (prime[i]) 
    for(int j=i*i; j<N; j+=i)
      prime[j] = 0;
}

int comb(int n, int k) {
  int ans = f[n];
  ans = 1LL * ans * inv[k] % MOD;
  ans = 1LL * ans * inv[n-k] % MOD;
  return ans;
}

int sub3(int n, int k) {
  int ans = inv[k];
  for(int i=n-k+1; i<=n; ++i) ans = 1LL * ans * i % MOD;
  return ans;
}

int cnt(ll n, ll k) {
  int ans = 0;
  ll cur = k;
  while (n/cur > 0) {
    ans += n/cur;
    cur *= k;
  }
  return ans;
}

int sub4(int n, int k) {
  int ans = 1;
  foru(i, 1, n) if (prime[i]) {
    ans = (1LL * ans * exp(i, cnt(n, i) - cnt(k, i) - cnt(n-k, i))) % MOD;
    // cout << cnt(n, i) << " " << cnt(k, i) << " " << cnt(n-k, i) << "\n"; 
  }
  return ans;
}

int main() {
  setIO("flowers");

  int t;
  cin >> t >> MOD;
  prep();

  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    int sec = 1LL * m * exp(m-1, k) % MOD;
    int fir;

    if (MOD == 998244353) {
      if (n <= 1000000) fir = comb(n-1, k);
      else fir = sub3(n-1, k);
    } 
    else {
      fir = sub4(n-1, k);
    }

    cout << 1LL * fir * sec % MOD << "\n";
  }
}