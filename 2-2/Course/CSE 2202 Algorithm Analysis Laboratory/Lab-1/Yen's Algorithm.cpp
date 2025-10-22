#include <bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &adj)
{
    adj[u].push_back({v, w});
    // adj[v].push_back({u,w});
}

vector<int> dijkstra(int src, int dest, vector<vector<pair<int, int>>> &adj)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    vector<int> dist(adj.size().INF_MAX);
    dist[src] = 0;
    vector<int> parent(adj.size(), -1);

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d != dist[u])
            continue;

        for (auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    vector<int> path;
    int curr = dest;
    if (dist[dest] == INT_MAX)
    {
        return path;
    }
    while (curr != src)
    {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    return path;
}
vector<vector<int>> Yens_algorithm(int src, int dest, int K, vector<vector<pair<int, int>>> &adj)
{
    vector<vector<int>> K_shortest_paths;
    vector<vector<int>> Candidate_paths;
    vector<int> first_path = dijkstra(src, dest, adj);
    if (first_path.empty())
    {
        return K_shortest_paths;
    }
    K_shortest_paths.push_back(first_path);
    set<pair<int, vector<int>>> candidates;
    for (int k = 1; k < K; k++)
    {
        for (int i = 0; i < K_shortest_paths[k - 1].size() - 1; i++)
        {
            int spur_node = K_shortest_paths[k - 1][i];
            vector<int> root_path(K_shortest_paths[k - 1].begin(), K_shortest_paths[k - 1].begin() + i + 1);
            vector<vector<pair<int, int>>> adj_copy = adj;
            for (auto path : K_shortest_paths)
            {
                if (path.size() > root_path.size() && equal(root_path.begin(), root_path.end(), path.begin()))
                {
                    int u = path[i];
                    int v = path[i + 1];
                    adj_copy[u].erase(remove_if(adj_copy[u].begin(), adj_copy[u].end(), [v](const pair<int, int> &p)
                                                { return p.first == v; }),
                                      adj_copy[u].end());
                }
                vector<int> spur_path = dijkstra(spur_node, dest, adj_copy);
                if(spur_path.empty())
                continue;

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

    dijkstra(src, adj, dist);

    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
            cout << "Distance of node " << i << " from source " << src << " is INF\n";
        else
            cout << "Distance of node " << i << " from source " << src << " is " << dist[i] << "\n";
    }
}
