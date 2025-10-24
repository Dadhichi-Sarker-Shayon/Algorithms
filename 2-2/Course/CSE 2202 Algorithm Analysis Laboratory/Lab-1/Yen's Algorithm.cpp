#include <bits/stdc++.h>
using namespace std;
void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &adj)
{
    adj[u].push_back({v, w});
}

pair<vector<int>, int> dijkstra_path(int n, int src, int dest, vector<vector<pair<int, int>>> &adj)
{
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty())
    {
        pair<int, int> top = pq.top();
        pq.pop();
        int d = top.first;
        int u = top.second;

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
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    if (dist[dest] == INT_MAX)
        return make_pair(vector<int>(), INT_MAX);

    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    return make_pair(path, dist[dest]);
}

vector<pair<vector<int>, int>> yenKShortestPaths(vector<vector<pair<int, int>>> graph, int source, int target, int K)
{
    int n = graph.size();
    vector<pair<vector<int>, int>> A;

    pair<vector<int>, int> firstResult = dijkstra_path(n, source, target, graph);
    vector<int> path = firstResult.first;
    int cost = firstResult.second;

    if (path.empty())
        return A;

    A.push_back(make_pair(path, cost));
    set<pair<int, vector<int>>> B; 

    for (int k = 1; k < K; ++k)
    {
        vector<int> prevPath = A[k - 1].first;
        int prevCost = A[k - 1].second;

        for (int i = 0; i < prevPath.size() - 1; ++i)
        {
            int spurNode = prevPath[i];
            vector<int> rootPath(prevPath.begin(), prevPath.begin() + i + 1);

            // Copy the graph
            vector<vector<pair<int, int>>> tempGraph = graph;

            // Remove edges creating same prefix
            for (auto it : A)
            {
                vector<int> p = it.first;
                if (p.size() > i && vector<int>(p.begin(), p.begin() + i + 1) == rootPath)
                {
                    int u = p[i];
                    int v = p[i + 1];
                    auto &edges = tempGraph[u];
                    edges.erase(remove_if(edges.begin(), edges.end(),
                                          [v](pair<int, int> &edge)
                                          { return edge.first == v; }),
                                edges.end());
                }
            }

            // Remove all nodes in root path except spurNode
            for (auto node : rootPath)
            {
                if (node == spurNode)
                    continue;
                tempGraph[node].clear();
                for (auto &edges : tempGraph)
                {
                    edges.erase(remove_if(edges.begin(), edges.end(),
                                          [node](pair<int, int> &edge)
                                          { return edge.first == node; }),
                                edges.end());
                }
            }

            pair<vector<int>, int> spurResult = dijkstra_path(n, spurNode, target, tempGraph);
            vector<int> spurPath = spurResult.first;
            int spurCost = spurResult.second;

            if (!spurPath.empty())
            {
                // Merge root and spur
                vector<int> totalPath = rootPath;
                totalPath.insert(totalPath.end(), spurPath.begin() + 1, spurPath.end());

                // Calculate total cost
                int totalCost = 0;
                for (int j = 0; j < (int)totalPath.size() - 1; ++j)
                {
                    int u = totalPath[j];
                    int v = totalPath[j + 1];
                    for (auto e : graph[u])
                    {
                        if (e.first == v)
                        {
                            totalCost += e.second;
                            break;
                        }
                    }
                }
                B.insert(make_pair(totalCost, totalPath));
            }
        }

        if (B.empty())
            break;

        pair<int, vector<int>> best = *B.begin();
        int bestCost = best.first;
        vector<int> bestPath = best.second;
        B.erase(B.begin());
        A.push_back(make_pair(bestPath, bestCost));
    }

    return A;
}


int main()
{
    int n = 5;
    vector<vector<pair<int, int>>> graph(n);

    add_edge(0, 1, 4, graph);
    add_edge(0, 2, 5, graph);
    add_edge(1, 2, 2, graph);
    add_edge(1, 3, 4, graph);
    add_edge(2, 3, 4, graph);

    int source = 0, target = 3, K = 3;

    vector<pair<vector<int>, int>> paths = yenKShortestPaths(graph, source, target, K);

    for (int i = 0; i < (int)paths.size(); ++i)
    {
        cout << "Path " << i + 1 << ": ";
        for (int j = 0; j < (int)paths[i].first.size(); ++j)
        {
            cout << (char)('A' + paths[i].first[j]);
            if (j != (int)paths[i].first.size() - 1)
                cout << " --> ";
        }
        cout << "  &  Cost: " << paths[i].second << "\n";
    }

    return 0;
}
