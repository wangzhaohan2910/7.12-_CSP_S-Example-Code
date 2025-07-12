#include <bits/stdc++.h>
using namespace std;
int n,m,u,v,h[1000005],dfn[1000005],low[1000005],t,cnt,cntt,x,c[1000005],f[1000005],mx,fla,inq[1000005],tt,hh[1000005],tmp[1000005],fl[1000005],summ[1000005];
vector<int> d,a[1000005],b;
bitset<1000005> in,vis;
struct Ed{
	int v,nxt;
};
Ed e[1000005],ee[1000005];
inline void add(int u,int v){
	e[++t]=Ed{v,h[u]};
	h[u]=t; 
}
inline void addd(int u,int v){
	ee[++tt]=Ed{v,hh[u]};
	hh[u]=tt;
}
stack<int> st;
void taja(int u){
	dfn[u]=low[u]=++cnt;
	st.push(u);
	in[u]=1;
	for(int i=h[u];~i;i=e[i].nxt){
		if(!dfn[e[i].v]){
			taja(e[i].v);
			low[u]=min(low[u],low[e[i].v]);
		}
		else if(in[e[i].v]) low[u]=min(low[u],dfn[e[i].v]);
	}
	if(dfn[u]==low[u]){
		cntt++;
		do{
			x=st.top();
			c[x]=cntt;
			a[cntt].push_back(x);
			in[x]=0;
			st.pop();
		}while(x!=u);
	}
}
queue<int> q;
signed main(){
	memset(hh,-1,sizeof(hh));
	memset(h,-1,sizeof(h));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		add(u,v);
	}
	for(int i=1;i<=n+1;i++) if(!dfn[i]) taja(i);
	for(int i=1;i<=n+1;i++) for(int j=h[i];~j;j=e[j].nxt)
		if(c[i]!=c[e[j].v]){
			addd(c[e[j].v],c[i]);
			inq[c[i]]++;
		} 
		else fl[c[i]]=1;
	for(int i=1;i<=cntt;i++) if(!inq[i]&&i!=c[n+1]) q.push(i);
	while(!q.empty()){
		x=q.front();
		q.pop();
		vis[x]=1;
		for(int i=hh[x];~i;i=ee[i].nxt) if(!(--inq[ee[i].v])&&ee[i].v!=c[n+1]) q.push(ee[i].v);
	}
	if(!fl[c[n+1]]){
		q.push(c[n+1]);
		f[c[n+1]]=1;
	} 
	while(!q.empty()){
		x=q.front();
		q.pop();
		vis[x]=1;
		for(int i=hh[x];~i;i=ee[i].nxt) if(!fl[ee[i].v]){
			f[ee[i].v]=min(f[ee[i].v]+f[x],36501);
			if(!(--inq[ee[i].v])) q.push(ee[i].v);
		} 	
	}
	for(int i=1;i<=cntt;i++) if(!vis[i]||f[i]==36501) d.push_back(i);
	if(!d.empty()){
		puts("zawsze");
		for(int i:d) for(int j:a[i]) b.push_back(j);
	} 
	else{
		for(int i=1;i<=cntt;i++){
			if(f[i]>mx&&!(c[n+1]==i&&(int)a[i].size()==1)){
				mx=f[i];
				b.clear();
				for(int j:a[i]) b.push_back(j);
			}
			else if(f[i]==mx) for(int j:a[i]) b.push_back(j);
		}
		printf("%d\n",mx);
	} 
	sort(b.begin(),b.end());
	if(!b.empty()&&b.back()==n+1) b.pop_back();
	printf("%d\n",(int)b.size());
	for(int i:b) printf("%d ",i);
	return 0;
}
