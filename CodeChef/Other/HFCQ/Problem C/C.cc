#include <bits/stdc++.h>

#define sd(x) scanf("%d",&x)
#define sd2(x,y) scanf("%d%d",&x,&y)
#define sd3(x,y,z) scanf("%d%d%d",&x,&y,&z)

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define foreach(it, v) for(__typeof((v).begin()) it=(v).begin(); it != (v).end(); ++it)
#define meta __FUNCTION__,__LINE__

#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);

using namespace std;

template<typename S, typename T> 
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
int l=v.size();for(int i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}

void tr(){cout << endl;}
template<typename S, typename ... Strings>
void tr(S x, const Strings&... rest){cout<<x<<' ';tr(rest...);}

typedef long long ll;
typedef pair<int,int> pii;

ll MOD = 1e9 + 7;
ll dp[106][201][3];
ll ways[106][201];
ll ways2[106][101];
ll C[310][310];
ll res[106][201][101];

void add(ll &x, ll y){
	x += y; if(x >= MOD) x -= MOD;
}

long long fast(long long a, long long b){
	long long ret = 1;
	while(b){
		if((b&1)) ret = (ret*a)%MOD;
		a = (a*a)%MOD;
		b >>= 1;
	}
	return ret;
}

void solve(){
	int r, f; sd2(r,f);
	
	ll ans = 0;
	for(int i = 100; i < 106; i++){
		for(int j = 0; j <= r; j++){
			for(int k = 0; k <= f; k++){
				add(ans, res[i][j][k]);
			}
		}
	}
	
	printf("%lld\n", ans);
}

int main(){
	int t; sd(t);
	
	C[0][0] = 1;
	for(int i = 1; i <= 310; i++){
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++){
			C[i][j] = (C[i-1][j] + C[i-1][j-1])%MOD;
		}
	}
	
	dp[0][0][0] = 1;
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 200; j++){
			for(int cnt = 0; cnt < 3; cnt++){
				add(dp[i+1][j+1][0], dp[i][j][cnt]);
				add(dp[i+2][j+1][0], dp[i][j][cnt]);
				add(dp[i+4][j+1][0], dp[i][j][cnt]);
				add(dp[i+6][j+1][0], dp[i][j][cnt]);
				if(cnt < 2) add(dp[i][j+1][cnt+1], dp[i][j][cnt]);
			}
		}
	}
	
	for(int i = 0; i < 106; i++){
		for(int j = 0; j < 201; j++){
			for(int cnt = 0; cnt < 3; cnt++){
				add(ways[i][j], dp[i][j][cnt]);
			}
		}
	}
	
	memset(ways2, 0, sizeof ways2);
	ways2[0][0] = 1;
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++){
			add(ways2[i][j+1], ways2[i][j]);
			add(ways2[i+1][j+1], ways2[i][j]);
			add(ways2[i+2][j+1], ways2[i][j]);
			add(ways2[i+4][j+1], ways2[i][j]);
			add(ways2[i+6][j+1], ways2[i][j]);
		}
	}
	
	for(int i = 100; i < 106; i++){
		for(int j = 0; j <= i; j++){
			for(int k = (j/6); k < 201; k++){
				for(int l = (i-j)/6; l < 101; l++){
					if(ways[j][k] != 0 and ways2[i-j][l] != 0){
						ll tmp = (ways[j][k] * ways2[i-j][l])%MOD;
						if(k > 0)
							tmp = (tmp * C[k+l-1][l])%MOD;
						add(res[i][k][l], tmp);
					}
				}
			}
		}
	}
	
	while(t--) solve();	
	return 0;
}
