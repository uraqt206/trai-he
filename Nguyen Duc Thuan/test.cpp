/**
 *                       \`*-.
 *                        )  _`-.
 *                       .  : `. .
 *                       : _   '  \
 *                       ; *` _.   `*-._
 *                       `-.-'          `-.
 *                         ;       `       `.
 *                         :.       .        \
 *                         . \  .   :   .-'   .
 *                         '  `+.;  ;  '      :
 *                         :  '  |    ;       ;-.
 *                         ; '   : :`-:     _.`* ;
 *          [WA]        .*' /  .*' ; .*`- +'  `*'
 *                      `*-*   `*-*  `*-*'
**/
/** :)) **/

#include <bits/stdc++.h>

using namespace std;

typedef double db;
typedef long long ll;
typedef long double ld;

#define int ll
typedef pair<int, int> pii;

#define X first
#define Y second
#define gcd __gcd
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define bit(i, mask) ((mask) >> (i) & 1)
#define reset(x, val) memset(x, val, sizeof(x))
#define foru(i,a,b) for(int i = (a); i <= (b); ++i)
#define ford(i,a,b) for(int i = (a); i >= (b); --i)
#define FastIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

template<typename T> bool maximize(T &res, const T &val) { if (res < val) { res = val; return true; } return false; }
template<typename T> bool minimize(T &res, const T &val) { if (res > val) { res = val; return true; } return false; }

const ll Linf = 0x3f3f3f3f3f3f3f3f;
const int Inf = 0x3f3f3f3f;
const int Mod = 1e9 + 7;
const int Lim = 1e6 + 5;
const int inv6 = 166666668;

// #define Sieve
#ifdef Sieve
    vector<int> pr;
    vector<int> lpf;
    void Linear_sieve(int n = Lim) {
        pr.assign(1, 2);
        lpf.assign(n + 1, 2);
    
        for (int x = 3; x <= n; x += 2) {
            if (lpf[x] == 2) pr.push_back(lpf[x] = x);
            for (int i = 1; i < pr.size() && pr[i] <= lpf[x] && pr[i] * x <= n; ++i)
                lpf[pr[i] * x] = pr[i];
        }
    }
#endif

// #define Ckn_calc
#ifdef Ckn_calc
    const int LIM = 1e6 + 16;
    const int MOD = Mod;
    
    int fact[LIM + 10]; /// factorial:         fact[n] = n!
    int invs[LIM + 10]; /// inverse modular:   invs[n] = n^(-1)
    int tcaf[LIM + 10]; /// inverse factorial: tcaf[n] = (n!)^(-1)
    void precal_nck(int n = LIM)
    {
        fact[0] = fact[1] = 1;
        invs[0] = invs[1] = 1;
        tcaf[0] = tcaf[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            fact[i] = (1LL * fact[i - 1] * i) % MOD;
            invs[i] = MOD - 1LL * (MOD / i) * invs[MOD % i] % MOD;
            tcaf[i] = (1LL * tcaf[i - 1] * invs[i]) % MOD;
        }
    }
    
    ll C(int n, int k) {
        ll res = fact[n];
        res *= tcaf[k], res %= Mod;
        res *= tcaf[n - k], res %= Mod;
        return res;
    }
    
    ll P(int n, int k) {
        ll res = fact[n];
        res *= tcaf[n - k], res %= Mod;
        return res;
    }
#endif

/// ====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====

const int base = 31;
const int N = 1e5 + 5;
const int K = 3e3 + 5;
const int dx[] = {+1, -1, 0, 0};
const int dy[] = {0, 0, +1, -1};
const int block_size = sqrt(2e9) + 2;

int n, q;
int a[N];

struct element {
    int sum, sqr, lazy, tp;
    element(int sum = 0, int sqr = 0, int lazy = 0, int tp = -1):
        sum(sum), sqr(sqr), lazy(lazy), tp(tp) {}
};

// tp = 0: update: a[i] += x
// tp = 1: modify: a[i] = x


element f[N * 4];
void refine(int id) {
    int k = id << 1;
    f[id].sum = f[k].sum + f[k + 1].sum;
    f[id].sqr = f[k].sqr + f[k + 1].sqr;
}

void push(int l, int r, int id, int x, int tp) {
    if (tp == -1 || l > r) return;

    auto &res = f[id];
    if (tp == 0) {
        res.sqr += 2LL * x * res.sum + (r - l + 1) * x * x;
        res.sum += (r - l + 1) * x;
        res.lazy += x;
        res.tp = (res.tp == 1 ? 1 : 0);
    }

    if (tp == 1) {
        res.sqr = (r - l + 1) * x * x;
        res.sum = (r - l + 1) * x;
        res.lazy = x;
        res.tp = 1;
    }
}

