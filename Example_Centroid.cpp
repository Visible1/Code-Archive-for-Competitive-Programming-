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
#define ll long long
#define double long double
#define MAX (int)(pow(10,5) + 10)
#define N 100000
#define pb(a) push_back(a)
// #define cout out
// #define cin in
ll inf = pow(10,9);
ll modulo = inf;
double eps = 1e-10;
ifstream in;
ofstream out;
namespace centroid{
	bool dlt[MAX]; 						// whether the node was deleted
	vector<ll> g[MAX];					// graph
	vector<vector<ll> > roots[MAX];	// all the parents (in centroid tree) of node i 
	vector<vector<ll> >	 dist[MAX];     // number of dudes at  distance  "k" from centre "i", with type "j"
	ll sz[MAX];						// sizes of subtrees
	void dfs(ll hd, ll pr){			// dfs to update sizes
		sz[hd] = 1;
		for(auto& hr : g[hd]){
			if(hr==pr || dlt[hr])
				continue;
			dfs(hr,hd);
			sz[hd]+=sz[hr];
		}
	}
	ll centre(ll hd,ll pr, ll siz){						// find the centre of the given tree 
		for(auto& hr : g[hd]){
			if(hr == pr || dlt[hr])
				continue;
			if(sz[hr] > siz/2 )
				return centre(hr,hd,siz);
		}
		return hd;
	}
	void push_root(ll hd, ll pr, ll root, ll dt, ll& ty, vector<ll>& track, ll& mx){		// push the chosen root to all the descendants in centroid tree
		roots[hd].push_back(vector<ll>({root, ty, dt}));
		track.pb(dt);
		mx = max(mx,dt);
		for(auto hr : g[hd]){
			if(hr==pr || dlt[hr])
				continue;
			push_root(hr,hd,root,dt+1, ty, track, mx);
		}
	}
	void create(ll st){									// create the centroid tree
		dfs(st,-1);
	//	cout<<"we started  "<<st<<endl;
		ll cnt = centre(st,-1,sz[st]);
		dlt[cnt] = 1;
//		cout<<"we at centre "<<cnt+1<<endl;
		dist[cnt] = vector<vector<ll> > (g[cnt].size() + 2);
		ll overall = 1;
		fori(g[cnt].size()){
			ll hr = g[cnt][i];
			if(!dlt[hr]){
				vector<ll> track;
				ll mx = 0;
				push_root(hr, cnt, cnt, 1, i, track, mx);
				++mx;
				dist[cnt][i].resize(mx, 0);
				overall = max(overall, mx);
				for(auto el : track)
					dist[cnt][i][el]++;
				for(ll j =1; j<mx; j++)
					dist[cnt][i][j] += dist[cnt][i][j-1];
/*				cout<<"for child "<<hr+1<<" the number of doods "<<endl;
				forj(mx)
					cout<<"up to distance "<<j<<" is "<<dist[cnt][i][j]<<endl;
				cout<<endl<<endl;
*/			}
		}
		{
			roots[cnt].pb(vector<ll>({cnt, (ll)g[cnt].size(), 0}));
			dist[cnt][g[cnt].size()].resize(1);
			dist[cnt][g[cnt].size()][0] = 1;
			ll last = dist[cnt].size()-1;
			dist[cnt][last].resize(overall,0);
			dist[cnt][last][0] = 1;
			fori(dist[cnt].size()-1)
				for(ll j = 1; j<dist[cnt][i].size(); j++)
					dist[cnt][last][j] += dist[cnt][last][j-1];
			for(ll i = 1; i<overall; i++)
				dist[cnt][last][i] += dist[cnt][last][i-1];
/*			cout<<"number of dudes for centre in total "<<endl;
			fori(overall){
				cout<<"up to distance "<<i<<" is "<<dist[cnt][last][i]<<endl;
			}
			cout<<endl<<endl;
*/
		}
	//	cout<<"we pushed the centre ( root ) "<<endl;
		if(sz[st]!=1)
			for(auto hr : g[cnt]){
				if(!dlt[hr])
					create(hr);
			}
	}
	ll find_up_to(ll hd, ll dt){
		ll ans = 0;
		for(auto& el: roots[hd]){
			auto root = el[0];
			auto ty   = el[1];
			auto dist_ = el[2];
			if(dt < dist_)
				continue;
			dist_ = dt - dist_;
			ll sz = min(dist_, (ll)dist[root][dist[root].size()-1].size()-1);
			ans += dist[root][dist[root].size()-1][sz];
			sz = min(dist_,(ll)dist[root][ty].size()-1 );
			ans -= dist[root][ty][sz];
		}
		return ans;
	}
	void ini(ll n){
		fori(n)
			dlt[i] = 0, g[i].clear(), roots[i].clear(), sz[i] = 0;
	}
}


void test(){
	// usage
	// add edges : g[i].pb(j)  
	// call create(0);
	ll n , k;
	cin>>n>>k;
	fori(n-1){
		ll a, b;
		cin>>a>>b;
		--a, --b;
		centroid::g[a].pb(b);
		centroid::g[b].pb(a);
	}
	if(k==1){
		cout<<2;
		return;
	}
	centroid::create(0);
	ll mx = 0;
	fori(n){
		ll ans = centroid::find_up_to(i, k/2) + 1;
		cout<<"up to for "<<i+1<<" is "<<ans<<endl;
	}
}


int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	test();
}

