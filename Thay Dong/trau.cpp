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
#define int long long
 
void setIO(string name="") {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  if (fopen((name + ".inp").c_str(), "r")) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

const int N = 5e5+5;
const int INF = 2e9+9;

struct node {
  int mn, mx;
  node(int _mn=0, int _mx=0) : mn(_mn), mx(_mx) {}
};

struct toy {
  int a, b;
  toy(int _a=0, int _b=0) : a(_a), b(_b) {}
  bool operator < (const toy &t) const { return a < t.a; }
};

int n, ans = INF;
toy a[N];
node pre[2][N];

void solve(bool inc) {
  foru(i, 0, 1) {
    pre[i][0].mn = INF;
    pre[i][0].mx = -INF;
  }

  foru(i, 1, n) {
    foru(j, 0, 1) { pre[j][i].mn = pre[j][i-1].mn; pre[j][i].mx = pre[j][i-1].mx; }
    pre[0][i].mn = min(pre[0][i].mn, a[i].b);
    pre[0][i].mx = max(pre[0][i].mx, a[i].b);
    pre[1][i].mn = min(pre[1][i].mn, a[n-i+1].b);
    pre[1][i].mx = max(pre[1][i].mx, a[n-i+1].b);
  }

  foru(l, 1, n)
    foru(r, l, n) if (l > 1 || r < n) {
      ans = min(ans, a[r].a - a[l].a + max(pre[0][l-1].mx, pre[1][n-r].mx) - min(pre[0][l-1].mn, pre[1][n-r].mn));
      if (ans == 4) {
        cout << l << " " << r;
        return;
      }
    }
}

signed main() {
  setIO("input");

  cin >> n;
  foru(i, 1, n) cin >> a[i].a >> a[i].b;
  sort(a+1, a+n+1);
  solve(1);
  cout << ans;
}