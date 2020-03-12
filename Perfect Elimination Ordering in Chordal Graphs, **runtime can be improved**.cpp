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
#define MAX (int)(pow(10,5) + 10)
#define ch 340
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10,9);
ll modulo = 998244353 ;


void deal(){
	ll t;
	cin>>t;
	while(t--){
		ll n , m;
		cin>>n>>m;
		vector<pair<ll,ll> > edg;
		vector<set<ll> > g(n);
		map<ll,map<ll,ll> > edges;
		
		
		
		
		fori(m){
			ll a, b;
			cin>>a>>b;
			--a, --b;
			edg.pb(mp(a,b));
			g[a].insert(b);
			g[b].insert(a);
		}
			
			
		vector<ll> when(n, inf);
		vector<ll> row;
		
		
		vector<ll> tot(n, 0);
		vector<ll> cur(n); // cur bucket of ith item
		vector<ll> how_many(n, 0); // how many from each bucket will advance
		vector<ll> yeni(n); // new bucket of ith item
		set<pair<ll,ll> > all;	// all elements paired by (bucket_number, i)
		
		fori(n){
			cur[i] = n-1;
			tot[cur[i]]++;
			all.insert(mp(cur[i], i));
		}
		
		while(all.size()){
			auto hd = (*all.begin()).ss;
			when[hd] = n-row.size();
			row.pb(hd);
			all.erase(all.begin());
			
			for(auto hr : g[hd]){
				if(when[hr]!=inf){
					continue;
				}
				how_many[cur[hr]]++;
			}
			for(auto hr : g[hd]){
				if(when[hr]!=inf){
					continue;
				}
				yeni[hr] = cur[hr] - (tot[cur[hr]] - how_many[cur[hr]]);
			}
			for(auto hr : g[hd]){
				if(when[hr]!=inf){
					continue;
				}
				all.erase(mp(cur[hr], hr));
				how_many[cur[hr]] = 0;
				--tot[cur[hr]];
				
				cur[hr] = yeni[hr];
				++tot[cur[hr]];
				all.insert(mp(cur[hr], hr));
			}
		}	
		
		
		
		
		reverse(row.begin(), row.end());
/*		cout<<"\n\nthe row \n\n";
		fori(n){
			cout<<row[i]+1<<' ';
		}
		cout<<endl;
*/		bool fucked =0 ;
		fori(n){
			auto hd = i;
			vector<pair<ll, ll> > cur;
			for(auto& el : g[hd]){
				if(when[el] > when[hd]){
					edges[hd][el] = 1;
					cur.pb(mp(when[el], el));
				}
			}
			sort(cur.begin(), cur.end());
			for(ll i = 1; i<cur.size(); i++){
				auto hr1 = cur[0].ss;
				auto hr2 = cur[i].ss;
				if(g[hr1].find(hr2) == g[hr1].end()){
					fucked = 1;
				}
			}
		}
		
		if(fucked){
			cout<<"No solution\n";
		}
		else{
			fori(edg.size()){
				ll a = edg[i].ff, b = edg[i].ss;
				if(edges[a][b]){
					cout<<'^';
				}
				else{
					cout<<'v';
				}
			}
			cout<<'\n';
		}
	}
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}
