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
#define ld long double
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10, 18);
ll modulo = pow(10,9) + 7;


// David Berard's Aho Corasick, slightly modified

#define NMAX 200200
#define ALPHA 26

int f[NMAX][ALPHA]; // down edges
int g[NMAX];        // fail links
int h[NMAX][ALPHA]; // compressed fail/down
ll val[NMAX];       // value at position i in 
int ord[NMAX];       // ord[i] = location of ith string
int qu[NMAX];        // queue 

struct AhoCorasick {
  int toi(char c) { return c-'a'; } // <- implement
  // int toi(char c) { return c - 'a'; } // char to int
  int sz;


  AhoCorasick() {
    	sz = 1;
    	fori(NMAX){
		memset(f[i], 0, sizeof f[i]);
		memset(h[i], 0, sizeof h[i]);
    	}
	memset(g, 0, sizeof g);
	memset(val, 0, sizeof val);
	memset(ord, 0, sizeof ord);
  }

  void insert(const string& s, int id, ll vl) {
    int u = 1;
    for (int i=0; i<(int)s.length(); ++i) {
      if (!f[u][toi(s[i])]) {
        f[u][toi(s[i])] = ++sz;
      }
      u = f[u][toi(s[i])];
    }
    val[u]+=vl;
    ord[id] = u;
  }

  void build() {
    int qcur=0, qlen=0;
    g[1] = 1;
    for (int j=0; j<ALPHA; ++j) {
      if (f[1][j]) {
        qu[qlen++] = f[1][j];
        g[f[1][j]] = 1;
        h[1][j] = f[1][j];
      } else {
        h[1][j] = 1;
      }
    }
    while (qcur < qlen) {
      int u = qu[qcur++];
      for (int j=0; j<ALPHA; ++j) {
        if (!f[u][j]) {
          h[u][j] = h[g[u]][j];
          continue;
        }
        h[u][j] = f[u][j];

        int p=g[u];
        while (p != 1 && f[p][j] == 0) p = g[p];
        if (f[p][j]) p=f[p][j];
        g[f[u][j]] = p;

        qu[qlen++] = f[u][j];
      }
    }
  }

  // find next occurrence of char nxt
  int next(int pos, char nxt) {
    /*
    int k = toi(nxt);
    while (pos != 1 && f[pos][k] == 0) pos = g[pos];
    if (f[pos][k]) return f[pos][k];
    return 1;
    */
    return h[pos][toi(nxt)];
  }

  // propagate val across failure edges
  void propagate() {
    int qcur=0, qlen=0;
    qu[qlen++] = 1;
    while (qcur < qlen) {
      int u = qu[qcur++];
      for (int j=0; j<ALPHA; ++j) {
        if (f[u][j]) {
          qu[qlen++] = f[u][j];
        }
      }
    }

    for (int i=0; i<qlen; ++i) {
      int u = qu[i];
      val[u] += val[g[u]];
    }
  }
};


void deal(){
	
}
 
 
int main(){
 	cin.tie(0);
 	ios_base::sync_with_stdio(0);
	deal();
}
