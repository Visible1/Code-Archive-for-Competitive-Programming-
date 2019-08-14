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
#define MAX (int)(5*pow(10,3) + 10)
#define pb(a) push_back(a)
// #define cout out
// #define cin in
ll inf = pow(10,9);
ll INF = inf;
ll modulo = pow(10,9) + 7;
double eps = 1e-10;
ifstream in;
ofstream out;


////////////////////////////////////////////////////////////////////////////////
// Maximum flow
// taken from rumblefool (codechef handle)
////////////////////////////////////////////////////////////////////////////////
//*!
struct graph {
  typedef int flow_type; // **** flow type ****
  typedef int cost_type; // **** cost type ****
  struct edge {
    int src, dst;
    flow_type capacity, flow;
    cost_type cost;
    size_t rev;
  };
  vector<edge> edges;
  void add_edge(int src, int dst, flow_type cap, cost_type cost) {
    adj[src].push_back({src, dst, cap, 0, cost, adj[dst].size()});
    adj[dst].push_back({dst, src, 0, 0, -cost, adj[src].size()-1});
  }
  int n;
  vector<vector<edge>> adj;
  graph(int n) : n(n), adj(n) { }

  pair<flow_type, cost_type> min_cost_max_flow(int s, int t) {
    flow_type flow = 0;
    cost_type cost = 0;

    for (int u = 0; u < n; ++u) // initialize
      for (auto &e: adj[u]) e.flow = 0;

    vector<cost_type> p(n, 0);

    auto rcost = [&](edge e) { return e.cost + p[e.src] - p[e.dst]; };
    for (int iter = 0; ; ++iter) {
      vector<int> prev(n, -1); prev[s] = 0;
      vector<cost_type> dist(n, INF); dist[s] = 0;
      if (iter == 0) { // use Bellman-Ford to remove negative cost edges
        vector<int> count(n); count[s] = 1;
        queue<int> que; 
        for (que.push(s); !que.empty(); ) {
          int u = que.front(); que.pop();
          count[u] = -count[u];
          for (auto &e: adj[u]) {
            if (e.capacity > e.flow && dist[e.dst] > dist[e.src] + rcost(e)) {
              dist[e.dst] = dist[e.src] + rcost(e);
              prev[e.dst] = e.rev;
              if (count[e.dst] <= 0) {
                count[e.dst] = -count[e.dst] + 1;
                que.push(e.dst);
              }
            }
          }
        }
        for(int i=0;i<n;i++) p[i] = dist[i]; // added it
        continue;
      } else { // use Dijkstra 
        typedef pair<cost_type, int> node;
        priority_queue<node, vector<node>, greater<node>> que;
        que.push({0, s});
        while (!que.empty()) {
          node a = que.top(); que.pop();
          if (a.ss == t) break;
          if (dist[a.ss] > a.ff) continue;
          for (auto e: adj[a.ss]) {
            if (e.capacity > e.flow && dist[e.dst] > a.ff + rcost(e)) {
              dist[e.dst] = dist[e.src] + rcost(e);
              prev[e.dst] = e.rev;
              que.push({dist[e.dst], e.dst});
            }
          }
        }
      }
      if (prev[t] == -1) break;

      for (int u = 0; u < n; ++u) 
        if (dist[u] < dist[t]) p[u] += dist[u] - dist[t];

      function<flow_type(int,flow_type)> augment = [&](int u, flow_type cur) {
        if (u == s) return cur;
        edge &r = adj[u][prev[u]], &e = adj[r.dst][r.rev];
        flow_type f = augment(e.src, min(e.capacity - e.flow, cur));
        e.flow += f; r.flow -= f;
        return f;
      };
      flow_type f = augment(t, INF);
      flow += f;
      cost += f * (p[t] - p[s]);
    }
    return {flow, cost};
  }
};
void deal(){
	// usage 
	// declare: graph n5 (number of vertices)
	// add edges:  n5.add_edge(a,b, cost,price)
	// .ff to outpu max flow, .ss to output min cost : n5.min_cost_max_flow().ff 
}
 
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}
