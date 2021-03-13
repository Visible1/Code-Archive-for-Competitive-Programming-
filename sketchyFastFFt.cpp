#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define REP(i,a,b) for(ll i=a;i<b;i++)
// #define int long long
#define F(i, n) for (int i = 0; i < n; i++)
#define all(x)(x).begin(), (x).end()
#define show(A) for (auto i: A) cout << i << " "; cout << '\n';
 
using namespace std;
using ll = long long;
using vi = vector < int > ;
 
const int N = 2500005;
const int MOD = 998244353;
const int root = 961777435;
const int root_1 = 246144584;
const int root_pw = 1ll << 23;
/***************************code begins here*****************************/
int power(int x, unsigned int y) {  
    int res = 1;
    x = x % MOD;
    if (x == 0) return 0;
  
    while (y > 0)  
    { 
        if (y & 1)  
            res = (1LL*res*x) % MOD;
        y = y>>1;
        x = (1LL*x*x) % MOD;  
    }  
    return res;  
}
 
void fft(vector<int> & a, bool invert) {
    int n = a.size();
 
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
 
        if (i < j)
            swap(a[i], a[j]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % MOD);
 
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % MOD);
                a[i+j] = u + v < MOD ? u + v : u + v - MOD;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + MOD;
                w = (int)(1LL * w * wlen % MOD);
            }
        }
    }
 
    if (invert) {
        int n_1 = power(n,MOD-2);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % MOD);
    }
}
void PolyMult(vi &a,vi &v) {
    ll n=1;
    while(n<((ll)a.size())+((ll)a.size()))
    { 
        n<<=1;
    }
    vi fa(a.begin(),a.end());
    fa.resize(n,0);
    
    fft(fa,false);
    v.resize(n,0);
    REP(i,0,n)
    {
        v[i]=((1LL*fa[i]*fa[i])%MOD);
    }
    fft(v,true);
    return;
}

void deal(){
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    deal();
}

