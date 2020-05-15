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
#define MAX (int)(pow(10,6) + 10)	// TODO set according to max string size
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10,9);
ll alpha = 26; // TODO size of alphabet (26 for lowercase english letters)

vector<ll> mods({(ll)pow(10,9) + 7, (ll)pow(10,9) + 9});
vector<ll> inv[MAX];	// inverse of alpha^(i)

ll pow_mod(ll a, ll b, ll modulo){
	a = a%modulo;
	if(!a){
		return 0;
	}
	ll has = 1;
	for(ll i = 62; i>-1; i--){
		has*=has;
		has%=modulo;
		if(((ll)1<<i)&b)
			has*=a, has%=modulo;
	}
	return has;
}


void pre(){
	forj((ll)mods.size()){
		inv[0].pb(1);
	}
	for(ll i = 1; i<MAX; i++){
		forj((ll)mods.size()){
			ll curmod = mods[j];
			ll val = pow_mod(alpha, i, curmod);
			ll curinv = pow_mod(val, curmod-2, curmod); 
			inv[i].pb(curinv);
		}
	}
	
}


void getHashes(vector<vector<ll> >& all ,string& a){
	ll n = a.length();
	fori((ll)mods.size()){
		ll curmod  = mods[i];
		vector<ll> cur(n+1, 0);
		ll pv = alpha;
		for(ll j = 1; j<=n; j++){
			cur[j]  = cur[j-1] + (a[j-1]-'A')*pv;	// TODO change the hash function according to alphabet
			cur[j] %= curmod;
			pv *= alpha;
			pv %= curmod;
		}
		all.pb(cur);
	}
}

vector<ll> hash_interval(ll a, ll b, vector<vector<ll> >& all){
	vector<ll> ans;
	fori((ll)mods.size()){
		ll curmod = mods[i];
		ll cur = (all[i][b] - all[i][a-1] + curmod) % curmod * inv[a][i] % curmod;
		ans.pb(cur);
	}
	return ans;
}

void disp(vector<ll>& all){
	fori((ll)all.size()){
		cout<<all[i]<<" ";
	}
	cout<<endl;
}
 
void deal(){
	pre();
	string a,b;
	cin>>a>>b;
	
	vector<vector<ll> > hash1, hash2;
	getHashes(hash1, a);
	getHashes(hash2, b); 
	
	
	
	
}
 
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
//  test(); ECNA 2016 I
    deal();
}
 
 
 
 
 
 
 
