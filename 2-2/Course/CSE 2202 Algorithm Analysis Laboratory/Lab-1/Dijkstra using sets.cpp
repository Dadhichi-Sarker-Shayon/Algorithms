#include <bits/stdc++.h>
using namespace std;
void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &edges)
{
    edges[u].push_back({v, w});
    // edges[v].push_back({u, w});
}

void Dijkstra(int src, vector<vector<pair<int, int>>> &adj, vector<int> &dist)
{
    set<pair<int, int>> s;
    s.insert({0, src});
    dist[src] = 0;
    while (!s.empty())
    {
        int u = s.begin()->second;
        s.erase(s.begin());
        for (auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;
            if (dist[u] + w < dist[v])
            {
                if (dist[v] != INT_MAX)
                {
                    s.erase(s.find({dist[v], v}));
                }
                dist[v] = dist[u] + w;
                s.insert({dist[v], v});
            }
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w, adj);
    }
    vector<int> dist(n, INT_MAX);
    int src;
    cin >> src;
    Dijkstra(src, adj, dist);
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
            cout << "Distance of node " << i << " from source " << src << " is INF\n";
        else
            cout << "Distance of node " << i << " from source " << src << " is " << dist[i] << "\n";
    }
    return 0;
}