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
#define forx(v) for(int x=0; x<v; x++)
#define fory(v) for(int y=0; y<v; y++)
#define ll long long
#define lll __int128
#define ld long double
#define pb(a) push_back(a)
#define mt make_tuple
// #define cout out
// #define cin in
ll inf = pow(10, 18);
ll modulo = pow(10, 9) + 7;
ld eps = 1e-13;
ifstream in;
ofstream out;

ll pow_mod(ll a, ll b){
	a = a%modulo;
	ll has = 1%modulo;
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

#define MAX 100'100

ll fkt[MAX];
ll invfkt[MAX];

void pre(){
	fkt[0] = 1;
	for(ll i = 1; i<MAX; i++){
		fkt[i] = fkt[i-1] * i % modulo;
	}
	invfkt[MAX-1] = inv(fkt[MAX-1]);
	for(ll i = MAX-2; i>-1; i--){
		invfkt[i] = invfkt[i+1] * (i+1) % modulo;
	}
}

ll choose(ll n, ll k){
	return fkt[n] * invfkt[k] % modulo * invfkt[n-k] % modulo;
}

void deal(){
	
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
	
	return 0;
}
 
 
