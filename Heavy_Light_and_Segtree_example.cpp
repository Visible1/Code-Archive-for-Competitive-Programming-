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
#define double long double
#define pb(a) push_back(a)
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10,18);
ll modulo = pow(10,9)+7;

struct Segtree{			// !!! 1 based indexing !!!
	

	struct node{
		ll l , r, val, tagval;						 											
		bool tag;
		node(){}													
		node(ll l, ll r, ll val, ll tagval) : l(l), r(r), val(val), tagval(tagval), tag(0){}	// TODO add additional types	
		void integrate(){	// TODO integrate tagvalue to node value
			val += tagval;
		}
		node operator+(node other){		// TODO merge "val" of  children properly															
			return node(l, other.r, val+other.val ,0);									
		}
		void operator+=(node& other){	// TODO merge 2 tag (existing tag, new tag) values 						
			tagval += other.tagval;
		}
		void operator*=(node& other){	// TODO merge node value to query value
			// merge other's "val" to our "val" only !!!! otherwise need modification
			val += other.val;
		}
	};
	node* lazy;
	Segtree(ll len){
		++len;
		lazy = new node[4*len];
		init(1, 0, len-1);
	}
	void init(ll num, ll l , ll r){
		if(l==r){
			lazy[num] = node ( l, r, 0, 0 ); 
			return;
		}
		init((num<<1), l, (l+r)/2), init((num<<1)|1, (l+r)/2+1, r);
		lazy[num] = lazy[num<<1] + lazy[(num<<1)|1];
	}
	
	void pull(ll num){
		lazy[num] = lazy[num<<1] + lazy[(num<<1)|1];
	}
	
	void push(ll num){
		lazy[num].integrate();
		lazy[num].tag = 0;
		if(lazy[num].l != lazy[num].r){
			lazy[(num<<1)].tag = lazy[(num<<1)|1].tag = 1;
			lazy[(num<<1)] += lazy[num], lazy[(num<<1)|1]+=lazy[num];
		}
		lazy[num].tagval = 0; 
	}
	
	void upd(ll num, node& b){
		if(lazy[num].tag)	
			push(num);
		if(lazy[num].l > b.r || lazy[num].r < b.l)
			return;
		if(lazy[num].l >= b.l && lazy[num].r<=b.r){
			lazy[num] += b;
			push(num);
			return;
		}
		upd(num<<1, b),		upd((num<<1)|1, b);
		pull(num); 
	}
	
	void que(ll num, node& b){ 							
		if(lazy[num].l > b.r || lazy[num].r < b.l)		return ; 
		if(lazy[num].tag)								push(num);
		if(lazy[num].l >= b.l && lazy[num].r<=b.r){		b *= lazy[num]; return; }
		que(num<<1, b) , que((num<<1)|1, b);
	}
	
	~Segtree(){ delete[] lazy; }
};

	// u ll have to modify "node" struct accordingly
	// usage : 
	// Segtree lz
	// lz.init(1,1,n);
	// Updates:
	// Segtree::node query(l,r,0,tagval), lz.upd(1, query). !!! tagval is the update  ( so initialize it ) !!!
	// Queries:
	// Segtree::node query(l,r,val,   0), lz.que(1, query). !!! val    will be answer to query ( so initialize it ) !!
#define N 200200
vector<ll> adj[N];// Heavy Light Decomposition (Paths > Trees) -- henryx
// TESTED: cf1023/F, cf101908/L, cf102059/A, SPOJ/QTREE, SPOJ/QTREE3, cf101669/L
////////////////////////////////////////////////////////////////////////////////
//usage: 0) 1-INDEXED. 1) build tree in vector<int> adj[N]; 2) implement SegTree
//dealing with the lca: path is lca-exclusive! for lca-inclusive, remove
// if(pos[a]!=pos[b]), and change update(pos[b]+1,...) to update(pos[b],...)
//editing insert_path: 1) for query_path, change segt[]->update to segt[]->query
// these queries should be accumulated into some variable to be returned
// 2) insert_node/query_node should look similar to segt[ch[a]]->query(pos[a]);
//NOTE: if SegTree operation is not commutative, then require b to be an
// ancestor of a, and split each path uv into u->lca and v->lca before using HLD

  /* implement the rest of the segment tree */ 
namespace HLD { Segtree* segt[N];
  ll d[N], par[N], sub[N], sz[N], root[N], ch[N], pos[N]; ll dn, cn;
  ll dfs(ll u, ll p) { d[u] = d[par[u]=p]+1; sub[u] = 1;
    for (ll x:adj[u]) if (x!=p) sub[u] += dfs(x,u); return sub[u]; }
  void hld(ll u, ll p) { if (dn == cn) { root[cn]=u; sz[cn++]=0; }
    pos[u] = sz[ch[u]=dn]++; ll b=-1, c=-1;
    for (ll x:adj[u]) if (x!=p && sub[x]>b) b=sub[c=x]; if (c!=-1) hld(c,u);
    for (ll y:adj[u]) if (y!=p && y!=c) { dn++; hld(y,u); } }
  void build(ll r) { d[0] = dn = cn = 0; dfs(r,0); hld(r,0);
    for (ll i=0; i<cn; i++) segt[i] = new Segtree(sz[i]); }
  // Returns LCA of path ab, MODIFY for insert_node, query_path, query_node
  ll insert_path(ll a, ll b, ll v) { // please expand this when typing
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      Segtree::node query(0, pos[a], 0, v);
	  segt[ch[a]]->upd(1, query); a = par[root[ch[a]]]; }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      Segtree::node query(pos[b]+1, pos[a], 0, v);
      segt[ch[a]]->upd(1, query); } return b; } 
    ll query_path(ll a, ll b, ll v) { // please expand this when typing
    Segtree::node ans(-1, -1, 0, 0);
    while (ch[a] != ch[b]) { if (d[root[ch[a]]] < d[root[ch[b]]]) swap(a,b);
      Segtree::node query(0, pos[a], 0, v);
	  segt[ch[a]]->que(1, query); a = par[root[ch[a]]]; 
	  ans *= query;
	  }
    if (pos[a] != pos[b]) { if (d[a] < d[b]) swap(a,b);
      Segtree::node query(pos[b]+1, pos[a], 0, v);
      segt[ch[a]]->que(1, query); 
	  ans *= query;} return ans.val; } 
} // returns lca

void test(){
	ll n;
	cin>>n;
	fori(n-1){
		ll a, b;
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	HLD::build(1);
	ll q;
	cin>>q;
	forl(q){
		ll ty;
		cin>>ty;
		if(ty == 1){
			ll a, b, vl;
			cin>>a>>b>>vl;
			HLD::insert_path(a,b,vl);
		}
		else{
			ll a, b;
			cin>>a>>b;
			cout<<HLD::query_path(a, b, -1)<<'\n';
		}
	}
}

int main(){
//	cin.tie(0);
//	ios_base::sync_with_stdio(0);
	deal();
}
