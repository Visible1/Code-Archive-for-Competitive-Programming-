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
#define ll int
#define double long double
#define pb(a) push_back(a)
#define MAX (int)(pow(10,7) + 10)
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10,9);
ll modulo = pow(10,9)+7;

#define N 100100
#define M 100100

//*/
////////////////////////////////////////////////////////////////////////////////
// Array-based undirected sparse graph - each edge has two copies: e <=> e^1
////////////////////////////////////////////////////////////////////////////////
// int first[N]; // first[u] is the first edge in the adjacency list of u.
// int nxt[2*M]; // nxt[e] is the next edge in the same adjacency list as e.
// int ep[2*M];  // ep[e] is the vertex whose adjacency list e is in. e^1 is
//          the reverse twin of e, so ep[e^1] is its other endpoint.
//
// memset(first, -1, sizeof first); // m edges are input as pairs of endpoints
// for(int e=0; e<2*m; ++e) cin>>ep[e], nxt[e] = first[ep[e]], first[ep[e]] = e;
//
// for(int e=first[u]; e!=-1; e=nxt[e]) int v = ep[e^1]; // scan neighbours of u
////////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////
// Maximum flow
////////////////////////////////////////////////////////////////////////////////
//*!
namespace n5 {
//*/
// data structures and helper functions common to all flow routines
int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];
void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
  nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
  nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
 
// Max flow without costs, USAGE: 1) init(); 2) add edges, 3) ll flow=0; and 4)
// for (ll del=INF; del; del/=2) while (ll df=mf_update(s, t, del)) flow+=df;
// Then if you want to extract a min cut: for (int e = 0; e < m; ++e)
// if (par[ep[e]] != -1 && par[ep[e^1]] == -1) cut.push_back(e);
// If you want to recover flow paths: get set of edges with flo[e] > 0.
// E^2logC in general, E*flow on integer capacity graphs
ll mf_update(int s, int t, ll del=1) {
  ll df[N]; memset(df, 0, sizeof df); memset(par, -1, sizeof par);
  queue<int> q; q.push(s); par[s] = -2; df[s] = INF;
  while (!q.empty()) { ll cf; int u = q.front(); q.pop();
    for (int v, e = first[u]; e != -1; e = nxt[e])
      if (par[v=ep[e^1]] == -1 && (cf = cap[e]-flo[e]) >= del)
        q.push(v), par[v] = e, df[v] = min(df[u], cf); }
  if (par[t] == -1) return 0;
  for (int e, i = t; i != s; i = ep[e])
    e = par[i], flo[e] += df[t], flo[e^1] -= df[t];
  return df[t]; }
 
// Dinic's fast maximum flow: tested on NAIPC 2015 F but not theoretically
// proven to be floating-point-safe.
// USAGE: 1) init(); 2) add edges
// 3) ll flow=0; while (bfs(S, T)) flow += dfs(S, T, INF);
// V^2E in general, min(V^(2/3),sqrt(E))E on unit caps, sqrt(V)E on bipartite
int L[N], cur[N];
bool bfs(int s, int t) {
  memset(L, INF, sizeof L);
  queue<int> q; q.push(s); L[s] = 0;
  while (!q.empty()) { int u = q.front(); q.pop();
    for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
      if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
        q.push(v), L[v] = L[u]+1;
  } return L[t] < INF; }
ll dfs(int u, int t, ll f) {
  if (u == t) return f;
  ll cf, df = 0;
  for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
    if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
      cf = dfs(v, t, min(cap[e]-flo[e], f-df));
      flo[e] += cf; flo[e^1] -= cf; df += cf;
    } return df; }
 
// Minimum cost maximum flow, assuming there are no negative cost cycles
// USAGE: 1) init(); 2) add edges, 3) mcf_pot_init(numV) and 4)
// ll price=0,flow=0; while (ll df = mcf_update(s, t, price, numV)) flow += df;
//! for sparse graphs, may help to change Dijkstra from O(N^2) to O(M*lgN)
//! code is provided in comments
/*!
int q[N], inq[N];
#define BUBL { \
    t = q[i]; q[i] = q[j]; q[j] = t; \
    t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }
*/
bool vis[N]; ll pot[N], dist[N];
void mcf_pot_init(int n) { memset(pot, 0, sizeof pot);
  // if all edge costs >= 0, we can safely return before the Bellman-Ford here
  for (int k = 1; k < n; ++k) for (int e = 0; e < m; ++e)
    if (cap[e]) pot[ep[e^1]] = min(pot[ep[e^1]], pot[ep[e]] + cost[e]); }
