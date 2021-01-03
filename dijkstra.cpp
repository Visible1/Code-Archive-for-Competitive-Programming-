#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp(a) setprecision(a)<<fixed
#define ss second
#define fori(v) for(int i=0; i<v; i++)
#define forj(v) for(int j=0; j<v; j++)
#define fork(v) for(int k=0; k<v; k++)
#define forl(v) for(int l=0; l<v; l++)
#define fort(v) for(int t=0; t<v; t++)
#define forz(v) for(int z=0; z<v; z++)
#define ll long long 
#define MAX (int)(pow(10,5)+ 10)
#define pb(a) push_back(a)
// #define cout out
// #define cin in
ll inf = pow(10,18);
ll modulo = 1000007;
double eps = 1e-6;
ifstream in;
ofstream out;

vector<pair<ll,ll> > g[MAX];

vector<ll> dijkstra(ll st, ll n){
	vector<ll> dt(n+10, inf);
	dt[st] = 0;
	priority_queue< pair<ll,ll> , vector<pair<ll,ll> > , greater<pair<ll,ll> > > pq;
	pq.push(mp(0, st));
	
	while(pq.size()){
		auto tp = pq.top();
		pq.pop();
		auto hardan = tp.ss;
		auto val = tp.ff;
		
		if(val != dt[hardan]){
			continue;
		}
		
		cout<<"minimum distance "<<hardan<<" "<<val<<endl;
		
		for(auto element : g[hardan]){
			auto hara = element.ff;
			if(dt[hardan] + element.ss < dt[hara] ){
				dt[hara]  = dt[hardan] + element.ss;
				pq.push(mp(dt[hara], hara));
			}
		}
	}
	
	return dt;
	
}

void deal(){
	ll n , m , s, t;
	cin>>n>>m>>s>>t;
	ll a, b;
	cin>>a>>b;
	vector<ll> workers(s);
	fori(s){
		cin>>workers[i];
	}
	vector<ll> clients(t);
	fori(t){
		cin>>clients[i];
	}
	
	fori(m){
		ll a, b, d;
		cin>>a>>b>>d;
		g[a].pb(mp(b,d));
		g[b].pb(mp(a,d));
	}
	
	dijkstra(a, n);
	
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
//	test();
	deal();
}



/* 
6 8 
1 2
2 3
3 4
4 1
2 5
3 5
1 6
4 6
*/
