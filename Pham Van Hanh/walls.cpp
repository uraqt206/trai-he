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
const int N = 1e6+1, V1 = 5000, V2 = 2e6;

int exp(int n, int k) {
  if (k == 0) return 1;
  int tmp = exp(n, k/2);
  tmp = 1LL * tmp * tmp % MOD;
  if (k & 1) tmp = 1LL * tmp * n % MOD;
  return tmp;
}

ll n, c;
int theta, t;
int fact[V2+1], inv[V2+1], cnk[10001][5001];

void prepCnk1() {
  cnk[0][0] = 1;
  foru(i, 1, V1*2) {
    cnk[i][0] = 1;
    foru(j, 1, V1) {
      cnk[i][j] = (cnk[i-1][j-1] + cnk[i-1][j]) % MOD;
    }
  }
  vector<int> tmp(V1+1);
  foru(i, 1, V1) {
    foru(j, 1, V1) {
      tmp[j] = cnk[j+i-1][i-1];
    }
    cnk[i][0] = 0;
    foru(j, 1, V1) {
      cnk[i][j] = (cnk[i][j-1] + tmp[j]) % MOD;
    }
  }
}

void prepCnk2() {
  fact[0] = inv[0] = 1;
  foru(i, 1, V2) {
    fact[i] = 1LL * fact[i-1] * i % MOD;
    inv[i] = 1LL * inv[i-1] * fact[i-1] % MOD;
  }
  int tmp = exp(1LL * inv[V2] * fact[V2] % MOD, MOD-2);
  ford(i, V2, 1) {
    inv[i] = 1LL * inv[i] * tmp % MOD;
    tmp = 1LL * tmp * fact[i] % MOD;
  }
}

bool comp[V2+1];
vector<int> prime;

void prepPrime() {
  comp[0] = comp[1] = 1;
  foru(i, 2, V2) {
    if (!comp[i]) {
      prime.push_back(i);
    }
    fore(j, prime) {
      if (1LL * i * j <= V2) {
        comp[i * j] = 1;
      } else break;
      if (i % j == 0) {
        break;
      }
    }
  }
}

int cnk2(int n, int k) {
  int ans = fact[n];
  ans = 1LL * ans * inv[k] % MOD;
  ans = 1LL * ans * inv[n-k] % MOD;
  return ans;
}

int cnk3(ll n, int k) {
  int ans = inv[k];
  int cur = (n-k+1) % MOD;
  for(ll i=n-k+1; i<=n; ++i) {
     ans = 1LL * ans * cur % MOD;
    cur += 1;
    if (cur == MOD) cur = 0;
  }
  return ans;
}

int count(ll n, int i) {
  int ans = 0;
  long long tmp = i;
  while (n/tmp > 0) {
    ans += n/tmp;
    tmp = tmp * i;
  }
  return ans;
}

int cnk4(int n, int k) {
  int ans = 1;
  for(int i : prime) {
    if (i > n) break;
    int tmp = count(n, i);
    if (i <= k) tmp -= count(k, i);
    if (i <= n-k) tmp -= count(n-k, i);
    ans = 1LL * ans * exp(i, tmp) % MOD;
  }
  return ans;
}

int main() {
  setIO("walls");

  cin >> theta >> t >> MOD;
  if (theta <= 2) prepCnk1();
  else if (theta <= 4) prepCnk2();
  else prepPrime();

  if (theta <= 2) {
    for(int i=1; i<=t; ++i) {
      cin >> n >> c;
      cout << cnk[c][n] << " ";
    }
  }

  else if (theta == 3) {
    for(int i=1; i<=t; ++i) {
      cin >> n >> c;
      int ans = cnk2(n+c, c);
      if ((ans -= 1) < 0) ans += MOD;
      cout << ans << " ";
    }
  }

  else if (theta == 4) {
    for(int i=1; i<=t; ++i) {
      cin >> n >> c;
      int ans = cnk3(n+c, c);
      if ((ans -= 1) < 0) ans += MOD;
      cout << ans << " ";
    }
  }

  else if (theta == 5) {
    for(int i=1; i<=t; ++i) {
      cin >> n >> c;
      int ans = cnk4(n+c, c);
      if ((ans -= 1) < 0) ans += MOD;
      cout << ans << " ";
    }
  }
}