#include <bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int,int>>>& adj)
{
    adj[u].push_back({v, w});  // directed; add adj[v].push_back if undirected
}

void k_shortest_paths(int src, int k, vector<vector<pair<int,int>>>& adj, vector<vector<int>>& dist)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    dist[src].push_back(0);

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (!dist[u].empty() && d > dist[u].back()) continue;

        for (auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;
            int newDist = d + w;

            if (dist[v].size() < k)
            {
                dist[v].push_back(newDist);
                sort(dist[v].begin(), dist[v].end());
                pq.push({newDist, v});
            }
            else if (dist[v][k - 1] > newDist)
            {
                dist[v][k - 1] = newDist;
                sort(dist[v].begin(), dist[v].end());
                pq.push({newDist, v});
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        // assume 0-based nodes; if 1-based, uncomment next line
        // u--; v--;
        add_edge(u, v, w, adj);
    }

    int k;
    cin >> k;
    int src;
    cin >> src;
    // if 1-based input, uncomment:
    // src--;

    vector<vector<int>> dist(n);
    k_shortest_paths(src, k, adj, dist);

    for (int i = 0; i < n; i++)
    {
        cout << "The " << k << "-th shortest path from source " << src
             << " to node " << i << " is ";
        if (dist[i].size() < k)
            cout << "INF\n";
        else
            cout << dist[i][k - 1] << "\n";
    }

    return 0;
}
