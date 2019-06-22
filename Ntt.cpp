#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp(a) setprecision(a)<<fixed
#define ss second
#define fori(v) for(ll i=0; i<v; i++)
#define forj(v) for(ll j=0; j<v; j++)
#define fork(v) for(ll k=0; k<v; k++)
#define forl(v) for(ll l=0; l<v; l++)
#define fort(v) for(ll t=0; t<v; t++)
#define forz(v) for(ll z=0; z<v; z++)
#define forx(v) for(ll x=0; x<v; x++)
#define fory(v) for(ll y=0; y<v; y++)
#define ll long long
#define pb(a) push_back(a)
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ld> vd;
typedef vector<vd> vvd;
typedef pair<ll, ll> pii;
typedef vector<pii> vpii;
const ll INF = 0x3f3f3f3f;
const ll inf =  pow(10,18);
ll modulo = pow(10,9) + 7;
const long long MOD = modulo;

// taken from https://www.codechef.com/viewsolution/18397100 
 
long long powmod(long long a, int p) {
    long long r = 1;
    while (p) {
        if (p & 1) r = r * a % MOD;
        p >>= 1; a = a * a % MOD;
    }
    return r;
}
 

namespace NTT {
    const long long P = modulo;
    const int K = 20;
    const int ROOT = 23;
    const int N = 1 << K;
    vector<int> W, invW;
    vector<int> rev;
 
    void init() {
        int n2 = N >> 1;
        W.resize(n2 + 1); W[0] = 1;
        W[1] = powmod(ROOT, (P - 1) / N);
        for (int i = 2; i <= n2; i++)
            W[i] = 1LL * W[i - 1] * W[1] % P;
        invW.resize(n2 + 1); invW[n2] = W[n2];
        for (int i = n2 - 1; i >= 0; i--)
            invW[i] = 1LL * invW[i + 1] * W[1] % P;
        rev.resize(N);
    }
 
    void transform(vector<int> &a, bool inv=false) {
        int k = 0; while ((1 << k) < a.size()) k++;
        int n = 1 << k;
        a.resize(n, 0);
        rev[0] = 0;
        for (int i = 1; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (k - 1));
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }
 
        vector<int> &twiddle = inv ? invW : W;
        for (int len = 2; len <= n; len <<= 1) {
            int half = len >> 1, diff = N / len;
            for (int i = 0; i < n; i += len) {
                int pw = 0;
                for (int j = i; j < i + half; j++) {
                    int v = 1LL * a[j + half] * twiddle[pw] % P;
                    a[j + half] = a[j] - v;
                    if (a[j + half] < 0) a[j + half] += P;
                    a[j] += v;
                    if (a[j] >= P) a[j] -= P;
                    pw += diff;
                }
            }
        }
 
        if (inv) {
            long long inv_n = powmod(n, P - 2);
            for (int &x : a) x = x * inv_n % P;
        }
    }
 
    void convolve(vector<int> &a, vector<int> &b) {
        int m = a.size() + b.size() - 1;
        a.resize(m, 0); transform(a);
        b.resize(m, 0); transform(b);
        for (int i = 0; i < a.size(); i++)
            a[i] = 1LL * a[i] * b[i] % P;
        transform(a, true);
        a.resize(m);
    }
};



void deal(){
	
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}



























