void down(int l, int r, int id) {
    int mid = (l + r) >> 1, k = id << 1;

    auto &res = f[id];
    push(l, mid, k, res.lazy, res.tp);
    push(mid + 1, r, k + 1, res.lazy, res.tp);

    res.tp = -1;
    res.lazy = 0;
}

void update(int u, int v, int x, int l, int r, int id) {
    if (r < u || v < l) return;
    if (u <= l && r <= v) {
        return push(l, r, id, x, 0);
    }

    down(l, r, id);

    int mid = (l + r) >> 1, k = id << 1;
    update(u, v, x, l, mid, k);
    update(u, v, x, mid + 1, r, k + 1);

    refine(id);
}

void modify(int u, int v, int x, int l, int r, int id) {
    if (r < u || v < l) return;
    if (u <= l && r <= v) {
        return push(l, r, id, x, 1);
    }

    down(l, r, id);
    int mid = (l + r) >> 1, k = id << 1;
    modify(u, v, x, l, mid, k);
    modify(u, v, x, mid + 1, r, k + 1);

    refine(id);
}

int get(int u, int v, int l, int r, int id) {
    if (r < u || v < l) return 0;
    if (u <= l && r <= v) return f[id].sqr;

    down(l, r, id);
    int mid = (l + r) >> 1, k = id << 1;
    return get(u, v, l, mid, k) + get(u, v, mid + 1, r, k + 1);
}

void update(int u, int v, int x) { return update(u, v, x, 1, n, 1); }
void modify(int u, int v, int x) { return modify(u, v, x, 1, n, 1); }
int get(int u, int v) { return get(u, v, 1, n, 1); }

void solve() {
    cin >> n >> q;
    foru(i, 1, n) cin >> a[i];

    foru(i, 1, n) modify(i, i, a[i]);

    while (q--) {
        int opt;
        cin >> opt;

        if (opt == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            modify(l, r, x);
        }

        if (opt == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            update(l, r, x);
        }

        if (opt == 2) {
            int l, r;
            cin >> l >> r;
            cout << get(l, r) << "\n";
        }
    }
}

signed main() {
    FastIO;

    freopen("input.inp", "r", stdin);
    freopen("input.out", "w", stdout);
    solve();
}

/**  /\_/\
 *  (= ._.)
 *  / >TL \>AC
**/

