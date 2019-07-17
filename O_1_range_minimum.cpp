#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp(x) setprecision(x)<<fixed
#define ss second
#define fori(v) for(lli i=0; i<v; i++)
#define forj(v) for(lli j=0; j<v; j++)
#define fork(v) for(lli k=0; k<v; k++)
#define forl(v) for(lli l=0; l<v; l++)
#define fort(v) for(lli t=0; t<v; t++)
#define forz(v) for(lli z=0; z<v; z++)
#define forx(v) for(lli x=0; x<v; x++)
#define lli long long int
#define MAX 100010
#define ch  350
#define double long double
template<typename T>
class range_minimum_query{
public:
	std::vector<T> data;
	std::vector<std::vector<int> > block;
	std::vector<int> sblock;
	std::vector<int> lookup;
	int N;
	int lg;
	int min(int a,int b){
		return data[b]<data[a]?b:a;
	}
	range_minimum_query(){}
	range_minimum_query(std::vector<T> &t){
		data=t;
		N=data.size();
		lg=32-__builtin_clz(N);
		block.assign((N+lg-1)/lg,std::vector<int>(lg,0));
		for(int i=0;i<N;i++){
			if(i%lg==0)
				block[i/lg][0]=i;
			block[i/lg][0]=min(i,block[i/lg][0]);
		}
		for(int j=1;j<lg;j++)
			for(int i=0;i<block.size();i++)
				block[i][j]=min(block[i][j-1],block[i+(i+(1<<(j-1))<block.size()?(1<<(j-1)):0)][j-1]);
		sblock.assign(N,0);
		std::vector<int> st;
		for(int i=0;i<block.size();i++){
			st.clear();
			for(int j=i*lg;j<N&&j<i*lg+lg;j++){
				while(!st.empty()&&data[j]<data[st.back()])
					st.pop_back();
				sblock[j]=1<<(i*lg+lg-j-1);
				if(!st.empty())
					sblock[j]|=sblock[st.back()];
				st.push_back(j);
			}
		}
		lookup.assign(1<<lg,0);
		for(int i=1,ans=lg-1;i<(1<<lg);i++){
			if(1<<(lg-ans)<=i)
				ans--;
			lookup[i]=ans;
		}
	}
	int q(int l,int r){
		if(r<l)
			swap(l,r);
		int l1=l/lg+1;
		int r1=r/lg-1;
		int ans=l;
		int t;
		if(l1<=r1){
			t=lg-lookup[r1-l1+1]-1;
			ans=min(ans,min(block[l1][t],block[r1-(1<<t)+1][t]));
		}
		t=l1*lg-1<r?l1*lg-1:r;
		ans=min(ans,lookup[sblock[t]&(~(((1<<(l-(l1*lg-lg)))-1)<<(l1*lg-l)))]+l1*lg-lg);
		t=r;
		l=l>r1*lg+lg?l:r1*lg+lg;
		ans=min(ans,lookup[sblock[t]&(~(((1<<(l-(r1*lg+lg)))-1)<<(r1*lg+(lg<<1)-l)))]+r1*lg+lg);
		return ans;
	}
};
void test(){
	int n;
	cin>>n;
	vector<int> all(n);
	fori(n)	cin>>all[i];
	range_minimum_query<int> shit(all);
	int q;
	cin>>q;
	fori(q){
		int l,r;
		cin>>l>>r;
		cout<<all[shit.q(l,r)]<<'\n';
	}
}
void deal(){
	
}
int main(){
	
}
