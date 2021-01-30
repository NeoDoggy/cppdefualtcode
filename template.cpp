#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define shimakaze ios_base::sync_with_stdio(0),cin.tie(0);
#define vi vector<int>
#define mii map<int,int>
#define debug(x) cout<<#x<<': '<<x<<',';
#define el cout<<endl;
#define pb(x) push_back(x)
const int NN=1e7+10;

using namespace std;

struct neo
{
	string abty="failed";
};

struct dinic
{
	static const int INFN=1e9+10;
	static const int N=1e2+10;

	struct edge
	{
		int to,cap,rev; //to graph end //reverse vector edge
		edge(){}
		edge(int TO,int CAP,int REV):to(TO),cap(CAP),rev(REV){}
	};

	vector<edge> g[N];

	void add_edge(int from ,int to ,int cap)
	{
		g[from].pb(edge(to,cap,(int)g[to].size()));
		g[to].pb(edge(from,0,(int)g[from].size()-1));
	}

	int n,s,t;

	void init(int _n,int _s,int _t)
	{
		n=_n,s=_s,t=_t;
		g->clear();
	}

	int level[N],iter[N];

	void bfs()
	{
		memset(level,-1,sizeof(level));
		level[s]=0;
		queue<int> que;que.push(s);
		while(!que.empty())
		{
			int tmp=que.front();
			que.pop();
			for(edge e:g[tmp])
			{
				if(e.cap>0&&level[e.to]==-1)
				{
					level[e.to]=level[tmp]+1;
					que.push(e.to);
				}
			}
		}
	}

	int dfs(int now,int flow)
	{
		if(now==t)
		{
			return flow;
		}
		for(int &i=iter[now];i<(int)g[now].size();i++)
		{
			edge &e=g[now][i];
			if(e.cap>0&&level[e.to]==level[now]+1)
			{
				int ret=dfs(e.to,min(flow,e.cap));
				if(ret>0)
				{
					e.cap-=ret;
					g[e.to][e.rev].cap=ret;
					return ret;
				}
			}
		}
		return 0;//failed
	}

	int flow()
	{
		int ret=0;
		while(1)
		{
			bfs();
			if(level[t]==-1)
				break;
			memset(iter,0,sizeof(iter));
			int tmp;
			while((tmp==dfs(s,INFN))>0)
			{
				ret+=tmp;//success
			}
		}
	}
};

struct ISAP
{
	static const int INFN=0x3f3f3f3f;
	static const int N=206;

	struct edge
	{
		int to,cap,rev; //to graph end //reverse vector edge
		edge(){}
		edge(int TO,int CAP,int REV):to(TO),cap(CAP),rev(REV){}
	};

	vector<edge> g[N];

	void add_edge(int from ,int to ,int cap)
	{
		g[from].pb(edge(to,cap,(int)g[to].size()));
		g[to].pb(edge(from,0,(int)g[from].size()-1));
	}

	int n,s,t;

	void init(int _n,int _s,int _t)
	{
		n=_n,s=_s,t=_t;
		g->clear();
	}

	int dis[N],iter[N],gap[N];
	bool vis[N];
	void bfs()
	{
		memset(dis,INFN,sizeof(dis));
		dis[t]=0;
		queue<int> que;
		que.push(t);
		while(!que.empty())
		{
			int tmp=que.front();
			que.pop();
			for(edge e:g[tmp])
			{
				if(e.cap==0&&dis[e.to]==INFN)
				{
					dis[e.to]=dis[tmp]+1;
					que.push(e.to);
				}
			}
		}
		if(dis[s]==INFN)
			return;
		memset(vis,0,sizeof(vis));
		vis[s]=1;
		que.push(s);
		while(!que.empty())
		{
			int tmp=que.front();
			que.pop();
			if(dis[tmp]!=INFN)
				gap[dis[tmp]]++;
			for(edge e:g[tmp])
			{
				if(e.cap>0&&!vis[e.to])
				{
					vis[e.to]=1;
					que.push(e.to);
				}
			}
		}
	}
	bool ok;
	int dfs(int now,int flow)
	{
		if(now==t)
			return flow;
		for(int &i = iter[now];i<(int)g[now].size();++i)
		{
			edge &e=g[now][i];
			if(e.cap>0&&dis[e.to]+1==dis[now])
			{
				int ret=dfs(e.to,min(e.cap,flow));
				if(ret>0)
				{
					e.cap-=ret;
					g[e.to][e.rev].cap+=ret;
					return ret;
				}
			}
		}
		if(!ok)
			return 0;
		--gap[dis[now]];
		if(gap[dis[now]]==0)
		{
			ok=0;
			return 0;
		}
		dis[now]=INFN;
		for(int i=0;i<(int)g[now].size();++i)
		{
			if(g[now][i].cap>0)
			{
				dis[now]=min(dis[now],dis[g[now][i].to]+1);
			}
		}
		if(dis[now]!=INFN)
			gap[dis[now]]++;
		iter[now]=0;
		return 0;
	}

	int flow()
	{
		int ret=0;
		bfs();
		ok=1;
		while(dis[s]<n&&ok)
		{
			ret+=dfs(s,INFN);
		}
		return ret;
	}
};

struct bipmatch
{
	static const int N=1e4+10;

	vector<int> g[N];
	bool v[N];
	int m[N];

	bool dfs(int x)
	{
		for(auto y:g[x])
		{
			if(v[y])
				continue;
			v[y]=true;
			if(m[y]==-1||dfs(m[y])==true)
			{
				m[y]=x;
				return true;
			}
		}
		return false;
	}

	int m_bipmatch(int x)
	{
		int ans=0;
		memset(m,-1,sizeof(m));
		for(int i=1;i<=x;i++)
		{
			memset(v,false,sizeof(v));
			ans+=dfs(i);
		}
		return ans;
	}
};

void solve()
{
	
	return ;
}

signed main()
{
	shimakaze;
	solve();
	return 0;
}
