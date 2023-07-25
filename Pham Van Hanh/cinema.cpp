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
#define left _left
#define right _right
 
void setIO(string name="") {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  if (!name.empty()) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

const int MOD = 998244353;
const int N = 1e6+1;
bool prime[N];

int n, a[N], f[N], inv[N], ans, left[N], right[N];

int exp(int n, int k) {
  if (k == 0) return 1;
  int tmp = exp(n, k/2);
  tmp = 1LL * tmp * tmp % MOD;
  if (k & 1) tmp = 1LL * tmp * n % MOD;
  return tmp;
}

void prep() {
  f[0] = inv[0] = 1;
  foru(i, 1, n) {
    f[i] = 1LL * f[i-1] * i % MOD;
    inv[i] = 1LL * inv[i-1] * f[i-1] % MOD;
  } 
  int tmp = exp(1LL * inv[n] * f[n] % MOD, MOD-2);
  ford(i, n, 1) {
    inv[i] = 1LL * inv[i] * tmp % MOD;
    tmp = 1LL * tmp * f[i] % MOD;
  }
}

int comb(int n, int k) {
  int ans = f[n];
  ans = 1LL * ans * inv[k] % MOD;
  ans = 1LL * ans * inv[n-k] % MOD;
  return ans;
}

bool checkLeft(int i) {
  int lst = -1;
  ford(j, i, 1) {
    if (a[j] == 0) continue;
    if (lst == -1) lst = a[j];
    else if (lst > a[j]) return 0;
    lst = a[j];
  }
  return 1;
}

bool checkRight(int i) {
  int lst = -1;
  foru(j, i, n) {
    if (a[j] == 0) continue;
    if (lst == -1) lst = a[j];
    else if (lst > a[j]) return 0;
    lst = a[j];
  }
  return 1;
}

int sub5() {
  foru(i, 0, n-1) ans = (ans + comb(n-1, i)) % MOD;
  return ans;
}

int solve(int lb, int rb, int used) {
  int ans = 1;
  while (lb > 1 || rb < n) {
    int i = (lb == 0 ? 0 : left[lb-1]), j = (rb == n+1 ? n+1 : right[rb+1]);
    if (lb <= 1 || (rb < n && a[i] > a[j])) {
      int have_to = a[j] - 1 - used;
      int need = j - 1 - rb;
      if (have_to < need) return 0; 
      int rem(have_to - need);
      int can_stand = (lb == 0 ? 0 : lb - 1 - i);
      used = a[j];
      lb -= rem;
      if (a[lb-1] != 0 && used >= a[lb-1]) --lb;
      rb = j;
      ans = 1LL * ans * comb(have_to, need) % MOD;
    }
    else {
      int have_to = a[i] - 1 - used;
      int need = lb - 1 - i;
      if (have_to < need) return 0;
      int rem(have_to - need);
      int can_stand = (rb == n+1 ? 0 : j - 1 - rb);
      if (rem > can_stand) return 0;
      lb = i;
      rb += rem;
      if (a[rb+1] != 0 && used >= a[rb+1]) ++rb;
      used = a[i];
      ans = 1LL * ans * comb(have_to, need) % MOD;
    }
  }
  return ans;
}

int main() {
  setIO("input");

  cin >> n;
  prep();

  int pos = -1;
  left[0] = 0;
  foru(i, 1, n) {
    cin >> a[i];
    if (a[i] != 0) left[i] = i;
    else left[i] = left[i-1];
    if (a[i] == 0) continue;
    if (pos == -1 || a[pos] > a[i]) pos = i;
  }
  a[0] = a[n+1] = n+1;
  
  right[n+1] = n+1;
  ford(i, n, 1) {
    if (a[i] != 0) right[i] = i;
    else right[i] = right[i+1];
  }

  if (pos == -1) {
    cout << sub5();
    return 0;
  }

  if (a[pos] == 1) {
    if (!checkLeft(pos) || !checkRight(pos)) {
      cout << 0;
      return 0;
    }
    cout << solve(pos, pos, 1);
    return 0;
  }

  int ans1 = 0, ans2 = 0;
  
  if (pos-a[pos]+1 > left[pos-1] && checkLeft(pos-1)) ans1 = 1LL * solve(pos-a[pos]+1, pos, a[pos]) * exp(2, a[pos]-2) % MOD;
  if (pos+a[pos]-1 < right[pos+1] && checkRight(pos+1)) ans2 = 1LL * solve(pos, pos+a[pos]-1, a[pos]) * exp(2, a[pos]-2) % MOD;

  cout << (ans1 + ans2) % MOD;
}