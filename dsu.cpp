#include <bits/stdc++.h>
using namespace std;
#define flash ios_base::sync_with_stdio(0);cin.tie(NULL);
#define int long long
#define frl(i,a,b) for(int i=a;i<b;i++)
#define MOD 1000000007
#define pi (3.141592653589)
#define vs vector<string>
#define vi vector<int>
#define vc vector<char>
#define vpii vector<pair<int, int>>
#define vvii vector<vector<int, int>>
#define pb push_back

class DisjointSet{

    vector<int> parent, rank, size;

    public:

    DisjointSet(int n)
    {
        parent.resize(n+1, 0);
        rank.resize(n+1, 0);
        size.resize(n+1, 1);

        for(int i=0;i<=n;i++)
        {
            parent[i] = i;
        }
    }

    int findParent(int node)
    {
        if(node==parent[node])
        return node;

        return parent[node] = findParent(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ult_u = findParent(u);
        int ult_v = findParent(v);

        if(ult_u==ult_v) return;

        if(rank[ult_u]>rank[ult_v])
        {
            parent[ult_v] = ult_u;
        }
        else if(rank[ult_v]>rank[ult_u])
        {
            parent[ult_u] = ult_v;
        }
        else {
            parent[ult_u] = ult_v;
            rank[ult_v]++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ult_u = findParent(u);
        int ult_v = findParent(v);

        if(ult_u==ult_v) return;

        if(size[ult_u]>size[ult_v])
        {
            parent[ult_v] = ult_u;
            size[ult_u] = size[ult_u] + size[ult_v];
        }
        else if(size[ult_v]>=size[ult_u])
        {
            parent[ult_u] = ult_v;
            size[ult_v] = size[ult_v] + size[ult_u];
        }
    }


};

void solve()
{
    DisjointSet ds(7);
    ds.unionByRank(1, 2);
    ds.unionByRank(3, 2);
    ds.unionByRank(4, 5);
    ds.unionByRank(7, 6);
    ds.unionByRank(5, 6);
    if(ds.findParent(3) == ds.findParent(7)) cout<<"Same set."<<endl;
    else cout<<"Not in same set"<<endl;
    ds.unionByRank(3, 7);
    if(ds.findParent(3) == ds.findParent(7)) cout<<"Same set."<<endl;
    else cout<<"Not in same set"<<endl;

    DisjointSet ds1(7);
    ds1.unionBySize(1, 2);
    ds1.unionBySize(3, 2);
    ds1.unionBySize(4, 5);
    ds1.unionBySize(7, 6);
    ds1.unionBySize(5, 6);
    if(ds1.findParent(3) == ds1.findParent(7)) cout<<"Same set."<<endl;
    else cout<<"Not in same set"<<endl;
    ds1.unionBySize(3, 7);
    if(ds1.findParent(3) == ds1.findParent(7)) cout<<"Same set."<<endl;
    else cout<<"Not in same set"<<endl;

}


int32_t main()
{
flash
int tt=1;
// cin>>tt;
while(tt--)
{
solve();
}
return 0;
}