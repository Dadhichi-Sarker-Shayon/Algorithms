#include <bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &edges)
{
    edges[u].push_back({v, w});
}

void Bellman_Ford(int src, vector<vector<pair<int, int>>> &edges, vector<int> &dist)
{
    int n = edges.size();
    dist[src] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            for (auto it : edges[u])
            {
                int v = it.first;
                int w = it.second;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }
        }
    }
}
int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<pair<int, int>>> edges(m);
    for (int i = 0; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w, edges);
    }
    vector<int> dist(m, INT_MAX);
    int src;
    cin >> src;
    Bellman_Ford(src, edges, dist);
    for (int i = 0; i < m; i++)
    {
        if (dist[i] == INT_MAX)
            cout << "Distance of node " << i << " from source " << src << " is INF\n";
        else
            cout << "Distance of node " << i << " from source " << src << " is " << dist[i] << "\n";
    }
    return 0;
}