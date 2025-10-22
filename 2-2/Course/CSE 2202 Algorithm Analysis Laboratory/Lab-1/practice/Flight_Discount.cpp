#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;

struct Edge {
    ll to, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<vector<pair<ll,ll>>> adj(n + 1);
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<ll> dist1(n + 1, INF), dist2(n + 1, INF);
    dist1[1] = 0;

    // priority_queue stores vector<ll>: {distance, node, usedDiscount}
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
    pq.push({0, 1, 0});

    while (!pq.empty()) {
        vector<ll> top = pq.top(); pq.pop();
        ll d = top[0], u = top[1], used = top[2];

        if (used && d > dist2[u]) continue;
        if (!used && d > dist1[u]) continue;

        for (auto it : adj[u]) {
            ll v = it.first, w = it.second;

            // Case 1: Go normally without discount
            if (!used && dist1[u] + w < dist1[v]) {
                dist1[v] = dist1[u] + w;
                pq.push({dist1[v], v, 0});
            }

            // Case 2: Use discount now
            if (!used && dist1[u] + w/2 < dist2[v]) {
                dist2[v] = dist1[u] + w/2;
                pq.push({dist2[v], v, 1});
            }

            // Case 3: Already used discount
            if (used && dist2[u] + w < dist2[v]) {
                dist2[v] = dist2[u] + w;
                pq.push({dist2[v], v, 1});
            }
        }
    }

    cout << dist2[n] << "\n";
    return 0;
}
