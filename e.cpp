#include<bits/stdc++.h>
using namespace std;
int t,r,p,s; 
int h[1000005],len,idx[1000005],vis[1000005],af[1000005],low[1000005],sum=0;
//low[u]表示从起点 S 到节点 u 的最短距离d
//idx表示节点入度个数 tp
//af表示每个原节点属于哪个缩点后的连通块。
vector<int>nw[1000005];//缩点后的连通块包含的原节点编号
struct edge{
	int nxt,to,x,is;
}e[1000005];
struct node{
	int x,d;
	bool operator < (const node&a)const{
		return a.d<d;
	}
};
priority_queue<node>q;//low
queue<int>qq;//tp
void add(int x,int y,int z,int k){
	e[++len].to=y;
	e[len].nxt=h[x];
	e[len].x=z;
	e[len].is=k;
	h[x]=len;
}
void dfs(int x,int y){//缩点 
	vis[x]=1;
	nw[y].push_back(x);
	af[x]=y;
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(e[i].is==0)continue;
		if(!vis[v])dfs(v,y);
	}
}
void dij(int x){
	memset(low,0x3f3f3f3f,sizeof low);
	low[x]=0;
	memset(vis,0,sizeof vis);
	for(int i=1;i<=sum;i++){
		if(idx[i]==0){
			qq.push(i);
		}
	}
	while(!qq.empty()){
		int f=qq.front();
		qq.pop();
		for(int i=0;i<nw[f].size();i++){
			if(low[nw[f][i]]<0x3f3f3f3f){
				q.push({nw[f][i],low[nw[f][i]]});
			}
		}
		while(!q.empty()){
			node u=q.top();
			q.pop();
			if(vis[u.x])continue;
			vis[u.x]=1;
			for(int i=h[u.x];i;i=e[i].nxt){
				int v=e[i].to;
				if(e[i].is==1&&low[v]>low[u.x]+e[i].x){
					low[v]=low[u.x]+e[i].x;
					q.push({v,low[v]});
				}else if(e[i].is==0){
					low[v]=min(low[v],low[u.x]+e[i].x);
				}
			}
		}
		for(int i=0;i<nw[f].size();i++){
			for(int j=h[nw[f][i]];j;j=e[j].nxt){
				int v=e[j].to;
				if(e[j].is==1)continue;
				if(--idx[af[v]]==0){
					qq.push(af[v]);
				}
			}
		}
	}
}
int main(){
	cin>>t>>r>>p>>s;
	for(int i=1;i<=r;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z,1);
		add(y,x,z,1);
	}
	for(int i=1;i<=p;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z,0);
	}
	for(int i=1;i<=t;i++){
		if(!vis[i])dfs(i,++sum);
	}
	for(int i=1;i<=t;i++){
		for(int j=h[i];j;j=e[j].nxt){
			if(e[j].is)continue;
			int v=e[j].to;
			idx[af[v]]++;
		}
	}
	dij();
	for(int i=1;i<=t;i++){
		if(low[i]==0x3f3f3f3f){
			cout<<"NO PATH"<<'\n';
		}else{
			cout<<low[i]<<'\n';
		}
	}
	return 0;
} 
//缩点+拓扑排序+Dijkstra
