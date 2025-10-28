#include<bits/stdc++.h>
using namespace std;

class DSU{
    vector<int>parent,rank;
    public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n);
        for(int i=0;i<n;i++)
        {
            parent[i]=i;
            rank[i]=1;
        }
    }
    int find(int u)
    {
        return parent[u]==u?u:parent[u]=find(parent[u]);
    }
    void union_set(int x,int y)
    {
        int parentx=find(x);
        int parenty=find(y);
        if(parentx==parenty)
        return;
        if(rank[parentx]<rank[parenty])
        {
            parent[parentx]=parenty;
        }
        else if(rank[parenty]<rank[parentx])
        {
            parent[parenty]=parentx;
        }
        else
        {
            parent[parenty]=parentx;
            rank[parentx]++;
        }


    }

};
bool comparator(vector<int>&a,vector<int>&b)
{
    return a[2]<b[2];
}
int kruskal(int n,vector<vector<int>>&edges,vector<vector<int>>&mst)
{
    DSU dsu(n);
    sort(edges.begin(),edges.end(),comparator);
    int total_weight=0;
    int count=0;
    for(auto &edge:edges)
    {
        int u=edge[0];
        int v=edge[1];
        int w=edge[2];
        if(dsu.find(u)!=dsu.find(v))
        {
            dsu.union_set(u,v);
            mst.push_back({u,v,w});
            total_weight+=w;
            count++;
            if(count==n-1)
            break;
        }
    }
    return total_weight;

}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>edges;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w});
    }
    vector<vector<int>>mst;
    int total_weight=kruskal(n,edges,mst);
    cout<<"Edges in the Minimum Spanning Tree are:\n";
    for(auto &edge:mst)
    {
        cout<<edge[0]<<" -- "<<edge[1]<<" with weight "<<edge[2]<<endl;
    }
    cout<<"Total weight of Minimum Spanning Tree is: "<<total_weight<<endl;
    return 0;
}