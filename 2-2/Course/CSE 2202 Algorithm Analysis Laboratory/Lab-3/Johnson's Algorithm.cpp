#include<bits/stdc++.h>
using namespace std;
void add_edge(int u, int v, int w, vector<vector<pair<int, int>> >&edges)
{
    edges[u].push_back({v, w});
}
bool Bellman_Ford(int src,vector<vector<pair<int,int>>>&adj,vector<int>&dist)
{
    int n=adj.size();
    dist[src]=0;
    for(int i=0;i<n-1;i++)
    {
        for(int u=0;u<n;u++)
        {
            for(auto & it:adj[u])
            {
                int v=it.first;
                int w=it.second;

                if(dist[u]!=INT_MAX&&dist[u]+w<dist[v])
                {
                    dist[v]=dist[u]+w;
                }
            }
        }
    }
    for(int u=0;u<n;u++)
    {
        for(auto & it:adj[u])
        {
            int v=it.first;
            int w=it.second;
            if(dist[u]!=INT_MAX&&dist[u]+w<dist[v])
            {
                cout<<"Graph contains negative weight cycle"<<endl;
                return false;
            }
        }
    }
    return true;
}
void Dijkstra(int src ,vector<vector<pair<int,int>>>&adj,vector<int>&dist)
{
    int n=adj.size();
    dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,src});
    while(!pq.empty()){
        int u=pq.top().second;
        int d=pq.top().first;
        pq.pop();
        if(d!=dist[u])continue;
        for(auto &it:adj[u])
        {
            int v=it.first;
            int w=it.second;
            if(dist[u]!=INT_MAX&&dist[u]+w<dist[v])
            {
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }   
        }

    }
}

vector<vector<int>> Johnsons_Algorithm(vector<vector<pair<int,int>>>&adj )
{
    int n=adj.size();
    vector<vector<pair<int,int>>>new_adj=adj;
    new_adj.push_back(vector<pair<int,int>>());
    for(int i=0;i<n;i++)
    {
        new_adj[n].push_back({i,0});
    }
    vector<int>dist(n+1,INT_MAX);
    if(!Bellman_Ford(n,new_adj,dist))
    {
        return {};
    }
    vector<vector<pair<int,int>>>reweighted_adj(n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            int u=i;
            int v=adj[i][j].first;
            int w=adj[i][j].second;
            int w_new=w+dist[u]-dist[v];
            reweighted_adj[u].push_back({v,w_new});
        }
    }
    vector<vector<int>>final_dist(n,vector<int>(n,INT_MAX));
    for(int i=0;i<n;i++)
    {
        vector<int>tdist(n,INT_MAX);
        Dijkstra(i,reweighted_adj,tdist);
        for(int j=0;j<n;j++)
        {
            if(tdist[j]!=INT_MAX)
            {
                final_dist[i][j]=tdist[j]-dist[i]+dist[j];
            }
        }
    }
    return final_dist;
}
int main()
{
    int n;
    cin>>n;
    vector<vector<pair<int,int>>>adj(n);
    int m;
    cin>>m;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w,adj);
    }
    vector<vector<int>>dist=Johnsons_Algorithm(adj);
    if(dist.size()==0)
    {
        return 0;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(dist[i][j]==INT_MAX)
            {
                cout<<"shortest distance from "<<i<<" to "<<j<<" is "<<"INF"<<endl;
            }
            else
            {
                cout<<"shortest distance from "<<i<<" to "<<j<<" is "<<dist[i][j]<<endl;
            }
        }
    }
}