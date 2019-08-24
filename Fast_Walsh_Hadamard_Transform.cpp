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
typedef long double ld;
const ll INF = 0x3f3f3f3f;
const ll inf =  pow(10,18);
ll modulo = pow(10,9) + 7;
#define MAX (int)(1<<20)

ll pow_mod(ll a, ll b){
	a = a%modulo;
	ll mx = 0;
	ll has = 1;
	for(ll i = 62; i>-1; i--){
		has*=has;
		has%=modulo;
		if(((ll)1<<i)&b)
			has*=a, has%=modulo;
	}
	return has;
}

ll inv(ll a){
	return pow_mod(a, modulo-2);
}


ll N = 1<<20;		// TODO change accordingly
ll invN = inv(N);	// TODO change accordingly

void fwht(vector<ll>& p, bool inv = false) {
	for (ll len=1; 2*len<=N; len*=2) {
		for (ll i=0; i<N; i+=2*len) {
			for (ll j=0; j<len; j++) {
				ll u = p[i+j];
				ll v = p[i+len+j];
				p[i+j] = u+v;				// TODO do % modulo if needed
				p[i+len+j] = u-v;			// TODO do % modulo if needed
			}
		}
	}
	if (inv) {
		fori(N) {
			p[i] = p[i] * invN;
			p[i] %= modulo;
		}
	}
}
    
bool prime[MAX];
vector<ll> all(MAX,0);
ll n;

void pre(){
	fori(MAX)
		prime[i] = 1;
	prime[0] = 0, prime[1] = 0;
	for(ll i = 2; i<MAX; i++)
		if(prime[i]){
			if(i<=n)
				all[i]++;
			for(ll j = 2*i; j<MAX; j+=i)
				prime[j] = 0;
		}
//	cout<<"we here bruh "<<endl;
		
} 
// fast walsh hadamard transform example 
// number of triplets of primes <= n such that a xor b xor c == 0
// the way to do walsh hadamard transform for two vectors p and q
// p = p'  using p' = H * p
// q = q'  using q' = H * q
// calculate p'q' by direct multiplication (p'q')[i] = p'[i] * q'[i]
// calculate pq using pq = H^-1  * (p'q') 
void test(){
	cin>>n;
	pre();
	vector<ll> all1;
	all1 = all;
//	cout<<"we before "<<endl;
	fwht(all);
//	cout<<"we after 1"<<endl;
	fwht(all1);
//	cout<<"we after 2"<<endl;
	fori(MAX)
		all[i]*=all1[i];
	fwht(all,1);
	ll ans = 0;
	fori(n+1)
		if(prime[i]){
		//	cout<<"for "<<i<<" answer is "<<all[i]<<endl;
			ans+=all[i];
		}
	ans/=6;
	cout<<ans;
}


void deal(){
	
}


int main()  
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	test();
	deal();
} 




























