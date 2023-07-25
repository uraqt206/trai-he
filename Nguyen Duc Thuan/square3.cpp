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

const int N = 5005, V = 1e6;

int n, a[N], comp[N], lpd[V+1];
vector<int> prime;
ll ans = 0;

void prep() {
  foru(i, 0, V) {
    lpd[i] = i;
  }

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

int main() {
  setIO("input");
  cin >> n;
  foru(i, 1, n) cin >> a[i];
  prep();
  foru(i, 1, n) {
    int num = a[i]; a[i] = 1;
    while (num > 1) {
      int exp = 0, p = lpd[num];
      while (num % p == 0) {
        num /= p;
        exp ^= 1;
      }
      if (exp) {
        a[i] *= p;
      }
    }
  }

  map<int, int> cnt;
  foru(i, 1, n) {
    ans += cnt[a[i]];
    foru(j, 1, i-1) {
      cnt[__gcd(a[i], a[j])] += 1;
    }
  }
  cout << ans;
}