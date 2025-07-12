#include<bits/stdc++.h>
using namespace std;
int dfn[1010],low[1010],cnt,f[1010],w[1010],v[1010],a[1010],in[1010],sum,dp[1010][1010],n,m,cost[1010], val[1010];
bool vis[1010];
stack<int> st;
vector<int> e[1010],g[1010];
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
		sum++;
		while(y=st.top()) {
			st.pop();
			f[y]=sum;
			vis[y]=0;
			if(x==y) break;
		}
	}
}

void dfs(int u){
	for(int i = cost[u];i <= m;i++) dp[u][i]=val[u];
	for(auto v:g[u]){
		dfs(v);
		for(int j = m;j >= cost[u];j--) for(int k = 0;k <= j-cost[u];k++) dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
	}
}

int main() {
	memset(dp,-0x3f,sizeof(dp)); 
	cin>>n>>m;
	for(int i = 1; i <= n; i++) cin>>w[i];
	for(int i = 1; i <= n; i++) cin>>v[i];
	for(int i = 1; i <= n; i++) {
		cin>>a[i];
		if(a[i])e[a[i]].push_back(i);
	}
	for(int i = 1; i <= n; i++)if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; i++) {
		int x=f[a[i]],y=f[i];
		cost[y]+=w[i],val[y]+=v[i];
		if (x!=y&&a[i]) {
			g[x].push_back(y);
			in[y]++;
		}
	}
	for(int i = 1;i <= sum;i++) if(!in[i]) g[0].push_back(i);
	dfs(0);
	cout<<dp[0][m];
}
