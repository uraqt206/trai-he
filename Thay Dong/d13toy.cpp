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

struct segment_tree {
  int n;
  vector<int> sgt;

  void init(int _n) {
    n = _n;
    sgt = vector<int>(n * 2, INF);
  }

  void upd(int i, int v) {
    sgt[i+=n] = v;
    for(i>>=1; i>=1; i>>=1) sgt[i] = min(sgt[i*2], sgt[i*2+1]);
  }

  int query(int l, int r) {
    int ans = INF;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1) {
      if (l & 1) ans = min(ans, sgt[l++]);
      if (!(r & 1)) ans = min(ans, sgt[r--]);
    }
    return ans;
  }
} sgt, sgt2;

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
int opt[N];

int ask(int a, int b, int c, int d, bool inc) {
  if (inc) return d-c+b-a;
  return d-c+a-b;
}

void solve(bool inc) {
  sgt.init(n);
  sgt2.init(n);

  foru(j, 0, 1) { 
    pre[j][0].mn = INF; pre[j][0].mx = -INF; 
  }

  foru(i, 1, n) {
    foru(j, 0, 1) { pre[j][i].mn = pre[j][i-1].mn; pre[j][i].mx = pre[j][i-1].mx; }
    pre[0][i].mn = min(pre[0][i].mn, a[i].b);
    pre[0][i].mx = max(pre[0][i].mx, a[i].b);
    pre[1][i].mn = min(pre[1][i].mn, a[n-i+1].b);
    pre[1][i].mx = max(pre[1][i].mx, a[n-i+1].b);
  }

  opt[0] = INF;
  foru(i, 1, n-1) {
    opt[i] = opt[i-1];
    if (inc) {
      sgt2.upd(i, - pre[0][i].mn - a[i+1].a);
      sgt.upd(i, pre[0][i].mx - pre[0][i].mn - a[i+1].a);
    }
    else {
      sgt2.upd(i, - pre[0][i].mn + a[i+1].a);
      sgt.upd(i, pre[0][i].mx - pre[0][i].mn + a[i+1].a);
    }
  }

  foru(r, 1, n) {
    int mnA, mxA, mnB, mxB, pos;
    mxA = a[r].a;

    // TH 1 : L R - +
    if (r < n) {
      mnB = pre[1][n-r].mn; mxB = pre[1][n-r].mx;
      pos = 0;
      for(int z=n; z>=1; z>>=1)
        while (pos+z < r && pre[0][pos+z].mn >= mnB && pre[0][pos+z].mx <= mxB)
          pos += z;
      mnA = a[pos+1].a;
      if (inc) ans = min(ans, mxA - mnA + mxB - mnB);
      else ans = min(ans, mnA - mxA + mxB - mnB);
    }

    // TH 2 : - L R + 
    mxB = pre[1][n-r].mx;
    int pmax = 0, pmin = 0;
    for(int z=n; z>=1; z>>=1) 
      while (pmin+z < r && pre[0][pmin+z].mn > pre[1][n-r].mn) 
        pmin += z;
    for(int z=n; z>=1; z>>=1)
      while (pmax+z < r && pre[0][pmax+z].mx <= pre[1][n-r].mx)
        pmax += z;
    if (pmin+1 <= pmax) {
      if (inc) ans = min(ans, mxA + mxB + sgt2.query(pmin+1, pmax));
      else ans = min(ans, - mxA + mxB + sgt2.query(pmin+1, pmax));
    }
    // cout << pos << "\n";

    // TH 3 : - + L R
    pos = 0;
    for(int z=n; z>=1; z>>=1)
      while (pos+z < r && (pre[0][pos+z].mn > pre[1][n-r].mn || pre[0][pos+z].mx < pre[1][n-r].mx)) 
        pos += z;
    if (inc) ans = min(ans, mxA + sgt.query(pos+1, r-1));
    else ans = min(ans, - mxA + sgt.query(pos+1, r-1));
    // cout << pos << "\n";
  }
}

signed main() {
  setIO("input");

  cin >> n;
  foru(i, 1, n) cin >> a[i].a >> a[i].b;

  sort(a+1, a+n+1);
  solve(1);
  reverse(a+1, a+n+1);
  solve(0);
  cout << ans;
}