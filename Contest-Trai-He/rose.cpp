#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
 
#define foru(i, l, r) for(int i=(l); i<=(r); ++i)
#define ford(i, l, r) for(int i=(l); i>=(r); --i)
#define fore(x, v) for(auto &x : v)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define lc id<<1
#define rc id<<1|1
 
void setIO(string name="") {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  if (!name.empty()) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out1").c_str(), "w", stdout);
  }
}

const ll LINF = 1e18;
const int INF = 2e9;
const int N = 5e5+5, V = 5e5;

int cnt[N];
vector<int> divs[V+1];

void prep() {
  foru(i, 1, V) {
    int j = i;
    while (j <= V) {
      divs[j].push_back(i);
      j += i;
    }
  }
}

int n, q, a[N], ans[N];
int now;

// segment tree here
int sgt[N * 4], lazy[N * 4];

void app(int id) {
  if (lazy[id] == 0) return;
  if (sgt[lc] < INF) {
    lazy[lc] += lazy[id];
    sgt[lc] -= lazy[id];
  }
  if (sgt[rc] < INF) {
    lazy[rc] += lazy[id];
    sgt[rc] -= lazy[id];
  }
  lazy[id] = 0;
}

void propaganda(int id, int lb, int rb) {
  if (lb == rb) {
    for(int i : divs[lb]) if ((cnt[i] -= 1) == 0) {
      ans[i] = now;
    }
    sgt[id] = INF;
    return;
  }
  app(id);
  int mb = (lb + rb) >> 1;
  if (sgt[lc] <= 0) propaganda(lc, lb, mb);
  if (sgt[rc] <= 0) propaganda(rc, mb+1, rb);
  sgt[id] = min(sgt[lc], sgt[rc]);
}

void build(int id, int lb, int rb) {
  if (lb ^ rb) {
    int mb = (lb + rb) >> 1;
    build(id*2, lb, mb);
    build(id*2+1, mb+1, rb);
    sgt[id] = min(sgt[lc], sgt[rc]);
  } else {
    if (a[lb] == 0) sgt[id] = INF;
    else sgt[id] = a[lb];
  }
}

void upd(int id, int lb, int rb, int l, int r, int v) {
  if (l <= lb && rb <= r) {
    if (sgt[id] < INF) {
      lazy[id] += v;
      if ((sgt[id]-=v) <= 0) propaganda(id, lb, rb);
    }
    return;
  } 
  if (rb < l || lb > r) {
    return;
  }
  app(id);
  int mb = (lb + rb) >> 1;
  upd(lc, lb, mb, l, r, v);
  upd(rc, mb+1, rb, l, r, v);
  sgt[id] = min(sgt[lc], sgt[rc]);
}

int main() {
  setIO("test");
  
  cin >> n >> q;
  prep();

  foru(i, 1, n) {
    cin >> a[i];
    if (a[i] > 0) for(int j : divs[i]) cnt[j] += 1;
  }
  build(1, 1, n);

  foru(i, 1, n) if (cnt[i] == 0) {
    ans[i] = 0;
  }

  for(now=1; now<=q; ++now) {
    int u, v, w;
    cin >> u >> v >> w;
    upd(1, 1, n, u, v, w);
  }

  foru(i, 1, n) 
    cout << (cnt[i] > 0 ? -1 : ans[i]) << " ";
}