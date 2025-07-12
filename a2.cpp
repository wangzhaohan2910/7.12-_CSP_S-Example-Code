#include<bits/stdc++.h>
using namespace std;
#define int long long
int dfn[100010],low[100010],cnt,f[100010],dp[100010],d[100010],size[100010],mod,sum,maxn,ans;
bool vis[100010];
stack<int> st;
vector<int> e[100010];
vector<int> g[100010];
void tarjan(int x) {
	dfn[x]=low[x]=++cnt;
	st.push(x);
	vis[x]=1;
	for(auto v:e[x]) {
		if(!dfn[v]) {
			tarjan(v);
			low[x]=min(low[v],low[x]);
		} else if(vis[v])low[x]=min(low[x],dfn[v]);
	}
	if(dfn[x]==low[x]) {
		int y;
		++sum;
		while(y=st.top()) {
			st.pop();
			f[y]=sum;
			size[sum]++;
			vis[y]=0;
			if(x==y) break;
		}
	}
}
signed main() {
	int n,m;
	cin>>n>>m>>mod;
	for(int i = 1,u,v; i <= m; i++) {
		cin>>u>>v;
		e[u].push_back(v);
	}
	for(int i = 1; i <= n; i++)if(!dfn[i]) tarjan(i);
	for(int i = 1;i <= n;i++) for(auto v:e[i]) if(f[v]!=f[i]) g[f[i]].push_back(f[v]);
	for(int i = 1;i <= sum;i++) sort(g[i].begin(),g[i].end()),g[i].erase(unique(g[i].begin(),g[i].end()),g[i].end());
	for(int i = sum; i; i--){
		if (dp[i] < size[i])dp[i]=size[i],d[i]=1;
        maxn=max(maxn,dp[i]);
        for(int v:g[i]){
            if(dp[v]<dp[i]+size[v])dp[v]=dp[i]+size[v],d[v]=d[i];
            else if(dp[v]==dp[i]+size[v])d[v]=(d[v]+d[i])%mod;
        }
	} 
	for(int i = 1;i <= sum;i++) if(dp[i]==maxn)ans=(ans+d[i])%mod;
	cout<<maxn<<'\n'<<ans<<'\n';
}
