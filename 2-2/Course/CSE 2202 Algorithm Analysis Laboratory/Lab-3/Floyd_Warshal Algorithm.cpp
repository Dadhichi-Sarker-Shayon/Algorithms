#include <bits/stdc++.h>
using namespace std;
void add_edge(vector<vector<int>> &graph, int u, int v, int w)
{
    graph[u][v] = w;
}
vector<vector<int>> floyd_warshall(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<vector<int>> dist = graph;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (dist[j][i] != INT_MAX && dist[i][k] != INT_MAX)
                {
                    dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                }
                
            }
        }
    }
    return dist;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++)
    {
        graph[i][i] = 0;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(graph, u, v, w);
    }
    vector<vector<int>> dist = floyd_warshall(graph);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INT_MAX)
            {
                cout << "shortest distance from " << i << " to " << j << " is " << "INF"<<endl;
            }
            else
            {
                cout << "shortest distance from " << i << " to " << j << " is " << dist[i][j]<<endl;
            }
        }
    }
}