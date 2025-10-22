#include<bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int,int>>>& adj)
{
    adj[u].push_back({v,w});
    //adj[v].push_back({u,w});
}

void dijkstra(int src, vector<vector<pair<int,int>>>& adj, vector<int>& dist,vector<int>&parent)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    dist[src] = 0;

    while(!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u]) continue;

        for (auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parent[v]=u;
            }
        }
    }
}
vector<int>path_print(int src ,int target,vector<int>&parent)
{
    vector<int>path;
    if(parent[target]==-1)
    return path;
   int curr=target;
    while(curr!=src)
    {
        path.push_back(curr);
        curr=parent[curr];

    }
    path.push_back(src);
    reverse(path.begin(),path.end());
    return path;
}


int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n);
    for (int i=0; i<m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w, adj);
    }

    vector<int> dist(n, INT_MAX),parent(n,-1);
    int src;
    cin >> src;
    int target;
    cin>>target;

    dijkstra(src, adj, dist,parent);
    vector<int>path=path_print(src,target,parent);
     for (int i=0; i<n; i++)
    {
        if (dist[i] == INT_MAX)
            cout << "Distance of node " << i << " from source " << src << " is INF\n";
        else
            cout << "Distance of node " << i << " from source " << src << " is " << dist[i] << "\n";
    }cout<<endl;
    if(path.size()==0)
    {
        cout<<"No path from "<<src<<" to "<<target<<"\n";
        return 0;
    }

     cout<<"Path from "<<src<<" to "<<target<<": ";
    for (int i=0; i<path.size(); i++)
    {
        cout<<path[i]<<" ";
    }
}
