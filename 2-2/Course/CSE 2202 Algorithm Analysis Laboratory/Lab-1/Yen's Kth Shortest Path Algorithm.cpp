#include <bits/stdc++.h>
using namespace std;
void add_edge(int u, int v, int w, vector<vector<pair<int, int>>> &adj)
{
    adj[u].push_back({v, w});
}
pair<vector<int>, int> dijkstra_pathxweight(int src, int dest, vector<vector<pair<int, int>>> &adj)
{
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d != dist[u])
        {
            continue;
        }
        for (auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[dest] == INT_MAX)
    {
        return make_pair(vector<int>(), INT_MAX);
    }
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return make_pair(path, dist[dest]);
}

vector<pair<vector<int>, int>> Yens_algorithm(vector<vector<pair<int, int>>> graph, int src, int dest, int K)
{
    int n = graph.size();
    vector<pair<vector<int>, int>> A;
    pair<vector<int>, int> firstResult = dijkstra_pathxweight(src, dest, graph);
    vector<int> path = firstResult.first;
    int cost = firstResult.second;
    A.push_back({path, cost});
    set<pair<vector<int>, int>> B;
    for (int k = 1; k < K; k++)
    {
        vector<int> prevPath = A[k - 1].first;
        int prevCost = A[k - 1].second;
        for (int i = 0; i < prevPath.size() - 1; i++)
        {
            int spurNode = prevPath[i];
            vector<int> rootPath(prevPath.begin(), prevPath.begin() + i + 1);
            vector<vector<pair<int, int>>> tempgraph = graph;
            for (auto it : A)
            {
                vector<int> currPath = it.first;
                if (currPath.size() > i && rootPath == vector<int>(currPath.begin(), currPath.begin() + i + 1))
                {
                    int u = currPath[i];
                    int v = currPath[i + 1];
                    auto &edges = tempgraph[u];
                    edges.erase(remove_if(edges.begin(), edges.end(),
                                          [v](pair<int, int> &edge)
                                          { return edge.first == v; }),
                                edges.end());
                }
            }

            for (auto node : rootPath)
            {
                if (node == spurNode)
                    continue;
                tempgraph[node].clear();
                for (auto &edges : tempgraph)
                {
                    edges.erase(remove_if(edges.begin(), edges.end(),
                                          [node](pair<int, int> &edge)
                                          { return edge.first == node; }),
                                edges.end());
                }
            }
            pair<vector<int>,int>spurResult=dijkstra_pathxweight(spurNode,dest,tempgraph);
            vector<int>spurPath=spurResult.first;
            int spurCost=spurResult.second;
            if(!spurPath.empty())
            {
                vector<int>totalPath=rootPath;
                totalPath.insert(totalPath.end(),spurPath.begin()+1,spurPath.end());
                int totalCost=0;
                for(int j=0;j<(int)totalPath.size()-1;j++)
                {
                    int u=totalPath[j];
                    int v=totalPath[j+1];
                    for(auto e:graph[u])
                    {
                        if(e.first==v)
                        {
                            totalCost+=e.second;
                            break;
                        }
                    }
                }
                B.insert({totalPath,totalCost});
            }

        }
         if(B.empty())
        {
            break;
        }
        pair<vector<int>,int> best = *B.begin();
        vector<int> bestPath = best.first;
        int bestCost = best.second;
        B.erase(B.begin());     
        A.push_back({bestPath, bestCost});
       
    }
    return A;
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w, graph);
    }
    int src, dest, K;
    cin >> src >> dest >> K;
    vector<pair<vector<int>, int>> paths = Yens_algorithm(graph, src, dest, K);
    for (int i = 0; i < paths.size(); i++)
    {
        cout << "Path " << i + 1 << ": ";
        for (int node : paths[i].first)
        {
            cout << node << " ";
        }
        cout << " Cost: " << paths[i].second << "\n";
    }
    return 0;
}
