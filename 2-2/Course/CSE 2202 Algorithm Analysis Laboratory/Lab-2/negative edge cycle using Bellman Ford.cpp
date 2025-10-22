#include <bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &edges)
{
    edges[u].push_back({v, w});
}

bool Bellman_Ford(int src, vector<vector<pair<int, int>>> &edges)
{

    int n = edges.size();
    vector<int> dist(n, INT_MAX);
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

    for (int u = 0; u < n; u++)
    {
        for (auto it : edges[u])
        {
            int v = it.first;
            int w = it.second;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                return true;
        }
    }
    return false;
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
    int src;
    cin >> src;
    bool b = Bellman_Ford(src, edges);
    if (b)
        cout << "Graph contains negative weight cycle\n";
    else
        cout << "Graph doesn't contain negative weight cycle\n";
    return 0;
}