ll mcf_update(int s, int t, ll& price, int n) {
  memset(vis, 0, sizeof vis); memset(dist, INF, sizeof dist); dist[s] = 0;
  /*!
  memset(inq, -1, sizeof inq);
  int qs = 0; inq[q[qs++] = s] = 0;
  while (qs) {
    int u = q[0]; inq[u] = -1;
    q[0] = q[--qs];
    if( qs ) inq[q[0]] = 0;
    for( int i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 ) {
      if( j + 1 < qs && dist[q[j + 1]] < dist[q[j]] ) j++;
      if( dist[q[j]] >= dist[q[i]] ) break;
      BUBL; }
    if (vis[u] == 1) continue; vis[u] = 1;
    for (int e = first[u]; e != -1; e = nxt[e]) { int v = ep[e^1];
      if (flo[e] < cap[e] && dist[v] > dist[u] + pot[u] - pot[v] + cost[e]) {
        dist[v] = dist[u] + pot[u] - pot[v] + cost[e], par[v] = e;
        if( inq[v] < 0 ) { inq[q[qs] = v] = qs; qs++; }
          for( int i = inq[v], j = ( i - 1 )/2, t;
            dist[q[i]] < dist[q[j]]; i = j, j = ( i - 1 )/2 )
              BUBL;
    }
  }
  }
  */
  //! replaces the below section
  for (int u = s; u != -1; ) { vis[u] = true; // do Dijkstra
    for (int e = first[u]; e != -1; e = nxt[e]) { int v = ep[e^1];
      if (flo[e] < cap[e] && dist[v] > dist[u] + pot[u] - pot[v] + cost[e])
        dist[v] = dist[u] + pot[u] - pot[v] + cost[e], par[v] = e; }
    u = -1; ll best = INF;
    for (int i = 0; i < n; ++i) if (!vis[i] && best>dist[i]) best=dist[u=i]; }
  //!
  if (dist[t] >= INF) return 0; ll df = INF;
  for (int e, i = t; i != s; i = ep[e])
    e = par[i], df = min(df, cap[e] - flo[e]);
  for (int e, i = t; i != s; i = ep[e])
    e = par[i], flo[e] += df, flo[e^1] -= df, price += df*cost[e];
  for (int i = 0; i < n; ++i) pot[i] = min(INF, dist[i] + pot[i]);
  return df; }
//*!
}
//*/
////////////////////////////////////////////////////////////////////////////////
// Maximum flow with lower bounds/demands
////////////////////////////////////////////////////////////////////////////////
// Create a new graph G' with source s' and sink t', where
// -all nodes and edges from the original graph G are retained
// -cap of s' to v: sum(demands into v)
// -cap of v to t': sum(demands from v)
// -cap of edge: (cap)-(demand) in original graph G
// -cap of t to s: infinity
// Run max flow on G' from s' to t'.
// A flow for G is feasible if the max flow in G' is saturated.
// To find the flow, run max flow on G, from the sink to the source, where
// -cap of v to u: (flow of u to v)
// Now subtract the edge values from this flow from the sum of (original max
// flow on G) and (demands on edges in G).
////////////////////////////////////////////////////////////////////////////////
// ifstream in;
// ofstream out;
// #define cin in
// #define cout out

void test(){
	ll n, m , p;
	cin>>n>>m>>p;
	n5::init();
	// 1 to n are children
	// n+1 to n+m are toys so bijection [1 m] - [n+1  n+m]
	ll index = n+m+1;
	ll S = index++, T = index++;
	fori(n){
		ll k;
		cin>>k;
		// child i is willing to play
		forj(k){
			ll ty;
			cin>>ty;
			n5::add_edge(n+ty, i+1);
		}
		n5::add_edge(i+1, T);
	}
	vector<bool> seen(m+1, 0);
	fori(p){
		ll l;
		cin>>l;
		vector<ll> all(l);
		forj(l)
			cin>>all[j], seen[all[j]] = 1;
		ll r;
		cin>>r;
		ll cur = index++;
		n5::add_edge(S, cur, r);
		forj(l)
			n5::add_edge(cur, n+all[j]);
	}
	for(ll i =1; i<=m; i++)
		if(!seen[i])
			n5::add_edge(S, n+i);
	ll flow=0; 
	while (n5::bfs(S, T)) flow += n5::dfs(S, T, INF);
	cout<<flow;
}

void deal(){
	
}

int main(){
//  cin.tie(0);
//  ios_base::sync_with_stdio(0);
//  test(); ECNA 2016 I
    deal();
}



