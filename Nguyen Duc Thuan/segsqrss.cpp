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
#define lc id<<1
#define rc id<<1|1

void setIO(string name="") {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  if (fopen((name + ".inp").c_str(), "r")) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

const ll LINF = 1e18;
const int INF = 1e9;
const int N = 1e5+1;

struct node {
  ll sqr, sum, x;
  int type;
  node(ll _sqr=0, ll s=0, ll l=0, int t=0) : sqr(_sqr), sum(s), x(l), type(t) {}
};

int n, q;
ll a[N];
node sgt[N * 4];

void pull(int id) {
  sgt[id].sqr = sgt[lc].sqr + sgt[rc].sqr;
  sgt[id].sum = sgt[lc].sum + sgt[rc].sum;
}

void app(int id, int lb, int rb, ll value, int type) {
  int mb = (lb + rb) >> 1;
  if (type == 1) {
    sgt[id].x += value;
    sgt[id].type == (sgt[id].type == 2 ? 2 : 1);
    sgt[id].sqr += 2LL * sgt[id].sum * value + value * value * (rb - lb + 1);
    sgt[id].sum += value * (rb - lb + 1);
  }
  else {
    sgt[id].x = value;
    sgt[id].type = 2;
    sgt[id].sqr = value * value * (rb - lb + 1);
    sgt[id].sum = value * (rb - lb + 1);
  }
}

void propaganda(int id, int lb, int rb) {
  if (sgt[id].type == 0) return;
  int mb = (lb + rb) >> 1;
  app(lc, lb, mb, sgt[id].x, sgt[id].type);
  app(rc, mb+1, rb, sgt[id].x, sgt[id].type);
  sgt[id].type = 0;
  sgt[id].x = 0;
}

void build(int id, int lb, int rb) {
  if (lb ^ rb) {
    int mb = (lb + rb) >> 1;
    build(lc, lb, mb);
    build(rc, mb+1, rb);
    pull(id);
  } else sgt[id] = node(a[lb]*a[lb], a[lb], 0, 0);
}

void upd(int id, int lb, int rb, int l, int r, ll value, int type) {
  if (lb > r || rb < l) return;
  if (l <= lb && rb <= r) { app(id, lb, rb, value, type); return; }
  int mb = (lb + rb) >> 1;
  propaganda(id, lb, rb);
  upd(lc, lb, mb, l, r, value, type);
  upd(rc, mb+1, rb, l, r, value, type);
  pull(id);
}

ll query(int id, int lb, int rb, int l, int r) {
  if (l <= lb && rb <= r) return sgt[id].sqr;
  if (rb < l || lb > r) return 0;
  int mb = (lb + rb) >> 1;
  propaganda(id, lb, rb);
  return query(lc, lb, mb, l, r) + query(rc, mb+1, rb, l, r);
}

/*
194
248
277
590
*/

int main() {
  setIO("input");

  cin >> n >> q;
  foru(i, 1, n) cin >> a[i];
  build(1, 1, n);

  foru(i, 1, q) {
    int cmd;
    cin >> cmd;

    if (cmd == 1) {
      int l, r, v;
      cin >> l >> r >> v;
      upd(1, 1, n, l, r, v, 1);
    } 
    else if (cmd == 0) {
      int l, r, v;
      cin >> l >> r >> v;
      upd(1, 1, n, l, r, v, 2);
    }
    else {
      int l, r;
      cin >> l >> r;
      cout << query(1, 1, n, l, r) << "\n";
    }
  }
}