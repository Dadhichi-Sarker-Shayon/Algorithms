#include <bits/stdc++.h>
using namespace std;
#define ll long long
void add_edge(vector<vector<pair<ll, ll>>> &adj, ll u, ll v, ll w)
{
    adj[u].push_back({v, w});
}

ll bellman_ford(ll src, ll dest, vector<vector<pair<ll, ll>>> &adj)
{
    ll n = adj.size()-1;
    vector<ll> dist(n+1, LLONG_MAX);
    dist[src] = 0;
    for (ll i = 0; i < n - 1; i++)
    {
        for (ll u = 1; u <= n; u++)
        {
            for (auto it : adj[u])
            {
                ll v = it.first;
                ll w = it.second;
                if (dist[u] != LLONG_MAX && dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    vector<ll> affected(n+1,0);
    for (ll u = 1; u <=n; u++)
    {
        for (auto it : adj[u])
        {
            ll v = it.first;
            ll w = it.second;
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v])
            {
                affected[v]=1;
            }
        }
    }
    priority_queue<ll> pq;
    for(ll i=1;i<=n;i++){
        if(affected[i]){
            pq.push(i);
        }
    }
    while(!pq.empty())
    {
        ll u=pq.top();
        pq.pop();
        for(auto it:adj[u]){
            ll v=it.first;
            if(!affected[v]){
                affected[v]=1;
                pq.push(v);
            }
        }
    }
    if(affected[dest]){
        return -1;
    }
    return -dist[dest];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> adj(n + 1);
    for (ll i = 0; i < m; i++)
    {
        ll u, v,w;
        cin >> u >> v>>w;
        add_edge(adj, u, v, -w);
    }
    
    ll res = bellman_ford(1, n, adj);
    {
        cout << res << "\n";
    }

    return 0;
}