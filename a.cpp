#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,mod,pp,us[100001],a[100001],dfn[100001],f[100001],dp[100001],p[100001],id[100001],low[100001],vis[100001],bb[100001];
int cnt,cntt,cmp,ans;
stack<int>s;
vector<int>z[100001];
vector<int>z1[100001];
map<pair<int,int>,bool>mp;
void dfs(int x){
	dfn[x]=++cnt;
	low[x]=dfn[x]; 
	s.push(x);
	vis[x]=1;
	for(int i=0;i<z[x].size();i++){
		if(!dfn[z[x][i]]){
			dfs(z[x][i]);
			low[x]=min(low[x],low[z[x][i]]);
		}else if(vis[z[x][i]]){
			low[x]=min(low[x],dfn[z[x][i]]);
		} 
	}if(dfn[x]==low[x]){
		cntt++;
		while(1){
			int y=s.top();
			s.pop();
			id[y]=cntt;
			vis[y]=0;
			a[cntt]++;
			if(x==y)break;
		}
	}
}signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>mod;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		z[x].push_back(y);
	}for(int i=1;i<=n;i++){
		f[i]=1;
		if(!dfn[i]){
			dfs(i);
		}
	}for(int i=1;i<=n;i++){
		for(int j=0;j<z[i].size();j++){
			if(id[i]!=id[z[i][j]]&&!mp[{id[i],id[z[i][j]]}]){
				mp[{id[i],id[z[i][j]]}]=1;
				p[id[z[i][j]]]++;
				z1[id[i]].push_back(id[z[i][j]]);
			}			
		}
	}/*for(int i=cntt;i>=1;i--){
		for(int j=0;j<z1[i].size();j++){
			int te=z1[i][j];
			if(us[te]==i)continue;
			us[te]=i;
			if(dp[te]<dp[i]+a[te])dp[te]=dp[i]+a[te],f[te]=f[i];
			else if(dp[te]==dp[i]+a[te])f[te]+=f[i],f[te]%=mod;
		}
	}*/
	queue<int>q;
	for(int i=1;i<=n;i++){
		if(p[i]==0)q.push(i);
		dp[i]=a[i];
	}while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<z1[u].size();i++){
			int te=z1[u][i];
			p[te]--;
			if(dp[te]<dp[u]+a[te])dp[te]=dp[u]+a[te],f[te]=f[u];
			else if(dp[te]==dp[u]+a[te])f[te]+=f[u],f[te]%=mod;			
			if(p[te]==0)q.push(te);
		}
	}
	for(int i=1;i<=n;i++){
		if(ans<dp[i])ans=dp[i],pp=f[i];
		else if(ans==dp[i])pp+=f[i],pp%=mod;
	}cout<<ans<<"\n"<<pp;
	return 0;
}/*
6 6 20070603
1 2
2 1
1 3
2 4
5 6
6 4
*/
