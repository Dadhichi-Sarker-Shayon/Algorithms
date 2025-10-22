#include<bits/stdc++.h>
using namespace std;
void add_edge(int u,int v,int w,vector<vector<pair<int,int>>>& graph)
{
    graph[u].push_back({v,w});
    graph[v].push_back({u,w});
}
void prims_algorithm(int src,vector<vector<pair<int,int>>>&graph)
{
    vector<pair<int,int>>mst;
    int v=graph.size();
    vector<int>visited(v,0);
    int lowest_cost=0;
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>>tupq;
    tupq.push({0,src,-1});
    while(!tupq.empty())
    {
        int cost,node,parent;
        tie(cost,node,parent)=tupq.top();
        tupq.pop();
        if(visited[node])continue;
        visited[node]=1;
        lowest_cost+=cost;
        if(parent!=-1)
        {
            mst.push_back({parent,node});
        }
        for(auto it:graph[node])
        {
            int v=it.first;
            int w=it.second;
            if(!visited[v])
            {
                tupq.push({w,v,node});
        
            }
        }


    }
    cout<<"Minimum cost is "<<lowest_cost<<endl;
    cout<<"Edges in MST are "<<endl;
    for(auto it:mst)
    {
        cout<<it.first<<" - "<<it.second<<endl;
    }
  
}
int main()
{
    int v,e;
    cin>>v>>e;
    vector<vector<pair<int,int>>>graph(v);
    for(int i=0;i<e;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        add_edge(u,v,w,graph);
    }
    int src;
    cin>>src;
    prims_algorithm(src,graph);
    return 0;
}