#include<bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int,int>>>& adj)
{
    adj[u].push_back({v,w});
    //adj[v].push_back({u,w});
}

void dijkstra(int src, vector<vector<pair<int,int>>>& adj, vector<int>& dist)
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
            }
        }
    }
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

    vector<int> dist(n, INT_MAX);
    int src;
    cin >> src;

    dijkstra(src, adj, dist);

    for (int i=0; i<n; i++)
    {
        if (dist[i] == INT_MAX)
            cout << "Distance of node " << i << " from source " << src << " is INF\n";
        else
            cout << "Distance of node " << i << " from source " << src << " is " << dist[i] << "\n";
    }
}
