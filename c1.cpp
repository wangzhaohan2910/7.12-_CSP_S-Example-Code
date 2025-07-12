#include <bits/stdc++.h>
using namespace std;
int dfn[200001],low[200001],cnt,n,m,vis[200001],ans,a,b;
vector<int>z[200001];
void dfs(int x,int fa){
	dfn[x]=low[x]=++cnt;
	int c=0;
	for(int i=0;i<z[x].size();i++){
		if(!dfn[z[x][i]]){
			c++;
			dfs(z[x][i],x);
			low[x]=min(low[x],low[z[x][i]]);
			if(low[z[x][i]]>=dfn[x]&&dfn[b]>=dfn[z[x][i]]){
				vis[x]=1;
			}
		}else {
			low[x]=min(low[x],dfn[z[x][i]]);
		}
	}if(fa==0&&c==1)vis[x]=0;
}
int main() {
	cin>>n; 
	while(1){
		int x,y;
		cin>>x>>y;
		if(x==0&&y==0)break;
		if(x!=y){
			z[x].push_back(y);
			z[y].push_back(x);
		}
	}cin>>a>>b;
	dfs(a,0);
	for(int i=1;i<=n;i++){
		if(vis[i]==1&&i!=a){
			cout<<i;
			return 0;
		}
	}cout<<"No solution";
	return 0;
}
