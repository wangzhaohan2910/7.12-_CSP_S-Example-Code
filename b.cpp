#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Ed{
	int v,nxt;
};
Ed e[1000005];
int n,m,h[100005],u,v,dfn[100005],low[100005],t,cnt,cntt[100005],x;
long long sum[100005];
inline void add(int u,int v){
	e[++t]=Ed{v,h[u]};
	h[u]=t;
}
bitset<100005> vis;
void taja(int u,int fa){
	dfn[u]=low[u]=++cnt;
	int c=0,cnttt=0;
	cntt[u]=1;
	for(int i=h[u];~i;i=e[i].nxt){
		if(!dfn[e[i].v]){
			c++;
			taja(e[i].v,u);
			low[u]=min(low[u],low[e[i].v]);
			if(low[e[i].v]>=dfn[u]){
				vis[u]=1;
				sum[u]+=cntt[e[i].v]*(n-cntt[e[i].v]);
				cnttt+=cntt[e[i].v];
			} 
			cntt[u]+=cntt[e[i].v];
		}
		else low[u]=min(low[u],dfn[e[i].v]);
	}
	if(u==fa&&c==1) vis[u]=0;  
	if(vis[u]) sum[u]+=(n-cnttt-1)*(cnttt+1);
	else sum[u]=n-1;
}
signed main(){
	memset(h,-1,sizeof(h));
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&u,&v);
		add(u,v);
		add(v,u);
	}
	taja(1,1);
	for(int i=1;i<=n;i++) printf("%lld\n",sum[i]+n-1);
	return 0;
}
