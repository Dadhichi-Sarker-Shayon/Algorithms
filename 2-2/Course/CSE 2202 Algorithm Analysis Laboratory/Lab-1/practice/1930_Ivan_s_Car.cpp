#include <bits/stdc++.h>
using namespace std;
void add_edge(vector<vector<pair<int, int>>> &adj, int u, int v, int w)
{
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}
vector<int> Dijkstra(int src, int dest, vector<vector<pair<int, int>>> &adj)
{
    int n = adj.size();
    vector<int> dist(n, INT_MAX), parent(n, -1);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto it : adj[u])
        {
            int v = it.first;
            int w = it.second;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parent[v] = u;
            }
        }
    }
    vector<int> path;
    if (dist[dest] == INT_MAX)
    {
        return path;
    }

    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    map<pair<int,int>,char> ud;
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        add_edge(adj, u, v, 1);
        ud[{u,v}]='u';
        ud[{v,u}]='d';
    }
    int src, dest;
    cin >> src >> dest;
    vector<int> path = Dijkstra(src, dest, adj);
    string s;
    for(int i=0;i<path.size()-1;i++){
        if(ud[{path[i],path[i+1]}]=='u'){
            s.push_back('u');
        }else if(ud[{path[i],path[i+1]}]=='d'){
            s.push_back('d');
        }
    }
    int count=0;
    for(int i=0;i<s.size()-1;i++){

        if(s[i]!=s[i+1]){
            count++;
        }
    }
    cout<<count<<endl;

    return 0;
}