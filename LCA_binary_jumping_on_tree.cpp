#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp setprecision(12)<<fixed
#define ss second
#define fori(v) for(ll i=0; i<v; i++)
#define forj(v) for(ll j=0; j<v; j++)
#define fork(v) for(ll k=0; k<v; k++)
#define forl(v) for(ll l=0; l<v; l++)
#define fort(v) for(ll t=0; t<v; t++)
#define forz(v) for(ll z=0; z<v; z++)
#define forx(v) for(ll x=0; x<v; x++)
#define ll long long 
#define double long double
#define MAX (int)(pow(10,6) + 10)
#define MAX2 (int)20
#define pb(a) push_back(a)
// #define cout out
// #define cin in
ll inf = pow(10,18);
ll modulo = pow(10,9) + 7;
double eps = 1e-10;
ifstream in;
ofstream out;
 
vector<ll> g[MAX];
ll lca[MAX][MAX2];
ll dep[MAX];
 
 
void dfs(ll hd, ll pr){
	lca[hd][0] = pr;
	for(auto hr : g[hd]){
		if(hr == pr)
			continue;
		dep[hr ] = dep[hd]+ 1; 
		dfs(hr, hd);
	}
}
 
void pre(ll n){
	for(ll j = 1; j<MAX2; j++)
		fori(n)
			lca[i][j]=  lca[lca[i][j-1]][j-1];
}
 
ll LCA(ll a, ll b){
	if(dep[a] < dep[b])
		swap(a,b);
	// a is deeper now, swim a upwards
	for(ll j = MAX2-1; j>-1; j--)
		if(dep[lca[a][j]] > dep[b])
			a = lca[a][j];
	if(dep[a] != dep[b])
		a = lca[a][0];
	for(ll j=MAX2-1; j>-1; j--)
		if(lca[a][j]!=lca[b][j])
			a = lca[a][j], b= lca[b][j];
	if(a!=b)
		a = lca[a][0];
	return a;
}
 
void test(){
	ll n , q;
	cin>>n>>q;
	vector<ll> dfs_;
	fori(n){
		ll ed;
		cin>>ed;
		if(ed == -1)
			dfs_.pb(i);
		else
			g[ed].pb(i);
	}
	for(auto el : dfs_)
		dfs(el, el);
	pre(n);
	forx(q){
		ll a, b;
		cin>>a>>b;
		if(lca[a][19] != lca[b][19])	
			cout<<"No\n";
		else{
			ll lc = LCA(a,b);
			if(lc==b)
				cout<<"Yes\n";
			else
				cout<<"No\n";
		}
	}
}

void deal(){
	// !!! call dfs(root, root) , dont put -1 as the parent of the root !!!
	// and then call pre() 
}
 
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	test();  // check whether lca of two nodes is the same
}
