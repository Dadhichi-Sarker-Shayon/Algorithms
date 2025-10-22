#include <bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &edges)
{
    edges[u].push_back({v, w});
}

vector<int> Bellman_Ford_cycle_print(int src, vector<vector<pair<int, int>>> &edges)
{

    int n = edges.size();
    vector<int> dist(n, INT_MAX), parent(n, -1), path;
    dist[src] = 0;
    int x = -1;
    for (int i = 0; i < n - 1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            for (auto it : edges[u])
            {
                int v = it.first;
                int w = it.second;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
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
            {
                x = v;
            }
        }
    }
    if (x == -1)
    {
        return path;
    }
    for (int i = 0; i < n; i++)
        x = parent[x];

    int curr = x;

    do
    {
        path.push_back(curr);
        curr = parent[curr];
    } while (curr != x);
    path.push_back(x);
    reverse(path.begin(), path.end());
    return path;
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
    vector<int> cycle = Bellman_Ford_cycle_print(src, edges);
    if (cycle.size() > 0)
    {
        cout << "Graph contains negative weight cycle\n";
        for (int i = 0; i < cycle.size(); i++)
        {
            cout << cycle[i] << " ";
        }
    }
    else
        cout << "Graph doesn't contain negative weight cycle\n";
    return 0;
}

