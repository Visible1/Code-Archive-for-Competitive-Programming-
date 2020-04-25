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
#define MAX 502
#define MAX2 2020
#define pb(a) push_back(a)
#define M 1010
#define N 100100
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ld> vd;
typedef vector<vd> vvd;
typedef pair<ll, ll> pii;
typedef vector<pii> vpii;
const ll INF = 0x3f3f3f3f;
const ll inf =  2*pow(10,9);
ll modulo = pow(10,9) + 7;

// matrix structure for classic Matrix exponentiation type of problems


struct Matrix{ // !!! everything is an integer , and we take modulo while exponentiating (is available up to 2^30) / multiplying 
			   // n should be nonzero
	bitset<MAX>* rows;
	bitset<MAX>* cols;
	int n, m;
	Matrix(){}
	Matrix(int n, int m, bool id){			// if id is true (it must be a square matrix!!) identity matrix is created
		this->n = n , this->m = m;
		rows = new bitset<MAX>[n];
		cols = new bitset<MAX>[m];
		if(id)
			fori(n)
				rows[i].set(i), cols[i].set(i);
	}
	
	void set(ll i, ll j){
		rows[i].set(j);
		cols[j].set(i);
	}
	
	void Multiply(Matrix& A){
		int n1 = A.n , m1 = A.m;
		assert(m==n1);
		
		bitset<MAX>* r1 = new bitset<MAX>[n];
		bitset<MAX>* c1 = new bitset<MAX>[m1];
		
		for(int i = 0; i<n; i++)
			for(int j1=0; j1<m1; j1++){
				int ans = ((rows[i] & A.cols[j1]).count())&1;
				if(ans){
					r1[i].set(j1);
					c1[j1].set(i);
				}
			}
		rows = r1;
		cols = c1;
	}
	bitset<MAX>& operator [] (ll  i){
		return rows[i];
	}
};

void display(Matrix& A){
	cout<<"number of rows "<<A.n<<" number of columns "<<A.m<<endl;
	fori(A.n){
		forj(A.m)
			cout<<A[i][j]<<' ';
		cout<<'\n';
	}
}

#define Max_pow 62
Matrix exponentiate(Matrix& B, ll pv){
	Matrix start( B.n, B.n, 1);
	for(ll i = Max_pow; i>-1; i--){
		start.Multiply(start);
		if(((ll)1<<i) & pv)
			start.Multiply(B);
	}
	return start;
}

void deal(){
	
}

int main()  
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
} 

 






