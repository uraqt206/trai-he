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
  if (fopen((name + ".inp").c_str(), "r")) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

const int N = 1010;
const int dx1[] = {-1, -1, 0, 1, 1}, dy1[] = {-1, 1, 0, -1, 1};
const int dx2[] = {-1, 0, 0, 1}, dy2[] = {0, -1, 1, 0};

int n, m;
char a[N][N], marked[N][N];

void app1(int i, int j) {
  foru(x, 0, 4) {
    int nx = dx1[x] + i, ny = dy1[x] + j;
    if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
    if (a[nx][ny] != '*') return;
  }
  foru(x, 0, 4) {
    int nx = dx1[x] + i, ny = dy1[x] + j;
    if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
    marked[nx][ny] = '*';
  }
}

void app2(int i, int j) {
  foru(x, 0, 3) {
    int nx = dx2[x] + i, ny = dy2[x] + j;
    if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
    if (a[nx][ny] != '*') return;
  }
  foru(x, 0, 3) {
    int nx = dx2[x] + i, ny = dy2[x] + j;
    if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
    marked[nx][ny] = '*';
  }
}

int main() {
  setIO("input");

  int t;
  cin >> t;

  while (t--) {
    cin >> n >> m;

    foru(i, 1, n) {
      foru(j, 1, m) {
        cin >> a[i][j];
        marked[i][j] = '.';
      }
    }

    foru(i, 1, n) {
      foru(j, 1, m) {
        app1(i, j);
        app2(i, j);
      }
    }

    bool good = 1;
    foru(i, 1, m) { 
      foru(j, 1, m) {
        if (a[i][j] != marked[i][j]) {
          good = 0;
          break;
        }
      }
      if (!good) break;
    }
    cout << (good ? "YES\n" : "NO\n");
  }
}