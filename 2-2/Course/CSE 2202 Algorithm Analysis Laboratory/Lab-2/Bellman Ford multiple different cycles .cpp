#include <bits/stdc++.h>
using namespace std;

void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &edges)
{
    edges[u].push_back({v, w});
}

vector<vector<int>> Bellman_Ford_cycle_print(int src, vector<vector<pair<int, int>>> &edges)
{

    int n = edges.size();
    vector<int> dist(n, INT_MAX), parent(n, -1), affected;
    vector<vector<int>> cycles;
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
                affected.push_back(v);
            }
        }
    }
    set<vector<int>> unique_cycles;
    for (int i = 0; i < affected.size(); i++)
    {
        vector<int> path;
        int x = affected[i];

        if (x == -1)
        {
            continue;
        }
        for (int i = 0; i < n; i++)
            x = parent[x];

        int curr = x;
        unordered_set<int>visited;
        do
        {
            if(visited.count(curr))break;
            visited.insert(curr);
            path.push_back(curr);
            curr = parent[curr];
        } while (curr != x);
        int min = min_element(path.begin(), path.end()) - path.begin();
        rotate(path.begin(), path.begin() + min, path.end());
        unique_cycles.insert(path);
    }
    for (auto it : unique_cycles)
    {
        cycles.push_back(it);
    }
    return cycles;
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
    vector<vector<int>> cycles = Bellman_Ford_cycle_print(src, edges);
    if (cycles.size() > 0)
    {
        cout << "Graph contains negative weight cycle\n";
 
        for (int i = 0; i < cycles.size(); i++)
        {
            cout << "cycle " << i << ": ";
            for (int j = 0; j < cycles[i].size(); j++)
            {
                cout << cycles[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
        cout << "Graph doesn't contain negative weight cycle\n";
    return 0;
}