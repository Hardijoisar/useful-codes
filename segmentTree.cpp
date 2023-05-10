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

class SGTree{

    vector<int> seg;

    public:
        SGTree(int n)
        {
            seg.resize(4*n+1);

        }

    void build(int ind, int low, int high, vector<int>& arr)
    {
        if(low==high)
        {
            seg[ind]=arr[low];
            return;
        }


        int mid= low + (high-low)/2;
        build(2*ind+1, low, mid,arr);
        build(2*ind+2, mid+1, high,arr);

        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);

    }

    int query(int ind, int low, int high, int l, int r)
    {
        // 3 cases 
        // no overlap
        if(r<low || l>high)
        {
            return INT_MAX;
        }
        // complete overlap
        if(l<=low && r>=high)
        {
            return seg[ind];
        }
        
        // partial overlap
        int mid= low+ (high-low)/2;
        int left = query(2*ind+1, low, mid, l, r);
        int right = query(2*ind+2, mid+1, high, l, r);

        return min(left, right);
    }

    void update(int ind, int low, int high, int index, int val, vector<int>&arr)
    {
        if(low==high)
        {
            seg[ind]=val;
            arr[low]=val;
            return;
        }

        int mid= low+ (high-low)/2;

        if(index<=mid) update(2*ind+1, low, mid, index, val,arr);
        else update(2*ind+2, mid+1, high, index, val,arr);

        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
    }

};

void solve()
{
    int n;
    cin>>n;
    vector<int> v1;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        v1.pb(x);
    }
    SGTree sg1(n);
    sg1.build(0,0,n-1,v1);
    
    int q;
    cin>>q;
    while(q--)
    {
        int type;
        cin>>type;
        if(type==1){
            int l,r;
            cin>>l>>r;
            // cout<<"l: "<<l<<" r: "<<r<<endl;
            int ans = sg1.query(0,0,n-1,l,r);
            cout<<"ans: "<<ans<<endl;
        }
        else{
            int index, val;
            cin>>index>>val;
            sg1.update(0, 0, n-1, index , val, v1);
            cout<<"Update done"<<endl;
        }
    }
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