/**
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠞⠉⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠈⠓⢄⠀⠀⠀⠙⠑⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⠀⠀⠀⢀⡴⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠈⠹⢦⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⣀⣠⣤⣴⣶⣶⣾⣟⠟⠀⠀⠠⠃⢠⠎⠀⠀⠀⣰⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡀⠀⠀⠀⠀⠑⣟⢿⣷⣶⣶⣶⣤⣤⣀⠀
⠀⠸⣿⣿⣿⣿⣿⡿⢻⠋⠀⠀⠀⠁⡰⠃⠀⠀⠀⢰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢶⡀⠀⠀⠀⠈⢺⠛⣿⣿⣿⣿⣿⣿⠃
⠀⠀⢿⣿⣿⣿⡿⢳⠃⢀⡀⠀⠀⡼⠁⠠⠀⠀⢀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢷⡀⠀⠑⠄⠀⠳⡛⢿⣿⣿⣿⡟⠀
⠀⠀⢸⣿⣿⣿⣤⡇⠃⠀⠀⠀⢰⠃⠀⢡⡎⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢱⡄⠀⠀⠀⠀⢱⢸⣿⣿⣿⠃⠀
⠀⠀⠀⣿⣿⢫⡟⠸⠀⠀⠀⠀⡏⠀⠀⡎⠀⠀⣸⡀⠀⠀⠀⠀⠀⠀⣄⢯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢧⠀⠈⢦⠀⠀⢫⡹⣿⡟⠀⠀
⠀⠀⠀⢸⣿⣿⠁⣏⠀⠀⠀⢸⠁⠀⡸⠀⠀⣼⠟⡇⠀⠀⠀⠀⠀⠀⠘⣼⡆⠀⠀⠈⣧⠀⠀⠀⠀⠀⠘⡆⠀⠀⢧⠀⠀⢻⣿⠃⠀⠀
⠀⠀⠀⠀⣿⠇⠀⠮⠀⠀⠀⡏⠀⠀⡇⠀⡰⠧⠤⠼⡀⢰⠀⠀⠀⠀⠀⠸⣿⣦⠀⠀⠘⣧⡀⠀⠀⠀⠀⠹⡀⠀⠸⡄⠀⠈⢿⣄⠀⠀
⠀⠀⠀⢠⡟⡄⠀⡳⠀⠀⢰⠇⠀⣼⠁⡰⢁⣀⣀⠀⠹⡄⢣⠀⠀⠀⠀⠀⠙⣌⠛⠦⡀⠱⡙⢦⡀⠀⢣⠀⢣⠀⠀⢇⠀⠈⢏⣏⠛⢖
⠀⠀⢠⢳⠃⡇⠀⢑⠀⠀⢸⠀⡜⢉⣦⣯⡵⠶⢦⣌⠐⠜⢄⠳⣄⡀⠀⠀⠀⠈⢲⣈⣭⣵⣿⣑⠳⣄⠈⡇⠘⡆⠀⢸⠀⠀⢸⠘⡆⠀
⠀⣠⠃⡞⠀⢱⠀⢸⠀⠀⢸⡜⢠⣿⠟⢁⠐⢿⣷⣌⢳⡀⠀⠑⠸⠯⠉⠑⠒⢢⡟⠁⠘⣿⣶⡍⠻⣬⡷⣧⠀⢳⠀⠨⡄⠀⢈⠆⢹⡀
⡜⠁⣼⠇⠀⠈⡆⠈⡆⠀⢸⠐⣾⠃⠀⣿⡖⣶⡽⣿⠀⣧⠀⠀⠀⠀⠀⠀⠀⣾⠀⣷⣶⣷⣹⣿⠀⢹⡾⢾⢀⣾⡀⠀⡇⠀⢸⠀⠀⢣
⣠⡾⢼⡁⠀⠀⠹⡄⢱⠀⢸⠐⣻⠀⠀⣿⣏⣿⣧⢿⠂⠀⠀⠀⠀⠀⠀⠀⠀⠈⠘⣿⢿⣿⢿⣻⠀⠀⡷⠞⠉⣯⡇⢀⡇⠀⣸⠀⠀⠘
⣿⡝⣾⠀⠀⠀⠀⢳⠈⢇⠸⡀⠹⡄⠀⠘⢇⣐⡨⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣔⣂⡸⠃⠀⢸⠓⠂⢰⢿⡇⢰⠀⢀⡇⠀⠀⠀
⣷⣛⣼⠀⠀⠀⠀⠀⠣⡈⢆⢇⠀⠈⠢⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡄⠋⠁⢀⡷⢫⣗⡸⠀⡼⠀⠀⠀⠀
⢷⣝⣾⡄⠀⠀⠀⠀⠀⠑⣌⢾⡀⠀⠀⠀⠀⠀⠀⣠⡖⠒⠒⠒⠒⠒⠒⠒⠒⠦⠤⣄⠀⠀⠁⠁⠀⠀⠀⡜⠛⣫⣷⠃⡼⠁⠀⠀⠀⠀
⠸⣿⣸⣇⠀⠀⠀⠀⠀⠀⠀⢣⣇⠀⠀⠀⠀⠀⢸⣿⡿⠟⠛⠛⠛⠛⠛⠛⠛⠛⠿⣿⡇⠀⠀⠀⠀⠀⢸⣧⢿⢿⡟⡸⠃⠀⠀⠀⠀⢀
⣧⠘⢿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠹⣆⠀⠀⠀⠀⠈⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡸⠁⠀⠀⠀⠀⢠⡿⣼⡹⣾⡟⠁⠀⠀⠀⠀⠀⢸
⠈⠁⠈⠻⡽⡄⠀⠀⠀⠀⠀⠀⠀⠘⢦⠀⠀⠀⠀⠀⠓⢦⡀⠀⠀⠀⠀⠀⢀⡠⠞⠁⠀⠀⠀⢀⣴⣟⡳⢧⣻⡽⠀⠀⠀⠀⠀⠀⢀⡯
⣿⣶⣤⣄⣹⡽⣆⠀⠀⠀⠀⠀⠀⠀⠈⠳⣄⡀⠀⠀⠀⠀⠈⠓⠒⠒⠒⠚⠉⠀⠀⠀⢀⣠⣴⢯⡳⣞⣿⣷⣹⡇⠀⠀⠀⠀⠀⢀⣾⢳
⣿⣿⣿⣿⣿⣿⣯⠷⣄⠀⠀⠀⠀⠀⠀⠀⠹⣿⣷⣒⣦⢤⣤⣠⣀⣄⣠⣤⣤⣴⣶⢻⡽⣻⣮⣗⣻⢼⣻⡟⢾⡇⠀⠀⠀⠀⢀⡾⣭⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣽⣳⢦⣀⠀⠀⠀⠀⠀⠹⡏⠁⠉⠓⠦⣉⡉⠛⣙⣩⠵⢚⠩⠳⣽⣽⣼⣿⣾⣷⣷⣿⣿⠆⠀⠀⠀⣠⣾⣻⣾⣿
**/
