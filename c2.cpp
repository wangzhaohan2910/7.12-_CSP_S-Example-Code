#include<bits/stdc++.h>
using namespace std;
int dfn[200010],low[200010],sum,a,b;
bool f[200010];
vector<int> e[500010];
void tarjan(int u) {
	low[u]=dfn[u]=++sum;
	int cnt=0;
	for(auto v:e[u])if(!dfn[v]){
		tarjan(v);
		low[u]=min(low[u],low[v]);
		if(a!=u&&low[v]>=dfn[u]&&dfn[b]>=dfn[v]) f[u]=1;
	} else low[u]=min(low[u],dfn[v]);
}
int main() {
	int n,u,v;
	cin>>n;
	while(1) {
		cin>>u>>v;
		if(u==0&&v==0) break;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	cin>>a>>b;
	tarjan(a);
	for (int i = 1; i <= n; i++)if (f[i]) return cout << i,0;
	return cout<<"No solution",0;
}
