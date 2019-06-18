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
#define ld long double
#define pb(a) push_back(a)
#define MAX (int)(pow(10,5) + 10)
const ll INF = 0x3f3f3f3f;
const ll inf = INF;
ll modulo = 998244353;

bool vis[MAX];
ll   fr[MAX];
vector<ll> g[MAX];
vector<ll> bfs;



void deal(){
	ll n, k, m;
	while(cin>>n>>k>>m){
		if(!n && !k && !m)
			return;
		fori(n)
			fr[i] = 0, vis[i] = 0, g[i].clear();
		bfs.clear();
		fori(k){
			ll ed;
			cin>>ed; --ed;
			fr[ed] = 1;
		}
		fori(m){
			ll hd, hr;
			cin>>hd>>hr; --hd, --hr;
			g[hd].pb(hr);
		}
		fori(n)
			if(fr[i])
				bfs.pb(i), vis[i] = 1;
		fori(bfs.size()){
			ll hd = bfs[i];
			forj(g[hd].size()){
				ll hr = g[hd][j];
				if(!vis[hr])
					vis[hr] = 1, bfs.pb(hr);
			}
		}
		bool good = 1;
		fori(n)
			if(!vis[i])
				good = 0;
		if(good)
			cout<<"yes\n";
		else	
			cout<<"no\n";
	}
}


int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}





// 4 1 1000 10
// 1 2 1
// ? 1 2
// ? 2 1
// + 2 4 1
// ? 1 4
// ? 4 1
// ? 4 2
// + 3 4 1
// ? 1 3
// ? 3 1








